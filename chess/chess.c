#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "chess.h"
#include "array.h"
#include "merge_sort.h"

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

	bound = white == 1 ? src >= 48 && src < 56 : src >= 7 && src < 16;
	
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
		case 1:
			x = wpawn_offsets[i][0];
			y = wpawn_offsets[i][1];
			break;
		case 2:
			x = bpawn_offsets[i][0];
			y = bpawn_offsets[i][1];
			break;
		}

		int ax = coord[0] + x;
		int ay = coord[1] + y;
		int axy[2] = { ax, ay };
		int dest = get_idx_by_coord(axy);

		if (is_xy_between_ab_inc(ax, ay, 0, 7)
		    && is_pawn_move_valid(i, src, dest))
			push_number(&squares[src].piece_dests, dest);
	}

	Number *number = squares[src].piece_dests;

	merge_sort(number->numbers, 0, number->size-1);
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
			push_number(&squares[src].piece_dests, dest);
	}
	Number *number = squares[src].piece_dests;

	merge_sort(number->numbers, 0, number->size-1);
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

			if (edge == 0 && contain_piece && dest_clr == color)
				edge = 1;

			if (edge == 0 && contain_piece && dest_clr != color) {
				edge = 1;
				push_number(&squares[src].piece_dests, dest);
			}

			if (dest_clr && edge == 0)
				push_number(&squares[src].piece_dests, dest);
			else if (dest_clr == color && edge  == 0
				 && squares[dest].chess_piece == 6
				 && can_castling(color, src, dest))
				push_number(&squares[src].piece_dests, dest);
		}
		
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
	Number *number = squares[src].piece_dests;

	merge_sort(number->numbers, 0, number->size-1);
}

void set_bishop_dests(int coord[2])
{
	int src = get_idx_by_coord(coord);
	int color = squares[src].piece_color;
	int b[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
	int blen = (sizeof(b) / sizeof(b[0])) * 7;
	int edge = 0;
	int j = 0;

	for (int i = 0; i < blen; i++) {
		int x = b[j][0] + coord[0];
		int y = b[j][1] + coord[1];
		int xy[] = { x, y };
		int dest = get_idx_by_coord(xy);

		if (is_xy_between_ab_inc(x, y, 0, 7)) {
			int dest_clr = squares[dest].piece_color;
			int contain_piece = squares[dest].contain_piece;

			if (edge == 0 && contain_piece && dest_clr == color)
				edge = 1;

			if (edge == 0 && contain_piece && dest_clr != color) {
				edge = 1;
				push_number(&squares[src].piece_dests, dest);
			}

			if (dest_clr && edge == 0)
				push_number(&squares[src].piece_dests, dest);
		}

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
			edge = 0;
		}
	}

	Number *number = squares[src].piece_dests;

	merge_sort(number->numbers, 0, number->size-1);
}

