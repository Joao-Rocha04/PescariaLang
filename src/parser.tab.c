/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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


#line 195 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENT = 3,                      /* IDENT  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_LET = 5,                        /* LET  */
  YYSYMBOL_NUM = 6,                        /* NUM  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_LOG = 11,                       /* LOG  */
  YYSYMBOL_PUXAR_LINHA = 12,               /* PUXAR_LINHA  */
  YYSYMBOL_RECOLHER_LINHA = 13,            /* RECOLHER_LINHA  */
  YYSYMBOL_TROCAR_ISCA = 14,               /* TROCAR_ISCA  */
  YYSYMBOL_AUMENTAR_PROF = 15,             /* AUMENTAR_PROF  */
  YYSYMBOL_REDUZIR_PROF = 16,              /* REDUZIR_PROF  */
  YYSYMBOL_DEFINIR_PROF = 17,              /* DEFINIR_PROF  */
  YYSYMBOL_SONAR = 18,                     /* SONAR  */
  YYSYMBOL_PEIXE_NA_LINHA = 19,            /* PEIXE_NA_LINHA  */
  YYSYMBOL_PROFUNDIDADE = 20,              /* PROFUNDIDADE  */
  YYSYMBOL_TRUE = 21,                      /* TRUE  */
  YYSYMBOL_FALSE = 22,                     /* FALSE  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_GE = 25,                        /* GE  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GT = 27,                        /* GT  */
  YYSYMBOL_LT = 28,                        /* LT  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_ASSIGN = 32,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 33,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 34,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 35,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 36,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 37,                    /* RBRACE  */
  YYSYMBOL_PLUS = 38,                      /* PLUS  */
  YYSYMBOL_MINUS = 39,                     /* MINUS  */
  YYSYMBOL_TIMES = 40,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 41,                    /* DIVIDE  */
  YYSYMBOL_COLON = 42,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_decl = 45,                      /* decl  */
  YYSYMBOL_type = 46,                      /* type  */
  YYSYMBOL_opt_assign = 47,                /* opt_assign  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_assign = 49,                    /* assign  */
  YYSYMBOL_if_stmt = 50,                   /* if_stmt  */
  YYSYMBOL_if_start = 51,                  /* if_start  */
  YYSYMBOL_if_after_cond = 52,             /* if_after_cond  */
  YYSYMBOL_if_end_no_else = 53,            /* if_end_no_else  */
  YYSYMBOL_if_else_part = 54,              /* if_else_part  */
  YYSYMBOL_if_end_with_else = 55,          /* if_end_with_else  */
  YYSYMBOL_while_stmt = 56,                /* while_stmt  */
  YYSYMBOL_while_start = 57,               /* while_start  */
  YYSYMBOL_while_after_cond = 58,          /* while_after_cond  */
  YYSYMBOL_while_end = 59,                 /* while_end  */
  YYSYMBOL_block = 60,                     /* block  */
  YYSYMBOL_stmt_list = 61,                 /* stmt_list  */
  YYSYMBOL_log_stmt = 62,                  /* log_stmt  */
  YYSYMBOL_action = 63,                    /* action  */
  YYSYMBOL_expr = 64,                      /* expr  */
  YYSYMBOL_or_expr = 65,                   /* or_expr  */
  YYSYMBOL_and_expr = 66,                  /* and_expr  */
  YYSYMBOL_not_expr = 67,                  /* not_expr  */
  YYSYMBOL_rel_expr = 68,                  /* rel_expr  */
  YYSYMBOL_sum_expr = 69,                  /* sum_expr  */
  YYSYMBOL_term = 70,                      /* term  */
  YYSYMBOL_factor = 71                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   151,   151,   152,   153,   159,   167,   168,   177,   178,
     192,   193,   194,   195,   196,   197,   203,   219,   221,   227,
     237,   249,   263,   281,   293,   298,   314,   326,   342,   346,
     347,   353,   362,   366,   370,   374,   378,   382,   391,   395,
     396,   401,   402,   407,   408,   413,   414,   416,   418,   420,
     422,   424,   429,   430,   432,   437,   438,   440,   445,   449,
     453,   457,   461,   465,   469,   478
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENT", "NUMBER",
  "LET", "NUM", "BOOL", "IF", "ELSE", "WHILE", "LOG", "PUXAR_LINHA",
  "RECOLHER_LINHA", "TROCAR_ISCA", "AUMENTAR_PROF", "REDUZIR_PROF",
  "DEFINIR_PROF", "SONAR", "PEIXE_NA_LINHA", "PROFUNDIDADE", "TRUE",
  "FALSE", "EQ", "NEQ", "GE", "LE", "GT", "LT", "AND", "OR", "NOT",
  "ASSIGN", "SEMICOLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "COLON", "$accept", "program", "decl",
  "type", "opt_assign", "stmt", "assign", "if_stmt", "if_start",
  "if_after_cond", "if_end_no_else", "if_else_part", "if_end_with_else",
  "while_stmt", "while_start", "while_after_cond", "while_end", "block",
  "stmt_list", "log_stmt", "action", "expr", "or_expr", "and_expr",
  "not_expr", "rel_expr", "sum_expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -112,    37,  -112,   -30,     7,  -112,  -112,   -10,     4,    10,
      12,    23,    24,    25,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,    57,    -1,    28,    29,    57,    32,    33,    57,
      57,    57,    57,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
      62,    57,    31,    39,    42,  -112,  -112,    74,   -33,  -112,
      27,    57,    57,    38,    52,    53,    54,    55,    58,    59,
    -112,    60,  -112,    57,    57,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,  -112,  -112,    40,    68,    69,
      72,  -112,  -112,    73,    75,    76,    77,  -112,    42,  -112,
      -3,    -3,    -3,    -3,    -3,    -3,   -33,   -33,  -112,  -112,
      57,    78,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,    51,    51,  -112,    83,  -112,     6,  -112,  -112,  -112,
    -112,  -112,    51,  -112,  -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,    19,    25,     0,     0,     0,
       0,     0,     0,     0,    15,     3,     4,    10,    12,    13,
      14,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,    58,    61,    62,    63,    59,    60,
       0,     0,     0,    38,    39,    41,    43,    45,    52,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     7,     8,     0,     0,
       0,    32,    33,     0,     0,     0,     0,    65,    40,    42,
      46,    47,    50,    51,    48,    49,    53,    54,    56,    57,
       0,     0,    20,    26,    31,    34,    35,    36,    37,     9,
       5,     0,     0,    29,    21,    27,     0,    22,    17,    24,
      28,    30,     0,    23,    18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -112,  -112,  -112,  -112,  -112,    -9,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -111,  -112,  -112,
    -112,   -26,  -112,    56,    50,    80,   -38,   -59,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    15,    77,   101,    16,    17,    18,    24,   111,
     118,   122,   124,    19,    25,   112,   119,   114,   116,    20,
      21,    42,    43,    44,    45,    46,    47,    48,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      53,   115,    22,    56,    57,    58,    59,    73,    74,     3,
      23,   123,    96,    97,     5,    61,     6,     7,     8,     9,
      10,    11,    12,    13,    26,    78,    79,    90,    91,    92,
      93,    94,    95,    75,    76,    71,    72,     2,    27,    14,
       3,    50,     4,   120,    28,     5,    29,     6,     7,     8,
       9,    10,    11,    12,    13,    98,    99,    30,    31,    32,
      33,    34,    51,    52,    62,    33,    34,    54,    55,    63,
      14,    64,   100,    80,   109,    35,    36,    37,    38,    39,
      35,    36,    37,    38,    39,    81,    82,   113,    40,    83,
      84,    41,   117,    85,    86,    87,    41,    65,    66,    67,
      68,    69,    70,   102,   103,   104,   105,   121,   106,   107,
     108,   110,    71,    72,    89,     0,     0,     0,     0,    88,
      60
};

