#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chess.h"

int find_chess_idx(const int RANK,
		const int FILECC)
{
        int column_idx = 0;
        int row_idx = 0;

        for (int i = 56; i != 49; i--) {
                if (i == RANK) break;
                else row_idx++;
        }
        for (int i = 97; i <= 104; i++) {
        	if (i == FILECC) break;
        	else column_idx++;
        }
        return (row_idx * 8) + column_idx;
}

int get_index_by_chess_position(char chess_position[3])
{
        const int RANK = (int)chess_position[0];
        const int FILECC = (int)chess_position[1];
        if ((RANK < 49 && RANK > 56) ||
			(FILECC < 97 && FILECC > 104))
		return -1;
        int index = find_chess_idx(RANK, FILECC);
        return index < 0 && index > 63 ? -1 : index;
}

void set_rook_coordinates(int xy[2],
		int offsets[56][2])
{
	int ROOK_START[4][2] = {{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }};
	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = 0;
	      	int y = 0;

		x = ROOK_START[j][0];
		y = ROOK_START[j][1];

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;

		if ((coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		} 
                else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}

		if (x == 0 && y >= 1)
			ROOK_START[j][1]++;
		else if (x >= 1 && y == 0) 
			ROOK_START[j][0]++;
		else if (x == 0 && y <= -1) 
			ROOK_START[j][1]--;
		else ROOK_START[j][0]--;

		if ((i +1) % 7 == 0) j++;
	}
}

