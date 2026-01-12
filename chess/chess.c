#include <stdio.h>
#include <string.h>

#include "chess.h"

int get_rank_row(const int RANK)
{
	int row = 0;
	for (int i = 56; i != 49; i--) {
		if (i == RANK)
			break;
		else
			row++;
	}
	return row;
}

int get_file_column(const int FILEC)
{
	int column = 0;
	for (int i = 97; i <= 104; i++) {
		if (i == FILEC)
			break;
		else
			column++;
	}
	return column;
}

int find_chess_idx(const int RANK, const int FILECC)
{
        int column = get_file_column(FILECC);
	int row = get_rank_row(RANK);
        return (row * 8) + column;
}

int get_index_by_chess_position(char chess_position[3])
{
        const int RANK = (int)chess_position[0];
        const int FILECC = (int)chess_position[1];
        if ((RANK < 49 && RANK > 56) || (FILECC < 97 && FILECC > 104))
		return 64;
        int index = find_chess_idx(RANK, FILECC);
        return index < 0 && index > 63 ? 64 : index;
}

int xy_is_between_inc(int x, int y)
{
	return ((x >= 0 && x <= 7) && (y >= 0 && y <= 7));
}

void set_rook_coordinates(int xy[2], int offsets[56][2])
{
	int rook[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = rook[j][0];
		int y = rook[j][1];

		int ax = xy[0] + x;
		int ay = xy[1] + y;

		if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else {
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}

		switch(j) {
		case 0:
			rook[j][1]++;
			break;
		case 1:
			rook[j][0]++;
			break;
		case 2:
			rook[j][1]--;
			break;
		case 3:
			rook[j][0]--;
			break;
		}

		if ((i+1) % 7 == 0)
			j++;
	}
}

void set_knight_coordinates(int xy[2], int offsets[56][2])
{
	const int KNIGHT[8][2] = {
		{ 1, 2 }, { 2, 1 }, { -1, 2 }, { -2, 1 }, { 1, -2 }, { 2, -1 },
		{ -1, -2 }, { -2, -1 }
	};
	for (int i = 0; i < 8; i++) {
		int x = KNIGHT[i][0];
	      	int y = KNIGHT[i][1];

		int ax = xy[0] + x;
		int ay = xy[1] + y;

		if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else { 	
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}
	}
}

