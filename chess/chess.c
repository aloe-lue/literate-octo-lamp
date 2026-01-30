#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "chess.h"

void set_coord_by_idx(int coord[2], int idx)
{
	int x = idx % 8;
	int y = idx / 8;

	coord[0] = x;
	coord[1] = y;
}

int get_idx_by_coord(int coord[2])
{
	int y = coord[1] * 8;
	int idx = y + coord[0];

	return idx;
}

const char *CHESS_FILES = "abcdefgh";
const char *CHESS_RANKS = "87654321";

void set_square_by_idx(char square[3], int idx)
{
	int x = idx % 8;
	int y = idx / 8;

	square[0] = CHESS_FILES[x];
	square[1] = CHESS_RANKS[y];
}


int get_row_by_rank(const char RANK)
{
	int row = 0;

	for (int i = '8'; i >= '1'; i--) {
		if (RANK == i)
			return row;

		row++;
	}

	return 8;
}


int get_column_by_file(const char FILECC)
{
	int column = 0;

	for (int i = 'a'; i <= 'h'; i++) {
		if (FILECC == i)
			return column;

		column++;
	}

	return 8;
}


int get_idx_by_square(char square[3])
{
	int row = get_row_by_rank(square[0]);
	int column = get_column_by_file(square[1]);

	if (row == 8 || column == 8)
		return 64;

	int idx = (row * 8) + column;

	return idx;
}

void set_coord_by_square(int coord[2], char square[3])
{
	coord[0] = get_column_by_file(square[0]);
	coord[1] = get_row_by_rank(square[1]);
}

static int piece_color_turn  = 1;

int can_pawn_move_2_blocks_forward(chess_square *squares, int src_idx,
		int dest_idx)
{
	if (piece_color_turn == 1 && (src_idx >= 48 && src_idx <= 55)
			&& !squares[dest_idx-8].contain_piece
			&& !squares[dest_idx].contain_piece)
		return 1;

	if (piece_color_turn == 0 && (src_idx >= 8 && src_idx <= 15)
			&& !squares[dest_idx+8].contain_piece
			&& !squares[dest_idx].contain_piece)
		return 1;

	return 0;
}

int can_pawn_move_diagonal_left(chess_square *squares, int src_idx,
		int dest_idx)
{
	int is_left_edge = src_idx % 8 == 0;

	if (piece_color_turn == 1 && !is_left_edge 
			&& (squares[src_idx].special_move == 1
				|| squares[src_idx].special_move == 0)
			&& (src_idx >= 0 && src_idx < 64)
			&& (squares[dest_idx].contain_piece
				&& squares[dest_idx].piece_color == 0))
		return 1;

	if (piece_color_turn == 1 && !is_left_edge
			&& (squares[src_idx].special_move == 1)
			&& (src_idx >= 24 && src_idx <= 31)
			&& (!squares[dest_idx].contain_piece
				&& squares[src_idx-1].piece_color == 0))
		return 1;

	if (piece_color_turn == 0 && !is_left_edge 
			&& (squares[src_idx].special_move == 1
				|| squares[src_idx].special_move == 0)
			&& (src_idx >= 0 && src_idx < 64)
			&& (squares[dest_idx].contain_piece
				&& squares[dest_idx].piece_color == 1))
		return 1;

	if (piece_color_turn == 0 && !is_left_edge
			&& (squares[src_idx].special_move == 1)
			&& (src_idx >= 32 && src_idx <= 40)
			&& (!squares[dest_idx].contain_piece
				&& squares[src_idx-1].piece_color == 1))
		return 1;

	return 0;
}