void set_knight_coordinates(int xy[2],
		int offsets[56][2])
{
	int knight_offsets[8][2] = {
		{ 1, 2 }, { 2, 1 }, { -1, 2 }, { -2, 1 },
		{ 1, -2 }, { 2, -1 }, { -1, -2 }, { -2, -1 }
	};
	for (int i = 0; i < 8; i++) {
		int x = 0;
	      	int y = 0;

		x = knight_offsets[i][0];
		y = knight_offsets[i][1];

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;

		if ((coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}
	}
}

void set_bishop_coordinates(int xy[2],
		int offsets[56][2])
{
	int j = 0;
	int bishop_start[4][2] = {{ 1, 1 }, { -1, 1 }, { 1, -1}, { -1, -1 }};
	for (int i = 0; i < 28; i++) {
		int x = 0;
		int y = 0;

		x = bishop_start[j][0];
		y = bishop_start[j][1];

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;
		if ((coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}

		if (x >= 1 && y >= 1) {
			bishop_start[j][0]++;
			bishop_start[j][1]++;
		}
                else if (x <= 0 && y >= 1) {
			bishop_start[j][0]--;
			bishop_start[j][1]++;
		}
                else if (x >= 1 && y <= 0) {
			bishop_start[j][0]++;
			bishop_start[j][1]--;
		}
                else {
			bishop_start[j][0]--;
			bishop_start[j][1]--;
		}
		if ((i + 1) % 7 == 0) j++;
	}
}

void set_queen_coordinates(int xy[2],
		int offsets[56][2])
{
	// I had to repeat this nonsense, true I can use the existing function but
	// how huh? use two offsets? nope i don't want it.
	int ROOK_START[4][2] = {{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }};
	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = 0;
	      	int y = 0;

		x = ROOK_START[j][0];
		y = ROOK_START[j][1];

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;

		if ((coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}

		if (x == 0 && y >= 1)
			ROOK_START[j][1]++;
		else if (x >= 1 && y == 0) 
			ROOK_START[j][0]++;
		else if (x == 0 && y <= -1) 
			ROOK_START[j][1]--;
		else ROOK_START[j][0]--;

		if ((i +1) % 7 == 0) j++;
	}
	int j1 = 0;
	int bishop_start[4][2] = {{ 1, 1 }, { -1, 1 }, { 1, -1}, { -1, -1 }};
	for (int i = 28; i < 56; i++) {
		int x = 0;
		int y = 0;

		x = bishop_start[j1][0];
		y = bishop_start[j1][1];

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;
		if ((coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}

		if (x >= 1 && y >= 1) {
			bishop_start[j1][0]++;
			bishop_start[j1][1]++;
		}
                else if (x <= 0 && y >= 1) {
			bishop_start[j1][0]--;
			bishop_start[j1][1]++;
		}
                else if (x >= 1 && y <= 0) {
			bishop_start[j1][0]++;
			bishop_start[j1][1]--;
		}
                else {
			bishop_start[j1][0]--;
			bishop_start[j1][1]--;
		}
		if ((i + 1) % 7 == 0) j1++;
	}
}

void set_king_coordinates(int xy[2],
		int offsets[56][2])
{
	int king_coordinates[8][2] = {
		{ 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 },
		{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
	};
	for (int i = 0; i < 8; i++) {
		int x = 0;
		int y = 0;

		x = king_coordinates[i][0];
		y = king_coordinates[i][1];

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;

		if ((coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}
	}
}

void set_pawn_coordinates(int xy[2],
		int offsets[56][2],
		int race) // race 1 white 0 black
{
	int white_path[4][2] = {{0, -1}, {0, -2}, {-1, -1}, {1, -1}};
	int black_path[4][2] = {{0, 1}, {0, 2}, {-1, 1}, {1, 1}};

	for (int i = 0; i < 2; i++) {
		int x = 0;
		int y = 0;

		switch(race) {
		case 0: 
			x = black_path[i][0];
			y = black_path[i][1];
			break;
		case 1: 
			x = white_path[i][0];
			y = white_path[i][1];
			break;
		}

		int coordx = xy[0] + x;
		int coordy = xy[1] + y;
		int bound = (coordx >= 0 && coordx <= 7) &&
				(coordy >= 0 && coordy <= 7);
		
		if (race == 1 && bound &&
				(xy[0] > 5)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                else if (race == 1 && bound &&
				(xy[0] <= 5)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
			break;
		}

		if (race == 0 && bound &&
				(xy[0] < 3)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
                 if (race == 0 && bound &&
				(xy[0] >= 3)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
			break;
		} 
	}
	for (int i = 2; i < 4; i++) {
		int x = 0;
		int y = 0;

		switch(race) {
		case 0: 
			x = black_path[i][0];
			y = black_path[i][1];
			break;
		case 1: 
			x = white_path[i][0];
			y = white_path[i][1];
			break;
		}

		int coordx = x + xy[0];
		int coordy = y + xy[1];

	        if ((coordx >= 0 && coordx <= 7) && 
			(coordy >= 0 && coordy <= 7)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		}
	}
}

void set_coordinate_by_index(int index,
		int coordinate[2])
{
	if (index > 63 || index < 0) return;
	int x = 0;
	int y = 0;
	for (int i = 0; i < 64; i += 8) {
		if (index >= i && index <= (i+8-1)) {
			x = i;
			break;
		}
		y++;
	}
	coordinate[0] = (index + y) - index;
	coordinate[1] = index - x;
}

int get_index_by_coordinate(int coordinate[2])
{
	int index = (coordinate[1] * 8) + coordinate[0];
	return index;
}

void set_square_by_coordinate(int coordinate[2],
                int square[2])
{
        int j = 0;
        for (int i = 56; i > 47; i--) {
                if (coordinate[0] == j) {
                        square[0] = i;
                        break;
                }
                j++;
        }
        int k = 0;
        for (int i = 97; i < 105; i++) {
                if (coordinate[1] == k) {
                        square[1] = i;
                        break;
                } 
                k++;
        }
}

void init_pieces(int i, chess_piece **pieces)
{
        if (i == 0 || i == 7 || i == 56 || i == 63) {
                pieces[i]->piece = 1;
                pieces[i]->symbol = 'r';
                if (i < 8)
                        strcpy(pieces[i]->ascii_symbol, B_ROOK);
                else  strcpy(pieces[i]->ascii_symbol, W_ROOK);
                return;
        }
        if (i == 1 || i == 6 || i == 57 || i == 62) {
                pieces[i]->piece = 2;
                pieces[i]->symbol = 'n';

                if (i < 7)
                        strcpy(pieces[i]->ascii_symbol, B_KNIGHT);
                else strcpy(pieces[i]->ascii_symbol, W_KNIGHT);
                return;
        }
        if (i == 2 || i == 5 || i == 58 || i == 61) {
                pieces[i]->piece = 3;
                pieces[i]->symbol = 'b';

                if (i < 6)
                        strcpy(pieces[i]->ascii_symbol, B_BISHOP);
                else strcpy(pieces[i]->ascii_symbol, W_BISHOP);
                return;
        }
        if (i == 3 || i == 59) {
                pieces[i]->piece = 4;
                pieces[i]->symbol = 'q';

                if (i < 4)
                        strcpy(pieces[i]->ascii_symbol, B_QUEEN);
                else strcpy(pieces[i]->ascii_symbol, W_QUEEN);
                return;
        }
        if (i == 4 || i == 60) {
                pieces[i]->piece = 5;
                pieces[i]->symbol = 'k';

                if (i < 5)
                        strcpy(pieces[i]->ascii_symbol, B_KING);
                else strcpy(pieces[i]->ascii_symbol, W_KING);
                return;
        }
        if ((i > 7 && i < 16) || (i > 47 && i < 57)) {
                pieces[i]->piece = 0;
                pieces[i]->symbol = 'e';

                if (i < 16)
                        strcpy(pieces[i]->ascii_symbol, B_PAWN);
                else strcpy(pieces[i]->ascii_symbol, W_PAWN);
                return;
        }
}

chess_piece **init_chess_pieces()
{
        chess_piece **pieces = malloc(sizeof(chess_piece) * 64);
        if (pieces == NULL) {
                fprintf(stderr, "malloc err init chess pieces.");
                exit(1);
        }
        for (int i = 0; i < 64; i++) {
                pieces[i] = malloc(sizeof(chess_piece));
                if (pieces[i] == NULL) {
                        fprintf(stderr, "malloc err init chess pieces.");
                        exit(1);
                }
                pieces[i]->race = -1;
                pieces[i]->piece = -1;
                pieces[i]->is_zero = 0;

                if (i < 16) { 
                        pieces[i]->race = 0;
                        pieces[i]->is_zero = 1;
                }
                if (i > 47) {
                        pieces[i]->race = 1;
                        pieces[i]->is_zero = 1;
                }
                int coordinate[2] = {-1};
                set_coordinate_by_index(i, coordinate);
                for (int j = 0; j < 2; j++)
                        pieces[i]->coordinate[j] = coordinate[j];
                init_pieces(i, pieces);
                set_square_by_coordinate(coordinate, pieces[i]->square);

                if (pieces[i]->piece == -1) strcpy(pieces[i]->ascii_symbol, "");

                // use this for debugging, weird
                // printf("[%c, %c]%s%s", (char)pieces[i]->square[0],
                //                 (char)pieces[i]->square[1],
                //                 (i+1) % 8 == 0 ? "\n" : ",",
                //                 (i+1) == 64 ? "\n" : " ");
        }
        return pieces;
}

void clear_chess_pieces(chess_piece **pieces) 
{
        for (int i = 0; i < 64; i++)
                free(pieces[i]);
        free(pieces);
}


void draw_chess_pieces(chess_piece **pieces)
{
        char draw_piece[400] = "\0";
        const char *FILES = "  * a  b  c  d  e  f  g  h  * \n";
        int r = 8;
        int bit = 0;
        strcat(draw_piece, FILES);
        for (int i = 0; i < 64; i++) {
                strcat(draw_piece, " ");
                int is_bound = (i+1) % 8 == 0;

                char snfrmt[] = " %d  ";
                int buf_sz = snprintf(NULL, 0, snfrmt, r);
                char draw_piece_r[buf_sz+1];
                snprintf(draw_piece_r, buf_sz, snfrmt, r);

                if (i == 0 || i % 8 == 0) strcat(draw_piece, draw_piece_r);

                strcat(draw_piece, pieces[i]->ascii_symbol);
                strcat(draw_piece, " ");
                int is_even = (pieces[i]->race == -1 && 
                                r % 2 == 0 && bit == 1);
                int is_odd = (pieces[i]->race == -1 &&
                                r % 2 == 1 && bit == 0);
                if (is_even || is_odd) // fill black without 
                                strcat(draw_piece, "° ");

                bit = bit == 1 ? 0 : 1;
                if (is_bound) {
                        strcat(draw_piece, draw_piece_r);
                        strcat(draw_piece, "\n");
                        r--;
                } 
        }
        strcat(draw_piece, FILES);
        puts(draw_piece);
}

