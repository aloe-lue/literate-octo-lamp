#ifndef MERGE_SORT_H
#define MERGE_SORT_H

/**
 * recursive merge sort that does the divide
 *
 * @params arr start and end 
 */
int *merge_sort(int *arr, int start, int end);

/**
 * merge function that does the sorting conquer
 *
 * @params
 */
void merge(int *arr, int start, int mid, int end);

#endif
