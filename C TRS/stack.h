#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Stack;

/* Stack operations */
Stack *stack_create(size_t initial_capacity);
void stack_destroy(Stack *stack);
bool stack_push(Stack *stack, int value);
bool stack_pop(Stack *stack, int *out_value);
bool stack_peek(const Stack *stack, int *out_value);
bool stack_is_empty(const Stack *stack);
size_t stack_size(const Stack *stack);

#endif /* STACK_H */
