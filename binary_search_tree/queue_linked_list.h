#ifndef QUEUE_SLL_H
#define QUEUE_SLL_H

#include "binary_search_tree.h"
#include "linked_list.h"

/**
 * follows first in first out
 * tail pointer
 */
typedef struct ql_node {
        bst_node *node;
        struct ql_node *next;
} ql_node;

typedef struct bst_qll {
        ql_node *tail;
        ql_node *head;
        int len;
} bst_qll;

/**
 * create queue list node
 * 
 * returns ql_node
 */
ql_node *create_ql_node(bst_node *node);

/**
 * yeah so create bst queue linked list
 *
 * returns bst_qll
 */
bst_qll *create_bst_qll();

/**
 * enqueue bst node in the bst_qll
 *
 * @params bst_qll and bst_node
 */
void bst_qll_enqueue(bst_qll *Q, bst_node *node);

/**
 * dequeue ql node from bst_qll
 *
 * @params bst_qll
 */
void bst_qll_dequeue(bst_qll *Q);

/**
 *  get the front bst 
 *
 */
bst_node *bst_front(bst_qll *Q);

#endif
