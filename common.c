
#include "y.tab.h" // for tokens 
#include <string.h>
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
	int data_size; 
} table[0xff]; 
int table_count; 

static int memory[0xffff]; 
int mem_start=0;
char* insert_text_into_mem(char* string) { 
	int sz =  strlen(string);
	// copy step 
	for (int i =0 ;i < sz;i++)
		memory[mem_start + i] = string[i];
	mem_start += sz; 
	return memory + mem_start - sz; 
}

int* insert_int_into_mem(int val) { 
	memory[mem_start] = val; 
	mem_start += 1;
	return memory + mem_start - 1 ; 
}
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
void* insert_buffer[0xff];
int insert_buffer_size =0 ; 

void insert_int_value(int value )  { 
	insert_buffer[insert_buffer_size++] = insert_int_into_mem(value);
}
void insert_text_value(char* value) { 
	insert_buffer[insert_buffer_size++] = insert_text_into_mem(value);
}


void insert_into_table(char* table_name) { 
	for (int i = 0 ;i < table_count; i++) { 
		if (strcmp(table_name , table[i].name) == 0 ) { 
			int data_size = table[i].data_size ; 
			for (int i = 0 ; i < insert_buffer_size; i++) { 
				table[i].data[data_size + i ] = insert_buffer[i];
			}
		}
		return ;
	}
	// no table found ;

}

