#include "chess.h"

void init_chess_coordinates(int coordinate_2d[64][2],
		int human_readable_2d[64][2])
{
        int rank = 56;
        int file = 97;
        int row = 0;
        int column = 0;

        for (int i = 0; i < 64; i++) {
                if (file >= 105) file = 97;

                coordinate_2d[i][0] = column;
                coordinate_2d[i][1] = row;

                human_readable_2d[i][0] = rank;
                human_readable_2d[i][1] = file;

                column++;
                if ((i + 1) % 8 == 0) {
                        column = 0;
                        row++;
                        rank--;
                }
                if (file >= 97) file++;
        }
}

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
		int offsets[28][2])
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

		if ((i +1) % 7 == 0) j++;
	}
}

void set_knight_coordinates(int xy[2],
		int offsets[8][2])
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

void set_bishop_coordinates(int xy[2],
		int offsets[28][2])
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
		if ((i + 1) % 7 == 0) j1++;
	}
}

void set_king_coordinates(int xy[2],
		int offsets[8][2])
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

void set_pawn_coordinates(int xy[2],
		int offsets[4][2],
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
		} else if (race == 1 && bound &&
				(xy[0] <= 5)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
			break;
		}

		if (race == 0 && bound &&
				(xy[0] < 3)) {
			offsets[i][0] = coordx;
			offsets[i][1] = coordy;
		} else if (race == 0 && bound &&
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
	coordinate[0] = index - x;
	coordinate[1] = (index + y) - index;
}

int get_index_by_coordinate(int coordinate[2])
{
	int index = (coordinate[1] * 8) + coordinate[0];
	return index;
}

