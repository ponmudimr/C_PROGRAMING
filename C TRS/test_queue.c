#include <stdio.h>
#include <assert.h>
#include "queue.h"

void test_queue_basic_ops(void) {
    Queue *q = queue_create(2);
    assert(q != NULL);
    assert(queue_is_empty(q) == true);
    assert(queue_size(q) == 0);

    int val;
    assert(queue_dequeue(q, &val) == false);
    assert(queue_peek(q, &val) == false);

    assert(queue_enqueue(q, 100) == true);
    assert(queue_enqueue(q, 200) == true);
    assert(queue_size(q) == 2);

    assert(queue_peek(q, &val) == true && val == 100);

    /* Enqueue causing capacity expansion */
    assert(queue_enqueue(q, 300) == true);
    assert(queue_size(q) == 3);

    assert(queue_dequeue(q, &val) == true && val == 100);
    assert(queue_dequeue(q, &val) == true && val == 200);
    assert(queue_dequeue(q, &val) == true && val == 300);
    assert(queue_is_empty(q) == true);

    /* Circular wraparound test */
    assert(queue_enqueue(q, 1) == true);
    assert(queue_enqueue(q, 2) == true);
    assert(queue_dequeue(q, &val) == true && val == 1);
    assert(queue_enqueue(q, 3) == true);
    assert(queue_dequeue(q, &val) == true && val == 2);
    assert(queue_dequeue(q, &val) == true && val == 3);
    assert(queue_is_empty(q) == true);

    queue_destroy(q);
    printf("  [PASS] test_queue_basic_ops\n");
}

int main(void) {
    printf("--- Running Queue Test Suite ---\n");
    test_queue_basic_ops();
    printf("=== ALL QUEUE TESTS PASSED ===\n");
    return 0;
}
