#ifndef CHESS_H
#define CHESS_H

// chess unicode
#define B_PAWN          "\u265F"
#define B_ROOK          "\u265C"
#define B_KNIGHT        "\u265E"
#define B_BISHOP        "\u265D"
#define B_QUEEN         "\u265B"
#define B_KING          "\u265A"
#define W_PAWN          "\u2659"
#define W_ROOK          "\u2656"
#define W_KNIGHT        "\u2658"
#define W_BISHOP        "\u2657"
#define W_KING         "\u2654"
#define W_QUEEN          "\u2655"
// pawn rook knight bishop queen king
// haha
#define CHESS_PIECE_LOCAL   [0, 1, 2, 3, 4, 5];
#define CHESS_MOVES        [0, 0]

/*****************************************
 * possible offsets would be the 56 that is queen
 * use symbol for pawn for promotion and use it for identifying if such moves is
 * legal
 * 
 * total moves of every pieces
 * the coordinate of current cell
 * *************************************/

typedef struct chess_piece {
	int coordinate[2];      // get posible chess piece moves
	int square[2];          // 
	int race;               // white pawn moves up and black pawn moves down
        int piece;              // it should be used with visuals
        int is_zero;            // or dead it sounds good for a computer
        char symbol;            // 
        char ascii_symbol[6];
} chess_piece;

/******************************************* 
 * main function of translate chess position 8 + 8 = 16 steps would improve if
 * not lazy.
 *
 * @params const int RANK, const int FILECC
 * ****************************************/ 
int find_chess_idx(const int RANK,
		const int FILECC);

/*******************************************
 * find index where 8 to find row and 8 to find column so 8 * reversed-row +
 * total_column_idx = idx
 *
 * @params char[3] // last value for null terminator return int
 * *******************************************/ 
int get_index_by_chess_position(char chess_position[3]);

/******************************************
 * gives you the possible moves at position xy
 *
 * @params struct chess_piece piece
 * returns *void  
 *
 ****************************************/ 
void set_rook_coordinates(int xy[2],
		int offsets[56][2]);

/*****************************************
 * gives you knight moves at position xy[2]
 *
 * @params struct chess_piece piece
 ****************************************/
void set_knight_coordinates(int xy[2],
		int offsets[56][2]);

/****************************************
 * gives you bishop moves at position xy[2]
 *
 * @params struct chess_piece piece
 ***************************************/
void set_bishop_coordinates(int xy[2],
		int offsets[56][2]);

/***************************************
 * gives you queen moves at position xy[2]
 *
 * @params struct chess_piece piece
 **************************************/
void set_queen_coordinates(int xy[2],
		int offsets[56][2]);

/**************************************
 * gives you king moves at position xy[2]
 *
 * @params struct chess_piece piece
 *************************************/
void set_king_coordinates(int xy[2],
		int offsets[56][2]);

/*************************************
 * gives you pawn moves at position xy[2]
 *
 * @params struct chess_piece piece, char race[1+1]
 ***********************************/
void set_pawn_coordinates(int xy[2],
		int offsets[56][2],
		int race);

/**********************************
 * assign chess piece coordinate
 * 
 * @params int index, int coordinate[2]
 * returns nothing
 ********************************/

void set_coordinate_by_index(int index,
		int coordinate[2]);
/********************************
 * use this to find chess piece by coordinate or to find exactly the place to
 * put the chess piece
 *
 * @params coordinate[2] returns int
 ******************************/
int get_index_by_coordinate(int coordinate[2]);

/*****************************************
 * add ascii based on chess reading such as 1b,etc
 *
 * @params int coordinate[2], int cell[2]
 * returns nothing
 * *************************************/
void set_square_by_coordinate(int coordinate[2],
                int square[2]);

/*****************************************
 * auxillary function that helps with init_chess_pieces
 *
 * @params int i
 * return nothing
 * *************************************/
void init_pieces(int i,
                chess_piece **pieces);

/*****************************************
 * default placement of chess pieces
 * 
 * @params
 * returns
 * *************************************/
chess_piece **init_chess_pieces();

/*****************************************
 * clear one by one dynamically allocated memory
 *
 * @params chess_piece **pieces
 * *************************************/
void clear_chess_pieces(chess_piece **pieces);

/*****************************************
 * show the chess piece in ascii well it's crappy
 * i don't intend to use gtk now since I want to build chess in c
 *
 * @params  chess_piece **pieces
 * @returns
 * *************************************/
void draw_chess_pieces(chess_piece **piece);

/*****************************************
 * auxillary funtion for set_chess_piece_to set coordinates based on the chess
 * piece
 *
 * @params int piece, int xy[2], int coordinates[56][2]
 * *************************************/
void set_coordinates_to_piece(int piece,
                int xy[2],
                int coordinates[56][2]);

/*****************************************
 * auxillary function for set_piece_to for validating legal move
 *
 * @params int dest[2], int coordinates[56][2]
 * *************************************/
int is_chess_piece_move_valid(int dest[2],
                int coordinates[56][2]);

/*****************************************
 * disambiguation should be prefered as it is more complex to implement notations
 * such as N6b it is more simple to use such as usage of file&rank for example
 *
 * N6b5d Knight from 6b goes to 5d 
 * @params char notation[5+1]
 * *************************************/
int set_chess_piece_to_by_char(char notation[6],
                chess_piece **pieces);

#endif // chess.h
