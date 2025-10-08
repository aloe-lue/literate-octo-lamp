#include <stdio.h>

int linear_search(int arr[], int size, int val);


int linear_search(int arr[], int size, int val)
{
        int i = -1;

        for (int j = 0; j < size - 1; j++) {
                if (arr[j] == val) {
                        return j;
                }         
        }

        return i;
}

int main()
{
        int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        int size = sizeof(arr) / sizeof(arr[0]);

        int fnd_idx = linear_search(arr, size, 8);

        printf("search val 8 ");
        printf("at idx %d \n", fnd_idx);

        return 0;
}
