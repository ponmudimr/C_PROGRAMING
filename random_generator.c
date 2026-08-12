#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int main(void) {
    init_random();
    printf("=== Random Generator Toolkit (v1.1) ===\n\n");
    
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

    return 0;
}

