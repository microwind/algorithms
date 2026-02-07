#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * output:
 * 90 = 2 * 3 * 3 * 5
 * ====
 * 2 * 3 * 3 * 5 = 90
 */
int main()
{
    int n = 90;
    if (n <= 3)
    {
        printf("%d", n);
    }
    int i;
    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            printf("%d", i);
            printf("%s", " * ");
            n = n / i;
            i = 1;
        }
    }
    printf("%d", n);

    ///////////////////

    printf("%s", "\r\n");
    int num = 4;
    if (num <= 3)
    {
        printf("%d", num);
    }

    int k = 2;
    while (k < num)
    {
        if (num % k == 0)
        {
            printf("%d", k);
            printf("%s", " * ");
            num = num / k;
            k = 1;
        }
        k++;
    }
    printf("%d", num);
    return 0;
}