#include <stdio.h>

#include "merge_sort.h"

void merge(int usort[], int low, int mid, int high)
{
	int n1 = mid - low + 1;
	int n2 = high - mid;
	int left[n1];
	int right[n2];

	for (int i = 0; i < n1; i++)
		left[i] = usort[low + i];
	for (int i = 0; i < n2; i++)
		right[i] = usort[mid + 1 + i];

	int i = 0;
	int j = 0;
	int k = low;

	while (i < n1 && j < n2) {
		if (left[i] <= right[j])
			usort[k] = left[i++];
		else
			usort[k] = right[j++];
		k++;
	}
	while (i < n1)
		usort[k++] = left[i++];
	while (j < n2)
		usort[k++] = right[j++];
}

void merge_sort(int usort[], int low, int high)
{
	if (high > low) {
		int mid = (low + high) >> 1;

		merge_sort(usort, low, mid);
		merge_sort(usort, mid+1, high);
		merge(usort, low, mid, high);
	}
}
