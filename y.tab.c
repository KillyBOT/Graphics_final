/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mdl.y" /* yacc.c:339  */

  /* C declarations */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "matrix.h"

#define YYERROR_VERBOSE 1

  SYMTAB *s;
  struct light *l;
  struct constants *c;
  struct command op[MAX_COMMANDS];
  struct matrix *m;
  int lastop=0;
  int lineno=0;
  

#line 86 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    COMMENT = 258,
    DOUBLE = 259,
    LIGHT = 260,
    AMBIENT = 261,
    CONSTANTS = 262,
    SAVE_COORDS = 263,
    CAMERA = 264,
    SPHERE = 265,
    TORUS = 266,
    BOX = 267,
    LINE = 268,
    CS = 269,
    MESH = 270,
    TEXTURE = 271,
    CYLINDER = 272,
    PLANE = 273,
    STRING = 274,
    SET = 275,
    SET_LIGHT_LOCATION = 276,
    SET_LIGHT_COLOR = 277,
    MOVE = 278,
    SCALE = 279,
    ROTATE = 280,
    BASENAME = 281,
    SAVE_KNOBS = 282,
    TWEEN = 283,
    FRAMES = 284,
    VARY = 285,
    PUSH = 286,
    POP = 287,
    SAVE = 288,
    GENERATE_RAYFILES = 289,
    SHADING = 290,
    SHADING_TYPE = 291,
    SETKNOBS = 292,
    FOCAL = 293,
    DISPLAY = 294,
    WEB = 295,
    CO = 296
  };
#endif
/* Tokens.  */
#define COMMENT 258
#define DOUBLE 259
#define LIGHT 260
#define AMBIENT 261
#define CONSTANTS 262
#define SAVE_COORDS 263
#define CAMERA 264
#define SPHERE 265
#define TORUS 266
#define BOX 267
#define LINE 268
#define CS 269
#define MESH 270
#define TEXTURE 271
#define CYLINDER 272
#define PLANE 273
#define STRING 274
#define SET 275
#define SET_LIGHT_LOCATION 276
#define SET_LIGHT_COLOR 277
#define MOVE 278
#define SCALE 279
#define ROTATE 280
#define BASENAME 281
#define SAVE_KNOBS 282
#define TWEEN 283
#define FRAMES 284
#define VARY 285
#define PUSH 286
#define POP 287
#define SAVE 288
#define GENERATE_RAYFILES 289
#define SHADING 290
#define SHADING_TYPE 291
#define SETKNOBS 292
#define FOCAL 293
#define DISPLAY 294
#define WEB 295
#define CO 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "mdl.y" /* yacc.c:355  */

  double val;
  char string[255];

#line 213 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 230 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  3
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    42,    47,    49,    62,    76,    90,   106,
     121,   136,   152,   169,   184,   199,   215,   232,   247,   262,
     278,   295,   312,   330,   347,   367,   385,   403,   421,   441,
     459,   478,   498,   519,   528,   538,   549,   560,   571,   583,
     594,   605,   629,   653,   660,   667,   674,   682,   707,   735,
     762,   771,   786,   809,   819,   847,   875,   882,   890,   901,
     909,   921,   928,   935,   943,   949,   959,   970
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMENT", "DOUBLE", "LIGHT", "AMBIENT",
  "CONSTANTS", "SAVE_COORDS", "CAMERA", "SPHERE", "TORUS", "BOX", "LINE",
  "CS", "MESH", "TEXTURE", "CYLINDER", "PLANE", "STRING", "SET",
  "SET_LIGHT_LOCATION", "SET_LIGHT_COLOR", "MOVE", "SCALE", "ROTATE",
  "BASENAME", "SAVE_KNOBS", "TWEEN", "FRAMES", "VARY", "PUSH", "POP",
  "SAVE", "GENERATE_RAYFILES", "SHADING", "SHADING_TYPE", "SETKNOBS",
  "FOCAL", "DISPLAY", "WEB", "CO", "$accept", "input", "command", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

