#include <stdio.h>
#include <stdlib.h>

int isEven(int n);

/**
 * output:
 * 1 is not even
 * 2 is even
 * 3 is not even 
 */
int main()
{
    int n;
    printf("please input the number :");
    scanf("%d", &n);

    if (isEven(n))
    {
        printf("\n%d is even", n);
    }
    else
    {
        printf("\n%d is not even ", n);
    }

    int i;
    for (i = 1; i <= 10; i++)
    {
        if (isEven(i))
        {
            printf("\n%d is even", i);
        }
        else
        {
            printf("\n%d is not even ", i);
        }
    }
    return 0;
}

int isEven(int n)
{
    return (n % 2 == 0);
}