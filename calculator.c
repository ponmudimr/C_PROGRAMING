#include <stdio.h>

int main()
{
    float a, b;
    char op;

    printf("Enter expression (e.g. 5 + 3): ");
    scanf("%f %c %f", &a, &op, &b);

    switch (op)
    {
        case '+':
            printf("%.2f + %.2f = %.2f\n", a, b, a + b);
            break;
        case '-':
            printf("%.2f - %.2f = %.2f\n", a, b, a - b);
            break;
        case '*':
            printf("%.2f * %.2f = %.2f\n", a, b, a * b);
            break;
        case '/':
            if (b == 0)
                printf("Error: division by zero\n");
            else
                printf("%.2f / %.2f = %.2f\n", a, b, a / b);
            break;
        default:
            printf("Unknown operator: %c\n", op);
    }

    return 0;
}
