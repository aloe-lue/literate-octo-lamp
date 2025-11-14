#ifndef QUEUE_LINKED_LIST_H
#define QUEUE_LINKED_LIST_H

#include "hash_set.h"

typedef struct queue_linked_list {
        list_node *head;
        list_node *tail;
        int size;
} queue_linked_list;


queue_linked_list *init_queue_linked_list();


list_node *create_queue_list_node(int keys[2]);


void enqueue_list_node(queue_linked_list **q_list, int keys[2]);


void dequeue_list_node(queue_linked_list **q_list);


list_node *front_list_node(queue_linked_list **q_list, int error_num[2]);

#endif
