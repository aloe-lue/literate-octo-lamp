#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "queue_linked_list.h"
#include "hash_set.h"


queue_linked_list *init_queue_linked_list()
{
        queue_linked_list *Q = (queue_linked_list *)malloc(sizeof(queue_linked_list));
        if (Q == NULL) {
                fprintf(stderr, "create queue list node: malloc failed.\n");
                exit(EXIT_FAILURE);
        }
        Q->head = NULL;
        Q->tail = NULL;
        Q->size = 0;
        return Q;
}

list_node *create_queue_list_node(int keys[2])
{
        list_node *node = (list_node *)malloc(sizeof(list_node));
        if (node == NULL) {
                fprintf(stderr, "create queue list node: malloc failed.\n");
                exit(EXIT_FAILURE);
        }
        
        for (int i = 0; i < 2; i++)
                node->keys[i] = keys[i];
        node->next = NULL;
        return node;
}

void enqueue_list_node(queue_linked_list **q_list, int keys[2])
{
        queue_linked_list *Q = *q_list;

        list_node *new_node = create_queue_list_node(keys);
        if ((Q->size == 0 && Q->head == NULL)) {
                Q->head = new_node;
                Q->tail = new_node;
                Q->size++;
                return;
        }
        Q->tail->next = new_node;
        Q->tail = new_node;
        Q->size++;
}

void dequeue_list_node(queue_linked_list **q_list)
{
        queue_linked_list *Q = *q_list;
        if (Q->size == 0)
                return;
        list_node *tmp = Q->head;
        Q->head = tmp->next;
        if (Q->head == NULL)
                Q->tail = NULL;
        Q->size--;
        free(tmp);
}

list_node *front_list_node(queue_linked_list **q_list, int error_num[2])
{
        queue_linked_list *q = *q_list;
        if (q == NULL)
                return NULL;
        return q->head;
}
