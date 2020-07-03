#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef int bool;
typedef enum
{
    false,
    true,
    FLASE,
    TRUE
} BOOL;
/**
 * 是否是完全数，即真约数(能被整除且小于自身的数)的和等于本身。
 * return {true : flase}
 */
bool isPerfect(int n);

/**
 * output:
 * 6 is perfect.
 * 28 is perfect.
 * 496 is perfect.
 * 8128 is perfect.
 */
int main()
{
    int i, num = 10000;
    for (i = 1; i < num; i++)
    {
        if (isPerfect(i))
        {
            printf("%d is perfect.\n", i);
        }
        else
        {
            //printf("%d is no perfect.\n", i);
        }
    }
    return 0;
}

bool isPerfect(int n)
{
    int i, sum = 0;
    for (i = 1; i < n; i++)
    {
        if (n % i == 0)
            sum += i;
    }

    return (sum == n);
}
