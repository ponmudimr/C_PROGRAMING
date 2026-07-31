#include <stdio.h>

int main()
{
    float a, b;
    char op;

    printf("Simple Calculator (type q to quit)\n");

    while (1)
    {
        printf("Enter expression (e.g. 5 + 3): ");
        if (scanf("%f %c %f", &a, &op, &b) != 3)
        {
            int c = getchar();
            if (c == 'q' || c == 'Q' || c == EOF)
            {
                printf("Bye!\n");
                break;
            }
            printf("Invalid input\n");
            while (c != '\n' && c != EOF)
                c = getchar();
            continue;
        }

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
            case '%':
                if ((int)b == 0)
                    printf("Error: modulus by zero\n");
                else
                    printf("%d %% %d = %d\n", (int)a, (int)b, (int)a % (int)b);
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
    }

    return 0;
}
