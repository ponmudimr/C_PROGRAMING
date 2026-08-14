#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t head;
    size_t tail;
    size_t size;
    size_t capacity;
} Queue;

/* Queue operations */
Queue *queue_create(size_t initial_capacity);
void queue_destroy(Queue *queue);
bool queue_enqueue(Queue *queue, int value);
bool queue_dequeue(Queue *queue, int *out_value);
bool queue_peek(const Queue *queue, int *out_value);
bool queue_is_empty(const Queue *queue);
size_t queue_size(const Queue *queue);

#endif /* QUEUE_H */
