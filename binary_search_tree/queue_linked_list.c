#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "queue_linked_list.h"
#include "binary_search_tree.h"

ql_node *create_ql_node(bst_node *node)
{
        ql_node *q_node = (ql_node *)malloc(sizeof(ql_node));
        if (q_node == NULL) {
                fprintf(stderr, "create_bst_qll func: q_node malloc failed.\n");
                exit(EXIT_FAILURE);
        }
        q_node->node = (bst_node *)malloc(sizeof(bst_node));
        if (q_node->node == NULL) {
                fprintf(stderr, "create_bst_qll func: bst node malloc failed.\n");
                exit(EXIT_FAILURE);
        }
        q_node->node->key = node->key;
        q_node->node->left = node->left;
        q_node->node->right = node->right;
        q_node->next = NULL;
        return q_node;
}

bst_qll *create_bst_qll()
{
        bst_qll *Q = (bst_qll *)malloc(sizeof(bst_qll));
        if (Q == NULL) {
                fprintf(stderr, "create_bst_qll func: malloc failed.\n");
                exit(EXIT_FAILURE);
        }
        Q->tail = NULL;
        Q->head = NULL;
        Q->len = 0;
        return Q;
}

void bst_qll_enqueue(bst_qll *Q, bst_node *node) 
{
        ql_node *new_ql_node = create_ql_node(node);
        if (Q->len == 0) {
                Q->head = Q->tail = new_ql_node;
                Q->len++;
                return;
        }
        Q->tail->next = new_ql_node;
        Q->tail = new_ql_node;
        Q->len++;
}

void bst_qll_dequeue(bst_qll *Q)
{
        if (Q->len == 0) {
                fprintf(stderr, "bst_qll_dequeue: Q empty. \n");
                exit(EXIT_FAILURE);
        }
        ql_node *tmp = Q->head;
        Q->head = tmp->next;
        if (Q->head == NULL)
                Q->tail = NULL;
        Q->len--;
        free(tmp);
}

bst_node *bst_front(bst_qll *Q) 
{
        if (Q == NULL)
                return NULL;
        return Q->head->node;
}
