#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

/* MinHeap Operations */
MinHeap *heap_create(size_t initial_capacity);
void heap_destroy(MinHeap *heap);
bool heap_insert(MinHeap *heap, int value);
bool heap_peek(const MinHeap *heap, int *min_val);
bool heap_extract_min(MinHeap *heap, int *min_val);
size_t heap_size(const MinHeap *heap);
bool heap_is_empty(const MinHeap *heap);

#endif /* HEAP_H */