int can_pawn_move_diagonal_right(chess_square *squares, int src_idx,
		int dest_idx)
{
	int is_right_edge = (src_idx+1) % 8 == 0;

	if (piece_color_turn == 1 && !is_right_edge 
			&& (squares[src_idx].special_move == 1
				|| squares[src_idx].special_move == 0)
			&& (src_idx >= 0 && src_idx < 64)
			&& (squares[dest_idx].contain_piece
				&& squares[dest_idx].piece_color == 0))
		return 1;

	if (piece_color_turn == 1 && !is_right_edge
			&& (squares[src_idx].special_move == 1)
			&& (src_idx >= 24 && src_idx <= 31)
			&& (!squares[dest_idx].contain_piece
				&& squares[src_idx+1].piece_color == 0))
		return 1;

	if (piece_color_turn == 0 && !is_right_edge 
			&& (squares[src_idx].special_move == 1
				|| squares[src_idx].special_move == 0)
			&& (src_idx >= 0 && src_idx < 64)
			&& (squares[dest_idx].contain_piece
				&& squares[dest_idx].piece_color == 1))
		return 1;

	if (piece_color_turn == 0 && !is_right_edge
			&& (squares[src_idx].special_move == 1)
			&& (src_idx >= 32 && src_idx <= 40)
			&& (!squares[dest_idx].contain_piece
				&& squares[src_idx+1].piece_color == 1))
		return 1;

	return 0;
}

int is_pawn_move_legal(chess_square *squares, int src_idx, int dest_idx, int i)
{
	switch (i) {
	case 0:
		if (!squares[dest_idx].contain_piece)
			return 1;
	case 1:
		return can_pawn_move_2_blocks_forward(squares, src_idx,
				dest_idx);
	case 2:
		return can_pawn_move_diagonal_left(squares, src_idx, dest_idx);
	case 3:
		return can_pawn_move_diagonal_right(squares, src_idx, dest_idx);
	default:
		return 0;
	}
}

int is_xy_between_ab_inc(int x, int y, const int a, const int b)
{
	return ((x >= a && x <= b) && (y >= a && y <= b));
}

void set_pawn_offsets_by_piece_color(int piece_color, int idx, int coord[2])
{
	const int WPAWN_OFFSETS[4][2] = {{0,-1}, {0,-2}, {-1,-1}, {1,-1}};
	const int BPAWN_OFFSETS[4][2] = {{0,1}, {0,2}, {-1,1}, {1,1}};

	switch(piece_color) {
	case 0: // black as dark
		coord[0] = BPAWN_OFFSETS[idx][0];
		coord[1] = BPAWN_OFFSETS[idx][1];
		return;
	case 1: // white as light
		coord[0] = WPAWN_OFFSETS[idx][0];
		coord[1] = WPAWN_OFFSETS[idx][1];
		return;
	}
}

void set_pawn_dests(chess_square *squares, int coord[2])
{
	int idx_src = get_idx_by_coord(coord);
	int piece_color = squares[idx_src].piece_color;

	for (int i = 0; i < 4; i++) {
		int xy[2] = {0};

		set_pawn_offsets_by_piece_color(piece_color, i, coord);

		int ax = coord[0] + xy[0];
		int ay = coord[1] + xy[1];
		int axy[2] = { ax, ay };
		int idx = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 7, 7))
			squares[i].chess_piece_dests[i] = idx;
		else 
			squares[i].chess_piece_dests[i] = 999;
	}
}

void set_rook_offsets(int rook_offsets[][2], int idx)
{
	switch(idx) {
	case 0:
		rook_offsets[idx][1]++;
		break;
	case 1:
		rook_offsets[idx][0]++;
		break;
	case 2:
		rook_offsets[idx][1]--;
		break;
	case 3:
		rook_offsets[idx][0]--;
		break;
	}
}

void set_rook_dests(chess_square *squares, int coord[2])
{
	int rook_offsets[][2] = {{0,1}, {1,0}, {0,-1},{-1,0}};
	int r_idx_src = get_idx_by_coord(coord);

	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = rook_offsets[j][0] + x;
		int ay = rook_offsets[j][1] + y;
		int axy[2] = { ax, ay };
		int r_idx_dest = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 7, 7))
			squares[r_idx_src].chess_piece_dests[i] = r_idx_dest;
		else
			squares[r_idx_src].chess_piece_dests[i] = 999;

		set_rook_offsets(rook_offsets, j);

		if ((i+1) % 7 == 0)
			j++;
	}
}

