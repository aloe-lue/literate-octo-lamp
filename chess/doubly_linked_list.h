#ifndef DLINKED_LIST_H
#define DLINKED_LIST_H

#define MAXNOTATION 100
/*
 * reverse user input to get back to previous
 *
 * also helps with en passant. i hate pawn. ughh
 */

typedef struct dnode_list {
	char data[MAXNOTATION]; 
	struct dnode_list *next;
	struct dnode_list *prev;
} dnode_list;

/*
 * queue linked list 
 */
typedef struct dlinked_list {
	dnode_list *head;
	dnode_list *tail;
	int dlist_size;
} dlinked_list;

/*
 * initialise queue doubly linked list
 */
dlinked_list *init_dlinked_list();

/*
 * auxillary method for enqueueing
 */
dnode_list *init_dnode_list(char *data);

/*
 * user input chess notation
 */
void enqueue_dnode_list(dlinked_list *dll, char *data);

/* 
 *  removes excessive and/or unnecessary user input moves
 *  or never remove things at all.
 */
void dequeue_dnode_list(dlinked_list *dll);

/*
 * clears dnodelist
 */
void clear_dnode_lists(dlinked_list *dll);

/*
 * useful for debug from prevtail to head
 */
void print_from_prev_tail_dnodelist(dlinked_list *dll);
/*
 * useful for debug from tail to head
 */
void print_from_tail_dnodelist(dlinked_list *dll);

/*
 * useful for debug from head to tail
 */
void print_from_head_dnodelist(dlinked_list *dll);

/*
 * remove dnode_list at the end pointed by tail
 */
void pop_dnode_list(dlinked_list *dll);

#endif // doubly_linked_list.h

