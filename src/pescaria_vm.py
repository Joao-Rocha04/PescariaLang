#!/usr/bin/env python3
import sys
import argparse
from typing import List, Tuple, Dict, Any

# Registradores "genéricos"
REGS = {"R0", "R1"}

# Sensores disponíveis
SENSORS = {"SONAR", "PEIXE", "PROF"}


def parse_program(lines: List[str]) -> Tuple[List[Tuple[str, List[str]]], Dict[str, int]]:
    """
    Parser de assembly estilo:
      label:
      OP arg1 arg2 ...

    Com comentários iniciados por ';' ou '#', exatamente como na VM de exemplo.
    """
    prog: List[Tuple[str, List[str]]] = []
    labels: Dict[str, int] = {}

    for line in lines:
        # remove comentários
        if ";" in line:
            line = line.split(";", 1)[0]
        if "#" in line:
            line = line.split("#", 1)[0]
        line = line.strip()
        if not line:
            continue

        # Pode ter "label:" antes da instrução
        while True:
            colon = line.find(":")
            if colon == -1:
                break
            label = line[:colon].strip()
            if not label:
                break
            if label in labels:
                raise ValueError(f"Label duplicado: {label}")
            labels[label] = len(prog)
            line = line[colon + 1 :].strip()
            if not line:
                break

        if not line:
            continue

        parts = line.split()
        op = parts[0].upper()
        args = parts[1:]
        prog.append((op, args))

    return prog, labels


def resolve_label_or_int(arg: str, labels: Dict[str, int]) -> int:
    if arg in labels:
        return labels[arg]
    return int(arg)


def clamp(v: int, lo: int, hi: int) -> int:
    return max(lo, min(hi, v))


def update_sensors(sens: Dict[str, int]):
    """
    Atualização bem simples/determinística só para simular dinâmica:

    - SONAR começa em 5 e vai caindo aos poucos até 0.
    - PROF é alterada pelas ACTIONs.
    - PEIXE = 1 quando PROF está em um "ponto bom" (ex.: 10..15), senão 0.
    """
    # SONAR decai até 0
    if sens["SONAR"] > 0:
        sens["SONAR"] -= 1

    # peixe_na_linha "aparece" se profundidade estiver em um range
    if 10 <= sens["PROF"] <= 15:
        sens["PEIXE"] = 1
    else:
        sens["PEIXE"] = 0


