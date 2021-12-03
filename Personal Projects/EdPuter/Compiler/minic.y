//Grammatical Parser Written with Bison

%{

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
} CONSTARR;        //constant arrays have a name and list of values

typedef struct
{
  string name;
  int value;
} CONSTANT;     //constant have a name and value


typedef struct
{
  string name;
  string size;
} ARRAY;      //arrays have a name and size in RAM



vector<CONSTANT> consts;
vector<CONSTARR> constArrs;

vector<string> variables;
vector<ARRAY> arrayVariables;

#define INT 0
#define STR 1

int loopcount=0; //keep track of the number loop or if statement we're on for the ASM generation step, 
int ifcount=0;   //since we need to label them accordingly for jumps

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
  
} MATH_OP;    //this computer only supports addition and subtraction operations, so a single boolean for add/sub should suffice







string getIdentifierType(string thing)
{
  for (CONSTANT c : consts) //see if this name is in the list of known constants
  {
    if (c.name == thing)
    {
      //its a constant
      return "const";
    }    
  }
  for (string s : variables) //see if this name is in the list of known variables
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
    
    for (auto c : constArrs) //see if this name is in the list of known constant arrays
    {
      if (c.name == thing.substr(0, thing.find("[")))
      {
        return "constarr";
      }      
    }
    
    for (auto c : arrayVariables) //see if this name is in the list of known arrays
    {
      if (c.name == thing.substr(0, thing.find("[")))
      {
        return "array";
      }      
    }
  } 
  
  //if we got here, then an unknown identifier was parsed
  
  cout << thing << "      <---- ??" << endl;
  
  yyerror("Unknown Identifier detected during code generation");
}



//This function is what actually generates ASM code from the operations input
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


%}

%union
{
	char* text;
  TYPE_INFO typeInfo;
  int i;
  
};

/*
 *  Token declaration. 'N_...' for rules, 'T_...' for tokens
 */
%token T_LPAREN  T_RPAREN  T_MULT  T_PLUS  T_COMMA  T_MINUS
%token T_ASSIGN  T_SCOLON  T_LT  T_LE  T_NE  T_EQ  T_GT
%token T_GE  T_LBRACK  T_RBRACK  T_AND  T_LCURLY  T_ADDR     
%token T_BOOL T_CHAR  T_CONST  T_DIV  T_ELSE  T_RCURLY
%token T_FALSE T_IF  T_INT  T_NOT T_OR
%token T_SCANF  T_TRUE  T_WHILE  T_VOID T_IDENT T_RETURN
%token T_IFORMAT  T_IFORMAT_NL T_CFORMAT  T_CFORMAT_NL T_IOIN
%token T_WRITE T_CHARCONST  T_INTCONST  T_UNKNOWN T_VRAMMAR T_FLIP T_GOTO T_COLON


%type <text> T_IDENT N_ASSIGN N_ENTIREVAR N_VARIABLE N_VARIDENT T_INTCONST N_TERM N_ADDOPLST N_ADDOP N_SIMPLEEXPR N_STMT N_STMTLST N_BLOCK N_RETURN N_GLOBALDEC N_PROG N_COMPOUND N_WHILE N_SETVRAM N_WRITE N_CONDITION N_GOTO N_IOIN N_FUNCTCALL N_FUNCTIDENT N_IDX N_IDENT N_IDXVAR N_ARRAYVAR N_CONSTLST N_CONSTDEC


%type <typeInfo>  N_IDENTLST N_CONST N_RELOP N_EXPR N_RETURNEXPR N_COND_IF_THEN

%type <i> N_SIGN



/*
 *  Start symbol for grammar
 */
%start      N_START

/*
 *  Translation rules.
 */
%%
N_START         : N_PROG
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
      
      //define variable arrays
      
      for (auto i : arrayVariables)
      {
        s += i.name;
        s += ": .DW &";
        s += i.name;
        s += "[";
        s += i.size;
        s += "]\n";
      }
      
      s += $1; //this inserts the entire actual program code that was generated before
            
      //put constant arrays at the very end of code memory
      
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
      outpu.open("Output.asm"); //output all of this to a file
      outpu << s;
      outpu.close();
      
      
			printf("\n--- Completed parsing ---\n\n");
      
      //Clean up dynamically allocated memory
      
      for (auto thing : memory)
      {
        if (thing)
          delete[] thing;
      }
			return 0;
			}
                ;
