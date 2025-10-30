#ifndef QUEUE_SLL_H
#define QUEUE_SLL_H

typedef struct q_list_node {
        int data[2];
        struct q_list_node *next;
} q_list_node;

typedef struct q_linked_list {
        q_list_node *head;
        q_list_node *tail;
        int q_ll_len;
} q_linked_list;

/**
 * init a q linked list
 * @params nothing
 * returns q_linked_list accessible
 */
q_linked_list *create_q_linked_list();
/**
 * create q list node
 *
 * @params int *data
 * returns q_list_node
 */
q_list_node *create_q_list_node(int *data);
/**
 * add to the front of the q_list_node head
 * update the tail of the q_list_node tail
 * if it's not NULL
 *
 * @params q_linked_list
 * returns void
 */
void enqueue_q_list_node(q_linked_list *QLL, int *data);

/**
 * get the tail of the queue
 * remove the tail of the queue
 * update the tail of the queue
 *
 * @params q_linked_list
 * returns a q_list_node of the removed q
 */
int *dequeue_q_list_node(q_linked_list *QLL);

/**
 * get the q_ll_len
 * 
 * @params q_linked_list
 */
int size_q_list_node(q_linked_list *q);

/*
 * print the front q_list_node
 *
 * @params q_linked_list q
 * returns nothing
 */
int *peek_q_list_node_s(q_linked_list *q);

/**
 * you want to destroy all of it after use weird phrasing
 *
 * @params q linked list Qll
 */

void destroy_q_list_node(q_list_node *q);

#endif
