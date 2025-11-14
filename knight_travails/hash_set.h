#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h>

typedef struct list_node {
        int keys[2];
        struct list_node *next;
} list_node;

typedef struct hash_set {
        list_node *buckets;
        list_node *head;
        list_node *tail;
        int max_buckets;
        float load_factor;
        int entries;
} hash_set;


hash_set *init_hash_set();


int hash_set_hash(hash_set h_set, int keys[2]);


list_node *init_hash_set_buckets(int bucket_size);


void hash_set_add(hash_set **h_set, int keys[2]);


void append_node(hash_set **h_set, int keys[2]);


list_node *create_node(int keys[2]);


void destroy_hash_set(hash_set **h_set);


void destroy_hash_set_nodes(list_node **list, 
                int size, 
                const int const_size);


bool hash_set_has(hash_set **h_set, int keys[2]);


int hash_set_nodes_size(list_node **list);


void print_nodes(list_node **list);


void print_hash_set(hash_set **h_set);


void hash_set_readd(hash_set **h_set, list_node **new_buckets);
#endif
