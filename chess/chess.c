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
	int r = get_row_by_rank(square[0]);
	int c = get_column_by_file(square[1]);

	if (r == 8 || c == 8)
		return 64;

	int i = (r * 8) + c;

	return i;
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
	if (squares[src_idx].piece_color == 1
			&& (src_idx >= 48 && src_idx <= 55)
			&& !squares[src_idx-8].contain_piece
			&& !squares[dest_idx].contain_piece)
		return 1;

	if (squares[src_idx].piece_color == 0
			&& (src_idx >= 8 && src_idx <= 15)
			&& !squares[src_idx+8].contain_piece
			&& !squares[dest_idx].contain_piece)
		return 1;

	return 0;
}

int can_pawn_move_diagonal_left(chess_square *squares, int src_idx,
		int dest_idx)
{
	int is_left_edge = src_idx % 8 == 0;

	if (squares[src_idx].piece_color == 1 && !is_left_edge 
			&& (squares[src_idx].special_move == 1
				|| squares[src_idx].special_move == 0)
			&& (src_idx >= 0 && src_idx < 64)
			&& (squares[dest_idx].contain_piece
				&& squares[dest_idx].piece_color == 0))
		return 1;

	if (squares[src_idx].piece_color == 1 && !is_left_edge
			&& (squares[src_idx].special_move == 1)
			&& (src_idx >= 24 && src_idx <= 31)
			&& (!squares[dest_idx].contain_piece
				&& squares[src_idx-1].piece_color == 0))
		return 1;

	if (squares[src_idx].piece_color == 0 && !is_left_edge 
			&& (squares[src_idx].special_move == 1
				|| squares[src_idx].special_move == 0)
			&& (src_idx >= 0 && src_idx < 64)
			&& (squares[dest_idx].contain_piece
				&& squares[dest_idx].piece_color == 1))
		return 1;

	if (squares[src_idx].piece_color == 0 && !is_left_edge
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
/*
 * implement pawn promotion by returning a different value
 * 5-2 from queen to knight
 */
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

void set_pawn_dests(chess_square *squares, int coord[2])
{
	int src = get_idx_by_coord(coord);
	int piece_color = squares[src].piece_color;
	int wpawn_offsets[4][2] = {{0,-1}, {0,-2}, {-1,-1}, {1,-1}};
	int bpawn_offsets[4][2] = {{0,1}, {0,2}, {-1,1}, {1,1}};

	for (int i = 0; i < 4; i++) {
		int x = 0;
		int y = 0;

		switch(piece_color) {
		case 0: // black as dark
			x = bpawn_offsets[i][0];
			y = bpawn_offsets[i][1];
			break;
		case 1: // white as light
			x = wpawn_offsets[i][0];
			y = wpawn_offsets[i][1];
			break;
		}

		int ax = coord[0] + x;
		int ay = coord[1] + y;
		int axy[2] = { ax, ay };
		int dest = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 0, 7)
				&& is_pawn_move_legal(squares, src, dest, i))
			squares[src].chess_piece_dests[i] = dest;
		else 
			squares[src].chess_piece_dests[i] = -1;
	}
}

int is_rook_mv_legal(chess_square *squares, int src, int dest, int skips,
		int leave)
{
}

void set_rook_dests(chess_square *squares, int coord[2])
{
	int offsets[4][2] = {{0,1}, {1,0}, {0,-1},{-1,0}};
	int src = get_idx_by_coord(coord);
	int filters[4] = {0};
	int j = 0;

	for (int i = 0; i < 28; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = offsets[j][0] + x;
		int ay = offsets[j][1] + y;
		int axy[] = { ax, ay };
		int dest = get_idx_by_coord(axy);
		

		if (is_xy_between_ab_inc(ax, ay, 0, 7))
			squares[src].chess_piece_dests[i] = dest;
		else 
			squares[src].chess_piece_dests[i] = dest;

		switch(j) {
		case 0:  /* bottom */ 
			offsets[j][1]++;
			break;
		case 1: /* right */
			offsets[j][0]++;
			break;
		case 2: /* top */
			offsets[j][1]--;
			break;
		case 3: /* left */
			offsets[j][0]--;
			break;
		}

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
		int n_dest_idx = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 7, 7)
				&& squares[n_src_idx].piece_color !=
				squares[n_dest_idx].piece_color)
			squares[n_src_idx].coordinate[i] = n_dest_idx;
		else
			squares[n_src_idx].coordinate[i] = 99;
	}
}

void set_bishop_offsets(int bishop_offsets[][2], int idx)
{
	switch(idx) {
	case 0: /* right top */
		bishop_offsets[idx][0]++;
		bishop_offsets[idx][1]++;
		break;
	case 1: /* right bottom */
		bishop_offsets[idx][0]++;
		bishop_offsets[idx][1]--;
		break;
	case 2: /* left bottom */
		bishop_offsets[idx][0]--;
		bishop_offsets[idx][1]--;
		break;
	case 3: /* left top */
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
	int e_idxs[] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53,
		54, 55};
	int e_len = sizeof e_idxs / sizeof e_idxs[0];
	
	for (int i = 0; i < e_len; i++) {
		int pwns = e_idxs[i];
		int coord[] = {-1, -1};


		if (pwns > 15) {
			squares[pwns].piece_color = 1;
			strcpy(squares[pwns].piece_symbol, WPAWN);
		} else {
			squares[pwns].piece_color = 0;
			strcpy(squares[pwns].piece_symbol, BPAWN);
		}

		squares[pwns].contain_piece = 1;
		squares[pwns].special_move = 1;
		squares[pwns].piece_notation = 'e';
		squares[pwns].chess_piece = 1;

		set_coord_by_idx(coord, pwns);
		set_pawn_dests(squares, coord);
	}
}

void init_knights(chess_square *squares)
{
	int n_idxs[] = {1, 6, 55, 62};
	int n_idxs_len = sizeof n_idxs / sizeof n_idxs[0];

	for (int i = 0; i < n_idxs_len; i++) {
		int ns = n_idxs[0];
		int coord[] = {-1, -1};

		set_coord_by_idx(coord, i);
		set_knight_dests(squares, coord);

		if (ns > 6) {
			squares[ns].piece_color = 1;
			strcpy(squares[ns].piece_symbol, WKNIGHT);
		} else {
			squares[ns].piece_color = 0;
			strcpy(squares[ns].piece_symbol, BKNIGHT);
		}

		squares[ns].contain_piece = 1;
		squares[ns].piece_notation = 'n';
		squares[ns].chess_piece = 2;
	}
}

void init_rooks(chess_square *squares)
{
	int r_idxs[] = {0, 7, 56, 63};
	int r_len = sizeof r_idxs / sizeof r_idxs[0];

	for (int i = 0; i < r_len; i++) {
		int rks = r_idxs[i];
		int coord[] = {-1, -1};

		
		if (rks > 7) {
			squares[rks].piece_color = 1;
			strcpy(squares[rks].piece_symbol, WROOK);
		} else {
			squares[rks].piece_color = 0;
			strcpy(squares[rks].piece_symbol, BROOK);
		}
		

		squares[rks].contain_piece = 1;
		squares[rks].piece_notation = 'r';
		squares[rks].chess_piece = 3;

		set_coord_by_idx(coord, rks);	
 		set_rook_dests(squares, coord);
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

	strcat(chessboard, "\n");
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
	if (squares[src_idx].chess_piece != piece_color_turn)
		return 3;
	
	return 0;
}


