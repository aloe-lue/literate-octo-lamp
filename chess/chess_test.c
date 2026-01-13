#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "chess_test.h"

void reset_coordinates();
void print_square(int coordinates[56][2], int xy[2], int piece);

void chess_test()
{
	chess_piece **pieces = init_chess_pieces();
	
	assert(get_index_by_chess_position("1h") == 63);
	assert(get_index_by_chess_position("1e") == 60);
	assert(get_index_by_chess_position("8e") == 4);
	assert(get_index_by_chess_position("8a") == 0);

	int coordinates[56][2] = {{-1}};
	int xy[2] = {4, 3};
	reset_coordinates(coordinates);
	set_rook_coordinates(xy, coordinates);
	print_square(coordinates, xy, 1);

	set_bishop_coordinates(xy, coordinates);
	print_square(coordinates, xy, 2);

	set_knight_coordinates(xy, coordinates);
	print_square(coordinates, xy, 3);

	set_queen_coordinates(xy, coordinates);
	print_square(coordinates, xy, 4);

	set_king_coordinates(xy, coordinates);
	print_square(coordinates, xy, 5);

	set_pawn_coordinates(xy, coordinates, 1);
	print_square(coordinates, xy, 0);

	draw_chess_pieces(pieces);
	free_chess_pieces(pieces);
}

void reset_coordinates(int coordinates[56][2])
{
	for (int i = 0; i < 56; i++)
		for (int j = 0; j < 2; j++)
			coordinates[i][j] = 8;
}

void print_square(int coordinates[56][2], int xy[2], int piece)
{
	int xy_char[2];
	set_square_by_coordinate(xy, xy_char);
	char piece_char[7] = "\0";
	switch(piece) {
	case 0:
		strcpy(piece_char, "pawn");
		break;
	case 1: 
		strcpy(piece_char, "rook");
		break;
	case 2:
		strcpy(piece_char, "knight");
		break;
	case 3:
		strcpy(piece_char, "bishop");
		break;
	case 4:
		strcpy(piece_char, "queen");
		break;
	case 5:
		strcpy(piece_char, "king");
		break;
	}
	printf("%s from %c%c to \n", piece_char,
			xy_char[1],
			xy_char[0]);
	for (int i = 0; i < 56; i++) {
		int ax = coordinates[i][0];
		int ay = coordinates[i][1];
		int axy[] = {ax, ay};
		int axy_char[2];
		set_square_by_coordinate(axy, axy_char);
		
		if (xy_is_between_inc(ax, ay))
			printf(" %c%c ", axy_char[1], axy_char[0]);
	}
	puts("\n");
	reset_coordinates(coordinates);
}