N_ADDOP         : T_PLUS
			{
			prRule("N_ADDOP", "+");
      $$ = "+";
			}
                | T_MINUS
			{
			prRule("N_ADDOP", "-");
      $$ = "-";
			}
      
                ;
N_ADDOPLST      : /* epsilon */
			{
			prRule("N_ADDOPLST", "epsilon");
      $$ = "";
			}
                | N_ADDOP N_TERM N_ADDOPLST
			{
			prRule("N_ADDOPLST", 
				 "N_ADDOP N_TERM N_ADDOPLST");
      
      
      char* newWord = new char[strlen($2)+strlen($3)+2];
      
      strcpy(newWord, $1);
      strcat(newWord, $2);
      if ($3!="")
      { 
        strcat(newWord, $3);
      }
      
      $$ = newWord;
      
      memory.push_back(newWord);         
         
			}
                ;
N_ARRAYVAR      : N_ENTIREVAR
			{
			prRule("N_ARRAYVAR", "N_ENTIREVAR");      
      $$ = $1;      
			}
                ;
N_ASSIGN        : N_VARIABLE T_ASSIGN N_SIMPLEEXPR
			{
			prRule("N_ASSIGN", "N_VARIABLE = N_SIMPLEEXPR");  
      
      //cout << "Assignment:" << endl;
      
      
      string s = $1;
      if (s.find("[")==string::npos)
      {
        string code = genaddopcode($3);
      
        code += "STA $";
        code += $1;
        code += "\n";
        
        char* newWord = new char[code.size()+1];
        
        strcpy(newWord, code.c_str());
        
        $$ = newWord;
        
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
        code += genaddopcode($3);        
        code += "POPC\n";
        code += "STARAMC\n";
        
        char* newWord = new char[code.size()+1];
        
        strcpy(newWord, code.c_str());
        
        $$ = newWord;
        
        memory.push_back(newWord);   
        
      }
      
      
			}
                ;
N_BLOCK         : T_LCURLY N_VARDECPART N_STMTLST 
			  N_RETURN T_SCOLON T_RCURLY
			{
			prRule("N_BLOCK", 
			       "{ N_VARDECPART N_STMTLST "
				 "N_RETURN ; }");
         
         
         
         string c = $3;
         
         if (getIdentifierType($4)!="void")
         {
           c += genaddopcode($4);
         }
         
         
         
         c += "RET\n";
         
         char* newWord = new char[c.size()+1];
         
         strcpy(newWord, c.c_str());
      
         $$ = newWord;
        
         memory.push_back(newWord);    
         
         
			}
      | N_COMPOUND
      {
        prRule("N_BLOCK", "N_COMPOUND");
        
        
         
         string c = $1;
                  
         c += "RET\n";
         
         char* newWord = new char[c.size()+1];
         
         strcpy(newWord, c.c_str());
      
         $$ = newWord;
        
         memory.push_back(newWord);    
         
        
      };
                
N_COMPOUND      : T_LCURLY N_VARDECPART N_STMTLST T_RCURLY
			{
			prRule("N_COMPOUND", 
			       "{ N_VARDECPART N_STMTLST }");
             
      $$ = $3;
      
			}
                ;
