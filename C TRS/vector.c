#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_INITIAL_CAPACITY 4

Vector* vector_create(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = DEFAULT_INITIAL_CAPACITY;
    }
    Vector *v = (Vector*) malloc(sizeof(Vector));
    if (!v) return NULL;

    v->data = (int*) malloc(initial_capacity * sizeof(int));
    if (!v->data) {
        free(v);
        return NULL;
    }
    v->size = 0;
    v->capacity = initial_capacity;
    return v;
}

bool vector_push(Vector *v, int element) {
    if (!v) return false;

    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity * 2;
        int *new_data = (int*) realloc(v->data, new_capacity * sizeof(int));
        if (!new_data) return false;
        v->data = new_data;
        v->capacity = new_capacity;
    }

    v->data[v->size++] = element;
    return true;
}

bool vector_pop(Vector *v, int *out_val) {
    if (!v || v->size == 0) return false;

    v->size--;
    if (out_val) {
        *out_val = v->data[v->size];
    }
    return true;
}

bool vector_get(const Vector *v, size_t index, int *out_val) {
    if (!v || !out_val || index >= v->size) return false;
    *out_val = v->data[index];
    return true;
}

bool vector_set(Vector *v, size_t index, int val) {
    if (!v || index >= v->size) return false;
    v->data[index] = val;
    return true;
}

size_t vector_size(const Vector *v) {
    return v ? v->size : 0;
}

size_t vector_capacity(const Vector *v) {
    return v ? v->capacity : 0;
}

void vector_free(Vector *v) {
    if (v) {
        if (v->data) {
            free(v->data);
        }
        free(v);
    }
}