#define YYPACT_NINF -19

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-19)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -19,     0,   -19,   -19,   -18,    -2,   -15,     3,    15,    37,
      38,    39,    40,    -5,    30,    41,    42,    31,    32,    48,
      49,    35,    36,    45,    61,    62,    50,   -19,   -19,    51,
     -19,    46,    63,    64,   -19,   -19,   -19,    67,    68,    69,
     -19,    70,    71,    72,    73,    74,    75,    76,    77,    79,
      47,    65,    81,    82,    83,    85,    86,    87,    78,    88,
      89,    90,   -19,   -19,    91,   -19,    92,   -19,   -19,   -19,
     -19,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    93,   106,   107,   109,   110,   111,   112,
     -19,   113,   114,   115,   108,   116,   117,   118,   119,   120,
     122,   124,   125,   126,   127,   128,   129,    43,   130,   121,
     -19,   132,   133,   135,   137,   138,   131,   134,   136,   -19,
     139,   140,   141,   -19,   142,   143,   144,   145,   147,   148,
     150,   152,   153,   155,    44,   -19,   156,   157,   158,   160,
     161,   -19,   -19,   -19,   -19,   162,   163,   164,   165,   -19,
     151,   154,   167,   168,   170,   171,   172,   173,   174,   175,
     166,   176,   169,   177,   -19,   178,   179,   -19,   -19,   -19,
     180,   181,   182,   183,   185,   186,   187,   188,   -19,   184,
     -19,   189,   -19,   190,   -19,   -19,   191,   -19,   192,   193,
     194,   197,   -19,   -19,   200,   -19,   -19,   -19,   195,   201,
     202,   -19,   203,   205,   209,   211,   212,   213,   214,   -19,
     -19
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,     0,
      67,     0,     0,     0,    45,    64,     3,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    56,    57,     0,    59,     0,    46,    61,    62,
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
      53,     0,     0,     0,    42,     0,     0,     0,    65,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      36,     0,     0,     0,     0,     0,    54,    38,    40,    41,
       0,     0,     0,    66,     0,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,    55,    37,    39,    58,     0,     0,     0,     0,     6,
       7,     9,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    13,     0,    60,     0,     0,    51,     8,    10,
      11,    21,     0,    25,     0,     0,     0,     0,    18,    19,
      14,    15,    47,     0,    12,    22,    23,    27,    26,    29,
       0,     0,    20,    16,     0,    24,    28,    31,    30,     0,
       0,    32,     0,    48,     0,     0,     0,     0,     0,    49,
      52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -19,   -19,   -19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       2,    37,    38,     3,    39,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    50,    13,    14,    15,    16,    41,
      17,    18,    40,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    51,    32,    33,    34,
      35,    42,    44,    46,    48,    53,    55,   132,   157,    52,
      57,    58,    59,    60,    61,    62,    43,    45,    47,    49,
      54,    56,   133,   158,    63,    64,    65,    69,    70,    66,
      67,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    68,    82,    84,    85,    86,    87,    83,    88,
      89,    90,    92,    93,    94,    95,    96,    91,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,   111,   109,   112,   113,   114,   115,   116,   117,   118,
       0,   121,   122,     0,   124,   110,   125,   119,   126,   127,
     128,   129,   130,   131,   134,   120,   136,   137,   123,   138,
     135,   139,   140,     0,   145,   146,   147,   148,     0,   150,
     141,   151,   152,   142,   153,   143,   154,   155,   144,   156,
     159,   160,   161,   149,   162,   163,   164,   165,   166,   167,
     168,   170,   171,   169,   172,   173,   174,   175,   176,   177,
     179,   181,   182,   183,     0,   178,   186,     0,   180,   188,
     189,   190,   191,     0,   194,     0,     0,     0,   198,   184,
     185,   199,   187,   192,   200,   202,   203,   204,   193,   205,
     195,   196,   197,   206,   201,   207,   208,   209,   210
};

