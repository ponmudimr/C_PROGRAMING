#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trie.h"

static void test_trie_creation_and_destruction(void) {
    Trie *trie = trie_create();
    assert(trie != NULL);
    assert(trie_is_empty(trie));
    assert(trie_word_count(trie) == 0);
    assert(trie_node_count(trie) == 1);

    trie_destroy(trie);
    printf("  [PASS] test_trie_creation_and_destruction\n");
}

static void test_trie_insert_and_search(void) {
    Trie *trie = trie_create();

    assert(trie_insert(trie, "apple"));
    assert(trie_insert(trie, "app"));
    assert(trie_insert(trie, "application"));
    assert(trie_insert(trie, "banana"));

    assert(trie_word_count(trie) == 4);
    assert(!trie_is_empty(trie));

    assert(trie_search(trie, "apple"));
    assert(trie_search(trie, "app"));
    assert(trie_search(trie, "application"));
    assert(trie_search(trie, "banana"));

    assert(!trie_search(trie, "appl"));
    assert(!trie_search(trie, "banan"));
    assert(!trie_search(trie, "orange"));

    // Case insensitivity
    assert(trie_search(trie, "APPLE"));
    assert(trie_search(trie, "App"));

    trie_destroy(trie);
    printf("  [PASS] test_trie_insert_and_search\n");
}

static void test_trie_prefix_search(void) {
    Trie *trie = trie_create();

    trie_insert(trie, "car");
    trie_insert(trie, "card");
    trie_insert(trie, "cart");
    trie_insert(trie, "cat");

    assert(trie_starts_with(trie, "ca"));
    assert(trie_starts_with(trie, "car"));
    assert(trie_starts_with(trie, "card"));
    assert(trie_starts_with(trie, "cat"));
    assert(!trie_starts_with(trie, "dog"));
    assert(!trie_starts_with(trie, "carts"));

    trie_destroy(trie);
    printf("  [PASS] test_trie_prefix_search\n");
}

static void test_trie_deletion(void) {
    Trie *trie = trie_create();

    trie_insert(trie, "app");
    trie_insert(trie, "apple");
    trie_insert(trie, "application");

    assert(trie_word_count(trie) == 3);

    // Delete "app"
    assert(trie_delete(trie, "app"));
    assert(trie_word_count(trie) == 2);
    assert(!trie_search(trie, "app"));
    assert(trie_search(trie, "apple"));
    assert(trie_search(trie, "application"));

    // Deleting non-existent word
    assert(!trie_delete(trie, "app"));
    assert(!trie_delete(trie, "orange"));

    // Delete "apple"
    assert(trie_delete(trie, "apple"));
    assert(trie_word_count(trie) == 1);
    assert(!trie_search(trie, "apple"));
    assert(trie_search(trie, "application"));

    trie_destroy(trie);
    printf("  [PASS] test_trie_deletion\n");
}

static void test_trie_autocomplete_and_lcp(void) {
    Trie *trie = trie_create();

    trie_insert(trie, "prefix");
    trie_insert(trie, "preform");
    trie_insert(trie, "prepare");
    trie_insert(trie, "preview");

    #define MAX_RESULTS 10
    #define MAX_LEN 32
    char *results[MAX_RESULTS];
    for (int i = 0; i < MAX_RESULTS; i++) {
        results[i] = (char *)malloc(MAX_LEN);
    }

    size_t count = trie_get_words_with_prefix(trie, "pre", results, MAX_RESULTS, MAX_LEN);
    assert(count == 4);

    char lcp[64];
    bool has_lcp = trie_longest_common_prefix(trie, lcp, sizeof(lcp));
    assert(has_lcp);
    assert(strcmp(lcp, "pre") == 0);

    for (int i = 0; i < MAX_RESULTS; i++) {
        free(results[i]);
    }

    trie_destroy(trie);
    printf("  [PASS] test_trie_autocomplete_and_lcp\n");
}

static void test_trie_clear_and_reuse(void) {
    Trie *trie = trie_create();

    trie_insert(trie, "test");
    trie_insert(trie, "trie");

    assert(trie_word_count(trie) == 2);
    trie_clear(trie);

    assert(trie_is_empty(trie));
    assert(trie_word_count(trie) == 0);
    assert(!trie_search(trie, "test"));

    assert(trie_insert(trie, "hello"));
    assert(trie_search(trie, "hello"));
    assert(trie_word_count(trie) == 1);

    trie_destroy(trie);
    printf("  [PASS] test_trie_clear_and_reuse\n");
}

int main(void) {
    printf("--- Running Trie Data Structure Test Suite ---\n");
    test_trie_creation_and_destruction();
    test_trie_insert_and_search();
    test_trie_prefix_search();
    test_trie_deletion();
    test_trie_autocomplete_and_lcp();
    test_trie_clear_and_reuse();
    printf("=== ALL TRIE TESTS PASSED ===\n");
    return 0;
}
