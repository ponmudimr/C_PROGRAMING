#include <stdio.h>

int main() {
    int rows;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    // Pattern 1: Right-angled triangle of stars
    printf("\nRight-angled triangle:\n");
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    // Pattern 2: Pyramid (centered triangle)
    printf("\nPyramid:\n");
    for (int i = 1; i <= rows; i++) {
        for (int s = 1; s <= rows - i; s++) {
            printf(" ");
        }
        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    // Pattern 3: Inverted pyramid (centered, upside down)
    printf("\nInverted pyramid:\n");
    for (int i = rows; i >= 1; i--) {
        for (int s = 1; s <= rows - i; s++) {
            printf(" ");
        }
        for (int j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }

    // Pattern 4: Inverted triangle
    printf("\nInverted triangle:\n");
    for (int i = rows; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }

    return 0;
}
