#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "linked_list.h"

list_node *create_node(void *key, void *data)
{
        list_node *node = (list_node *)malloc(sizeof(list_node));
        if (node == NULL) {
                puts("malloc failed at create_node func");
                return NULL;
        }
        node->key = key;
        node->data = data;
        return node;   
}

void append_node(list_node **head, void *key, void *data)
{
        if (*head == NULL) {
                *head = create_node(key, data);
                return;
        } else {
                list_node *temp = *head;

                while (temp->next != NULL)
                        temp = temp->next;
                temp->next = create_node(key, data);
        }
}

void preppend_node(list_node **head, void *key, void *data)
{
        list_node *node = create_node(key, data);
        node->next = *head;
        *head = &(*node);
        return;
}

/**
 * size? why? free(): pointer invalid if you where
 * to free the head then it becomes really 
 */
void destroy_nodes(list_node **head, int size)
{
        if (*head == NULL) {
                return;
        }
        destroy_nodes(&(*head)->next, --size);

        // don't free the head
        if (size > 1) 
                free(*head);
}

void print_nodes(list_node **head)
{
        list_node *temp = *head;

        while (temp != NULL) {
                printf("(key: %s, value: %s) -> ", 
                                (char *)temp->key, 
                                (char *)temp->data);
                temp = temp->next;
        }
        printf("NULL\n");
}

int nodes_size(list_node **head)
{
        int size = 0;
        if (*head == NULL)
                return size;        
        list_node *temp = *head;
        while (temp != NULL)  {
                size++;
                temp = temp->next;
        }
        return size;
}

int find_node(list_node **head, void *data)
{
        list_node *temp = *head;
        int size = 0;

        while (temp != NULL) {
                int rc = strcmp(data, (char *)temp->data);
                if (rc == 0) 
                        return size;
                size++;
                if (size >= nodes_size(head))
                        return -1;
                temp = temp->next;
        }
        return size;
}

bool contains_node(list_node **head, void *data)
{
        list_node *temp = *head;

        bool has_node = false;
        while (temp != NULL) {
                int rc = strcmp(data, (char *)temp->data);
                if (rc == 0) {
                        return !has_node;
                } 

                temp = temp->next;
        }
        return has_node;
}

void insert_node_at(list_node **head, void *key, void *data, int idx)
{
        if (*head == NULL) {
                *head = create_node(key, data);
                return;
        } 
        if (idx <= 0) {
                preppend_node(head, key, data);
                return;
        }
        if (idx >= nodes_size(head) - 1) {
                append_node(head, key, data);
                return;
        }


        int index = 0;
        list_node *curr = *head;
        list_node *prev = NULL;

        while (curr != NULL && index != idx) {
                index++;
                prev = curr;
                curr = curr->next;
        }
        if (curr != NULL) {
                list_node *node = create_node(key, data);
                node->next = curr;
                prev->next = node;
        }
}

void remove_node_at(list_node **head, int idx)
{
        if (*head == NULL) {
                puts("nothing to remove \n");
                return;
        }
        int index = 0;
        list_node *curr = NULL;
        if (idx == index) {
                curr = *head;
                *head = (*head)->next;
                free(curr);
                return;
        }
        curr = *head;
        list_node *prev = NULL;
        while (curr != NULL && index != idx) {
                index++;
                prev = curr;
                curr = curr->next;
        }
        if (curr == NULL) {
                puts("nothing to remove \n");
                return;
        }
        list_node *curr_temp = curr;
        prev->next = curr->next;
        free(curr_temp);
}
