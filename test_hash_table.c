#include <stdio.h>
#include <assert.h>
#include "hash_table.h"

void test_hash_table_operations(void) {
    HashTable *ht = ht_create(4);
    assert(ht != NULL);
    assert(ht_size(ht) == 0);

    /* Insert key-value pairs */
    assert(ht_insert(ht, "apple", 100) == true);
    assert(ht_insert(ht, "banana", 200) == true);
    assert(ht_insert(ht, "cherry", 300) == true);
    assert(ht_size(ht) == 3);

    /* Retrieve values */
    int val = 0;
    assert(ht_get(ht, "apple", &val) == true && val == 100);
    assert(ht_get(ht, "banana", &val) == true && val == 200);
    assert(ht_get(ht, "cherry", &val) == true && val == 300);
    assert(ht_get(ht, "durian", &val) == false);

    /* Key existence check */
    assert(ht_contains(ht, "banana") == true);
    assert(ht_contains(ht, "elderberry") == false);

    /* Key update test */
    assert(ht_insert(ht, "apple", 150) == true);
    assert(ht_get(ht, "apple", &val) == true && val == 150);
    assert(ht_size(ht) == 3);

    /* Removal test */
    assert(ht_remove(ht, "banana") == true);
    assert(ht_contains(ht, "banana") == false);
    assert(ht_size(ht) == 2);
    assert(ht_remove(ht, "nonexistent") == false);

    ht_destroy(ht);
    printf("  [PASS] test_hash_table_operations\n");
}

int main(void) {
    printf("--- Running Hash Table Test Suite ---\n");
    test_hash_table_operations();
    printf("=== ALL HASH TABLE TESTS PASSED ===\n");
    return 0;
}
