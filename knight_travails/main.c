#include <stdio.h>

#include "knight_moves.h"
#include "queue_linked_list.h"
#include "hash_set.h"

void init_array(int array[64][2]);

int main()
{

        int bot701[] = { 7, 0 };
        int bot702[] = { 7, 0 };
        int arr0[64][2];
        init_array(arr0);
        knight_moves(arr0, bot701, bot702);

        int bot70[] = { 7, 0 };
        int bot71[] = { 7, 1 };
        int arr1[64][2];
        init_array(arr1);
        knight_moves(arr1, bot70, bot71);
        
        
        int three3[] = { 3, 3 };
        int four3[] = { 4, 3 };
        int arr2[64][2];
        init_array(arr2);
        knight_moves(arr2, three3, four3);
        
        int seven7[] = { 7, 7 };
        int zero0[] = { 0, 0 };
        int arr3[64][2];
        init_array(arr3);
        knight_moves(arr3, seven7, zero0);
        
        int less31[] = { -3, -1 };
        int over99[] = { 9, 9 };
        int arr_err[64][2];
        init_array(arr_err);
        knight_moves(arr_err, less31, over99);

        return 0;


}


void init_array(int array[64][2])
{
        for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 2; j++)
                        array[i][j] = -1;
        }
}
