#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

static void test_linked_list_push_pop(void) {
    LinkedList *list = list_create();
    assert(list != NULL);
    assert(list_size(list) == 0);

    assert(list_push_back(list, 10));
    assert(list_push_back(list, 20));
    assert(list_push_front(list, 5));
    assert(list_size(list) == 3);

    int val;
    assert(list_pop_front(list, &val) && val == 5);
    assert(list_pop_front(list, &val) && val == 10);
    assert(list_size(list) == 1);

    list_free(list);
    printf("  [PASS] test_linked_list_push_pop\n");
}

static void test_linked_list_find_and_reverse(void) {
    LinkedList *list = list_create();
    list_push_back(list, 1);
    list_push_back(list, 2);
    list_push_back(list, 3);

    assert(list_find(list, 2));
    assert(!list_find(list, 99));

    list_reverse(list);

    int val;
    assert(list_pop_front(list, &val) && val == 3);
    assert(list_pop_front(list, &val) && val == 2);
    assert(list_pop_front(list, &val) && val == 1);
    assert(list_size(list) == 0);

    list_free(list);
    printf("  [PASS] test_linked_list_find_and_reverse\n");
}

int main(void) {
    printf("--- Running Linked List Test Suite ---\n");
    test_linked_list_push_pop();
    test_linked_list_find_and_reverse();
    printf("=== ALL LINKED LIST TESTS PASSED ===\n");
    return 0;
}
