#ifndef HASH_SET_H
#define HASH_SET_H

/**
 * make head members = null
 */
void init_buckets(list_node **buckets);

/**
 * uses multiplicative hashing string though not perfect
 *
 * @param key
 */
int hash_set_hash(int key);

/**
 * util function for hash_set_set
 * resetting things 
 * 
 * @params
 */
void hash_set_readd(list_node **keys, list_node **bucket);

/**
 * pretty print buckets
 *
 * @params buckets
 * returns void
 */
void hash_set_pretty_print(list_node **buckets);
/**
 * hash map set add a key-value pair 
 * to singly linked list as a bucket
 * uses hash to produce index to for 
 * finding where bucket to put key-value
 * pair.
 *
 * @params buckets, key, and data
 * returns void
 */

void hash_set_add(list_node **keys, list_node **buckets, int key);

/**
 * traverse the bucket using the key
 * and hash it to get the value.
 * 
 * @params buckets and key
 * returns list_node
 */
list_node *hash_set_get(list_node **buckets, int key);

/**
 * traverse the bucket using the key
 * and hash it to check whether value
 * exist or not. 
 *
 * @params buckets and key;
 * returns boolean
 *
 */
bool hash_set_has(list_node **buckets, int key);

/**
 * traverse the bucket using the key
 * and to hash it to remove that key-value 
 * pair.
 * 
 * @params buckets and key
 * returns void
 */
void hash_set_remove(list_node **keys, list_node **buckets, int key);

/**
 *
 * clear entries and buckects
 * ?note this operation is slow as it goes through the buckets
 * and destroy what's inside the bucket
 *
 * @params entries and buckets
 */
void hash_set_clear(list_node **keys, list_node **buckets);
/**
 * don't use the buckets for finding the
 * length. it is slow. use the list node
 * entries to find it instead 
 *
 * @params entries
 * returns int;
 */
int hash_set_length(list_node **keys);

#endif
