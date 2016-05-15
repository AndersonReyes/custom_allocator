#ifndef MEM_DS_H
#define MEM_DS_H
#include <stdlib.h>

struct node
{
	void *mem_ptr;
	unsigned long long mem_size;
	struct node* next;
} ;

void list_insert(void *ptr, size_t sz);
void list_remove(void *ptr);
void list_find(void *ptr, unsigned long long *mem_size);
void list_show(void);
void list_destroy(void);
void* list_gettop(void);
void* list_getend(void);

#endif
