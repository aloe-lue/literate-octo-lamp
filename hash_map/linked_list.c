#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "linked_list.h"

list_node *create_node(char *key, char *data)
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

void append_node(list_node **head, char *key, char *data)
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

void preppend_node(list_node **head, char *key, char *data)
{
        list_node *node = create_node(key, data);
        node->next = *head;
        *head = &(*node);
        return;
}

void destroy_nodes(list_node **head, int size, const int c_size)
{
        if (*head == NULL) 
                return;
        // choose minus one to delete except head
        destroy_nodes(&(*head)->next, size--, c_size);
        if (size != c_size)
                free(*head);
}

void print_nodes(list_node **head)
{
        list_node *temp = *head;

        while (temp != NULL && temp->key != NULL) {
                printf("( %s ) --> ", (char *)temp->data);
                temp = temp->next;
        }
        printf("null\n");
}

void print_nodes_key_value(list_node **head)
{
        list_node *temp = *head;

        while (temp != NULL && temp->key != NULL) {
                printf("(%s, %s) -> ", (char *)temp->key, (char *)temp->data) ;
                temp = temp->next;
        }
        printf("null\n");
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

int find_node_by_data(list_node **head, char *data)
{
        list_node *temp = *head;
        int size = 0;

        while (temp != NULL) {
                int rc = strcmp(data, (char *)temp->data);
                if (rc == 0) 
                        size++;
                        return size;
                if (size >= nodes_size(head))
                        return -1;
                temp = temp->next;
        }
        return size;
}

int find_node_by_key(list_node **head, char *key)
{
        list_node *temp = *head;
        int size = 0;

        while (temp != NULL) {
                int rc = strcmp(key, (char *)temp->key);
                if (rc == 0) 
                        return size;
                size++;
                if (size >= nodes_size(head))
                        return -1;
                temp = temp->next;
        }
        return size;
}

bool contains_node(list_node **head, char *data)
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

void insert_node_at(list_node **head, char *key, char *data, int idx)
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
        return;
}

// this is for replacing the head since a head is the parent pointer 
void remove_node_head(list_node **head)
{
        if (*head == NULL) {
                puts("nothing to remove \n");
                return;
        }
        list_node *tmp = *head;
        list_node *tmp_2 = *head;
        list_node *tmp_3 = (*head)->next;

        if (tmp_3 == NULL) {
                tmp->key = NULL;
                tmp->data = NULL; 
                tmp->next = NULL; 
                return;
        }
        tmp->key = tmp_2->next->key;
        tmp->data = tmp_2->next->data;
        tmp->next = tmp_2->next->next;
        free(tmp_2->next);
        return;
}

