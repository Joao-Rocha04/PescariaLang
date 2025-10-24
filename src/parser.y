%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
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

decl
    : LET IDENT COLON type opt_assign SEMICOLON
    ;

type
    : NUM
    | BOOL
    ;

opt_assign
    : /* vazio */
    | ASSIGN expr
    ;

stmt
    : assign
    | action
    | if_stmt
    | while_stmt
    | log_stmt
    | SEMICOLON
    ;

assign
    : IDENT ASSIGN expr SEMICOLON
    ;

if_stmt
    : IF LPAREN expr RPAREN block
    | IF LPAREN expr RPAREN block ELSE block
    ;

while_stmt
    : WHILE LPAREN expr RPAREN block
    ;

block
    : LBRACE stmt_list RBRACE
    ;

stmt_list
    : /* vazio */
    | stmt_list stmt
    ;

log_stmt
    : LOG LPAREN expr RPAREN SEMICOLON
    ;

action
    : PUXAR_LINHA LPAREN RPAREN SEMICOLON
    | RECOLHER_LINHA LPAREN RPAREN SEMICOLON
    | TROCAR_ISCA LPAREN expr RPAREN SEMICOLON
    | AUMENTAR_PROF LPAREN expr RPAREN SEMICOLON
    | REDUZIR_PROF LPAREN expr RPAREN SEMICOLON
    | DEFINIR_PROF LPAREN expr RPAREN SEMICOLON
    ;

expr
    : or_expr
    ;

or_expr
    : and_expr
    | or_expr OR and_expr
    ;

and_expr
    : not_expr
    | and_expr AND not_expr
    ;

not_expr
    : rel_expr
    | NOT rel_expr
    ;

rel_expr
    : sum_expr
    | sum_expr EQ sum_expr
    | sum_expr NEQ sum_expr
    | sum_expr GT sum_expr
    | sum_expr LT sum_expr
    | sum_expr GE sum_expr
    | sum_expr LE sum_expr
    ;

sum_expr
    : term
    | sum_expr PLUS term
    | sum_expr MINUS term
    ;

term
    : factor
    | term TIMES factor
    | term DIVIDE factor
    ;

factor
    : NUMBER
    | TRUE
    | FALSE
    | SONAR
    | PEIXE_NA_LINHA
    | PROFUNDIDADE
    | IDENT
    | LPAREN expr RPAREN
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main() {
    printf("Iniciando análise sintática...\n");
    yyparse();
    printf("Análise concluída com sucesso!\n");
    return 0;
}
