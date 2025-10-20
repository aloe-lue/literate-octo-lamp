#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#include "linked_list.h"

const float hash_map_load_factor = 0.80;
static int hash_map_max_buckets = 16;
static int hash_map_keys = 0;

void init_buckets(list_node **buckets)
{
        list_node *tmp_buckets = *buckets;
        for (int i = 0; i < hash_map_max_buckets; i++) {
                tmp_buckets[i].key = NULL;
                tmp_buckets[i].data = NULL;
                tmp_buckets[i].next = NULL;
        }
}

int hsh_mp_hash(char *key)
{
        int hash_code = 0;
        int key_size = strlen(key);
        for (int i = 0; i < key_size; i++) 
                hash_code += (int)key[i];
        long double kA = ((sqrt(5) -1) / 2) * hash_code; 
        int result = hash_map_max_buckets * ((long double)kA -(int)kA);
        return result;
}

void hsh_mp_reset(list_node **entries, list_node **bucket)
{
        list_node *tmp_entries = *entries;
        list_node *new_buckets = *bucket;

        while (tmp_entries != NULL) {
                int ex_idx = hsh_mp_hash(tmp_entries->key);
                list_node *new_bucket = &new_buckets[ex_idx];

                if (new_bucket->key == NULL 
                        && new_bucket->data == NULL) {
                        new_bucket->key = tmp_entries->key;
                        new_bucket->data = tmp_entries->data;
                } else if (new_bucket->key == tmp_entries->key) {
                        new_bucket->data = tmp_entries->data;
                } else {
                        append_node(&new_bucket, 
                                        tmp_entries->key, 
                                        tmp_entries->data);
                }
                tmp_entries = tmp_entries->next;
        }
}

void hsh_mp_pretty_print(list_node **buckets)
{
        list_node *tmp_buckets = *buckets;
        for (int i = 0; i < 32; i++) {
                list_node *bucket = &tmp_buckets[i];
                printf("bucket %d -> ", i);
                print_nodes_key_value(&bucket);
        }
}

void hsh_mp_set(list_node **entries, list_node **buckets, char *key, char *data)
{
        if (key == NULL && data == NULL) {
                puts("you need key and data value to store in the buckets\n");
                return;
        }
        if (*buckets == NULL) {
                puts("cannot set key-value pair on empty buckets.\n");
                return;
        }
        list_node *tmp_buckets = *buckets;
        if (hash_map_keys > (int)(hash_map_load_factor * hash_map_max_buckets)) {
                for (int i = 0; i < hash_map_max_buckets; i++) {
                        list_node *tmp_bucket = &tmp_buckets[i];
                        destroy_nodes(&tmp_bucket, 
                                        nodes_size(&tmp_bucket), 
                                        nodes_size(&tmp_bucket) -1);
                }
                // increase buckets
                hash_map_max_buckets *= 2;
                list_node *new_buckets = (list_node *)malloc(hash_map_max_buckets * sizeof(list_node));
                list_node *tmp_entries = *entries;
                
                hsh_mp_reset(&tmp_entries, &new_buckets);
                *buckets = new_buckets;
        }
        int idx = hsh_mp_hash(key);
        if (idx > hash_map_max_buckets || idx > INT_MAX) {
                puts("set key-value pair out of bounds. \n");
                return;
        }
        list_node *tmp_buckets_2 = *buckets;
        list_node *bucket = &tmp_buckets_2[idx];
        list_node *tmp_entries = *entries;

        if (bucket->key == NULL && bucket->data == NULL) {
                hash_map_keys += 1;
                bucket->key = key;
                bucket->data = data;
                if (tmp_entries == NULL)
                        *entries = create_node(key, data);
                else
                        append_node(&tmp_entries, key, data);
                return;
        }
        if (bucket->key == key) {
                while (tmp_entries != NULL && tmp_entries->key != key)
                        tmp_entries = tmp_entries->next;
                if (tmp_entries != NULL && tmp_entries->key == key) 
                        tmp_entries->data = data;
                bucket->data = data;
                return;
        }
        while (bucket != NULL && bucket->key != key)
                bucket = bucket->next;
        if (bucket != NULL && bucket->key == key) {
                bucket->data = data;
                while (tmp_entries != NULL && tmp_entries->key != key)
                        tmp_entries = tmp_entries->next;
                if (tmp_entries != NULL && tmp_entries->key == key)
                        tmp_entries->data = data;
                return;
        }

        list_node *tmp_bucket = &tmp_buckets[idx];
        list_node *temp_entries_2 = *entries;
        append_node(&tmp_bucket, key, data);
        append_node(&temp_entries_2, key, data);
        hash_map_keys += 1;
        return;
}

list_node *hsh_mp_get(list_node **buckets, char *key)
{
        list_node *bucket;
        if (*buckets == NULL) {
                puts("there\'s is nothing to get in bucket. \n");
                return bucket;
        }
        if (key == NULL || strlen(key) == 0) {
                puts("key is required to perform get operation. \n");
                return bucket;
        }
        int idx = hsh_mp_hash(key);
        if (idx > hash_map_max_buckets && idx > INT_MAX) {
                puts("hash_map getting out of hash value out of bounds.\n");
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


bool hsh_mp_has(list_node **buckets, char *key)
{
        if (*buckets == NULL) {
                puts("there\'s is nothing to get in bucket. \n");
                return false;
        }
        if (key == NULL || strlen(key) == 0) {
                puts("key is required to perform get operation. \n");
                return false;
        }
        int idx = hsh_mp_hash(key);
        if (idx > hash_map_max_buckets && idx > INT_MAX) {
                puts("hash_map getting out of hash value out of bounds.\n");
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

int hsh_mp_remove(list_node **entries, list_node **buckets, char *key)
{
        
        if (*buckets == NULL) {
                puts("there\'s is nothing to get in bucket. \n");
                return EXIT_FAILURE;
        }
        if (key == NULL || strlen(key) == 0) {
                puts("key is required to perform get operation. \n");
                return EXIT_FAILURE;
        }
        int idx = hsh_mp_hash(key);
        if (idx > hash_map_max_buckets && idx > INT_MAX) {
                puts("hash_map getting out of hash value out of bounds.\n");
                return EXIT_FAILURE;
        }
        list_node *tmp_buckets = *buckets;
        list_node *tmp_entries = *entries;
        list_node *tmp_bucket = &tmp_buckets[idx];
        
        int entry_idx = find_node_by_key(&tmp_entries, key);
        int node_idx = find_node_by_key(&tmp_bucket, key);

        if (node_idx == 0) 
                remove_node_head(&tmp_bucket);
        else 
                remove_node_at(&tmp_bucket, node_idx);
        
        // remove from entries
        remove_node_at(entries, node_idx);
        hash_map_keys -= 1;
        return EXIT_SUCCESS;
} 

int *hsh_mp_clear(list_node **entries, list_node **buckets)
{
        list_node *tmp_buckets = *buckets;
        list_node *tmp_entries = *entries;
        
        destroy_nodes(entries, nodes_size(&tmp_entries), nodes_size(&tmp_entries));
        for (int i = 0; i < hash_map_max_buckets; i++) {
                list_node *bucket = &tmp_buckets[i];
                destroy_nodes(&bucket, nodes_size(&bucket), nodes_size(&bucket) -1);
        }
        free(*buckets);
        hash_map_keys = 0;
        return EXIT_SUCCESS;
}

int hsh_mp_length(list_node **entries)
{
        list_node *tmp_entries = *entries;
        int size = 0;
        while (tmp_entries != NULL) {
                size++;
                tmp_entries = tmp_entries->next;
        }
        return size;
}


