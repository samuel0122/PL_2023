/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 15 "plp5.y"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TablaSimbolos.h"
#include "TablaTipos.h"


using namespace std;

#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;

TablaSimbolos *tsActual = new TablaSimbolos(NULL);
TablaTipos *tt = new TablaTipos();
Simbolo *simbolo;



extern int yylex();
extern char *yytext;
extern FILE *yyin;


int yyerror(char *s);

// const int ENTERO  = 1,
//           REAL    = 2,
//           BOOLEAN = 3,
//           FUNCION = 4;

string operador, operadorTrad, s1, s2;  // string auxiliares
int tipo1, tipo2;
int numentero;

string nextLine {'\n'};

bool esArray(uint tipo) { return tt->tipos[tipo].clase == TablaTipos::ARRAY; }
uint tipoBase(uint tipo)  { return tt->tipos[tipo].tipoBase; }
uint tamanyoTipo(uint tipo)  { return tt->tipos[tipo].tamanyo; }

int   ASCII_C = 'c',
      ASCII_F = 'f';

int tmp, tmpcnv;
int ctemp {INIT_DIR_TEMP};
int nuevaTemp();

int cvar {INIT_DIR_VAR};
int nuevaVar(string nombreVar, int tamVar);

int etiq1, etiq2;
int cetiq {0};
int nuevaEtiqueta();

uint tam, dir, tipo;

#line 133 "plp5.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PLP5_TAB_H_INCLUDED
# define YY_YY_PLP5_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    algoritmo = 258,
    dospto = 259,
    id = 260,
    falgoritmo = 261,
    var = 262,
    fvar = 263,
    pyc = 264,
    coma = 265,
    entero = 266,
    real = 267,
    logico = 268,
    tabla = 269,
    nentero = 270,
    de = 271,
    escribe = 272,
    lee = 273,
    si = 274,
    entonces = 275,
    sino = 276,
    mientras = 277,
    hacer = 278,
    repetir = 279,
    hasta = 280,
    blq = 281,
    fblq = 282,
    opasig = 283,
    obool = 284,
    ybool = 285,
    oprel = 286,
    opas = 287,
    opmd = 288,
    nreal = 289,
    pari = 290,
    pard = 291,
    nobool = 292,
    cierto = 293,
    falso = 294,
    cori = 295,
    cord = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PLP5_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   98

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  96

#define YYUNDEFTOK  2
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    92,    93,    96,    99,   100,   103,   103,
     106,   116,   127,   128,   129,   130,   138,   138,   139,   139,
     142,   160,   182,   182,   194,   194,   205,   213,   245,   245,
     250,   251,   254,   265,   268,   279,   282,   431,   434,   483,
     484,   511,   560,   563,   572,   577,   582,   583,   593,   598,
     605,   617,   617
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "algoritmo", "dospto", "id",
  "falgoritmo", "var", "fvar", "pyc", "coma", "entero", "real", "logico",
  "tabla", "nentero", "de", "escribe", "lee", "si", "entonces", "sino",
  "mientras", "hacer", "repetir", "hasta", "blq", "fblq", "opasig",
  "obool", "ybool", "oprel", "opas", "opmd", "nreal", "pari", "pard",
  "nobool", "cierto", "falso", "cori", "cord", "$accept", "S", "SDec",
  "Dec", "MDVar", "DVar", "@1", "LId", "Tipo", "SInstr", "@2", "@3",
  "Instr", "$@4", "$@5", "$@6", "ColaIf", "Expr", "Econj", "Ecomp",
  "Esimple", "Term", "Factor", "Ref", "$@7", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      25,     2,    30,    38,   -58,    37,    63,    39,   -58,    42,
      45,   -58,   -58,   -58,    32,    41,   -58,    52,   -58,    42,
      50,   -58,    -3,    55,    -3,    -3,    45,   -58,   -58,   -17,
      49,   -58,   -58,   -58,    45,   -58,     3,   -58,    -3,     3,
     -58,   -58,    51,    31,   -58,    -6,    33,   -58,    44,    44,
      51,    51,    53,    37,    -3,   -58,    63,    65,   -58,    33,
      -9,   -58,    -3,    -3,    -3,     3,     3,    59,    58,    -3,
      60,    51,    -3,   -58,   -58,    12,   -58,    31,   -58,    54,
      33,   -58,    45,    45,    51,   -58,   -27,   -58,    77,    64,
     -58,   -58,   -58,    45,   -58,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,    18,     0,     0,    18,     4,
       0,    12,    13,    14,     0,     0,     7,     0,     2,     3,
       0,    50,     0,     0,     0,     0,     0,    28,    19,     0,
       0,     5,     6,     8,     0,    44,     0,    45,     0,     0,
      48,    49,    20,    33,    35,    37,    39,    42,    43,    21,
      22,    24,     0,    18,     0,    51,     0,     0,    17,    40,
       0,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,    15,    11,     0,    46,    32,    34,    36,
      38,    41,     0,     0,    26,    29,     0,     9,     0,    31,
      25,    52,    10,     0,    23,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,    35,   -58,   -58,    74,   -58,   -58,    34,    83,
     -58,   -58,   -25,   -58,   -58,   -58,   -58,   -21,    36,    29,
     -57,   -26,   -20,   -10,   -58
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,     8,    15,    16,    57,    75,    17,     9,
      20,    10,    28,    67,    68,    53,    94,    42,    43,    44,
      45,    46,    47,    48,    72
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      29,    52,    21,    50,    51,    65,     3,    79,    21,    58,
      59,    54,    35,    49,    91,    86,    29,    60,    35,    61,
      62,    87,    88,    55,    29,    64,    65,    76,     1,    36,
       4,    37,    38,    71,    39,    40,    41,    37,    38,    80,
      39,    40,    41,     5,     6,    18,    81,    30,    84,    31,
      21,   -16,    11,    12,    13,    14,    33,    89,    90,    34,
      21,    63,    22,    23,    24,    56,    66,    25,    95,    26,
      74,    27,    29,    29,    11,    12,    13,    14,    69,    82,
      62,    83,    92,    29,    55,    93,    65,    85,    70,    32,
      73,    19,    78,     0,     0,     0,     0,     0,    77
};

