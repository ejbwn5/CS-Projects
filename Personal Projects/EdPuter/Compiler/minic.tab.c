
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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
#line 21 "minic.y"


#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

void	ignoreComment();
int ckInt();
void prRule(const char*, const char*);
void printTokenInfo(const char* tokenType, 
                    const char* lexeme);

int yyerror(const char*);

extern "C"  // compile these as C, not C++
{
    int yyparse(void);
    int yylex(void);
    int yywrap() {return 1;}
    
}


#define YYMAXDEPTH 100000

#define MAX_INT	"2147483647"

#define OUTPUT_TOKENS	     0	// 0 for no token output
#define OUTPUT_PRODUCTIONS 0	// 0 for no rule output

int lineNum = 1;               	// source line number



typedef struct
{
  string name;
  vector<int> vals;  
} CONSTARR;

typedef struct
{
  string name;
  int value;
} CONSTANT;


typedef struct
{
  string name;
  string size;
} ARRAY;

vector<CONSTANT> consts;
vector<CONSTARR> constArrs;


vector<string> variables;
vector<ARRAY> arrayVariables;

#define INT 0
#define STR 1

int loopcount=0;
int ifcount=0;

typedef struct
{
  int i;
  char* s;    
} VALUES;

typedef struct {
  int type;
  VALUES v;
} TYPE_INFO;


vector<char*> memory;


typedef struct
{  
  string b;
  bool addition;
  
} MATH_OP;







string getIdentifierType(string thing)
{
  for (CONSTANT c : consts)
  {
    if (c.name == thing)
    {
      //its a constant
      return "const";
    }    
  }
  for (string s : variables)
  {
    if (s == thing)
    {
      return "var";
    }
  }
  
  char* p;
  long converted = strtol(thing.c_str(), &p, 10);
  if (!(*p)) 
  {
      return "literal const";
  }
  if (thing=="[void]") return "void";
  
  
  if (thing.find("()") != string::npos)
  {
    //maybe func?
    return "func call";
  }

  if (thing.find("[") != string::npos)
  {    
    //either array or constant array
    
    for (auto c : constArrs)
    {
      if (c.name == thing.substr(0, thing.find("[")))
      {
        return "constarr";
      }      
    }
    //should be regular array
    return "array";
  }

  
  
  cout << thing << "      <---- ??" << endl;
  
  yyerror("Unknown Identifier detected during code generation");
}












string genaddopcode(string ops)
{
  //break down into steps
  
  //cout << ops << endl << "----------------" << endl;;
  
  /*
  char chars[] = "()";
  
  for (unsigned int i = 0; i < strlen(chars); ++i)
  {    
    ops.erase (std::remove(ops.begin(), ops.end(), chars[i]), ops.end());
  }
  */
  
  vector<MATH_OP> operations;
  
  int currPos = 0;
  int lastPos = 0;
  
  string curr = "";
  
  bool firstFound = false;
  
  string first = "";
  
  if (ops[0]=='-')
  {
    
    currPos=1;
    firstFound=true;
    first = "0";
  }
  size_t foundPlus, foundMinus;
  
  do
  { 
    lastPos=currPos;
  
    foundPlus = ops.find("+", currPos);
    foundMinus = ops.find("-", currPos);
    
    if (foundPlus==string::npos && foundMinus!=string::npos) //minus op
    {
      currPos = foundMinus+1;
      
      string term = ops.substr(lastPos, (currPos-lastPos-1));
      //cout << term << endl;
      
      if (!firstFound)
      {
        firstFound=true;
        first = term;
      }
      else 
      {
        //get sign from lastPos-1
        
        MATH_OP op;
        op.b = term;
        op.addition = (ops[lastPos-1]=='+');
        
        operations.push_back(op);
        
      }
      
    }
    else if (foundPlus!=string::npos && foundMinus==string::npos) //plus op
    {
      currPos = foundPlus+1;
      string term = ops.substr(lastPos, (currPos-lastPos-1));
      //cout << term << endl;
      
      if (!firstFound)
      {
        firstFound=true;
        first = term;
      }
      else 
      {
        //get sign from lastPos-1
        
        MATH_OP op;
        op.b = term;
        op.addition = (ops[lastPos-1]=='+');
        
        operations.push_back(op);
        
      }
    }    
    else if (foundPlus < foundMinus)
    {
      currPos = foundPlus+1;
      string term = ops.substr(lastPos, (currPos-lastPos-1));
      //cout << term << endl;
      
      if (!firstFound)
      {
        firstFound=true;
        first = term;
      }
      else 
      {
        //get sign from lastPos-1
        
        MATH_OP op;
        op.b = term;
        op.addition = (ops[lastPos-1]=='+');
        
        operations.push_back(op);
        
      }
    }
    else
    {
      currPos = foundMinus+1;
      string term = ops.substr(lastPos, (currPos-lastPos-1));
      //cout << term << endl;
      
      if (!firstFound)
      {
        firstFound=true;
        first = term;
      }
      else 
      {
        //get sign from lastPos-1
        
        MATH_OP op;
        op.b = term;
        op.addition = (ops[lastPos-1]=='+');
        
        operations.push_back(op);
              
      }
    }  
  } while (foundPlus!=string::npos || foundMinus!=string::npos);
  
  
  
  
  string code = "";
  
  //load first into A register
  
  
  string type = getIdentifierType(first);
  
  //cout << first << endl;
  
  
  char chars[] = "()";
  
  for (unsigned int i = 0; i < strlen(chars); ++i)
  {    
    first.erase (std::remove(first.begin(), first.end(), chars[i]), first.end());
  }
  
  if (type == "literal const")
  {
    code += "LDAI " + first + "\n";
  }
  else if (type == "const")
  {
    code += "LDACMA " + first + "\n";
  }
  else if (type == "var")
  {
    code += "LDARAM $" + first + "\n";
  }  
  else if (type == "array")
  {
    
    code += genaddopcode(first.substr(first.find("[")+1, first.find("]")-first.find("[")-1));
    code += "LDBCMA ";
    code += first.substr(0, first.find("["));
    code += "\n";
    code += "ADDC\n";
    code += "LDARAMC\n";
    
  }
  else if (type == "constarr")
  {
    code += genaddopcode(first.substr(first.find("[")+1, first.find("]")-first.find("[")-1));
    code += "LDBCMA ";
    code += first.substr(0, first.find("["));
    code += "\n";
    code += "ADDC\n";
    code += "LDACMC\n";
  }
  else
  {
    code += "CALL " + first + "\n";
    //cout << "What to do with func call?" << endl;
  }
  
  
  //if literal, simply LDAI number
  //if constant, load from code memory space
  //if var, load from variable location
  
  
  for (auto op : operations)
  {
        
    //cout << op.b << endl;
        
    type = getIdentifierType(op.b);
   
    if (type == "literal const")
    {
      code += "LDBI " + op.b + "\n";
    }
    else if (type == "const")
    {
      code += "LDBCMA " + op.b + "\n";
    }
    else if (type == "var")
    {
      code += "LDBRAM $" + op.b + "\n";
    }
    else if (type == "array")
    {
      string o = op.b;
      code += "PUSHA\n";
      code += genaddopcode(o.substr(o.find("[")+1, o.find("]")-o.find("[")-1));
      code += "LDBCMA ";
      code += o.substr(0, o.find("["));
      code += "\n";
      code += "ADDC\n";
      code += "LDARAMC\n";
      code += "MOVAB\n";
      code += "POPA\n";
    }
    else if (type == "constarr")
    {
        string o = op.b;
        code += "PUSHA\n";
        code += genaddopcode(o.substr(o.find("[")+1, o.find("]")-o.find("[")-1));
        code += "LDBCMA ";
        code += o.substr(0, o.find("["));
        code += "\n";
        code += "ADDC\n";
        code += "LDACMC\n";
        code += "MOVAB\n";
        code += "POPA\n";
    }
    else
    {
      
      string o = op.b;
      
      for (unsigned int i = 0; i < strlen(chars); ++i)
      {    
        o.erase (std::remove(o.begin(), o.end(), chars[i]), o.end());
      }
      
      code += "PUSHA\n";
      code += "CALL " + o + "\n";
      code += "MOVAB\n";
      code += "POPA\n";
      //cout << "What to do with func call?" << endl;
    }
    
    if (op.addition)
    {
      code += "ADDA\n";
    }
    else
    {
      code += "SUBA\n";
    }    
  }
  return code;
}




