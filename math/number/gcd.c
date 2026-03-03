#include <stdio.h>
typedef enum
{
    false,
    true,
    FLASE,
    TRUE
} BOOL;
/**
 * 欧几里德算法，根据量木棍理论，效率很高
 */
int gcdx(int x, int y);

/**
 * brute-force 普通循环法
 */
int gcd(int x, int y);

/**
 * 打印两个数的全部公约数
 */
void printGCD(int x, int y);

/**
 * 计算两个数之间的最大公约数，即能同时被2个数整除的自然整数
 * output:
 * [x=1, y=10 gcd=1]
 *    max : gcdx=1, gcd=1
 * [x=2, y=10 gcd=1]
 * [x=2, y=10 gcd=2]
 *    max : gcdx=2, gcd=2
 */
int main()
{
    int x, y, i;
    x = 1, y = 10;
    for (i = 1; i <= 10; i++)
    {
        x = i;
        printGCD(x, y);
        printf("\n    max : gcdx=%d, gcd=%d", gcdx(x, y), gcd(x, y));
    }
    return 0;
}

int gcdx(int x, int y)
{
    int r;
    while (TRUE)
    {
        r = x % y; // 设r为两者相除的余数
        if (r == 0)
            break; // 余数为0表示被整除了，r就是最大公约数
        x = y;     // x = 被除数，
        y = r;     // y = 余数，继续下一轮，能被两个数整除的最小数1
    }
    return y;
}

int gcd(int x, int y)
{
    int g;
    g = x < y ? x : y;
    // x和y如果不能整除就递减，直到1为止
    while (x % g != 0 || y % g != 0)
    {
        g--;
    }
    return g;
}

void printGCD(int x, int y)
{
    int g = 1, max;
    max = x > y ? x : y;
    while (g <= max)
    {
        if (x % g == 0 && y % g == 0)
        {
            printf("\n[x=%d, y=%d gcd=%d]", x, y, g);
        }
        g++;
    }
}