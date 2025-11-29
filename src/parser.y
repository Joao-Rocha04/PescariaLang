%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* Declarações do lexer / erro */
int yylex(void);
void yyerror(const char *s);

/* ========= Saída de código ========= */
FILE *out;

/* --------- Tabela de símbolos simples: IDENT -> índice de variável --------- */

#define MAX_VARS 256

typedef struct {
    char *name;
    int   index;
} Symbol;

static Symbol symtab[MAX_VARS];
static int sym_count = 0;

int lookup_symbol(const char *name) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(symtab[i].name, name) == 0)
            return symtab[i].index;
    }
    return -1;
}

int declare_symbol(const char *name) {
    int idx = lookup_symbol(name);
    if (idx >= 0) {
        /* já existe: só retorna o índice */
        return idx;
    }
    if (sym_count >= MAX_VARS) {
        fprintf(stderr, "Muitas variáveis\n");
        exit(1);
    }
    symtab[sym_count].name = strdup(name);
    symtab[sym_count].index = sym_count;
    return sym_count++;
}

/* --------- Emissão de assembly --------- */

void emit(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    fprintf(out, "\n");
    va_end(ap);
}

/* --------- Labels numéricos: L0, L1, ... --------- */

static int label_counter = 0;

int new_label_id() {
    return label_counter++;
}

void label_name(char *buf, int id) {
    sprintf(buf, "L%d", id);
}

/* Pilha de labels para while */
typedef struct {
    int l_start;
    int l_end;
} LoopLabel;

LoopLabel loop_stack[128];
int loop_sp = 0;

void push_loop(int s, int e) {
    loop_stack[loop_sp].l_start = s;
    loop_stack[loop_sp].l_end   = e;
    loop_sp++;
}

void pop_loop(int *s, int *e) {
    loop_sp--;
    *s = loop_stack[loop_sp].l_start;
    *e = loop_stack[loop_sp].l_end;
}

void peek_loop(int *s, int *e) {
    *s = loop_stack[loop_sp-1].l_start;
    *e = loop_stack[loop_sp-1].l_end;
}

/* Pilha de labels para if/else */
typedef struct {
    int l_else;
    int l_end;
} IfLabel;

IfLabel if_stack[128];
int if_sp = 0;

void push_if(int l_else, int l_end) {
    if_stack[if_sp].l_else = l_else;
    if_stack[if_sp].l_end  = l_end;
    if_sp++;
}

void pop_if(int *l_else, int *l_end) {
    if_sp--;
    *l_else = if_stack[if_sp].l_else;
    *l_end  = if_stack[if_sp].l_end;
}

void peek_if(int *l_else, int *l_end) {
    *l_else = if_stack[if_sp-1].l_else;
    *l_end  = if_stack[if_sp-1].l_end;
}

%}

%union {
    int ival;
    char* sval;
}

%token <sval> IDENT
%token <ival> NUMBER
%token LET NUM BOOL IF ELSE WHILE LOG
%token PUXAR_LINHA RECOLHER_LINHA TROCAR_ISCA
%token AUMENTAR_PROF REDUZIR_PROF DEFINIR_PROF
%token SONAR PEIXE_NA_LINHA PROFUNDIDADE
%token TRUE FALSE
%token EQ NEQ GE LE GT LT
%token AND OR NOT
%token ASSIGN SEMICOLON LPAREN RPAREN LBRACE RBRACE PLUS MINUS TIMES DIVIDE COLON

%left OR
%left AND
%left EQ NEQ GT LT GE LE
%left PLUS MINUS
%left TIMES DIVIDE
%right NOT

%%

program
    : /* vazio */
    | program decl
    | program stmt
    ;

/* ---------- Declaração de variáveis ---------- */

decl
    : LET IDENT COLON type opt_assign SEMICOLON
      {
        /* Se não inicializou em opt_assign, só garante a declaração */
        declare_symbol($2);
      }
    ;

