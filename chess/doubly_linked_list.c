#include <stdlib.h>
#include <stdio.h>

#include "doubly_linked_list.h"

dlinked_list *InitDLinkedList()
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

dnode_list *InitDNodeList(chess_square square)
{
	dnode_list *dnl = malloc(sizeof(dnode_list));

	if (dnl == NULL) {
		fprintf(stderr, "malloc err: InitDNodeList. ");
		exit(EXIT_FAILURE);
	}
	
	dnl->square = square;
	dnl->next = NULL;
	dnl->prev = NULL;
	
	return dnl;
}

void EnqueueDNodeList(dlinked_list *dll, chess_square square)
{
	dnode_list *new_dnl = InitDNodeList(square);
	
	if (dll->dlist_size == 0 || dll->head == NULL) {
		dll->head = new_dnl;
		dll->tail = new_dnl;
		dll->prev_tail = new_dnl;
		dll->dlist_size++;
		return;
	}

	new_dnl->prev = dll->prev_tail;
	dll->prev_tail->next = new_dnl;
	dll->prev_tail = new_dnl;

	dll->tail->next = new_dnl;
	dll->tail = new_dnl;
	dll->dlist_size++;
}

void PrintFromTailDNodeList(dlinked_list *dll)
{
	dnode_list *dnl = dll->tail;

	while (dnl != NULL) {
		// print what you want to debug here.

		dnl = dnl->prev;
	}

	printf("\n");
}


void PrintFromHeadNodeList(dlinked_list *dll)
{
	dnode_list *dnl = dll->head;

	while (dnl != NULL) {
		// print what you want to debug here.

		dnl = dnl->next;
	}
	printf("\n");
}


void PopDNodeList(dlinked_list *dll)
{
	dnode_list *tail = dll->tail;

	if (tail == NULL) {
		fprintf(stderr, "cannot pop an empty dnodelist. ");
		return;
	}

	dll->prev_tail = dll->tail->prev;
	dll->tail = dll->prev_tail;
	
	dll->dlist_size--;
	free(tail);
}

void DequeueDNodeList(dlinked_list *dll)
{
	if (dll->dlist_size == 0) {
		fprintf(stderr, "cannot dequeue empty dnodelist. ");
		return;
	}

	dnode_list *tmp = dll->head;
	dll->head = tmp->next;

	if (dll->head == NULL) {
		dll->tail = NULL;
		dll->prev_tail = NULL;
	}

	dll->dlist_size--;
	free(tmp);
}

void ClearDNodeLists(dlinked_list *dll)
{
	int dlist_size = dll->dlist_size;

	for (int i = 0; i < dlist_size; i++)
		DequeueDNodeList(dll);
}

