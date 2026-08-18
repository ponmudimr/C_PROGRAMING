#include "sort_search.h"
#include <stdlib.h>
#include <string.h>

bool is_sorted(const int *arr, size_t size) {
    if (!arr || size <= 1) return true;
    for (size_t i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void quick_sort_recursive(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void quick_sort(int *arr, size_t size) {
    if (!arr || size <= 1) return;
    quick_sort_recursive(arr, 0, (int)size - 1);
}

static void merge(int *arr, int left, int mid, int right, int *temp) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

static void merge_sort_recursive(int *arr, int left, int right, int *temp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(arr, left, mid, temp);
        merge_sort_recursive(arr, mid + 1, right, temp);
        merge(arr, left, mid, right, temp);
    }
}

void merge_sort(int *arr, size_t size) {
    if (!arr || size <= 1) return;
    int *temp = (int*) malloc(size * sizeof(int));
    if (!temp) return;
    merge_sort_recursive(arr, 0, (int)size - 1, temp);
    free(temp);
}

int binary_search(const int *arr, size_t size, int target) {
    if (!arr || size == 0) return -1;

    int low = 0;
    int high = (int)size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}
