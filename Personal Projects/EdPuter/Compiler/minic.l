/* 
 * Lexical Analyzer Using Flex
*/
%{

%}

QUOTE			'
UNDERSCORE		_

WSPACE		[ \t\r]+
NEWLINE          \n

SIGN			[+-]
COUNT_DIGIT	[1-9]
DIGIT			0|{COUNT_DIGIT}

LO_ALPHA		[a-z]
HI_ALPHA		[A-Z]
ALPHA			{LO_ALPHA}|{HI_ALPHA}

ALPHANUM		{ALPHA}|{DIGIT}

VALIDINT		(0*{COUNT_DIGIT}{DIGIT}{0,8})|(0*)
MAYBEINT		0*{COUNT_DIGIT}{DIGIT}{9,9}
INVALINT		0*{COUNT_DIGIT}{DIGIT}*

IDENT			({UNDERSCORE}|{ALPHA})({ALPHANUM}|{UNDERSCORE})*

CHARCONST		{QUOTE}.{QUOTE}
BADCHARCONST	{QUOTE}|{QUOTE}{QUOTE}

DOUBLEQUOTE	"\""
INT_FORMAT		{DOUBLEQUOTE}"%d"{DOUBLEQUOTE}
CHAR_FORMAT	{DOUBLEQUOTE}"%c"{DOUBLEQUOTE}
INT_NL_FORMAT	{DOUBLEQUOTE}"%d\\n"{DOUBLEQUOTE}
CHAR_NL_FORMAT	{DOUBLEQUOTE}"%c\\n"{DOUBLEQUOTE}


%%

"//".* 	 	{ 	/* skip over this type of comment */
			}			
"/*" 			{
				/* check for comment; if so, skip it */
				ignoreComment();
			}
"("			{
				printTokenInfo("T_LPAREN", yytext);
				return T_LPAREN;
			}
")"			{
				printTokenInfo("T_RPAREN", yytext);
				return T_RPAREN;
			}
"*"			{
				printTokenInfo("T_MULT", yytext);
				return T_MULT;
			}
"+"			{
				printTokenInfo("T_PLUS", yytext);
				return T_PLUS;
			}
","			{
				printTokenInfo("T_COMMA", yytext);
				return T_COMMA;
			}
"-"			{
				printTokenInfo("T_MINUS", yytext);
				return T_MINUS;
			}
"="			{
				printTokenInfo("T_ASSIGN", yytext);
				return T_ASSIGN;
			}
";"			{
				printTokenInfo("T_SCOLON", yytext);
				return T_SCOLON;
			}
"<"			{
				printTokenInfo("T_LT", yytext);
				return T_LT;
			}
"<="			{
				printTokenInfo("T_LE", yytext);
				return T_LE;
			}
"!="			{
				printTokenInfo("T_NE", yytext);
				return T_NE;
			}
"=="			{
				printTokenInfo("T_EQ", yytext);
				return T_EQ;
			}
">"			{
				printTokenInfo("T_GT", yytext);
				return T_GT;
			}
">="			{
				printTokenInfo("T_GE", yytext);
				return T_GE;
			}
"["			{
				printTokenInfo("T_LBRACK", yytext);
				return T_LBRACK;
			}
"]"			{
				printTokenInfo("T_RBRACK", yytext);
				return T_RBRACK;
			}
"&&"			{
				printTokenInfo("T_AND", yytext);
				return T_AND;
			}
"{"			{
				printTokenInfo("T_LCURLY", yytext);
				return T_LCURLY;
			}
"&"			{
				printTokenInfo("T_ADDR", yytext);
				return T_ADDR;
			}
":"			{
				printTokenInfo("T_COLON", yytext);
				return T_COLON;
			}      
"ioin"    {
        printTokenInfo("T_IOIN", yytext);
				return T_IOIN;
      }      
"bool"		{
				printTokenInfo("T_BOOL", yytext);
				return T_BOOL;
			}
"char"		{
				printTokenInfo("T_CHAR", yytext);
				return T_CHAR;
			}
"goto"		{
				printTokenInfo("T_GOTO", yytext);
				return T_GOTO;
			}
"const"		{
				printTokenInfo("T_CONST", yytext);
				return T_CONST;
			}
"/"			{
				printTokenInfo("T_DIV", yytext);
				return T_DIV;
			}
"else"		{
				printTokenInfo("T_ELSE", yytext);
				return T_ELSE;
			}
"}"			{
				printTokenInfo("T_RCURLY", yytext);
				return T_RCURLY;
			}
"false"		{
				printTokenInfo("T_FALSE", yytext);
				return T_FALSE;
			}
"if"			{
				printTokenInfo("T_IF", yytext);
				return T_IF;
			}
"int"			{
				printTokenInfo("T_INT", yytext);
				return T_INT;
			}
"!"			{
				printTokenInfo("T_NOT", yytext);
				return T_NOT;
			}
"||"			{
				printTokenInfo("T_OR", yytext);
				return T_OR;
			}
"scanf"		{
				printTokenInfo("T_SCANF", yytext);
				return T_SCANF;
			}
"true"		{
				printTokenInfo("T_TRUE", yytext);
				return T_TRUE;
			}
"while"		{
				printTokenInfo("T_WHILE", yytext);
				return T_WHILE;
			}
"void"		{
				printTokenInfo("T_VOID", yytext);
				return T_VOID;
			}
"return"		{
				printTokenInfo("T_RETURN", yytext);
				return T_RETURN;
			}
{INT_FORMAT}	{
				printTokenInfo("T_IFORMAT", yytext);
				return T_IFORMAT;
			}
{INT_NL_FORMAT}	{
				printTokenInfo("T_IFORMAT_NL", yytext);
				return T_IFORMAT_NL;
			}
{CHAR_FORMAT}	{
				printTokenInfo("T_CFORMAT", yytext);
				return T_CFORMAT;
			}
{CHAR_NL_FORMAT}	{
				printTokenInfo("T_CFORMAT_NL", yytext);
				return T_CFORMAT_NL;
			}
"write"		{
				printTokenInfo("T_WRITE", yytext);
				return T_WRITE;
			}
"flip"		{
				printTokenInfo("T_FLIP", yytext);
				return T_FLIP;
			}      
"vrammar" {
        printTokenInfo("T_VRAMMAR", yytext);
				return T_VRAMMAR;
      }
{VALIDINT}		{
				printTokenInfo("T_INTCONST", yytext);
        yylval.text = strdup(yytext);
				return T_INTCONST;
			}
{MAYBEINT}		{
				if (ckInt())
				{
				printf("Invalid integer constant: %s\n", 
				       yytext);
				return T_UNKNOWN;
				}
				else
				{
				printTokenInfo("T_INTCONST", yytext);
        yylval.text = strdup(yytext);
				return T_INTCONST;
				}
			}
{INVALINT}		{
				printf("Invalid integer constant: %s\n", 
				       yytext);
				return T_UNKNOWN;
			}
{IDENT}		{
				printTokenInfo("T_IDENT", yytext);
        yylval.text = strdup(yytext);
				return T_IDENT;
			}
{BADCHARCONST}	{
				printf("Invalid character constant: %s\n", 
				       yytext);
				return T_UNKNOWN;
			}
{CHARCONST}	{
				printTokenInfo("T_CHARCONST", yytext);
				return T_CHARCONST;
			}
{NEWLINE}   	{
                		++lineNum;
            	}
{WSPACE}		{ }
.			{
				printTokenInfo("T_UNKNOWN", yytext);
				return T_UNKNOWN;
			}

%%

