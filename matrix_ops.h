#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdbool.h>
#include <stddef.h>

// Calculates the sum of elements in an integer array.
int array_sum(const int *arr, size_t size);

// Finds the maximum value in an integer array.
int array_find_max(const int *arr, size_t size);

// Finds the minimum value in an integer array.
int array_find_min(const int *arr, size_t size);

// Transposes a matrix of dimensions rows x cols into dst (cols x rows).
void matrix_transpose(int rows, int cols, const int *src, int *dst);

// Checks whether an n x n square matrix is symmetric (A == A^T).
bool is_matrix_symmetric(int n, const int *mat);

// Multiplies matrix A (r1 x c1) by matrix B (r2 x c2) and stores result in res (r1 x c2).
// Returns true on success, false if dimensions are incompatible (c1 != r2).
bool matrix_multiply(int r1, int c1, const int *a, int r2, int c2, const int *b, int *res);

#endif // MATRIX_OPS_H
