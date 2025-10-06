#include <stdio.h>

void selection_sort(int my_array[], int size);

void selection_sort(int my_array[], int size)
{
        int n = size;

        for (int i = 0; i < n; i++) {
                int min_index = i;
                for (int j = i + 1; j < n; j++)  {
                        if (my_array[j] < my_array[min_index])
                                min_index = j;
                }
                int temp = my_array[i];
                my_array[i] = my_array[min_index];
                my_array[min_index] = temp;
        }
}

int main()
{
        int my_array[] = { 64, 34, 25, 5, 22, 1, 90, 12 };
        int n = sizeof(my_array) / sizeof(my_array[0]);

        selection_sort(my_array, n);
        printf("sorted array");
        for (int i = 0; i < n; i++)
                printf("%d ", my_array[i]);
        printf("\n");

        return 0;
}
