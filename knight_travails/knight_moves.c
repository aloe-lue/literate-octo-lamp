#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#include "hash_set.h"
#include "queue_linked_list.h"
#include "knight_moves.h"

const int KNIGHT_OFFSETS[][8] = {
        { 1, 2, }, 
        { -1, 2, }, 
        { 1, -2, },
        { -1, -2, },
        { 2, 1, },
        { 2, -1, },
        { -2, 1, },
        { -2, -1, }
};

void knight_moves(int array[64][2], int src[2], int dest[2])
{
        assert(src[0] >= 0 && src[0] <= 7 && src[1] >= 0 && src[1] <= 7);
        assert(dest[0] >= 0 && dest[0] <= 7 && dest[1] >= 0 && dest[1] <= 7);

        hash_set *visited_set = init_hash_set();
        hash_set_add(&visited_set, src);
        queue_linked_list *queue = init_queue_linked_list();
        enqueue_list_node(&queue, src);
        queue_linked_list *knight_paths[64]; 
        for (int i = 0; i < 64; i++) 
                knight_paths[i] = init_queue_linked_list();

        int knight_paths_idx = 0;
        int error_num[] = { -1, -1 };
        while (queue->size > 0) {
                int x = front_list_node(&queue, error_num)->keys[0];
                int y = front_list_node(&queue, error_num)->keys[1];
                int xy[] = { x, y };

                if (x == -1 && y == -1 ||
                                hash_set_has(&visited_set, dest))
                        break;
                enqueue_list_node(&knight_paths[knight_paths_idx], xy);

                for (int i = 0; i < 8; i++) {
                      int kx = 0;
                      int ky = 0;

                      kx = x + KNIGHT_OFFSETS[i][0];
                      ky = y + KNIGHT_OFFSETS[i][1];

                      int kxy[] = { kx, ky };
                      if ((kx >= 0 && kx <= 7) &&
                                      (ky >= 0 && ky <= 7) &&
                                      !hash_set_has(&visited_set, kxy)) {
                                enqueue_list_node(&queue, kxy);
                                enqueue_list_node(&knight_paths[knight_paths_idx], kxy);
                                hash_set_add(&visited_set, kxy);
                      }
                }
                knight_paths_idx += 1;
                dequeue_list_node(&queue);
        }
        int x = dest[0];
        int y = dest[1];
        int min_moves = 0;

        for (int i = knight_paths_idx-1; i >= 0; i--) {
                list_node *head = knight_paths[i]->head;
                int hx = head->keys[0];
                int hy = head->keys[1];

                while (head != NULL) {
                        if (head->keys[0] == x &&
                                        head->keys[1] == y) {
                                for (int j = 0; j < 2; j++) 
                                        array[i][j] = head->keys[j];
                                x = hx;
                                y = hy;
                                min_moves++;
                                break;
                        }
                        head = head->next;
                }
        }
        printf("you made it in %d move%s here\'s your path. \n", 
                        min_moves, 
                        min_moves > 1 ? "s." : ".");
        printf(" [%d, %d] \n", src[0], src[1]);
        for (int i = 0; i < knight_paths_idx; i++) {
                if (array[i][0] != -1 && array[i][1] != -1)
                        printf(" [%d, %d] %s",
                                        array[i][0],
                                        array[i][1], "\n");
        } 

        // clean up operation        
        for (int i = 0; i < 64; i++) {
                int knight_paths_size = knight_paths[i]->size;
                destroy_hash_set_nodes(&knight_paths[i]->head, 
                                knight_paths_size, 
                                knight_paths_size);
        }

        destroy_hash_set(&visited_set);
        int q_size = hash_set_nodes_size(&queue->head);
        destroy_hash_set_nodes(&queue->head, q_size, q_size);
        free(queue);
}