void set_bishop_coordinates(int xy[2], int offsets[56][2])
{
	int bishop[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
	int j = 0;
	for (int i = 0; i < 28; i++) {
		int x = bishop[j][0];
		int y = bishop[j][1];

		int ax = xy[0] + x;
		int ay = xy[1] + y;

		if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else {
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}
		switch(j) {
		case 0:
			bishop[j][0]++;
			bishop[j][1]++;
			break;
		case 1:
			bishop[j][0]--;
			bishop[j][1]++;
			break;
		case 2:
			bishop[j][0]++;
			bishop[j][1]--;
			break;
		case 3:
			bishop[j][0]--;
			bishop[j][1]--;
			break;
		}
	
		if ((i+1) % 7 == 0)
			j++;
	}
}

void set_queen_coordinates(int xy[2], int offsets[56][2])
{
	set_rook_coordinates(xy, offsets);
	int bishop[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
	int j = 0;
	for (int i = 28; i < 56; i++) {
		int x = bishop[j][0];
		int y = bishop[j][1];

		int ax = xy[0] + x;
		int ay = xy[1] + y;

		if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else {
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}

		switch(j) {
		case 0:
			bishop[j][0]++;
			bishop[j][1]++;
			break;
		case 1:
			bishop[j][0]--;
			bishop[j][1]++;
			break;
		case 2:
			bishop[j][0]++;
			bishop[j][1]--;
			break;
		case 3:
			bishop[j][0]--;
			bishop[j][1]--;
			break;
		}
	
		if ((i+1) % 7 == 0)
			j++;
	}
}

void set_king_coordinates(int xy[2], int offsets[56][2])
{

	const int KING[8][2] = {
		{ 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 }, { 0, 1 }, { 1, 0 },
		{ 0, -1 }, { -1, 0 }
	};
	for (int i = 0; i < 8; i++) {
		int x = KING[i][0];
		int y = KING[i][1];

		int ax = xy[0] + x;
		int ay = xy[1] + y;

		if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else {
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}
	}
}

const int WHITE_PAWN[4][2] = { { 0, -1 }, { 0, -2 }, { -1, -1 }, { 1, -1 } };
const int BLACK_PAWN[4][2] = { { 0, 1 }, { 0, 2 }, { -1, 1 }, { 1, 1 } };
void set_pawn_diagonal_coord(int xy[2], int offsets[56][2], int race)
{
	for (int i = 2; i < 4; i++) {
		int x = 0;
		int y = 0;

		switch(race) {
		case 0: 
			x = BLACK_PAWN[i][0];
			y = BLACK_PAWN[i][1];
			break;
		case 1: 
			x = WHITE_PAWN[i][0];
			y = WHITE_PAWN[i][1];
			break;
		}

		int ax = x + xy[0];
		int ay = y + xy[1];

	        if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else {
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}

	}
}

void set_pawn_coordinates(int xy[2], int offsets[56][2], int race)
{
	for (int i = 0; i < 2; i++) {
		int x = 0;
		int y = 0;

		switch(race) {
		case 0: 
			x = BLACK_PAWN[i][0];
			y = BLACK_PAWN[i][1];
			break;
		case 1: 
			x = WHITE_PAWN[i][0];
			y = WHITE_PAWN[i][1];
			break;
		}
		int ax = xy[0] + x;
		int ay = xy[1] + y;
		int bound = xy_is_between_inc(ax, ay);

		if (race == 1 && bound  && (xy[1] > 5)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else if (race == 1 && bound && (xy[1] <= 5)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
			break;
		}

		if (race == 0 && bound && (xy[1] < 3)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else if (race == 0 && bound && (xy[1] >= 3)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
			break;
		} 
	}
	set_pawn_diagonal_coord(xy, offsets, race);
}

void set_coordinate_by_index(int index, int coordinate[2])
{
	if (index > 63 || index < 0) 
                return;
	int x = 0;
	int y = 0;
	for (int i = 0; i < 64; i += 8) {
		if (index >= i && index <= (i+8-1)) {
			x = i;
			break;
		}
		y++;
	}
	coordinate[0] = index - x;
	coordinate[1] = (index + y) - index;
}

int get_index_by_coordinate(int coordinate[2])
{
	int index = 0;
	index = (coordinate[1] * 8) + coordinate[0];
	return index;
}

void set_square_x(int coordinate[2], int square[2])
{
        int j = 0;
        for (int i = 56; i > 47; i--) {
                if (coordinate[0] == j) {
                        square[0] = i;
                        break;
                }
                j++;
        }
}

void set_square_y(int coordinate[2], int square[2])
{
        int k = 0;
        for (int i = 97; i < 105; i++) {
                if (coordinate[1] == k) {
                        square[1] = i;
                        break;
                } 
                k++;
        }
}

void set_square_by_coordinate(int coordinate[2], int square[2])
{
	set_square_x(coordinate, square);
	set_square_y(coordinate, square);
}

chess_piece pieces[64];
void init_king(int i)
{
        if (i == 4 || i == 60) {
                pieces[i].piece = 5;
                pieces[i].symbol = 'k';

                if (i < 5)
                        strcpy(pieces[i].ascii_symbol, B_KING);
                else
                        strcpy(pieces[i].ascii_symbol, W_KING);
        }
}

void init_queen(int i)
{
        if (i == 3 || i == 59) {
                pieces[i].piece = 4;
                pieces[i].symbol = 'q';

                if (i < 4)
                        strcpy(pieces[i].ascii_symbol, B_QUEEN);
                else
                        strcpy(pieces[i].ascii_symbol, W_QUEEN);
        }
}

void init_bishop(int i)
{
        if (i == 2 || i == 5 || i == 58 || i == 61) {
                pieces[i].piece = 3;
                pieces[i].symbol = 'b';

                if (i < 6)
                        strcpy(pieces[i].ascii_symbol, B_BISHOP);
                else
                        strcpy(pieces[i].ascii_symbol, W_BISHOP);
        }
}

void init_knight(int i)
{
        if (i == 1 || i == 6 || i == 57 || i == 62) {
                pieces[i].piece = 2;
                pieces[i].symbol = 'n';

                if (i < 7)
                        strcpy(pieces[i].ascii_symbol, B_KNIGHT);
                else 
                        strcpy(pieces[i].ascii_symbol, W_KNIGHT);
        }
}

void init_rook(int i)
{
        if (i == 0 || i == 7 || i == 56 || i == 63) {
                pieces[i].piece = 1;
                pieces[i].symbol = 'r';
                if (i < 8)
                        strcpy(pieces[i].ascii_symbol, B_ROOK);
                else  
                        strcpy(pieces[i].ascii_symbol, W_ROOK);
        }
}
void init_pawn(int i)
{
        if ((i > 7 && i < 16) || (i > 47 && i < 56)) {
                pieces[i].piece = 0;
                pieces[i].symbol = 'e';

                if (i < 16)
                        strcpy(pieces[i].ascii_symbol, B_PAWN);
                else
                        strcpy(pieces[i].ascii_symbol, W_PAWN);
        }
}

void init_pieces(int i)
{
	init_king(i);
	init_queen(i);
	init_bishop(i);
	init_knight(i);
	init_rook(i);
	init_pawn(i);
}
void init_chess_pieces()
{
        int bit = 0;
        for (int i = 0; i < 64; i++) {
                pieces[i].race = -1;
                pieces[i].piece = -1;
                pieces[i].is_zero = 0;

                if (bit == 0 && (pieces[i].piece = -1))
                        strcpy(pieces[i].ascii_symbol, " □ ");
                if (bit == 1 && (pieces[i].piece = -1))
                        strcpy(pieces[i].ascii_symbol, " ■ ");

                if (i < 16) { 
                        pieces[i].race = 0;
                        pieces[i].is_zero = 1;
                }
                if (i > 47) {
                        pieces[i].race = 1;
                        pieces[i].is_zero = 1;
                }
                int coordinate[2] = {-1};
                set_coordinate_by_index(i, coordinate);
                for (int j = 0; j < 2; j++)
                        pieces[i].coordinate[j] = coordinate[j];
                init_pieces(i);
                set_square_by_coordinate(coordinate, pieces[i].square);

                pieces[i].clr = bit;
                bit = bit == 0 ? 1 : 0;
                if ((i+1) % 8 == 0)
                        bit = bit == 0 ? 1 : 0;
        }
}


void draw_chess_pieces() 
{
        const char *FILES = " *  a  b  c  d  e  f  g  h  *\n";
        char rank = 8;
	char squares[500] = "\0";

        strcat(squares, FILES);
        for (int i = 0; i < 64; i++) {
                const char *rank_format = " %d  ";
                int buffer_size_rank = snprintf(NULL, 0, rank_format, rank);
                char rank_char[buffer_size_rank+1];
                snprintf(rank_char, buffer_size_rank, rank_format, rank);

                if (i % 8 == 0)
                        strcat(squares, rank_char);

                strcat(squares, pieces[i].ascii_symbol);
                if ((i+1) % 8 == 0) {
                        strcat(squares, rank_char);
                        strcat(squares, "\n");
                        rank--;
                }
        }
	strcat(squares, FILES);
	puts(squares);
}

static int race_turn = 1; // white first
void set_coordinates_to_piece(int piece, int xy[2], int coordinates[56][2])
{
        switch(piece) {
        case 5: 
                set_king_coordinates(xy, coordinates);
                break;
        case 4:
                set_queen_coordinates(xy, coordinates);
                break;
        case 3:
                set_bishop_coordinates(xy, coordinates);
                break;
        case 2:
                set_knight_coordinates(xy, coordinates);
                break;
        case 1:
                set_rook_coordinates(xy, coordinates);
                break;
        case 0:
                set_pawn_coordinates(xy, coordinates, race_turn);
                break;
        default:
                break;
        }
}

void set_chess_piece_dest(int idx_dest, int idx_src)
{
	// you want to separate this values
        // replaces **pieces[idx_src]  with values empty
        pieces[idx_dest].race = pieces[idx_src].race;
        pieces[idx_dest].piece = pieces[idx_src].piece;
        pieces[idx_dest].is_zero = pieces[idx_src].is_zero;
        pieces[idx_dest].symbol = pieces[idx_src].symbol;
        strncpy(pieces[idx_dest].ascii_symbol,
			pieces[idx_src].ascii_symbol,
                       	5);
}

void set_left_square(int idx_src)
{
        pieces[idx_src].race = -1;
        pieces[idx_src].piece = -1;
        pieces[idx_src].is_zero = 0;
        pieces[idx_src].symbol = '\0';
        strncpy(pieces[idx_src].ascii_symbol,
			pieces[idx_src].clr == 1 ? " ■ " : " □ ",
                       	5);
}

int is_king_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int is_valid = 0;
	for (int i = 0; i < 8; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = (int)get_index_by_coordinate(coordinate);
		
		if (index == index_dest) {
			is_valid = 1;
			break;
		}
	}
	if (!is_valid)
		return 0;
	// so long as the dest isn't the same race as the src.
	int is_ally = (int)pieces[index_dest].race == pieces[index_src].race;
	if (is_ally)
		return 0;
	return 1;
}

int is_queen_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int start_track = 0;
	int end_track = 0;
	for (int i = 0; i < 56; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (index_dest == index) {
			end_track = i;
			break;
		}
	}
	start_track = (end_track / 7) * 7;
	for (int i = start_track; i <= end_track; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);
		int is_ally = (pieces[index].piece >= 0 &&
			pieces[index].piece <= 5) &&
			pieces[index_src].race == pieces[index].race;

		if (is_ally)
			return 0;
	}
	return 1;
}

int is_bishop_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int start_track = 0;
	int end_track = 0;
	for (int i = 0; i < 28; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = (int)get_index_by_coordinate(coordinate);

		if (index == index_dest) {
			end_track = i;
			break;
		}
	}
	start_track = (int)(end_track / 7) * 7;
	for (int i = start_track; i != end_track; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = (int)get_index_by_coordinate(coordinate);
		int is_ally = pieces[index_src].race == pieces[index].race;

		if (is_ally)
			return 0;
	}
	return 1;
}


