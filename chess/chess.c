#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "chess.h"

void SetCoordByIdx(int coord[2], int idx)
{
	int x = idx % 8;
	int y = idx / 8;

	coord[0] = x;
	coord[1] = y;
}

int GetIdxByCoord(int coord[2])
{
	int y = coord[1] * 8;
	int idx = y + coord[0];

	return idx;
}

const char *CHESS_FILES = "abcdefgh";
const char *CHESS_RANKS = "87654321";

void SetSquareByIdx(char square[3], int idx)
{
	int x = idx % 8;
	int y = idx / 8;

	square[0] = CHESS_FILES[x];
	square[1] = CHESS_RANKS[y];
}

void SetCoordBySquare(int coord[2], char square[3])
{
	coord[0] = CHESS_FILES[coord[0]];
	coord[1] = CHESS_RANKS[coord[1]];
}

int GetRowByRank(const char RANK)
{
	int row = 0;

	for (int i = 56; i >= 49; i--) {
		if (RANK == i)
			return row;

		row++;
	}
	return 8;
}


int GetColumnByFile(const char FILECC)
{
	int column = 0;

	for (int i = 97; i <= 104; i++) {
		if (FILECC == i)
			return column;

		column++;
	}

	return 8;
}

int GetIdxBySquare(char square[3])
{
	int row = GetRowByRank(square[0]);
	int column = GetColumnByFile(square[1]);

	if (row == 8 || column == 8)
		return 64;

	int idx = (column * 8) + row;

	return idx;
}

int IsPawnMoveLegal(chess_square *squares, int coord[2], int i)
{
}

int IsXYBetweenAB(int x, int y, const int a, const int b)
{
	return ((x >= a && x <= b) && (y >= a && y <= b));
}

void SetPawnOffsetsByPieceColor(int piece_color, int idx, int coord[2])
{
	const int WPAWN_OFFSETS[4][2] = {{0,-1}, {0,-2}, {-1,-1}, {1,-1}};
	const int BPAWN_OFFSETS[4][2] = {{0,1}, {0,2}, {-1,1}, {1,1}};

	switch(piece_color) {
	case 0: // black as dark
		coord[0] = BPAWN_OFFSETS[idx][0];
		coord[1] = BPAWN_OFFSETS[idx][1];
		return;
	case 1: // white as light
		coord[0] = WPAWN_OFFSETS[idx][0];
		coord[1] = WPAWN_OFFSETS[idx][1];
		return;
	}
}

void SetPawnDests(chess_square *squares, int coord[2])
{

	int idx_src = GetIdxByCoord(coord);
	int piece_color = squares[idx_src].piece_color;

	for (int i = 0; i < 4; i++) {
		int xy[2] = {0};

		SetPawnOffsetsByPieceColor(piece_color, i, coord);

		int ax = coord[0] + xy[0];
		int ay = coord[1] + xy[1];
		int axy[2] = { ax, ay };
		int idx = GetIdxByCoord(axy);

		if (IsXYBetweenAB(ax, ay, 7, 7))
			squares[i].chess_piece_dests[i] = idx;
		else 
			squares[i].chess_piece_dests[i] = 999;
	}
}

void SetRookOffset(int rook_offsets[][2], int idx)
{
	switch(idx) {
	case 0:
		rook_offsets[idx][1]++;
		break;
	case 1:
		rook_offsets[idx][0]++;
		break;
	case 2:
		rook_offsets[idx][1]--;
		break;
	case 3:
		rook_offsets[idx][0]--;
		break;
	}
}

void SetRookDests(chess_square *squares, int coord[2])
{
	int rook_offsets[][2] = {{0,1}, {1,0}, {0,-1},{-1,0}};
	int r_idx_src = GetIdxByCoord(coord);

	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = rook_offsets[j][0] + x;
		int ay = rook_offsets[j][1] + y;
		int axy[2] = { ax, ay };
		int r_idx_dest = GetIdxByCoord(axy);

		if (IsXYBetweenAB(ax, ay, 7, 7))
			squares[r_idx_src].chess_piece_dests[i] = r_idx_dest;
		else
			squares[r_idx_src].chess_piece_dests[i] = 999;

		SetRookOffset(rook_offsets, j);

		if ((i+1) % 7 == 0)
			j++;
	}
}

void SetKnightDests(chess_square *squares, int coord[2])
{
	int knight_offsets[8][2] = {{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2},
		{-1,-2}, {-2,-1}, {-2,1}};
	int n_src_idx = GetIdxByCoord(coord);

	for (int i = 0; i < 8; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = knight_offsets[i][0] + x;
		int ay = knight_offsets[i][1] + y;
		int axy[] = {ax,ay};
		int n_idx = GetIdxByCoord(axy);

		if (IsXYBetweenAB(ax, ay, 7, 7) &&
				// it doesn't fall on the same piece color
				squares[n_src_idx].piece_color !=
				squares[n_idx].piece_color)
			squares[n_idx].coordinate[i] = n_idx;
		else
			squares[n_idx].coordinate[i] = 99;
	}
}

void SetBishopOffsets(int bishop_offsets[][2], int idx)
{
	switch(idx) {
	case 0:
		bishop_offsets[idx][0]++;
		bishop_offsets[idx][1]++;
		break;
	case 1:
		bishop_offsets[idx][0]++;
		bishop_offsets[idx][1]--;
		break;
	case 2:
		bishop_offsets[idx][0]--;
		bishop_offsets[idx][1]--;
		break;
	case 3:
		bishop_offsets[idx][0]--;
		bishop_offsets[idx][1]++;
		break;
	}
}

