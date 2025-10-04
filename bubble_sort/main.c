#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int my_array[], int size); 


void bubble_sort(int my_array[], int size)
{
        int n = size;

        for (int i = 0; i < n-1; i++) {
                bool swapped = false;
                for (int j = 0; j < n-i-1; j++) {
                        if (my_array[j] > my_array[j+1]) {
                                int temp = my_array[j];
                                my_array[j] = my_array[j+1];
                                my_array[j+1] = temp;
                                swapped = true;
                        }
                }
                if (!swapped) {
                        break;
                }
        }
}


int main()
{
        int my_array[] = { 64, 34, 25, 12, 22, 11, 90, 5 };
        int n = sizeof(my_array) / sizeof(my_array[0]);

        bubble_sort(my_array, n);


        printf("sorted array: ");
        for (int i = 0; i < n; i++) {
                printf(" %d ", my_array[i]);
        }
        printf("\n");

        return 0;
}

