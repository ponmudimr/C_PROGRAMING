#include "sort_search.h"
#include <assert.h>
#include <stdio.h>

static void test_quick_sort(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    assert(!is_sorted(arr, n));
    quick_sort(arr, n);
    assert(is_sorted(arr, n));
    assert(arr[0] == 5 && arr[n - 1] == 90);

    printf("  [PASS] test_quick_sort\n");
}

static void test_merge_sort(void) {
    int arr[] = {9, -3, 5, 2, 6, 8, -6, 1, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    assert(!is_sorted(arr, n));
    merge_sort(arr, n);
    assert(is_sorted(arr, n));
    assert(arr[0] == -6 && arr[n - 1] == 9);

    printf("  [PASS] test_merge_sort\n");
}

static void test_binary_search(void) {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    assert(binary_search(arr, n, 10) == 4);
    assert(binary_search(arr, n, 2) == 0);
    assert(binary_search(arr, n, 20) == 9);
    assert(binary_search(arr, n, 15) == -1);

    printf("  [PASS] test_binary_search\n");
}

int main(void) {
    printf("--- Running Searching & Sorting Test Suite ---\n");
    test_quick_sort();
    test_merge_sort();
    test_binary_search();
    printf("=== ALL SORTING & SEARCHING TESTS PASSED ===\n");
    return 0;
}
