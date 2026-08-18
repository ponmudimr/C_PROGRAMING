#include "vector.h"
#include <assert.h>
#include <stdio.h>

static void test_vector_creation_and_push(void) {
    Vector *v = vector_create(2);
    assert(v != NULL);
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 2);

    assert(vector_push(v, 10));
    assert(vector_push(v, 20));
    assert(vector_size(v) == 2);
    assert(vector_capacity(v) == 2);

    // Dynamic resize trigger
    assert(vector_push(v, 30));
    assert(vector_size(v) == 3);
    assert(vector_capacity(v) >= 4);

    int val;
    assert(vector_get(v, 0, &val) && val == 10);
    assert(vector_get(v, 1, &val) && val == 20);
    assert(vector_get(v, 2, &val) && val == 30);

    vector_free(v);
    printf("  [PASS] test_vector_creation_and_push\n");
}

static void test_vector_pop_and_set(void) {
    Vector *v = vector_create(4);
    for (int i = 1; i <= 5; i++) {
        vector_push(v, i * 100);
    }
    assert(vector_size(v) == 5);

    int val;
    assert(vector_pop(v, &val) && val == 500);
    assert(vector_size(v) == 4);

    assert(vector_set(v, 1, 999));
    assert(vector_get(v, 1, &val) && val == 999);

    // Bounds checking
    assert(!vector_get(v, 10, &val));
    assert(!vector_set(v, 10, 123));

    vector_free(v);
    printf("  [PASS] test_vector_pop_and_set\n");
}

int main(void) {
    printf("--- Running Dynamic Vector Test Suite ---\n");
    test_vector_creation_and_push();
    test_vector_pop_and_set();
    printf("=== ALL VECTOR TESTS PASSED ===\n");
    return 0;
}
