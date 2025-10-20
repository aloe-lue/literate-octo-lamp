#ifndef HASH_MAP_H
#define HASH_MAP_H

/**
 * make head members = null
 */
void init_buckets(list_node **buckets);

/**
 * uses multiplicative hashing string though not perfect
 *
 * @param key
 */
int hsh_mp_hash(char *key);

/**
 * util function for hsh_mp_set
 * resetting things 
 * 
 * @params
 */
void hsh_mp_reset(list_node **bucket);

/**
 * pretty print buckets
 *
 * @params buckets
 * returns void
 */
void hsh_mp_pretty_print(list_node **buckets);
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

void hsh_mp_set(list_node **entries, list_node **buckets, char *key, char *data);

/**
 * traverse the bucket using the key
 * and hash it to get the value.
 * 
 * @params buckets and key
 * returns list_node
 */
list_node *hsh_mp_get(list_node **buckets, char *key);

/**
 * traverse the bucket using the key
 * and hash it to check whether value
 * exist or not. 
 *
 * @params buckets and key;
 * returns boolean
 *
 */
bool hsh_mp_has(list_node **buckets, char *key);

/**
 * traverse the bucket using the key
 * and to hash it to remove that key-value 
 * pair.
 * 
 * @params buckets and key
 * returns void
 */
void hsh_mp_remove(list_node **entries, list_node **buckets, char *key);

/**
 *
 * clear entries and buckects
 * ?note this operation is slow as it goes through the buckets
 * and destroy what's inside the bucket
 *
 * @params entries and buckets
 */
void hsh_mp_clear(list_node **entries, list_node **buckets);
/**
 * don't use the buckets for finding the
 * length. it is slow. use the list node
 * entries to find it instead 
 *
 * @params entries
 * returns int;
 */
int hsh_mp_length(list_node **entries);

#endif
