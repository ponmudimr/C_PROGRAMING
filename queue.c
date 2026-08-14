#include "queue.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 8

Queue *queue_create(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = DEFAULT_CAPACITY;
    }
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue) return NULL;

    queue->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!queue->data) {
        free(queue);
        return NULL;
    }
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    queue->capacity = initial_capacity;
    return queue;
}

void queue_destroy(Queue *queue) {
    if (!queue) return;
    free(queue->data);
    free(queue);
}

bool queue_enqueue(Queue *queue, int value) {
    if (!queue) return false;
    if (queue->size >= queue->capacity) {
        size_t new_capacity = queue->capacity * 2;
        int *new_data = (int *)malloc(new_capacity * sizeof(int));
        if (!new_data) return false;

        /* Re-align elements starting from index 0 */
        for (size_t i = 0; i < queue->size; i++) {
            new_data[i] = queue->data[(queue->head + i) % queue->capacity];
        }

        free(queue->data);
        queue->data = new_data;
        queue->head = 0;
        queue->tail = queue->size;
        queue->capacity = new_capacity;
    }

    queue->data[queue->tail] = value;
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;
    return true;
}

bool queue_dequeue(Queue *queue, int *out_value) {
    if (!queue || queue->size == 0) return false;
    if (out_value) {
        *out_value = queue->data[queue->head];
    }
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    return true;
}

bool queue_peek(const Queue *queue, int *out_value) {
    if (!queue || queue->size == 0) return false;
    if (out_value) {
        *out_value = queue->data[queue->head];
    }
    return true;
}

bool queue_is_empty(const Queue *queue) {
    if (!queue) return true;
    return queue->size == 0;
}

size_t queue_size(const Queue *queue) {
    if (!queue) return 0;
    return queue->size;
}
