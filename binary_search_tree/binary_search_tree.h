#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <string.h>

// add next for queue
typedef struct bst_node {
        int key;
        struct bst_node *parent;
        struct bst_node *next;
        struct bst_node *left;
        struct bst_node *right;
} bst_node;

/**
 *
 * @params value
 * returns bst_node
 */
bst_node *bst_create_node(int value);
/**
 * sort array
 * remove duplicates
 * build tree
 *
 * returns the root of the tree uses auxillary method -> remove duplicates
 * @params int *array
 */
int remove_duplicates(int *keys, int *arr, int keys_size);
bst_node *bst_build_tree(bst_node *root, int *arr, int start, int end);

/**
 *
 * returns the successor of the tree 
 *
 * @params bst_node
 *
 */
bst_node *bst_successor(bst_node* T);
/**
 * 
 *
 */
bst_node *bst_create(int *keys, int keys_size);
/**
 * inserts a node in the tree
 *
 * returns void;
 * @params tree and value
 */
void bst_insert(bst_node *tree, int value);
/**
 * delete a value in the tree
 *      handle intricate case such as when
 *      deleting a node that have 
 *      right children containing left children
 *
 * auxillary methods => implement transplant subroutine 
 *                       ""         bst_minimum  
 *
 * returns void;
 * @params tree and value
 */

void bst_delete(bst_node *root, int value);
/**
 * handles intricacies of deletion operation
 *
 * @params tree, place and in place
 */
void bst_transplant(bst_node **root, bst_node *u, bst_node *v);

/**
 * returns the largest value in bst
 * 
 * @params tree 
 */
bst_node *bst_maximum(bst_node *tree);
/**
 * returns the smallest value in bst
 * 
 * @params tree 
 */
bst_node *bst_minimum(bst_node *tree);

/**
 * finds the node with the value 
 * 
 * returns bst_node
 * @params tree and value
 */
bst_node *bst_find(bst_node *tree, int value);
/**
 * frees the bst nodes in level_order
 *
 * @params tree
 */
void bst_destroy(bst_node *tree);

/**
 * would you rather print it or would you rather
 * return the first array value
 *
 * use bfs 
 *
 * @params tree
 */
void bst_level_order(bst_node **tree);
/**
 * uses dfs methods
 * 
 * @params pre in and post order is tree
 */
int *bst_pre_order(bst_node *tree);
int *bst_in_order(bst_node *tree);
int *bst_post_order(bst_node *tree);
int bst_height(bst_node *tree);
int bst_depth(bst_node *tree);
bool bst_isBalanced(bst_node *tree);
/**
 * use bfs or dfs in my case I will use dfs inorder
 * use the previous element called build tree
 * 
 * @params tree
 * returns the root
 */
bst_node bst_rebalance(bst_node *tree);

/**
 * pretty print bst
 *
 * @params tree, prefix and false
 */
void bst_pretty_print(bst_node *root, int level, const char *prefix, int is_left) ;

#endif
