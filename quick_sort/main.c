#include <stdio.h>

void quick_sort(int array[], int low, int high);

int partition(int array[], int low, int high);

void quick_sort(int array[], int low, int high)
{
        if (low < high) {
                int pivot_idx = partition(array, low, high);
                quick_sort(array, low, pivot_idx - 1);
                quick_sort(array, pivot_idx + 1, high);
        }
};

int partition(int array[], int low, int high) 
{
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
                if (array[j] < pivot) {
                        i++;
                        int temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                }
        }

        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        return i + 1;
};

int main()
{
        int my_arr[] = { 64, 34, 25, 12, 22, 11, 90, 5 };
        int n = sizeof(my_arr) / sizeof(my_arr[0]);

        quick_sort(my_arr, 0, n - 1);

        printf("sorted arr: ");
        for (int i = 0; i < n; i++) {
                printf("%d ", my_arr[i]);
        }
        return 0;
}

