#include "stack.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 8

Stack *stack_create(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = DEFAULT_CAPACITY;
    }
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack) return NULL;

    stack->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!stack->data) {
        free(stack);
        return NULL;
    }
    stack->size = 0;
    stack->capacity = initial_capacity;
    return stack;
}

void stack_destroy(Stack *stack) {
    if (!stack) return;
    free(stack->data);
    free(stack);
}

bool stack_push(Stack *stack, int value) {
    if (!stack) return false;
    if (stack->size >= stack->capacity) {
        size_t new_capacity = stack->capacity * 2;
        int *new_data = (int *)realloc(stack->data, new_capacity * sizeof(int));
        if (!new_data) return false;
        stack->data = new_data;
        stack->capacity = new_capacity;
    }
    stack->data[stack->size++] = value;
    return true;
}

bool stack_pop(Stack *stack, int *out_value) {
    if (!stack || stack->size == 0) return false;
    stack->size--;
    if (out_value) {
        *out_value = stack->data[stack->size];
    }
    return true;
}

bool stack_peek(const Stack *stack, int *out_value) {
    if (!stack || stack->size == 0) return false;
    if (out_value) {
        *out_value = stack->data[stack->size - 1];
    }
    return true;
}

bool stack_is_empty(const Stack *stack) {
    if (!stack) return true;
    return stack->size == 0;
}

size_t stack_size(const Stack *stack) {
    if (!stack) return 0;
    return stack->size;
}
