#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "merge_sort.h"
#include "linked_list.h"
#include "hash_set.h"
#include "binary_search_tree.h"

bst_node *bst_create_node(int key)
{
        bst_node *node = (bst_node *)malloc(sizeof(bst_node));
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        return node;
}

void bst_insert(bst_node **root, int key)
{
        bst_node *y = NULL;
        bst_node *tmp_root = *root;

        while (tmp_root != NULL) {
                y = tmp_root;
                if (tmp_root->key > key)
                        tmp_root = tmp_root->left;
                else tmp_root = tmp_root->right;
        }
        bst_node *z = bst_create_node(key);
        z->parent = y;
        if (y == NULL) 
                *root = z;
        else if (tmp_root->key > z->key)
                tmp_root->left = z;
        else tmp_root->right = z;
}

void bst_transplant(bst_node **root, bst_node **u, bst_node **v)
{
        bst_node *U = *u;
        bst_node *V = *v;

        if (U->parent == NULL) 
                *root = V;
        else if (U->parent->left == U)
                U->parent->left = V;
        else U->parent->right = V;

        if (V != NULL)
                V->parent = U->parent;
}

bst_node *bst_minimum(bst_node **root)
{
        bst_node *tmp_root = *root;

        while (tmp_root->left != NULL)
                tmp_root = tmp_root->left;
        return tmp_root;
}

void bst_delete(bst_node **root, int key)
{
        if (key < 0 || key > INT_MAX) {
                puts("key should be non-negative \n");
                return;
        }
        // find the node to delete 
        bst_node *tmp_root = *root;
        bst_node *z = *root;
        while (z != NULL && z->key != key) {
                if (z->key > key) 
                        z = z->left;
                else z = z->right;
        }
        if (z == NULL) {
                puts("leaf doesn\'t exist in the tree. \n");
                return;
        }
        bst_node *tmp_z = z;
        if (z->left == NULL) {
                bst_transplant(&tmp_root, &z, &z->right);
        } else if (z->right == NULL) {
                bst_transplant(&tmp_root, &z, &z->left);
        } else {
                bst_node *y = bst_minimum(&z->right);
                if (y->parent->right != y) {
                        bst_transplant(&tmp_root, &y, &y->right);
                        y->right = z->right;
                        z->right->parent = y;
                }
                bst_transplant(&tmp_root, &z, &y);
                y->left = z->left;
                y->left->parent = y;
        }
        free(tmp_z);
}

bst_node *bst_find(bst_node **root, int key)
{
        if (key < 0 || key > INT_MAX) {
                puts("key should be non-negative value. \n");
                return;
        }
        bst_node *t_root = *root;
        while (t_root != NULL && t_root->key != key) {
                if (key > t_root->key) 
                        t_root = t_root->right;
                else t_root = t_root->left;
        }
        if (t_root == NULL)
                puts("key not found. \n");
        return t_root;
}

int *bst_level_order(bst_node **tree)
{
}

int *bst_pre_order(bst_node **tree);
int *bst_in_order(bst_node **tree);
int *bst_post_order(bst_node **tree);
int bst_height(bst_node **tree);
int bst_depth(bst_node **tree);
bool bst_isBalanced(bst_node **tree);

bst_node bst_rebalance(bst_node **tree);
