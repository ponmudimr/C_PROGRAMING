#ifndef SORT_SEARCH_H
#define SORT_SEARCH_H

#include <stdbool.h>
#include <stddef.h>

// Checks if an integer array is sorted in non-decreasing order.
bool is_sorted(const int *arr, size_t size);

// Sorts an integer array in-place using Quick Sort algorithm.
void quick_sort(int *arr, size_t size);

// Sorts an integer array in-place using Merge Sort algorithm.
void merge_sort(int *arr, size_t size);

// Performs binary search on a sorted integer array.
// Returns 0-based index if found, or -1 if target is not present.
int binary_search(const int *arr, size_t size, int target);

#endif // SORT_SEARCH_H
