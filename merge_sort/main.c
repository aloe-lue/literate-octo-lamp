#include <stdio.h>

void merge_sort(double arr[], int start, int end);
void merge(double arr[], int start, int mid, int end);


void merge(double arr[], int start, int mid, int end)
{
        int n1 = mid - start + 1;
        int n2 = end - mid;

        double left[n1], right[n2];

        for (int i = 0; i < n1; i++)
                left[i] = arr[start + i];
        for (int j = 0; j < n2; j++)
                right[j] = arr[mid + 1 + j];

        int i, j, k;
        i = 0;
        j = 0;
        k = start;

        while (i < n1 && j < n2) {
                if (left[i] <= right[j]) {
                        arr[k] = left[i];
                        i++;
                } else {
                        arr[k] = right[j];
                        j++;
                }
                k++;
        }

        while (i < n1) {
                arr[k] = left[i];
                i++;
                k++;
        }
        while (j < n2) {
                arr[k] = right[j];
                j++;
                k++;
        }
}

void merge_sort(double arr[], int start, int end)
{
        if (start < end) {
                int mid = (start + end) / 2;
                merge_sort(arr, start, mid);
                merge_sort(arr, mid + 1, end);
                merge(arr, start, mid, end);
        }
}


int main()
{
        double usorted_arr[] = { 3, 7, 6, -10, 15, 23.5, 55, -13};
        int size = sizeof(usorted_arr) / sizeof(usorted_arr[0]);

        merge_sort(usorted_arr, 0, size - 1);

        printf("sorted arr: ");
        for (int i = 0; i < size; i++)
                printf("%.1f ", usorted_arr[i]);
        printf("\n");
        return 0;
}


