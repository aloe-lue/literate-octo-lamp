#ifndef CHESS_H
#define CHESS_H

// chess unicode
#define BLACK_CHESS_PIECES  "\u265C\u265E\u265D\u265A\u265B\u265F";
#define WHITE_CHESS_PIECES  "\u2656\u2658\u2657\u2654\u2655\u2659";
// rook knight bishop king queen pawn
#define CHESS_PIECE_LOCAL   [0, 1, 2, 3, 4, 5];

struct chess_8x8 {
        int white_moves;
        int black_moves;
        int coordinate_2d[64][2];
        int human_readable_2d[64][2];
};

/********************************************
 * this helps later when finding the position of scanf position like Kb6 > Kb5
 * 
 * @params struct chess_8x8 c
 *******************************************/
void init_chess_coordinates(int coordinate_2d[64][2],
		int human_readable_2d[64][2]);

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

struct rook {
	int offsets[28][2];
	int xy[2];
	int total_offsets;
	int moves;
	int race;
};

struct knight {
	int offsets[8][2];
	int xy[2];
	int total_offsets;
	int moves;
	int race;
};

struct bishop {
	int offsets[28][2];
	int xy[2];
	int total_offsets;
	int moves;
	int race;
};

struct queen {
	int offsets[56][2];
	int xy[2];
	int total_offsets;
	int moves;
	int race;
};

struct king {
	int offsets[8][2];
	int xy[2];
	int total_offsets;
	int moves;
	int race;
};

struct pawn {
	int offsets[4][2];
	int xy[2];
	int total_offsets;
	int moves;
	int race;
};
/******************************************
 * gives you the possible moves at position xy
 *
 * @params struct chess_piece piece
 * returns *void  
 * 	probably a bad idea should be vector weird or
 * 	array huh?
 *
 ****************************************/ 
void set_rook_coordinates(int xy[2],
		int offsets[28][2]);

/*****************************************
 * gives you knight moves at position xy[2]
 *
 * @params struct chess_piece piece
 ****************************************/
void set_knight_coordinates(int xy[2],
		int offsets[8][2]);

/****************************************
 * gives you bishop moves at position xy[2]
 *
 * @params struct chess_piece piece
 ***************************************/
void set_bishop_coordinates(int cartesian2d[2],
		int moves_cartesian_2d[28][2]);

/***************************************
 * gives you queen moves at position xy[2]
 *
 * @params struct chess_piece piece
 **************************************/
void set_queen_coordinates(int cartesian2d[2],
		int moves_cartesian_2d[56][2]);

/**************************************
 * gives you king moves at position xy[2]
 *
 * @params struct chess_piece piece
 *************************************/
void set_king_coordinates(int xy[2],
		int offsets[8][2]);

/*************************************
 * gives you pawn moves at position xy[2]
 *
 * @params struct chess_piece piece, char race[1+1]
 ***********************************/
void set_pawn_coordinates(int xy[2],
		int offsets[4][2],
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

/******************************
 *  this initializes the default position of white pawns 
 *
 ****************************/
void init_white_pawn(int xy[2]);

#endif
