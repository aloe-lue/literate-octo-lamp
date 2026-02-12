#ifndef CHESS_H
#define CHESS_H

#include "array.h"

// unicode for chess piece
#define WKING		" \u2654 "
#define WQUEEN		" \u2655 "
#define WROOK		" \u2656 "
#define WBISHOP		" \u2657 "
#define WKNIGHT		" \u2658 "
#define WPAWN		" \u2659 "

#define BKING		" \u265A "
#define BQUEEN		" \u265B "
#define BROOK		" \u265C "
#define BBISHOP		" \u265D "
#define BKNIGHT		" \u265E "
#define BPAWN		" \u265F "

// chess piece
#define PAWN	 	1
#define KNIGHT 		2
#define ROOK 		3
#define BISHOP 		4
#define QUEEN 		5
#define KING 		6

// blank space for drawing chessboard
#define BLACKSQUARE	" ■ "
#define WHITESQUARE	" □ "

typedef struct chess_square {
	int filters[8];
	int piece_color;
	int contain_piece;
	int chess_piece;
	int special_move;
	Number *piece_dests;
	int square_color;
	int coordinate[2];
	char piece_notation;
	char piece_symbol[12];
	char square[3];
} chess_square;

/*
 * translate coord by idx 8x8
 *
 */
void set_coord_by_idx(int coord[2], int idx);

/*
 * translate user coord to idx 8x8
 */
int get_idx_by_coord(int coord[2]);

/*
 * translate idx to square chess notation 8a, 8b, etc.
 */
void set_square_by_idx(char square[3], int idx);

/*
 * hmm 
 */
void set_coord_by_square(int coord[2], char square[3]);

/*
 * aux functions for get idx by square
 */
int get_row_by_rank(const char RANK);
int get_column_by_file(const char FILECC);
/*
 * get index using chess notation
 */
int get_idx_by_square(char square[3]);

/*
 * filter move
 */
int is_xy_between_ab_inc(int x, int y, const int a, const int b);

/*
 * aux func for set pawn dests
 */
int can_pstep_dforward(int src, int dest);
int can_pstep_rdiagonal(int src, int dest);
int can_pstep_ldiagonal(int src, int dest);
int is_pawn_move_valid(int i, int src, int dest);

/*
 * set pawn dests by coord and square
 */
void set_pawn_dests(int coord[2]);

/*
 * give the knight destinations in idx
 */
void set_knight_dests(int coord[2]);

/*
 * aux func that helps with castling
 */
int can_castling(int color, int src, int dest);

/*
 * give the rook destinations in idx
 */
void set_rook_dests(int coord[2]);

/*
 * give the bishop destinations in idx
 */
void set_bishop_dests(int coord[2]);

/*
 * give the queen destinations in idx
 */
void set_queen_dests(int coord[2]);

/*
 * give the king destinations in idx
 */
void set_king_dests(int coord[2]);

/*
 * set default pawn position
 */
void init_pawns();

/*
 * set default rooks position
 */
void init_rooks();

/*
 * set default bishops position
 */
void init_bishops();

/*
 * set default queens position
 */
void init_queens();

/*
 * set default kings position
 */
void init_kings();

/*
 * initialize chessboard
 */
void init_chessboard();


/*
 * print ascii chessboard
 */
void draw_chessboard();

/**
 * helper function for general purpose
 */
char *get_chess_piece_by_number(int number);
/*
 * clear all the piece_dests number numbers
 */
void destroy_chess_piece_dests();

/*
 * useful for debugging piece dests
 */
void print_piece_dests();

void reverse(char s[]);
/*
 * convert int to ascii
 *
 * from K&R
 */
void itoa(int n, char s[]);

#endif // chess.h
