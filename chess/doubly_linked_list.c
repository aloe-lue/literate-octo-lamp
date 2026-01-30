#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "doubly_linked_list.h"

dlinked_list *init_dlinked_list()
{
	dlinked_list *list = malloc(sizeof(dlinked_list));

	if (list == NULL) {
		fprintf(stderr, "malloc err: InitDLinkedList");
		exit(EXIT_FAILURE);
	}

	list->head = NULL;
	list->tail = NULL;
	list->dlist_size = 0;

	return list;
}

dnode_list *init_dnode_list(char *data)
{
	dnode_list *dnl = malloc(sizeof(dnode_list));

	if (dnl == NULL) {
		fprintf(stderr, "malloc err: InitDNodeList. ");
		exit(EXIT_FAILURE);
	}

	strcpy(dnl->data, data);	
	dnl->next = NULL;
	dnl->prev = NULL;
	
	return dnl;
}

void enqueue_dnode_list(dlinked_list *dll, char *data)
{
	dnode_list *new_dnl = init_dnode_list(data);
	
	if (dll->dlist_size == 0 || dll->head == NULL) {
		dll->head = new_dnl;
		dll->tail = new_dnl;
		dll->dlist_size++;
		return;
	}

	dnode_list *tmp_tail = dll->tail;

	new_dnl->prev = tmp_tail;
	dll->tail->next = new_dnl;
	dll->tail = new_dnl;
	dll->dlist_size++;
}


void dequeue_dnode_list(dlinked_list *dll)
{
	if (dll->dlist_size == 0) {
		fprintf(stderr, "cannot dequeue empty dnodelist. ");
		return;
	}
	
	dnode_list *tmp_head = dll->head;

	dll->head = tmp_head->next;

	if (dll->head == NULL)
		dll->tail = NULL;
	else
		dll->head->prev = NULL;

	dll->dlist_size--;

	free(tmp_head);
}

void clear_dnode_lists(dlinked_list *dll)
{
	int dlist_size = dll->dlist_size;

	for (int i = 0; i < dlist_size; i++)
		dequeue_dnode_list(dll);
}


void print_from_tail_dnodelist(dlinked_list *dll)
{
	dnode_list *dnl = dll->tail;

	while (dnl != NULL) {
		// print what you want to debug here.
		printf("(%s)<-", dnl->data);

		dnl = dnl->prev;
	}

	printf("nil\n");
}


void print_from_head_dnodelist(dlinked_list *dll)
{
	dnode_list *dnl = dll->head;

	while (dnl != NULL) {
		// print what you want to debug here.
		printf("(%s)->", dnl->data);

		dnl = dnl->next;
	}

	printf("nil\n");
}


void pop_dnode_list(dlinked_list *dll)
{
	dnode_list *tail = dll->tail;

	if (tail == NULL) {
		fprintf(stderr, "cannot pop an empty dnodelist. ");
		return;
	}
	
	dll->tail = tail->prev;
	dll->dlist_size--;

	free(tail);
}

