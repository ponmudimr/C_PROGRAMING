#include "heap.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 8

MinHeap *heap_create(size_t initial_capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!heap) return NULL;

    size_t cap = (initial_capacity > 0) ? initial_capacity : DEFAULT_CAPACITY;
    heap->data = (int *)malloc(cap * sizeof(int));
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = cap;
    return heap;
}

void heap_destroy(MinHeap *heap) {
    if (!heap) return;
    if (heap->data) {
        free(heap->data);
    }
    free(heap);
}

bool heap_insert(MinHeap *heap, int value) {
    if (!heap) return false;

    if (heap->size >= heap->capacity) {
        size_t new_cap = heap->capacity * 2;
        int *new_data = (int *)realloc(heap->data, new_cap * sizeof(int));
        if (!new_data) return false;
        heap->data = new_data;
        heap->capacity = new_cap;
    }

    size_t curr = heap->size;
    heap->data[curr] = value;
    heap->size++;

    /* Sift up */
    while (curr > 0) {
        size_t parent = (curr - 1) / 2;
        if (heap->data[curr] < heap->data[parent]) {
            int temp = heap->data[curr];
            heap->data[curr] = heap->data[parent];
            heap->data[parent] = temp;
            curr = parent;
        } else {
            break;
        }
    }

    return true;
}

bool heap_peek(const MinHeap *heap, int *min_val) {
    if (!heap || heap->size == 0 || !min_val) return false;
    *min_val = heap->data[0];
    return true;
}

bool heap_extract_min(MinHeap *heap, int *min_val) {
    if (!heap || heap->size == 0 || !min_val) return false;

    *min_val = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    if (heap->size == 0) return true;

    /* Sift down */
    size_t curr = 0;
    while (true) {
        size_t left = 2 * curr + 1;
        size_t right = 2 * curr + 2;
        size_t smallest = curr;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }

        if (smallest != curr) {
            int temp = heap->data[curr];
            heap->data[curr] = heap->data[smallest];
            heap->data[smallest] = temp;
            curr = smallest;
        } else {
            break;
        }
    }

    return true;
}

size_t heap_size(const MinHeap *heap) {
    return heap ? heap->size : 0;
}

bool heap_is_empty(const MinHeap *heap) {
    return !heap || heap->size == 0;
}
