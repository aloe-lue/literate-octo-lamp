#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess.h"
#include "queue_linked_list.h"

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
	int rook[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
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
	int bishop[][2] = { { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 } };
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
	int queen[8][2] = {
		{ 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 }, 
		{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
	};
	int j = 0;
	for (int i = 0; i < 56; i++) {
		int x = queen[j][0];
		int y = queen[j][1];

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
			queen[j][0]++;
			queen[j][1]++;
			break;
		case 1:
			queen[j][0]--;
			queen[j][1]++;
			break;
		case 2:
			queen[j][0]++;
			queen[j][1]--;
			break;
		case 3:
			queen[j][0]--;
			queen[j][1]--;
			break;
		case 4:
			queen[j][1]++;
			break;
		case 5:
			queen[j][0]++;
			break;
		case 6:
			queen[j][1]--;
			break;
		case 7:
			queen[j][0]--;
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

void set_pawn_coordinates(int xy[2], int offsets[56][2], int race)
{
	const int WHITE_PAWN[4][2] = {
		{ 0, -1 }, { 0, -2 }, { -1, -1 }, { 1, -1 } 
	};
	const int BLACK_PAWN[4][2] = {
		{ 0, 1 }, { 0, 2 }, { -1, 1 }, { 1, 1 }
	};
	for (int i = 0; i < 4; i++) {
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

		if (xy_is_between_inc(ax, ay)) {
			offsets[i][0] = ax;
			offsets[i][1] = ay;
		} else {
			offsets[i][0] = 8;
			offsets[i][1] = 8;
		}
	}
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
	int x = 0;
	for (int i = 97; i <= 104; i++) {
		if (coordinate[0] == x) {
			square[0] = i;
			break;
		}
		x++;
	}
}

void set_square_y(int coordinate[2], int square[2])
{
	int y = 0;
	for (int i = 56; i >= 48; i--) {
		if (coordinate[1] == y) {
			square[1] = i;
			break;
		}
		y++;
	}
}

void set_square_by_coordinate(int coordinate[2], int square[2])
{
	set_square_x(coordinate, square);
	set_square_y(coordinate, square);
}

void init_king(chess_piece **pieces)
{
	int king_placements[] = { 4, 60 };
	for (int i = 0; i < 2; i++) {
		int k_loc = king_placements[i];
		pieces[k_loc]->piece = 5;
		pieces[k_loc]->symbol = 'k';
		pieces[k_loc]->contain_piece = 1;
		
		switch(k_loc) {
		case 4:
			pieces[k_loc]->race = 0;
                	strcpy(pieces[k_loc]->ascii_symbol, B_KING);
			break;
		case 60:
			pieces[k_loc]->race = 1;
                	strcpy(pieces[k_loc]->ascii_symbol, W_KING);
			break;
		}
	}
}

void init_queen(chess_piece **pieces)
{
	int queen_placements[] = { 3, 59 };
	for (int i = 0; i < 2; i++) {
		int q_loc = queen_placements[i];
		pieces[q_loc]->piece = 4;
		pieces[q_loc]->symbol = 'q';
		pieces[q_loc]->contain_piece = 1;
		
		switch(q_loc) {
		case 3:
			pieces[q_loc]->race = 0;
                	strcpy(pieces[q_loc]->ascii_symbol, B_QUEEN);
			break;
		case 59:
			pieces[q_loc]->race = 1;
                	strcpy(pieces[q_loc]->ascii_symbol, W_QUEEN);
			break;
		}
	}
}

void init_bishop(chess_piece **pieces)
{
        int bishop_placements[] = { 2, 5, 58, 61 };
	for (int i = 0; i < 4; i++) {
		int b_loc = bishop_placements[i];
		pieces[b_loc]->piece = 3;
		pieces[b_loc]->symbol = 'b';
		pieces[b_loc]->contain_piece = 1;

		switch(b_loc) {
		case 2:
		case 5:
			pieces[b_loc]->race = 0;
			strcpy(pieces[b_loc]->ascii_symbol, B_BISHOP);
			break;
		case 58:
		case 61:
			pieces[b_loc]->race = 1;
			strcpy(pieces[b_loc]->ascii_symbol, W_BISHOP);
			break;
		}
	}
}

void init_knight(chess_piece **pieces )
{
	int knight_placements[] = { 1, 6, 57, 62 };
	for (int i = 0; i < 4; i++) {
		int n_loc = knight_placements[i];
		pieces[n_loc]->piece = 2;
		pieces[n_loc]->symbol = 'n';
		pieces[n_loc]->contain_piece = 1;

		switch(n_loc) {
		case 1:
		case 6:
			pieces[n_loc]->race = 0;
			strcpy(pieces[n_loc]->ascii_symbol, B_KNIGHT);
			break;
		case 57:
		case 62:
			pieces[n_loc]->race = 1;
			strcpy(pieces[n_loc]->ascii_symbol, W_KNIGHT);
			break;
		}
	}

}

void init_rook(chess_piece **pieces)
{
	int rook_places[] = { 0, 7, 56, 63 };
	for (int i = 0; i < 4; i++) {
		int r_loc = rook_places[i];
		pieces[r_loc]->piece = 1;
		pieces[r_loc]->symbol = 'r';
        	pieces[i]->contain_piece = 1;

		switch(r_loc) {
		case 0:
		case 7:
        		pieces[i]->race = 0;
                	strcpy(pieces[r_loc]->ascii_symbol, B_ROOK);
			break;
		case 56:
		case 63:
        		pieces[i]->race = 1;
                        strcpy(pieces[r_loc]->ascii_symbol, W_ROOK);
			break;
		}
	}
}

void init_pawn(chess_piece **pieces)
{
	for (int i = 8; i < 16; i++) {
        	pieces[i]->piece = 0;
        	pieces[i]->symbol = 'e';
        	pieces[i]->race = 0;
        	pieces[i]->contain_piece = 1;

        	strcpy(pieces[i]->ascii_symbol, B_PAWN);
	}
	for (int i = 48; i < 56; i++) {
        	pieces[i]->piece = 0;
        	pieces[i]->symbol = 'e';
        	pieces[i]->race = 1;
        	pieces[i]->contain_piece = 1;

        	strcpy(pieces[i]->ascii_symbol, W_PAWN);
	}
}

chess_piece **init_chess_pieces()
{
	chess_piece **pieces = malloc(sizeof(chess_piece) * 64);
	if (pieces == NULL) {
		fprintf(stderr, "malloc fail: init_chess_pieces");
		exit(1);
	}
        int bit = 0;
        for (int i = 0; i < 64; i++) {
		pieces[i] = malloc(sizeof(chess_piece));
		if (pieces[i] == NULL) {
			fprintf(stderr, "malloc fail: init_chess_pieces");
			exit(1);
		}
       		pieces[i]->race = -1;
        	pieces[i]->piece = -1;
        	pieces[i]->contain_piece = 0;

        	if (bit == 0 && (pieces[i]->piece = -1))
        	        strcpy(pieces[i]->ascii_symbol, " □ ");
        	if (bit == 1 && (pieces[i]->piece = -1))
        	        strcpy(pieces[i]->ascii_symbol, " ■ ");

        	int coordinate[2] = {-1};
        	set_coordinate_by_index(i, coordinate);

        	for (int j = 0; j < 2; j++)
        	        pieces[i]->coordinate[j] = coordinate[j];

        	set_square_by_coordinate(coordinate, pieces[i]->square);

        	pieces[i]->clr = bit;
        	bit = bit == 0 ? 1 : 0;

        	if ((i+1) % 8 == 0)
        	        bit = bit == 0 ? 1 : 0;
        }
	return pieces;
}

void free_chess_pieces(chess_piece **pieces)
{
	for (int i = 0; i < 64; i++)
		free(pieces[i]);
	free(pieces);
}

void draw_chess_pieces(chess_piece **pieces) 
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

                strcat(squares, pieces[i]->ascii_symbol);
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
void set_coordinates_to_piece(int piece,
		int xy[2],
		int coordinates[56][2],
		chess_piece **pieces)
{
        switch(piece) {
        case 0:
                set_pawn_coordinates(xy, coordinates, race_turn);
                break;
        case 1:
                set_rook_coordinates(xy, coordinates);
                break;
        case 2:
                set_knight_coordinates(xy, coordinates);
                break;
        case 3:
                set_bishop_coordinates(xy, coordinates);
                break;
        case 4:
                set_queen_coordinates(xy, coordinates);
                break;
        case 5: 
                set_king_coordinates(xy, coordinates);
                break;
        default:
                break;
        }
}

void set_chess_piece_dest(int idx_dest, int idx_src, chess_piece **pieces)
{
	// you want to separate this values
        // replaces **pieces[idx_src]-> with values empty
        pieces[idx_dest]->race = pieces[idx_src]->race;
        pieces[idx_dest]->piece = pieces[idx_src]->piece;
        pieces[idx_dest]->contain_piece = pieces[idx_src]->contain_piece;
        pieces[idx_dest]->symbol = pieces[idx_src]->symbol;
        strncpy(pieces[idx_dest]->ascii_symbol,
			pieces[idx_src]->ascii_symbol,
                       	5);
}

void set_left_square(int idx_src, chess_piece **pieces)
{
	pieces[idx_src]->race = -1;
	pieces[idx_src]->piece = -1;
	pieces[idx_src]->contain_piece = 0;
	pieces[idx_src]->symbol = '\0';
	strncpy(pieces[idx_src]->ascii_symbol,
			pieces[idx_src]->clr == 1 ? " ■ " : " □ ",
			5);
}

int is_king_move_valid(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int is_valid = 0;
	for (int i = 0; i < 8; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (index == index_dest) {
			is_valid = 1;
			break;
		}
	}
	if (!is_valid)
		return 0;
	// so long as the dest isn't the same race as the src.
	int is_ally = pieces[index_src]->race == pieces[index_dest]->race;

	if (is_ally == 1)
		return 0;

	return 1;
}

int is_queen_move_valid(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int begin_track = 0;
	int end_track = 0;
	for (int i = 0; i < 56; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (index_dest == index) {
			end_track = i;
			break;
		}
	}
	begin_track = (int)(end_track / 7) * 7;
	for (int i = begin_track; i <= end_track; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);
		int is_ally = (pieces[index]->piece >= 0 &&
				pieces[index]->piece <= 5) &&
				pieces[index_src]->race == pieces[index]->race;

		if (is_ally)
			return 0;
	}
	return 1;
}

int is_bishop_move_valid(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int begin_track = 0;
	int end_track = 0;
	for (int i = 0; i < 28; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (index == index_dest) {
			end_track = i;
			break;
		}
	}
	begin_track = (int)(end_track / 7) * 7;
	for (int i = begin_track; i != end_track; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);
		int is_ally = pieces[index_src]->race == pieces[index]->race;

		if (is_ally)
			return 0;
	}
	return 1;
}

int is_knight_move_valid(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
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
	int is_ally = pieces[index_dest]->race == pieces[index_src]->race;
	if (is_ally)
		return 0;
	return 1;
}

int to_right_castling(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int indexes[7] = {-1};
	int j = 0;
	int is_in_dest = 0;
	for (int i = 7; i < 14; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (pieces[index]->piece >= 0 && pieces[index]->piece <= 4)
			indexes[j++] = pieces[index]->piece;

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
	set_chess_piece_dest(index_dest-1, index_dest, pieces);
	return is_no_block;
}

int to_left_castling(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int indexes[7] = {-1};
	int j = 0;
	int is_in_dest = 0;
	for (int i = 21; i < 28; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (pieces[index]->piece >= 0 && pieces[index]->piece <= 4)
			indexes[j++] = pieces[index]->piece;

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
	set_chess_piece_dest(index_dest+1, index_dest, pieces);
	return is_no_block;
}

int is_rook_move_valid(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int is_our_king = pieces[index_src]->race == pieces[index_dest]->race &&
		pieces[index_dest]->piece == 5 &&
		((pieces[index_src]->race == 1 && index_src >= 32) ||
		 (pieces[index_src]->race == 0 && index_src <= 32));

	if (is_our_king) { // order castling, DOOO ITTT!!! as long as
		if (index_dest > index_src)
			return to_right_castling(index_src,
				index_dest,
				coordinates,
				pieces);
		else if (index_dest < index_src)
			return to_left_castling(index_src,
				index_dest,
				coordinates,
				pieces);
		return 0;
	}
	int begin_track = 0;
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
	begin_track = (int)(end_track / 7) * 7;
	for (int i = begin_track; i <= end_track; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);

		if (pieces[index]->piece >= 0 && pieces[index]->piece <= 5 && 
			pieces[index]->race == pieces[index_src]->race)
			return 0;
	}
	return 1;
}

/***************************************
 * invalidate en passant is to invalidate
 * the en passant for moving other piece
 * other than the priority piece.  for
 * now this is the solution i can think of
 * since there should be other solution
 * that are far better. or exceptional
 * hmmmm simpleton that I am.
 *
 * use linked list queue to check within
 * the en passant bound everytime there
 * is move validation.
 * ************************************/
static int invalid_en_passant = 0;
static int en_passant_white = 0;
static int en_passant_black = 0;

/**************************************
 * this two functions together with above
 * declaration helps with invalidating
 * en passant i guess i should just use
 * global variables this is bad idea ain't
 * it?
 * ***********************************/
void white_en_passant(chess_piece **pieces, int index_src, int src_race)
{
	if (src_race == 1 && index_src >= 24 && index_src < 32) {
		if (index_src == 24 && pieces[index_src]->race !=
				pieces[index_src+1]->race &&
				pieces[index_src+1]->contain_piece)
		       en_passant_white++;
		else if (index_src == 31 && pieces[index_src]->race !=
				pieces[index_src-1]->race &&
				pieces[index_src-1]->contain_piece)
			en_passant_white++;
		else if (index_src > 24 && index_src < 31 &&
				(pieces[index_src]->race !=
				pieces[index_src-1]->race ||
				pieces[index_src]->race !=
				pieces[index_src+1]->race) &&
				(pieces[index_src-1]->contain_piece ||
				pieces[index_src+1]->contain_piece))
			en_passant_white++;
	}
}

void black_en_passant(chess_piece **pieces, int index_src, int src_race)
{
	if (src_race == 0 && index_src >= 32 && index_src < 40) {
		if (index_src == 32 && pieces[index_src]->race !=
				pieces[index_src+1]->race &&
				pieces[index_src+1]->contain_piece)
		       en_passant_black++;
		else if (index_src == 39 && pieces[index_src]->race !=
				pieces[index_src-1]->race &&
				pieces[index_src-1]->contain_piece)
			en_passant_black++;
		else if (index_src > 32 && index_src < 40 &&
				(pieces[index_src]->race !=
				pieces[index_src-1]->race ||
				pieces[index_src]->race !=
				pieces[index_src+1]->race) &&
				(pieces[index_src-1]->contain_piece ||
				pieces[index_src+1]->contain_piece))
			en_passant_black++;
	}
}

int is_pawn_move_valid(int index_src,
		int index_dest,
		int coordinates[56][2],
		chess_piece **pieces)
{
	int is_valid = 0;
	int loc = 0;

	for (int i = 0; i < 4; i++) {
		int ax = coordinates[i][0];
		int ay = coordinates[i][1];
		int axy[] = { ax, ay };
		int index = get_index_by_coordinate(axy);

		if (index == index_dest)
			is_valid = 1;

		if (i <= 1 && is_valid) {
			loc = i;
			break;
		}

		if (i >= 2 && is_valid) {
			loc = i;
			break;
		}
	}
	if (!is_valid)
		return 0;
	int src_race = pieces[index_src]->race;


	// move one forward
	if (is_valid && loc == 0 && !pieces[index_dest]->contain_piece) {
		int wpawn_promotion = src_race == 1 ?
			(index_src >= 0 && index_src <= 7) : 0;

		int bpawn_promotion = src_race == 0 ?
			(index_src >= 56 && index_src <= 63) : 0;

		if (wpawn_promotion || bpawn_promotion)
			return 5;

		black_en_passant(pieces, index_src, src_race);
		white_en_passant(pieces, index_src, src_race);
		return 1;
	}

	// devour diagonally
	if (is_valid && pieces[index_dest]->contain_piece &&
			src_race != pieces[index_dest]->race)
		return 1;

	// en passant left 
	if (is_valid && loc == 2 && !pieces[index_dest]->contain_piece &&
			!invalid_en_passant && src_race == 1 ?
			index_src >= 24 && index_src <= 31 :
			index_src >= 32 && index_src <= 39 &&
			src_race != pieces[index_src-1]->race) {
		set_left_square(index_src-1, pieces);
		return 1;
	}

	// en passant right
	if (is_valid && loc == 3 && !pieces[index_dest]->contain_piece &&
			!invalid_en_passant && src_race == 1 ?
			index_src >= 24 && index_src <= 31 : index_src >= 32 &&
			index_src <= 39 && src_race !=
			pieces[index_src+1]->race) {
		set_left_square(index_src+1, pieces);
		return 1;
	}

	// move twice block
	// potential error: ArrayIndexOutOfBoundExceptionError
	// nope i don't program in java or c# it just pretty good to read
	if (is_valid && loc == 1 && src_race == 1 ? index_src >= 48 &&
			index_src <= 55 : index_src >= 7 && index_src <= 15 &&
			src_race == 1 ? !pieces[index_dest-8]->contain_piece :
			!pieces[index_dest+8]->contain_piece)
		return 1;

	return 0;
}

int is_chess_piece_move_valid(int dest[2],
                int index_src,
		int index_dest,
		int piece,
                int coordinates[56][2],
		chess_piece **pieces)
{
	switch(piece) {
	case 0:
		return is_pawn_move_valid(index_src, index_dest, coordinates,
				pieces);
	case 1:
		return is_rook_move_valid(index_src, index_dest, coordinates,
				pieces);
	case 2:
		return is_knight_move_valid(index_src, index_dest, coordinates,
				pieces);
	case 3:
		return is_bishop_move_valid(index_src, index_dest, coordinates,
				pieces);
	case 4:
		return is_queen_move_valid(index_src, index_dest, coordinates,
				pieces);
	case 5:
		return is_king_move_valid(index_src, index_dest, coordinates,
				pieces);
	default:
		return 0;
	}
}

int get_chess_piece(int i)
{
	switch(i) {
	case 98: // bishop->b
		return 3;
	case 101: // pawn->e
		return 0;
	case 107: // king->k 
		return 5;
	case 110: // knight->n
		return 2;
	case 113: // queen->q
		return 4;
	case 114: // rook->r
		return 1;
	default:
	        return 6;
	}
}

/******************************************************************************
 * 5 invalid piece
 * 4 invalid destination or source
 * 3 attempt to change enemy pieces
 * 2 piece isn't there
 * 1 invalid move
 * 0 success move
 * ***************************************************************************/
int set_chess_piece_to_by_char(char notation[6], chess_piece **pieces) 
{
	// break notation by piece source and destination
	int piece = get_chess_piece((int)notation[0]);
	if (piece == 6)
		return 5;

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

	if (pieces[idx_src]->race != race_turn)
		return 3; // don't allow user moving your piece

	// assign the source and destination coordinates
        int src_xy[2] = {-1};
        int dest_xy[2] = {-1};
        int coordinates[56][2];
	for (int i = 0; i < 56; i++)
		for (int j = 0; j < 2; j++)
			coordinates[i][j] = -1;

	if (pieces[idx_src]->piece != piece)
		return 2; // avoid using other piece coordinates

        set_coordinate_by_index(idx_src, src_xy);
        set_coordinate_by_index(idx_dest, dest_xy);
        set_coordinates_to_piece(piece, src_xy, coordinates, pieces);

	// check if move is valid this will check if 
        int is_move_valid = is_chess_piece_move_valid(dest_xy, idx_src,
			idx_dest, piece, coordinates, pieces);
	
        if (is_move_valid)
                race_turn = race_turn == 1 ? 0 : 1;
	else
                return 1;

	// move the chess piece
	set_chess_piece_dest(idx_dest, idx_src, pieces);
	set_left_square(idx_src, pieces);
        return 0;
}

