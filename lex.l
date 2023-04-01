
%{ 
#include "y.tab.h"
#include <stdio.h> 
#include <stdlib.h> 

%}

%%


"select" { return SELECT; } 
"create" { return CREATE; }
"table"  { return TABLE; } 
"insert" { return INSERT; } 
"values" { return VALUES; }
"int"    { return INT; }
"text"   { return TEXT; } 
"into"	 { return INTO; }
"from"   { return FROM; } 
","      { return COMMA; } 
"{"      { return OPENBR; } 
"}" 	 { return CLOSEBR; } 
"(" 	 { return OPENPR; }
")"   	 { return CLOSEPR; }

[_a-zA-Z][_0-9a-zA-Z]* { 
		yylval.sval = strdup(yytext);
		return NAME;
	} 

\"(\\.|[^\"])*\" { 
		yylval.sval = strdup(yytext);
		return TEXT_DATA;
	}

[0-9]+	{
		yylval.ival = atoi(yytext); 
		return INT_DATA;
	}

";"	{ return SEMICOLON; }
. 	{} // ignore case 
%%


int yywrap() { return 1; }