static const yytype_int8 yycheck[] =
{
      26,   112,    32,    29,    30,    31,    32,    40,    41,     3,
       3,   122,    71,    72,     8,    41,    10,    11,    12,    13,
      14,    15,    16,    17,    34,    51,    52,    65,    66,    67,
      68,    69,    70,     6,     7,    38,    39,     0,    34,    33,
       3,    42,     5,    37,    34,     8,    34,    10,    11,    12,
      13,    14,    15,    16,    17,    73,    74,    34,    34,    34,
       3,     4,    34,    34,    33,     3,     4,    35,    35,    30,
      33,    29,    32,    35,   100,    18,    19,    20,    21,    22,
      18,    19,    20,    21,    22,    33,    33,    36,    31,    35,
      35,    34,     9,    35,    35,    35,    34,    23,    24,    25,
      26,    27,    28,    35,    35,    33,    33,   116,    33,    33,
      33,    33,    38,    39,    64,    -1,    -1,    -1,    -1,    63,
      40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    44,     0,     3,     5,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    33,    45,    48,    49,    50,    56,
      62,    63,    32,     3,    51,    57,    34,    34,    34,    34,
      34,    34,    34,     3,     4,    18,    19,    20,    21,    22,
      31,    34,    64,    65,    66,    67,    68,    69,    70,    71,
      42,    34,    34,    64,    35,    35,    64,    64,    64,    64,
      68,    64,    33,    30,    29,    23,    24,    25,    26,    27,
      28,    38,    39,    40,    41,     6,     7,    46,    64,    64,
      35,    33,    33,    35,    35,    35,    35,    35,    66,    67,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      32,    47,    35,    35,    33,    33,    33,    33,    33,    64,
      33,    52,    58,    36,    60,    60,    61,     9,    53,    59,
      37,    48,    54,    60,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    44,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    49,    50,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      61,    62,    63,    63,    63,    63,    63,    63,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    69,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     6,     1,     1,     0,     2,
       1,     1,     1,     1,     1,     1,     4,     8,    11,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     3,     0,
       2,     5,     4,     4,     5,     5,     5,     5,     1,     1,
       3,     1,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* decl: LET IDENT COLON type opt_assign SEMICOLON  */
#line 160 "parser.y"
      {
        /* Se não inicializou em opt_assign, só garante a declaração */
        declare_symbol((yyvsp[-4].sval));
      }
#line 1338 "parser.tab.c"
    break;

  case 9: /* opt_assign: ASSIGN expr  */
#line 179 "parser.y"
      {
        /* A variável é o IDENT antes do COLON,
           mas para simplificar, vamos assumir que
           'decl' já chamou declare_symbol e aqui
           só fazemos nada. Se quiser suportar inicialização,
           precisaria capturar o nome do IDENT via ação intermediária. */
        /* opcional: emitir STORE para última variável declarada se você guardar o índice */
      }
#line 1351 "parser.tab.c"
    break;

  case 16: /* assign: IDENT ASSIGN expr SEMICOLON  */
#line 204 "parser.y"
      {
        int idx = lookup_symbol((yyvsp[-3].sval));
        if (idx < 0) {
            fprintf(stderr, "Variável não declarada: %s\n", (yyvsp[-3].sval));
            exit(1);
        }
        /* expr deixou o valor no topo da pilha */
        emit("STORE %d", idx);
      }
#line 1365 "parser.tab.c"
    break;

  case 19: /* if_start: %empty  */
#line 227 "parser.y"
      {
        int l_else = new_label_id();
        int l_end  = new_label_id();
        push_if(l_else, l_end);
      }
#line 1375 "parser.tab.c"
    break;

  case 20: /* if_after_cond: %empty  */
#line 237 "parser.y"
      {
        int l_else, l_end;
        char buf[32];
        peek_if(&l_else, &l_end);
        label_name(buf, l_else);
        emit("JUMP_IF_FALSE %s", buf);
      }
#line 1387 "parser.tab.c"
    break;

  case 21: /* if_end_no_else: %empty  */
#line 249 "parser.y"
      {
        int l_else, l_end;
        char buf_else[32], buf_end[32];
        pop_if(&l_else, &l_end);
        label_name(buf_else, l_else);
        label_name(buf_end, l_end);
        emit("%s:", buf_else);  /* bloco else vazio */
        emit("%s:", buf_end);   /* fim do if */
      }
#line 1401 "parser.tab.c"
    break;

  case 22: /* if_else_part: %empty  */
#line 263 "parser.y"
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
#line 1419 "parser.tab.c"
    break;

  case 23: /* if_end_with_else: %empty  */
#line 281 "parser.y"
      {
        int l_else, l_end;
        char buf_end[32];
        pop_if(&l_else, &l_end);
        label_name(buf_end, l_end);
        emit("%s:", buf_end);
      }
#line 1431 "parser.tab.c"
    break;

  case 25: /* while_start: %empty  */
#line 298 "parser.y"
      {
        int l_start = new_label_id();
        int l_end   = new_label_id();

        push_loop(l_start, l_end);

        char buf_start[32];
        label_name(buf_start, l_start);
        /* label do início do loop */
        emit("%s:", buf_start);
      }
#line 1447 "parser.tab.c"
    break;

  case 26: /* while_after_cond: %empty  */
#line 314 "parser.y"
      {
        int l_start, l_end;
        char buf_end[32];
        peek_loop(&l_start, &l_end);
        label_name(buf_end, l_end);
        emit("JUMP_IF_FALSE %s", buf_end);
      }
#line 1459 "parser.tab.c"
    break;

  case 27: /* while_end: %empty  */
#line 326 "parser.y"
      {
        int l_start, l_end;
        char buf_start[32], buf_end[32];

        pop_loop(&l_start, &l_end);
        label_name(buf_start, l_start);
        label_name(buf_end,   l_end);

        emit("JUMP %s", buf_start);
        emit("%s:", buf_end);
      }
#line 1475 "parser.tab.c"
    break;

  case 31: /* log_stmt: LOG LPAREN expr RPAREN SEMICOLON  */
#line 354 "parser.y"
      {
        emit("LOG");
      }
#line 1483 "parser.tab.c"
    break;

  case 32: /* action: PUXAR_LINHA LPAREN RPAREN SEMICOLON  */
#line 363 "parser.y"
      {
        emit("ACTION PUXAR_LINHA");
      }
#line 1491 "parser.tab.c"
    break;

  case 33: /* action: RECOLHER_LINHA LPAREN RPAREN SEMICOLON  */
#line 367 "parser.y"
      {
        emit("ACTION RECOLHER_LINHA");
      }
#line 1499 "parser.tab.c"
    break;

  case 34: /* action: TROCAR_ISCA LPAREN expr RPAREN SEMICOLON  */
#line 371 "parser.y"
      {
        emit("ACTION TROCAR_ISCA");
      }
#line 1507 "parser.tab.c"
    break;

  case 35: /* action: AUMENTAR_PROF LPAREN expr RPAREN SEMICOLON  */
#line 375 "parser.y"
      {
        emit("ACTION AUMENTAR_PROF");
      }
#line 1515 "parser.tab.c"
    break;

  case 36: /* action: REDUZIR_PROF LPAREN expr RPAREN SEMICOLON  */
#line 379 "parser.y"
      {
        emit("ACTION REDUZIR_PROF");
      }
#line 1523 "parser.tab.c"
    break;

  case 37: /* action: DEFINIR_PROF LPAREN expr RPAREN SEMICOLON  */
#line 383 "parser.y"
      {
        emit("ACTION SET_PROF");
      }
#line 1531 "parser.tab.c"
    break;

  case 40: /* or_expr: or_expr OR and_expr  */
#line 397 "parser.y"
      { emit("OR"); }
#line 1537 "parser.tab.c"
    break;

  case 42: /* and_expr: and_expr AND not_expr  */
#line 403 "parser.y"
      { emit("AND"); }
#line 1543 "parser.tab.c"
    break;

  case 44: /* not_expr: NOT rel_expr  */
#line 409 "parser.y"
      { emit("NOT"); }
#line 1549 "parser.tab.c"
    break;

  case 46: /* rel_expr: sum_expr EQ sum_expr  */
#line 415 "parser.y"
      { emit("CMP_EQ"); }
#line 1555 "parser.tab.c"
    break;

  case 47: /* rel_expr: sum_expr NEQ sum_expr  */
#line 417 "parser.y"
      { emit("CMP_NE"); }
#line 1561 "parser.tab.c"
    break;

  case 48: /* rel_expr: sum_expr GT sum_expr  */
#line 419 "parser.y"
      { emit("CMP_GT"); }
#line 1567 "parser.tab.c"
    break;

  case 49: /* rel_expr: sum_expr LT sum_expr  */
#line 421 "parser.y"
      { emit("CMP_LT"); }
#line 1573 "parser.tab.c"
    break;

  case 50: /* rel_expr: sum_expr GE sum_expr  */
#line 423 "parser.y"
      { emit("CMP_GE"); }
#line 1579 "parser.tab.c"
    break;

  case 51: /* rel_expr: sum_expr LE sum_expr  */
#line 425 "parser.y"
      { emit("CMP_LE"); }
#line 1585 "parser.tab.c"
    break;

  case 53: /* sum_expr: sum_expr PLUS term  */
#line 431 "parser.y"
      { emit("ADD"); }
#line 1591 "parser.tab.c"
    break;

  case 54: /* sum_expr: sum_expr MINUS term  */
#line 433 "parser.y"
      { emit("SUB"); }
#line 1597 "parser.tab.c"
    break;

  case 56: /* term: term TIMES factor  */
#line 439 "parser.y"
      { emit("MUL"); }
#line 1603 "parser.tab.c"
    break;

  case 57: /* term: term DIVIDE factor  */
#line 441 "parser.y"
      { emit("DIV"); }
#line 1609 "parser.tab.c"
    break;

  case 58: /* factor: NUMBER  */
#line 446 "parser.y"
      {
        emit("PUSH %d", (yyvsp[0].ival));
      }
#line 1617 "parser.tab.c"
    break;

  case 59: /* factor: TRUE  */
#line 450 "parser.y"
      {
        emit("PUSH 1");
      }
#line 1625 "parser.tab.c"
    break;

  case 60: /* factor: FALSE  */
#line 454 "parser.y"
      {
        emit("PUSH 0");
      }
#line 1633 "parser.tab.c"
    break;

  case 61: /* factor: SONAR  */
#line 458 "parser.y"
      {
        emit("READ_SENSOR SONAR");
      }
#line 1641 "parser.tab.c"
    break;

  case 62: /* factor: PEIXE_NA_LINHA  */
#line 462 "parser.y"
      {
        emit("READ_SENSOR PEIXE");
      }
#line 1649 "parser.tab.c"
    break;

  case 63: /* factor: PROFUNDIDADE  */
#line 466 "parser.y"
      {
        emit("READ_SENSOR PROF");
      }
#line 1657 "parser.tab.c"
    break;

  case 64: /* factor: IDENT  */
#line 470 "parser.y"
      {
        int idx = lookup_symbol((yyvsp[0].sval));
        if (idx < 0) {
            fprintf(stderr, "Variável não declarada: %s\n", (yyvsp[0].sval));
            exit(1);
        }
        emit("LOAD %d", idx);
      }
#line 1670 "parser.tab.c"
    break;

  case 65: /* factor: LPAREN expr RPAREN  */
#line 479 "parser.y"
      { /* nada: expr já emitiu código */ }
#line 1676 "parser.tab.c"
    break;


#line 1680 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 482 "parser.y"


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
