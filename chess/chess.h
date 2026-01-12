#ifndef CHESS_H
#define CHESS_H

// chess unicode
#define B_PAWN          " \u265F "
#define B_ROOK          " \u265C "
#define B_KNIGHT        " \u265E "
#define B_BISHOP        " \u265D "
#define B_QUEEN         " \u265B "
#define B_KING          " \u265A "
#define W_PAWN          " \u2659 "
#define W_ROOK          " \u2656 "
#define W_KNIGHT        " \u2658 "
#define W_BISHOP        " \u2657 "
#define W_KING          " \u2654 "
#define W_QUEEN         " \u2655 "
// pawn rook knight bishop queen king
// haha
#define CHESS_PIECE_LOCAL   [0, 1, 2, 3, 4, 5];
#define CHESS_MOVES        [0, 0]

/*****************************************
 * use coordinate for validating moves of a chess move depending on the piece
 * race on the other hand is when you go with pawn moves and en passant move
 * is zero is when a piece is dead maybe not needed ascii symbol is when you
 * use it for special chess character unicode or black and white just not black
 * and white then chess character unicode
 * 
 * *************************************/
typedef struct chess_piece {
	int coordinate[2];
	int square[2];
	int race;
        int piece;
        int is_zero;
        char symbol;
        char ascii_symbol[6];
        int clr;
} chess_piece;

/******************************************************************************
 * auxillary functions that helps with between bound inclusive values 
 * 0 <= n <= 7
 *
 * ***************************************************************************/
int xy_is_between_inc(int x, int y);

/******************************************************************************
 * auxillary functions that helps with finding square[num, alpha]
 * 
 * ***************************************************************************/
void set_square_x(int coordinate[2], int square[2]);
void set_square_y(int coordinate[2], int square[2]);

/******************************************************************************
 * auxillary function that helps helps with finding index
 *
 * ***************************************************************************/
int get_rank_row(const int RANK);
int get_file_column(const int FILEC);
/******************************************* 
 * main function of translate chess position 8 + 8 = 16 steps would improve if
 * not lazy.
 *
 * @params const int RANK, const int FILECC
 * @returns int
 * ****************************************/ 
int find_chess_idx(const int RANK, const int FILECC);

/*******************************************
 * find index where 8 to find row and 8 to find column so 8 * reversed-row +
 * total_column_idx = idx
 *
 * @params char[3] // last value for null terminator return int
 * *******************************************/ 
int get_index_by_chess_position(char chess_position[3]);

/******************************************
 * set rook possible moves at position xy
 *
 * @params struct chess_piece piece
 * returns *void  
 *
 ****************************************/ 
void set_rook_coordinates(int xy[2], int offsets[56][2]);

/*****************************************
 * fill offsets knight moves at position xy[2]
 *
 * @params struct chess_piece piece
 ****************************************/
void set_knight_coordinates(int xy[2], int offsets[56][2]);

/****************************************
 * set bishop tracks at position xy[2]
 *
 * @params struct chess_piece piece
 ***************************************/
void set_bishop_coordinates(int xy[2], int offsets[56][2]);
/***************************************
 * sets queen tracks at position xy[2]
 *
 * @params struct chess_piece piece
 **************************************/
void set_queen_coordinates(int xy[2], int offsets[56][2]);

/**************************************
 * gives you king moves at position xy[2]
 *
 * @params struct chess_piece piece
 *************************************/
void set_king_coordinates(int xy[2], int offsets[56][2]);

/******************************************************************************
 * auxillary function for the set pawn coordinates
 *
 * @params int xy[2], int offsets[56][2], int race
 * ***************************************************************************/
void set_pawn_diagonal_coord(int xy[2], int offsets[56][2], int race);
/*************************************
 * gives you pawn moves at position xy[2]
 *
 * @params struct chess_piece piece, char race[1+1]
 ***********************************/
void set_pawn_coordinates(int xy[2], int offsets[56][2], int race);

/**********************************
 * assign chess piece coordinate
 * 
 * @params int index, int coordinate[2]
 * returns nothing
 ********************************/
void set_coordinate_by_index(int index, int coordinate[2]);

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
void set_square_by_coordinate(int coordinate[2], int square[2]);

/*****************************************
 * auxillary function that helps with init_chess_pieces
 *
 * @params int i
 * return nothing
 * *************************************/
void init_king(int i);
void init_queen(int i);
void init_bishop(int i);
void init_knight(int i);
void init_rook(int i);
void init_pawn(int i);
void init_pieces(int i);

/*****************************************
 * default placement of chess pieces
 * 
 * @params
 * returns
 * *************************************/
void init_chess_pieces();

/*****************************************
 * show the chess piece in terminal
 *
 * @params  chess_piece **pieces
 * @returns
 * *************************************/
void draw_chess_pieces();

/*****************************************
 * auxillary funtion for set_chess_piece_to set coordinates based on the chess
 * piece
 *
 * @params int piece, int xy[2], int coordinates[56][2]
 * *************************************/
void set_coordinates_to_piece(int piece, int xy[2], int coordinates[56][2]);

/******************************************************************************
 * this checks if such moves of king is valid or not
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * return int
 * ***************************************************************************/
int is_king_move_valid(int index_src, int index_dest, int coordinates[56][2]);
/*****************************************
 * this checks if such moves of queen is valid or not
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * return int
 * *************************************/
int is_queen_move_valid(int index_src, int index_dest, int coordinates[56][2]);

/*****************************************
 * i have to separate rook moves from this since there is a special moves for
 * the rook
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * @returns int
 * *************************************/
int is_bishop_move_valid(int index_src, int index_dest, int coordinates[56][2]);

/*****************************************
 * helps with king for special move called castling
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * *************************************/
int to_left_castling(int index_src, int index_dest, int coordinates[56][2]);
int to_right_castling(int index_src, int index_dest, int coordinates[56][2]);

/*****************************************
 * this checks if such rook move is valid or not 
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * *************************************/
int is_rook_move_valid(int index_src, int index_dest, int coordinates[56][2]);

/*****************************************
 * this checks if the moves of knight is valid or not
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * returns int
 * *************************************/
int is_knight_move_valid(int index_src, int index_dest, int coordinates[56][2]);

/******************************************************************************
 * this checks if such move is legal or not
 *
 * @params int index_src, int index_dest, int coordinates[56][2]
 * returns int
 * ***************************************************************************/
int is_pawn_move_valid(int index_src, int index_dest, int coordinates[56][2]);

/*****************************************
 * auxillary function for set_piece_to for validating legal move
 *
 * @params int dest[2], int coordinates[56][2]
 * *************************************/
int is_chess_piece_move_valid(int dest[2],
                int index_src,
                int index_dest,
		int chess_piece,
                int coordinates[56][2]);

/*****************************************
 * auxillary function for getting the chess piece by notation k q b n r e
 * 
 * @params int i
 * @returns int
 * *************************************/
int get_chess_piece(int i);

/*****************************************
 * this sets the piece set destination i need to separate this because the
 * function is too big
 *
 * @params int idx_dest, int idx_src
 * @returns
 * *************************************/
void set_chess_piece_dest(int idx_dest, int idx_src);

/*****************************************
 * set previous set dest with no values in place.
 *
 * @params idx_src
 * @returns
 * *************************************/
void set_left_square(int idx_src);

/*****************************************
 * disambiguation should be prefered as it is more complex to implement notations
 * such as N6b it is more simple to use such as usage of file&rank for example
 *
 * N6b5d Knight from 6b goes to 5d 
 * @params char notation[5+1]
 * *************************************/
int set_chess_piece_to_by_char(char notation[6]);

#endif // chess.h
