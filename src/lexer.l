%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT}|_)*

%%

"let"               return LET;
"num"               return NUM;
"bool"              return BOOL;

"if"                return IF;
"else"              return ELSE;
"while"             return WHILE;
"log"               return LOG;

"puxar_linha"           return PUXAR_LINHA;
"recolher_linha"        return RECOLHER_LINHA;
"trocar_isca"           return TROCAR_ISCA;
"aumentar_profundidade" return AUMENTAR_PROF;
"reduzir_profundidade"  return REDUZIR_PROF;
"definir_profundidade"  return DEFINIR_PROF;

"sonar"             return SONAR;
"peixe_na_linha"    return PEIXE_NA_LINHA;
"profundidade"      return PROFUNDIDADE;

"true"              return TRUE;
"false"             return FALSE;

"=="                return EQ;
"!="                return NEQ;
">="                return GE;
"<="                return LE;
">"                 return GT;
"<"                 return LT;

"&&"                return AND;
"||"                return OR;
"!"                 return NOT;

"="                 return ASSIGN;
";"                 return SEMICOLON;
"("                 return LPAREN;
")"                 return RPAREN;
"{"                 return LBRACE;
"}"                 return RBRACE;
"+"                 return PLUS;
"-"                 return MINUS;
"*"                 return TIMES;
"/"                 return DIVIDE;
":"                 return COLON;

{ID}                { yylval.sval = strdup(yytext); return IDENT; }
{DIGIT}+            { yylval.ival = atoi(yytext); return NUMBER; }

[ \t\r\n]+          ; // ignora espaços
"//".*              ; // ignora comentários de linha
"/*"([^*]|\*+[^*/])*\*+"/"   ; // ignora comentários de bloco

.                   { printf("Caractere inesperado: %s\n", yytext); }

%%

int yywrap(void) { return 1; }
