#include <stdio.h>

void counting_sort(int arr[], int n);

void counting_sort(int arr[], int n)
{
        int max_val = arr[0];
        for (int i = 1; i < n; i++) {
                if (arr[i] > max_val) { 
                        max_val = arr[i];
                }
        }

        int count[max_val + 1];
        for (int i = 0; i <= max_val; i++) 
                count[i] = 0;

        for (int i = 0; i < n; i++)
                count[arr[i]]++;

        int index = 0;
        for (int i = 0; i <= max_val; i++) {
                while (count[i] > 0) {
                        arr[index++] = i;
                        count[i]--;
                }
        }
}

int main()
{
        int arr[] = { 4, 2, 2, 6, 3 ,3 ,1 , 6, 5, 2, 3 };
        int n = sizeof(arr) / sizeof(arr[0]);
        
        counting_sort(arr, n);

        printf("sorted array: ");
        for (int i = 0; i < n; i++) 
                printf("%d ", arr[i]);
        printf("\n");

        return 0;
}

