#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_linked_list.h"

int main()
{
        q_linked_list *q = create_q_linked_list();
        int my_arr[] = { 0, 1 }; 
        int my_arr3[] = { 232, 2543 }; 
        enqueue_q_list_node(q, my_arr);
        enqueue_q_list_node(q, my_arr3);

        int val = size_q_list_node(q);

        printf("%d\n", val);
        destroy_q_list_node(q->head);
        free(q);
        return 0;
};