int is_knight_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int is_valid = 0;
	for (int i = 0; i < 8; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = (int)get_index_by_coordinate(coordinate);
		
		if (index == index_dest) {
			is_valid = 1;
			break;
		}
	}
	if (!is_valid)
		return 0;
	// so long as the dest isn't the same race as the src.
	int is_ally = (int)pieces[index_dest].race == pieces[index_src].race;
	if (is_ally)
		return 0;
	return 1;
}

int to_right_castling(int index_src, int index_dest, int coordinates[56][2])
{
	int indexes[7] = {-1};
	int j = 0;
	int is_in_dest = 0;
	for (int i = 7; i < 14; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (pieces[index].piece >= 0 && pieces[index].piece <= 4)
			indexes[j++] = pieces[index].piece;

		if (index == index_dest) {
			is_in_dest = 1;
			break;
		}
	}
	if (!is_in_dest) // there's no path from source to destination
		return 0;

	int is_no_block = 1; // there's no block
	for (int i = 0; i < j+1; i++)
		if (indexes[i] >= 0 && indexes[i] <= 4)
			is_no_block = 0; // there is block

	if (!is_no_block) // pieces are blocking the way to castling
		return 0;
		
	// king before rook
	set_chess_piece_dest(index_dest-1, index_dest);
	return is_no_block;
}

