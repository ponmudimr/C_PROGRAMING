#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "segment_tree.h"

static void test_segment_tree_creation_and_destruction(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    SegmentTree *tree = segment_tree_create(arr, n);
    assert(tree != NULL);
    assert(segment_tree_get_size(tree) == 6);

    segment_tree_destroy(tree);
    printf("  [PASS] test_segment_tree_creation_and_destruction\n");
}

static void test_segment_tree_point_update_and_range_queries(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    SegmentTree *tree = segment_tree_create(arr, n);
    assert(tree != NULL);

    int val = 0;
    assert(segment_tree_query_sum(tree, 0, 5, &val) && val == 36);
    assert(segment_tree_query_sum(tree, 1, 3, &val) && val == 15);
    assert(segment_tree_query_min(tree, 1, 4, &val) && val == 3);
    assert(segment_tree_query_max(tree, 1, 4, &val) && val == 9);

    // Update index 2: change 5 -> 10
    assert(segment_tree_update_point(tree, 2, 10));
    assert(segment_tree_query_sum(tree, 0, 5, &val) && val == 41);
    assert(segment_tree_query_sum(tree, 1, 3, &val) && val == 20);
    assert(segment_tree_query_min(tree, 1, 4, &val) && val == 3);
    assert(segment_tree_query_max(tree, 1, 4, &val) && val == 10);

    segment_tree_destroy(tree);
    printf("  [PASS] test_segment_tree_point_update_and_range_queries\n");
}

static void test_segment_tree_range_update_lazy(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    SegmentTree *tree = segment_tree_create(arr, n);
    assert(tree != NULL);

    int val = 0;
    // Add 10 to elements in range [1, 3]: array becomes [1, 12, 13, 14, 5]
    assert(segment_tree_update_range(tree, 1, 3, 10));

    assert(segment_tree_query_sum(tree, 0, 4, &val) && val == 45);
    assert(segment_tree_query_sum(tree, 1, 3, &val) && val == 39);
    assert(segment_tree_query_min(tree, 0, 4, &val) && val == 1);
    assert(segment_tree_query_min(tree, 1, 3, &val) && val == 12);
    assert(segment_tree_query_max(tree, 1, 4, &val) && val == 14);

    // Add 5 to range [2, 4]: array becomes [1, 12, 18, 19, 10]
    assert(segment_tree_update_range(tree, 2, 4, 5));
    assert(segment_tree_query_sum(tree, 0, 4, &val) && val == 60);
    assert(segment_tree_query_sum(tree, 2, 4, &val) && val == 47);
    assert(segment_tree_query_max(tree, 0, 4, &val) && val == 19);

    segment_tree_destroy(tree);
    printf("  [PASS] test_segment_tree_range_update_lazy\n");
}

static void test_segment_tree_edge_cases(void) {
    int val = 0;
    assert(segment_tree_create(NULL, 0) == NULL);

    int arr[] = {5, 10, 15};
    SegmentTree *tree = segment_tree_create(arr, 3);
    assert(tree != NULL);

    assert(!segment_tree_query_sum(NULL, 0, 2, &val));
    assert(!segment_tree_query_sum(tree, 2, 1, &val));
    assert(!segment_tree_query_sum(tree, 0, 5, &val));

    assert(!segment_tree_update_point(NULL, 0, 100));
    assert(!segment_tree_update_point(tree, 5, 100));

    assert(!segment_tree_update_range(NULL, 0, 2, 10));
    assert(!segment_tree_update_range(tree, 2, 1, 10));
    assert(!segment_tree_update_range(tree, 0, 5, 10));

    assert(segment_tree_get_size(NULL) == 0);

    segment_tree_destroy(tree);
    printf("  [PASS] test_segment_tree_edge_cases\n");
}

int main(void) {
    printf("--- Running Segment Tree Test Suite ---\n");
    test_segment_tree_creation_and_destruction();
    test_segment_tree_point_update_and_range_queries();
    test_segment_tree_range_update_lazy();
    test_segment_tree_edge_cases();
    printf("=== ALL SEGMENT TREE TESTS PASSED ===\n");
    return 0;
}