void set_queen_dests(int coord[2])
{
	int src = get_idx_by_coord(coord);
	int color = squares[src].piece_color;
	int q[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
		{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
	int qlen = (sizeof q / sizeof q[0]) * 7;
	int j = 0;
	int edge = 0;

	for (int i = 0; i < qlen; i++) {
		int x = coord[0] + q[j][0];
		int y = coord[1] + q[j][1];
		int xy[] = { x, y };
		int dest = get_idx_by_coord(xy);

		
		if (is_xy_between_ab_inc(x, y, 0, 7)) {
			int dest_clr = squares[dest].piece_color;
			int contain_piece = squares[dest].contain_piece;

			if (edge == 0 && contain_piece && dest_clr == color)
				edge = 1;

			if (edge == 0 && contain_piece && dest_clr != color) {
				edge = 1;
				push_number(&squares[src].piece_dests, dest);
			}

			if (dest_clr && edge == 0)
				push_number(&squares[src].piece_dests, dest);
			else if (dest_clr == color && edge  == 0)
				push_number(&squares[src].piece_dests, dest);
		}
	

		switch(j) {
		case 0:
			q[j][1]++;
			break;
		case 1:
			q[j][0]++;
			break;
		case 2:
			q[j][1]--;
			break;
		case 3:
			q[j][0]--;
			break;
		case 4: 
			q[j][0]++;
			q[j][1]++;
			break;
		case 5:
			q[j][0]--;
			q[j][1]++;
			break;
		case 6: 
			q[j][0]++;
			q[j][1]--;
			break;
		case 7: 
			q[j][0]--;
			q[j][1]--;
			break;
		}

		if ((i+1) % 7 == 0) {
			j++;
			edge = 0;
		}
	}

	Number *number = squares[src].piece_dests;

	merge_sort(number->numbers, 0, number->size-1);
}

// pieces are only declared thus only iteration happens in
// each piece color, should thye be ignored if the piece is
// no longer there -1
int b_pieces[16][2] = {{0, 'r'}, {1, 'n'}, {2, 'b'}, {3, 'q'}, {4, 'k'},
	{5, 'b'}, {6, 'n'}, {7, 'r'}, {8, 'e'}, {9, 'e'}, {10, 'e'}, {11, 'e'},
	{12, 'e'}, {13, 'e'}, {14, 'e'}, {15, 'e'}};
int w_pieces[16][2] = {{48, 'e'}, {49, 'e'}, {50, 'e'}, {51, 'e'},
	{52, 'e'}, {53, 'e'}, {54, 'e'}, {55, 'e'}, {56, 'r'}, {57, 'n'},
	{58, 'b'}, {59, 'q'}, {60, 'k'}, {61, 'b'}, {62, 'n'}, {63, 'r'}};
// how to check? check happens when there's still available
// safe destination to go. checkmate happens when there's no
// escape or dest in this case init shouldn't count

int can_king_step_here(int dest, int color)
{
	for (int i = 0; i < 16; i++) {
		int op_src = color == 1 ? b_pieces[i][0] : w_pieces[i][0];
		Number *numbers = squares[op_src].piece_dests;
		int num_len = numbers->size;

		if (num_len <= 0)
			return 1;

		for (int op_step = 0; op_step < num_len; op_step++)
			if (numbers->numbers[op_step] == dest)
				return 0;
	}

	return 1;
}

void set_king_dests(int coord[2])
{
	int k[8][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1},
		{0, -1}, {1, -1}};
	int klen = sizeof(k) / sizeof(k[0]);
	int src = get_idx_by_coord(coord);
	int c = squares[src].piece_color;

	for (int i = 0; i < klen; i++) {
		int x = coord[0] + k[i][0];
		int y = coord[1] + k[i][1];
		int xy[] = { x, y };
		int dest = get_idx_by_coord(xy);
		
		if (is_xy_between_ab_inc(x, y, 0, 7)
		    && can_king_step_here(dest, c)) {
			int dc = squares[dest].piece_color;
			int cp = squares[dest].contain_piece;

			if (cp == 1 && c != dc)
				push_number(&squares[src].piece_dests, dest);

			if (cp != 1)
				push_number(&squares[src].piece_dests, dest);
		}
	}

	Number *number = squares[src].piece_dests;

	merge_sort(number->numbers, 0, number->size-1);
}

void init_pawns()
{
	int e_idxs[] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53,
		54, 55};
	int e_len = sizeof(e_idxs) / sizeof(e_idxs[0]);
	
	for (int i = 0; i < e_len; i++) {
		int pwns = e_idxs[i];
		int coord[] = {-1, -1};

		if (pwns > 15)
			strcpy(squares[pwns].piece_symbol, WPAWN);
		else
			strcpy(squares[pwns].piece_symbol, BPAWN);

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

		if (nidx > 6)
			strcpy(squares[nidx].piece_symbol, WKNIGHT);
		else
			strcpy(squares[nidx].piece_symbol, BKNIGHT);
		
		squares[nidx].piece_notation = 'n';
		squares[nidx].chess_piece = 2;

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

		if (ridx > 15)
			strcpy(squares[ridx].piece_symbol, WROOK);
		else
			strcpy(squares[ridx].piece_symbol, BROOK);

		squares[ridx].special_move = 0;
		squares[ridx].piece_notation = 'r';
		squares[ridx].chess_piece = 3;
		
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

		if (bidx > 5)
			strcpy(squares[bidx].piece_symbol, WBISHOP);
		else
			strcpy(squares[bidx].piece_symbol, BBISHOP);

		squares[bidx].piece_notation = 'b';
		squares[bidx].chess_piece = 4;
		squares[bidx].special_move = 0;

		int xy[] = {-1, -1};

		set_coord_by_idx(xy, bidx);
		set_bishop_dests(xy);
	}

}

