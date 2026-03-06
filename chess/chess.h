#ifndef CHESS_H
#define CHESS_H

<<<<<<< HEAD
#define WHITE	 		1
#define BLACK	 	 	0
#define ROOKUP	 		0
#define ROOKBOTTOM 		1
#define ROOKRIGHT 		2
#define ROOKLEFT 		3

#define BISHOPTOPRIGHT  	0
#define BISHOPBOTTOMRIGHT	1
#define BISHOPBOTTOMLEFT	2
#define BISHOPTOPLEFT		3

#define WKING  		"\u2654"
#define WQUEEN  	"\u2655"
#define WROOK  		"\u2656"
#define WBISHOP  	"\u2657"
#define WKNIGHT  	"\u2658"
#define WPAWN  		"\u2659"

#define BKING  		"\u265A"
#define BQUEEN  	"\u265B"
#define BROOK  		"\u265C"
#define BBISHOP  	"\u265D"
#define BKNIGHT  	"\u265E"
#define BPAWN  		"\u265F"
/*
 *  chess piece from 0 to 5 e, r, n, b, q, k
 *  piece color = black or white
 *  square color = black or white
 *  cell contain piece ? == true or false 
 *  coordinateXY [x, y] = 0, 0
 *  coordinates[56][2] = [0, 0], [1, 1], etc.
 *  square = 1b 2b 3b
 *  piece symbol = ♛
 */
typedef struct chess_square {
	int chess_piece;
	int piece_color;
	int square_color;
	int contain_piece;
	int coordinate[2];
	int chess_piece_dests[56];
	int special_move;
	char piece_notation;
	char square[3];
	char piece_symbol[6];
} chess_square;

/*
 * init chess squares
 */
chess_square *InitChessSquare();

/*
 * free init chess square
 */
void ClearChessSquare(chess_square *squares);

/*
 * helps init chess squares
 */
void SetCoordByIdx(int coord[2], int idx);

/*
 * helps chess piece dests
 */
int GetIdxByCoord(int coord[2]);

/* 
 * set square by idx  
 */
void SetSquareByIdx(char square[3], int idx);

/*
 * help avoid going the bound
 *
 */
int IsXYBetweenAB(int x, int y, const int a, const int b);

/*
 * helps filters out illegal pawn move
 */
int IsPawnMoveLegal(chess_square *squares, int coord[2], int i);

/*
 * sets pawn coords in idx 
 */
void SetPawnDests(chess_square *squares, int coord[2]);

/*
 * set rook coords in idx
 */
void SetRookDests(chess_square *squares, int coord[2]);

/*
 * set knight coords in idx
 */
void SetKnightDests(chess_square *square, int coord[2]);

/*
 * set queen coords in idx
 */
void SetQueenDests(chess_square *square, int coord[2]);

/*
 * init default pawns position
 */
void InitPawns(chess_square *squares);
=======
#include "array.h"
#include "doubly_linked_list.h"

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
 * cheating king
 */
int can_king_step_here(int dest, int color);
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

/*
 * snippet from the book.
 * convert int to ascii and reverse
 * legendary code. indeed!
 * from K&R
 */
void reverse(char s[]);


void itoa(int n, char s[]);

/*
 * helps validates piece notation
 */
int get_chess_piece_by_letter(char letter);

/*
 * returns true if chess piece contain dest even dough(what? a bread) it's
 * not
 */
int chess_piece_contain_dest(int src, int dest);

void reset_pieces_dests();

/*
 * input validation for chess notation 
 */
int is_notation_valid(char *notation, char *src, char *dest);

/*
 * set chess piece dest hmm bad naming but it meant move piece
 */
void set_chess_piece_dest(dlinked_list **game_Q, dlinked_list **dbg_Q,
			  char *notation, int invalid, dlinked_list **black_Q,
			  dlinked_list **white_Q);

/*
 * main function that plays chess.
 */
void play_chess_user_inputs(void);
>>>>>>> chess

#endif // chess.h