type
    : NUM
    | BOOL
    ;

/* 
   opt_assign:
   - se vazio: só declara (feito em decl)
   - se tem ASSIGN expr: expr deixa valor na pilha e fazemos STORE no índice
*/
opt_assign
    : /* vazio */
    | ASSIGN expr
      {
        /* A variável é o IDENT antes do COLON,
           mas para simplificar, vamos assumir que
           'decl' já chamou declare_symbol e aqui
           só fazemos nada. Se quiser suportar inicialização,
           precisaria capturar o nome do IDENT via ação intermediária. */
        /* opcional: emitir STORE para última variável declarada se você guardar o índice */
      }
    ;

/* ---------- Statements ---------- */

stmt
    : assign
    | action
    | if_stmt
    | while_stmt
    | log_stmt
    | SEMICOLON
    ;

/* atribuição: IDENT = expr; */

assign
    : IDENT ASSIGN expr SEMICOLON
      {
        int idx = lookup_symbol($1);
        if (idx < 0) {
            fprintf(stderr, "Variável não declarada: %s\n", $1);
            exit(1);
        }
        /* expr deixou o valor no topo da pilha */
        emit("STORE %d", idx);
      }
    ;

/* ---------- IF / ELSE ---------- */

/* if sem else */
if_stmt
    : IF if_start LPAREN expr RPAREN if_after_cond block if_end_no_else
    /* if com else */
    | IF if_start LPAREN expr RPAREN if_after_cond block ELSE if_else_part block if_end_with_else
    ;

/* cria labels e empilha na pilha de if */
if_start
    : /* vazio */
      {
        int l_else = new_label_id();
        int l_end  = new_label_id();
        push_if(l_else, l_end);
      }
    ;

/* depois de avaliar a condição (expr), gera JUMP_IF_FALSE L_ELSE */
if_after_cond
    : /* vazio */
      {
        int l_else, l_end;
        char buf[32];
        peek_if(&l_else, &l_end);
        label_name(buf, l_else);
        emit("JUMP_IF_FALSE %s", buf);
      }
    ;

/* if sem else: gera label else e depois label end (else vazio) */
if_end_no_else
    : /* vazio */
      {
        int l_else, l_end;
        char buf_else[32], buf_end[32];
        pop_if(&l_else, &l_end);
        label_name(buf_else, l_else);
        label_name(buf_end, l_end);
        emit("%s:", buf_else);  /* bloco else vazio */
        emit("%s:", buf_end);   /* fim do if */
      }
    ;

/* ponto logo depois de 'ELSE' antes do bloco else */
if_else_part
    : /* vazio */
      {
        int l_else, l_end;
        char buf_else[32], buf_end[32];

        peek_if(&l_else, &l_end);
        label_name(buf_else, l_else);
        label_name(buf_end,  l_end);

        /* pular o else se o if foi verdadeiro */
        emit("JUMP %s", buf_end);
        /* marcar começo do else */
        emit("%s:", buf_else);
      }
    ;

/* fim do if com else */
if_end_with_else
    : /* vazio */
      {
        int l_else, l_end;
        char buf_end[32];
        pop_if(&l_else, &l_end);
        label_name(buf_end, l_end);
        emit("%s:", buf_end);
      }
    ;

/* ---------- WHILE ---------- */

while_stmt
    : WHILE while_start LPAREN expr RPAREN while_after_cond block while_end
    ;

while_start
    : /* vazio */
      {
        int l_start = new_label_id();
        int l_end   = new_label_id();

        push_loop(l_start, l_end);

        char buf_start[32];
        label_name(buf_start, l_start);
        /* label do início do loop */
        emit("%s:", buf_start);
      }
    ;

/* depois da condição, pula para L_END se for falsa */
while_after_cond
    : /* vazio */
      {
        int l_start, l_end;
        char buf_end[32];
        peek_loop(&l_start, &l_end);
        label_name(buf_end, l_end);
        emit("JUMP_IF_FALSE %s", buf_end);
      }
    ;

