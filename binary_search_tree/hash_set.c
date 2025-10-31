#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#include "linked_list.h"

const float hash_set_load_factor = 0.80;
static int hash_set_max_buckets = 16;
static int hash_set_keys = 0;

void init_buckets(list_node **buckets)
{
        list_node *tmp_buckets = *buckets;
        for (int i = 0; i < hash_set_max_buckets; i++) {
                tmp_buckets[i].key = -1;
                tmp_buckets[i].next = NULL;
        }
}

int hash_set_hash(int key)
{
        long double kA = ((sqrt(5) -1) / 2) * key; 
        int result = hash_set_max_buckets * ((long double)kA -(int)kA);
        return result;
}

void hash_set_readd(list_node **keys, list_node **buckets)
{
        list_node *tmp_keys = *keys;
        list_node *new_buckets = *buckets;

        while (tmp_keys != NULL) {
                int ex_idx = hash_set_hash(tmp_keys->key);
                list_node *new_bucket = &new_buckets[ex_idx];

                if (new_bucket->key == -1) 
                        new_bucket->key = tmp_keys->key;
                else
                        append_node(&new_bucket, tmp_keys->key);
                tmp_keys = tmp_keys->next;
        }
}

void hash_set_pretty_print(list_node **buckets)
{
        list_node *tmp_buckets = *buckets;
        for (int i = 0; i < hash_set_max_buckets; i++) {
                list_node *bucket = &tmp_buckets[i];
                printf("bucket %d -> ", i);
                print_nodes_key(&bucket);
        }
}

void hash_set_add(list_node **keys, list_node **buckets, int key)
{
        if (key < 0 || key > INT_MAX) {
                puts("key should be non-negative value and within limits. \n");
                return;
        }
        if (*buckets == NULL) {
                puts("cannot set key on empty bucket.\n");
                return;
        }
        list_node *tmp_buckets = *buckets;
        if (hash_set_keys > (int)(hash_set_load_factor * hash_set_max_buckets)) {
                for (int i = 0; i < hash_set_max_buckets; i++) {
                        list_node *tmp_bucket = &tmp_buckets[i];
                        destroy_nodes(&tmp_bucket, nodes_size(&tmp_bucket),nodes_size(&tmp_bucket) -1);
                }
                free(*buckets);
                // increase buckets
                hash_set_max_buckets *= 2;
                list_node *new_buckets = (list_node *)malloc(hash_set_max_buckets * sizeof(list_node));
                init_buckets(&new_buckets);
                list_node *tmp_keys = *keys;
                
                hash_set_readd(&tmp_keys, &new_buckets);
                *buckets = new_buckets;
        }
        int idx = hash_set_hash(key);
        if (idx > hash_set_max_buckets || idx > INT_MAX) {
                puts("set key idx out of bounds. \n");
                return;
        }
        list_node *tmp_buckets_2 = *buckets;
        list_node *bucket = &tmp_buckets_2[idx];
        list_node *tmp_keys = *keys;

        if (bucket->key == -1) {
                hash_set_keys += 1;
                bucket->key = key;
                if (tmp_keys == NULL)
                       *keys = create_node(key);
                else
                        append_node(keys, key);
                return;
        }

        if (bucket->key == key) {
                bucket->key = key;
                while (tmp_keys != NULL && tmp_keys->key != key)
                        tmp_keys = tmp_keys->next;
                if (tmp_keys != NULL && tmp_keys->key == key)
                        tmp_keys->key = key;
                return;
        }
        while (bucket != NULL && bucket->key != key)
                bucket = bucket->next;
        if (bucket != NULL && bucket->key == key) {
               while (tmp_keys != NULL && tmp_keys->key != key) 
                        tmp_keys = tmp_keys->next;
                if (tmp_keys != NULL && tmp_keys->key == key) 
                        tmp_keys = tmp_keys->next;
                return;
        }

        list_node *tmp_bucket = &tmp_buckets[idx];
        list_node *temp_keys_2 = *keys;
        append_node(&tmp_bucket, key);
        append_node(keys, key);
        hash_set_keys += 1;
        return;
}

