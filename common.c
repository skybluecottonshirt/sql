
#include "y.tab.h" // for tokens 
#include "common.h"


struct table_parameter_t { 
	int type;
	char* name; 
} parameter_buffer[0xff]; 


int parameter_buffer_len = 0; 

struct table_t { 
	char* name; 
	int field_count; 
	char* field_name[0xff];
	int field_type[0xff];
	void* data[0xff]; 
} table[0xff]; 
int table_count; 

void insert_parameter(char* name , int type ) {
	parameter_buffer[parameter_buffer_len++] = (struct table_parameter_t) { 
		.type = type, 
		.name = name,
	};
}

void create_table(char* name) { 
	table[table_count].name = name; 
	for(int i = 0 ; i < parameter_buffer_len; i++ )  { 
		table[table_count].field_name[i] = parameter_buffer[i].name;
		table[table_count].field_type[i] = parameter_buffer[i].type; 
	}
	parameter_buffer_len = 0;  // clear this for the next create statements
}
