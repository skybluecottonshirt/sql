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
%token INT TEXT VALUES OPENBR CLOSEBR TABLE TEXT_DATA 
%token OPENPR CLOSEPR INTO  INT_DATA
%type <sval> NAME  item_name table_name  TEXT_DATA
%type <ival> SELECT pair_init INT_DATA
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
	| insert_statement { 
	}


select_statement : SELECT item_names FROM table_name SEMICOLON { 
	}


create_statement : CREATE TABLE table_name OPENBR pair_init_values CLOSEBR SEMICOLON { 
		create_table($3); 
	}

insert_statement : INSERT INTO table_name VALUES OPENPR data_values CLOSEPR SEMICOLON { 
		insert_into_table($3);
	}

data_values : data_value { 	
	}
	| data_values COMMA data_value { 
	}


data_value : INT_DATA  { 
		insert_int_value($1); 
	}
	| TEXT_DATA { 
		insert_text_value($1); 
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
