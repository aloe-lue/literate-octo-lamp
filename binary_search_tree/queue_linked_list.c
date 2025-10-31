#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "queue_linked_list.h"
#include "binary_search_tree.h"

q_list_node *create_q_list_node(int *data)
{
        q_list_node *qln = (q_list_node *)malloc(sizeof(q_list_node));
        if (qln == NULL) {
                puts("malloc error: create_q_list_node func. \n");
                return qln;
        }
        for (int i = 0; i < 2; i++)
                qln->data[i] = data[i];
        qln->next = NULL;
        return qln;
}

q_linked_list *create_q_linked_list()
{
        q_linked_list *QLL = (q_linked_list *)malloc(sizeof(q_linked_list));
        QLL->head = NULL;
        QLL->tail = NULL;
        QLL->q_ll_len = 0;
        return QLL;
}

void enqueue_q_list_node(q_linked_list *QLL, int *data)
{
        q_list_node *new_q_list_node = create_q_list_node(data);
        if (new_q_list_node == NULL) {
                puts("malloc failed on enq func. \n");
                return;
        }
        if (QLL->tail == NULL) {
                QLL->head = QLL->tail = new_q_list_node;
                QLL->q_ll_len++;
                return;
        }
        QLL->tail->next = new_q_list_node;
        QLL->tail = new_q_list_node;
        QLL->q_ll_len++;
        return;
}

int *dequeue_q_list_node(q_linked_list *QLL)
{       
        int *value;
        if (QLL->q_ll_len == 0) {
                value = (int *)malloc(2 * sizeof(int));
                if (value == NULL) {
                        fprintf(stderr, "malloc failed: dequeue func");
                        exit(EXIT_FAILURE);
                }
                for (int i = 0; i < 2; i++)
                        value[i] = -1;
                return value;
        }
        q_list_node *tmp = QLL->head;
        QLL->head = tmp->next;
        if (QLL->head == NULL) {
                QLL->tail = NULL;
        }
        value = (int *)malloc(2 * sizeof(int));
        if (value == NULL) {
                fprintf(stderr, "malloc failed: dequeue func");
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 2; i++)
                value[i] = tmp->data[i];
        QLL->q_ll_len--;
        free(tmp);
        return value;
}

int size_q_list_node(q_linked_list *QLL)
{
        return QLL->q_ll_len;
}

int *peek_q_list_node_s(q_linked_list *QLL)
{
        return QLL->head->data;
}

void destroy_q_list_node(q_list_node *q)
{
        if (q->next == NULL) {
                return;
        }
        destroy_q_list_node(q->next);
        free(q);
}

/**
 * down here is for queue for bst
 */
bst_q_tree *bst_q_create()
{
        bst_q_tree *q_tree = (bst_q_tree *)malloc(sizeof(bst_q_tree));
        if (q_tree == NULL) {
                fprintf(stderr, "dequeue_bst_q_node: q is empty.");
                exit(EXIT_FAILURE);
        }
        q_tree->head = NULL;
        q_tree->tail = NULL;
        q_tree->size = 0;
        return q_tree;
}

void enqueue_bst_q_node(bst_q_tree *tree, bst_node *node) 
{
        if (tree->tail == NULL) {
                tree->tail = tree->head = node;
                tree->size++;
                return;
        }
        tree->tail->next = node;
        tree->tail = node;
        tree->size++;
}

bst_node *dequeue_bst_q_node(bst_q_tree *tree)
{
        if (tree->size == 0) {
                fprintf(stderr, "dequeue_bst_q_node: q is empty.");
                exit(EXIT_FAILURE);
        }
        bst_node *tmp = tree->head;
        tree->head = tmp->next;
        if (tree->head == NULL) {
                tree->tail = NULL;
        }
        bst_node *data = (bst_node *)malloc(sizeof(bst_node));
        data->key = tmp->key;
        data->right = tmp->right;
        data->left = tmp->left;;
        tree->size--;
        free(tmp);
        return data;
}


