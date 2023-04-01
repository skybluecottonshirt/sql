%{
#include <stdio.h>
#include <stdlib.h> 
int yyerror( const char* ) ; 

%}
%union { 
	int   ival; 
	char* sval; 
}

%token SELECT FROM SEMICOLON NAME COMMA CREATE INSERT 
%token INT TEXT VALUES OPENBR CLOSEBR
%type <sval> NAME 
// %type <ival> SELECT 
%start statements 

%% 
statements : single_statement  {
	} | 
	statements single_statement {
	}	

single_statement : select_statement {
	} 
	| create_statement { 
	}


select_statement : SELECT item_names FROM table_name SEMICOLON { 
		printf("found select statement\n"); 
	}


create_statement : CREATE table_name OPENBR pair_init_values CLOSEBR SEMICOLON { 
		printf("found a create statement\n"); 
	}
pair_init_values : pair_init { 
	} 
	| pair_init_values COMMA pair_init { 
	}

pair_init : INT item_name { 
		printf("found an INT item\n");
	} 
	| TEXT item_name { 
		printf("found a TEXT item\n");
	}

item_names : item_name { 

	}
	| item_names COMMA item_name { 

	}

item_name : NAME { 
		printf("found an item with name : %s\n" , yylval.sval); 
	}
 
table_name : NAME { 
		printf("found table name : %s\n", yylval.sval); 
	} 
%% 
int main() { 
	yyparse(); 
	return 0; 
}

extern int yylineno; 
extern char* yytext; 
int yyerror(const char* msg) { 
	printf("error : %d txt : %s\n", yylineno , yytext) ; 
	exit(0); 
	return 0; 
}
