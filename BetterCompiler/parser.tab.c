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
#include "AST.h"
#include "symbolTable.h"
//#include "semantic.h"
#include "TAC.h"
#include "optimizer.h"
//#include "codeGenerator.h"

#define TABLE_SIZE 100

extern int lines;
extern int chars;

extern int yylex(); // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin; // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern char *yytext;  // The text from the lexer file
extern TAC* tacHead;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

ASTNode* root = NULL;
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

// Declare global print booleans
int printSymbolDebug = 0;
int printParserDebug = 0;


#line 107 "parser.tab.c"

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
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_BOOL = 6,                       /* BOOL  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_TRUE = 8,                       /* TRUE  */
  YYSYMBOL_FALSE = 9,                      /* FALSE  */
  YYSYMBOL_PRINT = 10,                     /* PRINT  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_ELSE_IF = 13,                   /* ELSE_IF  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_SEMICOLON = 16,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_LPAREN = 18,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 19,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 22,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 23,                  /* RBRACKET  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 25,                      /* PLUS  */
  YYSYMBOL_MINUS = 26,                     /* MINUS  */
  YYSYMBOL_MULT = 27,                      /* MULT  */
  YYSYMBOL_DIV = 28,                       /* DIV  */
  YYSYMBOL_GREATER_THAN = 29,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN = 30,                 /* LESS_THAN  */
  YYSYMBOL_EQUAL_TO = 31,                  /* EQUAL_TO  */
  YYSYMBOL_GREATER_THAN_EQUAL_TO = 32,     /* GREATER_THAN_EQUAL_TO  */
  YYSYMBOL_LESS_THAN_EQUAL_TO = 33,        /* LESS_THAN_EQUAL_TO  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_NUMBER = 36,                    /* NUMBER  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_Program = 38,                   /* Program  */
  YYSYMBOL_StmtList = 39,                  /* StmtList  */
  YYSYMBOL_Stmt = 40,                      /* Stmt  */
  YYSYMBOL_IfBlock = 41,                   /* IfBlock  */
  YYSYMBOL_IfStmt = 42,                    /* IfStmt  */
  YYSYMBOL_ElseIfStmt = 43,                /* ElseIfStmt  */
  YYSYMBOL_ElseStmt = 44,                  /* ElseStmt  */
  YYSYMBOL_Condition = 45,                 /* Condition  */
  YYSYMBOL_SIGN = 46,                      /* SIGN  */
  YYSYMBOL_FunctionDeclaration = 47,       /* FunctionDeclaration  */
  YYSYMBOL_FunctionCall = 48,              /* FunctionCall  */
  YYSYMBOL_ParamList = 49,                 /* ParamList  */
  YYSYMBOL_ParamTail = 50,                 /* ParamTail  */
  YYSYMBOL_Param = 51,                     /* Param  */
  YYSYMBOL_ArgList = 52,                   /* ArgList  */
  YYSYMBOL_ArgTail = 53,                   /* ArgTail  */
  YYSYMBOL_Block = 54,                     /* Block  */
  YYSYMBOL_BlockStmtList = 55,             /* BlockStmtList  */
  YYSYMBOL_BlockStmt = 56,                 /* BlockStmt  */
  YYSYMBOL_ReturnStmt = 57,                /* ReturnStmt  */
  YYSYMBOL_Declaration = 58,               /* Declaration  */
  YYSYMBOL_DeclarationAssignment = 59,     /* DeclarationAssignment  */
  YYSYMBOL_Type = 60,                      /* Type  */
  YYSYMBOL_Assignment = 61,                /* Assignment  */
  YYSYMBOL_Print = 62,                     /* Print  */
  YYSYMBOL_Expr = 63,                      /* Expr  */
  YYSYMBOL_Term = 64,                      /* Term  */
  YYSYMBOL_Factor = 65                     /* Factor  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    64,    64,    67,    68,    71,    72,    73,    74,    75,
      76,    77,    80,    83,    86,    87,    90,    91,    94,    97,
      98,    99,   100,   101,   104,   107,   110,   111,   114,   115,
     118,   119,   122,   123,   126,   127,   130,   131,   134,   135,
     138,   139,   140,   141,   142,   143,   146,   149,   150,   153,
     156,   157,   158,   159,   162,   163,   164,   165,   168,   171,
     172,   173,   176,   177,   178,   181,   182,   183,   184
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT", "FLOAT",
  "BOOL", "VOID", "TRUE", "FALSE", "PRINT", "IF", "ELSE", "ELSE_IF",
  "WHILE", "RETURN", "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "ASSIGN", "PLUS", "MINUS", "MULT",
  "DIV", "GREATER_THAN", "LESS_THAN", "EQUAL_TO", "GREATER_THAN_EQUAL_TO",
  "LESS_THAN_EQUAL_TO", "AND", "OR", "NUMBER", "$accept", "Program",
  "StmtList", "Stmt", "IfBlock", "IfStmt", "ElseIfStmt", "ElseStmt",
  "Condition", "SIGN", "FunctionDeclaration", "FunctionCall", "ParamList",
  "ParamTail", "Param", "ArgList", "ArgTail", "Block", "BlockStmtList",
  "BlockStmt", "ReturnStmt", "Declaration", "DeclarationAssignment",
  "Type", "Assignment", "Print", "Expr", "Term", "Factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      65,    74,   -81,   -81,   -81,   -81,    11,    76,    47,   -81,
      65,   -81,    82,   -81,   -81,   -81,   -81,    57,   -81,   -81,
       3,     3,     4,     3,     3,   -81,   -81,    79,    87,    66,
      78,     3,   -81,    89,   -81,    36,   -14,   -81,    84,    -2,
     -81,    -7,    29,    93,    48,     3,    81,   -81,   -81,    99,
       3,     3,     3,    38,   100,     3,     3,     3,     3,     3,
      95,   -81,   104,   101,   -81,   -81,   -81,   -81,   -81,     3,
     103,    65,   105,   -81,   106,   122,    88,    -1,    92,   -81,
     -81,   -81,   -14,   -14,   -81,   -81,     4,   -81,    65,    33,
     107,   -81,   -81,   108,   111,    65,   -81,   -81,   125,   -81,
     -81,   110,    99,   109,   116,   -81,   -81,   -81,    12,   112,
      65,   -81,     3,   -81,   -81,    67,    65,   -81,   113,   -81,
     -81,   -81,   114,    18,   117,   -81,    82,   -81,   -81,   -81
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    50,    51,    52,    53,     0,     0,     0,     2,
       3,    11,    14,    10,     9,     5,     6,     0,     7,     8,
      32,     0,     0,     0,     0,     1,     4,     0,    16,     0,
      66,     0,    68,     0,    33,    34,    61,    64,     0,    66,
      55,     0,     0,     0,     0,     0,     0,    12,    47,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,     0,     0,    19,    20,    21,    22,    23,     0,
       0,    38,     0,    27,    28,     0,     0,     0,     0,    65,
      25,    35,    59,    60,    62,    63,     0,    58,    38,    18,
       0,    45,    44,     0,    37,    38,    40,    41,     0,    42,
      43,     0,     0,    30,     0,    49,    67,    57,     0,     0,
      38,    17,     0,    36,    39,     0,    38,    29,     0,    48,
      56,    13,     0,     0,     0,    31,    14,    46,    24,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   124,   -81,    17,   -81,    13,   -81,    96,   -81,
     -81,     1,   -81,    40,   -81,   -81,    85,   -80,    49,   -81,
     -81,    35,    41,     0,    42,    46,   -19,     9,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    91,    12,    28,    47,    43,    69,
      13,    92,    72,    73,    74,    33,    34,    93,    94,    95,
     113,    96,    97,    98,    99,   100,    35,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      17,    14,    38,    41,    42,    44,    30,    39,   109,    61,
      17,    14,    53,    58,    59,   105,    20,    11,    56,    57,
      52,    31,    31,    40,    56,    57,    44,    11,   120,    23,
     122,    76,    77,    78,   127,    15,   124,    56,    57,    32,
      32,    16,    18,    56,    57,    15,    19,    25,    62,    75,
      89,    16,    18,    55,    56,    57,    19,    79,    56,    57,
      29,    56,    57,    56,    57,    82,    83,   108,     1,     2,
       3,     4,     5,    56,    57,     6,     7,    64,    65,    66,
      67,    68,    48,    48,    49,    84,    85,   107,    50,    50,
      51,    51,    20,   123,    24,    27,    21,    45,    22,    46,
      52,    71,    75,     2,     3,     4,     5,    60,    54,    56,
      57,   104,    63,    56,    57,   106,    80,    56,    57,    86,
      87,    88,    90,   102,   101,   103,   112,   110,   115,   111,
     116,   118,   119,   121,    26,   126,   125,     0,   128,   129,
      81,    70,   117,     0,   114
};

static const yytype_int8 yycheck[] =
{
       0,     0,    21,    22,    23,    24,     3,     3,    88,    16,
      10,    10,    31,    27,    28,    16,    18,     0,    25,    26,
      22,    18,    18,    22,    25,    26,    45,    10,    16,    18,
     110,    50,    51,    52,    16,     0,   116,    25,    26,    36,
      36,     0,     0,    25,    26,    10,     0,     0,    19,    49,
      69,    10,    10,    17,    25,    26,    10,    19,    25,    26,
       3,    25,    26,    25,    26,    56,    57,    86,     3,     4,
       5,     6,     7,    25,    26,    10,    11,    29,    30,    31,
      32,    33,    16,    16,    18,    58,    59,    86,    22,    22,
      24,    24,    18,   112,    18,    13,    22,    18,    24,    12,
      22,    20,   102,     4,     5,     6,     7,    23,    19,    25,
      26,    23,    19,    25,    26,    23,    16,    25,    26,    24,
      16,    20,    19,    17,    19,     3,    15,    20,     3,    21,
      20,    22,    16,    21,    10,    21,    23,    -1,    21,   126,
      55,    45,   102,    -1,    95
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    10,    11,    38,    39,
      40,    41,    42,    47,    48,    58,    59,    60,    61,    62,
      18,    22,    24,    18,    18,     0,    39,    13,    43,     3,
       3,    18,    36,    52,    53,    63,    64,    65,    63,     3,
      48,    63,    63,    45,    63,    18,    12,    44,    16,    18,
      22,    24,    22,    63,    19,    17,    25,    26,    27,    28,
      23,    16,    19,    19,    29,    30,    31,    32,    33,    46,
      45,    20,    49,    50,    51,    60,    63,    63,    63,    19,
      16,    53,    64,    64,    65,    65,    24,    16,    20,    63,
      19,    41,    48,    54,    55,    56,    58,    59,    60,    61,
      62,    19,    17,     3,    23,    16,    23,    48,    63,    54,
      20,    21,    15,    57,    55,     3,    20,    50,    22,    16,
      16,    21,    54,    63,    54,    23,    21,    16,    21,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    40,    40,
      40,    40,    41,    42,    43,    43,    44,    44,    45,    46,
      46,    46,    46,    46,    47,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      56,    56,    56,    56,    56,    56,    57,    58,    58,    59,
      60,    60,    60,    60,    61,    61,    61,    61,    62,    63,
      63,    63,    64,    64,    64,    65,    65,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     7,     0,     8,     0,     4,     3,     1,
       1,     1,     1,     1,     8,     5,     0,     1,     1,     3,
       2,     4,     0,     1,     1,     3,     2,     1,     0,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     6,     5,
       1,     1,     1,     1,     4,     3,     7,     6,     5,     3,
       3,     1,     3,     3,     1,     3,     1,     4,     1
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
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 55 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 864 "parser.tab.c"
        break;

      default:
        break;
    }
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
  case 2: /* Program: StmtList  */
