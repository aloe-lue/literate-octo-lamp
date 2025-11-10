#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue_linked_list.h"
#include "linked_list.h"
#include "merge_sort.h"
#include "hash_set.h"
#include "binary_search_tree.h"

void rand_num(int *array, int keys);

void rand_num_insert(bst_node **tree);


int main()
{
        const int keys = 100;
        int array[keys];
        rand_num(array, keys);
        bst_node *hando_bst = bst_create(array, keys);
        printf("is balanced? %s \n", bst_is_balanced(hando_bst) != -1 ? "yes" : "nah uh");
        bst_print(hando_bst);

        printf("print in level order traversal.\n");
        list_node *lvl_ord = bst_level_order(&hando_bst);
        print_nodes(&lvl_ord);

        printf("print in preorder traversal.\n");
        list_node *pre_head = NULL;
        list_node *pre_tail = NULL;
        bst_pre_order(hando_bst, &pre_head, &pre_tail);
        print_nodes(&pre_head);

        printf("print in postorder traversal.\n");
        list_node *post_head = NULL;
        list_node *post_tail = NULL;
        bst_post_order(hando_bst, &post_head, &post_tail);
        print_nodes(&post_head);

        printf("print in inorder  traversal.\n");
        list_node *in_head = NULL;
        list_node *in_tail = NULL;
        bst_in_order(hando_bst, &in_head, &in_tail);
        print_nodes(&in_head);

        // clean up operation
        int lvl = nodes_size(&lvl_ord);
        int pre = nodes_size(&pre_head);
        int post = nodes_size(&post_head);
        int inorder = nodes_size(&in_head);
        destroy_nodes(&lvl_ord, lvl, lvl);
        destroy_nodes(&pre_head, pre, pre);
        destroy_nodes(&post_head, post, post);
        destroy_nodes(&in_head, inorder, inorder);

        rand_num_insert(&hando_bst);
        printf("is balanced? %s \n", bst_is_balanced(hando_bst) != -1 ? "yes" : "nah uh");
        bst_print(hando_bst);
              
        bst_node *reb = bst_rebalance(&hando_bst);

        // bst_print(hando_bst);

        printf("is balanced? %s \n", bst_is_balanced(reb) != -1 ? "yes" : "nah uh");
        // bst_print(reb);
        
        printf("print in level order traversal.\n");
        list_node *lvl_ord_2 = bst_level_order(&reb);
        print_nodes(&lvl_ord_2);

        printf("print in preorder traversal.\n");
        list_node *pre_head_2 = NULL;
        list_node *pre_tail_2 = NULL;
        bst_pre_order(reb, &pre_head_2, &pre_tail_2);
        print_nodes(&pre_head_2);

        printf("print in postorder traversal.\n");
        list_node *post_head_2 = NULL;
        list_node *post_tail_2 = NULL;
        bst_post_order(reb, &post_head_2, &post_tail_2);
        print_nodes(&post_head_2);

        printf("print in inorder  traversal.\n");
        list_node *in_head_2 = NULL;
        list_node *in_tail_2 = NULL;
        bst_in_order(reb, &in_head_2, &in_tail_2);
        print_nodes(&in_head_2);

        // clean up operation
        int lvl_2 = nodes_size(&lvl_ord_2);
        int pre_2 = nodes_size(&pre_head_2);
        int post_2 = nodes_size(&post_head_2);
        int inorder_2 = nodes_size(&in_head);
        destroy_nodes(&lvl_ord_2, lvl_2, lvl_2);
        destroy_nodes(&pre_head_2, pre_2, pre_2);
        destroy_nodes(&post_head_2, post_2, post_2);
        destroy_nodes(&in_head_2, inorder_2, inorder_2);

        bst_print(reb);

        bst_destroy(hando_bst);
        bst_destroy(reb);
        return 0;
}


void rand_num(int *array, int keys)
{
        srand(time(NULL)); // use current time as seed for random generator
        
        for (int i = 0; i < keys; i++) 
                array[i] = rand() % 100;
}


void rand_num_insert(bst_node **tree)
{
        for (int i = 0; i < 100; i++) {
                int rando = rand() % 200 + i;
                bst_insert(&(*tree), rando);
        }
}
