#include <stdio.h>

int binary_search(int arr[], int size, int targetVal);
int binary_search(int arr[], int size, int targetVal)
{
        int left = 0;
        int right = size - 1;

        while (left <= right) {
                int mid = (left + right) / 2;

                if (arr[mid] == targetVal) 
                        return mid;

                if (arr[mid] < targetVal) {
                        left = mid + 1;
                } else {
                        right = mid - 1;
                }
        }

        return -1;
}

int main()
{
        int arr[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
        int target = 15;
        int size = sizeof(arr) / sizeof(arr[0]);

        int result = binary_search(arr, size, target);

        if (result != -1) {
                printf("Value %d found at index %d\n", target, result); 
        } else {
                printf("Target not found in array.\n");
        }

        return 0;
}
