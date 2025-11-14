#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "hash_set.h"

list_node *init_hash_set_buckets(int bucket_size)
{
        list_node *buckets = (list_node *)malloc(bucket_size * sizeof(list_node));
        if (buckets == NULL) {
                fprintf(stderr, "init h set buckets: malloc failure. \n");
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i < bucket_size; i++) {
                for (int j = 0; j < 2; j++)
                        buckets[i].keys[j] = -1;
                buckets[i].next = NULL;
        }
        return buckets;
}

hash_set *init_hash_set()
{
        hash_set *h_set = (hash_set *)malloc(sizeof(hash_set));
        if (h_set == NULL) {
                fprintf(stderr, "init h set: malloc failure. \n");
                exit(EXIT_FAILURE);
        }
        h_set->head = NULL;
        h_set->tail = NULL;
        h_set->entries = 0;
        h_set->load_factor = 1.00;
        h_set->max_buckets = 16;
        h_set->buckets = init_hash_set_buckets(h_set->max_buckets);
        return h_set;
}

int hash_set_hash(hash_set h_set, int keys[2])
{
        int hash_code = 0;
        for (int i = 0; i < 2; i++)
                hash_code += keys[i];
        const long double kA = ((sqrt(5) -1) /2) *hash_code;
        int result = h_set.max_buckets *((long double)kA -(int)kA);
        return result;
}

list_node *create_node(int keys[2])
{
        list_node *node = (list_node *)malloc(sizeof(list_node));
        if (node == NULL) {
                fprintf(stderr, "init h set: malloc failure. \n");
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 2; i++) 
                node->keys[i] = keys[i];
        node->next = NULL;
        return node;
}

void append_node(hash_set **h_set, int keys[2])
{
        list_node *new_node = create_node(keys);
        if ((*h_set)->head == NULL) {
                (*h_set)->head = new_node;
                (*h_set)->tail = new_node;
                return;
        }
        (*h_set)->tail->next = new_node;
        (*h_set)->tail = new_node;
}

bool hash_set_has(hash_set **h_set, int keys[2])
{
        hash_set *set = *h_set;
        int idx = hash_set_hash(*set, keys);
        list_node *bucket = &set->buckets[idx];
        bool not_bucket = (bucket->keys[0] != keys[0] &&
                        bucket->keys[1] != keys[1]);
        if (!not_bucket)
                return true;

        while (bucket->next != NULL && 
                        (bucket->keys[0] != keys[0] &&
                        bucket->keys[1] != keys[1]))
                bucket = bucket->next;
        if ((bucket->keys[0] == keys[0] &&
                        bucket->keys[1] == keys[1]))
                return true;
        else return false;
}

void hash_set_readd(hash_set **h_set, list_node **new_buckets)
{
        hash_set *set = *h_set;
        list_node *entries = set->head;
        list_node *n_buckets = *new_buckets;
        // surely this level of indentation makes me want to puke
        while (entries != NULL) {
                int idx = hash_set_hash(*set, entries->keys);
                list_node *tmp = &n_buckets[idx];

                bool empty = (tmp->keys[0] == -1 &&
                          tmp->keys[1] == -1);

                if (empty) {
                        for (int i = 0; i < 2; i++) 
                                tmp->keys[i] = entries->keys[i];
                } else if (!empty) {
                        while (tmp->next != NULL)
                                tmp = tmp->next;
                        if (tmp->next == NULL)
                                tmp->next = create_node(entries->keys);
                }
                entries = entries->next;
        }
}
void hash_set_add(hash_set **h_set, int keys[2])
{
        hash_set *set = *h_set;
        if (set->entries > (set->load_factor * set->max_buckets)) {
                // destroy all the buckets content except it's head
                // because it's not a ptr but buckets are
                for (int i = 0; i < set->max_buckets; i++) {
                        list_node *bucket = &(set->buckets[i]);
                        // destroy_hash_set_nodes(bucket, size, size-1);
                }
                free((*h_set)->buckets);
                // increase max_buckets
                set->max_buckets *= 2;
                list_node *new_buckets = init_hash_set_buckets(set->max_buckets);
                // rehash it and add it
                hash_set_readd(h_set, &new_buckets);
                (*h_set)->buckets = new_buckets;
        }
        // reads current after set readds
        hash_set *set_two = *h_set;
        int idx = hash_set_hash((*set_two), keys);
        list_node *bucket = &(set_two)->buckets[idx];
        bool empty = (bucket->keys[0] == -1 &&
                        bucket->keys[1] == -1);
        if (empty) {
                for (int i = 0; i < 2; i++) 
                        bucket->keys[i] = keys[i];
                append_node(h_set, keys);
                set_two->entries++;
                return;
        }
        if (hash_set_has(h_set, keys))
                return;

        list_node *new_node = create_node(keys);
        while (bucket->next != NULL) 
                bucket = bucket->next;
        if (bucket->next == NULL) {
                bucket->next = new_node;
                append_node(h_set, keys);
                set_two->entries++;
        }
}

void destroy_hash_set_nodes(list_node **list, int size, const int const_size)
{
        if (*list == NULL)
                return;
        destroy_hash_set_nodes(&(*list)->next, size -= 1, const_size);
        if (size != const_size)
                free(*list);
}

int hash_set_nodes_size(list_node **list)
{
        list_node *tmp = *list;
        int size = 0;
        if (tmp == NULL)
                return size;
        while (tmp != NULL) {
                size++;
                tmp = tmp->next;
        }
        return size;
}

void print_nodes(list_node **list)
{
        list_node *tmp = *list;
        if (tmp == NULL) {
                printf("NULL\n");
                return;
        }
        if (tmp->keys[0] != -1 && tmp->keys[1] != -1)
                printf("[%d, %d] --> ", tmp->keys[0], tmp->keys[1]);
        print_nodes(&tmp->next);
}

void print_hash_set(hash_set **h_set)
{
        hash_set *set = *h_set;
        list_node *head = set->head;
        
        printf("entries: %d\n", set->entries);
        print_nodes(&head);
        for (int i = 0; i < set->max_buckets; i++) {
                list_node *bucket = &(set)->buckets[i];
                print_nodes(&bucket);
        }
}

void destroy_hash_set(hash_set **h_set)
{
        hash_set *set = *h_set;
        list_node *head = set->head;
        int size = set->entries;

        // destroy entries
        destroy_hash_set_nodes(&head, size, size);
        // destroy buckets extension
        for (int i = 0; i < set->max_buckets; i++) {
                list_node *bucket = &(set)->buckets[i];
                int nodes_size = hash_set_nodes_size(&bucket);
                destroy_hash_set_nodes(&bucket, nodes_size, nodes_size-1);
        }
        // finally destroy the hash set
        free(*h_set);
}

