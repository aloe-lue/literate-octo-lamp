#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
/**
 * contain any type 
 * next self refferencing node 
 *
 */
typedef struct list_node {
        char *key;
        char *data;
        struct list_node *next;
} list_node;


list_node *create_node(char *key, char *data);

/**
 * add node at the end of the list
 *
 * @params head and data
 *
 */
void append_node(list_node **head, char *key, char *data);

/**
 * add node at the beginning of the list
 *
 * @params head and data
 */
void preppend_node(list_node **head, char *key, char *data);

/**
 * created node have used malloc so use this to free them
 *
 * @param head
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
void print_nodes_key_value(list_node **head);

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
 * @params head and data
 */
int find_node_by_data(list_node **head, char *data);

/**
 * returns the index of the node, well i don't know why but why?
 *
 * @params head and data
 */
int find_node_by_key(list_node **head, char *key);
/**
 * returns true or false wether or not the data exist
 * 
 * @params head and data
 *
 */
bool contains_node(list_node **head, char *data);

/**
 *  insert the node at specific index
 *
 *  @params head, data, and index
 *
 */
void insert_node_at(list_node **head, char *key, char *data, int idx);

/**
 * remove the node at specific index
 *
 * @params head, data, and index
 */
void remove_node_at(list_node **head, int idx);

/**
 * remove node at head
 *
 * @params head
 */
void remove_node_head(list_node **head);

#endif