void init_queens()
{
	int q[] = {3, 59};
	int qlen = sizeof(q) / sizeof(q[0]);
	
	for (int i = 0; i < qlen; i++) {
		int qidx = q[i];
		int xy[] = {-1, -1};

		if (qidx > 3)
			strcpy(squares[qidx].piece_symbol, WQUEEN);
		else
			strcpy(squares[qidx].piece_symbol, BQUEEN);

		squares[qidx].piece_notation = 'q';
		squares[qidx].chess_piece = 5;
		squares[qidx].special_move = 0;

		set_coord_by_idx(xy, qidx);
		set_queen_dests(xy);
	}
}

void init_kings()
{
	int k[] = {4, 60};
	int klen = sizeof(k) / sizeof(k[0]);

	for (int i = 0; i < klen; i++) {
		int kidx = k[i];

		if (kidx > 4)
			strcpy(squares[kidx].piece_symbol, WKING);
		else
			strcpy(squares[kidx].piece_symbol, BKING);

		squares[kidx].piece_notation = 'k';
		squares[kidx].chess_piece = 6;
		squares[kidx].special_move = 1;

		int xy[] = {-1, -1};

		set_coord_by_idx(xy, kidx);
		set_king_dests(xy);
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

		squares[i].piece_dests = init_number();

		if (i >= 0 && i < 16) {
			squares[i].piece_color = 2;
			squares[i].contain_piece = 1;
		}

		if (i >= 48 && i < 64) {
			squares[i].piece_color = 1;
			squares[i].contain_piece = 1;
		}
	}
	init_pawns();
	init_knights();
	init_rooks();
	init_bishops();
	init_queens();
	init_kings();

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


void destroy_chess_piece_dests()
{
	for (int i = 0; i < 64; i++) {
		Number *number = squares[i].piece_dests;

		clear_number_numbers(&number);	
		destroy_number(&number);
	}
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

char asc[5] = "\0";
char *get_chess_piece_by_number(int number)
{
	switch(number) {
	case 1:
		return "pawn";
	case 2:
		return "knight";
	case 3:
		return "rook";
	case 4:
		return "bishop";
	case 5:
		return "queen";
	case 6:
		return "king";
	default:
		itoa(number, asc);
		return asc;
	}
}

void print_piece_dests()
{
	for (int i = 0; i < 64; i++) {
		Number *number = squares[i].piece_dests;
		int piece_number = squares[i].chess_piece;
		char *chess_piece = get_chess_piece_by_number(piece_number);
	
		printf("%s from %s: moves->", chess_piece,
		       squares[i].square);

		for (int i = 0; i < number->size; i++)
			printf(" %s ", squares[number->numbers[i]].square);

		printf("\n");
	}
}

int get_chess_piece_by_letter(char letter)
{
	switch(letter) {
	case 'b':
		return 4;
	case 'e':
		return 1;
	case 'k':
		return 6;
	case 'n':
		return 2;
	case 'q':
		return 5;
	case 'r':
		return 3;
	default: 
		return 0;
	}
}

int chess_piece_contain_dest(int src, int dest)
{
	Number *steps = squares[src].piece_dests;

	for (int i = 0; i < steps->size; i++) {
		if (steps->numbers[i] == dest)
			return 1;
	}

	return 0;
}

static int piece_turn = 1;
int is_notation_valid(char *notation)
{
	int piece = get_chess_piece_by_letter(notation[0]);

	if (piece == 0)
		return 1; // no such piece

	char src[3] = "\0";
	char dest[3] = "\0";
	int s = 0;
	int d = 0;

	for (int i = 1; i < 3; i++)
		src[s++] = notation[i];
	for (int i = 3; i < 5; i++)
		dest[d++] = notation[i];

	int sidx = get_idx_by_square(src);
	int didx = get_idx_by_square(dest);

	if (sidx == 64 && didx == 64)
		return 2; // over the bound
	if (sidx == 64 || didx == 64)
		return 3; // over the bound from source or dest

	if (squares[sidx].piece_color != piece_turn) // not the players nor
						     // enemies turn
		return 4;

	if (!chess_piece_contain_dest(sidx, didx))
		return 5; // illegal move
		
	return 0;
}

