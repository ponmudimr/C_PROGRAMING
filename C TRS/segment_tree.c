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

static void push_down(SegmentTree *tree, size_t node, size_t start, size_t end) {
    if (!tree->has_lazy[node]) {
        return;
    }
    int lazy_val = tree->lazy[node];
    tree->lazy[node] = 0;
    tree->has_lazy[node] = false;

    if (start != end) {
        size_t mid = start + (end - start) / 2;
        size_t left_child = 2 * node + 1;
        size_t right_child = 2 * node + 2;

        tree->lazy[left_child] += lazy_val;
        tree->has_lazy[left_child] = true;
        tree->tree_sum[left_child] += lazy_val * (int)(mid - start + 1);
        tree->tree_min[left_child] += lazy_val;
        tree->tree_max[left_child] += lazy_val;

        tree->lazy[right_child] += lazy_val;
        tree->has_lazy[right_child] = true;
        tree->tree_sum[right_child] += lazy_val * (int)(end - mid);
        tree->tree_min[right_child] += lazy_val;
        tree->tree_max[right_child] += lazy_val;
    }
}

static int query_sum_recursive(SegmentTree *tree, size_t node, size_t start, size_t end, size_t ql, size_t qr) {
    if (ql <= start && end <= qr) {
        return tree->tree_sum[node];
    }
    push_down(tree, node, start, end);
    size_t mid = start + (end - start) / 2;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;
    int sum = 0;

    if (ql <= mid) {
        sum += query_sum_recursive(tree, left_child, start, mid, ql, qr);
    }
    if (qr > mid) {
        sum += query_sum_recursive(tree, right_child, mid + 1, end, ql, qr);
    }
    return sum;
}

static int query_min_recursive(SegmentTree *tree, size_t node, size_t start, size_t end, size_t ql, size_t qr) {
    if (ql <= start && end <= qr) {
        return tree->tree_min[node];
    }
    push_down(tree, node, start, end);
    size_t mid = start + (end - start) / 2;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;

    if (qr <= mid) {
        return query_min_recursive(tree, left_child, start, mid, ql, qr);
    }
    if (ql > mid) {
        return query_min_recursive(tree, right_child, mid + 1, end, ql, qr);
    }

    int left_min = query_min_recursive(tree, left_child, start, mid, ql, qr);
    int right_min = query_min_recursive(tree, right_child, mid + 1, end, ql, qr);
    return (left_min < right_min) ? left_min : right_min;
}

static int query_max_recursive(SegmentTree *tree, size_t node, size_t start, size_t end, size_t ql, size_t qr) {
    if (ql <= start && end <= qr) {
        return tree->tree_max[node];
    }
    push_down(tree, node, start, end);
    size_t mid = start + (end - start) / 2;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;

    if (qr <= mid) {
        return query_max_recursive(tree, left_child, start, mid, ql, qr);
    }
    if (ql > mid) {
        return query_max_recursive(tree, right_child, mid + 1, end, ql, qr);
    }

    int left_max = query_max_recursive(tree, left_child, start, mid, ql, qr);
    int right_max = query_max_recursive(tree, right_child, mid + 1, end, ql, qr);
    return (left_max > right_max) ? left_max : right_max;
}

static void update_point_recursive(SegmentTree *tree, size_t node, size_t start, size_t end, size_t index, int val) {
    if (start == end) {
        tree->tree_sum[node] = val;
        tree->tree_min[node] = val;
        tree->tree_max[node] = val;
        tree->lazy[node] = 0;
        tree->has_lazy[node] = false;
        return;
    }
    push_down(tree, node, start, end);
    size_t mid = start + (end - start) / 2;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;

    if (index <= mid) {
        update_point_recursive(tree, left_child, start, mid, index, val);
    } else {
        update_point_recursive(tree, right_child, mid + 1, end, index, val);
    }

    tree->tree_sum[node] = tree->tree_sum[left_child] + tree->tree_sum[right_child];
    tree->tree_min[node] = (tree->tree_min[left_child] < tree->tree_min[right_child]) ? tree->tree_min[left_child] : tree->tree_min[right_child];
    tree->tree_max[node] = (tree->tree_max[left_child] > tree->tree_max[right_child]) ? tree->tree_max[left_child] : tree->tree_max[right_child];
}

static void update_range_recursive(SegmentTree *tree, size_t node, size_t start, size_t end, size_t ql, size_t qr, int add_val) {
    push_down(tree, node, start, end);
    if (ql <= start && end <= qr) {
        tree->lazy[node] += add_val;
        tree->has_lazy[node] = true;
        tree->tree_sum[node] += add_val * (int)(end - start + 1);
        tree->tree_min[node] += add_val;
        tree->tree_max[node] += add_val;
        return;
    }
    size_t mid = start + (end - start) / 2;
    size_t left_child = 2 * node + 1;
    size_t right_child = 2 * node + 2;

    if (ql <= mid) {
        update_range_recursive(tree, left_child, start, mid, ql, qr, add_val);
    }
    if (qr > mid) {
        update_range_recursive(tree, right_child, mid + 1, end, ql, qr, add_val);
    }

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

bool segment_tree_query_sum(SegmentTree *tree, size_t left, size_t right, int *result) {
    if (!tree || !result || left > right || right >= tree->n) {
        return false;
    }
    *result = query_sum_recursive(tree, 0, 0, tree->n - 1, left, right);
    return true;
}

bool segment_tree_query_min(SegmentTree *tree, size_t left, size_t right, int *result) {
    if (!tree || !result || left > right || right >= tree->n) {
        return false;
    }
    *result = query_min_recursive(tree, 0, 0, tree->n - 1, left, right);
    return true;
}

bool segment_tree_query_max(SegmentTree *tree, size_t left, size_t right, int *result) {
    if (!tree || !result || left > right || right >= tree->n) {
        return false;
    }
    *result = query_max_recursive(tree, 0, 0, tree->n - 1, left, right);
    return true;
}

bool segment_tree_update_point(SegmentTree *tree, size_t index, int val) {
    if (!tree || index >= tree->n) {
        return false;
    }
    update_point_recursive(tree, 0, 0, tree->n - 1, index, val);
    return true;
}

bool segment_tree_update_range(SegmentTree *tree, size_t left, size_t right, int add_val) {
    if (!tree || left > right || right >= tree->n) {
        return false;
    }
    update_range_recursive(tree, 0, 0, tree->n - 1, left, right, add_val);
    return true;
}
