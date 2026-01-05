#include <stdio.h>
#include <string.h>

#include "chess.h"

static int white_moves = 0;
static int black_moves = 0;

int find_chess_idx(const int RANK, const int FILECC)
{
        int column_idx = 0;
        int row_idx = 0;

        for (int i = 56; i != 49; i--) {
                if (i == RANK)
                        break;
                else
                        row_idx++;
        }
        for (int i = 97; i <= 104; i++) {
        	if (i == FILECC) 
                        break;
        	else
                        column_idx++;
        }
        return (row_idx * 8) + column_idx;
}

int get_index_by_chess_position(char chess_position[3])
{
        const int RANK = (int)chess_position[0];
        const int FILECC = (int)chess_position[1];
        if ((RANK < 49 && RANK > 56) || (FILECC < 97 && FILECC > 104))
		return -1;
        int index = find_chess_idx(RANK, FILECC);
        return index < 0 && index > 63 ? -1 : index;
}

void set_rook_coordinates(int xy[2], int offsets[56][2])
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
		} else {
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

		if ((i + 1) % 7 == 0)
                        j++;
	}
}

void set_knight_coordinates(int xy[2], int offsets[56][2])
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
		} else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}
	}
}

void set_bishop_coordinates(int xy[2], int offsets[56][2])
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
		} else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}

		if (x >= 1 && y >= 1) {
			bishop_start[j][0]++;
			bishop_start[j][1]++;
		} else if (x <= 0 && y >= 1) {
			bishop_start[j][0]--;
			bishop_start[j][1]++;
		} else if (x >= 1 && y <= 0) {
			bishop_start[j][0]++;
			bishop_start[j][1]--;
		} else {
			bishop_start[j][0]--;
			bishop_start[j][1]--;
		}
		if ((i + 1) % 7 == 0)
                        j++;
	}
}

void set_queen_coordinates(int xy[2], int offsets[56][2])
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
		} else {
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

		if ((i +1) % 7 == 0)
                        j++;
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
		} else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}

		if (x >= 1 && y >= 1) {
			bishop_start[j1][0]++;
			bishop_start[j1][1]++;
		} else if (x <= 0 && y >= 1) {
			bishop_start[j1][0]--;
			bishop_start[j1][1]++;
		} else if (x >= 1 && y <= 0) {
			bishop_start[j1][0]++;
			bishop_start[j1][1]--;
		} else {
			bishop_start[j1][0]--;
			bishop_start[j1][1]--;
		}
		if ((i + 1) % 7 == 0)
                        j1++;
	}
}

void set_king_coordinates(int xy[2], int offsets[56][2])
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
		} else {
			offsets[i][0] = -1;
			offsets[i][1] = -1;
		}
	}
}

void set_pawn_coordinates(int xy[2], int offsets[56][2], int race)
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
		
		if (race == 1 && bound && (xy[1] > 5)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		} else if (race == 1 && bound && (xy[1] <= 5)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
			break;
		}

		if (race == 0 && bound && (xy[1] < 3)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		} else if (race == 0 && bound && (xy[1] >= 3)) {
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
	coordinate[1] = (index + y) - index;
	coordinate[0] = index - x;
}

int get_index_by_coordinate(int coordinate[2])
{
	int index = 0;
	index = (coordinate[1] * 8) + coordinate[0];
	return index;
}

void set_square_by_coordinate(int coordinate[2], int square[2])
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

chess_piece pieces[64];
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

void init_pieces(int i)
{
        if (i == 0 || i == 7 || i == 56 || i == 63) {
                pieces[i].piece = 1;
                pieces[i].symbol = 'r';
                if (i < 8)
                        strcpy(pieces[i].ascii_symbol, B_ROOK);
                else  
                        strcpy(pieces[i].ascii_symbol, W_ROOK);
                return;
        }
        if (i == 1 || i == 6 || i == 57 || i == 62) {
                pieces[i].piece = 2;
                pieces[i].symbol = 'n';

                if (i < 7)
                        strcpy(pieces[i].ascii_symbol, B_KNIGHT);
                else 
                        strcpy(pieces[i].ascii_symbol, W_KNIGHT);
                return;
        }
        if (i == 2 || i == 5 || i == 58 || i == 61) {
                pieces[i].piece = 3;
                pieces[i].symbol = 'b';

                if (i < 6)
                        strcpy(pieces[i].ascii_symbol, B_BISHOP);
                else
                        strcpy(pieces[i].ascii_symbol, W_BISHOP);
                return;
        }
        if (i == 3 || i == 59) {
                pieces[i].piece = 4;
                pieces[i].symbol = 'q';

                if (i < 4)
                        strcpy(pieces[i].ascii_symbol, B_QUEEN);
                else
                        strcpy(pieces[i].ascii_symbol, W_QUEEN);
                return;
        }
        if (i == 4 || i == 60) {
                pieces[i].piece = 5;
                pieces[i].symbol = 'k';

                if (i < 5)
                        strcpy(pieces[i].ascii_symbol, B_KING);
                else
                        strcpy(pieces[i].ascii_symbol, W_KING);
                return;
        }
        if ((i > 7 && i < 16) || (i > 47 && i < 57)) {
                pieces[i].piece = 0;
                pieces[i].symbol = 'e';

                if (i < 16)
                        strcpy(pieces[i].ascii_symbol, B_PAWN);
                else
                        strcpy(pieces[i].ascii_symbol, W_PAWN);
                return;
        }
}

