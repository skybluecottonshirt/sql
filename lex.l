
%{ 
#include "y.tab.h"
#include <stdio.h> 
#include <stdlib.h> 

%}

%%


"select" { return SELECT; } 
"create" { return CREATE; }
"insert" { return INSERT; } 
"values" { return VALUES; }
"int"    { return INT; }
"text"   { return TEXT; } 
"from"   { return FROM; } 
","      { return COMMA; } 
"{"      { return OPENBR; } 
"}" 	 { return CLOSEBR; } 

[_a-zA-Z][_0-9a-zA-Z]* { 
		yylval.sval = strdup(yytext);
		return NAME;
	} 

";"	{ return SEMICOLON; }
. 	{} // ignore case 
%%


int yywrap() { return 1; }
