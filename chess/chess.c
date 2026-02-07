#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "chess.h"

chess_square squares[64];

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

int is_xy_between_ab_inc(int x, int y, const int a, const int b)
{
	return ((x >= a && x <= b) && (y >= a && y <= b));
}

int can_pstep_forward(int src, int dest)
{
	if (!squares[dest].contain_piece)
		return 1;

	return 0;
}

int can_pstep_dforward(int src, int dest)
{
	int white = squares[src].piece_color;
	int bound;

	bound = white ? src >= 48 && src < 56 : src >= 7 && src < 16;
	
	if (!bound)
		return 0;

	if (white && (squares[dest+8].contain_piece
	    || squares[dest].contain_piece))
		return 0;

	if (!white && (squares[dest-8].contain_piece
	    || squares[dest].contain_piece))
		return 0;

	return 1;
}

int can_pstep_rdiagonal(int src, int dest)
{
	int piece_color = squares[src].piece_color;
	int is_enemy = piece_color ? 0 : 1;
	
	if (squares[dest].contain_piece)
		return squares[dest].piece_color == is_enemy;

	int en_passant_bound = is_enemy ?
		src > 31 && src < 39 :
		src > 23 && src < 31;

	if (!en_passant_bound)
		return 0;

	if (squares[src+1].contain_piece
	    && squares[src+1].piece_color == is_enemy)
		return 1;
	
	return 0;
}

int can_pstep_ldiagonal(int src, int dest)
{
	int piece_color = squares[src].piece_color;
	int is_enemy = piece_color ? 0 : 1;
	
	if (squares[dest].contain_piece)
		return squares[dest].piece_color == is_enemy;

	int en_passant_bound = is_enemy ?
		src > 32 && src < 40 :
		src > 24 && src < 32;

	if (!en_passant_bound)
		return 0;

	if (squares[src-1].contain_piece
	    && squares[src-1].piece_color == is_enemy)
		return 1;
	
	return 0;
}

int is_pawn_move_valid(int i, int src, int dest)
{
	switch(i) {
	case 0:
		return can_pstep_forward(src, dest);
	case 1:
		return can_pstep_dforward(src, dest);
	case 2:
		return can_pstep_ldiagonal(src, dest);
	case 3:
		return can_pstep_rdiagonal(src, dest);
	default:
		return 0;
	}
}

void set_pawn_dests(int coord[2])
{
	int src = get_idx_by_coord(coord);
	int piece_color = squares[src].piece_color;
	int wpawn_offsets[4][2] = {{0,-1}, {0,-2}, {-1,-1}, {1,-1}};
	int bpawn_offsets[4][2] = {{0,1}, {0,2}, {-1,1}, {1,1}};

	for (int i = 0; i < 4; i++) {
		int x = 0;
		int y = 0;

		switch(piece_color) {
		case 0:
			x = bpawn_offsets[i][0];
			y = bpawn_offsets[i][1];
			break;
		case 1:
			x = wpawn_offsets[i][0];
			y = wpawn_offsets[i][1];
			break;
		}

		int ax = coord[0] + x;
		int ay = coord[1] + y;
		int axy[2] = { ax, ay };
		int dest = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 0, 7)
		    && is_pawn_move_valid(i, src, dest))
			squares[src].piece_dests[i] = dest;
		else 
			squares[src].piece_dests[i] = -1;
	}
}

void set_knight_dests(int coord[2])
{
	int n[][2] = {{1, 2}, {-1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2},
		{-2, 1}, {-2, -1}};
	int nlen = sizeof(n) / sizeof(n[0]);
	int src = get_idx_by_coord(coord);
	int color = squares[src].piece_color;

	for (int i = 0; i < nlen; i++) {
		int x = coord[0] + n[i][0];
		int y = coord[1] + n[i][1];
		int xy[] = { x, y };
		int dest = get_idx_by_coord(xy);

		if (is_xy_between_ab_inc(x, y, 0, 7)
		    && squares[dest].piece_color != color)
			squares[src].piece_dests[i] = dest;
		else 
			squares[src].piece_dests[i] = -1;
	}
}

