#include <stdio.h>
#include <assert.h>
#include "stack.h"

void test_stack_basic_ops(void) {
    Stack *s = stack_create(2);
    assert(s != NULL);
    assert(stack_is_empty(s) == true);
    assert(stack_size(s) == 0);

    int val;
    assert(stack_pop(s, &val) == false);
    assert(stack_peek(s, &val) == false);

    assert(stack_push(s, 10) == true);
    assert(stack_push(s, 20) == true);
    assert(stack_size(s) == 2);
    assert(stack_is_empty(s) == false);

    assert(stack_peek(s, &val) == true && val == 20);

    /* Test automatic resizing */
    assert(stack_push(s, 30) == true);
    assert(stack_size(s) == 3);

    assert(stack_pop(s, &val) == true && val == 30);
    assert(stack_pop(s, &val) == true && val == 20);
    assert(stack_pop(s, &val) == true && val == 10);
    assert(stack_is_empty(s) == true);

    stack_destroy(s);
    printf("  [PASS] test_stack_basic_ops\n");
}

int main(void) {
    printf("--- Running Stack Test Suite ---\n");
    test_stack_basic_ops();
    printf("=== ALL STACK TESTS PASSED ===\n");
    return 0;
}
