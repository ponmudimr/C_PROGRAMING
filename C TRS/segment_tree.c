#include "segment_tree.h"
#include <stdlib.h>

static void build_tree(SegmentTree *tree, const int *arr, size_t node, size_t start, size_t end) {
    if (start == end) {
        int val = arr ? arr[start] : 0;
        tree->tree_sum[node] = val;
        tree->tree_min[node] = val;
        tree->tree_max[node] = val;
        return;
    }
    size_t mid = start + (end - start) / 2;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;

    build_tree(tree, arr, left_child, start, mid);
    build_tree(tree, arr, right_child, mid + 1, end);

    tree->tree_sum[node] = tree->tree_sum[left_child] + tree->tree_sum[right_child];
    tree->tree_min[node] = (tree->tree_min[left_child] < tree->tree_min[right_child]) ? tree->tree_min[left_child] : tree->tree_min[right_child];
    tree->tree_max[node] = (tree->tree_max[left_child] > tree->tree_max[right_child]) ? tree->tree_max[left_child] : tree->tree_max[right_child];
}

SegmentTree* segment_tree_create(const int *arr, size_t n) {
    if (n == 0) {
        return NULL;
    }

    SegmentTree *tree = (SegmentTree*)malloc(sizeof(SegmentTree));
    if (!tree) {
        return NULL;
    }

    tree->n = n;
    tree->tree_size = 4 * n;

    tree->tree_sum = (int*)calloc(tree->tree_size, sizeof(int));
    tree->tree_min = (int*)calloc(tree->tree_size, sizeof(int));
    tree->tree_max = (int*)calloc(tree->tree_size, sizeof(int));
    tree->lazy = (int*)calloc(tree->tree_size, sizeof(int));
    tree->has_lazy = (bool*)calloc(tree->tree_size, sizeof(bool));

    if (!tree->tree_sum || !tree->tree_min || !tree->tree_max || !tree->lazy || !tree->has_lazy) {
        segment_tree_destroy(tree);
        return NULL;
    }

    build_tree(tree, arr, 0, 0, n - 1);

    return tree;
}

void segment_tree_destroy(SegmentTree *tree) {
    if (!tree) {
        return;
    }
    if (tree->tree_sum) free(tree->tree_sum);
    if (tree->tree_min) free(tree->tree_min);
    if (tree->tree_max) free(tree->tree_max);
    if (tree->lazy) free(tree->lazy);
    if (tree->has_lazy) free(tree->has_lazy);
    free(tree);
}

size_t segment_tree_get_size(const SegmentTree *tree) {
    if (!tree) {
        return 0;
    }
    return tree->n;
}