int to_left_castling(int index_src, int index_dest, int coordinates[56][2])
{
	int indexes[7] = {-1};
	int j = 0;
	int is_in_dest = 0;
	for (int i = 21; i < 28; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (pieces[index].piece >= 0 && pieces[index].piece <= 4)
			indexes[j++] = pieces[index].piece;

		if (index == index_dest) {
			is_in_dest = 1;
			break;
		}
	}
	if (!is_in_dest) // there's no path from source to destination
		return 0;

	int is_no_block = 1; // there's no block
	for (int i = 0; i <= j; i++)
		if (indexes[i] >= 0 && indexes[i] <= 4)
			is_no_block = 0; // there is block

	if (!is_no_block) return 0;

	// king after rook
	set_chess_piece_dest(index_dest+1, index_dest);
	return is_no_block;
}

int is_rook_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int is_our_king = pieces[index_src].race == pieces[index_dest].race &&
		pieces[index_dest].piece == 5 &&
		((pieces[index_src].race == 1 && index_src >= 32) ||
		 (pieces[index_src].race == 0 && index_src <= 40));

	if (is_our_king) { // order castling, DOOO ITTT!!! as long as
		if (index_dest > index_src)
			return to_right_castling(index_src,
					index_dest,
					coordinates);
		else if (index_dest < index_src)
			return to_left_castling(index_src,
					index_dest,
					coordinates);
		return 0;
	}
	int start_track = 0;
	int end_track = 0;
	for (int i = 0; i < 28; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = (int)get_index_by_coordinate(coordinate);

		if (index == index_dest) {
			end_track = i;
			break;
		}
	}
	start_track = (int)(end_track / 7) * 7;
	for (int i = start_track; i <= end_track; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = (int)get_index_by_coordinate(coordinate);

		if (pieces[index].piece >= 0 && pieces[index].piece <= 5 && 
				pieces[index].race == pieces[index_src].race)
			return 0;
	}
	return 1;
}