static const yytype_int8 yycheck[] =
{
      10,    26,     5,    24,    25,    32,     4,    64,     5,    34,
      36,    28,    15,    23,    41,    72,    26,    38,    15,    39,
      29,     9,    10,    40,    34,    31,    32,    36,     3,    32,
       0,    34,    35,    54,    37,    38,    39,    34,    35,    65,
      37,    38,    39,     5,     7,     6,    66,    15,    69,     8,
       5,     9,    11,    12,    13,    14,     4,    82,    83,     9,
       5,    30,    17,    18,    19,    16,    33,    22,    93,    24,
       5,    26,    82,    83,    11,    12,    13,    14,    25,    20,
      29,    23,     5,    93,    40,    21,    32,    27,    53,    15,
      56,     8,    63,    -1,    -1,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    43,     4,     0,     5,     7,    44,    45,    51,
      53,    11,    12,    13,    14,    46,    47,    50,     6,    51,
      52,     5,    17,    18,    19,    22,    24,    26,    54,    65,
      15,     8,    47,     4,     9,    15,    32,    34,    35,    37,
      38,    39,    59,    60,    61,    62,    63,    64,    65,    65,
      59,    59,    54,    57,    28,    40,    16,    48,    54,    63,
      59,    64,    29,    30,    31,    32,    33,    55,    56,    25,
      44,    59,    66,    50,     5,    49,    36,    60,    61,    62,
      63,    64,    20,    23,    59,    27,    62,     9,    10,    54,
      54,    41,     5,    21,    58,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    46,    46,    48,    47,
      49,    49,    50,    50,    50,    50,    52,    51,    53,    51,
      54,    54,    55,    54,    56,    54,    54,    54,    57,    54,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      62,    63,    63,    64,    64,    64,    64,    64,    64,    64,
      65,    66,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     2,     1,     3,     2,     1,     0,     5,
       3,     1,     1,     1,     1,     4,     0,     4,     0,     2,
       2,     2,     0,     6,     0,     5,     4,     3,     0,     4,
       2,     0,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     3,     1,     1,     1,     1,     3,     2,     1,     1,
       1,     0,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 81 "plp5.y"
                                             { 
                                                /* comprobar que después del programa no hay ningún token más */
                                                int tk = yylex();
                                                if (tk != 0) yyerror("");
                                                std::cout << yyvsp[-1].cod + "halt";
                                                // tt->imprimir();
                                                // tsActual->imprimir();
                                             }
#line 1470 "plp5.tab.c"
    break;

  case 3:
#line 92 "plp5.y"
                     { yyval.cod = yyvsp[0].cod; }
#line 1476 "plp5.tab.c"
    break;

  case 4:
#line 93 "plp5.y"
                     { yyval.cod = yyvsp[0].cod; }
#line 1482 "plp5.tab.c"
    break;

  case 5:
#line 96 "plp5.y"
                        {}
#line 1488 "plp5.tab.c"
    break;

  case 6:
#line 99 "plp5.y"
                     {}
#line 1494 "plp5.tab.c"
    break;

  case 7:
#line 100 "plp5.y"
                     {}
#line 1500 "plp5.tab.c"
    break;

  case 8:
#line 103 "plp5.y"
                     { yyval.tipoH = yyvsp[-1].tipo; yyval.tamH = yyvsp[-1].tam; }
#line 1506 "plp5.tab.c"
    break;

  case 9:
#line 103 "plp5.y"
                                                                        {}
#line 1512 "plp5.tab.c"
    break;

  case 10:
#line 106 "plp5.y"
                        {  
                           tipo = yyvsp[-3].tipoH;        // tipoH
                           tam = yyvsp[-3].tamH;          // tam
                           s1 = string(yyvsp[0].lexema); // id
                           dir = nuevaVar(s1, tam);// dir

                           if(!tsActual->newSymb({s1, tipo, dir, tam}))
                              errorSemantico(ERR_YADECL, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                           
                        }
#line 1527 "plp5.tab.c"
    break;

  case 11:
#line 116 "plp5.y"
                        {
                           tipo = yyvsp[-1].tipoH;        // tipoH
                           tam = yyvsp[-1].tamH;          // tam
                           s1 = string(yyvsp[0].lexema); // id
                           dir = nuevaVar(s1, tam);// dir

                           if(!tsActual->newSymb({s1, tipo, dir, tam}))
                              errorSemantico(ERR_YADECL, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                        }
#line 1541 "plp5.tab.c"
    break;

  case 12:
#line 127 "plp5.y"
                                 { yyval.tipo = ENTERO; yyval.tam = 1; }
#line 1547 "plp5.tab.c"
    break;

  case 13:
#line 128 "plp5.y"
                                 { yyval.tipo = REAL; yyval.tam = 1; }
#line 1553 "plp5.tab.c"
    break;

  case 14:
#line 129 "plp5.y"
                                 { yyval.tipo = LOGICO; yyval.tam = 1; }
#line 1559 "plp5.tab.c"
    break;

  case 15:
#line 130 "plp5.y"
                                 { 
                                    numentero = stoi(yyvsp[-2].lexema); 
                                    if(numentero <= 0) errorSemantico(ERR_DIM, yyvsp[-3].nlin, yyvsp[-3].ncol, yyvsp[-3].lexema);

                                    yyval.tipo = tt->nuevoTipoArray(numentero, yyvsp[0].tipo); 
                                    yyval.tam = yyvsp[0].tam * numentero; }
#line 1570 "plp5.tab.c"
    break;

  case 16:
#line 138 "plp5.y"
                { yyval.nlin = ctemp; }
#line 1576 "plp5.tab.c"
    break;

  case 17:
#line 138 "plp5.y"
                                                { ctemp = yyvsp[-2].nlin; yyval.cod = yyvsp[-3].cod + yyvsp[0].cod;}
#line 1582 "plp5.tab.c"
    break;

  case 18:
#line 139 "plp5.y"
         { yyval.nlin = ctemp; }
#line 1588 "plp5.tab.c"
    break;

  case 19:
#line 139 "plp5.y"
                                                { ctemp = yyvsp[-1].nlin; yyval.cod = yyvsp[0].cod; }
#line 1594 "plp5.tab.c"
    break;

  case 20:
#line 142 "plp5.y"
                                          {  if(yyvsp[0].tipo == LOGICO)
                                             {
                                                tmp = nuevaTemp();
                                                etiq1 = nuevaEtiqueta();
                                                etiq2 = nuevaEtiqueta();
                                                s1 = "mov A " + std::to_string(yyvsp[0].dir) + nextLine +
                                                      "jz L" + std::to_string(etiq1) +  nextLine +     // Si Z (false) salta
                                                      "wrc #" + std::to_string(ASCII_C) + nextLine +   // CASO TRUE
                                                      "jmp L" + std::to_string(etiq2) + nextLine +   // Salta al final
                                                      'L' + std::to_string(etiq1) + "\n" +
                                                      "wrc #" + std::to_string(ASCII_F) + nextLine +   // CASO FALSE
                                                      'L' + std::to_string(etiq2) + "\n";
                                             }
                                             else
                                                s1 = ((yyvsp[0].tipo == ENTERO) ? "wri " : "wrr ") + std::to_string(yyvsp[0].dir) + nextLine;
                                             
                                             yyval.cod = yyvsp[0].cod + s1 + "wrl\n";
                                          }
#line 1617 "plp5.tab.c"
    break;

  case 21:
#line 160 "plp5.y"
                                          {  if(esArray(yyvsp[-1].tipo)) errorSemantico(ERR_FALTAN, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                                             if(yyvsp[0].tipo == LOGICO)
                                             {
                                                tmp = nuevaTemp();
                                                s1 =  "rdc A\n";                                      // Lee ASCII
                                                s1 += "eqli #" + std::to_string(ASCII_C)  + nextLine; // Mira si lo leído es C 
                                                s1 += "mov A " + std::to_string(tmp)      + nextLine; // Guarda en variable temporal
                                                s1 += "mov "   + std::to_string(yyvsp[0].dir)   + " A\n";   // Carga saltos en array de Ref
                                                s1 += "addi #" + std::to_string(yyvsp[0].dbase) + nextLine; // Añade dirección base
                                                s1 += "mov "   + std::to_string(tmp)      + " @A\n";  // Muebe variable temporal a A
                                             }  
                                             else
                                             {
                                                operador = ((yyvsp[0].tipo == ENTERO) ? "rdi " : "rdr ");
                                                s1 =  "mov " + std::to_string(yyvsp[0].dir)     + " A\n";   // Carga saltos en array Ref
                                                s1 += "addi #" + std::to_string(yyvsp[0].dbase) + nextLine; // Añade dirección base
                                                s1 += operador + " @A\n";                             // Lee numero en Ref
                                             }
                                             
                                             yyval.cod = yyvsp[0].cod + s1;
                                             
                                          }
#line 1644 "plp5.tab.c"
    break;

  case 22:
#line 182 "plp5.y"
                 { if(yyvsp[0].tipo != LOGICO) errorSemantico(ERR_EXP_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema); }
#line 1650 "plp5.tab.c"
    break;

  case 23:
#line 183 "plp5.y"
                                          {  etiq1 = nuevaEtiqueta();
                                             etiq2 = nuevaEtiqueta();
                                             yyval.cod =    yyvsp[-4].cod;                                      // Ejecuta Expr
                                             yyval.cod +=   "mov " + std::to_string(yyvsp[-4].dir)  + " A\n";   // Carga Expr
                                             yyval.cod +=   "jz L" + std::to_string(etiq1)   + '\n';     // Salta a caso FALSE
                                             yyval.cod +=   yyvsp[-1].cod;                                      // Caso TRUE
                                             yyval.cod +=   "jmp L" + std::to_string(etiq2)  + '\n';     // Salta al final
                                             yyval.cod +=   'L' + std::to_string(etiq1)      + "\n";     // Etiq FALSE
                                             yyval.cod +=   yyvsp[0].cod;                                      // Caso FALSE (sino)
                                             yyval.cod +=   'L' + std::to_string(etiq2)      + "\n";     // Etiq final
                                          }
#line 1666 "plp5.tab.c"
    break;

  case 24:
#line 194 "plp5.y"
                        { if(yyvsp[0].tipo != LOGICO) errorSemantico(ERR_EXP_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema); }
#line 1672 "plp5.tab.c"
    break;

  case 25:
#line 195 "plp5.y"
                                           { etiq1 = nuevaEtiqueta();
                                             etiq2 = nuevaEtiqueta();
                                             yyval.cod =    'L'   + std::to_string(etiq1)       + "\n";  // Etiq inicio
                                             yyval.cod +=   yyvsp[-3].cod;                                      // Ejecuta Expr
                                             yyval.cod +=   "mov "  + std::to_string(yyvsp[-3].dir)   + " A\n"; // Carga resultado de Expr
                                             yyval.cod +=   "jz L"  + std::to_string(etiq2)    + '\n';   // Si Expr FALSE, salta a final
                                             yyval.cod +=   yyvsp[0].cod;                                      // Ejecuta Instr
                                             yyval.cod +=   "jmp L" + std::to_string(etiq1)    + '\n';   // Salta a inicio
                                             yyval.cod +=   'L'     + std::to_string(etiq2)    + "\n";   // Etiq final
                                          }
#line 1687 "plp5.tab.c"
    break;

  case 26:
#line 205 "plp5.y"
                                          {  if(yyvsp[0].tipo != LOGICO) errorSemantico(ERR_EXP_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                             etiq1 = nuevaEtiqueta();
                                             yyval.cod =    'L'      + std::to_string(etiq1)    + "\n";     // Etiq inicio
                                             yyval.cod +=   yyvsp[-2].cod;                                         // Ejecutar Instr
                                             yyval.cod +=   yyvsp[0].cod;                                         // Ejecutar Expr
                                             yyval.cod +=   "mov "   + std::to_string(yyvsp[0].dir)   + " A\n";   // Carga resultado de Expr
                                             yyval.cod +=   "jz L"   + std::to_string(etiq1)    + '\n';     // Si Expr FALSE, salta a inicio
                                          }
#line 1700 "plp5.tab.c"
    break;

  case 27:
#line 213 "plp5.y"
                                          {  // Puedo asignar real a una variable entera? NO
                                             if(esArray(yyvsp[-2].tipo)) errorSemantico(ERR_FALTAN, yyvsp[-2].nlin, yyvsp[-2].ncol, yyvsp[-2].lexema);
                                             if(yyvsp[-2].tipo != yyvsp[0].tipo)
                                             {
                                                if(yyvsp[0].tipo == LOGICO)   // No se puede asignar valor lógico a variables enteras o reales
                                                {
                                                   if(yyvsp[-2].tipo == ENTERO) errorSemantico(ERR_EXDER_ENT, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                                   if(yyvsp[-2].tipo == REAL) errorSemantico(ERR_EXDER_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                                }
                                                // No se puede asignar valores enteros o reales a variable lógica
                                                if(yyvsp[-2].tipo == LOGICO) errorSemantico(ERR_EXDER_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);

                                                // No se puede asignar valor real a variable entera
                                                if(yyvsp[-2].tipo == ENTERO) errorSemantico(ERR_EXDER_ENT, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                                
                                                tmp = nuevaTemp();
                                                // Variable real -> Expr entero -> ITOR
                                                s1 =  "mov "   + std::to_string(yyvsp[0].dir)   + " A\n";   // Carga resultado entero de Expr
                                                s1 += "itor\n";                                       // ITOR
                                                s1 += "mov A " + std::to_string(tmp)      + '\n';     // Guarda resultado de Expr en temporal
                                                s1 += "mov "   + std::to_string(yyvsp[-2].dir)   + " A\n";   // Carga saltos en array Ref
                                                s1 += "addi #" + std::to_string(yyvsp[-2].dbase) + '\n';     // Añade dirección base
                                                s1 += "mov "   + std::to_string(tmp)      + " @A\n";  // Guarda resultado de Expr en Ref
                                             }
                                             else
                                             {
                                                s1 =  "mov "   + std::to_string(yyvsp[-2].dir)   + " A\n";   // Carga saltos en array Ref
                                                s1 += "addi #" + std::to_string(yyvsp[-2].dbase) + "\n";     // Añade dirección base
                                                s1 += "mov "   + std::to_string(yyvsp[0].dir)   + " @A\n";  // Guarda resultado de Expr en Ref
                                             }
                                             yyval.cod = yyvsp[-2].cod + yyvsp[0].cod + s1;
                                          }
#line 1737 "plp5.tab.c"
    break;

  case 28:
#line 245 "plp5.y"
             { tsActual = new TablaSimbolos(tsActual); }
#line 1743 "plp5.tab.c"
    break;

  case 29:
#line 245 "plp5.y"
                                                                      {
                                                                                    tsActual = tsActual->getAmbitoAnterior(); 
                                                                                    yyval.cod = yyvsp[-1].cod; }
#line 1751 "plp5.tab.c"
    break;

  case 30:
#line 250 "plp5.y"
                     { yyval.cod = yyvsp[0].cod;   }
#line 1757 "plp5.tab.c"
    break;

  case 31:
#line 251 "plp5.y"
                     { yyval.cod = "";       }
#line 1763 "plp5.tab.c"
    break;

  case 32:
#line 254 "plp5.y"
                           {  
                              yyval.tipo = LOGICO; 
                              if(yyvsp[-2].tipo != LOGICO) errorSemantico(ERR_EXIZQ_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                              if(yyvsp[0].tipo != LOGICO) errorSemantico(ERR_EXDER_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);

                              tmp = nuevaTemp(); yyval.dir = tmp;
                              yyval.cod +=   yyvsp[-2].cod   + yyvsp[0].cod;
                              yyval.cod +=   "mov "   + std::to_string(yyvsp[-2].dir)   + " A\n";
                              yyval.cod +=   "ori "   + std::to_string(yyvsp[0].dir)   + '\n';
                              yyval.cod +=   "mov A " + std::to_string(tmp)      + '\n';
                           }
#line 1779 "plp5.tab.c"
    break;

  case 33:
#line 265 "plp5.y"
                           {  yyval.tipo = yyvsp[0].tipo; yyval.cod = yyvsp[0].cod; yyval.dir = yyvsp[0].dir; }
#line 1785 "plp5.tab.c"
    break;

  case 34:
#line 268 "plp5.y"
                           {  
                              yyval.tipo = LOGICO; 
                              if(yyvsp[-2].tipo != LOGICO) errorSemantico(ERR_EXIZQ_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                              if(yyvsp[0].tipo != LOGICO) errorSemantico(ERR_EXDER_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);

                              tmp = nuevaTemp(); yyval.dir = tmp;
                              yyval.cod +=   yyvsp[-2].cod   + yyvsp[0].cod;
                              yyval.cod +=   "mov "   + std::to_string(yyvsp[-2].dir)   + " A\n";
                              yyval.cod +=   "andi "  + std::to_string(yyvsp[0].dir)   + '\n';
                              yyval.cod +=   "mov A " + std::to_string(tmp)      + '\n';
                           }
#line 1801 "plp5.tab.c"
    break;

  case 35:
#line 279 "plp5.y"
                           {  yyval.tipo = yyvsp[0].tipo; yyval.cod = yyvsp[0].cod; yyval.dir = yyvsp[0].dir; }
#line 1807 "plp5.tab.c"
    break;

  case 36:
#line 282 "plp5.y"
                                 {  tipo1 = yyvsp[-2].tipo;
                                    tipo2 = yyvsp[0].tipo;
                                    if(yyvsp[-2].tipo == LOGICO) errorSemantico(ERR_EXIZQ_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                    if(yyvsp[0].tipo == LOGICO) errorSemantico(ERR_EXDER_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                    yyval.tipo = LOGICO; 

                                    tmp = nuevaTemp(); yyval.dir = tmp;
                                    operador = string(yyvsp[-1].lexema);
                                    if(operador == "=")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "eqli" : "eqlr";
                                          s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                operador + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1
                                             s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                   string("itor\n")+
                                                   "eqlr " + std::to_string(yyvsp[0].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2
                                             s1 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +
                                                   string("itor\n")+
                                                   "eqlr " + std::to_string(yyvsp[-2].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == "<>")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "neqi" : "neqr";
                                          s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                operador + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1
                                             s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                   string("itor\n")+
                                                   "neqr " + std::to_string(yyvsp[0].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2
                                             s1 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +
                                                   string("itor\n")+
                                                   "neqr " + std::to_string(yyvsp[-2].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == "<")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "lssi" : "lssr";
                                          s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                operador + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 < tipo2)
                                             s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                   string("itor\n")+
                                                   "lssr " + std::to_string(yyvsp[0].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 > tipo1)
                                             s1 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +
                                                   string("itor\n")+
                                                   "gtrr " + std::to_string(yyvsp[-2].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == "<=")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "leqi" : "leqr";
                                          s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                operador + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 <= tipo2)
                                             s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                   "itor\n" +
                                                   "leqr " + std::to_string(yyvsp[0].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 >= tipo1)
                                             s1 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +
                                                   "itor\n" +
                                                   "geqr " + std::to_string(yyvsp[-2].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == ">")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "gtri" : "gtrr";
                                          s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                operador + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 > tipo2)
                                             s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                   "itor\n" +
                                                   "gtrr " + std::to_string(yyvsp[0].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 < tipo1)
                                             s1 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +
                                                   "itor\n" +
                                                   "lssr " + std::to_string(yyvsp[-2].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == ">=")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "geqi" : "geqr";
                                          s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                operador + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 > tipo2)
                                             s1 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                                   "itor\n" +
                                                   "geqr " + std::to_string(yyvsp[0].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 < tipo1)
                                             s1 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +
                                                   "itor\n" +
                                                   "leqr " + std::to_string(yyvsp[-2].dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }

                                    yyval.cod = yyvsp[-2].cod + yyvsp[0].cod + s1;
                                 }
#line 1961 "plp5.tab.c"
    break;

  case 37:
#line 431 "plp5.y"
                                 {  yyval.tipo = yyvsp[0].tipo; yyval.cod = yyvsp[0].cod; yyval.dir = yyvsp[0].dir; }
#line 1967 "plp5.tab.c"
    break;

  case 38:
#line 434 "plp5.y"
                              {   
                                 tipo1 = yyvsp[-2].tipo;
                                 tipo2 = yyvsp[0].tipo;
                                 if(tipo1 == LOGICO) errorSemantico(ERR_EXIZQ_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                 if(tipo2 == LOGICO) errorSemantico(ERR_EXDER_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                 // TODO: operadores '||' y '&&' deben tener operandos booleanos?  (enteros)
                                 tmp = nuevaTemp(); yyval.dir = tmp;
                                 operador = string(yyvsp[-1].lexema);

                                 if(tipo1 == tipo2)
                                 {  // No hace falta convertir tipos
                                    if(tipo1 == ENTERO)
                                       operadorTrad = (operador == "+") ? "addi" : "subi";
                                    else
                                       operadorTrad = (operador == "+") ? "addr" : "subr";
                                    
                                    s2 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                          operadorTrad + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                          "mov A " + std::to_string(tmp) + nextLine;
                                    
                                    yyval.tipo = tipo1;  // Tipo el que hayan sido ambos
                                 }
                                 else
                                 {
                                    operadorTrad = (operador == "+") ? "addr" : "subr";

                                    if(tipo1 == ENTERO)  // Entero opas Real
                                    {
                                       s2 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                             string("itor\n")+
                                             operadorTrad + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                             "mov A " + std::to_string(tmp) + nextLine;
                                    }
                                    else  // Real opas Entero
                                    {
                                       tmpcnv = nuevaTemp();
                                       s2 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +  //Carga Entero
                                             string("itor\n")+                 // itor
                                             "mov A " + std::to_string(tmpcnv) + nextLine +   // Guarda el convertido
                                             "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +                   // Carga Real
                                             operadorTrad + ' ' + std::to_string(tmpcnv) + nextLine +  // Opera con Entero convertido
                                             "mov A " + std::to_string(tmp) + nextLine;             // Guarda resultado
                                    }

                                    yyval.tipo = REAL;   // Tipo será real por itor
                                 }

                                 yyval.cod = yyvsp[-2].cod + yyvsp[0].cod + s2;
                              }
#line 2021 "plp5.tab.c"
    break;

  case 39:
#line 483 "plp5.y"
                              {  yyval.tipo = yyvsp[0].tipo; yyval.cod = yyvsp[0].cod; yyval.dir = yyvsp[0].dir; }
#line 2027 "plp5.tab.c"
    break;

  case 40:
#line 484 "plp5.y"
                              {  
                                 tipo1 = yyvsp[0].tipo;
                                 if(tipo1 == LOGICO) errorSemantico(ERR_EXDER_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                                 tmp = nuevaTemp(); yyval.dir = tmp;

                                 if(tipo1 == ENTERO)
                                 {
                                    operadorTrad = (operador == "+") ? "addi" : "subi";
                                    s2 = "mov #0 A\n" +     // Carga 0
                                       operadorTrad + ' ' + std::to_string(yyvsp[0].dir) + nextLine +  // Opera con Term
                                       "mov A " + std::to_string(tmp) + nextLine;                // Guarda resultado
                                 }
                                 else
                                 {
                                    operadorTrad = (operador == "+") ? "addr" : "subr";
                                    s2 = "mov $0 A\n" +     // Carga 0
                                       operadorTrad + ' ' + std::to_string(yyvsp[0].dir) + nextLine +  // Opera con Term
                                       "mov A " + std::to_string(tmp) + nextLine;                // Guarda resultado
                                 }
                                 
                                 
                                 
                                 yyval.tipo = tipo1;
                                 yyval.cod = yyvsp[0].cod + s2;
                              }
#line 2057 "plp5.tab.c"
    break;

  case 41:
#line 511 "plp5.y"
                           {
                              tipo1 = yyvsp[-2].tipo;
                              tipo2 = yyvsp[0].tipo;
                              if(tipo1 == LOGICO) errorSemantico(ERR_EXIZQ_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                              if(tipo2 == LOGICO) errorSemantico(ERR_EXDER_RE, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                              // TODO: operadores '||' y '&&' deben tener operandos booleanos?  (enteros)
                              tmp = nuevaTemp(); yyval.dir = tmp;
                              operador = string(yyvsp[-1].lexema);

                              if(tipo1 == tipo2)
                              {  // No hace falta convertir tipos
                                 if(tipo1 == ENTERO)
                                    operadorTrad = (operador == "*") ? "muli" : "divi";
                                 else
                                    operadorTrad = (operador == "*") ? "mulr" : "divr";
                                 
                                 s2 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                       operadorTrad + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                       "mov A " + std::to_string(tmp) + nextLine;
                                 
                                 yyval.tipo = tipo1;  // Tipo el que hayan sido ambos
                              }
                              else
                              {
                                 operadorTrad = (operador == "*") ? "mulr" : "divr";

                                 if(tipo1 == ENTERO)  // Entero opmd Real
                                 {
                                    s2 = "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +
                                          string("itor\n")+
                                          operadorTrad + ' ' + std::to_string(yyvsp[0].dir) + nextLine +
                                          "mov A " + std::to_string(tmp) + nextLine;
                                 }
                                 else  // Real opmd Entero
                                 {
                                    tmpcnv = nuevaTemp();
                                    s2 = "mov " + std::to_string(yyvsp[0].dir) + " A\n" +  //Carga Entero
                                          string("itor\n")+                 // itor
                                          "mov A " + std::to_string(tmpcnv) + nextLine +   // Guarda el convertido
                                          "mov " + std::to_string(yyvsp[-2].dir) + " A\n" +                   // Carga Real
                                          operadorTrad + ' ' + std::to_string(tmpcnv) + nextLine +  // Opera con Entero convertido
                                          "mov A " + std::to_string(tmp) + nextLine;             // Guarda resultado
                                 }

                                 yyval.tipo = REAL;   // Tipo será real por itor
                              }

                              yyval.cod = yyvsp[-2].cod + yyvsp[0].cod + s2;
                           }
#line 2111 "plp5.tab.c"
    break;

  case 42:
#line 560 "plp5.y"
                           {  yyval.tipo = yyvsp[0].tipo; yyval.cod = yyvsp[0].cod; yyval.dir = yyvsp[0].dir; }
#line 2117 "plp5.tab.c"
    break;

  case 43:
#line 563 "plp5.y"
                        {  
                           if(esArray(yyvsp[0].tipo)) errorSemantico(ERR_FALTAN, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                           yyval.tipo = yyvsp[0].tipo;
                           tmp = nuevaTemp(); yyval.dir = tmp;
                           yyval.cod = yyvsp[0].cod + 
                                    "mov " + std::to_string(yyvsp[0].dir) + " A\n"+
                                    string("addi #") + std::to_string(yyvsp[0].dbase) + nextLine +
                                    "mov @A " + std::to_string(tmp) + nextLine;
                        }
#line 2131 "plp5.tab.c"
    break;

  case 44:
#line 572 "plp5.y"
                        {  
                           yyval.tipo = ENTERO; 
                           tmp = nuevaTemp(); yyval.dir = tmp;
                           yyval.cod = "mov #" + string(yyvsp[0].lexema) + ' ' + std::to_string(tmp) + nextLine; 
                        }
#line 2141 "plp5.tab.c"
    break;

  case 45:
#line 577 "plp5.y"
                        {  
                           yyval.tipo = REAL; 
                           tmp = nuevaTemp(); yyval.dir = tmp;
                           yyval.cod = "mov $" + string(yyvsp[0].lexema) + ' ' + std::to_string(tmp) + nextLine; 
                        }
#line 2151 "plp5.tab.c"
    break;

  case 46:
#line 582 "plp5.y"
                        {  yyval.tipo = yyvsp[-1].tipo; yyval.cod = yyvsp[-1].cod; yyval.dir = yyvsp[-1].dir; }
#line 2157 "plp5.tab.c"
    break;

  case 47:
#line 583 "plp5.y"
                        {
                           tipo1 = yyvsp[0].tipo;
                           if(tipo1 != LOGICO) errorSemantico(ERR_EXDER_LOG, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                           yyval.tipo = tipo1; 
                           tmp = nuevaTemp(); yyval.dir = tmp;
                           yyval.cod = yyvsp[0].cod + 
                                    "mov " + std::to_string(yyvsp[0].dir) + "A\n" +
                                    "noti\n" +
                                    "mov A " + std::to_string(tmp) + nextLine;
                        }
#line 2172 "plp5.tab.c"
    break;

  case 48:
#line 593 "plp5.y"
                        {
                           yyval.tipo = LOGICO; 
                           tmp = nuevaTemp(); yyval.dir = tmp;
                           yyval.cod = "mov #1 " + std::to_string(tmp) + nextLine; 
                        }
#line 2182 "plp5.tab.c"
    break;

  case 49:
#line 598 "plp5.y"
                        {
                           yyval.tipo = LOGICO; 
                           tmp = nuevaTemp(); yyval.dir = tmp;
                           yyval.cod = "mov #0 " + std::to_string(tmp) + nextLine; 
                        }
#line 2192 "plp5.tab.c"
    break;

  case 50:
#line 605 "plp5.y"
                                 {  
                                    simbolo = tsActual->searchSymb(yyvsp[0].lexema);
                                    if(simbolo == NULL) 
                                       errorSemantico(ERR_NODECL, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                                    tmp = nuevaTemp(); yyval.dir = tmp;
                                    yyval.cod = "mov #0 " + std::to_string(tmp) + nextLine;
                                    // $$.cod = "mov #0 " + std::to_string(tmp) + nextLine;
                                    yyval.tipo = simbolo->tipo;
                                    yyval.dbase = simbolo->dir; 
                                    yyval.esArray = esArray(simbolo->tipo);
                                    yyval.nlin = yyvsp[0].nlin; yyval.ncol = yyvsp[0].ncol;
                                 }
#line 2209 "plp5.tab.c"
    break;

  case 51:
#line 617 "plp5.y"
                  { if(!esArray(yyvsp[-1].tipo))
                     {
                        if(yyvsp[-1].esArray) errorSemantico(ERR_SOBRAN, yyvsp[0].nlin, yyvsp[0].ncol, yyvsp[0].lexema);
                        else           errorSemantico(ERR_SOBRAN, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema);
                     }  
                  }
#line 2220 "plp5.tab.c"
    break;

  case 52:
#line 622 "plp5.y"
                                    {  
                                       if(yyvsp[-1].tipo != ENTERO) errorSemantico(ERR_INDICE_ENTERO, yyvsp[-1].nlin, yyvsp[-1].ncol, yyvsp[-1].lexema); 
                                       yyval.tipo = tipoBase(yyvsp[-4].tipo);
                                       yyval.dbase = yyvsp[-4].dbase;
                                       yyval.esArray = yyvsp[-4].esArray;
                                       tmp = nuevaTemp(); yyval.dir = tmp;
                                       yyval.cod = yyvsp[-4].cod + yyvsp[-1].cod + 
                                                "mov " + std::to_string(yyvsp[-4].dir) + " A\n" +
                                                "muli #" + std::to_string(tamanyoTipo(yyvsp[-4].tipo)) + nextLine +
                                                "addi " + std::to_string(yyvsp[-1].dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       yyval.lexema = yyvsp[0].lexema; yyval.nlin = yyvsp[0].nlin; yyval.ncol = yyvsp[0].ncol;   /* Por si luego tengo que lanzar error */
                                    }
#line 2238 "plp5.tab.c"
    break;


#line 2242 "plp5.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 637 "plp5.y"

int nuevaTemp(void)
{
   if (ctemp > MAX_DIR_TEMP)
      errorSemantico (ERR_MAXTMP, 0, 0, NULL);
   
   int tempReservado = ctemp;
   ++ctemp;
   
   return tempReservado;
}

int nuevaVar(string nombreVar, int tamVar)
{
   if (cvar + tamVar - 1 > MAX_DIR_VAR)
      errorSemantico (ERR_NOCABE, 0, 0, nombreVar.c_str());
   
   int tempReservado = cvar;
   cvar += tamVar;
   
   return tempReservado;
}


int nuevaEtiqueta()
{
   cetiq++;
   
   return cetiq;
}

void errorSemantico(int nerror,int nlin,int ncol,const char *s)
{
   fprintf(stderr,"Error semantico (%d,%d): ", nlin,ncol);
   switch(nerror) {
         case ERR_YADECL:        fprintf(stderr,"variable '%s' ya declarada\n",s);
            break;
         case ERR_NODECL:        fprintf(stderr,"variable '%s' no declarada\n",s);
            break;
         case ERR_DIM:           fprintf(stderr,"la dimension debe ser mayor que cero\n");
            break;
         case ERR_FALTAN:        fprintf(stderr,"faltan indices\n");
            break;
         case ERR_SOBRAN:        fprintf(stderr,"sobran indices\n");
            break;
         case ERR_INDICE_ENTERO: fprintf(stderr,"la expresion entre corchetes debe ser de tipo entero\n");
            break;
         case ERR_EXP_LOG:       fprintf(stderr,"la expresion debe ser de tipo logico\n");
            break;
         case ERR_EXDER_LOG:     fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo logico\n",s);
            break;
         case ERR_EXDER_ENT:     fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo entero\n",s);
            break;
         case ERR_EXDER_RE:      fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo real o entero\n",s);
            break;        
         case ERR_EXIZQ_LOG:     fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo logico\n",s);
            break;       
         case ERR_EXIZQ_RE:      fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo real o entero\n",s);
            break;       
         case ERR_NOCABE:        fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
            break;
         case ERR_MAXTMP:        fprintf(stderr,"no hay espacio para variables temporales\n");
            break;
   }
   exit(-1);
}

void msgError(int nerror,int nlin,int ncol,const char *s)
{
    switch (nerror) {
         case ERRLEXICO:   fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT:     fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF:      fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
     }

     exit(1);
}

int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,0,0,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    exit(-1);
    return -1;
}

int main(int argc,char *argv[])
{
    FILE *fent;
    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        fprintf(stderr,"Uso: ejemplo <nombre de fichero>\n");
}
