#include <stdio.h>


// func proto: insertion sort
void insertion_sort(int my_array[], int n);


void insertion_sort(int my_array[], int n)
{
        for (int i = 1; i < n; i++) {
                int insert_idx = i;
                int curr_val = my_array[i];
                int j = i - 1;

                while (j >= 0 && my_array[j] > curr_val) {
                        my_array[j + 1] = my_array[j];
                        insert_idx = j;
                        j--;
                }
                my_array[insert_idx] = curr_val;
        }
}

int main()
{
        int my_array[] = { 64, 34, 25, 12, 22, 11, 90, 5 };
        int n = sizeof(my_array) / sizeof(my_array[0]);
        
        insertion_sort(my_array, n);

        printf("sorted array: ");
        for (int i = 0; i < n; i++) {
                printf("%d ", my_array[i]);
        }

        return 0;
}