/* Line 189 of yacc.c  */
#line 521 "minic.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
     T_LPAREN = 258,
     T_RPAREN = 259,
     T_MULT = 260,
     T_PLUS = 261,
     T_COMMA = 262,
     T_MINUS = 263,
     T_ASSIGN = 264,
     T_SCOLON = 265,
     T_LT = 266,
     T_LE = 267,
     T_NE = 268,
     T_EQ = 269,
     T_GT = 270,
     T_GE = 271,
     T_LBRACK = 272,
     T_RBRACK = 273,
     T_AND = 274,
     T_LCURLY = 275,
     T_ADDR = 276,
     T_BOOL = 277,
     T_CHAR = 278,
     T_CONST = 279,
     T_DIV = 280,
     T_ELSE = 281,
     T_RCURLY = 282,
     T_FALSE = 283,
     T_IF = 284,
     T_INT = 285,
     T_NOT = 286,
     T_OR = 287,
     T_SCANF = 288,
     T_TRUE = 289,
     T_WHILE = 290,
     T_VOID = 291,
     T_IDENT = 292,
     T_RETURN = 293,
     T_IFORMAT = 294,
     T_IFORMAT_NL = 295,
     T_CFORMAT = 296,
     T_CFORMAT_NL = 297,
     T_IOIN = 298,
     T_WRITE = 299,
     T_CHARCONST = 300,
     T_INTCONST = 301,
     T_UNKNOWN = 302,
     T_VRAMMAR = 303,
     T_FLIP = 304,
     T_GOTO = 305,
     T_COLON = 306
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 469 "minic.y"

	char* text;
  TYPE_INFO typeInfo;
  int i;
  



/* Line 214 of yacc.c  */
#line 617 "minic.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 629 "minic.tab.c"

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
# if YYENABLE_NLS
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   150

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  177

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    10,    14,    16,    20,
      27,    29,    34,    37,    42,    47,    50,    56,    66,    67,
      71,    73,    75,    79,    81,    85,    87,    90,    93,    98,
     104,   110,   114,   119,   124,   126,   130,   132,   138,   144,
     149,   152,   153,   157,   158,   162,   167,   169,   172,   174,
     176,   178,   180,   182,   184,   189,   192,   194,   196,   197,
     199,   201,   204,   207,   210,   213,   215,   217,   219,   222,
     225,   228,   231,   234,   237,   240,   242,   245,   249,   250,
     254,   256,   258,   260,   266,   271,   276
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    75,    -1,     6,    -1,     8,    -1,    -1,
      54,    67,    55,    -1,    65,    -1,    86,     9,    80,    -1,
      20,    85,    83,    77,    10,    27,    -1,    59,    -1,    20,
      85,    83,    27,    -1,    61,    81,    -1,    61,    81,    26,
      81,    -1,    29,     3,    66,     4,    -1,    79,    46,    -1,
      24,    37,     9,    62,    10,    -1,    24,    30,    71,     9,
      20,    62,    64,    27,    10,    -1,    -1,     7,    62,    64,
      -1,    87,    -1,    80,    -1,    80,    76,    80,    -1,    62,
      -1,     3,    66,     4,    -1,    37,    -1,     6,    37,    -1,
       8,    37,    -1,    37,    17,    66,    18,    -1,     6,    37,
      17,    66,    18,    -1,     8,    37,    17,    66,    18,    -1,
      37,     3,     4,    -1,     6,    37,     3,     4,    -1,     8,
      37,     3,     4,    -1,    37,    -1,    68,     3,     4,    -1,
      63,    -1,    30,    37,     3,     4,    58,    -1,    36,    37,
       3,     4,    58,    -1,    30,    71,    72,    10,    -1,    37,
      73,    -1,    -1,     7,    71,    72,    -1,    -1,    17,    46,
      18,    -1,    56,    17,    66,    18,    -1,    70,    -1,    75,
      70,    -1,    11,    -1,    15,    -1,    12,    -1,    16,    -1,
      14,    -1,    13,    -1,    38,     3,    78,     4,    -1,    38,
      78,    -1,    36,    -1,    66,    -1,    -1,     6,    -1,     8,
      -1,    67,    55,    -1,    57,    10,    -1,    69,    10,    -1,
      89,    10,    -1,    60,    -1,    88,    -1,    59,    -1,    90,
      10,    -1,    49,    10,    -1,    82,    10,    -1,    37,    51,
      -1,    91,    10,    -1,    77,    10,    -1,    50,    37,    -1,
      81,    -1,    81,    83,    -1,    30,    71,    72,    -1,    -1,
      84,    10,    85,    -1,    65,    -1,    74,    -1,    37,    -1,
      35,     3,    66,     4,    81,    -1,    44,     3,    66,     4,
      -1,    48,     3,    66,     4,    -1,    43,     3,    86,     4,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   508,   508,   623,   628,   636,   640,   664,   672,   724,
     754,   775,   784,  1089,  1450,  1459,  1467,  1486,  1517,  1521,
    1542,  1548,  1556,  1577,  1593,  1616,  1621,  1636,  1650,  1670,
    1690,  1710,  1727,  1744,  1762,  1769,  1775,  1821,  1844,  1864,
    1944,  1965,  1970,  1999,  2003,  2027,  2056,  2063,  2082,  2088,
    2094,  2100,  2106,  2112,  2119,  2124,  2130,  2135,  2144,  2148,
    2153,  2159,  2179,  2184,  2204,  2209,  2215,  2220,  2225,  2230,
    2235,  2240,  2254,  2259,  2277,  2291,  2296,  2312,  2320,  2323,
    2329,  2334,  2340,  2346,  2742,  2762,  2781
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_LPAREN", "T_RPAREN", "T_MULT",
  "T_PLUS", "T_COMMA", "T_MINUS", "T_ASSIGN", "T_SCOLON", "T_LT", "T_LE",
  "T_NE", "T_EQ", "T_GT", "T_GE", "T_LBRACK", "T_RBRACK", "T_AND",
  "T_LCURLY", "T_ADDR", "T_BOOL", "T_CHAR", "T_CONST", "T_DIV", "T_ELSE",
  "T_RCURLY", "T_FALSE", "T_IF", "T_INT", "T_NOT", "T_OR", "T_SCANF",
  "T_TRUE", "T_WHILE", "T_VOID", "T_IDENT", "T_RETURN", "T_IFORMAT",
  "T_IFORMAT_NL", "T_CFORMAT", "T_CFORMAT_NL", "T_IOIN", "T_WRITE",
  "T_CHARCONST", "T_INTCONST", "T_UNKNOWN", "T_VRAMMAR", "T_FLIP",
  "T_GOTO", "T_COLON", "$accept", "N_START", "N_ADDOP", "N_ADDOPLST",
  "N_ARRAYVAR", "N_ASSIGN", "N_BLOCK", "N_COMPOUND", "N_CONDITION",
  "N_COND_IF_THEN", "N_CONST", "N_CONSTDEC", "N_CONSTLST", "N_ENTIREVAR",
  "N_EXPR", "N_TERM", "N_FUNCTIDENT", "N_FUNCTCALL", "N_GLOBALDEC",
  "N_IDENT", "N_IDENTLST", "N_IDX", "N_IDXVAR", "N_PROG", "N_RELOP",
  "N_RETURN", "N_RETURNEXPR", "N_SIGN", "N_SIMPLEEXPR", "N_STMT", "N_GOTO",
  "N_STMTLST", "N_VARDEC", "N_VARDECPART", "N_VARIABLE", "N_VARIDENT",
  "N_WHILE", "N_WRITE", "N_SETVRAM", "N_IOIN", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    56,    57,    58,
      58,    59,    60,    60,    61,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    68,    69,    70,    70,    70,    70,
      71,    72,    72,    73,    73,    74,    75,    75,    76,    76,
      76,    76,    76,    76,    77,    77,    78,    78,    79,    79,
      79,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    82,    83,    83,    84,    85,    85,
      86,    86,    87,    88,    89,    90,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     0,     3,     1,     3,     6,
       1,     4,     2,     4,     4,     2,     5,     9,     0,     3,
       1,     1,     3,     1,     3,     1,     2,     2,     4,     5,
       5,     3,     4,     4,     1,     3,     1,     5,     5,     4,
       2,     0,     3,     0,     3,     4,     1,     2,     1,     1,
       1,     1,     1,     1,     4,     2,     1,     1,     0,     1,
       1,     2,     2,     2,     2,     1,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     3,     0,     3,
       1,     1,     1,     5,     4,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    36,    46,     2,     0,     0,
      43,    41,     0,     1,    47,    43,     0,    58,     0,     0,
      40,     0,     0,     0,     0,    59,    60,     0,     0,     0,
       0,    41,    39,     0,    58,    16,    15,    78,    37,    10,
      44,    42,    38,    18,     0,     0,     0,    58,     0,    41,
      78,    78,     0,     0,    82,    58,     0,     0,     0,     0,
       0,     0,     0,    67,    65,     0,    80,     0,     0,    81,
       0,    75,     0,     0,     0,    20,    66,     0,     0,     0,
      18,     0,    77,    79,     0,    58,    58,    71,    58,    59,
      60,    56,    25,    23,    57,     5,    55,    21,     0,    58,
      58,    69,    74,    58,    62,    12,     0,    63,    73,    76,
      70,    11,     0,    58,    64,    68,    72,    19,    17,     0,
      58,     0,     0,     0,     0,    26,    27,     0,    58,     3,
       4,    58,    61,    48,    50,    53,    52,    49,    51,    58,
      82,     0,     0,     0,     0,     0,    35,     0,     8,     0,
      14,     0,    24,    54,     0,    58,     0,    58,    31,     0,
       5,    22,    86,    84,    85,    45,    13,     9,    83,    32,
       0,    33,     0,    28,     6,    29,    30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   131,   132,    61,    62,    38,    63,    64,    65,
      93,     5,    48,    66,    94,    95,    67,    68,     6,    11,
      22,    20,    69,     7,   139,    70,    96,    28,    97,    71,
      72,    73,    45,    46,    74,    75,    76,    77,    78,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -107
