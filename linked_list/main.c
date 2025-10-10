#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "linked_list.h"

int main()
{
        list_node *head = NULL;
        append_node(&head, "anteater");
        append_node(&head, "bear");
        append_node(&head, "cat");
        append_node(&head, "dog");
        preppend_node(&head, "horse");
        append_node(&head, "wolf");
        print_nodes(&head);
        int wolf_idx = find_node(&head, "wolf");
        printf("wolf is found at index %d\n", wolf_idx);
        int head_size1 = nodes_size(&head);
        printf("linked list size %d\n", head_size1);

        printf("test remove node at and insert node at methods \n");
        insert_node_at(&head, "capybara", 3);
        remove_node_at(&head, 3);
        insert_node_at(&head, "capybara", 3);
        preppend_node(&head, "dolphin");
        insert_node_at(&head, "ant", 0);
        insert_node_at(&head, "moth", 10);
        remove_node_at(&head, 9);
        remove_node_at(&head, 0);
        insert_node_at(&head, "goth girl", 10);

        print_nodes(&head);
        int head_size2 = nodes_size(&head);
        printf("linked list size %d\n", head_size2);

        // free after use
        destroy_nodes(&head);
        printf("\n");

        return 0;
}
