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

int main(void) {
    init_random();
    printf("=== Random Generator Toolkit (v1.0) ===\n\n");
    
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

    return 0;
}