N_CONDITION     : N_COND_IF_THEN N_STMT
			{
			prRule("N_CONDITION", 
			       "N_COND_IF_THEN N_THEN_STMT");
             
         string s = $1.v.s;           
           
         string a, b;
         
         if ($1.v.i==-1)
         {
           //cout << "Compare to 0" << endl;
           
             a=$1.v.s;             
             b="0";
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord); 
           
         }
         else
         { 
           //cout << "Relational" << endl;
  
           
           
           if ($1.v.i==0) //<
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
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
           
           }
           else if ($1.v.i==1) //>
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
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==2) //<=
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
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==3) //>=
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
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==4) //==
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
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==5) //!=
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
             code += $2;             
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
             
           }
         }
          ifcount++;
             
			}
                |  
			N_COND_IF_THEN N_STMT T_ELSE N_STMT 
			{
			prRule("N_CONDITION", 
			       "N_COND_IF_THEN "
			       "else N_STMT");
             
             
         string s = $1.v.s;           
           
         string a, b;
         
         if ($1.v.i==-1)
         {
           //cout << "Compare to 0" << endl;
           
             a=$1.v.s;             
             b="0";
                          
             string code = genaddopcode(a);
             code += "PUSHA\n";
             code += genaddopcode(b);
             code += "MOVAB\n";
             code += "POPA\n";
             code += "CMP\n";
             code += "JZI ifskp"+std::to_string(ifcount);
             code += "\n";
             code += $2;  
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord); 
           
         }
         else
         { 
           //cout << "Relational" << endl;
  
           
           
           if ($1.v.i==0) //<
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
             code += $2;             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
           
           }
           else if ($1.v.i==1) //>
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
             code += $2;             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==2) //<=
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
             code += $2;             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==3) //>=
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
             code += $2;             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==4) //==
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
             code += $2;             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($1.v.i==5) //!=
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
             code += $2;             
             code += "JMP if2skp"+std::to_string(ifcount);
             code += "\n";
             code += "ifskp";
             code += std::to_string(ifcount);
             code += ": ";
             code += $4;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
             
           }
         }
          ifcount++;       
			}
			;
N_COND_IF_THEN  : T_IF T_LPAREN N_EXPR T_RPAREN
			{
			prRule("N_COND_IF_THEN", "if ( N_EXPR )");
      
      $$.v.s = $3.v.s;
      $$.v.i = $3.v.i;
      
			}
			;
N_CONST         : N_SIGN T_INTCONST
			{
			prRule("N_CONST", "N_SIGN T_INTCONST");
      $$.type = INT;
      
      $$.v.i = $1 * stoi($2);      
			}                
                ;
N_CONSTDEC  	: T_CONST T_IDENT T_ASSIGN N_CONST 
			  T_SCOLON
			{
			prRule("N_CONSTDECPART",
			       "const T_IDENT = N_CONST ;");             
      
      string s = $2;
      s += "[";
      s += std::to_string($4.v.i);
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
    
      $$ = newWord;      
      memory.push_back(newWord);  
      
			}
      |     T_CONST T_INT N_IDENT T_ASSIGN T_LCURLY N_CONST N_CONSTLST T_RCURLY T_SCOLON
      {
        prRule("N_CONSTDEC", "const int IDENT = { CONSTLST };");   
        
        
        string s = $3;
        s = s.substr(0, s.find("["));
        s += "{";
        s += std::to_string($6.v.i);
        
        if ($7!="")
        {
          s += ",";
        }
        
        s += $7;
        s += "}";
      
        //cout << "CONST ARRAY DEC: " << s << endl;
      
        char* newWord = new char[s.size()+1];
      
        strcpy(newWord, s.c_str());
    
        $$ = newWord;      
        memory.push_back(newWord);  
        
        
      }
                ;
N_CONSTLST    :     
      {
        $$ = "";
        prRule("N_CONSTLST", "epsilon");   
      }         
      | T_COMMA N_CONST N_CONSTLST
      {
        prRule("N_CONSTLST", ", const constlst");   
        
        string s = std::to_string($2.v.i);
        
        if ($3!="")
        {
          s += ",";
        }
        s += $3;
        
        char* newWord = new char[s.size()+1];
      
        strcpy(newWord, s.c_str());
    
        $$ = newWord;      
        memory.push_back(newWord); 
        
      }
      
N_ENTIREVAR     : N_VARIDENT
			{
			prRule("N_ENTIREVAR", "N_VARIDENT");   
      $$ = $1;      
			}
                ;
N_EXPR          : N_SIMPLEEXPR
			{
			prRule("N_EXPR", "N_SIMPLEEXPR");
      
      $$.v.s = $1;
      $$.v.i=-1;
      
			}
                | N_SIMPLEEXPR N_RELOP N_SIMPLEEXPR
			{
			prRule("N_EXPR", 
			       "N_SIMPLEEXPR N_RELOP N_SIMPLEEXPR"); 

             string s = $1;
             s += $2.v.s;
             s += $3;
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             memory.push_back(newWord);
             
             $$.v.s = newWord;
             $$.v.i = $2.v.i;

             
			}
                ;
