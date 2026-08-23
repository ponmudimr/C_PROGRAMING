#include "avl_tree.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

static int g_inorder_buffer[100];
static size_t g_inorder_idx = 0;

static void collect_inorder(int key) {
    if (g_inorder_idx < 100) {
        g_inorder_buffer[g_inorder_idx++] = key;
    }
}

static void test_avl_creation_and_basic_ops(void) {
    AVLTree *tree = avl_create();
    assert(tree != NULL);
    assert(avl_size(tree) == 0);
    assert(avl_height(tree) == 0);
    assert(avl_is_balanced(tree) == true);

    int val;
    assert(avl_min(tree, &val) == false);
    assert(avl_max(tree, &val) == false);
    assert(avl_search(tree, 10) == false);

    avl_destroy(tree);
    printf("  [PASS] test_avl_creation_and_basic_ops\n");
}

static void test_avl_insertions_and_rotations(void) {
    AVLTree *tree = avl_create();

    /* RR Rotation Test: 10 -> 20 -> 30 */
    assert(avl_insert(tree, 10) == true);
    assert(avl_insert(tree, 20) == true);
    assert(avl_insert(tree, 30) == true);
    assert(avl_size(tree) == 3);
    assert(avl_height(tree) == 2);
    assert(avl_is_balanced(tree) == true);

    /* LL Rotation Test: Insert 5, 2 */
    assert(avl_insert(tree, 5) == true);
    assert(avl_insert(tree, 2) == true);
    assert(avl_is_balanced(tree) == true);

    /* LR and RL Rotation Tests: Insert 15, 25 */
    assert(avl_insert(tree, 15) == true);
    assert(avl_insert(tree, 25) == true);
    assert(avl_size(tree) == 7);
    assert(avl_is_balanced(tree) == true);

    int min_val, max_val;
    assert(avl_min(tree, &min_val) == true && min_val == 2);
    assert(avl_max(tree, &max_val) == true && max_val == 30);

    avl_destroy(tree);
    printf("  [PASS] test_avl_insertions_and_rotations\n");
}

static void test_avl_search_and_duplicates(void) {
    AVLTree *tree = avl_create();

    int keys[] = {40, 20, 60, 10, 30, 50, 70};
    for (int i = 0; i < 7; i++) {
        assert(avl_insert(tree, keys[i]) == true);
    }

    for (int i = 0; i < 7; i++) {
        assert(avl_search(tree, keys[i]) == true);
        assert(avl_contains(tree, keys[i]) == true);
    }

    assert(avl_search(tree, 99) == false);
    assert(avl_search(tree, 5) == false);

    /* Duplicate insertion test */
    assert(avl_insert(tree, 40) == false);
    assert(avl_insert(tree, 20) == false);
    assert(avl_size(tree) == 7);

    avl_destroy(tree);
    printf("  [PASS] test_avl_search_and_duplicates\n");
}

static void test_avl_deletion_and_rebalancing(void) {
    AVLTree *tree = avl_create();

    int keys[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 28, 35};
    for (int i = 0; i < 11; i++) {
        avl_insert(tree, keys[i]);
    }
    assert(avl_is_balanced(tree) == true);
    assert(avl_size(tree) == 11);

    /* Delete leaf node */
    assert(avl_remove(tree, 35) == true);
    assert(avl_size(tree) == 10);
    assert(avl_is_balanced(tree) == true);
    assert(avl_search(tree, 35) == false);

    /* Delete node with 1 child */
    assert(avl_remove(tree, 10) == true);
    assert(avl_size(tree) == 9);
    assert(avl_is_balanced(tree) == true);

    /* Delete node with 2 children */
    assert(avl_remove(tree, 50) == true);
    assert(avl_size(tree) == 8);
    assert(avl_is_balanced(tree) == true);
    assert(avl_search(tree, 50) == false);

    /* Remove non-existent key */
    assert(avl_remove(tree, 999) == false);
    assert(avl_size(tree) == 8);

    avl_destroy(tree);
    printf("  [PASS] test_avl_deletion_and_rebalancing\n");
}

static void test_avl_traversals(void) {
    AVLTree *tree = avl_create();

    int keys[] = {30, 10, 50, 20, 40};
    for (int i = 0; i < 5; i++) {
        avl_insert(tree, keys[i]);
    }

    g_inorder_idx = 0;
    avl_inorder(tree, collect_inorder);
    assert(g_inorder_idx == 5);
    for (size_t i = 1; i < g_inorder_idx; i++) {
        assert(g_inorder_buffer[i - 1] < g_inorder_buffer[i]);
    }

    avl_destroy(tree);
    printf("  [PASS] test_avl_traversals\n");
}

static void test_avl_stress_and_balance_invariant(void) {
    AVLTree *tree = avl_create();

    /* Insert sequential numbers 1 to 500 */
    for (int i = 1; i <= 500; i++) {
        assert(avl_insert(tree, i) == true);
        assert(avl_is_balanced(tree) == true);
    }
    assert(avl_size(tree) == 500);

    /* Height of balanced AVL tree with 500 nodes should be <= 12 */
    assert(avl_height(tree) <= 12);

    /* Delete even numbers */
    for (int i = 2; i <= 500; i += 2) {
        assert(avl_remove(tree, i) == true);
    }
    assert(avl_size(tree) == 250);
    assert(avl_is_balanced(tree) == true);

    /* Verify odd numbers still present */
    for (int i = 1; i <= 500; i += 2) {
        assert(avl_search(tree, i) == true);
    }

    avl_destroy(tree);
    printf("  [PASS] test_avl_stress_and_balance_invariant\n");
}

int main(void) {
    printf("--- Running AVL Tree Test Suite ---\n");
    test_avl_creation_and_basic_ops();
    test_avl_insertions_and_rotations();
    test_avl_search_and_duplicates();
    test_avl_deletion_and_rebalancing();
    test_avl_traversals();
    test_avl_stress_and_balance_invariant();
    printf("=== ALL AVL TREE TESTS PASSED ===\n");
    return 0;
}