static const yytype_int8 yycheck[] =
{
       0,    19,     4,     3,    19,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    19,    15,    16,    17,    18,     4,
      20,    21,    19,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    41,    37,    38,    39,
      40,     4,     4,     4,     4,     4,     4,     4,     4,    19,
      19,    19,     4,     4,    19,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    19,     4,     4,     4,     4,    19,
      19,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,    36,     4,    19,     4,     4,     4,    41,     4,
       4,     4,     4,     4,     4,     4,     4,    19,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
      -1,     4,    19,     4,     4,     4,     4,     4,     4,     4,
      -1,     4,     4,    -1,     4,    19,     4,    19,     4,     4,
       4,     4,     4,     4,     4,    19,     4,     4,    19,     4,
      19,     4,     4,    -1,     4,     4,     4,     4,    -1,     4,
      19,     4,     4,    19,     4,    19,     4,     4,    19,     4,
       4,     4,     4,    19,     4,     4,     4,     4,     4,     4,
      19,     4,     4,    19,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,    -1,    19,     4,    -1,    19,     4,
       4,     4,     4,    -1,     4,    -1,    -1,    -1,     4,    19,
      19,     4,    19,    19,     4,     4,     4,     4,    19,     4,
      19,    19,    19,     4,    19,     4,     4,     4,     4
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,     0,     3,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    15,    16,    17,    18,    20,    21,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    37,    38,    39,    40,    44,    19,     4,    19,
      19,     4,     4,    19,     4,    19,     4,    19,     4,    19,
      19,    41,    19,     4,    19,     4,    19,    19,    19,     4,
       4,    19,    19,    19,     4,     4,    19,    19,    36,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    41,    19,     4,     4,     4,     4,     4,
       4,    19,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    19,
      19,     4,     4,     4,     4,     4,     4,     4,     4,    19,
      19,     4,     4,    19,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    19,     4,    19,     4,     4,     4,     4,
       4,    19,    19,    19,    19,     4,     4,     4,     4,    19,
       4,     4,     4,     4,     4,     4,     4,     4,    19,     4,
       4,     4,     4,     4,     4,     4,     4,     4,    19,    19,
       4,     4,     4,     4,     4,     4,     4,     4,    19,     4,
      19,     4,     4,     4,    19,    19,     4,    19,     4,     4,
       4,     4,    19,    19,     4,    19,    19,    19,     4,     4,
       4,    19,     4,     4,     4,     4,     4,     4,     4,     4,
       4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     5,     6,     6,     7,     6,
       7,     7,     8,     6,     7,     7,     8,     6,     7,     7,
       8,     7,     8,     8,     9,     7,     8,     8,     9,     8,
       9,     9,    10,     3,     4,     5,     4,     5,     4,     5,
       4,     4,     3,     1,     1,     1,     2,     8,    11,    14,
       2,     7,    14,     3,     4,     5,     2,     2,     5,     2,
       6,     2,     2,     2,     1,     4,     5,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 4:
#line 47 "mdl.y" /* yacc.c:1646  */
    {}
#line 1431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 50 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SPHERE;
  op[lastop].op.sphere.d[0] = (yyvsp[-3].val);
  op[lastop].op.sphere.d[1] = (yyvsp[-2].val);
  op[lastop].op.sphere.d[2] = (yyvsp[-1].val);
  op[lastop].op.sphere.d[3] = 0;
  op[lastop].op.sphere.r = (yyvsp[0].val);
  op[lastop].op.sphere.constants = NULL;
  op[lastop].op.sphere.cs = NULL;
  lastop++;
}
#line 1448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 63 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SPHERE;
  op[lastop].op.sphere.d[0] = (yyvsp[-4].val);
  op[lastop].op.sphere.d[1] = (yyvsp[-3].val);
  op[lastop].op.sphere.d[2] = (yyvsp[-2].val);
  op[lastop].op.sphere.d[3] = 0;
  op[lastop].op.sphere.r = (yyvsp[-1].val);
  op[lastop].op.sphere.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.sphere.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 77 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SPHERE;
  op[lastop].op.sphere.d[0] = (yyvsp[-3].val);
  op[lastop].op.sphere.d[1] = (yyvsp[-2].val);
  op[lastop].op.sphere.d[2] = (yyvsp[-1].val);
  op[lastop].op.sphere.d[3] = 0;
  op[lastop].op.sphere.r = (yyvsp[0].val);
  op[lastop].op.sphere.cs = NULL;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.sphere.constants = add_symbol((yyvsp[-4].string),SYM_CONSTANTS,c);
  lastop++;
}
#line 1484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 91 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SPHERE;
  op[lastop].op.sphere.d[0] = (yyvsp[-4].val);
  op[lastop].op.sphere.d[1] = (yyvsp[-3].val);
  op[lastop].op.sphere.d[2] = (yyvsp[-2].val);
  op[lastop].op.sphere.d[3] = 0;
  op[lastop].op.sphere.r = (yyvsp[-1].val);
  op[lastop].op.sphere.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.sphere.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.sphere.constants = add_symbol((yyvsp[-5].string),SYM_CONSTANTS,c);
  lastop++;
}
#line 1504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 107 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = TORUS;
  op[lastop].op.torus.d[0] = (yyvsp[-4].val);
  op[lastop].op.torus.d[1] = (yyvsp[-3].val);
  op[lastop].op.torus.d[2] = (yyvsp[-2].val);
  op[lastop].op.torus.d[3] = 0;
  op[lastop].op.torus.r0 = (yyvsp[-1].val);
  op[lastop].op.torus.r1 = (yyvsp[0].val);
  op[lastop].op.torus.constants = NULL;
  op[lastop].op.torus.cs = NULL;

  lastop++;
}
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 122 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = TORUS;
  op[lastop].op.torus.d[0] = (yyvsp[-5].val);
  op[lastop].op.torus.d[1] = (yyvsp[-4].val);
  op[lastop].op.torus.d[2] = (yyvsp[-3].val);
  op[lastop].op.torus.d[3] = 0;
  op[lastop].op.torus.r0 = (yyvsp[-2].val);
  op[lastop].op.torus.r1 = (yyvsp[-1].val);
  op[lastop].op.torus.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.torus.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 137 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = TORUS;
  op[lastop].op.torus.d[0] = (yyvsp[-4].val);
  op[lastop].op.torus.d[1] = (yyvsp[-3].val);
  op[lastop].op.torus.d[2] = (yyvsp[-2].val);
  op[lastop].op.torus.d[3] = 0;
  op[lastop].op.torus.r0 = (yyvsp[-1].val);
  op[lastop].op.torus.r1 = (yyvsp[0].val);
  op[lastop].op.torus.cs = NULL;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.torus.constants = add_symbol((yyvsp[-5].string),SYM_CONSTANTS,c);

  lastop++;
}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 153 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = TORUS;
  op[lastop].op.torus.d[0] = (yyvsp[-5].val);
  op[lastop].op.torus.d[1] = (yyvsp[-4].val);
  op[lastop].op.torus.d[2] = (yyvsp[-3].val);
  op[lastop].op.torus.d[3] = 0;
  op[lastop].op.torus.r0 = (yyvsp[-2].val);
  op[lastop].op.torus.r1 = (yyvsp[-1].val);
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.torus.constants = add_symbol((yyvsp[-6].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.torus.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);

  lastop++;
}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 170 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = PLANE;
  op[lastop].op.plane.d[0] = (yyvsp[-4].val);
  op[lastop].op.plane.d[1] = (yyvsp[-3].val);
  op[lastop].op.plane.d[2] = (yyvsp[-2].val);
  op[lastop].op.plane.d[3] = 0;
  op[lastop].op.plane.w = (yyvsp[-1].val);
  op[lastop].op.plane.h = (yyvsp[0].val);
  op[lastop].op.plane.constants = NULL;
  op[lastop].op.plane.cs = NULL;

  lastop++;
}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 185 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = PLANE;
  op[lastop].op.plane.d[0] = (yyvsp[-5].val);
  op[lastop].op.plane.d[1] = (yyvsp[-4].val);
  op[lastop].op.plane.d[2] = (yyvsp[-3].val);
  op[lastop].op.plane.d[3] = 0;
  op[lastop].op.plane.w = (yyvsp[-2].val);
  op[lastop].op.plane.h = (yyvsp[-1].val);
  op[lastop].op.plane.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.plane.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 200 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = PLANE;
  op[lastop].op.plane.d[0] = (yyvsp[-4].val);
  op[lastop].op.plane.d[1] = (yyvsp[-3].val);
  op[lastop].op.plane.d[2] = (yyvsp[-2].val);
  op[lastop].op.plane.d[3] = 0;
  op[lastop].op.plane.w = (yyvsp[-1].val);
  op[lastop].op.plane.h = (yyvsp[0].val);
  op[lastop].op.plane.cs = NULL;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.plane.constants = add_symbol((yyvsp[-5].string),SYM_CONSTANTS,c);

  lastop++;
}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 216 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = PLANE;
  op[lastop].op.plane.d[0] = (yyvsp[-5].val);
  op[lastop].op.plane.d[1] = (yyvsp[-4].val);
  op[lastop].op.plane.d[2] = (yyvsp[-3].val);
  op[lastop].op.plane.d[3] = 0;
  op[lastop].op.plane.w = (yyvsp[-2].val);
  op[lastop].op.plane.h = (yyvsp[-1].val);
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.plane.constants = add_symbol((yyvsp[-6].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.plane.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);

  lastop++;
}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 233 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = CYLINDER;
  op[lastop].op.cylinder.d[0] = (yyvsp[-4].val);
  op[lastop].op.cylinder.d[1] = (yyvsp[-3].val);
  op[lastop].op.cylinder.d[2] = (yyvsp[-2].val);
  op[lastop].op.cylinder.d[3] = 0;
  op[lastop].op.cylinder.r = (yyvsp[-1].val);
  op[lastop].op.cylinder.h = (yyvsp[0].val);
  op[lastop].op.cylinder.constants = NULL;
  op[lastop].op.cylinder.cs = NULL;

  lastop++;
}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 248 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = CYLINDER;
  op[lastop].op.cylinder.d[0] = (yyvsp[-5].val);
  op[lastop].op.cylinder.d[1] = (yyvsp[-4].val);
  op[lastop].op.cylinder.d[2] = (yyvsp[-3].val);
  op[lastop].op.cylinder.d[3] = 0;
  op[lastop].op.cylinder.r = (yyvsp[-2].val);
  op[lastop].op.cylinder.h = (yyvsp[-1].val);
  op[lastop].op.cylinder.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.cylinder.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 263 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = CYLINDER;
  op[lastop].op.cylinder.d[0] = (yyvsp[-4].val);
  op[lastop].op.cylinder.d[1] = (yyvsp[-3].val);
  op[lastop].op.cylinder.d[2] = (yyvsp[-2].val);
  op[lastop].op.cylinder.d[3] = 0;
  op[lastop].op.cylinder.r = (yyvsp[-1].val);
  op[lastop].op.cylinder.h = (yyvsp[0].val);
  op[lastop].op.cylinder.cs = NULL;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.cylinder.constants = add_symbol((yyvsp[-5].string),SYM_CONSTANTS,c);

  lastop++;
}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 279 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = CYLINDER;
  op[lastop].op.cylinder.d[0] = (yyvsp[-5].val);
  op[lastop].op.cylinder.d[1] = (yyvsp[-4].val);
  op[lastop].op.cylinder.d[2] = (yyvsp[-3].val);
  op[lastop].op.cylinder.d[3] = 0;
  op[lastop].op.cylinder.r = (yyvsp[-2].val);
  op[lastop].op.cylinder.h = (yyvsp[-1].val);
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.cylinder.constants = add_symbol((yyvsp[-6].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.cylinder.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);

  lastop++;
}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 296 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = BOX;
  op[lastop].op.box.d0[0] = (yyvsp[-5].val);
  op[lastop].op.box.d0[1] = (yyvsp[-4].val);
  op[lastop].op.box.d0[2] = (yyvsp[-3].val);
  op[lastop].op.box.d0[3] = 0;
  op[lastop].op.box.d1[0] = (yyvsp[-2].val);
  op[lastop].op.box.d1[1] = (yyvsp[-1].val);
  op[lastop].op.box.d1[2] = (yyvsp[0].val);
  op[lastop].op.box.d1[3] = 0;

  op[lastop].op.box.constants = NULL;
  op[lastop].op.box.cs = NULL;
  lastop++;
}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 313 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = BOX;
  op[lastop].op.box.d0[0] = (yyvsp[-6].val);
  op[lastop].op.box.d0[1] = (yyvsp[-5].val);
  op[lastop].op.box.d0[2] = (yyvsp[-4].val);
  op[lastop].op.box.d0[3] = 0;
  op[lastop].op.box.d1[0] = (yyvsp[-3].val);
  op[lastop].op.box.d1[1] = (yyvsp[-2].val);
  op[lastop].op.box.d1[2] = (yyvsp[-1].val);
  op[lastop].op.box.d1[3] = 0;

  op[lastop].op.box.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.box.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 331 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = BOX;
  op[lastop].op.box.d0[0] = (yyvsp[-5].val);
  op[lastop].op.box.d0[1] = (yyvsp[-4].val);
  op[lastop].op.box.d0[2] = (yyvsp[-3].val);
  op[lastop].op.box.d0[3] = 0;
  op[lastop].op.box.d1[0] = (yyvsp[-2].val);
  op[lastop].op.box.d1[1] = (yyvsp[-1].val);
  op[lastop].op.box.d1[2] = (yyvsp[0].val);
  op[lastop].op.box.d1[3] = 0;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.box.constants = add_symbol((yyvsp[-6].string),SYM_CONSTANTS,c);
  op[lastop].op.box.cs = NULL;
  lastop++;
}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 348 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = BOX;
  op[lastop].op.box.d0[0] = (yyvsp[-6].val);
  op[lastop].op.box.d0[1] = (yyvsp[-5].val);
  op[lastop].op.box.d0[2] = (yyvsp[-4].val);
  op[lastop].op.box.d0[3] = 0;
  op[lastop].op.box.d1[0] = (yyvsp[-3].val);
  op[lastop].op.box.d1[1] = (yyvsp[-2].val);
  op[lastop].op.box.d1[2] = (yyvsp[-1].val);
  op[lastop].op.box.d1[3] = 0;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.box.constants = add_symbol((yyvsp[-7].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.box.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);

  lastop++;
}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 368 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-5].val);
  op[lastop].op.line.p0[1] = (yyvsp[-4].val);
  op[lastop].op.line.p0[2] = (yyvsp[-3].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-2].val);
  op[lastop].op.line.p1[1] = (yyvsp[-1].val);
  op[lastop].op.line.p1[2] = (yyvsp[0].val);
  op[lastop].op.line.p1[3] = 0;
  op[lastop].op.line.constants = NULL;
  op[lastop].op.line.cs0 = NULL;
  op[lastop].op.line.cs1 = NULL;
  lastop++;
}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 386 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-6].val);
  op[lastop].op.line.p0[1] = (yyvsp[-5].val);
  op[lastop].op.line.p0[2] = (yyvsp[-4].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-2].val);
  op[lastop].op.line.p1[1] = (yyvsp[-1].val);
  op[lastop].op.line.p1[2] = (yyvsp[0].val);
  op[lastop].op.line.p1[3] = 0;
  op[lastop].op.line.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs0 = add_symbol((yyvsp[-3].string),SYM_MATRIX,m);
  op[lastop].op.line.cs1 = NULL;
  lastop++;
}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 404 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-6].val);
  op[lastop].op.line.p0[1] = (yyvsp[-5].val);
  op[lastop].op.line.p0[2] = (yyvsp[-4].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-3].val);
  op[lastop].op.line.p1[1] = (yyvsp[-2].val);
  op[lastop].op.line.p1[2] = (yyvsp[-1].val);
  op[lastop].op.line.p1[3] = 0;
  op[lastop].op.line.constants = NULL;
  op[lastop].op.line.cs0 = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs1 = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 422 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-7].val);
  op[lastop].op.line.p0[1] = (yyvsp[-6].val);
  op[lastop].op.line.p0[2] = (yyvsp[-5].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-3].val);
  op[lastop].op.line.p1[1] = (yyvsp[-2].val);
  op[lastop].op.line.p1[2] = (yyvsp[-1].val);
  op[lastop].op.line.p1[3] = 0;
  op[lastop].op.line.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs0 = add_symbol((yyvsp[-4].string),SYM_MATRIX,m);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs1 = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 442 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-5].val);
  op[lastop].op.line.p0[1] = (yyvsp[-4].val);
  op[lastop].op.line.p0[2] = (yyvsp[-3].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-2].val);
  op[lastop].op.line.p1[1] = (yyvsp[-1].val);
  op[lastop].op.line.p1[2] = (yyvsp[0].val);
  op[lastop].op.line.p1[3] = 0;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.line.constants = add_symbol((yyvsp[-6].string),SYM_CONSTANTS,c);
  op[lastop].op.line.cs0 = NULL;
  op[lastop].op.line.cs1 = NULL;
  lastop++;
}
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 460 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-6].val);
  op[lastop].op.line.p0[1] = (yyvsp[-5].val);
  op[lastop].op.line.p0[2] = (yyvsp[-4].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-2].val);
  op[lastop].op.line.p1[1] = (yyvsp[-1].val);
  op[lastop].op.line.p1[2] = (yyvsp[0].val);
  op[lastop].op.line.p1[3] = 0;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.line.constants = add_symbol((yyvsp[-7].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs0 = add_symbol((yyvsp[-3].string),SYM_MATRIX,m);
  op[lastop].op.line.cs1 = NULL;
  lastop++;
}
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 479 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-6].val);
  op[lastop].op.line.p0[1] = (yyvsp[-5].val);
  op[lastop].op.line.p0[2] = (yyvsp[-4].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-3].val);
  op[lastop].op.line.p1[1] = (yyvsp[-2].val);
  op[lastop].op.line.p1[2] = (yyvsp[-1].val);
  op[lastop].op.line.p1[3] = 0;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.line.constants = add_symbol((yyvsp[-7].string),SYM_CONSTANTS,c);
  op[lastop].op.line.cs0 = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs1 = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  op[lastop].op.line.cs0 = NULL;
  lastop++;
}
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 499 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = LINE;
  op[lastop].op.line.p0[0] = (yyvsp[-7].val);
  op[lastop].op.line.p0[1] = (yyvsp[-6].val);
  op[lastop].op.line.p0[2] = (yyvsp[-5].val);
  op[lastop].op.line.p0[3] = 0;
  op[lastop].op.line.p1[0] = (yyvsp[-3].val);
  op[lastop].op.line.p1[1] = (yyvsp[-2].val);
  op[lastop].op.line.p1[2] = (yyvsp[-1].val);
  op[lastop].op.line.p1[3] = 0;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.line.constants = add_symbol((yyvsp[-8].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs0 = add_symbol((yyvsp[-4].string),SYM_MATRIX,m);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.line.cs1 = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 520 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = MESH;
  strcpy(op[lastop].op.mesh.name,(yyvsp[0].string));
  op[lastop].op.mesh.constants = NULL;
  op[lastop].op.mesh.cs = NULL;
  lastop++;
}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 529 "mdl.y" /* yacc.c:1646  */
    { /* name and constants */
  lineno++;
  op[lastop].opcode = MESH;
  strcpy(op[lastop].op.mesh.name,(yyvsp[0].string));
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.mesh.constants = add_symbol((yyvsp[-2].string),SYM_CONSTANTS,c);
  op[lastop].op.mesh.cs = NULL;
  lastop++;
}
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 539 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = MESH;
  strcpy(op[lastop].op.mesh.name,(yyvsp[-1].string));
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.mesh.constants = add_symbol((yyvsp[-3].string),SYM_CONSTANTS,c);
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.mesh.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 550 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = MESH;
  strcpy(op[lastop].op.mesh.name,(yyvsp[-1].string));
  op[lastop].op.mesh.constants = NULL;
  m = (struct matrix *)new_matrix(4,4);
  op[lastop].op.mesh.cs = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 561 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = MOVE;
  op[lastop].op.move.d[0] = (yyvsp[-3].val);
  op[lastop].op.move.d[1] = (yyvsp[-2].val);
  op[lastop].op.move.d[2] = (yyvsp[-1].val);
  op[lastop].op.move.d[3] = 0;
  op[lastop].op.move.p = add_symbol((yyvsp[0].string),SYM_VALUE,0);
  lastop++;
}
#line 2080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 572 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = MOVE;
  op[lastop].op.move.d[0] = (yyvsp[-2].val);
  op[lastop].op.move.d[1] = (yyvsp[-1].val);
  op[lastop].op.move.d[2] = (yyvsp[0].val);
  op[lastop].op.move.d[3] = 0;
  op[lastop].op.move.p = NULL;
  lastop++;
}
#line 2095 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 584 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SCALE;
  op[lastop].op.scale.d[0] = (yyvsp[-3].val);
  op[lastop].op.scale.d[1] = (yyvsp[-2].val);
  op[lastop].op.scale.d[2] = (yyvsp[-1].val);
  op[lastop].op.scale.d[3] = 0;
  op[lastop].op.scale.p = add_symbol((yyvsp[0].string),SYM_VALUE,0);
  lastop++;
}
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 595 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SCALE;
  op[lastop].op.scale.d[0] = (yyvsp[-2].val);
  op[lastop].op.scale.d[1] = (yyvsp[-1].val);
  op[lastop].op.scale.d[2] = (yyvsp[0].val);
  op[lastop].op.scale.d[3] = 0;
  op[lastop].op.scale.p = NULL;
  lastop++;
}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 606 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = ROTATE;
  switch (*(yyvsp[-2].string))
    {
    case 'x':
    case 'X':
      op[lastop].op.rotate.axis = 0;
      break;
    case 'y':
    case 'Y':
      op[lastop].op.rotate.axis = 1;
      break;
    case 'z':
    case 'Z':
      op[lastop].op.rotate.axis = 2;
      break;
    }

  op[lastop].op.rotate.degrees = (yyvsp[-1].val);
  op[lastop].op.rotate.p = add_symbol((yyvsp[0].string),SYM_VALUE,0);
  lastop++;
}
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 630 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = ROTATE;
  switch (*(yyvsp[-1].string))
    {
    case 'x':
    case 'X':
      op[lastop].op.rotate.axis = 0;
      break;
    case 'y':
    case 'Y':
      op[lastop].op.rotate.axis = 1;
      break;
    case 'z':
    case 'Z':
      op[lastop].op.rotate.axis = 2;
      break;
    }
  op[lastop].op.rotate.degrees = (yyvsp[0].val);
  op[lastop].op.rotate.p = NULL;
  lastop++;
}
#line 2180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 654 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = PUSH;
  lastop++;
}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 661 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = POP;
  lastop++;
}
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 668 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = DISPLAY;
  lastop++;
}
#line 2210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 675 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SAVE;
  op[lastop].op.save.p = add_symbol((yyvsp[0].string),SYM_FILE,0);
  lastop++;
}
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 683 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  l = (struct light *)malloc(sizeof(struct light));
  l->l[0]= (yyvsp[-5].val);
  l->l[1]= (yyvsp[-4].val);
  l->l[2]= (yyvsp[-3].val);
  l->l[3]= 0;
  l->c[0]= (yyvsp[-2].val);
  l->c[1]= (yyvsp[-1].val);
  l->c[2]= (yyvsp[0].val);
  op[lastop].opcode=LIGHT;
  op[lastop].op.light.l[0] = (yyvsp[-5].val);
  op[lastop].op.light.l[1] = (yyvsp[-4].val);
  op[lastop].op.light.l[2] = (yyvsp[-3].val);
  op[lastop].op.light.l[3] = 0;
  op[lastop].op.light.c[0] = (yyvsp[-2].val);
  op[lastop].op.light.c[1] = (yyvsp[-1].val);
  op[lastop].op.light.c[2] = (yyvsp[0].val);
  op[lastop].op.light.c[3] = 0;
  op[lastop].op.light.p = add_symbol((yyvsp[-6].string),SYM_LIGHT,l);
  op[lastop].op.light.v = NULL;
  lastop++;
}
#line 2249 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 708 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  c = (struct constants *)malloc(sizeof(struct constants));
  c->r[0]=(yyvsp[-8].val);
  c->r[1]=(yyvsp[-7].val);
  c->r[2]=(yyvsp[-6].val);
  c->r[3]=0;

  c->g[0]=(yyvsp[-5].val);
  c->g[1]=(yyvsp[-4].val);
  c->g[2]=(yyvsp[-3].val);
  c->g[3]=0;

  c->b[0]=(yyvsp[-2].val);
  c->b[1]=(yyvsp[-1].val);
  c->b[2]=(yyvsp[0].val);
  c->b[3]=0;

  c->red = 0;
  c->green = 0;
  c->blue = 0;

  op[lastop].op.constants.p =  add_symbol((yyvsp[-9].string),SYM_CONSTANTS,c);
  op[lastop].opcode=CONSTANTS;
  lastop++;
}
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 736 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  c = (struct constants *)malloc(sizeof(struct constants));
  c->r[0]=(yyvsp[-11].val);
  c->r[1]=(yyvsp[-10].val);
  c->r[2]=(yyvsp[-9].val);
  c->r[3]=0;

  c->g[0]=(yyvsp[-8].val);
  c->g[1]=(yyvsp[-7].val);
  c->g[2]=(yyvsp[-6].val);
  c->g[3]=0;

  c->b[0]=(yyvsp[-5].val);
  c->b[1]=(yyvsp[-4].val);
  c->b[2]=(yyvsp[-3].val);
  c->b[3]=0;

  c->red = (yyvsp[-2].val);
  c->green = (yyvsp[-1].val);
  c->blue = (yyvsp[0].val);
  op[lastop].op.constants.p =  add_symbol((yyvsp[-12].string),SYM_CONSTANTS,c);
  op[lastop].opcode=CONSTANTS;
  lastop++;
}
#line 2310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 763 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SAVE_COORDS;
  m = new_matrix(4,4);
  op[lastop].op.save_coordinate_system.p = add_symbol((yyvsp[0].string),SYM_MATRIX,m);
  lastop++;
}
#line 2322 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 772 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = CAMERA;
  op[lastop].op.camera.eye[0] = (yyvsp[-5].val);
  op[lastop].op.camera.eye[1] = (yyvsp[-4].val);
  op[lastop].op.camera.eye[2] = (yyvsp[-3].val);
  op[lastop].op.camera.eye[3] = 0;
  op[lastop].op.camera.aim[0] = (yyvsp[-2].val);
  op[lastop].op.camera.aim[1] = (yyvsp[-1].val);
  op[lastop].op.camera.aim[2] = (yyvsp[0].val);
  op[lastop].op.camera.aim[3] = 0;
  lastop++;
}
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 787 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = TEXTURE;
  c = (struct constants *)malloc(sizeof(struct constants));
  op[lastop].op.texture.d0[0] = (yyvsp[-11].val);
  op[lastop].op.texture.d0[1] = (yyvsp[-10].val);
  op[lastop].op.texture.d0[2] = (yyvsp[-9].val);
  op[lastop].op.texture.d1[0] = (yyvsp[-8].val);
  op[lastop].op.texture.d1[1] = (yyvsp[-7].val);
  op[lastop].op.texture.d1[2] = (yyvsp[-6].val);
  op[lastop].op.texture.d2[0] = (yyvsp[-5].val);
  op[lastop].op.texture.d2[1] = (yyvsp[-4].val);
  op[lastop].op.texture.d2[2] = (yyvsp[-3].val);
  op[lastop].op.texture.d3[0] = (yyvsp[-2].val);
  op[lastop].op.texture.d3[1] = (yyvsp[-1].val);
  op[lastop].op.texture.d3[2] = (yyvsp[0].val);
  op[lastop].op.texture.cs = NULL;
  op[lastop].op.texture.constants =  add_symbol("",SYM_CONSTANTS,c);
  op[lastop].op.texture.p = add_symbol((yyvsp[-12].string),SYM_FILE,0);
  lastop++;
}
#line 2366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 810 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SET;
  op[lastop].op.set.p = add_symbol((yyvsp[-1].string),SYM_VALUE,0);
  set_value(op[lastop].op.set.p,(yyvsp[0].val));
  op[lastop].op.set.val = (yyvsp[0].val);
  lastop++;
}
#line 2379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 820 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SET_LIGHT_LOCATION;
  op[lastop].op.set_light_location.p = add_symbol((yyvsp[-2].string),SYM_LIGHT,0);
  switch(*(yyvsp[-1].string)){
    case 'x':
    case 'X':
      op[lastop].op.set_light_location.axis = 0;
      break;
    case 'y':
    case 'Y':
      op[lastop].op.set_light_location.axis = 1;
      break;
    case 'z':
    case 'Z':
      op[lastop].op.set_light_location.axis = 2;
      break;
    default:
      op[lastop].op.set_light_location.axis = 0;
      break;
  }

  op[lastop].op.set_light_location.val = (yyvsp[0].val);
  op[lastop].op.set_light_location.v = NULL;
  lastop++;
}
#line 2410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 848 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SET_LIGHT_LOCATION;
  op[lastop].op.set_light_location.p = add_symbol((yyvsp[-3].string),SYM_LIGHT,0);
  switch(*(yyvsp[-2].string)){
    case 'x':
    case 'X':
      op[lastop].op.set_light_location.axis = 0;
      break;
    case 'y':
    case 'Y':
      op[lastop].op.set_light_location.axis = 1;
      break;
    case 'z':
    case 'Z':
      op[lastop].op.set_light_location.axis = 2;
      break;
    default:
      op[lastop].op.set_light_location.axis = 0;
      break;
  }

  op[lastop].op.set_light_location.val = (yyvsp[-1].val);
  op[lastop].op.set_light_location.v = add_symbol((yyvsp[0].string),SYM_VALUE,0);
  lastop++;
}
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 876 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = BASENAME;
  op[lastop].op.basename.p = add_symbol((yyvsp[0].string),SYM_STRING,0);
  lastop++;
}
#line 2452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 883 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SAVE_KNOBS;
  op[lastop].op.save_knobs.p = add_symbol((yyvsp[0].string),SYM_KNOBLIST,0);
  lastop++;
}
#line 2463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 891 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = TWEEN;
  op[lastop].op.tween.start_frame = (yyvsp[-3].val);
  op[lastop].op.tween.end_frame = (yyvsp[-2].val);
  op[lastop].op.tween.knob_list0 = add_symbol((yyvsp[-1].string),SYM_STRING,0);
  op[lastop].op.tween.knob_list1 = add_symbol((yyvsp[0].string),SYM_STRING,0);
  lastop++;
}
#line 2477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 902 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = FRAMES;
  op[lastop].op.frames.num_frames = (yyvsp[0].val);
  lastop++;
}
#line 2488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 910 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = VARY;
  op[lastop].op.vary.p = add_symbol((yyvsp[-4].string),SYM_STRING,0);
  op[lastop].op.vary.start_frame = (yyvsp[-3].val);
  op[lastop].op.vary.end_frame = (yyvsp[-2].val);
  op[lastop].op.vary.start_val = (yyvsp[-1].val);
  op[lastop].op.vary.end_val = (yyvsp[0].val);
  lastop++;
}
#line 2503 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 922 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SHADING;
  op[lastop].op.shading.p = add_symbol((yyvsp[0].string),SYM_STRING,0);
  lastop++;
}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 929 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = SETKNOBS;
  op[lastop].op.setknobs.value = (yyvsp[0].val);
  lastop++;
}
#line 2525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 936 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = FOCAL;
  op[lastop].op.focal.value = (yyvsp[0].val);
  lastop++;
}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 944 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = WEB;
  lastop++;
}
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 950 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = AMBIENT;
  op[lastop].op.ambient.c[0] = (yyvsp[-2].val);
  op[lastop].op.ambient.c[1] = (yyvsp[-1].val);
  op[lastop].op.ambient.c[2] = (yyvsp[0].val);
  lastop++;
}
#line 2559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 960 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = AMBIENT;
  op[lastop].op.ambient.c[0] = (yyvsp[-3].val);
  op[lastop].op.ambient.c[1] = (yyvsp[-2].val);
  op[lastop].op.ambient.c[2] = (yyvsp[-1].val);
  op[lastop].op.ambient.p = add_symbol((yyvsp[0].string), SYM_VALUE, 0);
  lastop++;
}
#line 2573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 971 "mdl.y" /* yacc.c:1646  */
    {
  lineno++;
  op[lastop].opcode = GENERATE_RAYFILES;
  lastop++;
}
#line 2583 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2587 "y.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 976 "mdl.y" /* yacc.c:1906  */



/* Other C stuff */
int yyerror(char *s)
{
  printf("Error in line %d:%s\n",lineno,s);
  return 0;
}

int yywrap()
{
  return 1;
}


extern FILE *yyin;


int main(int argc, char **argv) {

  yyin = fopen(argv[1],"r");

  yyparse();
  //COMMENT OUT PRINT_PCODE AND UNCOMMENT
  //MY_MAIN IN ORDER TO RUN YOUR CODE

  //print_pcode();
  my_main();

  return 0;
}