// you want to run this every time you render the view, could get ugly if it
// very inefficient function :(
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
        case 107: 
                set_king_coordinates(xy, coordinates);
                break;
        case 113:
                set_queen_coordinates(xy, coordinates);
                break;
        case 98:
                set_bishop_coordinates(xy, coordinates);
                break;
        case 110:
                set_knight_coordinates(xy, coordinates);
                break;
        case 114:
                set_rook_coordinates(xy, coordinates);
                break;
        case 101:
                set_pawn_coordinates(xy, coordinates, race_turn);
                break;
        default:
                break;
        }
}

int is_rook_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int start_track = 0;
	int end_track = 0;
	for (int i = 0; i < 28; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int j = (int)get_index_by_coordinate(coordinate);

		if (j == index_dest)
			end_track = i;
	}
	start_track = (int)(end_track / 7) * 7;
	for (int i = start_track; i != end_track; i++) {
		int x = (int)coordinates[i][0];
		int y = (int)coordinates[i][1];
		int coordinate[2] = { x, y };
		int j = (int)get_index_by_coordinate(coordinate);

		int is_ally = pieces[index_src].race == pieces[j].race;
		if (is_ally)
			return 0;
	}
	return 1;
}

int is_knight_move_valid(int index_src, int index_dest, int coordinates[56][2])
{
	int is_valid = 0;
	for (int i = 0; i < 8; i++) {
		int x = coordinates[i][0];
		int y = coordinates[i][1];
		int coordinate[2] = { x, y };
		int index = get_index_by_coordinate(coordinate);
		
		if (index == index_dest)
			is_valid = 1;
	}
	if (!is_valid)
		return 0; // move isn't valid and it isn't in the coordinates
	int is_ally = pieces[index_dest].race == pieces[index_src].race;
	if (is_ally)
		return 0; // don't kill ally
	return 1;
}

int is_chess_piece_move_valid(int dest[2],
                int index_src,
		int index_dest,
		int piece,
                int coordinates[56][2])
{
	int is_allowed = 0;	
	switch(piece) {
	case 5: // k
	case 4: // q
	case 3: 
		is_allowed = is_rook_move_valid(index_src,
			index_dest,
			coordinates);
		break;
	case 2: // n
		is_allowed = is_knight_move_valid(index_src,
			index_dest,
			coordinates);
		break;
	case 1: // r
		is_allowed = is_rook_move_valid(index_src,
			index_dest,
			coordinates);
		break;
	case 0: // e
	default:
		break;;
	}
	return is_allowed;
}

int get_chess_piece(int i)
{
	switch(i) {
	case 104: // k
		return 5;
	case 113: // g
		return 4;
	case 98: // b
		return 3;
	case 110: // n
		return 2;
	case 114: // r
		return 1;
	case 101: // e
		return 0;
	default:
		return -1;
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
                       6);
}

int set_chess_piece_to_by_char(char notation[6]) 
{
	// break notation by piece source and destination
	int piece = get_chess_piece((int)notation[0]);
	if (piece == -1)
		return 0;
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
        if (idx_dest == -1 || idx_src == -1)
                return 0;

	// assign the source and destination coordinates
        int src_xy[2] = {-1};
        int dest_xy[2] = {-1};
        int coordinates[56][2] = {{-1}};
        set_coordinate_by_index(idx_src, src_xy);
        set_coordinate_by_index(idx_dest, dest_xy);
        set_coordinates_to_piece((int)notation[0], src_xy, coordinates);

	// check if move is valid this will check if 
        int is_move_valid = is_chess_piece_move_valid(dest_xy,
                        idx_src,
			idx_dest,
			piece,
                        coordinates); // 0 || 1
        if (is_move_valid)
                race_turn = race_turn == 1 ? 0 : 1;
	else
                return 1;

	// move the chess piece
	set_chess_piece_dest(idx_dest, idx_src);
	set_left_square(idx_src);
        return 0;
}