int is_pawn_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int is_move_forward = 0; 
	for (int i = 0; i < 2; i++) {
		int ax = coordinates[i][0];
		int ay = coordinates[i][1];
		int axy[2] = { ax, ay };
		int index = get_index_by_coordinate(axy);

		// check if what's in front of it has piece
		if (pieces[index].piece >= 0 && pieces[index].piece <= 5)
			return 0;

		if (index_dest == index)
			is_move_forward = 1;
	}
	if (is_move_forward)
		return 1;

	for (int i = 2; i < 4; i++) {
		int ax = coordinates[i][0];
		int ay = coordinates[i][1];
		int axy[2] = { ax, ay };
		int index = get_index_by_coordinate(axy);

		if (index == index_dest &&
				pieces[index_src].race != pieces[index].race)
			return 1;
	}
	return 0;
}

int is_chess_piece_move_valid(int dest[2],
                int index_src,
		int index_dest,
		int piece,
                int coordinates[56][2])
{
	switch(piece) {
	case 5: return is_king_move_valid(index_src, index_dest, coordinates);
	case 4: return is_queen_move_valid(index_src, index_dest, coordinates);
	case 3: return is_bishop_move_valid(index_src,index_dest, coordinates);
	case 2: return is_knight_move_valid(index_src, index_dest, coordinates);
	case 1: return is_rook_move_valid(index_src, index_dest, coordinates);
	case 0: return is_pawn_move_valid(index_src, index_dest, coordinates);
	default: return 0;
	}
}

int get_chess_piece(int i)
{
	switch(i) {
	case 104:
		return 5;
	case 113:
		return 4;
	case 98:
		return 3;
	case 110:
		return 2;
	case 114:
		return 1;
	case 101:
		return 0;
	default:
	        return 99999;
	}
}
/******************************************************************************
 * 5 for invalid piece
 * 4 for invalid destination or source
 * 3 attempt to change enemy pieces
 * 2 invalid move
 * 0 success move
 * ***************************************************************************/
int set_chess_piece_to_by_char(char notation[6]) 
{
	// break notation by piece source and destination
	int piece = get_chess_piece((int)notation[0]);
	if (piece == 99999)
		return 5; // 

        int i_src = 0;
        int i_dest = 0;
        char src[3] = "\0";
        char dest[3] = "\0";
        for (int i = 1; i < 3; i++)
                src[i_src++] = notation[i];
        for (int i = 3; i < 6; i++)
                dest[i_dest++] = notation[i];

	// use these indexes for validation and faster lookup
        int idx_src = get_index_by_chess_position(src);
        int idx_dest = get_index_by_chess_position(dest);
        if (idx_dest == 64 || idx_src == 64)
                return 4; // over the bound error

	if (pieces[idx_src].race != race_turn)
		return 3; // don't allow user moving your pice

	// assign the source and destination coordinates
        int src_xy[2] = {-1};
        int dest_xy[2] = {-1};
        int coordinates[56][2];
	for (int i = 0; i < 56; i++)
		for (int j = 0; j < 2; j++)
			coordinates[i][j] = 8;

        set_coordinate_by_index(idx_src, src_xy);
        set_coordinate_by_index(idx_dest, dest_xy);
        set_coordinates_to_piece(piece, src_xy, coordinates);

	// check if move is valid this will check if 
        int is_move_valid = is_chess_piece_move_valid(dest_xy,
                        idx_src,
			idx_dest,
			piece,
                        coordinates); // 0 || 1
	
        if (is_move_valid)
                race_turn = race_turn == 1 ? 0 : 1;
	else
                return 2;

	// move the chess piece
	set_chess_piece_dest(idx_dest, idx_src);
	set_left_square(idx_src);
        return 0;
}

