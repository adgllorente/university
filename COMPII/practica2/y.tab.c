/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "pascual1.y"

/**********************************************************************
 * fichero: pascual.y
 *          Analizador sint'actico de Pascual
 *          2011-03-21
 *             jfabra - Cambios en la gram'atica
 **********************************************************************/

/**********************************************************************
 * Nombre: Adrián Gómez Llorente
 * NIP: 605731
 * Asignatura: Compiladores 2
 * Año: 2011
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errores.h"
#include "listas.h"
#include "tabla.h"

//P2
#include "codigop.h"
#include "genast.h"

#define MAX_ANIDACION 50

TABLA_SIMBOLOS tabsim;
int nivel;
extern lineno;
int muestra;
FILE *fxml;
FILE *fcompilado;
FILE *yyout;
int xml;
int nErrores;
int tabs;
int dar_warnings;
//P2: Dirección símbolos
int sig[MAX_ANIDACION];
char msg[100];

typedef struct{
		TIPO_VARIABLE tipo_var;
		SIMBOLO *simbolo;
		int valor;
		int es_componente;
		int tiene_valor;
		LISTA cod; //P2
		char *valor_cadena;
}EXPRESION;


void abrir_bloque();
void cerrar_bloque();
void ptabs(int i);

char *lend;



/* Line 189 of yacc.c  */
#line 134 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tPROGRAMA = 258,
     tACCION = 259,
     tCONSTENTERA = 260,
     tCONSTCHAR = 261,
     tCONSTCAD = 262,
     tTRUE = 263,
     tFALSE = 264,
     tENTACAR = 265,
     tCARAENT = 266,
     tBOOLEANO = 267,
     tIDENTIFICADOR = 268,
     tENTERO = 269,
     tCARACTER = 270,
     tESCRIBIR = 271,
     tLEER = 272,
     tOPAS = 273,
     tPRINCIPIO = 274,
     tFIN = 275,
     tAND = 276,
     tOR = 277,
     tNOT = 278,
     tMQ = 279,
     tFMQ = 280,
     tMEI = 281,
     tMAI = 282,
     tNI = 283,
     tMOD = 284,
     tDIV = 285,
     tSI = 286,
     tENT = 287,
     tSI_NO = 288,
     tFSI = 289,
     tVAL = 290,
     tREF = 291,
     tVECTOR = 292,
     tDE = 293,
     MENOSU = 294
   };
#endif
/* Tokens.  */
#define tPROGRAMA 258
#define tACCION 259
#define tCONSTENTERA 260
#define tCONSTCHAR 261
#define tCONSTCAD 262
#define tTRUE 263
#define tFALSE 264
#define tENTACAR 265
#define tCARAENT 266
#define tBOOLEANO 267
#define tIDENTIFICADOR 268
#define tENTERO 269
#define tCARACTER 270
#define tESCRIBIR 271
#define tLEER 272
#define tOPAS 273
#define tPRINCIPIO 274
#define tFIN 275
#define tAND 276
#define tOR 277
#define tNOT 278
#define tMQ 279
#define tFMQ 280
#define tMEI 281
#define tMAI 282
#define tNI 283
#define tMOD 284
#define tDIV 285
#define tSI 286
#define tENT 287
#define tSI_NO 288
#define tFSI 289
#define tVAL 290
#define tREF 291
#define tVECTOR 292
#define tDE 293
#define MENOSU 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 79 "pascual1.y"

  int constante;
  char *cadena;
  char car;
  SIMBOLO *simbolo;
  LISTA lista;
  LISTA cod;
  CLASE_PARAMETRO clase_parametro;
  
        struct{
                int extremo;
                TIPO_VARIABLE tipo;
        }indice_vector;
  
        struct{
                TIPO_VARIABLE tipo_var;
                SIMBOLO *simbolo;
                int valor;
				int es_componente;
				int tiene_valor;
				LISTA cod; //P2
				char *valor_cadena;
        }expresion;
  
        struct{
                TIPO_VARIABLE tipo_variable; //Tipo de variable o tipo de las variables del Vector
                int es_vector; //0: No | 1: SI
                int extremo1, extremo2; //Extremos de los vectores izquierda y derecha respectivamente
                int tipo_extremo; // 1: ENTERO | 2: BOOLEANO | 3: CARACTER
        }control_tipo;
  
  //Estructura de tIDENTIFICADOR
  struct{
        char *nombre;
        SIMBOLO *simbolo;
  }identificador;
  
  //Estructura operador_multiplicativo operador_aditivo operador_relacional
        struct{
                TIPO_VARIABLE tipo;
                char *op;
				LISTA cod; //P2
        }operador;
        
        TIPO_VARIABLE tipo;



