
# PescariaLang — Linguagem de Controle da PescariaVM

**PescariaLang** é uma linguagem de programação criada para controlar a **PescariaVM**, uma máquina virtual minimalista que simula ações e sensores de pesca.  
Este projeto demonstra todo o pipeline clássico de construção de um compilador:

> **Linguagem → Lexer (Flex) → Parser (Bison) → Assembly → Execução na VM**


---



#  A Máquina Virtual — PescariaVM

A **PescariaVM** é uma máquina virtual simples inspirada em máquinas de Minsky, projetada especificamente para executar o assembly gerado pelo compilador da PescariaLang.

---

##  Registradores Mutáveis

| Registrador | Função |
|------------|--------|
| **R_A** | Registrador geral A |
| **R_B** | Registrador geral B |
| **PROF** | Profundidade alvo da isca (cm) |
| **ISCA** | Tipo de isca (enum inteiro) |

---

##  Sensores (somente leitura)

| Sensor | Significado |
|--------|-------------|
| **SONAR** | Número de peixes detectados |
| **PEIXE** | 1 se há peixe fisgado; 0 caso contrário |
| **PROFUNDIDADE_ATUAL** | Profundidade atual real da isca |

A leitura é feita com:

```asm
READ_SENSOR SONAR
```

---

##  Pilha

A VM possui uma pilha LIFO:

```asm
PUSH 10
POP R_A
```

Usada internamente para avaliação de expressões.

---

##  Instruções da PescariaVM

| Instrução | Descrição |
|-----------|-----------|
| `PUSH n` | Empilha n |
| `POP R` | Desempilha para registrador |
| `LOAD i` | Empilha variável local |
| `STORE i` | Armazena topo da pilha em variável |
| `READ_SENSOR nome` | Empilha valor do sensor |
| `ADD`, `SUB`, `MUL`, `DIV` | Aritmética |
| `CMP_EQ`, `CMP_NE`, `CMP_GT`, `CMP_LT`, `CMP_GE`, `CMP_LE` | Comparações |
| `AND`, `OR`, `NOT` | Operações lógicas |
| `JUMP label` | Salto |
| `JUMP_IF_FALSE label` | Salta se valor no topo for 0 |
| `ACTION nome` | Executa ação de pesca |
| `LOG` | Imprime topo |
| `HALT` | Encerra execução |

---

##  Ambiente Simulado

A VM implementa um ambiente básico:

- `SONAR` diminui aos poucos  
- `PEIXE` pode ocorrer aleatoriamente  
- `PROFUNDIDADE_ATUAL` converge lentamente ao alvo `PROF`  

Isso é suficiente para testar condicionais, loops e ações.

---

#  A Linguagem — PescariaLang

---

##  Sensores

- `sonar`
- `peixe_na_linha`
- `profundidade`

---

##  Ações

```c
puxar_linha();
recolher_linha();
trocar_isca(x);
aumentar_profundidade(x);
reduzir_profundidade(x);
definir_profundidade(x);
```

---

##  Estruturas

```c
if (expr) { ... } else { ... }

while (expr) { ... }

log(expr);
```

---

#  Exemplo: pescar.fl

```c
let peixe : bool = true;
let profund : num = 10;

while (sonar > 0) {
  if (peixe_na_linha) {
    puxar_linha();
    recolher_linha();
  } else {
    aumentar_profundidade(5);
  }
}
```

---

#  Compilação e Execução

### 1 Compilar tudo + gerar `.pvm` + executar na VM

Na pasta `src/`:

```bash
make run
```

O Makefile:

1. Gera parser e lexer  
2. Compila o executável `pescaria`  
3. Converte `pescar.fl` em `pescar.pvm`  
4. Executa a VM automaticamente  

---

###  Gerar `.pvm` manualmente

```bash
./pescaria < ../examples.fl/pescar.fl > ../examples.fl/pescar.pvm
```

###  Rodar VM manualmente

```bash
python3 pescaria_vm.py ../examples.fl/pescar.pvm
```

---

#  Estrutura do Repositório

```
PescariaLang/
├── examples.fl/
│   └── pescar.fl
├── src/
│   ├── lexer.l
│   ├── parser.y
│   ├── pescaria_vm.py
│   ├── Makefile
│   └── pescaria (gerado)
├── Pescaria.ebnf
└── README.md
```

---

#  Gramática EBNF da Linguagem

```ebnf
PROGRAM     = { DECL | STMT } ;

DECL        = "let" IDENT ":" TYPE [ "=" EXPR ] ";" ;
TYPE        = "num" | "bool" ;

STMT        = ASSIGN | ACTION | IF | WHILE | LOG | ";" ;

ASSIGN      = IDENT "=" EXPR ";" ;

IF          = "if" "(" EXPR ")" BLOCK [ "else" BLOCK ] ;
WHILE       = "while" "(" EXPR ")" BLOCK ;

BLOCK       = "{" { STMT } "}" ;

LOG         = "log" "(" EXPR ")" ";" ;

ACTION      = "puxar_linha" "(" ")" ";"
            | "recolher_linha" "(" ")" ";"
            | "trocar_isca" "(" EXPR_NUM ")" ";"
            | "aumentar_profundidade" "(" EXPR_NUM ")" ";"
            | "reduzir_profundidade" "(" EXPR_NUM ")" ";"
            | "definir_profundidade" "(" EXPR_NUM ")" ";" ;

EXPR        = OR ;
OR          = AND { "||" AND } ;
AND         = NOT { "&&" NOT } ;
NOT         = [ "!" ] REL ;

REL         = SUM [ COMPARISON SUM ] ;
COMPARISON  = "==" | "!=" | ">" | "<" | ">=" | "<=" ;

SUM         = TERM { ("+" | "-") TERM } ;
TERM        = FACT { ("*" | "/") FACT } ;

FACT        = NUMBER
            | "true" | "false"
            | SENSOR
            | IDENT
            | "(" EXPR ")" ;

EXPR_NUM    = EXPR ;

SENSOR      = "sonar" | "peixe_na_linha" | "profundidade" ;

IDENT       = LETTER { LETTER | DIGIT | "_" } ;
NUMBER      = DIGIT { DIGIT } ;
```

---

#  Observações para Avaliação

- Linguagem criada do zero  
- EBNF formal e completa  
- Lexer e Parser com Flex/Bison  
- Geração de assembly própria  
- VM original com registradores, sensores, pilha e ISA mínima  
- Makefile automatizado  
- Exemplo funcional  
- Documentação completa — este arquivo

---

#  Conclusão

**PescariaLang** demonstra o ciclo completo de um compilador real, capaz de transformar uma linguagem personalizada em assembly executável em uma máquina virtual criada especificamente para este projeto acadêmico.
