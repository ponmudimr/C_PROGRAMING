#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

// Creates a new dynamic vector with specified initial capacity.
Vector* vector_create(size_t initial_capacity);

// Appends an element to the vector. Resizes automatically.
bool vector_push(Vector *v, int element);

// Removes the last element from the vector and stores it in *out_val.
bool vector_pop(Vector *v, int *out_val);

// Gets element at index into *out_val. Returns false if index out of bounds.
bool vector_get(const Vector *v, size_t index, int *out_val);

// Sets element at index. Returns false if index out of bounds.
bool vector_set(Vector *v, size_t index, int val);

// Returns current number of elements in the vector.
size_t vector_size(const Vector *v);

// Returns current total allocated capacity of the vector.
size_t vector_capacity(const Vector *v);

// Frees all memory associated with the vector.
void vector_free(Vector *v);

#endif // VECTOR_H
