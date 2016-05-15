#include "../include/mem_ds.h"
#include <stdio.h>
#include <stdlib.h>

struct node *head = NULL;
void *tail = NULL;


void list_insert(void* ptr, size_t sz)
{
	if (head == NULL)
	{
		head = malloc(sizeof(struct node));
		head->mem_ptr = ptr;
		head->mem_size = sz;
		tail = malloc(sizeof(void*));
	}
	else
	{
		struct node *current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}

		struct node *newptr = malloc(sizeof(struct node));
		newptr->mem_ptr = ptr;
		newptr->mem_size = sz;
		current->next = newptr;
		tail = ptr;
	}
}

void list_show(void)
{
	struct node *current = head;
	printf("Location  :  Size\n");
	while (current != NULL)
	{
		printf("%p   %10llu\n", current->mem_ptr, current->mem_size);
		current = current->next;
	}
}

void list_find(void *ptr, unsigned long long *memsize)
{
	struct node *current = head;

	while (current != NULL)
	{
		if (current->mem_ptr == ptr)
		{
			ptr = current->mem_ptr;
			*memsize = current->mem_size;
			break;
		}

		current = current->next;
	}
}

void list_remove(void *ptr)
{
	struct node *current = head->next;
	struct node *prev = head;

	if (ptr == head->mem_ptr)
	{
		struct node *temp = head;
		head = head->next;

		free(temp);
		temp = NULL;
	}

	while (current != NULL)
	{
		if (current->mem_ptr == ptr)
		{
			prev->next = current->next;
			free(current);
			current = NULL;
		}

		current = current->next;
		prev = prev->next;
	}
}

void list_destroy(void)
{
	while(head != NULL)
	{
		struct node *temp = head;
		head = head->next;

		free(temp);
		temp = NULL;
	}
}

void* list_gettop(void)
{
	return head->mem_ptr;
}

void* list_getend(void)
{
	return tail;
}