def run(prog: List[Tuple[str, List[str]]], labels: Dict[str, int], step_limit: int = 100000):

    # Registradores
    regs: Dict[str, int] = {r: 0 for r in REGS}

    # Variáveis (você pode aumentar esse tamanho, se quiser)
    VAR_COUNT = 256
    vars_mem = [0] * VAR_COUNT

    # Sensores
    sens: Dict[str, int] = {
        "SONAR": 5,
        "PEIXE": 0,
        "PROF": 10,
    }

    stack: List[int] = []

    pc = 0
    steps = 0

    def get_reg(name: str) -> str:
        up = name.upper()
        if up not in REGS:
            raise ValueError(f"Registrador inválido: {name}")
        return up

    while 0 <= pc < len(prog):
        if steps >= step_limit:
            raise RuntimeError(f"Step limit atingido ({step_limit}). Possível loop infinito.")

        op, args = prog[pc]

        # -------------- EXECUÇÃO DAS INSTRUÇÕES --------------
        if op == "PUSH":
            # PUSH n
            n = int(args[0])
            stack.append(n)
            pc += 1

        elif op == "LOAD":
            idx = int(args[0])
            if not (0 <= idx < VAR_COUNT):
                raise RuntimeError(f"LOAD: índice de variável fora do range: {idx}")
            stack.append(vars_mem[idx])
            pc += 1

        elif op == "STORE":
            idx = int(args[0])
            if not (0 <= idx < VAR_COUNT):
                raise RuntimeError(f"STORE: índice de variável fora do range: {idx}")
            if not stack:
                raise RuntimeError("STORE: stack underflow")
            vars_mem[idx] = stack.pop()
            pc += 1

        elif op in {"ADD", "SUB", "MUL", "DIV"}:
            if len(stack) < 2:
                raise RuntimeError(f"{op}: stack underflow")
            b = stack.pop()
            a = stack.pop()
            if op == "ADD":
                stack.append(a + b)
            elif op == "SUB":
                stack.append(a - b)
            elif op == "MUL":
                stack.append(a * b)
            elif op == "DIV":
                if b == 0:
                    raise ZeroDivisionError("DIV por zero na VM")
                stack.append(a // b)
            pc += 1

        elif op == "NEG":
            if not stack:
                raise RuntimeError("NEG: stack underflow")
            a = stack.pop()
            stack.append(-a)
            pc += 1

        elif op == "NOT":
            if not stack:
                raise RuntimeError("NOT: stack underflow")
            a = stack.pop()
            stack.append(0 if a else 1)
            pc += 1

        elif op in {"AND", "OR"}:
            if len(stack) < 2:
                raise RuntimeError(f"{op}: stack underflow")
            b = stack.pop()
            a = stack.pop()
            if op == "AND":
                stack.append(1 if (a != 0 and b != 0) else 0)
            else:
                stack.append(1 if (a != 0 or b != 0) else 0)
            pc += 1

        elif op.startswith("CMP_"):
            if len(stack) < 2:
                raise RuntimeError(f"{op}: stack underflow")
            b = stack.pop()
            a = stack.pop()
            if op == "CMP_EQ":
                stack.append(1 if a == b else 0)
            elif op == "CMP_NE":
                stack.append(1 if a != b else 0)
            elif op == "CMP_GT":
                stack.append(1 if a > b else 0)
            elif op == "CMP_LT":
                stack.append(1 if a < b else 0)
            elif op == "CMP_GE":
                stack.append(1 if a >= b else 0)
            elif op == "CMP_LE":
                stack.append(1 if a <= b else 0)
            else:
                raise ValueError(f"Instrução CMP_ desconhecida: {op}")
            pc += 1

        elif op == "READ_SENSOR":
            sname = args[0].upper()
            if sname not in SENSORS:
                raise ValueError(f"Sensor desconhecido: {sname}")
            stack.append(sens[sname])
            pc += 1

        elif op == "ACTION":
            aname = args[0].upper()

            if aname == "PUXAR_LINHA":
                print("[ACTION] puxar_linha()")
                # se quiser, pode alterar sensores aqui (ex: SONAR-- etc.)

            elif aname == "RECOLHER_LINHA":
                print("[ACTION] recolher_linha()")

            elif aname == "TROCAR_ISCA":
                if not stack:
                    raise RuntimeError("TROCAR_ISCA: stack underflow")
                isca = stack.pop()
                print(f"[ACTION] trocar_isca({isca})")

            elif aname == "AUMENTAR_PROF":
                if not stack:
                    raise RuntimeError("AUMENTAR_PROF: stack underflow")
                delta = stack.pop()
                sens["PROF"] += max(0, delta)
                print(f"[ACTION] aumentar_profundidade({delta}) -> PROF={sens['PROF']}")

            elif aname == "REDUZIR_PROF":
                if not stack:
                    raise RuntimeError("REDUZIR_PROF: stack underflow")
                delta = stack.pop()
                sens["PROF"] -= max(0, delta)
                print(f"[ACTION] reduzir_profundidade({delta}) -> PROF={sens['PROF']}")

            elif aname == "SET_PROF":
                if not stack:
                    raise RuntimeError("SET_PROF: stack underflow")
                target = stack.pop()
                sens["PROF"] = max(0, target)
                print(f"[ACTION] definir_profundidade({target}) -> PROF={sens['PROF']}")

            else:
                raise ValueError(f"ACTION desconhecida: {aname}")

            pc += 1

        elif op == "JUMP":
            target = resolve_label_or_int(args[0], labels)
            pc = target

        elif op == "JUMP_IF_FALSE":
            if not stack:
                raise RuntimeError("JUMP_IF_FALSE: stack underflow")
            cond = stack.pop()
            if cond == 0:
                target = resolve_label_or_int(args[0], labels)
                pc = target
            else:
                pc += 1

        elif op == "LOG":
            if not stack:
                raise RuntimeError("LOG: stack underflow")
            v = stack.pop()
            print(f"[LOG] {v}")
            pc += 1

        elif op == "HALT":
            print("[VM] HALT")
            break

        else:
            raise ValueError(f"Instrução desconhecida: {op}")

        # Atualiza sensores a cada tick
        update_sensors(sens)
        steps += 1


def main():
    ap = argparse.ArgumentParser(description="PescariaVM – interpretador de assembly da PescariaLang")
    ap.add_argument("file", help="caminho para arquivo .pvm (ou .asm)")
    ap.add_argument(
        "--steps",
        type=int,
        default=100000,
        help="limite de passos (anti-loop infinito)",
    )
    args = ap.parse_args()

    with open(args.file, "r", encoding="utf-8") as f:
        lines = f.readlines()

    prog, labels = parse_program(lines)
    run(prog, labels, step_limit=args.steps)


if __name__ == "__main__":
    main()
