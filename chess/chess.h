#ifndef CHESS_H
#define CHESS_H

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

#define PAWN	 	1
#define KNIGHT 		2
#define BISHOP 		3
#define ROOK 		4
#define QUEEN 		5
#define KING 		6

#define BLACKSQUARE	" ■ "
#define WHITESQUARE	" □ "

typedef struct chess_square {
	int coordinate[2];
	int piece_color;
	int contain_piece;
	int chess_piece;
	int square_color;
	int chess_piece_dests[56];
	char square[3];
	char piece_notation;
	char piece_symbol[12];
} chess_square;

/*
 * translate coord by idx 8x8
 *
 */
void SetCoordByIdx(int coord[2], int idx);

/*
 * translate user coord to idx 8x8
 */
int GetIdxByCoord(int coord[2]);

/*
 * translate idx to square chess notation 8a, 8b, etc.
 */
void SetSquareByIdx(char square[3], int idx);

/*
 * hmm 
 */
void SetCoordBySquare(int coord[2], char square[3]);

/*
 * aux functions for get idx by square
 */
int GetRowByRank(const char RANK);
int GetColumnByFile(const char FILECC);
/*
 * get index using chess notation
 */
int GetIdxBySquare(char square[3]);
/*
 * filters pawn destinations
 */
int IsPawnMoveLegal(chess_square *squares, int coord[2], int i);

/*
 * aux 
 */
int IsXYBetweenAB(int x, int y, const int a, const int b);

/*
 * aux func for set pawn dests
 */
void SetPawnOffsetsByPieceColor(int piece_color, int idx, int coord[2]);
/*
 * set pawn dests by coord and square
 */
void SetPawnDests(chess_square *squares, int coord[2]);

/*
 * set rook offsets malamang
 */
void SetRookOffset(int rook_offsets[][2], int idx);


void SetRookDests(chess_square *squares, int coord[2]);


void SetKnightDests(chess_square *squares, int coord[2]);

/*
 * aux function for bishop dests
 */
void SetBishopOffsets(int bishop_offsets[][2], int idx);


void SetBishopDests(chess_square *squares, int coord[2]);

/*
 * aux function for setqueendests
 */
void SetQueenOffsets(int queen_offsets[][2], int idx);


void SetQueenDests(chess_square *squares, int coord[2]);


void InitPawns(chess_square *squares);


chess_square *InitChessSquare();


void ClearChessSquare(chess_square *squares);

/*
 * print ascii chessboard
 */
void DrawChessBoard(chess_square *squares);

/*
 * put the chess piece from here to there.
 */
int SetPieceDestTo(chess_square *squares, const char *NOTATION);


#endif // chess.h