void set_knight_dests(chess_square *squares, int coord[2])
{
	int knight_offsets[8][2] = {{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2},
		{-1,-2}, {-2,-1}, {-2,1}};
	int n_src_idx = get_idx_by_coord(coord);

	for (int i = 0; i < 8; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = knight_offsets[i][0] + x;
		int ay = knight_offsets[i][1] + y;
		int axy[] = {ax,ay};
		int n_idx = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 7, 7) &&
				// it doesn't fall on the same piece color
				squares[n_src_idx].piece_color !=
				squares[n_idx].piece_color)
			squares[n_idx].coordinate[i] = n_idx;
		else
			squares[n_idx].coordinate[i] = 99;
	}
}

void set_bishop_offsets(int bishop_offsets[][2], int idx)
{
	switch(idx) {
	case 0:
		bishop_offsets[idx][0]++;
		bishop_offsets[idx][1]++;
		break;
	case 1:
		bishop_offsets[idx][0]++;
		bishop_offsets[idx][1]--;
		break;
	case 2:
		bishop_offsets[idx][0]--;
		bishop_offsets[idx][1]--;
		break;
	case 3:
		bishop_offsets[idx][0]--;
		bishop_offsets[idx][1]++;
		break;
	}
}

void set_bishop_dests(chess_square *squares, int coord[2])
{
	int bishop_offsets[][2] = {{1,1}, {1,-1}, {-1,-1}, {-1, 1}};
	int b_idx_src = get_idx_by_coord(coord);

	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = bishop_offsets[j][0] + x;
		int ay = bishop_offsets[j][1] + y;
		int axy[] = { ax, ay };
		int b_idx = get_idx_by_coord(axy);
		
		set_bishop_offsets(bishop_offsets, j);

		if ((i+1) % 7 == 0)
			j++;
	}
}

void set_queen_offsets(int queen_offsets[][2], int idx)
{
	switch(idx) {
	case 0: // top
		queen_offsets[idx][1]++;
		break;
	case 1: // right
		queen_offsets[idx][0]++;
		break;
	case 2: // bottom
		queen_offsets[idx][1]--;
		break;
	case 3: // left
		queen_offsets[idx][0]--;
		break;
	case 4: // right top
		queen_offsets[idx][0]++;
		queen_offsets[idx][1]++;
		break;
	case 5: // right bottom
		queen_offsets[idx][0]++;
		queen_offsets[idx][1]--;
		break;
	case 6: // left bottom
		queen_offsets[idx][0]--;
		queen_offsets[idx][1]--;
		break;
	case 7: // left top
		queen_offsets[idx][0]--;
		queen_offsets[idx][1]++;
		break;
	}
}

void set_queen_dests(chess_square *squares, int coord[2])
{
	int queen_offsets[][2] = {{0,1}, {1,0}, {0,-1},{-1,0},
		{1,1}, {1,-1}, {-1,-1}, {-1,1}};

	int j = 0;
	for (int i = 0; i < 56; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = queen_offsets[j][0] + y;
		int ay = queen_offsets[j][1] + x;
		int axy[] = {ax,ay};
		int q_idx = get_idx_by_coord(axy);

		set_queen_offsets(queen_offsets, j);

		if ((i+1) % 7 == 0)
			j++;
	}
}

void set_king_dests(chess_square *squares, int coord[2])
{
	int king_offsets[8][2] = {{-1,1}, {0, 1}, {1,1}, {1,0}, {1,-1}, {0,-1},
		{-1,-1}, {-1,0}};
	int k_idx_src = get_idx_by_coord(coord);

	for (int i = 0; i < 8; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = king_offsets[i][0] + x;
		int ay = king_offsets[i][1] + y;
		int axy[] = { ax, ay };
		int k_idx = get_idx_by_coord(axy);
	}
}

