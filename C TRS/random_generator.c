#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "random_generator.h"

void init_random(void) {
    srand((unsigned int)time(NULL));
}

int get_random_int(int min, int max) {
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }
    return min + rand() % (max - min + 1);
}

double get_random_double(double min, double max) {
    if (min > max) {
        double temp = min;
        min = max;
        max = temp;
    }
    double scale = (double)rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

int roll_dice(int count, int sides) {
    if (count <= 0 || sides <= 0) return 0;
    int total = 0;
    printf("Rolling %d d%d dice: [ ", count, sides);
    for (int i = 0; i < count; i++) {
        int roll = get_random_int(1, sides);
        printf("%d ", roll);
        total += roll;
    }
    printf("] => Total: %d\n", total);
    return total;
}

void generate_random_password(char *buffer, size_t length, int include_symbols) {
    if (!buffer || length == 0) return;
    static const char alpha_num[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    static const char symbols[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    size_t alpha_len = sizeof(alpha_num) - 1;
    size_t sym_len = sizeof(symbols) - 1;

    for (size_t i = 0; i < length - 1; i++) {
        if (include_symbols && get_random_int(0, 3) == 0) {
            buffer[i] = symbols[get_random_int(0, (int)sym_len - 1)];
        } else {
            buffer[i] = alpha_num[get_random_int(0, (int)alpha_len - 1)];
        }
    }
    buffer[length - 1] = '\0';
}

void generate_hex_token(char *buffer, size_t length) {
    if (!buffer || length == 0) return;
    static const char hex_chars[] = "0123456789abcdef";
    for (size_t i = 0; i < length - 1; i++) {
        buffer[i] = hex_chars[get_random_int(0, 15)];
    }
    buffer[length - 1] = '\0';
}

void shuffle_array(int *arr, size_t size) {
    if (!arr || size <= 1) return;
    for (size_t i = size - 1; i > 0; i--) {
        size_t j = (size_t)get_random_int(0, (int)i);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void fill_random_matrix(int rows, int cols, int *matrix, int min, int max) {
    if (!matrix || rows <= 0 || cols <= 0) return;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = get_random_int(min, max);
        }
    }
}

void print_matrix(int rows, int cols, const int *matrix) {
    if (!matrix || rows <= 0 || cols <= 0) return;
    for (int i = 0; i < rows; i++) {
        printf("  [ ");
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i * cols + j]);
        }
        printf("]\n");
    }
}

void simulate_guessing_game(int min, int max) {
    int target = get_random_int(min, max);
    printf("Simulating Number Guessing Game (Target between %d and %d)...\n", min, max);
    
    int low = min, high = max;
    int attempts = 0;
    int guess;

    do {
        attempts++;
        guess = (low + high) / 2;
        printf("  Attempt %d: Guessed %d -> ", attempts, guess);
        if (guess < target) {
            printf("Too Low!\n");
            low = guess + 1;
        } else if (guess > target) {
            printf("Too High!\n");
            high = guess - 1;
        } else {
            printf("CORRECT! Target %d found in %d attempts.\n", target, attempts);
        }
    } while (guess != target && low <= high);
}

void compute_random_stats(int sample_size, int min, int max) {
    if (sample_size <= 0) return;
    printf("Computing statistics for %d random numbers in [%d, %d]...\n", sample_size, min, max);
    
    long long sum = 0;
    int min_val = max;
    int max_val = min;
    
    int *samples = malloc(sizeof(int) * sample_size);
    if (!samples) return;

    for (int i = 0; i < sample_size; i++) {
        int val = get_random_int(min, max);
        samples[i] = val;
        sum += val;
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }

    double mean = (double)sum / sample_size;
    double var_sum = 0.0;
    for (int i = 0; i < sample_size; i++) {
        double diff = samples[i] - mean;
        var_sum += diff * diff;
    }
    double variance = var_sum / sample_size;
    double stddev = sqrt(variance);
    double expected_mean = (min + max) / 2.0;

    printf("  Min: %d, Max: %d\n", min_val, max_val);
    printf("  Sample Mean: %.2f (Expected: %.2f)\n", mean, expected_mean);
    printf("  Variance: %.2f, StdDev: %.2f\n", variance, stddev);

    free(samples);
}

int main(void) {
    init_random();
    printf("=== Random Generator Toolkit (v1.3) ===\n\n");
    
    printf("--- Random Integers ---\n");
    for (int i = 0; i < 5; i++) {
        printf("Random int [10, 50]: %d\n", get_random_int(10, 50));
    }
    
    printf("\n--- Random Doubles ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Random double [0.0, 1.0]: %.4f\n", get_random_double(0.0, 1.0));
    }
    
    printf("\n--- Dice Roller ---\n");
    roll_dice(3, 6);
    roll_dice(2, 20);

    printf("\n--- Random Password & Token Generator ---\n");
    char pass[17];
    generate_random_password(pass, sizeof(pass), 1);
    printf("Generated Password (16 chars, with symbols): %s\n", pass);
    
    char token[33];
    generate_hex_token(token, sizeof(token));
    printf("Generated Hex Token (32 chars): %s\n", token);

    printf("\n--- Fisher-Yates Array Shuffle ---\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    for (size_t i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    printf("\n");
    shuffle_array(arr, arr_size);
    printf("Shuffled array: ");
    for (size_t i = 0; i < arr_size; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("\n--- Random Matrix Generation (3x4) ---\n");
    int mat[3][4];
    fill_random_matrix(3, 4, (int *)mat, 1, 99);
    print_matrix(3, 4, (const int *)mat);

    printf("\n--- Automated Number Guessing Game ---\n");
    simulate_guessing_game(1, 100);

    printf("\n--- Statistical Distribution Analysis ---\n");
    compute_random_stats(10000, 1, 100);

    return 0;
}



