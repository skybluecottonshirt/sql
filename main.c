#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

enum field  { 
	INT , 
	TEXT
}; 

struct table { 
	int          nf; /* num fields */ 
	char**       name; /* name of the field */ 
	enum field   ft; /* field type */ 
	void**       data;
	int 	     nr;  /* num rows */ 
	int          len;  /* nf * nr */ 
}; 


/* accepts number of bytes and gives off that many bytes */ 
void* allocate(int size) { 
	static int buffer[0xffff]; 
	static int cur_size = 0 ; 
	cur_size += size; 
	return buffer + cur_size - size; 
}

/* given a arbitrary string , this will allocate it into our custom allocator and return address */ 
char* local_string(char *s) { 
	int l = strlen(s); 
	char *res = (char*) allocate(sizeof(char) * l ); 
	strncpy(res , s , l ) ; 
	return res; 
}

void insert(struct table *t , char* d ) {
	t->data[t->len] = d; 
	t->len++;
} 

void print(struct table *t ) { 
	for (int i = 0 ;i < t->len ; i++) { 
		printf("%s\n" , t->data[i]) ; 
	}
}

int main() { 

//	struct table *t = (struct table*) allocate(sizeof(table)); 
//	t->nf = 2; 
//	t->name = (char**) allocate(2) ; 
//
//	t->name[0] = "student_name" ; 
//	t->name[1] = "student_age" ; 
//
//	t->data = (void**) allocate(0xff);  /* max fields */ 
//	insert(t, local_string("asdf"));
//	insert(t, local_string("b")); 
//	
//	print(t); 
//	return 0 ; 
}
