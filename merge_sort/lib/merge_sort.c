#include <stdio.h>
#include <stdlib.h>

void merge_sort(double arr[], int length);
void merge(double left[], int left_size, double right[], int right_size, double result[]);

void merge(double left[], int left_size, double right[], int right_size, double result[])
{
        int i = 0, j = 0, k = 0;

        while (i < left_size && j < right_size) {
                if (left[i] < right[j]) {
                        result[k++] = left[i++];
                } else {
                        result[k++] = right[j++];
                }
        }

        while (i < left_size)
                result[k++] = left[i++];
        while (j < right_size)
                result[k++] = right[j++];
}

void merge_sort(double arr[], int length)
{
        int step = 1;

        while (step < length) {
                for (int i = 0; i < length; i+=2*step) {
                        int left_size = step;
                        int right_size = step;

                        if (i + step >= length) left_size = length - i;
                        if (i + step >= length) right_size = 0;
                        else if (i + 2 * step > length) right_size = length - (i + step);

                        double *left = (double *)malloc(left_size * sizeof(double));
                        double *right = (double *)malloc(right_size * sizeof(double));
                        double *merged = (double *)malloc((left_size + right_size) * sizeof(double));
                        for (int j = 0; j < left_size; ++j)
                                left[j] = arr[i + j];
                        for (int j = 0; j < right_size; ++j)
                                right[j] = arr[i + step + j];
                        
                        merge(left, left_size, right, right_size, merged);

                        for (int j = 0; j < left_size + right_size; ++j) 
                                arr[i + j] = merged[j];
                        
                        free(left);
                        free(right);
                        free(merged);
                }
                step *= 2;
        }
}


int main()
{
        double arr[8] = { -18.0, 3.9, 2.9, -19.0, 20.2, 18.8, 18.3, 1.0 };
        int size = sizeof(arr) / sizeof(arr[0]);

        merge_sort(arr, size);

        printf("Sorted Arr: ");
        for (int i = 0; i < size; i++) 
                printf("%.1f ", arr[i]);
        printf("\n");

        return 0;
};

