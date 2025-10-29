#include <stdio.h>
#include <stdlib.h>

#include "queue_linked_list.h"

q_list_node *create_q_list_node(void *data)
{
        q_list_node *qln = (q_list_node *)malloc(sizeof(q_list_node));
        if (qln == NULL) {
                puts("malloc error: create_q_list_node func. \n");
                return qln;
        }
        qln->data = data;
        qln->next = NULL;
        return qln;
}

q_linked_list *create_q_linked_list()
{
        q_linked_list *QLL = (q_linked_list *)malloc(sizeof(q_linked_list));
        QLL->head = NULL;
        QLL->tail = NULL;
        QLL->size = 0;
        return QLL;
}

void enqueue_q_list_node(q_linked_list *QLL, void *data)
{
        q_list_node *new_q_list_node = create_q_list_node(data);
        if (new_q_list_node == NULL) {
                puts("can\'t enqueue on empty list_node. \n");
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
}
char *dequeue_q_list_node_s(q_linked_list *QLL)
{
        const int c_size = 50;
        if (QLL->q_ll_len == 0) {
                char *value = (char *)malloc((c_size + 1) * sizeof(char)); 
                strncpy(value, "cannot dequeue on an empty queue.", c_size);
                value[c_size] = '\0';
                return value;
        }
        q_list_node *tmp = QLL->face;
        QLL->face = tmp->next;
        if (QLL->face == NULL) {
                QLL->tail = NULL;
        }
        char *data = (char *)malloc((c_size + 1) * sizeof(char));
        strncpy(data, tmp->data, c_size);
        data[c_size] = '\0';
        QLL->q_ll_len--;
        free(tmp);
        return data;
}

int size_q_list_node(q_linked_list *QLL)
{
        return QLL->q_ll_len;
}

char *peek_q_list_node_s(q_linked_list *QLL)
{
        return QLL->head->data;
}

void destroy_q_linked_list_h(q_linked_list *QLL)
{
        if (QLL->head == NULL) {
                return;
        }
        destroy_q_linked_list(QLL->head->next);
        free(QLL->head);
}

