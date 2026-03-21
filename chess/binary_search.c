#include "binary_search.h"

int binary_search(int numbers[], int numbers_len, int target_number)
{
	int left = 0;
	int right = numbers_len - 1;
	
	while (left <= right) {
		int mid = (left + right) >> 1;

		if (numbers[mid] == target_number)
			return mid;

		if (numbers[mid] < target_number)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return 64;
}
