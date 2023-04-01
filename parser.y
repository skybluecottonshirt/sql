%{
#include <stdio.h>
#include <stdlib.h> 
#include "common.h"
int yyerror( const char* ) ; 

%}
%union { 
	int   ival; 
	char* sval; 
}

%token SELECT FROM SEMICOLON NAME COMMA CREATE INSERT 
%token INT TEXT VALUES OPENBR CLOSEBR TABLE
%type <sval> NAME  item_name table_name 
%type <ival> SELECT pair_init 
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


create_statement : CREATE TABLE table_name OPENBR pair_init_values CLOSEBR SEMICOLON { 
		create_table($3); 
	}
pair_init_values : pair_init { 
	} 
	| pair_init_values COMMA pair_init { 
	}

pair_init : INT item_name { 
		insert_parameter($2 , INT); 
	} 
	| TEXT item_name { 
		insert_parameter($2 , TEXT);
	}


item_names : item_name { 

	}
	| item_names COMMA item_name { 

	}

item_name : NAME { 
		$$=$1; 
	}
 
table_name : NAME { 
		$$=$1;
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
