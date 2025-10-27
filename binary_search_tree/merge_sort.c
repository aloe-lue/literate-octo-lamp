#include "merge_sort.h"

void merge(int *arr, int start, int mid, int end)
{
        int n1 = mid - start + 1;
        int n2 = end - mid;

        int left[n1], right[n2];

        for (int i = 0; i < n1; i++)
                left[i] = arr[start + i];
        for (int j = 0; j < n2; j++)
                right[j] = arr[mid + 1 + j];

        int i, j, k;
        i = 0;
        j = 0;
        k = start;

        while (i < n1 && j < n2) {
                if (left[i] <= right[j]) 
                        arr[k] = left[i++];
                else 
                        arr[k] = right[j++];
                k++;
        }

        while (i < n1) 
                arr[k++] = left[i++];
        while (j < n2) 
                arr[k++] = right[j++];
}

int *merge_sort(int *arr, int start, int end)
{
        if (start < end) {
                int mid = (start + end) / 2;
                merge_sort(arr, start, mid);
                merge_sort(arr, mid + 1, end);
                merge(arr, start, mid, end);
        }
        return arr;
}
