#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "doubly_linked_list.h"
#include "dll_test.h"
#include "merge_sort.h"
#include "array.h"

int main()
{
	// dll_test();
	// int usorted[] = {128, 64, 32, 16, 8, 4, 2, 0};
	// int usortedlen = sizeof(usorted) / sizeof(usorted[0]);
	// merge_sort(usorted, 0, usortedlen-1);
	// for (int i = 0; i < usortedlen; i++)
	// 	printf(" %d ", usorted[i]);

	// Number *number = init_number();

	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);
	// push_number(&number, 5);

	// merge_sort(number->numbers, 0, number->size-1);
	// clear_number_numbers(&number);

	// print_numbers(&number);

	// push_number(&number, 6);
	// push_number(&number, 7);
	// push_number(&number, 5);
	// push_number(&number, 8);
	// push_number(&number, 5);
	// push_number(&number, 2);

	// merge_sort(number->numbers, 0, number->size-1);

	// print_numbers(&number);


	// clear_number_numbers(&number);
	// destroy_number(&number);

	init_chessboard();

	print_piece_dests();

	draw_chessboard();

	play_chess_user_inputs();
	
	destroy_chess_piece_dests();
	
	return 0;
}
