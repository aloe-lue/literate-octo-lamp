#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include "chess.h"

int cell[64][2] = {{-1}};
// chess piece offsets
int KING_OFFSETS[][2] = {
        { -1, 1 }, { 0, 1 }, { 1, 1 }, { -1, 0 }, { 1, 0 }, { -1, -1 },
        { 0, -1 }, { 1, -1 }
};
int QUEEN_OFFSETS[64][2] = {
        { 1, 1 }, { 7, 7 },
        { -1, 1 }, { -7, 7 },
        { -1, -1 }, { -7, -7 },
        { 1, -1 }, { 7, -7 },
        { 0, 1 }, { 0, 7 },
        { 1, 0 }, { 7, 0 },
        { 0, -1 }, { 0, -7 },
        { -1, 0 }, { -7, 0 }
};
int KNIGHT_OFFSETS[][2] = {
        { -1, 2 }, { 1, 2 }, { 2, 1 }, { 2, -1 }, { -1, -2 }, { 1, -2 },
        { -2, 1 }, { -2, -1 }
};
int BISHOP_OFFSETS[][2] = {
        { 1, 1 }, { 7, 7 },
        { -1, 1 }, { -7, 7 },
        { -1, -1 }, { -7, -7 },
        { 1, -1 }, { 7, -7 }
};
int ROOK_OFFSETS[][2] = {
        { 0, 1 }, { 0, 7 },
        { 1, 0 }, { 7, 0 },
        { 0, -1 }, { 0, -7 },
        { -1, 0 }, { -7, 0 }
};
int PAWN_OFFSETS[][2] = {
        { 0, 2 }, { 0, 1 }, 
        { -1, 1 }, { 1, 1 }
};

void init_chess_board()
{
        int file = 97;
        int rank = 56;

        for (int i = 0; i < 64; i++) {
                if (file >= 105) file = 97;

                cell[i][0] = rank;
                cell[i][1] = file;

                if (file >= 97) file++;
                if ((i +1) % 8 == 0) rank--;
        }
}

int translate_coordinate_char(const char *xy)
{
        int xy_i[2] = {0};
        if (((int)xy[1] >= 105 && (int)xy[1] <= 96)
                        || ((int)xy[0] >= 57 && (int)xy[0] <= 48)) {
                fprintf(stderr, "over the bounds. translate coordinate char.");
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 2; i++)
                xy_i[i] = (int)xy[i];
        for (int i = 0; i < 64; i++) {
                if (cell[i][0] == xy_i[0] && cell[i][1] == xy_i[1])
                        return i;
        }
}

chess_piece chess_cell[64];
void init_chess_pieces()
{
        size_t unicode_size = sizeof BLACK_PAWN_SYMBOL;
        for (int i = 0; i < 64; i++) {
                 if (i == 0 || i == 7)
                         strncpy(chess_cell[i].symbol,
                                         BLACK_ROOK_SYMBOL,
                                         unicode_size);
                 if (i == 1 || i == 6)
                         strncpy(chess_cell[i].symbol,
                                         BLACK_KNIGHT_SYMBOL,
                                         unicode_size);
                 if (i == 2 || i == 5)
                         strncpy(chess_cell[i].symbol,
                                         BLACK_BISHOP_SYMBOL,
                                         unicode_size);
                 if (i == 3)
                         strncpy(chess_cell[i].symbol,
                                         BLACK_QUEEN_SYMBOL,
                                         unicode_size);
                 if (i == 4)
                         strncpy(chess_cell[i].symbol,
                                         BLACK_KING_SYMBOL,
                                         unicode_size);
                 if (i >= 8 && i <= 15)
                         strncpy(chess_cell[i].symbol,
                                         BLACK_PAWN_SYMBOL,
                                         unicode_size);
                 if (i >= 0 && i <= 15) {
                         chess_cell[i].race = 'b';
                         chess_cell[i].index_position = i;
                         chess_cell[i].is_here = true;
                         continue;
                 }

                 if (i >= 48 && i <= 55)
                         strncpy(chess_cell[i].symbol,
                                         WHITE_PAWN_SYMBOL,
                                         unicode_size);
                 if (i == 56 || i == 63)
                         strncpy(chess_cell[i].symbol,
                                         WHITE_ROOK_SYMBOL,
                                         unicode_size);
                 if (i == 57 || i == 62)
                         strncpy(chess_cell[i].symbol,
                                         WHITE_KNIGHT_SYMBOL,
                                         unicode_size);
                 if (i == 58 || i == 61)
                         strncpy(chess_cell[i].symbol,
                                         WHITE_BISHOP_SYMBOL,
                                         unicode_size);
                 if (i == 59)
                         strncpy(chess_cell[i].symbol,
                                         WHITE_QUEEN_SYMBOL,
                                         unicode_size);
                 if (i == 60)
                         strncpy(chess_cell[i].symbol,
                                         WHITE_KING_SYMBOL,
                                         unicode_size);

                 if (i >= 48 && i <= 63) {
                         chess_cell[i].race = 'b';
                         chess_cell[i].index_position = i;
                         chess_cell[i].is_here = true;
                 } else chess_cell[i].is_here = false;
        }
}

void draw_chess()
{
        const char FILES[] = " a  b  c  d  e  f  g  h  \n";
        const int RANKS[] = { 8, 7, 6, 5, 4, 3, 2, 1 };
        int rank_idx = 0;
        
        char chess_board[1024] = "\0";
        strcat(chess_board, FILES);
        for (int i = 0; i < 64; i++) {
                bool is_append_new_line = (i + 1) % 8 == 0;
                
                strcat(chess_board, " ");
                if (is_append_new_line) {
                        strcat(chess_board,
                                        chess_cell[i].is_here ? 
                                                chess_cell[i].symbol :
                                                " ");
                        char rank_format[] = "  %d ";
                        int rank_sz = snprintf(NULL, 
                                        0, 
                                        rank_format, 
                                        RANKS[rank_idx]);
                        char broo[rank_sz +1];
                        snprintf(broo,
                                        rank_sz,
                                        rank_format,
                                        RANKS[rank_idx]);
                        strcat(chess_board, broo);
                        strcat(chess_board, "\n");
                        rank_idx++;
                        continue;
                }
                strcat(chess_board,
                                chess_cell[i].is_here ? 
                                        chess_cell[i].symbol :
                                        " ");
                strcat(chess_board, " ");
        }
        puts(chess_board);
}

