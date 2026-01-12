#include <assert.h>
#include <stdio.h>
#include "chess_test.h"

void reset_coordinates();
void print_index(int coordinates[56][2], int xy[2]);

void chess_test()
{
	init_chess_pieces();
	
	assert(get_index_by_chess_position("1h") == 63);
	assert(get_index_by_chess_position("1e") == 60);
	assert(get_index_by_chess_position("8e") == 4);
	assert(get_index_by_chess_position("8a") == 0);

	int coordinates[56][2] = {{-1}};
	int xy[2] = {4, 3};
	reset_coordinates(coordinates);
	set_rook_coordinates(xy, coordinates);
	print_index(coordinates, xy);

	set_bishop_coordinates(xy, coordinates);
	print_index(coordinates, xy);

	set_queen_coordinates(xy, coordinates);
	print_index(coordinates, xy);

	set_knight_coordinates(xy, coordinates);
	print_index(coordinates, xy);

	set_knight_coordinates(xy, coordinates);
	print_index(coordinates, xy);
}

void reset_coordinates(int coordinates[56][2])
{
	for (int i = 0; i < 56; i++)
		for (int j = 0; j < 2; j++)
			coordinates[i][j] = 8;
}

void print_index(int coordinates[56][2], int xy[2])
{
	for (int i = 0; i < 56; i++) {
		int ax = coordinates[i][0];
		int ay = coordinates[i][1];
		
		if (xy_is_between_inc(ax, ay))
			printf(" %d %d ", ax, ay);
	}
	puts("\n");
	reset_coordinates(coordinates);
}