#line 64 "parser.y"
                  { (yyval.node) = createProgramNode((yyvsp[0].node)); root = (yyval.node); }
#line 1254 "parser.tab.c"
    break;

  case 3: /* StmtList: %empty  */
#line 67 "parser.y"
           { (yyval.node) = NULL; }
#line 1260 "parser.tab.c"
    break;

  case 4: /* StmtList: Stmt StmtList  */
#line 68 "parser.y"
                        { (yyval.node) = createStmtListNode((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1266 "parser.tab.c"
    break;

  case 5: /* Stmt: Declaration  */
#line 71 "parser.y"
                  { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1272 "parser.tab.c"
    break;

  case 6: /* Stmt: DeclarationAssignment  */
#line 72 "parser.y"
                                { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1278 "parser.tab.c"
    break;

  case 7: /* Stmt: Assignment  */
#line 73 "parser.y"
                     { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1284 "parser.tab.c"
    break;

  case 8: /* Stmt: Print  */
#line 74 "parser.y"
                { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1290 "parser.tab.c"
    break;

  case 9: /* Stmt: FunctionCall  */
#line 75 "parser.y"
                       { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1296 "parser.tab.c"
    break;

  case 10: /* Stmt: FunctionDeclaration  */
#line 76 "parser.y"
                              { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1302 "parser.tab.c"
    break;

  case 11: /* Stmt: IfBlock  */
#line 77 "parser.y"
                  { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1308 "parser.tab.c"
    break;

  case 12: /* IfBlock: IfStmt ElseIfStmt ElseStmt  */
#line 80 "parser.y"
                                    { (yyval.node) = createIfBlockNode((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1314 "parser.tab.c"
    break;

  case 13: /* IfStmt: IF LPAREN Condition RPAREN LBRACE Block RBRACE  */
#line 83 "parser.y"
                                                       { (yyval.node) = createIfStmtNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1320 "parser.tab.c"
    break;

  case 14: /* ElseIfStmt: %empty  */
#line 86 "parser.y"
            { (yyval.node) = NULL; }
#line 1326 "parser.tab.c"
    break;

  case 15: /* ElseIfStmt: ELSE_IF LPAREN Condition RPAREN LBRACE Block RBRACE ElseIfStmt  */
#line 87 "parser.y"
                                                                         { (yyval.node) = createElseIfStmtNode((yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1332 "parser.tab.c"
    break;

  case 16: /* ElseStmt: %empty  */
#line 90 "parser.y"
          { (yyval.node) = NULL; }
#line 1338 "parser.tab.c"
    break;

  case 17: /* ElseStmt: ELSE LBRACE Block RBRACE  */
#line 91 "parser.y"
                                   { (yyval.node) = createElseStmtNode((yyvsp[-1].node)); }
#line 1344 "parser.tab.c"
    break;

  case 18: /* Condition: Expr SIGN Expr  */
#line 94 "parser.y"
                          { (yyval.node) = createConditionNode((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1350 "parser.tab.c"
    break;

  case 19: /* SIGN: GREATER_THAN  */
#line 97 "parser.y"
                   { (yyval.node) = createSignNode((yyvsp[0].stringOp)); }
#line 1356 "parser.tab.c"
    break;

  case 20: /* SIGN: LESS_THAN  */
#line 98 "parser.y"
                    { (yyval.node) = createSignNode((yyvsp[0].stringOp)); }
#line 1362 "parser.tab.c"
    break;

  case 21: /* SIGN: EQUAL_TO  */
#line 99 "parser.y"
                   { (yyval.node) = createSignNode((yyvsp[0].stringOp)); }
#line 1368 "parser.tab.c"
    break;

  case 22: /* SIGN: GREATER_THAN_EQUAL_TO  */
#line 100 "parser.y"
                                { (yyval.node) = createSignNode((yyvsp[0].stringOp)); }
#line 1374 "parser.tab.c"
    break;

  case 23: /* SIGN: LESS_THAN_EQUAL_TO  */
#line 101 "parser.y"
                             { (yyval.node) = createSignNode((yyvsp[0].stringOp)); }
#line 1380 "parser.tab.c"
    break;

  case 24: /* FunctionDeclaration: Type ID LPAREN ParamList RPAREN LBRACE Block RBRACE  */
#line 104 "parser.y"
                                                                         { (yyval.node) = createFunctionDeclarationNode((yyvsp[-7].node), createIDNode((yyvsp[-6].string)), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1386 "parser.tab.c"
    break;

  case 25: /* FunctionCall: ID LPAREN ArgList RPAREN SEMICOLON  */
#line 107 "parser.y"
                                                { printf("HERE\n"); (yyval.node) = createFunctionCallNode(createIDNode((yyvsp[-4].string)), (yyvsp[-2].node)); }
#line 1392 "parser.tab.c"
    break;

  case 26: /* ParamList: %empty  */
#line 110 "parser.y"
           { (yyval.node) = NULL; }
#line 1398 "parser.tab.c"
    break;

  case 27: /* ParamList: ParamTail  */
#line 111 "parser.y"
                    { (yyval.node) = createParamListNode((yyvsp[0].node)); }
#line 1404 "parser.tab.c"
    break;

  case 28: /* ParamTail: Param  */
#line 114 "parser.y"
                 { (yyval.node) = createParamTailNode((yyvsp[0].node), NULL); }
#line 1410 "parser.tab.c"
    break;

  case 29: /* ParamTail: Param COMMA ParamTail  */
#line 115 "parser.y"
                                { (yyval.node) = createParamTailNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1416 "parser.tab.c"
    break;

  case 30: /* Param: Type ID  */
#line 118 "parser.y"
               { (yyval.node) = createParamNode(createDeclarationNode((yyvsp[-1].node), createIDNode((yyvsp[0].string)))); }
#line 1422 "parser.tab.c"
    break;

  case 31: /* Param: Type ID LBRACKET RBRACKET  */
#line 119 "parser.y"
                                { (yyval.node) = createParamNode(createArrayDeclarationNode((yyvsp[-3].node), createIDNode((yyvsp[-2].string)), NULL)); }
#line 1428 "parser.tab.c"
    break;

  case 32: /* ArgList: %empty  */
#line 122 "parser.y"
         { (yyval.node) = NULL; }
#line 1434 "parser.tab.c"
    break;

  case 33: /* ArgList: ArgTail  */
#line 123 "parser.y"
                 { (yyval.node) = createArgListNode((yyvsp[0].node)); }
#line 1440 "parser.tab.c"
    break;

  case 34: /* ArgTail: Expr  */
#line 126 "parser.y"
              { (yyval.node) = createArgTailNode((yyvsp[0].node), NULL); }
#line 1446 "parser.tab.c"
    break;

  case 35: /* ArgTail: Expr COMMA ArgTail  */
#line 127 "parser.y"
                            { (yyval.node) = createArgTailNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1452 "parser.tab.c"
    break;

  case 36: /* Block: BlockStmtList ReturnStmt  */
#line 130 "parser.y"
                                { (yyval.node) = createBlockNode((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1458 "parser.tab.c"
    break;

  case 37: /* Block: BlockStmtList  */
#line 131 "parser.y"
                     { (yyval.node) = createBlockNode((yyvsp[0].node), NULL); }
#line 1464 "parser.tab.c"
    break;

  case 38: /* BlockStmtList: %empty  */
#line 134 "parser.y"
                { (yyval.node) = NULL; }
#line 1470 "parser.tab.c"
    break;

  case 39: /* BlockStmtList: BlockStmt BlockStmtList  */
#line 135 "parser.y"
                                  { (yyval.node) = createBlockStmtListNode((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1476 "parser.tab.c"
    break;

  case 40: /* BlockStmt: Declaration  */
#line 138 "parser.y"
                       { (yyval.node) = createBlockStmtNode((yyvsp[0].node)); }
#line 1482 "parser.tab.c"
    break;

  case 41: /* BlockStmt: DeclarationAssignment  */
#line 139 "parser.y"
                                { (yyval.node) = createStmtNode((yyvsp[0].node)); }
#line 1488 "parser.tab.c"
    break;

  case 42: /* BlockStmt: Assignment  */
#line 140 "parser.y"
                     { (yyval.node) = createBlockStmtNode((yyvsp[0].node)); }
#line 1494 "parser.tab.c"
    break;

  case 43: /* BlockStmt: Print  */
#line 141 "parser.y"
                { (yyval.node) = createBlockStmtNode((yyvsp[0].node)); }
#line 1500 "parser.tab.c"
    break;

  case 44: /* BlockStmt: FunctionCall  */
#line 142 "parser.y"
                       { (yyval.node) = createBlockStmtNode((yyvsp[0].node)); }
#line 1506 "parser.tab.c"
    break;

  case 45: /* BlockStmt: IfBlock  */
#line 143 "parser.y"
                  { printf("IF Stmt\n"); }
#line 1512 "parser.tab.c"
    break;

  case 46: /* ReturnStmt: RETURN Expr SEMICOLON  */
#line 146 "parser.y"
                                  { (yyval.node) = createReturnNode((yyvsp[-1].node)); }
#line 1518 "parser.tab.c"
    break;

  case 47: /* Declaration: Type ID SEMICOLON  */
#line 149 "parser.y"
                               { (yyval.node) = createDeclarationNode((yyvsp[-2].node), createIDNode((yyvsp[-1].string))); }
#line 1524 "parser.tab.c"
    break;

  case 48: /* Declaration: Type ID LBRACKET Expr RBRACKET SEMICOLON  */
#line 150 "parser.y"
                                                   { (yyval.node) = createArrayDeclarationNode((yyvsp[-5].node), createIDNode((yyvsp[-4].string)), (yyvsp[-2].node)); }
#line 1530 "parser.tab.c"
    break;

  case 49: /* DeclarationAssignment: Type ID ASSIGN Expr SEMICOLON  */
#line 153 "parser.y"
                                                     { (yyval.node) = createDeclarationAssignmentNode((yyvsp[-4].node), createIDNode((yyvsp[-3].string)), (yyvsp[-1].node));}
#line 1536 "parser.tab.c"
    break;

  case 50: /* Type: INT  */
#line 156 "parser.y"
          { printf("HERE\n"); (yyval.node) = createTypeNode((yyvsp[0].string)); }
#line 1542 "parser.tab.c"
    break;

  case 51: /* Type: FLOAT  */
#line 157 "parser.y"
            { (yyval.node) = createTypeNode((yyvsp[0].string)); }
#line 1548 "parser.tab.c"
    break;

  case 52: /* Type: BOOL  */
#line 158 "parser.y"
               { (yyval.node) = createTypeNode((yyvsp[0].string)); }
#line 1554 "parser.tab.c"
    break;

  case 53: /* Type: VOID  */
#line 159 "parser.y"
               { (yyval.node) = createTypeNode((yyvsp[0].string)); }
#line 1560 "parser.tab.c"
    break;

  case 54: /* Assignment: ID ASSIGN Expr SEMICOLON  */
#line 162 "parser.y"
                                     { (yyval.node) = createAssignmentNode(createIDNode((yyvsp[-3].string)), (yyvsp[-1].node)); }
#line 1566 "parser.tab.c"
    break;

  case 55: /* Assignment: ID ASSIGN FunctionCall  */
#line 163 "parser.y"
                                 { (yyval.node) = createAssignmentNode(createIDNode((yyvsp[-2].string)), (yyvsp[0].node)); }
#line 1572 "parser.tab.c"
    break;

  case 56: /* Assignment: ID LBRACKET Expr RBRACKET ASSIGN Expr SEMICOLON  */
#line 164 "parser.y"
                                                          { (yyval.node) = createArrayAssignmentNode(createIDNode((yyvsp[-6].string)), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1578 "parser.tab.c"
    break;

  case 57: /* Assignment: ID LBRACKET Expr RBRACKET ASSIGN FunctionCall  */
#line 165 "parser.y"
                                                        { (yyval.node) = createArrayAssignmentNode(createIDNode((yyvsp[-5].string)), (yyvsp[-3].node), (yyvsp[0].node)); }
#line 1584 "parser.tab.c"
    break;

  case 58: /* Print: PRINT LPAREN Expr RPAREN SEMICOLON  */
#line 168 "parser.y"
                                          { (yyval.node) = createPrintNode((yyvsp[-2].node)); }
#line 1590 "parser.tab.c"
    break;

  case 59: /* Expr: Expr PLUS Term  */
#line 171 "parser.y"
                     { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", (yyvsp[-1].op));(yyval.node) = createExprNode(strdup(opStr), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1596 "parser.tab.c"
    break;

  case 60: /* Expr: Expr MINUS Term  */
#line 172 "parser.y"
                          { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", (yyvsp[-1].op));(yyval.node) = createExprNode(strdup(opStr), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1602 "parser.tab.c"
    break;

  case 61: /* Expr: Term  */
#line 173 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1608 "parser.tab.c"
    break;

  case 62: /* Term: Term MULT Factor  */
#line 176 "parser.y"
                       { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", (yyvsp[-1].op));(yyval.node) = createExprNode(strdup(opStr), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1614 "parser.tab.c"
    break;

  case 63: /* Term: Term DIV Factor  */
#line 177 "parser.y"
                          { char opStr[2]; snprintf(opStr, sizeof(opStr), "%c", (yyvsp[-1].op));(yyval.node) = createExprNode(strdup(opStr), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1620 "parser.tab.c"
    break;

  case 64: /* Term: Factor  */
#line 178 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1626 "parser.tab.c"
    break;

  case 65: /* Factor: LPAREN Expr RPAREN  */
#line 181 "parser.y"
                           { (yyval.node) = createFactorNode((yyvsp[-1].node)); }
#line 1632 "parser.tab.c"
    break;

  case 66: /* Factor: ID  */
#line 182 "parser.y"
             { (yyval.node) = createIDNode((yyvsp[0].string)); }
#line 1638 "parser.tab.c"
    break;

  case 67: /* Factor: ID LBRACKET Expr RBRACKET  */
#line 183 "parser.y"
                                    { (yyval.node) = createArrayAccessNode(createIDNode((yyvsp[-3].string)), (yyvsp[-1].node)); }
#line 1644 "parser.tab.c"
    break;

  case 68: /* Factor: NUMBER  */
#line 184 "parser.y"
                 { (yyval.node) = createNumberNode((yyvsp[0].number)); }
#line 1650 "parser.tab.c"
    break;


#line 1654 "parser.tab.c"

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

#line 187 "parser.y"




int main() {
    yyin = fopen("testProg.cmm", "r");

	yydebug = 0;

	// Initialize symbol table
	symTab = createSymbolTable(TABLE_SIZE);
    if (symTab == NULL) {
        // Handle error
        return EXIT_FAILURE;
    }

	printf("\n=== PARSER ===\n\n");
    int result = yyparse();

    if (result == 0) {

		// Print symbol table for debugging
		if(printSymbolDebug == 1)
		{
			printSymbolTable(symTab);
		}

		printf("\n=== AST ===\n\n");

		printAST(root, 0);
		

		// Semantic analysis
		//printf("\n=== SEMANTIC ANALYSIS ===\n\n");
		//semanticAnalysis(root, symTab, symTab->topLevelStatements);


		// print symbolTable
		printSymbolTable(symTab);

		printf("\n=== THREE ADDRESS CODE ===\n");
		generateTAC(root);
		printTAC(&tacHead);

		printTACToFile("TAC.ir", &tacHead);

		// Code optimization
		printf("\n\n=== CODE OPTIMIZATION ===\n");

		//optimizeTAC(&tacHead);
		printOptimizedTAC("TACOptimized.ir", tacHead);

		printf("\n=== CODE GENERATION ===\n");
		//initCodeGenerator("output.s");
		//generateMIPS(tacHead);
		//finalizeCodeGenerator("output.s");

        //freeAST(root);
		//freeSymbolTable(symTab);

    }

    fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "\nPARSER ERROR:\n%s at line %d, column %d\n", s, lines, chars);
}

