#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

void radix_sort(int arr[], int size);

void radix_sort(int arr[], int size)
{
        int max_val = arr[0];
        for (int i = 0; i < size; i++) {
                if (arr[i] > max_val) {
                        max_val = arr[i];
                }
        }

        int exp = 1;
        int *radix_array[10];
        for (int i = 0; i < 10; i++) 
                radix_array[i] = (int *)malloc(sizeof(int) * size);
        int counts[10] = {0};

        while (max_val / exp > 0) {
                for (int i = 0; i < size; i++) {
                        int radix_index = (arr[i] / exp) % 10;
                        radix_array[radix_index][counts[radix_index]] = arr[i];
                        counts[radix_index]++;
                }

                int pos = 0;
                for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < counts[i]; j++) {
                                arr[pos] = radix_array[i][j];
                                pos++;
                        }
                        counts[i] = 0;
                }
                exp *= 10;
        }

        for (int i = 0; i < 10; i++) 
                free(radix_array[i]);

}

int main()
{
        int arr[SIZE] = { 170, 45, 75, 90, 802, 24, 2, 66 };
        printf("Original Array: ");
        for (int i = 0; i < SIZE; i++)
                printf("%d ", arr[i]);
        printf("\n");

        radix_sort(arr, SIZE);

        printf("Sorted Array: ");
        for (int i = 0; i < SIZE; i++)
                printf("%d ", arr[i]);
        printf("\n");

        return 0;
}
