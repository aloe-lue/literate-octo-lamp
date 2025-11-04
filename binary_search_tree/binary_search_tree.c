#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#include "merge_sort.h"
#include "linked_list.h"
#include "hash_set.h"
#include "binary_search_tree.h"
#include "queue_linked_list.h"

#define PREFIX_MAX_LEN 1024 
void bst_pretty_print(bst_node *root,
                               int level,
                               char *prefix_buffer, // Pass the buffer itself
                               size_t buffer_size,  // Pass the total buffer size
                               int is_left) 
{
        if (root == NULL)
                return;
        
        size_t current_len = strlen(prefix_buffer);
        // Use snprintf to safely append to the current buffer, tracking remaining space
        snprintf(prefix_buffer + current_len, 
                        buffer_size - current_len, 
                        "%s", 
                        (is_left ? "│   " : "    "));
        bst_pretty_print(root->right, 
                        level + 1, 
                        prefix_buffer, 
                        buffer_size, 0);
        
        // Reset the prefix to its state *before* the right child's indentation was added
        prefix_buffer[current_len] = '\0';
        
        printf("%s%s%d\n",
                prefix_buffer,
                (is_left ?
                "\u2570─\u2022 " : // ╰─•
                "\u256D─\u2022 "), // ╭─•
                root->key);
        
        // Safely append the *left* child's indentation pattern to the prefix buffer
        current_len = strlen(prefix_buffer); // Get the length again after printing the current node
        snprintf(prefix_buffer + current_len, 
                        buffer_size - current_len, 
                        "%s", 
                        (is_left ? "    " : "│   "));
        bst_pretty_print(root->left, 
                        level + 1, 
                        prefix_buffer, 
                        buffer_size, 1);
         
        // After this call returns, we must ensure the buffer is truncated back to its parent's length
        prefix_buffer[current_len] = '\0';
}
        
void bst_print(bst_node* root) 
{
        char buffer[PREFIX_MAX_LEN] = "";
        
        if (root != NULL) {
                bst_pretty_print(root, 0, buffer, sizeof(buffer), 0);
        }
}

int remove_duplicates(int *keys, int *arr, int keys_size)
{
        list_node *buckets = (list_node *)malloc(16 * sizeof(list_node));
        list_node *key_entries = NULL;
        int j = 0;

        for (int i = 0; i < keys_size; i++) {
                if (!hash_set_has(&buckets, keys[i])) {
                        hash_set_add(&key_entries, &buckets, keys[i]);
                        arr[j++] = keys[i];
                }         
        }
        int unique = nodes_size(&key_entries);
        hash_set_clear(&key_entries, &buckets);
        return unique;
}

bst_node *bst_build_tree(bst_node *root, int *arr, int start, int end)
{
        if (start > end)
                return NULL;

        int mid = (start + end) >> 1;

        bst_node *parent = bst_create_node(arr[mid]);
        parent->parent = root;

        parent->left = bst_build_tree(parent, arr, start, mid -1);
        parent->right = bst_build_tree(parent, arr, mid +1, end);

        return parent;
}

bst_node *bst_create(int *keys, int keys_size)
{
        int *keys_sort = merge_sort(keys, 0, keys_size -1);
        int arr[keys_size];
        int unique_keys = remove_duplicates(keys_sort, arr, keys_size);
        
        bst_node *root = bst_build_tree(NULL, arr, 0, unique_keys -1);
        return root;
}

bst_node *bst_create_node(int key)
{
        bst_node *node = (bst_node *)malloc(sizeof(bst_node));
        if (node == NULL) {
                fprintf(stderr, "bst_create_node: failed malloc. \n");
                exit(EXIT_FAILURE);
        }
        node->key = key;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
        return node;
}

void bst_insert(bst_node *root, int key)
{
        bst_node *y = NULL;
        bst_node *tmp_root = root;

        while (tmp_root != NULL) {
                y = tmp_root;
                if (tmp_root->key > key)
                        tmp_root = tmp_root->left;
                else tmp_root = tmp_root->right;
        }
        bst_node *z = bst_create_node(key);
        z->parent = y;
        if (y == NULL) 
                root = z;
        else if (tmp_root->key > z->key)
                tmp_root->left = z;
        else tmp_root->right = z;
}

void bst_transplant(bst_node **root, bst_node *u, bst_node *v)
{
        if (u == NULL)
                return;
        else if (u->parent == NULL) 
                *root = v;
        else if (u == u->parent->left)
                u->parent->left = v;
        else u->parent->right = v;

        if (v != NULL)
                v->parent = u->parent;
}

bst_node *bst_minimum(bst_node *root)
{
        bst_node *tmp_root = root;

        while (tmp_root->left != NULL)
                tmp_root = tmp_root->left;
        return tmp_root;
}

bst_node *bst_maximum(bst_node *root)
{
        bst_node *tmp_root = root;

        while (tmp_root->right != NULL)
                tmp_root = tmp_root->right;
        return tmp_root;
}

bst_node* bst_successor(bst_node *root) 
{
        if (root == NULL)
                return root;
        else if (root->left != NULL) {
                while (root->left != NULL)
                        root = root->left;
                return root;
        } else {
                while (root->parent != NULL && root->parent->right == root)
                        root = root->parent;
                return root->parent;
        }
} 

void bst_delete(bst_node **root, int key)
{
        bst_node *z = bst_find(*root, key);
        
        if (z->right == NULL)
                bst_transplant(root, z, z->left);
        else if (z->left == NULL)
                bst_transplant(root, z, z->right);
        else {
                bst_node *y = bst_minimum(z->right);

                if (y->parent != z) {
                        bst_transplant(root, y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                }
                bst_transplant(root, z, y);
                y->left = z->left;
                y->left->parent = y;
        }
        free(z);
}
        
bst_node *bst_find(bst_node *root, int key)
{
        bst_node *t_root = root;
        if (key < 0 || key > INT_MAX) {
                puts("key should be non-negative value. \n");
                return t_root;
        }
                while (t_root != NULL && t_root->key != key) {
                        if (key > t_root->key) 
                                t_root = t_root->right;
                else t_root = t_root->left;
        }
        if (t_root == NULL)
                puts("key not found. \n");
        return t_root;
}

void bst_destroy(bst_node *tree)
{
        if (tree == NULL) 
                return;
        bst_destroy(tree->left);
        bst_destroy(tree->right);
        free(tree);
}

int *bst_level_order(bst_node *tree)
{
        bst_qll *Q = create_bst_qll();
        bst_qll_enqueue(Q, tree);

        while (Q->len != 0) {
                bst_node *front = bst_qll_dequeue(Q);

                if (front->left != NULL)
                        bst_qll_enqueue(Q, front->left);
                if (front->right != NULL)
                        bst_qll_enqueue(Q, front->right);

                free(front);
        }
        free(Q);
}

int *bst_pre_order(bst_node *tree);
int *bst_in_order(bst_node *tree);
int *bst_post_order(bst_node *tree);

int bst_height(bst_node *tree);
int bst_depth(bst_node *tree);
bool bst_is_balanced(bst_node *tree);

bst_node *bst_rebalance(bst_node *tree);
