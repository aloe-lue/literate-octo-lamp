#ifndef CHESS_H
#define CHESS_H

#define WHITE	 			1
#define BLACK	 		 	0
#define ROOKUP	 			0
#define ROOKBOTTOM 			1
#define ROOKRIGHT 			2
#define ROOKLEFT 			3

#define BISHOPTOPRIGHT  	0
#define BISHOPBOTTOMRIGHT	1
#define BISHOPBOTTOMLEFT	2
#define BISHOPTOPLEFT		3
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
 */

void SetQueenDests(chess_square *square, int coord[2]);

#endif // chess.h