/* Line 214 of yacc.c  */
#line 297 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 309 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  191

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,    41,    39,    48,    40,    46,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
      52,    51,    53,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    47,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    16,    17,    18,    22,
      26,    28,    31,    34,    37,    39,    41,    43,    45,    46,
      48,    50,    52,    62,    64,    68,    71,    72,    78,    79,
      84,    85,    89,    93,    95,    96,    99,   102,   108,   110,
     114,   116,   118,   122,   125,   126,   128,   130,   132,   134,
     136,   138,   140,   146,   148,   152,   158,   162,   164,   169,
     177,   194,   195,   201,   202,   210,   211,   214,   218,   221,
     225,   229,   231,   233,   237,   239,   241,   243,   245,   247,
     249,   251,   255,   257,   259,   261,   263,   267,   269,   271,
     273,   275,   278,   281,   285,   290,   295,   297,   299,   301,
     303,   305,   307
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    -1,    -1,    -1,     3,    13,    44,    56,
      59,    57,    68,    58,    78,    -1,    -1,    -1,    60,    61,
      44,    -1,    61,    44,    62,    -1,    62,    -1,    65,    67,
      -1,    66,    67,    -1,    64,     5,    -1,     8,    -1,     9,
      -1,     6,    -1,    40,    -1,    -1,    14,    -1,    12,    -1,
      15,    -1,    37,    45,    63,    46,    46,    63,    47,    38,
      65,    -1,    13,    -1,    67,    48,    13,    -1,    68,    69,
      -1,    -1,    70,    44,    59,    68,    78,    -1,    -1,     4,
      13,    71,    72,    -1,    -1,    49,    73,    50,    -1,    73,
      44,    74,    -1,    74,    -1,    -1,    77,    75,    -1,    65,
      76,    -1,    37,    13,    45,    63,    47,    -1,    13,    -1,
      76,    48,    13,    -1,    35,    -1,    36,    -1,    19,    79,
      20,    -1,    79,    80,    -1,    -1,    81,    -1,    83,    -1,
      85,    -1,    86,    -1,    89,    -1,    87,    -1,    92,    -1,
      17,    49,    82,    50,    44,    -1,    13,    -1,    82,    48,
      13,    -1,    16,    49,    84,    50,    44,    -1,    84,    48,
      95,    -1,    95,    -1,    13,    18,    95,    44,    -1,    13,
      45,    95,    47,    18,    95,    44,    -1,    13,    45,    95,
      46,    46,    95,    47,    18,    13,    45,    95,    46,    46,
      95,    47,    44,    -1,    -1,    24,    95,    88,    79,    25,
      -1,    -1,    31,    95,    90,    32,    79,    91,    34,    -1,
      -1,    33,    79,    -1,    13,    93,    44,    -1,    13,    44,
      -1,    49,    94,    50,    -1,    94,    48,    95,    -1,    95,
      -1,    97,    -1,    95,    96,    97,    -1,    51,    -1,    52,
      -1,    53,    -1,    26,    -1,    27,    -1,    28,    -1,    99,
      -1,    97,    98,    99,    -1,    39,    -1,    40,    -1,    22,
      -1,   101,    -1,    99,   100,   101,    -1,    41,    -1,    30,
      -1,    29,    -1,    21,    -1,    40,   101,    -1,    23,   101,
      -1,    49,    95,    50,    -1,    10,    49,    95,    50,    -1,
      11,    49,    95,    50,    -1,    13,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,     9,    -1,    13,    45,    95,
      47,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   146,   146,   158,   164,   145,   203,   205,   205,   218,
     219,   224,   225,   231,   239,   244,   249,   258,   259,   265,
     270,   275,   284,   313,   342,   374,   380,   386,   417,   416,
     461,   464,   472,   477,   482,   490,   497,   502,   512,   543,
     576,   580,   587,   595,   601,   608,   612,   616,   620,   624,
     628,   632,   639,   647,   673,   704,   714,   730,   753,   814,
     870,  1054,  1052,  1078,  1076,  1107,  1111,  1120,  1180,  1198,
    1205,  1210,  1217,  1227,  1278,  1286,  1294,  1302,  1310,  1318,
    1329,  1339,  1387,  1395,  1403,  1414,  1424,  1470,  1478,  1486,
    1494,  1506,  1523,  1540,  1550,  1566,  1582,  1612,  1622,  1632,
    1645,  1655,  1665
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tPROGRAMA", "tACCION", "tCONSTENTERA",
  "tCONSTCHAR", "tCONSTCAD", "tTRUE", "tFALSE", "tENTACAR", "tCARAENT",
  "tBOOLEANO", "tIDENTIFICADOR", "tENTERO", "tCARACTER", "tESCRIBIR",
  "tLEER", "tOPAS", "tPRINCIPIO", "tFIN", "tAND", "tOR", "tNOT", "tMQ",
  "tFMQ", "tMEI", "tMAI", "tNI", "tMOD", "tDIV", "tSI", "tENT", "tSI_NO",
  "tFSI", "tVAL", "tREF", "tVECTOR", "tDE", "'+'", "'-'", "'*'", "'/'",
  "MENOSU", "';'", "'['", "'.'", "']'", "','", "'('", "')'", "'='", "'<'",
  "'>'", "$accept", "programa", "$@1", "$@2", "$@3",
  "declaracion_variables", "$@4", "lista_declaraciones", "declaracion",
  "indice_vector", "signo", "tipo_variables", "tipo_variable_vector",
  "identificadores", "declaracion_acciones", "declaracion_accion",
  "cabecera_accion", "$@5", "parametros_formales", "lista_parametros",
  "parametros", "declaracion_parametro", "identificadores_parametros",
  "clase_parametros", "bloque_instrucciones", "lista_instrucciones",
  "instruccion", "leer", "lista_asignables", "escribir",
  "lista_escribibles", "asignacion", "asignacion_vector", "mientras_que",
  "$@6", "seleccion", "$@7", "resto_seleccion", "invocacion_accion",
  "argumentos", "lista_expresiones", "expresion", "operador_relacional",
  "expresion_simple", "operador_aditivo", "termino",
  "operador_multiplicativo", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    43,
      45,    42,    47,   294,    59,    91,    46,    93,    44,    40,
      41,    61,    60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    56,    57,    58,    55,    59,    60,    59,    61,
      61,    62,    62,    63,    63,    63,    63,    64,    64,    65,
      65,    65,    66,    67,    67,    68,    68,    69,    71,    70,
      72,    72,    73,    73,    73,    74,    75,    75,    76,    76,
      77,    77,    78,    79,    79,    80,    80,    80,    80,    80,
      80,    80,    81,    82,    82,    83,    84,    84,    85,    86,
      86,    88,    87,    90,    89,    91,    91,    92,    92,    93,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      97,    97,    98,    98,    98,    99,    99,   100,   100,   100,
     100,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     9,     0,     0,     3,     3,
       1,     2,     2,     2,     1,     1,     1,     1,     0,     1,
       1,     1,     9,     1,     3,     2,     0,     5,     0,     4,
       0,     3,     3,     1,     0,     2,     2,     5,     1,     3,
       1,     1,     3,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     3,     5,     3,     1,     4,     7,
      16,     0,     5,     0,     7,     0,     2,     3,     2,     3,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     2,     3,     4,     4,     1,     1,     1,     1,
       1,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     7,     3,     0,    26,
      20,    19,    21,     0,     0,    10,     0,     0,     4,    18,
       8,    23,    11,    12,     0,     0,    25,     0,    16,    14,
      15,    17,     0,     0,     9,     0,    28,    44,     5,     7,
       0,    13,    24,    30,     0,    26,    18,    34,    29,     0,
       0,     0,    42,     0,     0,    43,    45,    46,    47,    48,
      50,    49,    51,     0,     0,    40,    41,     0,    33,     0,
       0,    68,     0,     0,     0,     0,     0,    97,    98,    99,
     100,   101,     0,     0,    96,     0,     0,     0,    61,    72,
      80,    85,    63,    27,     0,     0,    31,     0,     0,    35,
       0,     0,     0,    71,    67,     0,    57,    53,     0,     0,
       0,     0,    92,    91,     0,    77,    78,    79,    74,    75,
      76,    44,     0,    84,    82,    83,     0,    90,    89,    88,
      87,     0,     0,     0,    32,     0,    38,    36,    58,     0,
       0,     0,    69,     0,     0,     0,     0,     0,     0,     0,
      93,     0,    73,    81,    86,    44,    22,    18,     0,     0,
       0,    70,    56,    55,    54,    52,    94,    95,   102,    62,
      65,     0,    39,     0,     0,    44,     0,    37,     0,    59,
      66,    64,     0,     0,     0,     0,     0,     0,     0,     0,
      60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     9,    25,     7,     8,    14,    15,    32,
      33,    16,    17,    22,    18,    26,    27,    43,    48,    67,
      68,    99,   137,    69,    38,    44,    55,    56,   108,    57,
     105,    58,    59,    60,   121,    61,   132,   176,    62,    74,
     102,    88,   122,    89,   126,    90,   131,    91
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -118
static const yytype_int16 yypact[] =
{
      42,    -6,    24,   -16,  -118,  -118,    27,  -118,    25,  -118,
    -118,  -118,  -118,    30,    39,  -118,    75,    75,    97,    14,
      25,  -118,    56,    56,   115,    89,  -118,    85,  -118,  -118,
    -118,  -118,    86,   126,  -118,   125,  -118,  -118,  -118,    27,
      88,  -118,  -118,    91,   173,  -118,    14,     6,  -118,   -15,
      93,   114,  -118,     4,     4,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,    60,    94,  -118,  -118,    32,  -118,    66,
       4,  -118,     4,     4,   120,     4,   152,  -118,  -118,  -118,
    -118,  -118,   117,   122,   124,     4,     4,     4,   131,   -14,
     147,  -118,   131,  -118,   132,     6,  -118,   165,   172,  -118,
      33,    21,    15,   131,  -118,    52,   131,  -118,    63,     4,
       4,     4,  -118,  -118,    43,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,     4,  -118,  -118,  -118,     4,  -118,  -118,  -118,
    -118,     4,   155,    95,  -118,   153,  -118,   144,  -118,   159,
     188,     4,  -118,     4,   157,   195,   166,    64,    71,    92,
    -118,   178,   -14,   147,  -118,  -118,  -118,    14,   198,     4,
       4,   131,   131,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
      19,   168,  -118,    99,   109,  -118,   179,  -118,   194,  -118,
     183,  -118,   203,   174,     4,   121,   171,     4,   128,   176,
    -118
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,  -118,  -118,  -118,  -118,   182,  -118,  -118,   202,   -45,
    -118,   -67,  -118,   201,   180,  -118,  -118,  -118,  -118,  -118,
     129,  -118,  -118,  -118,   160,  -117,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,   -54,  -118,   104,  -118,   101,  -118,   -80
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -7
static const yytype_int16 yytable[] =
{
      92,    64,    98,    70,   151,   112,   113,     3,   123,    77,
      78,    79,    80,    81,    82,    83,   100,    84,   101,   103,
      28,   106,    29,    30,     4,   124,   125,    85,     5,    71,
      72,    -6,    49,   114,    73,    50,    51,    10,   170,    11,
      12,    65,    66,    53,    86,     1,    -6,   115,   116,   117,
      54,   154,   175,    87,    31,   147,   148,   149,   180,   115,
     116,   117,    13,   141,    24,   142,   156,   139,   140,   115,
     116,   117,   118,   119,   120,    19,    95,   138,    10,    37,
      11,    12,    96,    20,   118,   119,   120,   161,    21,   162,
     115,   116,   117,   150,   118,   119,   120,   115,   116,   117,
     143,    24,   144,    97,    35,   173,   174,    10,    37,    11,
      12,   145,   171,   146,   166,   118,   119,   120,   115,   116,
     117,   167,   118,   119,   120,   115,   116,   117,    36,    39,
     185,    41,    40,   188,    46,   115,   116,   117,    42,   168,
      47,    94,    75,   118,   119,   120,   178,   115,   116,   117,
     118,   119,   120,   179,   115,   116,   117,   115,   116,   117,
     118,   119,   120,    76,   104,   107,   109,   186,   127,   111,
     133,   110,   118,   119,   120,   189,   128,   129,   135,   118,
     119,   120,   118,   119,   120,   136,    49,   155,   130,    50,
      51,    49,   158,    52,    50,    51,    49,    53,   157,    50,
      51,   163,    53,   169,    54,   159,   160,    53,   164,    54,
     165,   172,   182,   181,    54,   177,   183,   187,    23,   184,
     190,    45,    34,    93,   134,    63,   152,   153
};

static const yytype_uint8 yycheck[] =
{
      54,    46,    69,    18,   121,    85,    86,    13,    22,     5,
       6,     7,     8,     9,    10,    11,    70,    13,    72,    73,
       6,    75,     8,     9,     0,    39,    40,    23,    44,    44,
      45,     4,    13,    87,    49,    16,    17,    12,   155,    14,
      15,    35,    36,    24,    40,     3,    19,    26,    27,    28,
      31,   131,    33,    49,    40,   109,   110,   111,   175,    26,
      27,    28,    37,    48,     4,    50,   133,    46,    47,    26,
      27,    28,    51,    52,    53,    45,    44,    44,    12,    19,
      14,    15,    50,    44,    51,    52,    53,   141,    13,   143,
      26,    27,    28,    50,    51,    52,    53,    26,    27,    28,
      48,     4,    50,    37,    48,   159,   160,    12,    19,    14,
      15,    48,   157,    50,    50,    51,    52,    53,    26,    27,
      28,    50,    51,    52,    53,    26,    27,    28,    13,    44,
     184,     5,    46,   187,    46,    26,    27,    28,    13,    47,
      49,    47,    49,    51,    52,    53,    47,    26,    27,    28,
      51,    52,    53,    44,    26,    27,    28,    26,    27,    28,
      51,    52,    53,    49,    44,    13,    49,    46,    21,    45,
      38,    49,    51,    52,    53,    47,    29,    30,    13,    51,
      52,    53,    51,    52,    53,    13,    13,    32,    41,    16,
      17,    13,    48,    20,    16,    17,    13,    24,    45,    16,
      17,    44,    24,    25,    31,    46,    18,    24,    13,    31,
      44,    13,    18,    34,    31,    47,    13,    46,    17,    45,
      44,    39,    20,    63,    95,    45,   122,   126
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    55,    13,     0,    44,    56,    59,    60,    57,
      12,    14,    15,    37,    61,    62,    65,    66,    68,    45,
      44,    13,    67,    67,     4,    58,    69,    70,     6,     8,
       9,    40,    63,    64,    62,    48,    13,    19,    78,    44,
      46,     5,    13,    71,    79,    59,    46,    49,    72,    13,
      16,    17,    20,    24,    31,    80,    81,    83,    85,    86,
      87,    89,    92,    68,    63,    35,    36,    73,    74,    77,
      18,    44,    45,    49,    93,    49,    49,     5,     6,     7,
       8,     9,    10,    11,    13,    23,    40,    49,    95,    97,
      99,   101,    95,    78,    47,    44,    50,    37,    65,    75,
      95,    95,    94,    95,    44,    84,    95,    13,    82,    49,
      49,    45,   101,   101,    95,    26,    27,    28,    51,    52,
      53,    88,    96,    22,    39,    40,    98,    21,    29,    30,
      41,   100,    90,    38,    74,    13,    13,    76,    44,    46,
      47,    48,    50,    48,    50,    48,    50,    95,    95,    95,
      50,    79,    97,    99,   101,    32,    65,    45,    48,    46,
      18,    95,    95,    44,    13,    44,    50,    50,    47,    25,
      79,    63,    13,    95,    95,    33,    91,    47,    47,    44,
      79,    34,    18,    13,    45,    95,    46,    46,    95,    47,
      44
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1464 of yacc.c  */
#line 146 "pascual1.y"
    {
		lend = newlabel();
		//P2: Inicializamos las direcciones para las variables y parametros
		sig[nivel] = 3;
		nivel = 0;
		tabs = 0;
		inicializar_tabla (tabsim);
		introducir_programa(tabsim, (yyvsp[(2) - (3)].identificador).nombre, "P");
		if(xml) fprintf(fxml, "<Programa name=\"%s\">\n", (yyvsp[(2) - (3)].identificador).nombre);
		tabs++;
    }
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 158 "pascual1.y"
    {
			if(xml) ptabs(tabs);
			if(xml) fprintf(fxml, "<declaracion_acciones>\n");
			tabs++;
	}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 164 "pascual1.y"
    {
			tabs--;
			if(xml) ptabs(tabs);
			if(xml) fprintf(fxml, "</declaracion_acciones>\n");
	}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 170 "pascual1.y"
    {
		if(muestra) mostrar_tabla(tabsim);
		eliminar_variables (tabsim, nivel);
		eliminar_acciones (tabsim, nivel);
		--nivel;
		if(xml) fprintf(fxml, "</Programa>\n");
		
		//EMIT
		char *lenp = newlabel();
		(yyval.cod) = code(ENP, lenp);
		
		//ACCIONES
		concatenar(&(yyval.cod), (yyvsp[(7) - (9)].cod));
		
		//PROGRAMA
		sprintf(msg, "Inicio %s", "P");
		comment(&((yyval.cod)), msg);
		label(&((yyval.cod)), lenp);
		
		//INSTRUCCIONES
		concatenar(&((yyval.cod)), (yyvsp[(9) - (9)].cod));
		sprintf(msg, "Fin de %s", "P");
		comment(&((yyval.cod)), msg);
		
		//FIN
		label(&(yyval.cod), lend);
		emit(&((yyval.cod)),LVP);
		
		dumpcode((yyval.cod),yyout);
		xmldumpcode((yyval.cod), fcompilado);
    }
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 205 "pascual1.y"
    {
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "<declaracion_variables>\n");
                tabs++;
        }
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 210 "pascual1.y"
    {
                tabs--;
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "</declaracion_variables>\n");
        }
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 232 "pascual1.y"
    {
                if((yyvsp[(1) - (2)].constante) == 0)
                        (yyval.indice_vector).extremo = -(yyvsp[(2) - (2)].constante);
                else
                        (yyval.indice_vector).extremo = (yyvsp[(2) - (2)].constante);
                (yyval.indice_vector).tipo = ENTERO;
        }
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 240 "pascual1.y"
    {
                (yyval.indice_vector).extremo = 1;
                (yyval.indice_vector).tipo = BOOLEANO;
        }
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 245 "pascual1.y"
    {
                (yyval.indice_vector).extremo = 0;
                (yyval.indice_vector).tipo = BOOLEANO;
        }
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 250 "pascual1.y"
    {
                (yyval.indice_vector).extremo = (int)(yyvsp[(1) - (1)].constante);
                (yyval.indice_vector).tipo = CHAR;
        }
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 258 "pascual1.y"
    {(yyval.constante) = 0; }
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 259 "pascual1.y"
    {(yyval.constante) = 1;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 266 "pascual1.y"
    {
                (yyval.control_tipo).tipo_variable = ENTERO;
                (yyval.control_tipo).es_vector = 0;
        }
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 271 "pascual1.y"
    {
                (yyval.control_tipo).tipo_variable = BOOLEANO;
                (yyval.control_tipo).es_vector = 0;
        }
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 276 "pascual1.y"
    {
                (yyval.control_tipo).tipo_variable = CHAR;
                (yyval.control_tipo).es_vector = 0;
        }
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 285 "pascual1.y"
    {
                if((yyvsp[(3) - (9)].indice_vector).tipo != (yyvsp[(6) - (9)].indice_vector).tipo){
                        error_semantico("Los índices son de distinto tipo");
                }
                if((yyvsp[(3) - (9)].indice_vector).extremo >= (yyvsp[(6) - (9)].indice_vector).extremo){
                        error_semantico("Los índices del vector deben declararse de menor a mayor");
                }
                if((yyvsp[(3) - (9)].indice_vector).tipo == 3){
                        if((yyvsp[(3) - (9)].indice_vector).extremo < 32 || (yyvsp[(6) - (9)].indice_vector).extremo > 126){
                                error_semantico("Los índices del vector deben ser un caracter imprimible ASCII");
                        }
                }/*if($<indice_vector>3.tipo != $<control_tipo>9.tipo_variable){
                        error_semantico("Los índices y el tipo de las variables no coinciden");
                }*/
                (yyval.control_tipo).es_vector = 1;
                (yyval.control_tipo).extremo1 = (yyvsp[(3) - (9)].indice_vector).extremo;
                (yyval.control_tipo).extremo2 = (yyvsp[(6) - (9)].indice_vector).extremo;
                (yyval.control_tipo).tipo_extremo = (yyvsp[(3) - (9)].indice_vector).tipo;
                (yyval.control_tipo).tipo_variable = (yyvsp[(9) - (9)].control_tipo).tipo_variable;
        }
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 314 "pascual1.y"
    { 
                //INSERCIÓN DE LA VARIABLE
                
                if((yyvsp[(1) - (1)].identificador).simbolo == NULL || (yyvsp[(1) - (1)].identificador).simbolo->nivel != nivel){ //El símbolo no existe o el nivel es distinto
                        if((yyvsp[(0) - (1)].control_tipo).es_vector == 0){
                                SIMBOLO *s = introducir_variable(tabsim, (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable, nivel, sig[nivel]);
                                s->es_vector = 0;
                                s->asignado = 0;
                                
								//P2: Aumentamos el sig
								sig[nivel]++;
								
								if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"%s\">\n", (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable == 1 ? "entero" : (yyvsp[(0) - (1)].control_tipo).tipo_variable == 2 ? "booleano" : "caracter");
                        }else{ //Se trata de un vector
                                SIMBOLO *s = introducir_variable_vector(tabsim, (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable, nivel, sig[nivel], (yyvsp[(0) - (1)].control_tipo).extremo1, (yyvsp[(0) - (1)].control_tipo).extremo2, (yyvsp[(0) - (1)].control_tipo).tipo_extremo);
                                s->es_vector = 1;
                                s->asignado = 1;
								sig[nivel] = sig[nivel] + ((yyvsp[(0) - (1)].control_tipo).extremo2 - (yyvsp[(0) - (1)].control_tipo).extremo1)+1;
                                //s->componenteVector = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"vector\" valores=\"%s\" inf=\"%d\" sup=\"%d\">\n", (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable == 1 ? "entero" : (yyvsp[(0) - (1)].control_tipo).tipo_variable == 2 ? "booleano" : "caracter", (yyvsp[(0) - (1)].control_tipo).extremo1, (yyvsp[(0) - (1)].control_tipo).extremo2);
                        }
                }
                else{
                        error_semantico("El simbolo ya se ha declarado en este nivel");
                }
         }
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 343 "pascual1.y"
    { 
                //INSERCIÓN DE LA VARIABLE
                if((yyvsp[(3) - (3)].identificador).simbolo == NULL || (yyvsp[(3) - (3)].identificador).simbolo->nivel != nivel){ //El símbolo no existe o el nivel es distinto
                        if((yyvsp[(0) - (3)].control_tipo).es_vector == 0){
                                SIMBOLO *s = introducir_variable(tabsim, (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable, nivel, sig[nivel]);
                                s->es_vector = 0;
                                s->asignado = 0;
								
								//P2: Aumentamos el sig
								sig[nivel]++;
								
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"%s\">\n", (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable == 1 ? "entero" : (yyvsp[(0) - (3)].control_tipo).tipo_variable == 2 ? "booleano" : "caracter");
                        }else{ //Se trata de un vector
                                SIMBOLO *s = introducir_variable_vector(tabsim, (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable, nivel, sig[nivel], (yyvsp[(0) - (3)].control_tipo).extremo1, (yyvsp[(0) - (3)].control_tipo).extremo2, (yyvsp[(0) - (3)].control_tipo).tipo_extremo);
                                s->es_vector = 1;
                                s->asignado = 1;
								sig[nivel] = sig[nivel] + ((yyvsp[(0) - (3)].control_tipo).extremo2 - (yyvsp[(0) - (3)].control_tipo).extremo1)+1;
                                //s->componenteVector = 0;
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<var nombre=\"%s\" tipo=\"vector\" valores=\"%s\" inf=\"%d\" sup=\"%d\">\n", (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable == 1 ? "entero" : (yyvsp[(0) - (3)].control_tipo).tipo_variable == 2 ? "booleano" : "caracter", (yyvsp[(0) - (3)].control_tipo).extremo1, (yyvsp[(0) - (3)].control_tipo).extremo2);
                        }
                }
                else{
                        error_semantico("El simbolo ya se ha declarado en este nivel");
                }
        }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 375 "pascual1.y"
    {
			(yyval.cod) = (yyvsp[(1) - (2)].cod);
			concatenar(&(yyval.cod), (yyvsp[(2) - (2)].cod));
		}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 380 "pascual1.y"
    {
			(yyval.cod) = newcode();
		}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 391 "pascual1.y"
    {
                cerrar_bloque();
                tabs--;
                if(xml) ptabs(tabs);
                if(xml) fprintf(fxml, "</accion>\n");
				
				//EMIT
				(yyval.cod) = newcode();
				
				//Cabecera
				concatenar(&(yyval.cod), (yyvsp[(1) - (5)].cod));
				
				//Acciones
				concatenar(&(yyval.cod), (yyvsp[(4) - (5)].cod));
				
				//Cuerpo
				concatenar(&(yyval.cod), (yyvsp[(5) - (5)].cod));
				
				//Fin
				emit(&(yyval.cod), CSF);
         }
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 417 "pascual1.y"
    {
                if((yyvsp[(2) - (2)].identificador).simbolo == NULL){
                        if(((yyvsp[(2) - (2)].identificador).simbolo = introducir_accion(tabsim, (yyvsp[(2) - (2)].identificador).nombre, nivel, (yyvsp[(2) - (2)].identificador).nombre)) == NULL){    
								error_semantico("El identificador de la acción está duplicado");
                        }else{
                                if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<accion nombre=\"%s\">\n", (yyvsp[(2) - (2)].identificador).nombre);
                                tabs++;
                        }       
                }else{
                        error_semantico("El identificador de la acción está duplicado");
                }
                abrir_bloque();
				sig[nivel] = 3;
         }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 433 "pascual1.y"
    {
                if((yyvsp[(2) - (4)].identificador).simbolo != NULL){
                        (yyvsp[(2) - (4)].identificador).simbolo->parametros = (yyvsp[(4) - (4)].lista);
                }
				
				//EMIT
				(yyval.cod) = newcode();
				sprintf(msg, "Acción %s", (yyvsp[(2) - (4)].identificador).simbolo->nombre);
				comment(&(yyval.cod), msg);
				
				//Label
				label(&(yyval.cod), (yyvsp[(2) - (4)].identificador).simbolo->nombre);
				
				//Parámetros
				int i;
				for(i=0;i<longitud_lista((yyvsp[(4) - (4)].lista));i++){
					emit(&(yyval.cod), SRF, 0, 2+longitud_lista((yyvsp[(4) - (4)].lista))-i);
					emit(&(yyval.cod), ASGI);
				}
				
				//Cuerpo
				char *laccion = newlabel();
				emit(&(yyval.cod), JMP, laccion);
				label(&(yyval.cod), laccion);
         }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 461 "pascual1.y"
    {
                crear_vacia(&(yyval.lista));
        }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 465 "pascual1.y"
    {
                (yyval.lista) = (yyvsp[(2) - (3)].lista);
        }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 473 "pascual1.y"
    {
                concatenar(&(yyvsp[(1) - (3)].lista), (yyvsp[(3) - (3)].lista));
                (yyval.lista) = (yyvsp[(1) - (3)].lista);
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 478 "pascual1.y"
    {
                (yyval.lista) = (yyvsp[(1) - (1)].lista);
        }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 482 "pascual1.y"
    {
                crear_vacia(&(yyval.lista));
        }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 491 "pascual1.y"
    {
                (yyval.lista) = (yyvsp[(2) - (2)].lista);
         }
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 498 "pascual1.y"
    {
                //Subimos la lista
                (yyval.lista) = (yyvsp[(2) - (2)].lista);
        }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 503 "pascual1.y"
    {
        
        }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 513 "pascual1.y"
    {
                //Vamos a crear una lista para controlar los parámetros
                crear_vacia(&(yyval.lista));
                if((yyvsp[(1) - (1)].identificador).simbolo == NULL || (yyvsp[(1) - (1)].identificador).simbolo->nivel != nivel){
                        SIMBOLO *p = introducir_parametro(tabsim, (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable, (yyvsp[(-1) - (1)].clase_parametro), nivel, sig[nivel]);
                        p->parametro = (yyvsp[(-1) - (1)].clase_parametro);
						p->es_vector = 0;
                        if(xml) ptabs(tabs);
                        if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable == ENTERO ? "entero" : (yyvsp[(0) - (1)].control_tipo).tipo_variable == BOOLEANO ? "booleano" : "caracter", (yyvsp[(-1) - (1)].clase_parametro) == VAL ? "val" : "ref");
                        
                        //Lo añadimos a la lista
                        anadir_derecha(p, &(yyval.lista));
						sig[nivel]++;
                }else{
                        
                        if((yyvsp[(1) - (1)].identificador).simbolo->es_vector){
                                error_semantico("No se permite el paso de un vector como parámetro");
                        }else if((yyvsp[(1) - (1)].identificador).simbolo->nivel == nivel){
							error_semantico("El nombre del parámetro está duplicado");
						}else{
                                SIMBOLO *p = introducir_parametro(tabsim, (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable, (yyvsp[(-1) - (1)].clase_parametro), nivel, sig[nivel]);
                                p->es_vector = 0;
                                p->parametro = (yyvsp[(-1) - (1)].clase_parametro);
								if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", (yyvsp[(1) - (1)].identificador).nombre, (yyvsp[(0) - (1)].control_tipo).tipo_variable == ENTERO ? "entero" : (yyvsp[(0) - (1)].control_tipo).tipo_variable == BOOLEANO ? "booleano" : "caracter", (yyvsp[(-1) - (1)].clase_parametro) == VAL ? "val" : "ref");
                                anadir_derecha(p, &(yyval.lista));
								sig[nivel]++;
                        }
                }
        }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 544 "pascual1.y"
    {
                //Parecido a la versión de un único identificador
                if((yyvsp[(3) - (3)].identificador).simbolo == NULL){
                        SIMBOLO *p = introducir_parametro(tabsim, (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable, (yyvsp[(-1) - (3)].clase_parametro), nivel, sig[nivel]);
                        p->parametro = (yyvsp[(-1) - (3)].clase_parametro);
						if(xml) ptabs(tabs);
                        if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable == ENTERO ? "entero" : (yyvsp[(0) - (3)].control_tipo).tipo_variable == BOOLEANO ? "booleano" : "caracter", (yyvsp[(-1) - (3)].clase_parametro) == VAL ? "val" : "ref");
                        
                        //Lo añadimos a la lista
                        anadir_derecha(p, &(yyvsp[(1) - (3)].lista));
						sig[nivel]++;
                }else{
                        //El símbolo existe así que comprobamos el tipo
                        if((yyvsp[(3) - (3)].identificador).simbolo->es_vector){
                                error_semantico("No se permite el paso de un vector como parámetro");
                        }else if((yyvsp[(3) - (3)].identificador).simbolo->nivel == nivel){
							error_semantico("El nombre del parámetro está duplicado");
						}else{
                                SIMBOLO *p = introducir_parametro(tabsim, (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable, (yyvsp[(-1) - (3)].clase_parametro), nivel, sig[nivel]);
                                p->parametro = (yyvsp[(-1) - (3)].clase_parametro);
								if(xml) ptabs(tabs);
                                if(xml) fprintf(fxml, "<parametro nombre=\"%s\" tipo=\"%s\" paso=\"%s\" />\n", (yyvsp[(3) - (3)].identificador).nombre, (yyvsp[(0) - (3)].control_tipo).tipo_variable == ENTERO ? "entero" : (yyvsp[(0) - (3)].control_tipo).tipo_variable == BOOLEANO ? "booleano" : "caracter", (yyvsp[(-1) - (3)].clase_parametro) == VAL ? "val" : "ref");
                                anadir_derecha(p, &(yyvsp[(1) - (3)].lista));
								sig[nivel]++;
                        }
                }
                //Subimos la lista
                (yyval.lista)=(yyvsp[(1) - (3)].lista);
        }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 577 "pascual1.y"
    {
                (yyval.clase_parametro) = VAL;
         }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 581 "pascual1.y"
    {
                (yyval.clase_parametro) = REF;
        }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 588 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(2) - (3)].cod);
	}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 596 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (2)].cod);
		concatenar(&(yyval.cod), (yyvsp[(2) - (2)].cod));
	}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 601 "pascual1.y"
    {
		(yyval.cod) = newcode();
	}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 609 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 613 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 617 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 621 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 625 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 629 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 633 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(1) - (1)].cod);
	}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 641 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(3) - (5)].cod);
	}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 648 "pascual1.y"
    {
		crear_vacia(&(yyval.cod));
		if((yyvsp[(1) - (1)].identificador).simbolo == NULL){
			error_semantico("El identificador no está declarado");
		}else if((yyvsp[(1) - (1)].identificador).simbolo->nivel > nivel){
			error_semantico("El identificador no es accesible");
		}else if((yyvsp[(1) - (1)].identificador).simbolo->tipo != PARAMETRO && (yyvsp[(1) - (1)].identificador).simbolo->tipo != VARIABLE){
			error_semantico("El identificador no es un parámetro o una variable");
		}else if((yyvsp[(1) - (1)].identificador).simbolo->tipo == PARAMETRO && (yyvsp[(1) - (1)].identificador).simbolo->parametro == VAL){
			error_semantico("No se puede asignara un parámetro por VALOR");
		}else{ //P2: EMIT
			emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (1)].identificador).simbolo->nivel, (yyvsp[(1) - (1)].identificador).simbolo->dir);
			if((yyvsp[(1) - (1)].identificador).simbolo->tipo == PARAMETRO && (yyvsp[(1) - (1)].identificador).simbolo->parametro == REF){
				//Parametro REF
				emit(&(yyval.cod), DRF);
			}
			if((yyvsp[(1) - (1)].identificador).simbolo->variable == CHAR){
				//CHAR
				emit(&(yyval.cod), RD, 0);
			}else{
				//ENTERO o BOOL
				emit(&(yyval.cod), RD, 1);
			}
		}
	}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 674 "pascual1.y"
    {
		crear_vacia(&(yyval.cod));
		concatenar(&(yyval.cod), (yyvsp[(1) - (3)].cod));
		if((yyvsp[(3) - (3)].identificador).simbolo == NULL){
			error_semantico("El identificador no está declarado");
		}else if((yyvsp[(3) - (3)].identificador).simbolo->nivel > nivel){
			error_semantico("El identificador no es accesible");
		}else if((yyvsp[(3) - (3)].identificador).simbolo->tipo != PARAMETRO && (yyvsp[(3) - (3)].identificador).simbolo->tipo != VARIABLE){
			error_semantico("El identificador no es un parámetro o una variable");
		}else if((yyvsp[(3) - (3)].identificador).simbolo->tipo == PARAMETRO && (yyvsp[(3) - (3)].identificador).simbolo->parametro == VAL){
			error_semantico("No se puede asignar a un parámetro por VALOR");
		}else{ //P2: EMIT
			emit(&(yyval.cod), SRF, nivel-(yyvsp[(3) - (3)].identificador).simbolo->nivel, (yyvsp[(3) - (3)].identificador).simbolo->dir);
			if((yyvsp[(3) - (3)].identificador).simbolo->tipo == PARAMETRO && (yyvsp[(3) - (3)].identificador).simbolo->parametro == REF){
				//Parametro REF
				emit(&(yyval.cod), DRF);
			}
			if((yyvsp[(3) - (3)].identificador).simbolo->variable == CHAR){
				//CHAR
				emit(&(yyval.cod), RD, 0);
			}else{
				//ENTERO o BOOL
				emit(&(yyval.cod), RD, 1);
			}
		}
	}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 706 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(3) - (5)].cod);
	}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 715 "pascual1.y"
    {
		concatenar(&(yyval.cod), (yyvsp[(3) - (3)].expresion).cod);
		if((yyvsp[(3) - (3)].expresion).tipo_var == BOOLEANO){
			error_semantico("No se puede escribir un BOOLEANO");
		}else{ //P2: EMIT
			(yyval.cod) = (yyvsp[(1) - (3)].cod);
			concatenar(&(yyval.cod), (yyvsp[(3) - (3)].expresion).cod);
			
			if((yyvsp[(3) - (3)].expresion).tipo_var == ENTERO){
				emit(&(yyval.cod), WRT, 1);
			}else if((yyvsp[(3) - (3)].expresion).tipo_var == CHAR){
				emit(&(yyval.cod), WRT, 0);
			}
		}
	}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 731 "pascual1.y"
    {
		crear_vacia(&(yyval.cod));
		concatenar(&(yyval.cod), (yyvsp[(1) - (1)].expresion).cod);
		if((yyvsp[(1) - (1)].expresion).tipo_var == BOOLEANO){
			error_semantico("No se puede escribir un BOOLEANO");
		}else{ //P2: EMIT
			(yyval.cod) = (yyvsp[(1) - (1)].expresion).cod;
			
			if((yyvsp[(1) - (1)].expresion).tipo_var == ENTERO){
				emit(&(yyval.cod), WRT, 1);
			}else if((yyvsp[(1) - (1)].expresion).tipo_var == CHAR){
				emit(&(yyval.cod), WRT, 0);
			}
		}
	}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 754 "pascual1.y"
    {
                if((yyvsp[(1) - (4)].identificador).simbolo == NULL){
                        error_semantico("El identificador no está declarado");
                }else if((yyvsp[(1) - (4)].identificador).simbolo->nivel > nivel){
                        error_semantico("El identificador no es accesible");
                }else if((yyvsp[(1) - (4)].identificador).simbolo->tipo != VARIABLE && (yyvsp[(1) - (4)].identificador).simbolo->tipo != PARAMETRO){
                        error_semantico("El identificador no es una variable o un parámetro");
                }else if((yyvsp[(1) - (4)].identificador).simbolo->tipo == PARAMETRO && (yyvsp[(1) - (4)].identificador).simbolo->parametro == VAL){
                        error_semantico("No se puede asignar un valor a un parámetro pasado por VALOR");
                }else if((yyvsp[(1) - (4)].identificador).simbolo->variable != (yyvsp[(3) - (4)].expresion).tipo_var){
                        error_semantico("Los tipos asignados no coinciden");
                }else if((yyvsp[(3) - (4)].expresion).simbolo != NULL && (yyvsp[(3) - (4)].expresion).simbolo->es_vector == 1 && (yyvsp[(1) - (4)].identificador).simbolo->es_vector == 0){
					error_semantico("No se puede asignar un vector a un identificador");
				}else if((yyvsp[(3) - (4)].expresion).tipo_var == CADENA){ 
                        error_semantico("El tipo cadena no está permitido");
                }else if((yyvsp[(1) - (4)].identificador).simbolo->es_vector == 1){//Si el símbolo es vector la asignación del vector deberá ser completa
                        if((yyvsp[(3) - (4)].expresion).simbolo == NULL){
                                error_semantico("El identificador asignado no es válido");
                        }else if((yyvsp[(1) - (4)].identificador).simbolo->es_vector != (yyvsp[(3) - (4)].expresion).simbolo->es_vector){ 
                                error_semantico("Los identificadores asignados no son vectores");
                        }else if((yyvsp[(3) - (4)].expresion).simbolo == NULL){
                                error_semantico("La asignación del vector debe ser completa");
                        }else{
                                //Comprobamos el tamaño de los vectores asignados.
                                //Tiene que ser el mismo
                                int size1 = (yyvsp[(1) - (4)].identificador).simbolo->extremo2 - (yyvsp[(1) - (4)].identificador).simbolo->extremo1;
                                int size2 = (yyvsp[(3) - (4)].expresion).simbolo->extremo2 - (yyvsp[(3) - (4)].expresion).simbolo->extremo1;
                                if(size1 != size2){
                                        error_semantico("El tamaño de los vectores es distinto");
                                }else{
									int i;
									(yyval.cod) = newcode();
									for(i=0; i<size1+1;i++){
										emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (4)].identificador).simbolo->nivel, (yyvsp[(1) - (4)].identificador).simbolo->dir+i);
									}
									for(i=0;i<size1+1;i++){
										emit(&(yyval.cod), SRF, nivel-(yyvsp[(3) - (4)].expresion).simbolo->nivel, (yyvsp[(3) - (4)].expresion).simbolo->dir+size1-i);
										emit(&(yyval.cod), DRF);
										emit(&(yyval.cod), ASG);
									}
								}
                        }
                }else{
					(yyvsp[(1) - (4)].identificador).simbolo->valor = (yyvsp[(3) - (4)].expresion).valor;
					(yyvsp[(1) - (4)].identificador).simbolo->asignado = 1;
					
					//EMIT
					(yyval.cod) = code(SRF, nivel-(yyvsp[(1) - (4)].identificador).simbolo->nivel, (yyvsp[(1) - (4)].identificador).simbolo->dir);
					if((yyvsp[(1) - (4)].identificador).simbolo->parametro == REF){
						emit(&(yyval.cod), DRF);
					}
					concatenar(&(yyval.cod), (yyvsp[(3) - (4)].expresion).cod);
					emit(&(yyval.cod), ASG);
                }
         }
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 815 "pascual1.y"
    {
                if((yyvsp[(1) - (7)].identificador).simbolo == NULL){
                        error_semantico("El símbolo NO está declarado");
                }else if(!(yyvsp[(1) - (7)].identificador).simbolo->es_vector){
                        error_semantico("El tipo del símbolo NO es un vector");
                }else if((yyvsp[(1) - (7)].identificador).simbolo->nivel > nivel){
                        error_semantico("La símbolo no es accesible");
                }else if(!ES_VARIABLE(*(yyvsp[(1) - (7)].identificador).simbolo)){
                        error_semantico("El identificador debe ser una variable");
                }else if((yyvsp[(6) - (7)].expresion).tipo_var == CADENA){
                        error_semantico("El tipo CADENA no es válido");
                }else if((yyvsp[(1) - (7)].identificador).simbolo->variable != (yyvsp[(6) - (7)].expresion).tipo_var){
                        error_semantico("Los tipos asignados deben ser los mismos");
                }else if((yyvsp[(1) - (7)].identificador).simbolo->tipo_extremo != (yyvsp[(3) - (7)].expresion).tipo_var){
                        error_semantico("El tipo del índice no es válido");
                }else if((yyvsp[(3) - (7)].expresion).tiene_valor == 1 && ((yyvsp[(3) - (7)].expresion).valor < (yyvsp[(1) - (7)].identificador).simbolo->extremo1 || (yyvsp[(3) - (7)].expresion).valor > (yyvsp[(1) - (7)].identificador).simbolo->extremo2)){
						error_semantico("El índice está fuera de rango");
				}else{
					(yyval.cod) = newcode();
					LISTA l1;
					asignar(&l1, (yyvsp[(3) - (7)].expresion).cod, sizeof(NODE));
					concatenar(&(yyval.cod), l1);
					emit(&(yyval.cod), STC, (yyvsp[(1) - (7)].identificador).simbolo->extremo1);
					emit(&(yyval.cod), LT);
					LISTA l2;
					asignar(&l2, (yyvsp[(3) - (7)].expresion).cod, sizeof(NODE));
					concatenar(&(yyval.cod), l2);
					emit(&(yyval.cod), STC, (yyvsp[(1) - (7)].identificador).simbolo->extremo2);
					emit(&(yyval.cod), GT);
					emit(&(yyval.cod), OR);
					
					char *lsino = newlabel();
					
					emit(&(yyval.cod), JMF, lsino);
					//INSTR1: NOK
					int i;
					char error[200];
					sprintf(error, "ERROR EN EJECUCION: Acceso fuera de rango");
					for(i=0;i<strlen(error);i++){
						emit(&(yyval.cod), STC, error[i]);
						emit(&(yyval.cod), WRT, 0);
					}
					
					emit(&(yyval.cod), JMP, lend);
					label(&(yyval.cod), lsino);
					
					concatenar(&(yyval.cod), (yyvsp[(3) - (7)].expresion).cod);
					emit(&(yyval.cod), STC, (yyvsp[(1) - (7)].identificador).simbolo->extremo1);
					emit(&(yyval.cod), SBT);
					emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (7)].identificador).simbolo->nivel, (yyvsp[(1) - (7)].identificador).simbolo->dir);
					emit(&(yyval.cod), PLUS);
					concatenar(&(yyval.cod), (yyvsp[(6) - (7)].expresion).cod);
					emit(&(yyval.cod), ASG);
				}
        }
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 871 "pascual1.y"
    {
                if((yyvsp[(1) - (16)].identificador).simbolo == NULL){ //Comprobación de tipos del 1º vector
                        error_semantico("El símbolo de la izquierda NO está declarado");
                }else if(!(yyvsp[(1) - (16)].identificador).simbolo->es_vector){
                        error_semantico("El tipo del símbolo de la izquierda NO es un vector");
                }else if((yyvsp[(1) - (16)].identificador).simbolo->nivel > nivel){
                        error_semantico("La símbolo de la izquierda no es accesible");
                }else if(!ES_VARIABLE(*(yyvsp[(1) - (16)].identificador).simbolo)){
                        error_semantico("El identificador de la izquierda debe ser una variable");
                }else if((yyvsp[(6) - (16)].expresion).tipo_var == CADENA){
                        error_semantico("El tipo CADENA no es válido");
                }else if((yyvsp[(1) - (16)].identificador).simbolo->tipo_extremo != (yyvsp[(3) - (16)].expresion).tipo_var || (yyvsp[(1) - (16)].identificador).simbolo->tipo_extremo != (yyvsp[(6) - (16)].expresion).tipo_var){
                        error_semantico("Los tipos de los índices y el vector de la izda deben ser los mismos");
                }if((yyvsp[(9) - (16)].identificador).simbolo == NULL){ //Comprobación de tipos del 2º vector
                        error_semantico("El símbolo de la derecha NO está declarado");
                }else if(!(yyvsp[(9) - (16)].identificador).simbolo->es_vector){
                        error_semantico("El tipo del símbolo de la derecha NO es un vector");
                }else if((yyvsp[(9) - (16)].identificador).simbolo->nivel > nivel){
                        error_semantico("La símbolo la derecha NO es accesible");
                }else if(!ES_VARIABLE(*(yyvsp[(9) - (16)].identificador).simbolo)){
                        error_semantico("El identificador la derecha debe ser una variable");
                }else if((yyvsp[(6) - (16)].expresion).tipo_var == CADENA){
                        error_semantico("El tipo CADENA no es válido");
                }else if((yyvsp[(9) - (16)].identificador).simbolo->tipo_extremo != (yyvsp[(11) - (16)].expresion).tipo_var || (yyvsp[(9) - (16)].identificador).simbolo->tipo_extremo != (yyvsp[(14) - (16)].expresion).tipo_var){
                        error_semantico("Los tipos de los índices y vector de la derecha deben ser los mismos");
                }else if((yyvsp[(1) - (16)].identificador).simbolo->variable != (yyvsp[(9) - (16)].identificador).simbolo->variable){ //Comprobando la asignación
                        error_semantico("Los tipos de los vectores asignados deben ser iguales");
                }else if(((yyvsp[(3) - (16)].expresion).tiene_valor == 1 && (yyvsp[(6) - (16)].expresion).tiene_valor == 1) && ((yyvsp[(3) - (16)].expresion).valor < (yyvsp[(1) - (16)].identificador).simbolo->extremo1 || (yyvsp[(6) - (16)].expresion).valor > (yyvsp[(1) - (16)].identificador).simbolo->extremo2)){ //Comprobamos que accedemos a un conjunto correcto del vector
						error_semantico("Índice fuera de rango");
                }else if(((yyvsp[(11) - (16)].expresion).tiene_valor == 1 && (yyvsp[(14) - (16)].expresion).tiene_valor == 1) && ((yyvsp[(11) - (16)].expresion).valor < (yyvsp[(9) - (16)].identificador).simbolo->extremo1 || (yyvsp[(14) - (16)].expresion).valor > (yyvsp[(9) - (16)].identificador).simbolo->extremo2)){ //Comprobamos que accedemos a un conjunto correcto del vector
						error_semantico("Índice fuera de rango");
                }else{
                        //Comprobando que el tamaño de los vectores asignados es el mismo
                        int size1 = (yyvsp[(6) - (16)].expresion).valor - (yyvsp[(3) - (16)].expresion).valor;
                        int size2 = (yyvsp[(14) - (16)].expresion).valor - (yyvsp[(11) - (16)].expresion).valor;
                        if(((yyvsp[(3) - (16)].expresion).tiene_valor == 1 && (yyvsp[(6) - (16)].expresion).tiene_valor == 1 && (yyvsp[(11) - (16)].expresion).tiene_valor == 1 && (yyvsp[(14) - (16)].expresion).tiene_valor == 1) && (size1 != size2)){
								error_semantico("Los rangos asignados no tienen el mismo tamaño");
                        }else{
							if((yyvsp[(3) - (16)].expresion).tiene_valor == 1 && (yyvsp[(6) - (16)].expresion).tiene_valor == 1 && (yyvsp[(11) - (16)].expresion).tiene_valor == 1 && (yyvsp[(14) - (16)].expresion).tiene_valor == 1){
								//Los índices tienen valor
								(yyval.cod) = newcode();
								int i;
								for(i=0;i<(yyvsp[(6) - (16)].expresion).valor-(yyvsp[(3) - (16)].expresion).valor+1;i++){ //Recorremos todo el conjunto
									//Componente Vector 1
									emit(&(yyval.cod), STC, (yyvsp[(3) - (16)].expresion).valor+i); //Ref
									emit(&(yyval.cod), STC, (yyvsp[(1) - (16)].identificador).simbolo->extremo1);  //Índice min
									emit(&(yyval.cod), SBT); // Ref de la componente
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, (yyvsp[(1) - (16)].identificador).simbolo->dir); //Dirección símbolo
									emit(&(yyval.cod), PLUS); // Dirección componente
									
									//Valor de la componente 2
									emit(&(yyval.cod), STC, (yyvsp[(11) - (16)].expresion).valor+i);  //Ref
									emit(&(yyval.cod), STC, (yyvsp[(9) - (16)].identificador).simbolo->extremo1);  //Índice min
									emit(&(yyval.cod), SBT); // Ref de la componente
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(9) - (16)].identificador).simbolo->nivel, (yyvsp[(9) - (16)].identificador).simbolo->dir); //Dirección símbolo
									emit(&(yyval.cod), PLUS); // Dirección componente
									emit(&(yyval.cod), DRF);
									
									//Asignación
									emit(&(yyval.cod), ASG);
								}
							}else{
								LISTA laux;
								char *lcond = newlabel();
								char *lbloque = newlabel();
								char *lsino = newlabel();
								char *lfin = newlabel();
								
								//Condición de OK
								asignar(&laux, (yyvsp[(3) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								asignar(&laux, (yyvsp[(6) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								emit(&(yyval.cod), LT);
								asignar(&laux, (yyvsp[(11) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								asignar(&laux, (yyvsp[(14) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								emit(&(yyval.cod), LT);
								emit(&(yyval.cod), AND);
								asignar(&laux, (yyvsp[(3) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								emit(&(yyval.cod), STC, (yyvsp[(1) - (16)].identificador).simbolo->extremo1);
								emit(&(yyval.cod), GTE);
								emit(&(yyval.cod), AND);
								asignar(&laux, (yyvsp[(6) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								emit(&(yyval.cod), STC, (yyvsp[(1) - (16)].identificador).simbolo->extremo2);
								emit(&(yyval.cod), LTE);
								emit(&(yyval.cod), AND);
								asignar(&laux, (yyvsp[(11) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								emit(&(yyval.cod), STC, (yyvsp[(9) - (16)].identificador).simbolo->extremo1);
								emit(&(yyval.cod), GTE);
								emit(&(yyval.cod), AND);
								asignar(&laux, (yyvsp[(14) - (16)].expresion).cod, sizeof(NODE));
								concatenar(&(yyval.cod), laux);
								emit(&(yyval.cod), STC, (yyvsp[(9) - (16)].identificador).simbolo->extremo2);
								emit(&(yyval.cod), LTE);
								emit(&(yyval.cod), AND);
								
								emit(&(yyval.cod), JMF, lsino);
								
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, 999);
									emit(&(yyval.cod), STC, 0);
									emit(&(yyval.cod), ASG);
									
									emit(&(yyval.cod), JMP, lcond);
									label(&(yyval.cod), lbloque);
									
									//-->BLOQUE
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, 999);
									emit(&(yyval.cod), DRF);
									asignar(&laux, (yyvsp[(3) - (16)].expresion).cod, sizeof(NODE));
									concatenar(&(yyval.cod), laux);
									emit(&(yyval.cod), PLUS);
									emit(&(yyval.cod), STC, (yyvsp[(1) - (16)].identificador).simbolo->extremo1);  //Índice min
									emit(&(yyval.cod), SBT); // Ref de la componente
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, (yyvsp[(1) - (16)].identificador).simbolo->dir); //Dirección símbolo
									emit(&(yyval.cod), PLUS); // Dirección componente
									
									//Valor de la componente 2
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, 999);
									emit(&(yyval.cod), DRF);
									asignar(&laux, (yyvsp[(11) - (16)].expresion).cod, sizeof(NODE));
									concatenar(&(yyval.cod), laux);
									emit(&(yyval.cod), PLUS);
									emit(&(yyval.cod), STC, (yyvsp[(9) - (16)].identificador).simbolo->extremo1);  //Índice min
									emit(&(yyval.cod), SBT); // Ref de la componente
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(9) - (16)].identificador).simbolo->nivel, (yyvsp[(9) - (16)].identificador).simbolo->dir); //Dirección símbolo
									emit(&(yyval.cod), PLUS); // Dirección componente
									emit(&(yyval.cod), DRF);
									
									//Asignación
									emit(&(yyval.cod), ASG);
									
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, 999);
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, 999);
									emit(&(yyval.cod), DRF);
									emit(&(yyval.cod), STC, 1);
									emit(&(yyval.cod), PLUS);
									emit(&(yyval.cod), ASG);
									//BLOQUE<--
									
									label(&(yyval.cod), lcond);
									//-->COND
									emit(&(yyval.cod), SRF, nivel-(yyvsp[(1) - (16)].identificador).simbolo->nivel, 999);
									emit(&(yyval.cod), DRF);
									asignar(&laux, (yyvsp[(6) - (16)].expresion).cod, sizeof(NODE));
									concatenar(&(yyval.cod), laux);
									asignar(&laux, (yyvsp[(3) - (16)].expresion).cod, sizeof(NODE));
									concatenar(&(yyval.cod), laux);
									emit(&(yyval.cod), SBT);
									emit(&(yyval.cod), LTE);
									//COND<--
									
									emit(&(yyval.cod), JMT, lbloque);
									
								emit(&(yyval.cod), JMP, lfin);
								
								label(&(yyval.cod), lsino);
									int i;
									char error[200];
									sprintf(error, "ERROR EN EJECUCION: Los rangos no están correctamente definidos");
									for(i=0;i<strlen(error);i++){
										emit(&(yyval.cod), STC, error[i]);
										emit(&(yyval.cod), WRT, 0);
									}
									emit(&(yyval.cod), JMP, lend);
									
								label(&(yyval.cod), lfin);
								
							}
						}
						
                }
        }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 1054 "pascual1.y"
    {
                if((yyvsp[(2) - (2)].expresion).tipo_var != BOOLEANO){
                        error_semantico("El tipo de la condición debe ser BOOLEANO");
                }
        }
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 1061 "pascual1.y"
    {
		char *lcond = newlabel();
		char *lbloque = newlabel();
		
		(yyval.cod) = code(JMP, lcond);
		label(&(yyval.cod), lbloque);
		concatenar(&(yyval.cod), (yyvsp[(4) - (5)].cod));
		label(&(yyval.cod), lcond);
		concatenar(&(yyval.cod), (yyvsp[(2) - (5)].expresion).cod);
		emit(&(yyval.cod), JMT, lbloque);
	}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 1078 "pascual1.y"
    {
                if((yyvsp[(2) - (2)].expresion).tipo_var != BOOLEANO){
                        error_semantico("El tipo de la condición debe ser BOOLEANO");
                }
        }
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 1087 "pascual1.y"
    {
		char *lsino = newlabel();
		char *lfin = newlabel();
		
		(yyval.cod) = (yyvsp[(2) - (7)].expresion).cod;
		emit(&(yyval.cod), JMF, lsino);
		concatenar(&(yyval.cod), (yyvsp[(5) - (7)].cod));
		if(longitud_lista((yyvsp[(6) - (7)].cod)) > 0){
			emit(&(yyval.cod), JMP, lfin);
			label(&(yyval.cod), lsino);
			concatenar(&(yyval.cod), (yyvsp[(6) - (7)].cod));
			label(&(yyval.cod), lfin);
		}else{
			label(&(yyval.cod), lsino);
		}
	}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 1107 "pascual1.y"
    {
		(yyval.cod) = newcode();
	}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 1113 "pascual1.y"
    {
		(yyval.cod) = (yyvsp[(2) - (2)].cod);
	}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 1121 "pascual1.y"
    {
                if((yyvsp[(1) - (3)].identificador).simbolo == NULL){
                        error_semantico("La acción NO está declarada");
                }else if((yyvsp[(1) - (3)].identificador).simbolo->tipo != ACCION){
                        error_semantico("El símbolo no es una ACCIÓN");
                }else if((yyvsp[(1) - (3)].identificador).simbolo->nivel > nivel){
                        error_semantico("La acción no es accesible");
                }else{
                        //Comprobamos los parámetros de invocación
                        
                        if(longitud_lista((yyvsp[(1) - (3)].identificador).simbolo->parametros) != longitud_lista((yyvsp[(2) - (3)].lista))){
                                error_semantico("El número de argumentos no es correcto");
                        }else{
								(yyval.cod) = newcode();
								
                                SIMBOLO *param;
                                EXPRESION *exp;
								
                                int i = 1;
                                while(longitud_lista((yyvsp[(1) - (3)].identificador).simbolo->parametros) >= i){
                                        
                                        //Obtenemos los símbolos
                                        param = observar((yyvsp[(1) - (3)].identificador).simbolo->parametros, i);
                                        exp = observar((yyvsp[(2) - (3)].lista), i);
                                        
                                        if(exp->simbolo != NULL){ //Es un símbolo
												if(exp->simbolo->variable != param->variable){
                                                        error_semantico("El tipo del parámetro no es correcto");
                                                }else if(exp->simbolo->es_vector){
                                                        error_semantico("No se permite el paso de un vector entero");
                                                }else{
													//EMIT
													emit(&(yyval.cod), SRF, nivel-exp->simbolo->nivel, exp->simbolo->dir);
													if(param->parametro == VAL){
														emit(&(yyval.cod), DRF);
													}
												}
                                        }else{ //Es una expresión
                                                if(param->parametro == REF && exp->es_componente != 1){
													error_semantico("Se esperaba un parámetro por REFERENCIA");
                                                }else if(param->variable != exp->tipo_var){
													error_semantico("El tipo del parámetro no es correcto");
												}else{
													concatenar(&(yyval.cod), exp->cod);
													if(exp->es_componente == 1 && param->parametro == REF){
														//Quitamos el DRF
														eliminar_derecha(&(yyval.cod));
														comment(&((yyval.cod)), msg);
													}
												}
                                        }
                                        i++;
                                }
								
								//EMIT
								emit(&(yyval.cod), OSF, sig[nivel], nivel-(yyvsp[(1) - (3)].identificador).simbolo->nivel, (yyvsp[(1) - (3)].identificador).simbolo->etiq);
                        }
                }
         }
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 1181 "pascual1.y"
    {
		if((yyvsp[(1) - (2)].identificador).simbolo == NULL){
				error_semantico("La acción NO está declarada");
		}else if((yyvsp[(1) - (2)].identificador).simbolo->tipo != ACCION){
				error_semantico("El símbolo no es una ACCIÓN");
		}else if((yyvsp[(1) - (2)].identificador).simbolo->nivel > nivel){
				error_semantico("La acción no es accesible");
		}else if(longitud_lista((yyvsp[(1) - (2)].identificador).simbolo->parametros) > 0){
			error_semantico("El número de parámetros no es correcto");
		}else{
			(yyval.cod) = newcode();
			emit(&((yyval.cod)),OSF,sig[nivel],nivel-(yyvsp[(1) - (2)].identificador).simbolo->nivel,(yyvsp[(1) - (2)].identificador).simbolo->etiq);
		}
	}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 1199 "pascual1.y"
    {
                (yyval.lista) = (yyvsp[(2) - (3)].lista);
        }
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 1206 "pascual1.y"
    {
		anadir_derecha_copiando(&(yyvsp[(3) - (3)].expresion), &(yyvsp[(1) - (3)].lista), sizeof(EXPRESION));
		(yyval.lista) = (yyvsp[(1) - (3)].lista);
	}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 1211 "pascual1.y"
    {
		crear_unitaria_copiando(&(yyval.lista), &(yyvsp[(1) - (1)].expresion), sizeof(EXPRESION));
	}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 1218 "pascual1.y"
    {
                (yyval.expresion).tipo_var = (yyvsp[(1) - (1)].expresion).tipo_var;
                (yyval.expresion).simbolo = (yyvsp[(1) - (1)].expresion).simbolo;
                (yyval.expresion).valor = (yyvsp[(1) - (1)].expresion).valor;
				(yyval.expresion).tiene_valor = (yyvsp[(1) - (1)].expresion).tiene_valor;
				
				//EMIT
				(yyval.expresion).cod = (yyvsp[(1) - (1)].expresion).cod;
         }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 1228 "pascual1.y"
    { //Tenemos que controlar los tipos. Similar a la acción operador_multiplicativo
                if((yyvsp[(1) - (3)].expresion).tipo_var != (yyvsp[(3) - (3)].expresion).tipo_var){ //Tipos distintos
                        error_semantico("Los tipos no son compatibles");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == CADENA){
                        error_semantico("Tipo CADENA no permitido");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == BOOLEANO && (yyvsp[(2) - (3)].operador).tipo != BOOLEANO){
                        error_semantico("Operación no permitida con tipo BOOLEANO");
                }else{
                        (yyval.expresion).simbolo = NULL;
						(yyval.expresion).tipo_var = BOOLEANO;
                        
						if((yyvsp[(1) - (3)].expresion).tiene_valor == 1 && (yyvsp[(3) - (3)].expresion).tiene_valor == 1){
							(yyval.expresion).tiene_valor = 1;
							
							//Calculamos el resultado
							if(strcmp((yyvsp[(2) - (3)].operador).op, "=") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor == (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "<") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor < (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, ">") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor > (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, ">=") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor >= (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "<=") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor <= (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "!=") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor != (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else{
									(yyval.expresion).valor = NULL;
									(yyval.expresion).tipo_var = NULL;
							}
						}else{
							(yyval.expresion).tiene_valor = 0;
						}
					//EMIT
					(yyval.expresion).cod = newcode();
					concatenar(&(yyval.expresion).cod, (yyvsp[(1) - (3)].expresion).cod);
					concatenar(&(yyval.expresion).cod, (yyvsp[(3) - (3)].expresion).cod);
					concatenar(&(yyval.expresion).cod, (yyvsp[(2) - (3)].operador).cod);
                }
        }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 1279 "pascual1.y"
    {
                (yyval.operador).tipo = BOOLEANO;
                (yyval.operador).op = "=";
				
				//EMIT
				(yyval.operador).cod = code(EQ);
        }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 1287 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "<";
				
				//EMIT
				(yyval.operador).cod = code(LT);
        }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 1295 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = ">";
				
				//EMIT
				(yyval.operador).cod = code(GT);
        }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 1303 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "<=";
				
				//EMIT
				(yyval.operador).cod = code(LTE);
        }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 1311 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = ">=";
				
				//EMIT
				(yyval.operador).cod = code(GTE);
        }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 1319 "pascual1.y"
    {
                (yyval.operador).tipo = BOOLEANO;
                (yyval.operador).op = "!=";
				
				//EMIT
				(yyval.operador).cod = code(NEQ);
        }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 1330 "pascual1.y"
    {
                (yyval.expresion).tipo_var = (yyvsp[(1) - (1)].expresion).tipo_var;
                (yyval.expresion).simbolo = (yyvsp[(1) - (1)].expresion).simbolo;
                (yyval.expresion).valor = (yyvsp[(1) - (1)].expresion).valor;
				(yyval.expresion).tiene_valor = (yyvsp[(1) - (1)].expresion).tiene_valor;
				
				//EMIT
				(yyval.expresion).cod = (yyvsp[(1) - (1)].expresion).cod;
         }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 1340 "pascual1.y"
    { //Tenemos que controlar los tipos. Similar a la acción operador_multiplicativo
                if((yyvsp[(1) - (3)].expresion).tipo_var != (yyvsp[(3) - (3)].expresion).tipo_var){ //Tipos distintos
                        error_semantico("Los tipos no son compatibles");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == CHAR){
                        error_semantico("Tipo CHAR no permitido");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == CADENA){
                        error_semantico("Tipo CADENA no permitido");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == ENTERO && (yyvsp[(2) - (3)].operador).tipo != ENTERO){
                        error_semantico("Operación no permitida con tipo ENTERO");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == BOOLEANO && (yyvsp[(2) - (3)].operador).tipo != BOOLEANO){
                        error_semantico("Operación no permitida con tipo BOOLEANO");
                }else{
                        (yyval.expresion).tipo_var = (yyvsp[(1) - (3)].expresion).tipo_var;
                        (yyval.expresion).simbolo = NULL;
                        
						if((yyvsp[(1) - (3)].expresion).tiene_valor == 1 && (yyvsp[(3) - (3)].expresion).tiene_valor == 1){
							(yyval.expresion).tiene_valor = 1;
							//Calculamos el resultado
							if(strcmp((yyvsp[(2) - (3)].operador).op, "+") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor + (yyvsp[(3) - (3)].expresion).valor;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "-") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor - (yyvsp[(3) - (3)].expresion).valor;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "or") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor || (yyvsp[(3) - (3)].expresion).valor;
									(yyval.expresion).tipo_var = BOOLEANO;
							}else{
									(yyval.expresion).valor = NULL;
							}
							
							//EMIT
							(yyval.expresion).cod = code(STC, (yyval.expresion).valor);
						}else{
							(yyval.expresion).tiene_valor = 0;
							
							//EMIT: Concatenaaaaarl!!
							(yyval.expresion).cod = newcode();
							concatenar(&(yyval.expresion).cod, (yyvsp[(1) - (3)].expresion).cod);
							concatenar(&(yyval.expresion).cod, (yyvsp[(3) - (3)].expresion).cod);
							concatenar(&(yyval.expresion).cod, (yyvsp[(2) - (3)].operador).cod);
						}
						
                        
                }
        }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 1388 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "+";
				
				//EMIT
				(yyval.operador).cod = code(PLUS);
        }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 1396 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "-";
				
				//EMIT
				(yyval.operador).cod = code(SBT);
        }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 1404 "pascual1.y"
    {
                (yyval.operador).tipo = BOOLEANO;
                (yyval.operador).op = "or";
				
				//EMIT
				(yyval.operador).cod = code(OR);
        }
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 1415 "pascual1.y"
    { //Subimos los datos del factor
                (yyval.expresion).tipo_var = (yyvsp[(1) - (1)].expresion).tipo_var;
                (yyval.expresion).simbolo = (yyvsp[(1) - (1)].expresion).simbolo;
                (yyval.expresion).valor = (yyvsp[(1) - (1)].expresion).valor;
				(yyval.expresion).tiene_valor = (yyvsp[(1) - (1)].expresion).tiene_valor;
				
				//EMIT
				(yyval.expresion).cod = (yyvsp[(1) - (1)].expresion).cod;
         }
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 1425 "pascual1.y"
    { //Tenemos que controlar los tipos
                if((yyvsp[(1) - (3)].expresion).tipo_var != (yyvsp[(3) - (3)].expresion).tipo_var){ //Tipos distintos
                        error_semantico("Los tipos no son compatibles");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == CHAR){
                        error_semantico("Tipo CHAR no permitido");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == CADENA){
                        error_semantico("Tipo CADENA no permitido");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == ENTERO && (yyvsp[(2) - (3)].operador).tipo != ENTERO){
                        error_semantico("Operación no permitida con tipo ENTERO");
                }else if((yyvsp[(1) - (3)].expresion).tipo_var == BOOLEANO && (yyvsp[(2) - (3)].operador).tipo != BOOLEANO){
                        error_semantico("Operación no permitida con tipo BOOLEANO");
                }else{
                        (yyval.expresion).tipo_var = (yyvsp[(1) - (3)].expresion).tipo_var;
                        (yyval.expresion).simbolo = NULL;
						
						if((yyvsp[(1) - (3)].expresion).tiene_valor == 1 && (yyvsp[(3) - (3)].expresion).tiene_valor == 1){
							(yyval.expresion).tiene_valor = 1;
							if(strcmp((yyvsp[(2) - (3)].operador).op, "*") == 0){
                                (yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor * (yyvsp[(3) - (3)].expresion).valor;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "div") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor / (yyvsp[(3) - (3)].expresion).valor;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "mod") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor % (yyvsp[(3) - (3)].expresion).valor;
							}else if(strcmp((yyvsp[(2) - (3)].operador).op, "and") == 0){
									(yyval.expresion).valor = (yyvsp[(1) - (3)].expresion).valor && (yyvsp[(3) - (3)].expresion).valor;
							}else{
									(yyval.expresion).valor = NULL;
							}
							
							//EMIT: Emitimos el valor directamente
							(yyval.expresion).cod = code(STC, (yyval.expresion).valor);
						}else{
							(yyval.expresion).tiene_valor = 0;
							
							//EMIT: No hay valor calculado. Concatenamos
							(yyval.expresion).cod = newcode();
							concatenar(&(yyval.expresion).cod, (yyvsp[(1) - (3)].expresion).cod);
							concatenar(&(yyval.expresion).cod, (yyvsp[(3) - (3)].expresion).cod);
							concatenar(&(yyval.expresion).cod, (yyvsp[(2) - (3)].operador).cod);
						}
                }
        }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 1471 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "*";
				
				//EMIT
				(yyval.operador).cod = code(TMS);
         }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 1479 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "div";
				
				//EMIT
				(yyval.operador).cod = code(DIV);
        }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 1487 "pascual1.y"
    {
                (yyval.operador).tipo = ENTERO;
                (yyval.operador).op = "mod";
				
				//EMIT
				(yyval.operador).cod = code(MOD);
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 1495 "pascual1.y"
    {
                (yyval.operador).tipo = BOOLEANO;
                (yyval.operador).op = "and";
				
				//EMIT
				(yyval.operador).cod = code(AND);
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 1507 "pascual1.y"
    {
                if((yyvsp[(2) - (2)].expresion).tipo_var != ENTERO){ //El tipo no es entero
                        error_semantico("El tipo no es válido. Se esperaba un ENTERO");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else{
                        (yyval.expresion).tipo_var = ENTERO;
                        (yyval.expresion).simbolo = NULL;
                        (yyval.expresion).valor = -(yyvsp[(2) - (2)].expresion).valor;
						(yyval.expresion).tiene_valor = (yyvsp[(2) - (2)].expresion).tiene_valor;
						
						//EMIT
						(yyval.expresion).cod = (yyvsp[(2) - (2)].expresion).cod;
						emit(&(yyval.expresion).cod, NGI);
                }
         }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 1524 "pascual1.y"
    {
                if((yyvsp[(2) - (2)].expresion).tipo_var != BOOLEANO){
                        error_semantico("El tipo no es válido. Se esperaba un BOOLEANO");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else{
                        (yyval.expresion).tipo_var = BOOLEANO;
                        (yyval.expresion).simbolo = NULL;
                        (yyval.expresion).valor = (yyvsp[(2) - (2)].expresion).valor;
						(yyval.expresion).tiene_valor = (yyvsp[(2) - (2)].expresion).tiene_valor;
						
						//EMIT
						(yyval.expresion).cod = (yyvsp[(2) - (2)].expresion).cod;
						emit(&(yyval.expresion).cod, NGB);
                }
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 1541 "pascual1.y"
    {
                (yyval.expresion).tipo_var = (yyvsp[(2) - (3)].expresion).tipo_var;
                (yyval.expresion).simbolo = (yyvsp[(2) - (3)].expresion).simbolo;
                (yyval.expresion).valor = (yyvsp[(2) - (3)].expresion).valor;
				(yyval.expresion).tiene_valor = (yyvsp[(2) - (3)].expresion).tiene_valor;
				
				//EMIT
				(yyval.expresion).cod = (yyvsp[(2) - (3)].expresion).cod;
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 1551 "pascual1.y"
    {
                if((yyvsp[(3) - (4)].expresion).tipo_var != ENTERO){
                        error_semantico("El tipo no es válido. Se esperaba un ENTERO");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else{
                        (yyval.expresion).tipo_var = CHAR;
                        (yyval.expresion).simbolo = NULL;
                        (yyval.expresion).valor = (yyvsp[(3) - (4)].expresion).valor;
						(yyval.expresion).tiene_valor = (yyvsp[(3) - (4)].expresion).tiene_valor;
						
						//EMIT
						(yyval.expresion).cod = (yyvsp[(3) - (4)].expresion).cod;
                }
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 1567 "pascual1.y"
    {
                if((yyvsp[(3) - (4)].expresion).tipo_var != CHAR){
                        error_semantico("El tipo no es válido. Se esperaba un CHAR");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else{
                        (yyval.expresion).tipo_var = ENTERO;
                        (yyval.expresion).simbolo = NULL;
                        (yyval.expresion).valor = (yyvsp[(3) - (4)].expresion).valor;
						(yyval.expresion).tiene_valor = (yyvsp[(3) - (4)].expresion).tiene_valor;
						
						//EMIT
						(yyval.expresion).cod = (yyvsp[(3) - (4)].expresion).cod;
                }
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 1583 "pascual1.y"
    {
                if((yyvsp[(1) - (1)].identificador).simbolo == NULL){ //La variable no existe
                        error_semantico("La variable no está declarada");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else if(nivel < (yyvsp[(1) - (1)].identificador).simbolo->nivel){ //La variable no es visible por el nivel
                        error_semantico("La variable no es accesible por el nivel");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else{ //La variable está en el nivel correcto y existe
                        (yyval.expresion).tipo_var = (yyvsp[(1) - (1)].identificador).simbolo->variable;
                        (yyval.expresion).simbolo = (yyvsp[(1) - (1)].identificador).simbolo;
						(yyval.expresion).tiene_valor = 0;
                        if((yyvsp[(1) - (1)].identificador).simbolo->asignado == 1){
                                (yyval.expresion).valor = (yyvsp[(1) - (1)].identificador).simbolo->valor; //Actualizamos el valor
                        }else{
                                warning("El identificador podría no estar inicializado");
                                (yyval.expresion).valor = NULL;
                        }
						
						//EMIT
						(yyval.expresion).cod = code(SRF, nivel-(yyvsp[(1) - (1)].identificador).simbolo->nivel, (yyvsp[(1) - (1)].identificador).simbolo->dir);
						emit(&(yyval.expresion).cod, DRF);
						if((yyvsp[(1) - (1)].identificador).simbolo->parametro == REF){
							emit(&(yyval.expresion).cod, DRF);
						}
                }
                
        }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 1613 "pascual1.y"
    {
                (yyval.expresion).tipo_var = ENTERO;
                (yyval.expresion).simbolo = NULL;
                (yyval.expresion).valor = yylval.constante;
				(yyval.expresion).tiene_valor = 1;
				
				//EMIT
				(yyval.expresion).cod = code(STC, (yyval.expresion).valor);
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 1623 "pascual1.y"
    {
                (yyval.expresion).tipo_var = CHAR;
                (yyval.expresion).simbolo = NULL;
                (yyval.expresion).valor = yylval.constante;
				(yyval.expresion).tiene_valor = 1;
				
				//EMIT
				(yyval.expresion).cod = code(STC, yylval.constante);
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 1633 "pascual1.y"
    {
                (yyval.expresion).tipo_var = CADENA;
                (yyval.expresion).simbolo = NULL;
				(yyval.expresion).tiene_valor = 0;
				(yyval.expresion).valor_cadena = yylval.cadena;
				
				int i;
				for(i=0;i<strlen((yyvsp[(1) - (1)].cadena));i++){
					emit(&(yyval.expresion).cod, STC, (yyvsp[(1) - (1)].cadena)[i]);
					emit(&(yyval.expresion).cod, WRT, 0);
				}
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 1646 "pascual1.y"
    {
                (yyval.expresion).tipo_var = BOOLEANO;
                (yyval.expresion).simbolo = NULL;
                (yyval.expresion).valor = 1;
				(yyval.expresion).tiene_valor = 1;
				
				//EMIT
				(yyval.expresion).cod = code(STC, 1);
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 1656 "pascual1.y"
    {
                (yyval.expresion).tipo_var = BOOLEANO;
                (yyval.expresion).simbolo = NULL;
                (yyval.expresion).valor = 0;
				(yyval.expresion).tiene_valor = 1;
				
				//EMIT
				(yyval.expresion).cod = code(STC, 0);
        }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 1666 "pascual1.y"
    {
                if((yyvsp[(1) - (4)].identificador).simbolo == NULL){ //La variable no existe
                        error_semantico("La variable no está declarada");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;

                }else if(nivel < (yyvsp[(1) - (4)].identificador).simbolo->nivel){ //La variable no es visible por el nivel
                        error_semantico("La variable no es accesible por el nivel");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else if((yyvsp[(1) - (4)].identificador).simbolo->tipo_extremo != (yyvsp[(3) - (4)].expresion).tipo_var){ //La variable está en el nivel correcto y existe
                        error_semantico("El tipo del índice no es correcto");
                        (yyval.expresion).tipo_var = DESCONOCIDO;
                        (yyval.expresion).simbolo = NULL;
                }else if((yyvsp[(3) - (4)].expresion).tiene_valor == 1 && ((yyvsp[(3) - (4)].expresion).valor < (yyvsp[(1) - (4)].identificador).simbolo->extremo1 || (yyvsp[(3) - (4)].expresion).valor > (yyvsp[(1) - (4)].identificador).simbolo->extremo2)){
					error_semantico("El índice está fuera de rango");
					(yyval.expresion).tipo_var = (yyvsp[(1) - (4)].identificador).simbolo->variable;
					(yyval.expresion).simbolo = NULL;
                }else{
                        (yyval.expresion).tipo_var = (yyvsp[(1) - (4)].identificador).simbolo->variable;
                        //$1.simbolo->componenteVector = 1;
                        (yyval.expresion).simbolo = NULL;
						(yyval.expresion).es_componente = 1;
						(yyval.expresion).tiene_valor = 0;
						
						//EMIT
						(yyval.expresion).cod = newcode();
						LISTA l1;
						asignar(&l1, (yyvsp[(3) - (4)].expresion).cod, sizeof(NODE));
						concatenar(&(yyval.expresion).cod, l1);
						emit(&(yyval.expresion).cod, STC, (yyvsp[(1) - (4)].identificador).simbolo->extremo1);
						emit(&(yyval.expresion).cod, LT);
						LISTA l2;
						asignar(&l2, (yyvsp[(3) - (4)].expresion).cod, sizeof(NODE));
						concatenar(&(yyval.expresion).cod, l2);
						emit(&(yyval.expresion).cod, STC, (yyvsp[(1) - (4)].identificador).simbolo->extremo2);
						emit(&(yyval.expresion).cod, GT);
						emit(&(yyval.expresion).cod, OR);
						
						char *lsino = newlabel();
						
						emit(&(yyval.expresion).cod, JMF, lsino);
						//INSTR1: NOK
						int i;
						char error[200];
						sprintf(error, "ERROR EN EJECUCION: Acceso fuera de rango");
						for(i=0;i<strlen(error);i++){
							emit(&(yyval.expresion).cod, STC, error[i]);
							emit(&(yyval.expresion).cod, WRT, 0);
						}

						
						emit(&(yyval.expresion).cod, JMP, lend);
						label(&(yyval.expresion).cod, lsino);
						//INSTR2: OK
						LISTA l3;
						asignar(&l3, (yyvsp[(3) - (4)].expresion).cod, sizeof(NODE));
						concatenar(&(yyval.expresion).cod, l3);
						emit(&(yyval.expresion).cod, STC, (yyvsp[(1) - (4)].identificador).simbolo->extremo1);
						emit(&(yyval.expresion).cod, SBT);
						emit(&(yyval.expresion).cod, SRF, nivel-(yyvsp[(1) - (4)].identificador).simbolo->nivel, (yyvsp[(1) - (4)].identificador).simbolo->dir);
						emit(&(yyval.expresion).cod, PLUS);
						emit(&(yyval.expresion).cod, DRF);
                }
        }
    break;



/* Line 1464 of yacc.c  */
#line 3602 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 1733 "pascual1.y"


/**********************************************************************/
main(int argc, char *argv[])
/**********************************************************************/
{

    extern FILE *yyin;
    char namein[100], nameout[100];
        nErrores = 0;
        
        if(argc <= 0){
                fprintf(stderr, "Ejecución errónea de pascual.y");
                exit(1);
        }
        
        //Controlamos los warnings
        if(argc == 3){
                if(strcmp(argv[2], "-w") == 0)
                        dar_warnings = 1;
                else{
                        printf("Los parámetros no son correctos: ./pascual.y <fichero> [-w]");
                        exit(1);
                }
        }
        
        //Control de muestra de resultados
        muestra = 0;
        
        //INICIO: XML
        xml = 1;
        if(xml == 1){
                fxml = fopen("resultado.xml", "w");
				fcompilado = fopen("compilado.xml", "w");
                if(fxml == NULL){
                        fprintf(stderr, "El fichero resultado.xml o compilado.xml no ha podido abrirse.\n");
                        exit (1);
                }
        }
        //FIN: XML      
        strcpy (namein, argv[1]);
        strcat (namein, ".pc");
        yyin = fopen (namein, "r");
        if (yyin == NULL) {
           fprintf (stderr, "Fichero %s no existe.\n", namein);
           exit (1);
        }

    yyparse ();

    fclose (yyin);
        fclose(fxml);
        
        //Controlamos si hay errores para borrar el XML
        if(nErrores > 0){
                remove("resultado.xml");
				remove("compilado.xml");
        }
}

/**********************************************************************/
void abrir_bloque()
/**********************************************************************/
{
        nivel++;
}

/**********************************************************************/
void cerrar_bloque()
/**********************************************************************/
{       
        //Añadidas las funciones necesarias para cerrar bloque
        eliminar_variables(tabsim,nivel);
        ocultar_parametros(tabsim,nivel);
        eliminar_acciones(tabsim,nivel);
        eliminar_parametros_ocultos(tabsim,nivel+1);
        nivel--;
}

void ptabs(int i){
        int n;
        for(n=0;n<i;n++)
                fprintf(fxml, "\t");
}
