#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "chess_test.h"

void reset_coordinates();
void print_square(int coordinates[56][2], int xy[2], int piece);
void print_chess_piece_err(int err, chess_piece **pieces);

void chess_test()
{
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

	chess_piece **pieces = init_chess_pieces();
	init_rook(pieces); // i have done this so i can test individual chess piece
	init_king(pieces);
	init_knight(pieces);
	init_bishop(pieces);
	init_queen(pieces);
	init_pawn(pieces);
	
	draw_chess_pieces(pieces);
	int ch_len = 0;
	char piece_dest[6] = "\0";
        for (int ch; (ch = getchar()) != EOF;) {
		piece_dest[ch_len++] = ch;

		if (ch_len == 6) {
			int error = set_chess_piece_to_by_char(piece_dest,
					pieces);
			print_chess_piece_err(error, pieces);
			ch_len = 0;
		}
	}
 
	if (feof(stdin))
	    puts("End of file reached");
	else if (ferror(stdin)) {
	    perror("getchar()");
	    fprintf(stderr, "getchar() failed in file %s at line # %d\n",
	            __FILE__, __LINE__ - 9);
	    exit(EXIT_FAILURE);
	}

	free_chess_pieces(pieces);
}

void print_chess_piece_err(int err, chess_piece **pieces)
{
	switch(err) {
	case 5:
		printf("%s", "invalid piece.\n");
		break;
	case 4: 
		puts("invalid destination or source.\n");
		break;
	case 3:
		puts("Don\'t move enemy piece!\n");
		break;
	case 2:
		puts("piece is not here.\n");
		break;
	case 1:
		puts("invalid move.\n");
		break;
	case 0:
		draw_chess_pieces(pieces);
		break;
	}
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