void SetBishopDests(chess_square *squares, int coord[2])
{
	int bishop_offsets[][2] = {{1,1}, {1,-1}, {-1,-1}, {-1, 1}};
	int b_idx_src = GetIdxByCoord(coord);

	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = bishop_offsets[j][0] + x;
		int ay = bishop_offsets[j][1] + y;
		int axy[] = { ax, ay };
		int b_idx = GetIdxByCoord(axy);
		
		SetBishopOffsets(bishop_offsets, j);

		if ((i+1) % 7 == 0)
			j++;
	}
}

void SetQueenOffsets(int queen_offsets[][2], int idx)
{
	switch(idx) {
	case 0: // top
		queen_offsets[idx][1]++;
		break;
	case 1: // right
		queen_offsets[idx][0]++;
		break;
	case 2: // bottom
		queen_offsets[idx][1]--;
		break;
	case 3: // left
		queen_offsets[idx][0]--;
		break;
	case 4: // right top
		queen_offsets[idx][0]++;
		queen_offsets[idx][1]++;
		break;
	case 5: // right bottom
		queen_offsets[idx][0]++;
		queen_offsets[idx][1]--;
		break;
	case 6: // left bottom
		queen_offsets[idx][0]--;
		queen_offsets[idx][1]--;
		break;
	case 7: // left top
		queen_offsets[idx][0]--;
		queen_offsets[idx][1]++;
		break;
	}
}

void SetQueenDests(chess_square *squares, int coord[2])
{
	int queen_offsets[][2] = {{0,1}, {1,0}, {0,-1},{-1,0},
		{1,1}, {1,-1}, {-1,-1}, {-1,1}};

	int j = 0;
	for (int i = 0; i < 56; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = queen_offsets[j][0] + y;
		int ay = queen_offsets[j][1] + x;
		int axy[] = {ax,ay};
		int q_idx = GetIdxByCoord(axy);

		SetQueenOffsets(queen_offsets, j);

		if ((i+1) % 7 == 0)
			j++;
	}
}

void SetKingDests(chess_square *squares, int coord[2])
{
	int king_offsets[8][2] = {{-1,1}, {0, 1}, {1,1}, {1,0}, {1,-1}, {0,-1},
		{-1,-1}, {-1,0}};
	int k_idx_src = GetIdxByCoord(coord);

	for (int i = 0; i < 8; i++) {
		int x = coord[0];
		int y = coord[1];
		int ax = king_offsets[i][0] + x;
		int ay = king_offsets[i][1] + y;
		int axy[] = { ax, ay };
		int k_idx = GetIdxByCoord(axy);
	}
}

void InitPawns(chess_square *squares)
{
	for (int i = 8; i < 16; i++) {
		int coord[] = {-1,-1};

		SetCoordByIdx(coord, i);
		SetPawnDests(squares, coord);
		strcpy(squares[i].piece_symbol, BPAWN);

		squares[i].piece_color = 0;
		squares[i].chess_piece = 1;
		squares[i].contain_piece = 1;
		squares[i].piece_notation = 'e';
	}

	for (int i = 48; i < 56; i++) {
		int coord[] = {-1, -1};

		SetCoordByIdx(coord, i);
		SetPawnDests(squares, coord);
		strcpy(squares[i].piece_symbol, WPAWN);

		squares[i].piece_color = 1;
		squares[i].piece_notation = 'e';
		squares[i].chess_piece = 1;
		squares[i].contain_piece = 1;
	}
}


chess_square *InitChessSquare()
{
	chess_square *squares = malloc(sizeof(chess_square) * 64);

	if (squares == NULL) {
		fprintf(stderr, "init_chess_squares: func = malloc. ");
		exit(EXIT_FAILURE);
	}

	int square_color = 0;
	for (int i = 0; i < 64; i++) {
		SetCoordByIdx(squares[i].coordinate, i);
		SetSquareByIdx(squares[i].square, i);

		squares[i].contain_piece = 0;
		squares[i].piece_color = 2;
		squares[i].piece_notation = 'o';
		squares[i].square_color = square_color;

		square_color ? strcat(squares[i].piece_symbol, WHITESQUARE) :
			strcat(squares[i].piece_symbol, BLACKSQUARE);

		if ((i+1) % 8 != 0)
			square_color = square_color == 0 ? 1 : 0;
	}

	return squares;
}

void DrawChessBoard(chess_square *squares)
{
	char chessboard[1024] = "\0";
	const char *FILES = "*  a  b  c  d  e  f  g  h  *";
	int rank = 8;

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

void ClearChessSquare(chess_square *squares)
{
	free(squares);
}

int GetPieceByNotation(char piece_notation)
{
	switch(piece_notation) {
	case 'b':
		return BISHOP;
	case 'e':
		return PAWN;
	case 'k':
		return KING;
	case 'n':
		return KNIGHT;
	case 'q':
		return QUEEN;
	case 'r':
		return ROOK;
	default:
		return 0;
	}
}

static int piece_color_turn  = 1; // white first

int SetPieceDestTo(chess_square *squares, const char *NOTATION)
{
	int piece = GetPieceByNotation(NOTATION[0]);

	if (!piece)
		return 100;

	int j = 0;
        int k = 0;
	char notation_src[3] = "\0";
	char notation_dest[3] = "\0";

	for (int i = 1; i < 3; i++)
		notation_src[j] = NOTATION[i];
	for (int i = 3; i < 5; i++)
		notation_dest[k] = NOTATION[i];
	
	int src_idx = GetIdxBySquare(notation_src);	
	int dest_idx = GetIdxBySquare(notation_dest);

	if (src_idx == 64 || dest_idx == 64)
		return 200;

}


