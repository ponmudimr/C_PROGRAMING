#include <stdio.h>
#include <assert.h>
#include "matrix_ops.h"

void test_array_stats(void) {
    int arr[] = {10, -5, 20, 15, 0, 30};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    assert(array_sum(arr, len) == 70);
    assert(array_find_max(arr, len) == 30);
    assert(array_find_min(arr, len) == -5);

    printf("  [PASS] test_array_stats\n");
}

void test_matrix_transpose(void) {
    int mat[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int transposed[3][2];

    matrix_transpose(2, 3, (const int *)mat, (int *)transposed);

    int expected[3][2] = {
        {1, 4},
        {2, 5},
        {3, 6}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            assert(transposed[i][j] == expected[i][j]);
        }
    }

    printf("  [PASS] test_matrix_transpose\n");
}

void test_is_matrix_symmetric(void) {
    int sym[3][3] = {
        {1, 7, 3},
        {7, 4, -5},
        {3, -5, 6}
    };
    assert(is_matrix_symmetric(3, (const int *)sym) == true);

    int non_sym[3][3] = {
        {1, 7, 3},
        {2, 4, -5},
        {3, -5, 6}
    };
    assert(is_matrix_symmetric(3, (const int *)non_sym) == false);

    printf("  [PASS] test_is_matrix_symmetric\n");
}

void test_matrix_multiply(void) {
    int a[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int b[3][2] = {
        {7, 8},
        {9, 1},
        {2, 3}
    };
    int res[2][2];

    bool success = matrix_multiply(2, 3, (const int *)a, 3, 2, (const int *)b, (int *)res);
    assert(success == true);

    // Expected result:
    // [1*7 + 2*9 + 3*2,  1*8 + 2*1 + 3*3] = [7 + 18 + 6,  8 + 2 + 9]  = [31, 19]
    // [4*7 + 5*9 + 6*2,  4*8 + 5*1 + 6*3] = [28 + 45 + 12, 32 + 5 + 18] = [85, 55]
    assert(res[0][0] == 31 && res[0][1] == 19);
    assert(res[1][0] == 85 && res[1][1] == 55);

    // Test dimension mismatch
    int invalid_res[2][2];
    assert(matrix_multiply(2, 3, (const int *)a, 2, 2, (const int *)b, (int *)invalid_res) == false);

    printf("  [PASS] test_matrix_multiply\n");
}

int main(void) {
    printf("--- Running Matrix & Array Operations Test Suite ---\n");
    test_array_stats();
    test_matrix_transpose();
    test_is_matrix_symmetric();
    test_matrix_multiply();
    printf("=== ALL MATRIX & ARRAY TESTS PASSED ===\n");
    return 0;
}
