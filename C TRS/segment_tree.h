#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <stddef.h>
#include <stdbool.h>

/**
 * SegmentTree structure representing a dynamic Segment Tree with lazy propagation.
 */
typedef struct {
    int *tree_sum;      /* Sum of segments */
    int *tree_min;      /* Min of segments */
    int *tree_max;      /* Max of segments */
    int *lazy;          /* Lazy propagation values */
    bool *has_lazy;     /* Flags tracking pending lazy updates */
    size_t n;           /* Number of elements in the base array */
    size_t tree_size;   /* Allocated size of tree internal arrays */
} SegmentTree;

/**
 * Creates and initializes a Segment Tree from an input array.
 * @param arr Initial array values (can be NULL if n == 0, initialized to zeroes)
 * @param n Size of the array
 * @return Pointer to allocated SegmentTree, or NULL on failure
 */
SegmentTree* segment_tree_create(const int *arr, size_t n);

/**
 * Destroys a Segment Tree and frees all associated memory.
 * @param tree Pointer to SegmentTree
 */
void segment_tree_destroy(SegmentTree *tree);

/**
 * Queries the sum of elements in the range [left, right] inclusive.
 * @param tree Pointer to SegmentTree
 * @param left Start index (0-based)
 * @param right End index (0-based)
 * @param result Pointer to output sum
 * @return true on success, false on invalid parameters/bounds
 */
bool segment_tree_query_sum(SegmentTree *tree, size_t left, size_t right, int *result);

/**
 * Queries the minimum value in the range [left, right] inclusive.
 * @param tree Pointer to SegmentTree
 * @param left Start index (0-based)
 * @param right End index (0-based)
 * @param result Pointer to output min
 * @return true on success, false on invalid parameters/bounds
 */
bool segment_tree_query_min(SegmentTree *tree, size_t left, size_t right, int *result);

/**
 * Queries the maximum value in the range [left, right] inclusive.
 * @param tree Pointer to SegmentTree
 * @param left Start index (0-based)
 * @param right End index (0-based)
 * @param result Pointer to output max
 * @return true on success, false on invalid parameters/bounds
 */
bool segment_tree_query_max(SegmentTree *tree, size_t left, size_t right, int *result);

/**
 * Updates a single element at the specified index.
 * @param tree Pointer to SegmentTree
 * @param index Index to update (0-based)
 * @param val New value for element
 * @return true on success, false on invalid index
 */
bool segment_tree_update_point(SegmentTree *tree, size_t index, int val);

/**
 * Adds value to all elements in the range [left, right] inclusive using lazy propagation.
 * @param tree Pointer to SegmentTree
 * @param left Start index (0-based)
 * @param right End index (0-based)
 * @param add_val Value to add to each element in range
 * @return true on success, false on invalid parameters/bounds
 */
bool segment_tree_update_range(SegmentTree *tree, size_t left, size_t right, int add_val);

/**
 * Returns the size of the original base array.
 * @param tree Pointer to SegmentTree
 * @return Size of base array, or 0 if NULL
 */
size_t segment_tree_get_size(const SegmentTree *tree);

#endif /* SEGMENT_TREE_H */
