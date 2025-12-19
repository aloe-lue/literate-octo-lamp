#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>
// chess symbols
#define WHITE_KING_SYMBOL       "\u2654"
#define WHITE_QUEEN_SYMBOL      "\u2655"
#define WHITE_ROOK_SYMBOL       "\u2656"
#define WHITE_BISHOP_SYMBOL     "\u2657"
#define WHITE_KNIGHT_SYMBOL     "\u2658"
#define WHITE_PAWN_SYMBOL       "\u2659"
#define BLACK_KING_SYMBOL       "\u265A"
#define BLACK_QUEEN_SYMBOL      "\u265B"
#define BLACK_ROOK_SYMBOL       "\u265C"
#define BLACK_BISHOP_SYMBOL     "\u265D"
#define BLACK_KNIGHT_SYMBOL     "\u265E"
#define BLACK_PAWN_SYMBOL       "\u265F"

static int coordinate = 0; 

typedef struct chess_piece {
        char symbol[5];
        char race;
        int index_position;
        bool is_here;
} chess_piece;
/*******************
 * init chess board
 *
 * helper function that deals with cells
 * such as 1a 2b 3b etc
 ******************/
void init_chess_board();

/***************** 
 * translate coordinate
 *
 * finds the index of the given xy that is "1b, 1a, etc."
 *******************/ 
int translate_coordinate_char(const char *xy);

/***************** 
 * give chess piece
 *
 * gives the symbol of the chess piece by i
 *
 ******************/ 
const char *give_chess_piece(int i);

/***************** 
 * draw chessboard
 *
 * i dunno how to do this really 
 *****************/  
void draw_chessboard();

/**********************
 * defaults the chess pieces position
 *********************/
void init_chess_pieces();

/**
 * well draw chess
 *
 *
 *
 */
void draw_chess();

#endif
