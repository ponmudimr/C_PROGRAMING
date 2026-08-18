#include <stdio.h>
#include <assert.h>
#include "bst.h"

static int collected_keys[32];
static size_t collected_count = 0;

static void collect_key(int key) {
    if (collected_count < 32) {
        collected_keys[collected_count++] = key;
    }
}

void test_bst_operations(void) {
    BST *tree = bst_create();
    assert(tree != NULL);
    assert(bst_size(tree) == 0);
    assert(bst_height(tree) == 0);

    /* Insert keys: 50, 30, 70, 20, 40, 60, 80 */
    assert(bst_insert(tree, 50) == true);
    assert(bst_insert(tree, 30) == true);
    assert(bst_insert(tree, 70) == true);
    assert(bst_insert(tree, 20) == true);
    assert(bst_insert(tree, 40) == true);
    assert(bst_insert(tree, 60) == true);
    assert(bst_insert(tree, 80) == true);

    /* Duplicate insertion test */
    assert(bst_insert(tree, 50) == false);

    assert(bst_size(tree) == 7);
    assert(bst_height(tree) == 3);

    /* Search tests */
    assert(bst_search(tree, 40) == true);
    assert(bst_search(tree, 99) == false);

    /* In-order traversal test */
    collected_count = 0;
    bst_inorder(tree, collect_key);
    assert(collected_count == 7);
    int expected[] = {20, 30, 40, 50, 60, 70, 80};
    for (size_t i = 0; i < 7; i++) {
        assert(collected_keys[i] == expected[i]);
    }

    /* Node removal tests */
    /* 1. Leaf node (20) */
    assert(bst_remove(tree, 20) == true);
    assert(bst_search(tree, 20) == false);
    assert(bst_size(tree) == 6);

    /* 2. Node with 2 children (50 root) */
    assert(bst_remove(tree, 50) == true);
    assert(bst_search(tree, 50) == false);
    assert(bst_size(tree) == 5);

    /* Verify in-order traversal post removal */
    collected_count = 0;
    bst_inorder(tree, collect_key);
    assert(collected_count == 5);
    int expected_after[] = {30, 40, 60, 70, 80};
    for (size_t i = 0; i < 5; i++) {
        assert(collected_keys[i] == expected_after[i]);
    }

    bst_destroy(tree);
    printf("  [PASS] test_bst_operations\n");
}

int main(void) {
    printf("--- Running Binary Search Tree Test Suite ---\n");
    test_bst_operations();
    printf("=== ALL BST TESTS PASSED ===\n");
    return 0;
}
