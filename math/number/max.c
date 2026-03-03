#include <stdio.h>
#include <stdlib.h>

double max(double a, double b);
int min(int a, int b);

/**
 * output:
 * please input the first number :5
 * please input the second number :6
 * 5 and 6 max is 6.00
 * 5 and 6 min is 5
 */
int main()
{
    int a, b;
    printf("please input the first number :");
    scanf("%d", &a);
    printf("please input the second number :");
    scanf("%d", &b);
    printf("\n%d and %d max is %.2f", a, b, max(a, b));
    printf("\n%d and %d min is %d", a, b, min(a, b));

    getchar();
    return 0;
}

double max(double a, double b)
{
    return (a > b) ? (a) : (b);
}

int min(int a, int b)
{
    return a < b ? a : b;
}