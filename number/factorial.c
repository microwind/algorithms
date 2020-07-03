#include <stdio.h>
#include <stdlib.h>
/**
 * output: 
 * factorial(0) = 1
 * factorial(1) = 1 = 1
 * factorial(2) = 2 = 1 * 2
 * factorial(3) = 6 = 1* 2 * 3
 * factorial(4) = 24 = 1* 2 * 3 * 4
 * factorial(5) = 120 = 1* 2 * 3 * 4 * 5
 */
int factorial(int n);
int printFactorial(int n);

int main()
{
    int i, j;
    int max, product;
    max = 10;
    for (i = 0; i <= max; i++)
    {
        product = 1;

        for (j = 1; j <= i; j++)
        {
            product *= j;
        }
        printf("factorial(%d) = %3d \n", i, product);
    }

    printf("\n====");

    for (i = 0; i <= max; i++)
    {
        printf("\n factorial(%d) = %3d = ", i, factorial(i));
        printFactorial(i);
    }

    getchar();
    return 0;
}

int printFactorial(int n)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        printf("%d", i);
        if (i < n)
            printf(" * ");
    }
    return 0;
}

int factorial(int n)
{
    int product, i;
    product = 1;

    for (i = 1; i <= n; i++)
    {
        product *= i;
    }
    return product;
}
