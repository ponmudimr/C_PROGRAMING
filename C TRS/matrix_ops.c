#include "matrix_ops.h"
#include <limits.h>

int array_sum(const int *arr, size_t size) {
    if (!arr || size == 0) return 0;
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int array_find_max(const int *arr, size_t size) {
    if (!arr || size == 0) return INT_MIN;
    int max_val = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int array_find_min(const int *arr, size_t size) {
    if (!arr || size == 0) return INT_MAX;
    int min_val = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

void matrix_transpose(int rows, int cols, const int *src, int *dst) {
    if (!src || !dst || rows <= 0 || cols <= 0) return;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            dst[c * rows + r] = src[r * cols + c];
        }
    }
}

bool is_matrix_symmetric(int n, const int *mat) {
    if (!mat || n <= 0) return false;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (mat[r * n + c] != mat[c * n + r]) {
                return false;
            }
        }
    }
    return true;
}

bool matrix_multiply(int r1, int c1, const int *a, int r2, int c2, const int *b, int *res) {
    if (!a || !b || !res || c1 != r2 || r1 <= 0 || c1 <= 0 || c2 <= 0) {
        return false;
    }

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            int sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += a[i * c1 + k] * b[k * c2 + j];
            }
            res[i * c2 + j] = sum;
        }
    }
    return true;
}