static const yytype_int16 yypact[] =
{
      26,    27,   -23,    -2,    61,  -107,  -107,    26,    28,    54,
       5,    59,    64,  -107,  -107,    53,    60,    41,    68,    32,
    -107,    28,    65,    75,    76,  -107,  -107,    71,    38,    77,
      67,    59,  -107,    77,    41,  -107,  -107,    69,  -107,  -107,
    -107,  -107,  -107,    91,    28,    90,    39,    41,    74,    59,
      69,    69,    99,   100,     0,     3,   101,   102,   103,    97,
      72,    93,    98,  -107,  -107,    39,    94,   109,   104,  -107,
     105,    39,   106,     7,   108,  -107,  -107,   110,   111,   112,
      91,   113,  -107,  -107,    39,    18,    18,  -107,    17,    81,
      82,  -107,    10,  -107,  -107,    52,  -107,    79,    87,    18,
      18,  -107,  -107,    18,  -107,   107,   121,  -107,  -107,  -107,
    -107,  -107,   116,    18,  -107,  -107,  -107,  -107,  -107,    86,
      18,   123,   124,   125,   126,    14,    29,   127,    18,  -107,
    -107,    18,  -107,  -107,  -107,  -107,  -107,  -107,  -107,    18,
    -107,   128,   130,   131,   118,    39,  -107,   114,  -107,   125,
    -107,    39,  -107,  -107,   133,    18,   134,    18,  -107,   122,
      52,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
     129,  -107,   132,  -107,  -107,  -107,  -107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,   -18,  -107,  -107,   115,    19,  -107,  -107,
      -5,  -107,    63,  -107,   -84,     8,  -107,  -107,   137,    -3,
     -21,  -107,  -107,  -107,  -107,    73,    57,  -107,  -106,   -65,
    -107,   -41,  -107,   -13,    51,  -107,  -107,  -107,  -107,  -107
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -35
static const yytype_int16 yytable[] =
{
     105,   121,   122,   -34,   123,    16,    88,   148,    18,    89,
      41,    90,    27,   127,    10,   142,   143,   154,    31,   144,
     120,   120,    19,    89,    89,    90,    90,   128,    82,    43,
     109,   155,   156,   161,   111,    12,   149,    83,    84,    91,
      92,    49,    80,   119,   159,    55,   157,    25,    39,    26,
       1,    87,    39,    91,    92,    92,     2,     8,   129,    51,
     130,    13,     3,    17,     9,    15,    21,    23,    52,    24,
      19,   170,    29,   172,    53,    32,    54,    55,    30,    33,
     166,    35,    56,    57,    36,    40,   168,    58,    59,    60,
     133,   134,   135,   136,   137,   138,    34,    37,    47,    44,
      50,    81,    85,    86,    98,    99,   100,   101,   104,   102,
     103,    -7,   106,   111,   107,   108,   110,   113,   125,   126,
     114,   115,   116,   118,   140,   146,   147,   150,   151,   152,
     153,   158,   162,   145,   163,   164,   165,   169,   171,   160,
     173,   167,   174,   117,    14,   124,   112,   175,    42,   141,
     176
};

static const yytype_uint8 yycheck[] =
{
      65,    85,    86,     3,    88,     8,     3,   113,     3,     6,
      31,     8,    17,     3,    37,    99,   100,     3,    21,   103,
       3,     3,    17,     6,     6,     8,     8,    17,    49,    34,
      71,    17,     3,   139,    27,    37,   120,    50,    51,    36,
      37,    44,    47,    84,   128,    38,    17,     6,    29,     8,
      24,    51,    33,    36,    37,    37,    30,    30,     6,    20,
       8,     0,    36,     9,    37,    37,     7,     3,    29,     9,
      17,   155,     4,   157,    35,    10,    37,    38,    46,     4,
     145,    10,    43,    44,    46,    18,   151,    48,    49,    50,
      11,    12,    13,    14,    15,    16,    20,    20,     7,    30,
      10,    27,     3,     3,     3,     3,     3,    10,    10,    37,
      17,    17,     3,    27,    10,    10,    10,     9,    37,    37,
      10,    10,    10,    10,    37,     4,    10,     4,     4,     4,
       4,     4,     4,    26,     4,     4,    18,     4,     4,   131,
      18,    27,   160,    80,     7,    88,    73,    18,    33,    98,
      18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    30,    36,    53,    63,    70,    75,    30,    37,
      37,    71,    37,     0,    70,    37,    71,     9,     3,    17,
      73,     7,    72,     3,     9,     6,     8,    62,    79,     4,
      46,    71,    10,     4,    20,    10,    46,    20,    58,    59,
      18,    72,    58,    62,    30,    84,    85,     7,    64,    71,
      10,    20,    29,    35,    37,    38,    43,    44,    48,    49,
      50,    56,    57,    59,    60,    61,    65,    68,    69,    74,
      77,    81,    82,    83,    86,    87,    88,    89,    90,    91,
      62,    27,    72,    85,    85,     3,     3,    51,     3,     6,
       8,    36,    37,    62,    66,    67,    78,    80,     3,     3,
       3,    10,    37,    17,    10,    81,     3,    10,    10,    83,
      10,    27,    77,     9,    10,    10,    10,    64,    10,    83,
       3,    66,    66,    66,    78,    37,    37,     3,    17,     6,
       8,    54,    55,    11,    12,    13,    14,    15,    16,    76,
      37,    86,    66,    66,    66,    26,     4,    10,    80,    66,
       4,     4,     4,     4,     3,    17,     3,    17,     4,    66,
      67,    80,     4,     4,     4,    18,    81,    27,    81,     4,
      66,     4,    66,    18,    55,    18,    18
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
# if YYLTYPE_IS_TRIVIAL
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

/* Line 1455 of yacc.c  */
#line 509 "minic.y"
    {
			prRule("N_START", "N_PROG");
      
      string s = "LCALL mainAdd\n";
     // s += "HLT\n";
      s += "end:  JMP end\n";
      s += "mainAdd:  .DA main\n";
      
      //put constants
      
      for (auto i : consts)
      {        
        s += i.name;
        s += ":  .DW ";
        s += std::to_string(i.value >> 8);
        s += " ";
        s += std::to_string(i.value & 255);
        s += "\n";
      }
      
      for (auto i : constArrs)
      {
        s += i.name;
        s += ": .DA ";
        s += i.name;
        s += "Loc\n";
      }
      
      
      for (auto i : arrayVariables)
      {
        s += i.name;
        s += ": .DW &";
        s += i.name;
        s += "[";
        s += i.size;
        s += "]\n";
      }
      
      s += (yyvsp[(1) - (1)].text);
            
      for (auto i : constArrs)
      {
        s += i.name;
        s += "Loc: ";
        
        for (auto v : i.vals)
        {
          s += ".DW ";
          s += std::to_string(v >> 8);
          s += " ";
          s += std::to_string(v & 255);
          s += "\n";
        }
      }
      
      
      //cout << s;
      
      ofstream outpu;
      outpu.open("Output.asm");
      outpu << s;
      outpu.close();
      
      
			printf("\n--- Completed parsing ---\n\n");
      
      /*
      cout << "Variables:" << endl;
      for (auto i : variables)
      {
        cout << i << endl;
      }
      cout << "Arrays:" << endl;
      for (auto i : arrayVariables)

        {
        cout << i.name << " : " << i.size << endl;
      }
      cout << "Constants:" << endl;
      for (auto i : consts)
      {
        cout << "'" << i.name << "' = " << i.value << endl;
      }
      cout << "Constant Arrays:" << endl;
      for (auto i : constArrs)
      {
        cout << "'" << i.name << "' = { ";
        for (auto v : i.vals)
        {
          cout << v << " ";
        }
        cout << "}" << endl;
      }
      
      cout << "Memory:" << endl;
      for (auto i : memory)
      {
        cout << i << endl;
      }
      */
      
      
      
      
      
      for (auto thing : memory)
      {
        if (thing)
          delete[] thing;
      }
			return 0;
			;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 624 "minic.y"
    {
			prRule("N_ADDOP", "+");
      (yyval.text) = "+";
			;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 629 "minic.y"
    {
			prRule("N_ADDOP", "-");
      (yyval.text) = "-";
			;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 636 "minic.y"
    {
			prRule("N_ADDOPLST", "epsilon");
      (yyval.text) = "";
			;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 641 "minic.y"
    {
			prRule("N_ADDOPLST", 
				 "N_ADDOP N_TERM N_ADDOPLST");
      
      
      char* newWord = new char[strlen((yyvsp[(2) - (3)].text))+strlen((yyvsp[(3) - (3)].text))+2];
      
      strcpy(newWord, (yyvsp[(1) - (3)].text));
      strcat(newWord, (yyvsp[(2) - (3)].text));
      if ((yyvsp[(3) - (3)].text)!="")
      { 
        strcat(newWord, (yyvsp[(3) - (3)].text));
      }
      
      
      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);         
         
			;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 665 "minic.y"
    {
			prRule("N_ARRAYVAR", "N_ENTIREVAR");
      //yyerror("Arrays are not supported yet");      
      (yyval.text) = (yyvsp[(1) - (1)].text);
      
			;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 673 "minic.y"
    {
			prRule("N_ASSIGN", "N_VARIABLE = N_SIMPLEEXPR");  
      
      //cout << "Assignment:" << endl;
      
      
      string s = (yyvsp[(1) - (3)].text);
      if (s.find("[")==string::npos)
      {
        string code = genaddopcode((yyvsp[(3) - (3)].text));
      
        code += "STA $";
        code += (yyvsp[(1) - (3)].text);
        code += "\n";
        
        char* newWord = new char[code.size()+1];
        
        strcpy(newWord, code.c_str());
        
        (yyval.text) = newWord;
        
        memory.push_back(newWord);    
      }
      else
      {
        
        //assign to array
        
        string code = genaddopcode(s.substr(s.find("[")+1,s.find("]")-s.find("[")-1));
        code += "LDBCMA ";
        code += s.substr(0, s.find("["));
        code += "\n";                
        code += "ADDC\n";    
        code += "PUSHC\n";
        code += genaddopcode((yyvsp[(3) - (3)].text));        
        code += "POPC\n";
        code += "STARAMC\n";
        
        char* newWord = new char[code.size()+1];
        
        strcpy(newWord, code.c_str());
        
        (yyval.text) = newWord;
        
        memory.push_back(newWord);   
        
      }
      
      
			;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 726 "minic.y"
    {
			prRule("N_BLOCK", 
			       "{ N_VARDECPART N_STMTLST "
				 "N_RETURN ; }");
         
         
         
         string c = (yyvsp[(3) - (6)].text);
         
         if (getIdentifierType((yyvsp[(4) - (6)].text))!="void")
         {
           c += genaddopcode((yyvsp[(4) - (6)].text));
         }
         
         
         
         c += "RET\n";
         
         char* newWord = new char[c.size()+1];
         
         strcpy(newWord, c.c_str());
      
         (yyval.text) = newWord;
        
         memory.push_back(newWord);    
         
         
			;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 755 "minic.y"
    {
        prRule("N_BLOCK", "N_COMPOUND");
        
        
         
         string c = (yyvsp[(1) - (1)].text);
                  
         c += "RET\n";
         
         char* newWord = new char[c.size()+1];
         
         strcpy(newWord, c.c_str());
      
         (yyval.text) = newWord;
        
         memory.push_back(newWord);    
         
        
      ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 776 "minic.y"
    {
			prRule("N_COMPOUND", 
			       "{ N_VARDECPART N_STMTLST }");
             
      (yyval.text) = (yyvsp[(3) - (4)].text);
      
			;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 785 "minic.y"
    {
			prRule("N_CONDITION", 
			       "N_COND_IF_THEN N_THEN_STMT");
             
         string s = (yyvsp[(1) - (2)].typeInfo).v.s;           
           
         string a, b;
         
         if ((yyvsp[(1) - (2)].typeInfo).v.i==-1)
         {
           //cout << "Compare to 0" << endl;
           
             a=(yyvsp[(1) - (2)].typeInfo).v.s;             
             b="0";
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JZI skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord); 
           
         }
         else
         { 
           //cout << "Relational" << endl;
  
           
           
           if ((yyvsp[(1) - (2)].typeInfo).v.i==0) //<
           {           
           
             a=s.substr(0, s.find("<"));             
             b=s.substr(s.find("<")+1);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifcnt"+std::to_string(ifcount);
             code += "\n";
             code += "JMP ifskp"+std::to_string(ifcount);
             code += "\n";
             code += "ifcnt";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JCI continue
                       jmp skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
           
           }
           else if ((yyvsp[(1) - (2)].typeInfo).v.i==1) //>
           {
             a=s.substr(0, s.find(">"));             
             b=s.substr(s.find(">")+1);
                          
             string code = genaddopcode(b);
             code += "PUSHA\n";
             code += genaddopcode(a);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifcnt"+std::to_string(ifcount);
             code += "\n";
             code += "JMP ifskp"+std::to_string(ifcount);
             code += "\n";
             code += "ifcnt";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is B
                       right is A
                       CMP
                       JCI continue
                       jmp skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (2)].typeInfo).v.i==2) //<=
           {
             
             a=s.substr(0, s.find("<="));             
             b=s.substr(s.find("<=")+2);
                          
             string code = genaddopcode(b);
             code += "PUSHA\n";
             code += genaddopcode(a);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is B
                       right is A
                       CMP
                       JCI skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (2)].typeInfo).v.i==3) //>=
           {
             
             a=s.substr(0, s.find(">="));             
             b=s.substr(s.find(">=")+2);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JCI skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (2)].typeInfo).v.i==4) //==
           {
              
             a=s.substr(0, s.find("=="));             
             b=s.substr(s.find("==")+2);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifcnt"+std::to_string(ifcount);
             code += "\n";
             code += "JMP ifskp"+std::to_string(ifcount);
             code += "\n";
             code += "ifcnt";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JZI continue
                       jmp skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (2)].typeInfo).v.i==5) //!=
           {
             
             a=s.substr(0, s.find("!="));             
             b=s.substr(s.find("!=")+2);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (2)].text);             
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JZI skip
               continue: STATEMENT
               skip:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
             
           }
         }
          ifcount++;
             
			;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 1090 "minic.y"
    {
			prRule("N_CONDITION", 
			       "N_COND_IF_THEN "
			       "else N_STMT");
             
             
         string s = (yyvsp[(1) - (4)].typeInfo).v.s;           
           
         string a, b;
         
         if ((yyvsp[(1) - (4)].typeInfo).v.i==-1)
         {
           //cout << "Compare to 0" << endl;
           
             a=(yyvsp[(1) - (4)].typeInfo).v.s;             
             b="0";
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (4)].text);  
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
             
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JZI skip
               continue: STATEMENT
                       JMP skip2
               skip:  STATEMENT2
               skip2:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord); 
           
         }
         else
         { 
           //cout << "Relational" << endl;
  
           
           
           if ((yyvsp[(1) - (4)].typeInfo).v.i==0) //<
           {           
           
             a=s.substr(0, s.find("<"));             
             b=s.substr(s.find("<")+1);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifcnt"+std::to_string(ifcount);
             code += "\n";
             code += "JMP ifskp"+std::to_string(ifcount);
             code += "\n";
             code += "ifcnt";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(2) - (4)].text);             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JCI continue
                       jmp skip
               continue: STATEMENT
                      JMP skip2
               skip:  STATEMENT2
               skip2:
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
           
           }
           else if ((yyvsp[(1) - (4)].typeInfo).v.i==1) //>
           {
             a=s.substr(0, s.find(">"));             
             b=s.substr(s.find(">")+1);
                          
             string code = genaddopcode(b);
             code += "PUSHA\n";
             code += genaddopcode(a);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifcnt"+std::to_string(ifcount);
             code += "\n";
             code += "JMP ifskp"+std::to_string(ifcount);
             code += "\n";
             code += "ifcnt";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(2) - (4)].text);             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is B
                       right is A
                       CMP
                       JCI continue
                       jmp skip
               continue: STATEMENT
                       JMP skip2
               skip:  STATEMENT2
               skip2:
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (4)].typeInfo).v.i==2) //<=
           {
             
             a=s.substr(0, s.find("<="));             
             b=s.substr(s.find("<=")+2);
                          
             string code = genaddopcode(b);
             code += "PUSHA\n";
             code += genaddopcode(a);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (4)].text);             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is B
                       right is A
                       CMP
                       JCI skip
               continue: STATEMENT
                      JMP skip2
               skip:  STATEMENT2
               skip2:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (4)].typeInfo).v.i==3) //>=
           {
             
             a=s.substr(0, s.find(">="));             
             b=s.substr(s.find(">=")+2);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (4)].text);             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JCI skip
               continue: STATEMENT
                        JMP skip2
               skip:  STATEMENT2
               skip2:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (4)].typeInfo).v.i==4) //==
           {
              
             a=s.substr(0, s.find("=="));             
             b=s.substr(s.find("==")+2);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifcnt"+std::to_string(ifcount);
             code += "\n";
             code += "JMP ifskp"+std::to_string(ifcount);
             code += "\n";
             code += "ifcnt";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(2) - (4)].text);             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JZI continue
                       jmp skip
               continue: STATEMENT
                        JMP skip2
               skip:  STATEMENT2
               skip2:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(1) - (4)].typeInfo).v.i==5) //!=
           {
             
             a=s.substr(0, s.find("!="));             
             b=s.substr(s.find("!=")+2);
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += (yyvsp[(2) - (4)].text);             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += (yyvsp[(4) - (4)].text);
             code += "if2skp";
             code += std::to_string(ifcount);
             code += ": ";
                          
             /*                      
                       left is A
                       right is B
                       CMP
                       JZI skip
               continue: STATEMENT
                        JMP skip2
               skip:  STATEMENT2
               skip2:
               
           */
             
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
             
           }
         }
          ifcount++;       
			;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 1451 "minic.y"
    {
			prRule("N_COND_IF_THEN", "if ( N_EXPR )");
      
      (yyval.typeInfo).v.s = (yyvsp[(3) - (4)].typeInfo).v.s;
      (yyval.typeInfo).v.i = (yyvsp[(3) - (4)].typeInfo).v.i;
      
			;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 1460 "minic.y"
    {
			prRule("N_CONST", "N_SIGN T_INTCONST");
      (yyval.typeInfo).type = INT;
      
      (yyval.typeInfo).v.i = (yyvsp[(1) - (2)].i) * stoi((yyvsp[(2) - (2)].text));      
			;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 1469 "minic.y"
    {
			prRule("N_CONSTDECPART",
			       "const T_IDENT = N_CONST ;");             
      
      string s = (yyvsp[(2) - (5)].text);
      s += "[";
      s += std::to_string((yyvsp[(4) - (5)].typeInfo).v.i);
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
    
      (yyval.text) = newWord;      
      memory.push_back(newWord);  
      
			;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 1487 "minic.y"
    {
        prRule("N_CONSTDEC", "const int IDENT = { CONSTLST };");   
        
        
        string s = (yyvsp[(3) - (9)].text);
        s = s.substr(0, s.find("["));
        s += "{";
        s += std::to_string((yyvsp[(6) - (9)].typeInfo).v.i);
        
        if ((yyvsp[(7) - (9)].text)!="")
        {
          s += ",";
        }
        
        s += (yyvsp[(7) - (9)].text);
        s += "}";
      
        //cout << "CONST ARRAY DEC: " << s << endl;
      
        char* newWord = new char[s.size()+1];
      
        strcpy(newWord, s.c_str());
    
        (yyval.text) = newWord;      
        memory.push_back(newWord);  
        
        
      ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 1517 "minic.y"
    {
        (yyval.text) = "";
        prRule("N_CONSTLST", "epsilon");   
      ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 1522 "minic.y"
    {
        prRule("N_CONSTLST", ", const constlst");   
        
        string s = std::to_string((yyvsp[(2) - (3)].typeInfo).v.i);
        
        if ((yyvsp[(3) - (3)].text)!="")
        {
          s += ",";
        }
        s += (yyvsp[(3) - (3)].text);
        
        char* newWord = new char[s.size()+1];
      
        strcpy(newWord, s.c_str());
    
        (yyval.text) = newWord;      
        memory.push_back(newWord); 
        
      ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 1543 "minic.y"
    {
			prRule("N_ENTIREVAR", "N_VARIDENT");   
      (yyval.text) = (yyvsp[(1) - (1)].text);      
			;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 1549 "minic.y"
    {
			prRule("N_EXPR", "N_SIMPLEEXPR");
      
      (yyval.typeInfo).v.s = (yyvsp[(1) - (1)].text);
      (yyval.typeInfo).v.i=-1;
      
			;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 1557 "minic.y"
    {
			prRule("N_EXPR", 
			       "N_SIMPLEEXPR N_RELOP N_SIMPLEEXPR"); 

             string s = (yyvsp[(1) - (3)].text);
             s += (yyvsp[(2) - (3)].typeInfo).v.s;
             s += (yyvsp[(3) - (3)].text);
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             memory.push_back(newWord);
             
             (yyval.typeInfo).v.s = newWord;
             (yyval.typeInfo).v.i = (yyvsp[(2) - (3)].typeInfo).v.i;

             
			;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 1578 "minic.y"
    {
			prRule("N_TERM", "N_CONST");
      
      string s = std::to_string((yyvsp[(1) - (1)].typeInfo).v.i);
      
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      memory.push_back(newWord);
      
      (yyval.text) = newWord;
      
			;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 1594 "minic.y"
    {
			prRule("N_TERM", "( N_EXPR )");
      
      char* newWord = new char[strlen((yyvsp[(2) - (3)].typeInfo).v.s)+3];
      
      strcpy(newWord, "(");
      strcat(newWord, (yyvsp[(2) - (3)].typeInfo).v.s);
      strcat(newWord, ")");
      
      
      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 1617 "minic.y"
    {
			prRule("N_TERM", "T_IDENT");
      (yyval.text) = (yyvsp[(1) - (1)].text);
			;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 1622 "minic.y"
    {
			prRule("N_TERM", "+ T_IDENT");
      
      string s = "+";
      s += (yyvsp[(2) - (2)].text);
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 1637 "minic.y"
    {
			prRule("N_TERM", "- T_IDENT");
      
      char* newWord = new char[strlen((yyvsp[(2) - (2)].text))+1];
      
      strcpy(newWord, "-");
      strcat(newWord, (yyvsp[(2) - (2)].text));      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 1651 "minic.y"
    {
			prRule("N_TERM", "T_IDENT [ N_EXPR ]");
      //yyerror("Arrays are not yet supported");
           
      
      string s = (yyvsp[(1) - (4)].text);
      s += "[";
      s += (yyvsp[(3) - (4)].typeInfo).v.s;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());       
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 1671 "minic.y"
    {
			prRule("N_TERM", "+ T_IDENT [ N_EXPR ]");
      //yyerror("Arrays are not yet supported");
      
      string s = "+";
      s += (yyvsp[(2) - (5)].text);
      s += "[";
      s += (yyvsp[(4) - (5)].typeInfo).v.s;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());       
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1691 "minic.y"
    {
			prRule("N_TERM", "- T_IDENT [ N_EXPR ]");
      //yyerror("Arrays are not yet supported");
      
      string s = "-";
      s += (yyvsp[(2) - (5)].text);
      s += "[";
      s += (yyvsp[(4) - (5)].typeInfo).v.s;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());       
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 1711 "minic.y"
    {
			prRule("N_TERM", "T_IDENT ( )");
      
      char* newWord = new char[strlen((yyvsp[(1) - (3)].text))+3];
            
      strcpy(newWord, (yyvsp[(1) - (3)].text));
      strcat(newWord, "(");
      strcat(newWord, ")");
      
      
      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
			;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 1728 "minic.y"
    {
			prRule("N_TERM", "+ T_IDENT ( )");
      
      string s = "+";
      s += (yyvsp[(2) - (4)].text);
      s += "()";
      
      char* newWord = new char[s.size()+1];
            
      strcpy(newWord, s.c_str());
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1745 "minic.y"
    {
			prRule("N_TERM", "- T_IDENT ( )");
      
      string s = "-";
      s += (yyvsp[(2) - (4)].text);
      s += "()";
      
      char* newWord = new char[s.size()+1];
            
      strcpy(newWord, s.c_str());
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1763 "minic.y"
    {
			prRule("N_FUNCTIDENT", "T_IDENT");
      (yyval.text) = (yyvsp[(1) - (1)].text);
      
			;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 1770 "minic.y"
    {
			prRule("N_FUNCTCALL", "N_FUNCTIDENT ( )");
      (yyval.text) = (yyvsp[(1) - (3)].text);      
			;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1776 "minic.y"
    {
			prRule("N_GLOBALDEC", "N_CONSTDEC");
      
      string s = (yyvsp[(1) - (1)].text);
      if (s.find("[")!=string::npos) //regular const
      {
        CONSTANT c;
        
        string s = (yyvsp[(1) - (1)].text);
        
        c.name = s.substr(0, s.find("["));
        c.value = stoi(s.substr(s.find("[")+1, s.find("]")-s.find("[")-1));
        
        consts.push_back(c);        
      }
      else //const arr
      {
        //cout << "Const arr: " << s << endl;
        
        CONSTARR c;
        
        c.name = s.substr(0, s.find("{"));
        
        string vals = s.substr(s.find("{")+1, s.find("}")-s.find("{")-1);
        
        
        stringstream check1(vals);
        string intermediate;
        
        while(getline(check1, intermediate, ','))
        {           
          c.vals.push_back(stoi(intermediate));
        }          
        
        constArrs.push_back(c);
        
        
      }
      (yyval.text) = "";
			;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1822 "minic.y"
    {
			prRule("N_GLOBALDEC", 
			       "int T_IDENT ( ) N_BLOCK");
             
        
        
        string c = (yyvsp[(2) - (5)].text);
        c += ": ";
        c += (yyvsp[(5) - (5)].text);
               
        
        char* newWord = new char[c.size()+1];
      
        strcpy(newWord, c.c_str());
        
        (yyval.text) = newWord;
        
        memory.push_back(newWord);
        
        //cout << $$;
             
			;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 1845 "minic.y"
    {
			prRule("N_GLOBALDEC", 
				 "void T_IDENT ( ) N_BLOCK");   

        string c = (yyvsp[(2) - (5)].text);
        c += ": ";
        c += (yyvsp[(5) - (5)].text);
               
        
        char* newWord = new char[c.size()+1];
      
        strcpy(newWord, c.c_str());
        
        (yyval.text) = newWord;
        
        memory.push_back(newWord);

         
			;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 1865 "minic.y"
    {
			prRule("N_GLOBALDEC", 
			       "int N_IDENT N_IDENTLST ;");
      string s = (yyvsp[(2) - (4)].text);
      if (s.find("[")!=string::npos)
      {
        //array
        
        string s;
        s = (yyvsp[(2) - (4)].text);      
        if ((yyvsp[(3) - (4)].typeInfo).v.s!="")
        {
          s = s + "," + (yyvsp[(3) - (4)].typeInfo).v.s;
        }
        
        //cout << "Array Variable declaration: " + s << endl;      
        
        stringstream check1(s);
        string intermediate;
        
        while(getline(check1, intermediate, ','))
        {
          
          for (auto var : arrayVariables)
          {
            if (var.name == intermediate)
            {
              string err = "Duplicate array variable declaration: " + intermediate;
              yyerror(err.c_str());
            }
          }        
          
          ARRAY a;
          
          
          
          a.name = intermediate.substr(0, intermediate.find("["));
          
          a.size = intermediate.substr(intermediate.find("[")+1,intermediate.find("]")-intermediate.find("[")-1);
          
          
          arrayVariables.push_back(a);
        }
        
        (yyval.text) = "";
        
      }
      else
      {
        string s;
        s = (yyvsp[(2) - (4)].text);      
        if ((yyvsp[(3) - (4)].typeInfo).v.s!="")
        {
          s = s + "," + (yyvsp[(3) - (4)].typeInfo).v.s;
        }
        
        //cout << "Variable declaration: " + s << endl;      
        
        stringstream check1(s);
        string intermediate;
        
        while(getline(check1, intermediate, ','))
        {
          
          for (auto var : variables)
          {
            if (var == intermediate)
            {
              string err = "Duplicate variable declaration: " + intermediate;
              yyerror(err.c_str());
            }
          }        
          variables.push_back(intermediate);
        }
        
        (yyval.text) = "";
      }
      
			;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 1945 "minic.y"
    {
			prRule("N_IDENT", "T_IDENT N_IDX"); 
      
      //$$.type = STR;      
      
      string s = (yyvsp[(1) - (2)].text);
      s += (yyvsp[(2) - (2)].text);
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
         
			;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1965 "minic.y"
    {
			prRule("N_IDENTLST", "epsilon");      
      (yyval.typeInfo).type = STR;
      (yyval.typeInfo).v.s = "";
			;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 1971 "minic.y"
    {
			prRule("N_IDENTLST", 
			       ", N_IDENT N_IDENTLST");      
             
             
      (yyval.typeInfo).type = STR;
      
      
      
      char* newWord = new char[strlen((yyvsp[(2) - (3)].text))+strlen((yyvsp[(3) - (3)].typeInfo).v.s)+2];
      
      strcpy(newWord, (yyvsp[(2) - (3)].text));
      if ((yyvsp[(3) - (3)].typeInfo).v.s!="")
      {
        strcat(newWord, ",");
        strcat(newWord, (yyvsp[(3) - (3)].typeInfo).v.s);
      }
      
      
      
      
      (yyval.typeInfo).v.s = newWord;
      
      memory.push_back(newWord);
      
			;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 1999 "minic.y"
    {
			prRule("N_IDX", "epsilon");
      (yyval.text)="";
			;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 2004 "minic.y"
    {
			prRule("N_IDX", "[ T_INTCONST ]");
      
      
      string s = "[";
      s += (yyvsp[(2) - (3)].text);
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      
      
      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
      
			;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 2028 "minic.y"
    {
			prRule("N_IDXVAR", "N_ARRAYVAR [ N_EXPR ]");
      
      //cout << "Var: " << $1 << endl;
      //cout << "Expr: " << genaddopcode($3.v.s) << endl;
      
      
      string s = (yyvsp[(1) - (4)].text);
      s += "[";
      s += (yyvsp[(3) - (4)].typeInfo).v.s;
      s += "]";
      
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      
      
      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
      
			;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 2057 "minic.y"
    {
			prRule("N_PROG", "N_GLOBALDEC");
      
      (yyval.text) = (yyvsp[(1) - (1)].text);
      
			;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 2064 "minic.y"
    {
			prRule("N_PROG", "N_PROG N_GLOBALDEC");
      
      string s = (yyvsp[(1) - (2)].text);
      
      s += (yyvsp[(2) - (2)].text);
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);
      
      
			;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 2083 "minic.y"
    {
			prRule("N_RELOP", "<");
      (yyval.typeInfo).v.s = "<";
      (yyval.typeInfo).v.i = 0;
			;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 2089 "minic.y"
    {
			prRule("N_RELOP", ">");
      (yyval.typeInfo).v.s = ">";
      (yyval.typeInfo).v.i = 1;
			;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 2095 "minic.y"
    {
			prRule("N_RELOP", "<=");
      (yyval.typeInfo).v.s = "<=";
      (yyval.typeInfo).v.i = 2;
			;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 2101 "minic.y"
    {
			prRule("N_RELOP", ">=");
      (yyval.typeInfo).v.s = ">=";
      (yyval.typeInfo).v.i = 3;
			;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 2107 "minic.y"
    {
			prRule("N_RELOP", "==");
      (yyval.typeInfo).v.s = "==";
      (yyval.typeInfo).v.i = 4;
			;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 2113 "minic.y"
    {
			prRule("N_RELOP", "!=");
      (yyval.typeInfo).v.s = "!=";
      (yyval.typeInfo).v.i = 5;
			;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 2120 "minic.y"
    {
			prRule("N_RETURN", "return ( N_RETURNEXPR )");
      (yyval.text) = (yyvsp[(3) - (4)].typeInfo).v.s;
			;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 2125 "minic.y"
    {
			prRule("N_RETURN", "return N_RETURNEXPR");
      (yyval.text) = (yyvsp[(2) - (2)].typeInfo).v.s;
			;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 2131 "minic.y"
    {
			prRule("N_RETURNEXPR", "void");
      (yyval.typeInfo).v.s = "[void]";
			;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 2136 "minic.y"
    {
			prRule("N_RETURNEXPR", "N_EXPR");
      (yyval.typeInfo).v.s = (yyvsp[(1) - (1)].typeInfo).v.s;
      (yyval.typeInfo).v.i = (yyvsp[(1) - (1)].typeInfo).v.i;
      
			;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 2144 "minic.y"
    {
			prRule("N_SIGN", "epsilon");
      (yyval.i) = 1;
			;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 2149 "minic.y"
    {
			prRule("N_SIGN", "+");
      (yyval.i) = 1;
			;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 2154 "minic.y"
    {
			prRule("N_SIGN", "-");
      (yyval.i) = -1;
			;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 2160 "minic.y"
    {
			prRule("N_SIMPLEEXPR", "N_TERM N_ADDOPLST");
      
      //cout << $1 << " : " << $2 << endl;
      
      char* newWord = new char[strlen((yyvsp[(1) - (2)].text))+strlen((yyvsp[(2) - (2)].text))+1];
      
      
      
      
      strcpy(newWord, (yyvsp[(1) - (2)].text));
      strcat(newWord, (yyvsp[(2) - (2)].text));
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);          
      
			;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 2180 "minic.y"
    {
			prRule("N_STMT", "N_ASSIGN ;");
      (yyval.text) = (yyvsp[(1) - (2)].text);
			;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 2185 "minic.y"
    {
			prRule("N_STMT", "N_FUNCTCALL ;");
      
      string s = "CALL ";
      s += (yyvsp[(1) - (2)].text);
      s += "\n";
      
      char* newWord = new char[s.size()+1];
      
      
      
      
      strcpy(newWord, s.c_str());      
      
      (yyval.text) = newWord;
      
      memory.push_back(newWord);       
      
			;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 2205 "minic.y"
    {
			prRule("N_STMT", "N_WRITE ;");
      (yyval.text) = (yyvsp[(1) - (2)].text);
			;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 2210 "minic.y"
    {
			prRule("N_STMT", "N_CONDITION");
      (yyval.text) = (yyvsp[(1) - (1)].text);
      //cout << $1 << endl;
			;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 2216 "minic.y"
    {
			prRule("N_STMT", "N_WHILE");
      (yyval.text) = (yyvsp[(1) - (1)].text);
			;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 2221 "minic.y"
    {
			prRule("N_STMT", "N_COMPOUND");
      (yyval.text) = (yyvsp[(1) - (1)].text);
			;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 2226 "minic.y"
    {
      prRule("N_STMT", "N_SETVRAM ;");  
        (yyval.text) = (yyvsp[(1) - (2)].text);
      ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 2231 "minic.y"
    {
        prRule("N_STMT", "N_FLIP ;");  
        (yyval.text) = "FLIP\n";
      ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 2236 "minic.y"
    {
        prRule("N_STMT", "N_GOTO ;");          
        (yyval.text) = (yyvsp[(1) - (2)].text);               
      ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 2241 "minic.y"
    {
        prRule("N_STMT", "N_IDENT :");   
        string s = (yyvsp[(1) - (2)].text);
        s += ": ";
        
        char* newWord = new char[s.size()+1];
      
      
        strcpy(newWord, s.c_str());      
        (yyval.text) = newWord;      
        memory.push_back(newWord); 
        
      ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 2255 "minic.y"
    {
        prRule("N_STMT", "N_IOIN ;");   
        (yyval.text) = (yyvsp[(1) - (2)].text);  
      ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 2260 "minic.y"
    {
        prRule("N_STMT", "N_RETURN ;");   
        string s = "";
        if (getIdentifierType((yyvsp[(1) - (2)].text))!="void")
        {
          s += genaddopcode((yyvsp[(1) - (2)].text));
        }
        s += "RET\n";
        
        char* newWord = new char[s.size()+1];
      
      
        strcpy(newWord, s.c_str());      
        (yyval.text) = newWord;      
        memory.push_back(newWord); 
      ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 2278 "minic.y"
    {
          prRule("N_GOTO", "T_GOTO T_IDENT");
          
          string s = "JMP ";
          s += (yyvsp[(2) - (2)].text);
          s += "\n";
          
          char* newWord = new char[s.size()+1];
      
          strcpy(newWord, s.c_str());      
          (yyval.text) = newWord;      
          memory.push_back(newWord);           
      ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 2292 "minic.y"
    {
			prRule("N_STMTLST", "N_STMT");
      (yyval.text) = (yyvsp[(1) - (1)].text);      
			;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 2297 "minic.y"
    {
			prRule("N_STMTLST", "N_STMT N_STMTLST");
      
      string s = (yyvsp[(1) - (2)].text);
      s += (yyvsp[(2) - (2)].text);
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      (yyval.text) = newWord;      
      memory.push_back(newWord);              
           
			;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 2313 "minic.y"
    {
			prRule("N_VARDEC", 
				 "T_INT N_IDENT N_IDENTLST");
         yyerror("No.");
			;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 2320 "minic.y"
    {
			prRule("N_VARDECPART", "epsilon");
			;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 2324 "minic.y"
    {
			prRule("N_VARDECPART",
			       "N_VARDEC ; N_VARDECPART");
			;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 2330 "minic.y"
    {
			prRule("N_VARIABLE", "N_ENTIREVAR");
      (yyval.text) = (yyvsp[(1) - (1)].text);
			;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 2335 "minic.y"
    {
			prRule("N_VARIABLE", "N_IDXVAR");
      (yyval.text) = (yyvsp[(1) - (1)].text);
			;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 2341 "minic.y"
    {
			prRule("N_VARIDENT", "T_IDENT");
      (yyval.text) = (yyvsp[(1) - (1)].text);
			;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 2347 "minic.y"
    {
			prRule("N_WHILE", 
				 "T_WHILE ( N_EXPR ) N_STMT");
         
         string s = (yyvsp[(3) - (5)].typeInfo).v.s;           
           
         string a, b;
         
         if ((yyvsp[(3) - (5)].typeInfo).v.i==-1)
         {
           //cout << "Compare to 0" << endl;
           
           
           //cout << "Not equal" << endl;
             a=(yyvsp[(3) - (5)].typeInfo).v.s;             
             b="0";
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI loopdn"+std::to_string(loopcount);
             code += "\n";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is A
                        right is 0
                        CMP
                        JZI done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord); 
           
           
           
         }
         else
         {
           
           
           
           //cout << "Relational" << endl;
  
           
           
           if ((yyvsp[(3) - (5)].typeInfo).v.i==0) //<
           { 
           
             //cout << "Less than" << endl;
             a=s.substr(0, s.find("<"));             
             b=s.substr(s.find("<")+1);
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI loopcnt"+std::to_string(loopcount);
             code += "\n";
             code += "JMP loopdn"+std::to_string(loopcount);
             code += "\n";
             code += "loopcnt";
             code += std::to_string(loopcount);
             code += ": ";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is A
                        right is B
                        CMP
                        JCI continue
                        jmp done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);     
             
             
           }
           else if ((yyvsp[(3) - (5)].typeInfo).v.i==1) //>
           {
             //cout << "Greater than" << endl;
             
             a=s.substr(0, s.find(">"));             
             b=s.substr(s.find(">")+1);
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(b);
             code += "PUSHA\n";
             code += genaddopcode(a);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI loopcnt"+std::to_string(loopcount);
             code += "\n";
             code += "JMP loopdn"+std::to_string(loopcount);
             code += "\n";
             code += "loopcnt";
             code += std::to_string(loopcount);
             code += ": ";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is B
                        right is A
                        CMP
                        JCI continue
                        jmp done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
            
              
            
             (yyval.text) = newWord;      
             memory.push_back(newWord); 
             
             
             
             
           }
           else if ((yyvsp[(3) - (5)].typeInfo).v.i==2) //<=
           {
             
             //cout << "Less or equal than" << endl;
             
             a=s.substr(0, s.find("<="));             
             b=s.substr(s.find("<=")+2);
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(b);
             code += "PUSHA\n";
             code += genaddopcode(a);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI loopdn"+std::to_string(loopcount);
             code += "\n";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is B
                        right is A
                        CMP
                        JCI done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
            
              
            
             (yyval.text) = newWord;      
             memory.push_back(newWord); 
             
             
           }
           else if ((yyvsp[(3) - (5)].typeInfo).v.i==3) //>=
           {
             
             //cout << "Greater or equal than" << endl;
             a=s.substr(0, s.find(">="));             
             b=s.substr(s.find(">=")+2);
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JCI loopdn"+std::to_string(loopcount);
             code += "\n";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is A
                        right is B
                        CMP
                        JCI done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);    
             
             
           }
           else if ((yyvsp[(3) - (5)].typeInfo).v.i==4) //==
           {
             
             //cout << "Equal" << endl;
             a=s.substr(0, s.find("=="));             
             b=s.substr(s.find("==")+2);
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI loopcnt"+std::to_string(loopcount);
             code += "\n";
             code += "JMP loopdn"+std::to_string(loopcount);
             code += "\n";
             code += "loopcnt";
             code += std::to_string(loopcount);
             code += ": ";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is A
                        right is B
                        CMP
                        JZI continue
                        jmp done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ((yyvsp[(3) - (5)].typeInfo).v.i==5) //!=
           {
             //cout << "Not equal" << endl;
             a=s.substr(0, s.find("!="));             
             b=s.substr(s.find("!=")+2);
             
             string code = "loopstart"+std::to_string(loopcount);
             code += ": ";
             code += genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI loopdn"+std::to_string(loopcount);
             code += "\n";
             code += (yyvsp[(5) - (5)].text);
             code += "JMP loopstart"+std::to_string(loopcount);
             code += "\n";
             code += "loopdn";
             code += std::to_string(loopcount);
             code += ": ";
             
             
             /*
             
             
             loopstart: left is A
                        right is B
                        CMP
                        JZI done
             continue:  STATEMENT
                        JMP loopstart
             done:
             
             
             */
             
             char* newWord = new char[code.size()+1];
      
             strcpy(newWord, code.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord); 
           }




           

           
           
           
           
         }
         
        loopcount++;
         
			;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 2743 "minic.y"
    {
			prRule("N_WRITE", 
			       "write ( N_EXPR )");
             
             string s = genaddopcode((yyvsp[(3) - (4)].typeInfo).v.s);
             
             s += "MOVAC\n";
             s += "VRCC\n";
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);   
             
             
			;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 2763 "minic.y"
    {
          prRule("N_SETVRAM", 
			       "vrammar ( N_EXPR )");
             
             
             string s = genaddopcode((yyvsp[(3) - (4)].typeInfo).v.s);
             
             s += "VMARA\n";
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);     
             
             
      ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 2782 "minic.y"
    {
          prRule("N_IOIN", 
			       "ioin ( N_VARIABLE )");
             
             
             string s = "LDAIO\n";
             s += "STA $";
             s += (yyvsp[(3) - (4)].text);
             s += "\n";
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             (yyval.text) = newWord;      
             memory.push_back(newWord);     
             
             
      ;}
    break;



/* Line 1455 of yacc.c  */
#line 4646 "minic.tab.c"
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



/* Line 1675 of yacc.c  */
#line 2802 "minic.y"


#include "lex.yy.c"
extern FILE *yyin;

// Output left- and right-hand side of a production
void prRule(const char *lhs, const char *rhs) 
{
  if (OUTPUT_PRODUCTIONS)
    printf("%s -> %s\n", lhs, rhs);
  return;
}

// Output specified error message and terminate execution
int yyerror(const char *s) 
{
  printf("Line %d: %s\n", lineNum, s);
  exit(1);
}

// Check whether yytext contains a valid int, returning
// 0 if valid, 1 if maybe valid (needs more checking) 
// or invalid
int ckInt() 
{
  char *ptr;
  int	rc = 0;
  ptr = yytext;

  // Ignore leading zeroes
  while (*ptr == '0')
    ++ptr;

  switch (*ptr) {
  case '1':	// Valid
			break;

  case '2':	// It depends
			if (strcmp(MAX_INT, ptr) < 0)
                  rc = 1;
			break;

  default:	     // Invalid
			rc = 1;
			break;
		}
  return rc;
}

// Read and ignore input until you get an ending token
void ignoreComment() 
{
  char c, pc = 0;

  while (((c = yyinput()) != '/' || pc != '*') && c != 0) 
  {
    pc = c;
    if (c == '\n') lineNum++;
  }

  return;
}

// Output token and lexeme
void printTokenInfo(const char* tokenType, const char* lexeme) 
{
  if (OUTPUT_TOKENS)
    printf("\t\t\t\t\t\tTOKEN: %-15s  LEXEME: %s\n", tokenType, lexeme);
}

int main()
{
  // Loop as long as there is anything to parse
  do {
    yyparse();
  } while (!feof(yyin));

  return 0;
}



