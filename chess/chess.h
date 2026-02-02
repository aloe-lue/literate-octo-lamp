#ifndef CHESS_H
#define CHESS_H

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
	int chess_piece_dests[56];
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
 * filters out diagonal left and right from center
 */
int can_pawn_move_2_blocks_forward(chess_square *squares, int src_idx,
		int dest_idx);

int can_pawn_move_diagonal_left(chess_square *squares, int src_idx,
		int dest_idx);

int can_pawn_move_diagonal_right(chess_square *squares, int src_idx,
		int dest_idx);

/*
 * filters pawn destinations
 */
int is_pawn_move_legal(chess_square *squares, int src_idx, int dest_idx, int i);

/*
 * aux 
 */
int is_xy_between_ab_inc(int x, int y, const int a, const int b);

/*
 * aux func for set pawn dests
 */
void set_pawn_offsets_by_piece_color(int piece_color, int idx, int coord[2]);
/*
 * set pawn dests by coord and square
 */
void set_pawn_dests(chess_square *squares, int coord[2]);

/*
 * set rook offsets malamang
 * this is bad naming
 */
void set_rook_offsets(int rook_offsets[][2], int idx);


void set_rook_dests(chess_square *squares, int coord[2]);


void set_knight_dests(chess_square *squares, int coord[2]);

/*
 * aux function for bishop dests
 */
void set_bishop_offsets(int bishop_offsets[][2], int idx);


void set_bishop_dests(chess_square *squares, int coord[2]);

/*
 * aux function for setqueendests
 */
void set_queen_offsets(int queen_offsets[][2], int idx);


void set_queen_dests(chess_square *squares, int coord[2]);

/*
 * init default pawn position
 */
void init_pawns(chess_square *squares);

/*
 * init default rooks position
 */
void init_rooks(chess_square *squares);


chess_square *init_chess_squares();


void clear_chess_squares(chess_square *squares);

/*
 * print ascii chessboard
 */
void draw_chessboard(chess_square *squares);

/*
 * put the chess piece from here to there.
 */
int set_piece_dest_to(chess_square *squares, const char *NOTATION);


#endif // chess.h
