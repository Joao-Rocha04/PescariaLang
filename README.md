# PescariaLang — Resumo de Alto Nível

**PescariaLang** é uma linguagem de domínio (DSL) para controlar uma máquina virtual de pesca (**PescariaVM**).  
Ela expõe **sensores** do ambiente aquático e oferece **ações** de controle de linha, profundidade e isca por meio de comandos simples e declarativos.

---


## Sensores (somente leitura)
- **`sonar`**: número de peixes detectados nas proximidades (inteiro ≥ 0).  
  *Uso típico*: decidir quando aproximar a isca ou recolher.
- **`peixe_na_linha`**: indica se há peixe fisgado (0 = não, 1 = sim).  
  *Uso típico*: acionar um “puxão” somente quando houver peixe.
- **`profundidade`**: profundidade atual da **isca** (em centímetros, 0 = superfície).  
  *Uso típico*: manter a isca numa faixa desejada (p. ex., 60–90 cm).

> Sensores são lidos em expressões e condições. Não são alteráveis por programas.

---

## Controles internos (ajustados por ações)
- **Isca (`ISCA`)**: tipo de isca selecionada (enumerado; ex.: 0=milho, 1=minhoca, 2=spoon…).  
  *Finalidade*: testar variações e adaptar-se ao comportamento dos peixes.
- **Linha**: estado e posição da linha (puxar, recolher, profundidade alvo).  
  *Finalidade*: fisgar, trazer o peixe e posicionar a isca no nível desejado.

---

## Ações da linguagem (alto nível)

> As ações abaixo descrevem **o que fazem** e **quais parâmetros recebem** (tipo/unidade/intervalo esperado).  
> A implementação de baixo nível é responsabilidade do compilador/VM.

- **`puxar_linha`**  
  Dá um tranco para fisgar o peixe quando houver captura.  

- **`recolher_linha`**  
  Recolhe a linha continuamente.  

- **`trocar_isca codigo`**  
  Troca o tipo de isca utilizado.  
  **Parâmetro**: `codigo` (inteiro enumerado; ex.: 0=milho, 1=minhoca, 2=spoon…).

- **`aumentar_profundidade delta_cm`**  
  Aumenta a profundidade alvo da isca (leva a isca **mais fundo**).  
  **Parâmetro**: `delta_cm` (inteiro ≥ 0, em centímetros).

- **`reduzir_profundidade delta_cm`**  
  Reduz a profundidade alvo da isca (leva a isca **mais para cima**).  
  **Parâmetro**: `delta_cm` (inteiro ≥ 0, em centímetros).

- **`definir_profundidade alvo_cm`**  
  Define diretamente a profundidade alvo da isca.  
  **Parâmetro**: `alvo_cm` (inteiro ≥ 0, em centímetros).

---

## Estruturas de controle (esboço de sintaxe)


### Condicional: `if … else`
```c
if (EXPR) {
  /* bloco-then */
} else {
  /* bloco-else (opcional) */
}
```

### Laço

```c
while (EXPR) {
  /* corpo do laço */
}
```

## EBNF

```c
# PescariaLang — EBNF v2.0 (estilo C para if/while)

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
            | "trocar_isca" "(" EXPR_NUM ")" ";"                /* enum da isca */
            | "aumentar_profundidade" "(" EXPR_NUM ")" ";"      /* Δ cm ≥ 0 */
            | "reduzir_profundidade" "(" EXPR_NUM ")" ";"       /* Δ cm ≥ 0 */
            | "definir_profundidade" "(" EXPR_NUM ")" ";" ;     /* alvo cm ≥ 0 */

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

EXPR_NUM    = EXPR ;  /* deve avaliar para número inteiro */

SENSOR      = "sonar" | "peixe_na_linha" | "profundidade" ;

IDENT       = LETTER { LETTER | DIGIT | "_" } ;
NUMBER      = DIGIT { DIGIT } ;

LETTER      = "A" | ... | "Z" | "a" | ... | "z" ;
DIGIT       = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

/* Espaços/tabs ignorados. Comentários:
   // linha inteira
   /* bloco *\/
*/




```

