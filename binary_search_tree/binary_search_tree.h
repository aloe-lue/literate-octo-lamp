#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <string.h>

typedef struct bst_node {
        int key;
        struct bst_node *parent;
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
 * returns the root of the tree
 * @params int *array
 */
bst_node *bst_build_tree(int *array);

/**
 * inserts a node in the tree
 *
 * returns void;
 * @params tree and value
 */
void bst_insert(bst_node **tree, int value);
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
void bst_transplant(bst_node **root, bst_node **u, bst_node **v);
bst_node *bst_minimum(bst_node **root);
void bst_delete(bst_node **root, int value);

/**
 * finds the node with the value 
 * 
 * returns bst_node
 * @params tree and value
 */
bst_node bst_find(bst_node **tree, int value);

/**
 * would you rather print it or would you rather
 * return the first array value
 *
 * use bfs 
 *
 * @params tree
 */
int *bst_level_order(bst_node **tree);
/**
 * uses dfs methods
 * 
 * @params pre in and post order is tree
 */
int *bst_pre_order(bst_node **tree);
int *bst_in_order(bst_node **tree);
int *bst_post_order(bst_node **tree);
int bst_height(bst_node **tree);
int bst_depth(bst_node **tree);
bool bst_isBalanced(bst_node **tree);
/**
 * use bfs or dfs in my case I will use dfs inorder
 * use the previous element called build tree
 * 
 * @params tree
 * returns the root
 */
bst_node bst_rebalance(bst_node **tree);

#endif