list_node *hash_set_get(list_node **buckets, int key)
{
        list_node *bucket;
        if (key < 0 || key > INT_MAX) {
                puts("key should be non negative value and within limits. \n");
                return bucket;
        }
        if (*buckets == NULL) {
                puts("there\'s is nothing to get in bucket. \n");
                return bucket;
        }
        int idx = hash_set_hash(key);
        if (idx > hash_set_max_buckets && idx > INT_MAX) {
                puts("hash_set getting out of hash value out of bounds.\n");
                return bucket;
        }
        list_node *tmp_buckets = *buckets;
        list_node *tmp_bucket = &tmp_buckets[idx];

        while (tmp_bucket != NULL && tmp_bucket->key != key) 
                tmp_bucket = tmp_bucket->next;
        if (tmp_bucket != NULL && tmp_bucket->key == key)  {
                bucket = &(*tmp_bucket);
                return bucket;
        }
        return bucket;
}


bool hash_set_has(list_node **buckets, int key)
{

        if (key < 0 || key > INT_MAX) {
                puts("key should be non-negative value and within limits. \n");
                return false;
        }
        if (*buckets == NULL) {
                puts("there\'s is nothing to get in bucket. \n");
                return false;
        }
        int idx = hash_set_hash(key);
        if (idx > hash_set_max_buckets && idx > INT_MAX) {
                puts("hash_set getting out of hash value out of bounds.\n");
                return false;
        }
        list_node *tmp_buckets = *buckets;
        list_node *tmp_bucket = &tmp_buckets[idx];

        while (tmp_bucket != NULL && tmp_bucket->key != key) 
                tmp_bucket = tmp_bucket->next;
        if (tmp_bucket != NULL && tmp_bucket->key == key)
                return true;
        return false;
}

int hash_set_remove(list_node **keys, list_node **buckets, int key)
{
        if (key < 0 || key > INT_MAX) {
                puts("key should be non-negative value and within limits. \n");
                return EXIT_FAILURE;
        }
        if (*buckets == NULL) {
                puts("there\'s is nothing to get in bucket. \n");
                return EXIT_FAILURE;
        }
        int idx = hash_set_hash(key);
        if (idx > hash_set_max_buckets && idx > INT_MAX) {
                puts("hash_set getting out of hash value out of bounds.\n");
                return EXIT_FAILURE;
        }
        list_node *tmp_buckets = *buckets;
        list_node *tmp_keys = *keys; 
        list_node *tmp_bucket = &tmp_buckets[idx];
        
        int key_idx = find_node_by_key(&tmp_keys, key);
        int node_idx = find_node_by_key(&tmp_bucket, key);

        if (node_idx == 0) 
                remove_node_head(&tmp_bucket);
        else 
                remove_node_at(&tmp_bucket, node_idx);

        remove_node_at(keys, key_idx);
        hash_set_keys -= 1;
        return EXIT_SUCCESS;
} 

int *hash_set_clear(list_node **keys, list_node **buckets)
{
        list_node *tmp_buckets = *buckets;
        list_node *tmp_keys = *keys;
        
        destroy_nodes(keys, nodes_size(&tmp_keys), nodes_size(&tmp_keys));
        for (int i = 0; i < hash_set_max_buckets; i++) {
                list_node *bucket = &tmp_buckets[i];
                destroy_nodes(&bucket, nodes_size(&bucket), nodes_size(&bucket) -1);
        }
        free(*buckets);
        hash_set_keys = 0;
        return EXIT_SUCCESS;
}

int hash_set_length(list_node **keys)
{
        list_node *tmp_keys = *keys;
        int size = 0;
        while (tmp_keys != NULL) {
                size++;
                tmp_keys = tmp_keys->next;
        }
        return size;
}


