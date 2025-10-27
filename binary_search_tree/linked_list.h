#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
/**
 * contain any type 
 * next self refferencing node 
 *
 */

typedef struct list_node {
        int key;
        struct list_node *next;
} list_node;

list_node *create_node(int key);

void enqueue_node(list_node **head, int key, list_node **tail);
list_node *dequeue_node();

/**
 * add node at the end of the list
 *
 * @params head and key
 *
 */

void append_node(list_node **head, int key);

/**
 * add node at the beginning of the list
 * every time you use it find the tail node
 *
 * @params head and key
 */
void preppend_node(list_node **head, int key);

/**
 * created node have used malloc so use this to free them
 *
 * @param head size and c_size
 *
 */
void destroy_nodes(list_node **head, int size, const int c_size);

/**
 * print nodes beautifully like so ( node ) -> ( node ) -> NULL
 *
 * @param head
 *
 */
void print_nodes(list_node **head);


/**
 * print nodes beautifully like so (k, v) -> (k, v) -> NULL
 *
 * @param head
 *
 */
void print_nodes_key(list_node **head);

/**
 * return the head node 
 *
 * @param head
 */
void head_node(list_node **head);

/**
 * returns the size of the list 
 *
 * @param head
 */
int nodes_size(list_node **head);

/**
 * returns the index of the node, well i don't know why but why?
 *
 * @params head and key
 */
int find_node_by_key(list_node **head, int key);
/**
 * returns true or false wether or not the data exist
 * 
 * @params head and key 
 *
 */
bool contains_node(list_node **head, int key);

/**
 *  insert the node at specific index
 *
 *  @params head, key, and index
 *
 */
void insert_node_at(list_node **head, int key, int idx);

/**
 * remove the node at specific index
 *
 * @params head, and index
 */
void remove_node_at(list_node **head, int idx);

/**
 * remove node at head
 *
 * @params head
 */
void remove_node_head(list_node **head);

#endif
