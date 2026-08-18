#include <stdio.h>
#include <assert.h>
#include "heap.h"

void test_min_heap_operations(void) {
    MinHeap *heap = heap_create(4);
    assert(heap != NULL);
    assert(heap_is_empty(heap) == true);
    assert(heap_size(heap) == 0);

    int val = -1;
    assert(heap_peek(heap, &val) == false);
    assert(heap_extract_min(heap, &val) == false);

    /* Insert unsorted elements */
    assert(heap_insert(heap, 40) == true);
    assert(heap_insert(heap, 10) == true);
    assert(heap_insert(heap, 30) == true);
    assert(heap_insert(heap, 5) == true);
    assert(heap_insert(heap, 20) == true);
    assert(heap_insert(heap, 15) == true);

    assert(heap_size(heap) == 6);
    assert(heap_is_empty(heap) == false);

    /* Peek min element */
    assert(heap_peek(heap, &val) == true);
    assert(val == 5);

    /* Extract elements and verify min-heap order */
    int expected[] = {5, 10, 15, 20, 30, 40};
    for (size_t i = 0; i < 6; i++) {
        assert(heap_extract_min(heap, &val) == true);
        assert(val == expected[i]);
    }

    assert(heap_size(heap) == 0);
    assert(heap_is_empty(heap) == true);
    assert(heap_extract_min(heap, &val) == false);

    heap_destroy(heap);
    printf("  [PASS] test_min_heap_operations\n");
}

int main(void) {
    printf("--- Running Min Heap Test Suite ---\n");
    test_min_heap_operations();
    printf("=== ALL HEAP TESTS PASSED ===\n");
    return 0;
}
