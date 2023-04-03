
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
	int rows;
} table[0xff]; 
int table_count; 

static char memory[0xffff]; 
int mem_start=0;
char* insert_text_into_mem(char* string) { 
	int sz =  strlen(string);
	// copy step 
	
	for (int i =1 ;i < sz-1;i++)
		memory[mem_start + i - 1]  = string[i];
	memory[mem_start + sz-1] = 0;
	mem_start += sz; 
	return memory + mem_start - sz; 
}

int* insert_int_into_mem(int val) { 
	memory[mem_start] = (char)val; 
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
	table[table_count].field_count = parameter_buffer_len; 
	for(int i = 0 ; i < parameter_buffer_len; i++ )  { 
		table[table_count].field_name[i] = parameter_buffer[i].name;
		table[table_count].field_type[i] = parameter_buffer[i].type; 
	}
	parameter_buffer_len = 0;  // clear this for the next create statements
	table_count++;
}
void* insert_buffer[0xff];
int insert_buffer_size =0 ; 

void insert_int_value(int value )  { 
	insert_buffer[insert_buffer_size++] = (void*)value; 
}
void insert_text_value(char* value) { 
	insert_buffer[insert_buffer_size++] = insert_text_into_mem(value);
}


void insert_into_table(char* table_name) { 
	for (int i = 0 ;i < table_count; i++) { 
		if (strcmp(table_name , table[i].name) == 0 ) { 
			int data_size = table[i].data_size ; 
			for (int j = 0 ; j < insert_buffer_size; j++) { 
				table[i].data[data_size + j ] = insert_buffer[j];
			}
			table[i].data_size += insert_buffer_size; 
			insert_buffer_size = 0 ; 
			table[i].rows++;
		}
		return ;
	}
	// no table found ;

}

void print_all_table(char* name)  { 
	struct table_t *cur_table = NULL;
	for (int i = 0 ;i  < table_count; i++) { 
		if (strcmp(name , table[i].name) ==0) { 
			cur_table = &table[i];
			break;
		}
	}
	if (!cur_table) {  
		printf("no table found\n");
		return; 
	} 
	for (int i =0 ; i < cur_table->field_count; i++) { 
		if (i != 0 ) printf("|");
		printf("%s", cur_table->field_name[i]);
	}
	printf("\n");
	for (int i = 0 ; i < cur_table->rows ; i++) { 
		for (int j = 0 ; j < cur_table->field_count; j++) { 
			if (j != 0 ) printf("|");
			if (cur_table->field_type[j] == INT) { 
				printf("%d",  (int)cur_table->data[ i * cur_table->field_count+j]); 
			} else { 
				printf("%s", (char*)cur_table->data[ i * cur_table->field_count+j]); 
			}
		}
		printf("\n");
	}
}