/* no final do bloco, volta para L_START e emite L_END */
while_end
    : /* vazio */
      {
        int l_start, l_end;
        char buf_start[32], buf_end[32];

        pop_loop(&l_start, &l_end);
        label_name(buf_start, l_start);
        label_name(buf_end,   l_end);

        emit("JUMP %s", buf_start);
        emit("%s:", buf_end);
      }
    ;

/* ---------- Blocos ---------- */

block
    : LBRACE stmt_list RBRACE
    ;

stmt_list
    : /* vazio */
    | stmt_list stmt
    ;

/* ---------- Log ---------- */

log_stmt
    : LOG LPAREN expr RPAREN SEMICOLON
      {
        emit("LOG");
      }
    ;

/* ---------- Ações ---------- */

action
    : PUXAR_LINHA LPAREN RPAREN SEMICOLON
      {
        emit("ACTION PUXAR_LINHA");
      }
    | RECOLHER_LINHA LPAREN RPAREN SEMICOLON
      {
        emit("ACTION RECOLHER_LINHA");
      }
    | TROCAR_ISCA LPAREN expr RPAREN SEMICOLON
      {
        emit("ACTION TROCAR_ISCA");
      }
    | AUMENTAR_PROF LPAREN expr RPAREN SEMICOLON
      {
        emit("ACTION AUMENTAR_PROF");
      }
    | REDUZIR_PROF LPAREN expr RPAREN SEMICOLON
      {
        emit("ACTION REDUZIR_PROF");
      }
    | DEFINIR_PROF LPAREN expr RPAREN SEMICOLON
      {
        emit("ACTION SET_PROF");
      }
    ;

/* ---------- Expressões ---------- */

expr
    : or_expr
    ;

or_expr
    : and_expr
    | or_expr OR and_expr
      { emit("OR"); }
    ;

and_expr
    : not_expr
    | and_expr AND not_expr
      { emit("AND"); }
    ;

not_expr
    : rel_expr
    | NOT rel_expr
      { emit("NOT"); }
    ;

rel_expr
    : sum_expr
    | sum_expr EQ sum_expr
      { emit("CMP_EQ"); }
    | sum_expr NEQ sum_expr
      { emit("CMP_NE"); }
    | sum_expr GT sum_expr
      { emit("CMP_GT"); }
    | sum_expr LT sum_expr
      { emit("CMP_LT"); }
    | sum_expr GE sum_expr
      { emit("CMP_GE"); }
    | sum_expr LE sum_expr
      { emit("CMP_LE"); }
    ;

sum_expr
    : term
    | sum_expr PLUS term
      { emit("ADD"); }
    | sum_expr MINUS term
      { emit("SUB"); }
    ;

term
    : factor
    | term TIMES factor
      { emit("MUL"); }
    | term DIVIDE factor
      { emit("DIV"); }
    ;

factor
    : NUMBER
      {
        emit("PUSH %d", $1);
      }
    | TRUE
      {
        emit("PUSH 1");
      }
    | FALSE
      {
        emit("PUSH 0");
      }
    | SONAR
      {
        emit("READ_SENSOR SONAR");
      }
    | PEIXE_NA_LINHA
      {
        emit("READ_SENSOR PEIXE");
      }
    | PROFUNDIDADE
      {
        emit("READ_SENSOR PROF");
      }
    | IDENT
      {
        int idx = lookup_symbol($1);
        if (idx < 0) {
            fprintf(stderr, "Variável não declarada: %s\n", $1);
            exit(1);
        }
        emit("LOAD %d", idx);
      }
    | LPAREN expr RPAREN
      { /* nada: expr já emitiu código */ }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main() {
    out = stdout;  /* assembly na saída padrão */
    yyparse();
    /* garante fim de programa para a VM */
    emit("HALT");
    return 0;
}