int can_castling(int color, int src, int dest)
{
	int bound = color == 1 ? src > 31 : src < 32;

	if (!bound)
		return 0;

	for (int ledge = 0; ledge < 57; ledge += 8) {
		int redge = ledge + 7;

		if (src >= ledge && src <= redge && dest >= ledge
		    && dest <= redge)
			return 1;
	}

	return 0;
}
/*
 * allow rook move to be in king's place within their ranks.
*/
void set_rook_dests(int coord[2])
{
	int src = get_idx_by_coord(coord);
	int color = squares[src].piece_color;
	int r[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int j = 0;
	int edge = 0;

	for (int i = 0; i < 28; i++) {
		int x = coord[0] + r[j][0];
		int y = coord[1] + r[j][1];
		int xy[] = { x, y };
		int dest = get_idx_by_coord(xy);

		if (is_xy_between_ab_inc(x, y, 0, 7)) {
			int dest_clr = squares[dest].piece_color;
			int contain_piece = squares[dest].contain_piece;

			if (contain_piece && dest_clr == color) {
				edge = 1;
				squares[src].piece_dests[i] = -1;
			}

			if (contain_piece && dest_clr != color) {
				edge = 1;
				squares[src].piece_dests[i] = dest;
			}

			if (dest_clr && edge == 0)
				squares[src].piece_dests[i] = dest;
			else if (dest_clr == color
				 && squares[dest].chess_piece == 6
				 && can_castling(color, src, dest))
				squares[src].piece_dests[i] = dest;
			else
				squares[src].piece_dests[i] = -1;
		} else 
			squares[src].piece_dests[i] = -1;
		
		switch(j) {
		case 0:
			r[j][1]++;
			break;
		case 1:
			r[j][0]++;
			break;
		case 2:
			r[j][1]--;
			break;
		case 3:
			r[j][0]--;
			break;
		}

		int last_step_bound = (i+1) % 7 == 0;

		if (last_step_bound) {
			j++;
			edge = 0;
		}
	}
}

void set_bishop_dests(int coord[2])
{
	int src = get_idx_by_coord(coord);
	int color = squares[src].piece_color;
	int b[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
	int blen = (sizeof(b) / sizeof(b[0])) * 7;
	int bedge = 0;
	int j = 0;

	for (int i = 0; i < blen; i++) {
		int x = b[j][0] + coord[0];
		int y = b[j][1] + coord[1];
		int xy[] = { x, y };
		int dest = get_idx_by_coord(xy);

		if (is_xy_between_ab_inc(x, y, 0, 7)) {
			int dest_clr = squares[dest].piece_color;
			int contain_piece = squares[dest].contain_piece;

			if (contain_piece && dest_clr == color) {
				bedge = 1;
				squares[src].piece_dests[i] = -1;
			}

			if (contain_piece && dest_clr != color) {
				bedge = 1;
				squares[src].piece_dests[i] = dest;
			}

			if (dest_clr && bedge == 0)
				squares[src].piece_dests[i] = dest;
			else
				squares[src].piece_dests[i] = -1;
		
		} else 
			squares[src].piece_dests[i] = -1;

		switch(j) {
		case 0: 
			b[j][0]++;
			b[j][1]++;
			break;
		case 1:
			b[j][0]--;
			b[j][1]++;
			break;
		case 2: 
			b[j][0]++;
			b[j][1]--;
			break;
		case 3: 
			b[j][0]--;
			b[j][1]--;
			break;
		}

		int bound_last_step = (i+1) % 7 == 0;

		if (bound_last_step) {
			j++;
			bedge = 0;
		}
	}

}

void init_pawns()
{
	int e_idxs[] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53,
		54, 55};
	int e_len = sizeof(e_idxs) / sizeof(e_idxs[0]);
	
	for (int i = 0; i < e_len; i++) {
		int pwns = e_idxs[i];
		int coord[] = {-1, -1};

		if (pwns > 15) {
			squares[pwns].piece_color = 1;
			strcpy(squares[pwns].piece_symbol, WPAWN);
		} else {
			squares[pwns].piece_color = 2;
			strcpy(squares[pwns].piece_symbol, BPAWN);
		}

		squares[pwns].contain_piece = 1;
		squares[pwns].special_move = 1;
		squares[pwns].piece_notation = 'e';
		squares[pwns].chess_piece = 1;

		set_coord_by_idx(coord, pwns);
		set_pawn_dests(coord);
	}
}

void init_knights()
{
	int n[] = {1, 6, 57, 62};
	int nlen = sizeof(n) / sizeof(n[0]);

	for (int i = 0; i < nlen; i++) {
		int nidx = n[i];

		if (nidx > 6) {
			squares[nidx].piece_color = 1;
			strcpy(squares[nidx].piece_symbol, WKNIGHT);
		} else {
			squares[nidx].piece_color = 2;
			strcpy(squares[nidx].piece_symbol, BKNIGHT);
		}
		
		squares[nidx].contain_piece = 1;
		squares[nidx].piece_notation = 'n';
		squares[nidx].chess_piece = 2;
	}

	for (int i = 0; i < nlen; i++) {
		int nidx = n[i];
		int xy[] = { -1, -1 };

		set_coord_by_idx(xy, nidx);
		set_knight_dests(xy);
	}
}

void init_rooks()
{
	int r[] = {0, 7, 56, 63};
	int rlen = sizeof(r) / sizeof(r[0]);

	for (int i = 0; i < rlen; i++) {
		int ridx = r[i];

		if (ridx > 15) {
			squares[ridx].piece_color = 1;
			strcpy(squares[ridx].piece_symbol, WROOK);
		} else {
			squares[ridx].piece_color = 2;
			strcpy(squares[ridx].piece_symbol, BROOK);
		}

		squares[ridx].contain_piece = 1;
		squares[ridx].special_move = 0;
		squares[ridx].piece_notation = 'r';
		squares[ridx].chess_piece = 3;
		
	}
	for (int i = 0; i < rlen; i++) {
		int ridx = r[i];
		int xy[] = {-1, -1};

		set_coord_by_idx(xy, ridx);
		set_rook_dests(xy);
	}
}

void init_bishops()
{
	int b[] = {2, 5, 58, 61};
	int blen = sizeof(b) / sizeof(b[0]);

	for (int i = 0; i < blen; i++) {
		int bidx = b[i];

		if (bidx > 5) {
			squares[bidx].piece_color = 1;
			strcpy(squares[bidx].piece_symbol, WBISHOP);
		} else {
			squares[bidx].piece_color = 2;
			strcpy(squares[bidx].piece_symbol, BBISHOP);
		}

		squares[bidx].piece_notation = 'b';
		squares[bidx].chess_piece = 4;
		squares[bidx].special_move = 0;
		squares[bidx].contain_piece = 1;
	}
	for (int i = 0; i < blen; i++) {
		int bidx = b[i];
		int xy[] = {-1, -1};

		set_coord_by_idx(xy, bidx);
		set_bishop_dests(xy);
	}
}

void print_piece_dests(int piece)
{
	for (int i = 0; i < 56; i++) {
		int dest = squares[2].piece_dests[i];
		char square[3] = "\0";
		set_square_by_idx(square, dest);
		
		printf(" %c%c ", square[0], square[1]);
	}
}

void init_chessboard()
{
	int square_color = 0;

	for (int i = 0; i < 64; i++) {
		set_coord_by_idx(squares[i].coordinate, i);
		set_square_by_idx(squares[i].square, i);

		squares[i].contain_piece = 0;
		squares[i].piece_color = -1;
		squares[i].piece_notation = 'o';
		squares[i].square_color = square_color;

		square_color ? strcat(squares[i].piece_symbol, WHITESQUARE) :
			strcat(squares[i].piece_symbol, BLACKSQUARE);

		if ((i+1) % 8 != 0)
			square_color = square_color == 0 ? 1 : 0;

		for (int j = 0; j < 56; j++)
			squares[i].piece_dests[j] = -1;
	}
	// init_pawns();
	// init_knights();
	// init_rooks();
	init_bishops();

}

void draw_chessboard()
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




