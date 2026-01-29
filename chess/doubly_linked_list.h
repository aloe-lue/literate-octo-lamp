#ifndef DLINKED_LIST_H
#define DLINKED_LIST_H

#include "chess.h"

/*
 * reverse user input to get back to previous
 *
 * also helps with en passant. i hate pawn. ughh
 */
typedef struct dnode_list {
    chess_square square;
    struct dnode_list *next;
    struct dnode_list *prev;
} dnode_list;

/*
 * queue linked list 
 */
typedef struct dlinked_list {
	dnode_list *head;
	dnode_list *tail;
	dnode_list *prev_tail;
	int dlist_size;
} dlinked_list;

/*
 * initialise queue doubly linked list
 */
dlinked_list *InitDLinkedList();

/*
 * auxillary method for enqueueing
 */
dnode_list *InitDNodeList(chess_square square);

/*
 * user input chess notation
 */
void EnqueueDNodeList(dlinked_list *dll, chess_square square);

/* 
 *  removes excessive and/or unnecessary user input moves
 *  or never remove things at all.
 */
void DequeueDNodeList(dlinked_list *dll);

/*
 * clears dnodelist
 */
void ClearDNodeLists(dlinked_list *dll);

/*
 * useful for debug from tail to head
 */
void PrintFromTailDNodeList(dlinked_list *dll);

/*
 * useful for debug from head to tail
 */
void PrintFromHeadDNodeList(dlinked_list *dll);

/*
 * remove dnode_list at the end pointed by tail
 */
void PopDNodeList(dlinked_list *dll);

#endif // doubly_linked_list.h

