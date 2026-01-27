#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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

int IsPawnMoveLegal(chess_square *squares, int coord[2], int i)
{
}

int IsXYBetweenAB(int x, int y, const int a, const int b)
{
	return ((x >= a && x <= b) && (y >= a && y <= b));
}


void SetPawnDests(chess_square *squares, int coord[2])
{
	const int WPAWN_OFFSETS[4][2] = {{0,-1}, {0,-2}, {-1,-1}, {1,-1}};
	const int BPAWN_OFFSETS[4][2] = {{0,1}, {0,2}, {-1,1}, {1,1}};
	int idx_src = GetIdxByCoord(coord);
	int piece_color = squares[idx_src].piece_color;

	for (int i = 0; i < 4; i++) {
		int xy[2] = {0};

		switch(piece_color) {
		case BLACK:
			coord[0] = BPAWN_OFFSETS[i][0];
			coord[1] = BPAWN_OFFSETS[i][1];
			return;
		case WHITE:
			coord[0] = WPAWN_OFFSETS[i][0];
			coord[1] = WPAWN_OFFSETS[i][1];
			return;
		}

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

		int r_idx = GetIdxByCoord(axy);

		if (IsXYBetweenAB(ax, ay, 7, 7))
			squares[r_idx_src].chess_piece_dests[i] =  r_idx;
		else
			squares[r_idx_src].chess_piece_dests[i] =  999;
		
		switch(i) {
		case ROOKUP:
			rook_offsets[j][1]++;
			break;
		case ROOKRIGHT:
			rook_offsets[j][0]++;
			break;
		case ROOKBOTTOM:
			rook_offsets[j][1]--;
			break;
		case ROOKLEFT:
			rook_offsets[j][0]--;
			break;
		}

		if ((i+1) % 7 == 0)
			j++;
	}
}

void SetKnightDests(chess_square *squares, int coord[2])
{
	int knight_offsets[][2] = {{-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2},
		{-1,-2}, {-2,-1}, {-2,1}};

	for (int i = 0; i < 8; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = knight_offsets[i][0] + x;
		int ay = knight_offsets[i][1] + y;
		int axy[] = {ax,ay};
		int k_idx = GetIdxByCoord(axy);
	}
}

void SetBishopDests(chess_square *squares, int coord[2])
{
	int bishop_offsets[][2] = {{1,1}, {1,-1}, {-1,-1}, {-1, 1}};
	int b_idx_src  = GetIdxByCoord(coord);

	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = bishop_offsets[j][0] + x;
		int ay = bishop_offsets[j][1] + y;
		int axy[] = { ax, ay };
		int b_idx = GetIdxByCoord(axy);
		
		switch(j) {
		case BISHOPTOPRIGHT:
			bishop_offsets[j][0]++;
			bishop_offsets[j][1]++;
			break;
		case BISHOPBOTTOMRIGHT:
			bishop_offsets[j][0]++;
			bishop_offsets[j][1]--;
			break;
		case BISHOPBOTTOMLEFT:
			bishop_offsets[j][0]--;
			bishop_offsets[j][1]--;
			break;
		case BISHOPTOPLEFT:
			bishop_offsets[j][0]--;
			bishop_offsets[j][1]++;
			break;
		}

		if ((i+1) % 7 == 0)
			j++;
	}
}

void SetQueenDests(chess_square *square, int coord[2])
{
	int queen_offsets[][2] = {{0,1}, {1,0}, {0,-1},{-1,0},
		{1,1}, {1,-1}, {-1,-1}, {-1, 1}};

	int j = 0;
	for (int i = 0; i < 56; i++) {
		int x = coord[0];
		int y = coord[1];

		int ax = queen_offsets[j][0] + y;
		int ay = queen_offsets[j][1] + x;
		int axy[] = {ax,ay};
		int q_idx = GetIdxByCoord(axy);

		switch(j) {
		case ROOKUP:
			queen_offsets[j][1]++;
			break;
		case ROOKRIGHT:
			queen_offsets[j][0]++;
			break;
		case ROOKBOTTOM:
			queen_offsets[j][1]--;
			break;
		case ROOKLEFT:
			queen_offsets[j][0]--;
			break;
		case BISHOPTOPRIGHT+5:
			queen_offsets[j][0]++;
			queen_offsets[j][1]++;
			break;
		case BISHOPBOTTOMRIGHT+5:
			queen_offsets[j][0]++;
			queen_offsets[j][1]--;
			break;
		case BISHOPBOTTOMLEFT+5:
			queen_offsets[j][0]--;
			queen_offsets[j][1]--;
			break;
		case BISHOPTOPLEFT+5:
			queen_offsets[j][0]--;
			queen_offsets[j][1]++;
			break;
		}

		if ((i+1) % 7 == 0)
			j++;
	}
}


chess_square *InitChessSquare()
{
	chess_square *squares = malloc(sizeof(chess_square) * 64);

	if (squares == NULL) {
		fprintf(stderr, "init_chess_squares: func = malloc. ");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 64; i++) {
		SetCoordByIdx(squares[i].coordinate, i);
		SetSquareByIdx(squares[i].square, i); 
	}

	return squares;
}

void ClearChessSquare(chess_square *squares)
{
	free(squares);
}