N_TERM        : N_CONST
			{
			prRule("N_TERM", "N_CONST");
      
      string s = std::to_string($1.v.i);
      
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      memory.push_back(newWord);
      
      $$ = newWord;
      
			}
                | T_LPAREN N_EXPR T_RPAREN
			{
			prRule("N_TERM", "( N_EXPR )");
      
      char* newWord = new char[strlen($2.v.s)+3];
      
      strcpy(newWord, "(");
      strcat(newWord, $2.v.s);
      strcat(newWord, ")");
      
      
      
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}     
			| T_IDENT
			{
			prRule("N_TERM", "T_IDENT");
      $$ = $1;
			}
			| T_PLUS T_IDENT
			{
			prRule("N_TERM", "+ T_IDENT");
      
      string s = "+";
      s += $2;
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
			| T_MINUS T_IDENT
			{
			prRule("N_TERM", "- T_IDENT");
      
      char* newWord = new char[strlen($2)+1];
      
      strcpy(newWord, "-");
      strcat(newWord, $2);      
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
			| T_IDENT T_LBRACK N_EXPR T_RBRACK
			{
			prRule("N_TERM", "T_IDENT [ N_EXPR ]");           
      
      string s = $1;
      s += "[";
      s += $3.v.s;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());       
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
			| T_PLUS T_IDENT T_LBRACK N_EXPR T_RBRACK
			{
			prRule("N_TERM", "+ T_IDENT [ N_EXPR ]");
      
      string s = "+";
      s += $2;
      s += "[";
      s += $4.v.s;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());       
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
			| T_MINUS T_IDENT T_LBRACK N_EXPR T_RBRACK
			{
			prRule("N_TERM", "- T_IDENT [ N_EXPR ]");
      
      string s = "-";
      s += $2;
      s += "[";
      s += $4.v.s;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());       
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
			| T_IDENT T_LPAREN T_RPAREN
			{
			prRule("N_TERM", "T_IDENT ( )");
      
      char* newWord = new char[strlen($1)+3];
            
      strcpy(newWord, $1);
      strcat(newWord, "(");
      strcat(newWord, ")");
      
      
      
      
      $$ = newWord;
      
      memory.push_back(newWord);
			}
			| T_PLUS T_IDENT T_LPAREN T_RPAREN      
			{
			prRule("N_TERM", "+ T_IDENT ( )");
      
      string s = "+";
      s += $2;
      s += "()";
      
      char* newWord = new char[s.size()+1];
            
      strcpy(newWord, s.c_str());
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
			| T_MINUS T_IDENT T_LPAREN T_RPAREN
			{
			prRule("N_TERM", "- T_IDENT ( )");
      
      string s = "-";
      s += $2;
      s += "()";
      
      char* newWord = new char[s.size()+1];
            
      strcpy(newWord, s.c_str());
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
			}
                ;
N_FUNCTIDENT    : T_IDENT
			{
			prRule("N_FUNCTIDENT", "T_IDENT");
      $$ = $1;
      
			}
                ;
N_FUNCTCALL     : N_FUNCTIDENT T_LPAREN T_RPAREN
			{
			prRule("N_FUNCTCALL", "N_FUNCTIDENT ( )");
      $$ = $1;      
			}
                ;
N_GLOBALDEC     : N_CONSTDEC
			{
			prRule("N_GLOBALDEC", "N_CONSTDEC");
      
      string s = $1;
      if (s.find("[")!=string::npos) //regular const
      {
        CONSTANT c;
        
        string s = $1;
        
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
      $$ = "";
			}
			/* Note: Following rules must be specified
				    this way to avoid S/R conflicts
				    that would occur between
				    function and var declarations
			*/
			| T_INT T_IDENT T_LPAREN T_RPAREN N_BLOCK
			{
			prRule("N_GLOBALDEC", 
			       "int T_IDENT ( ) N_BLOCK");
             
        
        
        string c = $2;
        c += ": ";
        c += $5;
               
        
        char* newWord = new char[c.size()+1];
      
        strcpy(newWord, c.c_str());
        
        $$ = newWord;
        
        memory.push_back(newWord);
        
        //cout << $$;
             
			}			
			| T_VOID T_IDENT T_LPAREN T_RPAREN N_BLOCK
			{
			prRule("N_GLOBALDEC", 
				 "void T_IDENT ( ) N_BLOCK");   

        string c = $2;
        c += ": ";
        c += $5;
               
        
        char* newWord = new char[c.size()+1];
      
        strcpy(newWord, c.c_str());
        
        $$ = newWord;
        
        memory.push_back(newWord);

         
			}
			| T_INT N_IDENT N_IDENTLST T_SCOLON
			{
			prRule("N_GLOBALDEC", 
			       "int N_IDENT N_IDENTLST ;");
      string s = $2;
      if (s.find("[")!=string::npos)
      {
        //array
        
        string s;
        s = $2;      
        if ($3.v.s!="")
        {
          s = s + "," + $3.v.s;
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
        
        $$ = "";
        
      }
      else
      {
        string s;
        s = $2;      
        if ($3.v.s!="")
        {
          s = s + "," + $3.v.s;
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
        
        $$ = "";
      }
      
			};
N_IDENT         : T_IDENT N_IDX
			{
			prRule("N_IDENT", "T_IDENT N_IDX"); 
     
      string s = $1;
      s += $2;
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
         
			}
                ;
N_IDENTLST      : /* epsilon */
			{
			prRule("N_IDENTLST", "epsilon");      
      $$.type = STR;
      $$.v.s = "";
			}
                | T_COMMA N_IDENT N_IDENTLST
			{
			prRule("N_IDENTLST", 
			       ", N_IDENT N_IDENTLST");      
             
             
      $$.type = STR;
      
      
      
      char* newWord = new char[strlen($2)+strlen($3.v.s)+2];
      
      strcpy(newWord, $2);
      if ($3.v.s!="")
      {
        strcat(newWord, ",");
        strcat(newWord, $3.v.s);
      }
      
      
      
      
      $$.v.s = newWord;
      
      memory.push_back(newWord);
      
			}
                ;
N_IDX           : /* epsilon */
			{
			prRule("N_IDX", "epsilon");
      $$="";
			}
			| T_LBRACK T_INTCONST T_RBRACK
			{
			prRule("N_IDX", "[ T_INTCONST ]");
      
      
      string s = "[";
      s += $2;
      s += "]";
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      
      
      
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
      
			}
                ;
N_IDXVAR        : N_ARRAYVAR T_LBRACK N_EXPR T_RBRACK
			{
			prRule("N_IDXVAR", "N_ARRAYVAR [ N_EXPR ]");
      
      
      string s = $1;
      s += "[";
      s += $3.v.s;
      s += "]";
      
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      
      
      
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
      
			}
                ;
N_PROG          : N_GLOBALDEC
			{
			prRule("N_PROG", "N_GLOBALDEC");
      
      $$ = $1;
      
			}
			| N_PROG N_GLOBALDEC
			{
			prRule("N_PROG", "N_PROG N_GLOBALDEC");
      
      string s = $1;
      
      s += $2;
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      $$ = newWord;
      
      memory.push_back(newWord);
      
      
			}
                ;
N_RELOP         : T_LT
			{
			prRule("N_RELOP", "<");
      $$.v.s = "<";
      $$.v.i = 0;
			}
                | T_GT
			{
			prRule("N_RELOP", ">");
      $$.v.s = ">";
      $$.v.i = 1;
			}
                | T_LE
			{
			prRule("N_RELOP", "<=");
      $$.v.s = "<=";
      $$.v.i = 2;
			}
                | T_GE
			{
			prRule("N_RELOP", ">=");
      $$.v.s = ">=";
      $$.v.i = 3;
			}
                | T_EQ
			{
			prRule("N_RELOP", "==");
      $$.v.s = "==";
      $$.v.i = 4;
			}
                | T_NE
			{
			prRule("N_RELOP", "!=");
      $$.v.s = "!=";
      $$.v.i = 5;
			}
                ;
N_RETURN      	: T_RETURN T_LPAREN N_RETURNEXPR T_RPAREN 	
			{
			prRule("N_RETURN", "return ( N_RETURNEXPR )");
      $$ = $3.v.s;
			}
      | T_RETURN N_RETURNEXPR
			{
			prRule("N_RETURN", "return N_RETURNEXPR");
      $$ = $2.v.s;
			}
                ;
N_RETURNEXPR    : T_VOID 
			{
			prRule("N_RETURNEXPR", "void");
      $$.v.s = "[void]";
			}
                | N_EXPR
			{
			prRule("N_RETURNEXPR", "N_EXPR");
      $$.v.s = $1.v.s;
      $$.v.i = $1.v.i;
      
			}
                ;
N_SIGN          : /* epsilon */
			{
			prRule("N_SIGN", "epsilon");
      $$ = 1;
			}
                | T_PLUS
			{
			prRule("N_SIGN", "+");
      $$ = 1;
			}
                | T_MINUS
			{
			prRule("N_SIGN", "-");
      $$ = -1;
			}
                ;
N_SIMPLEEXPR    : N_TERM N_ADDOPLST
			{
			prRule("N_SIMPLEEXPR", "N_TERM N_ADDOPLST");
      
      //cout << $1 << " : " << $2 << endl;
      
      char* newWord = new char[strlen($1)+strlen($2)+1];
      
      
      
      
      strcpy(newWord, $1);
      strcat(newWord, $2);
      
      $$ = newWord;
      
      memory.push_back(newWord);          
      
			}
                ;
N_STMT          : N_ASSIGN T_SCOLON
			{
			prRule("N_STMT", "N_ASSIGN ;");
      $$ = $1;
			}
                | N_FUNCTCALL T_SCOLON
			{
			prRule("N_STMT", "N_FUNCTCALL ;");
      
      string s = "CALL ";
      s += $1;
      s += "\n";
      
      char* newWord = new char[s.size()+1];
      
      
      
      
      strcpy(newWord, s.c_str());      
      
      $$ = newWord;
      
      memory.push_back(newWord);       
      
			}
                | N_WRITE T_SCOLON
			{
			prRule("N_STMT", "N_WRITE ;");
      $$ = $1;
			}
                | N_CONDITION
			{
			prRule("N_STMT", "N_CONDITION");
      $$ = $1;
			}
                | N_WHILE 
			{
			prRule("N_STMT", "N_WHILE");
      $$ = $1;
			}
                | N_COMPOUND
			{
			prRule("N_STMT", "N_COMPOUND");
      $$ = $1;
			}
                | N_SETVRAM T_SCOLON
      {
      prRule("N_STMT", "N_SETVRAM ;");  
        $$ = $1;
      }
      | T_FLIP T_SCOLON
      {
        prRule("N_STMT", "N_FLIP ;");  
        $$ = "FLIP\n";
      }
      | N_GOTO T_SCOLON
      {
        prRule("N_STMT", "N_GOTO ;");          
        $$ = $1;               
      }
      | T_IDENT T_COLON
      {
        prRule("N_STMT", "N_IDENT :");   
        string s = $1;
        s += ": ";
        
        char* newWord = new char[s.size()+1];
      
      
        strcpy(newWord, s.c_str());      
        $$ = newWord;      
        memory.push_back(newWord); 
        
      }
      | N_IOIN T_SCOLON
      {
        prRule("N_STMT", "N_IOIN ;");   
        $$ = $1;  
      }
      | N_RETURN T_SCOLON
      {
        prRule("N_STMT", "N_RETURN ;");   
        string s = "";
        if (getIdentifierType($1)!="void")
        {
          s += genaddopcode($1);
        }
        s += "RET\n";
        
        char* newWord = new char[s.size()+1];
      
      
        strcpy(newWord, s.c_str());      
        $$ = newWord;      
        memory.push_back(newWord); 
      }
                ;
N_GOTO    : T_GOTO T_IDENT
      {
          prRule("N_GOTO", "T_GOTO T_IDENT");
          
          string s = "JMP ";
          s += $2;
          s += "\n";
          
          char* newWord = new char[s.size()+1];
      
          strcpy(newWord, s.c_str());      
          $$ = newWord;      
          memory.push_back(newWord);           
      }                
N_STMTLST       : N_STMT 
			{
			prRule("N_STMTLST", "N_STMT");
      $$ = $1;      
			}
                | N_STMT N_STMTLST
			{
			prRule("N_STMTLST", "N_STMT N_STMTLST");
      
      string s = $1;
      s += $2;
      
      char* newWord = new char[s.size()+1];
      
      strcpy(newWord, s.c_str());
      
      $$ = newWord;      
      memory.push_back(newWord);              
           
			}
                ;
N_VARDEC        : T_INT N_IDENT N_IDENTLST 
			{
			prRule("N_VARDEC", 
				 "T_INT N_IDENT N_IDENTLST");
         yyerror("No.");
			}
                ;
N_VARDECPART    : /* epsilon */
			{
			prRule("N_VARDECPART", "epsilon");
			}
                | N_VARDEC T_SCOLON N_VARDECPART
			{
			prRule("N_VARDECPART",
			       "N_VARDEC ; N_VARDECPART");
			}
                ;
N_VARIABLE      : N_ENTIREVAR
			{
			prRule("N_VARIABLE", "N_ENTIREVAR");
      $$ = $1;
			}
                | N_IDXVAR
			{
			prRule("N_VARIABLE", "N_IDXVAR");
      $$ = $1;
			}
                ;
N_VARIDENT      : T_IDENT
			{
			prRule("N_VARIDENT", "T_IDENT");
      $$ = $1;
			}
                ;
N_WHILE         : T_WHILE T_LPAREN N_EXPR T_RPAREN N_STMT
			{
			prRule("N_WHILE", 
				 "T_WHILE ( N_EXPR ) N_STMT");
         
         string s = $3.v.s;           
           
         string a, b;
         
         if ($3.v.i==-1)
         {
           //cout << "Compare to 0" << endl;
           
           
           //cout << "Not equal" << endl;
             a=$3.v.s;             
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
             code += $5;
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
            
             $$ = newWord;      
             memory.push_back(newWord); 
           
           
           
         }
         else
         {
           
           
           
           //cout << "Relational" << endl;
  
           
           
           if ($3.v.i==0) //<
           { 
           
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
             code += $5;
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
            
             $$ = newWord;      
             memory.push_back(newWord);     
             
             
           }
           else if ($3.v.i==1) //>
           {
             
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
             code += $5;
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
            
            
              
            
             $$ = newWord;      
             memory.push_back(newWord); 
             
             
             
             
           }
           else if ($3.v.i==2) //<=
           {
             
             
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
             code += $5;
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
            
            
              
            
             $$ = newWord;      
             memory.push_back(newWord); 
             
             
           }
           else if ($3.v.i==3) //>=
           {
             
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
             code += $5;
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
            
             $$ = newWord;      
             memory.push_back(newWord);    
             
             
           }
           else if ($3.v.i==4) //==
           {
             
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
             code += $5;
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
            
             $$ = newWord;      
             memory.push_back(newWord);  
             
           }
           else if ($3.v.i==5) //!=
           {
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
             code += $5;
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
            
             $$ = newWord;      
             memory.push_back(newWord); 
           }

           
         }
         
        loopcount++;
         
			}
                ;
N_WRITE        : T_WRITE T_LPAREN N_EXPR T_RPAREN 
			{
			prRule("N_WRITE", 
			       "write ( N_EXPR )");
             
             string s = genaddopcode($3.v.s);
             
             s += "MOVAC\n";
             s += "VRCC\n";
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             $$ = newWord;      
             memory.push_back(newWord);   
             
             
			}
                ;
N_SETVRAM     : T_VRAMMAR T_LPAREN N_EXPR T_RPAREN
      {
          prRule("N_SETVRAM", 
			       "vrammar ( N_EXPR )");
             
             
             string s = genaddopcode($3.v.s);
             
             s += "VMARA\n";
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             $$ = newWord;      
             memory.push_back(newWord);     
             
             
      };
N_IOIN     : T_IOIN T_LPAREN N_VARIABLE T_RPAREN
      {
          prRule("N_IOIN", 
			       "ioin ( N_VARIABLE )");
             
             
             string s = "LDAIO\n";
             s += "STA $";
             s += $3;
             s += "\n";
             
             char* newWord = new char[s.size()+1];
      
             strcpy(newWord, s.c_str());
            
             $$ = newWord;      
             memory.push_back(newWord);     
             
             
      }

%%

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