void init_pawns(chess_square *squares)
{
	for (int i = 8; i < 16; i++) {
		int coord[] = {-1,-1};

		set_coord_by_idx(coord, i);
		set_pawn_dests(squares, coord);
		strcpy(squares[i].piece_symbol, BPAWN);

		squares[i].piece_color = 0;
		squares[i].chess_piece = 1;
		squares[i].contain_piece = 1;
		squares[i].piece_notation = 'e';
	}

	for (int i = 48; i < 56; i++) {
		int coord[] = {-1, -1};

		set_coord_by_idx(coord, i);
		set_pawn_dests(squares, coord);
		strcpy(squares[i].piece_symbol, WPAWN);

		squares[i].piece_color = 1;
		squares[i].piece_notation = 'e';
		squares[i].chess_piece = 1;
		squares[i].contain_piece = 1;
	}
}


chess_square *init_chess_squares()
{
	chess_square *squares = malloc(sizeof(chess_square) * 64);

	if (squares == NULL) {
		fprintf(stderr, "init_chess_squares: func = malloc. ");
		exit(EXIT_FAILURE);
	}

	int square_color = 0;
	for (int i = 0; i < 64; i++) {
		set_coord_by_idx(squares[i].coordinate, i);
		set_square_by_idx(squares[i].square, i);

		squares[i].contain_piece = 0;
		squares[i].piece_color = 2;
		squares[i].piece_notation = 'o';
		squares[i].square_color = square_color;

		square_color ? strcat(squares[i].piece_symbol, WHITESQUARE) :
			strcat(squares[i].piece_symbol, BLACKSQUARE);

		if ((i+1) % 8 != 0)
			square_color = square_color == 0 ? 1 : 0;
	}

	return squares;
}

void draw_chessboard(chess_square *squares)
{
	char chessboard[1024] = "\0";
	const char *FILES = "*  a  b  c  d  e  f  g  h  *";
	int rank = 8;

	strcat(chessboard, FILES);
	strcat(chessboard, "\n");

	for (int i = 0; i < 64; i++) {
		char rank_format[] = "%d ";
		int bufs = snprintf(NULL, 0, rank_format, rank);
		char rank_fr[bufs+1];

		snprintf(rank_fr, bufs+1, rank_format, rank);

		if (i % 8 == 0)
			strcat(chessboard, rank_fr);

		strcat(chessboard, squares[i].piece_symbol);

		if ((i+1) % 8 == 0) {
			strcat(chessboard, " ");
			strcat(chessboard, rank_fr);
			strcat(chessboard, "\n");
			rank--;
		}
	}

	strcat(chessboard, FILES);
	puts(chessboard);
}

void clear_chess_squares(chess_square *squares)
{
	free(squares);
}

int piece_by_notation(char piece_notation)
{
	switch(piece_notation) {
	case 'b':
		return BISHOP;
	case 'e':
		return PAWN;
	case 'k':
		return KING;
	case 'n':
		return KNIGHT;
	case 'q':
		return QUEEN;
	case 'r':
		return ROOK;
	default:
		return 0;
	}
}


int set_piece_dest_to(chess_square *squares, const char *NOTATION)
{
	int piece = piece_by_notation(NOTATION[0]);

	if (!piece)
		return 1;

	int j = 0;
        int k = 0;
	char notation_src[3] = "\0";
	char notation_dest[3] = "\0";

	for (int i = 1; i < 3; i++)
		notation_src[j] = NOTATION[i];
	for (int i = 3; i < 5; i++)
		notation_dest[k] = NOTATION[i];
	
	int src_idx = get_idx_by_square(notation_src);	
	int dest_idx = get_idx_by_square(notation_dest);

	if (src_idx == 64 || dest_idx == 64)
		return 2;
	
	return 0;
}


