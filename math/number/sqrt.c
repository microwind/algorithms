#include <stdio.h>
#include <math.h>

#define precision 0.00001
typedef int bool;
typedef enum
{
    false,
    true,
    FLASE,
    TRUE
} BOOL;

/**
 * 求一个数的平方根;
 */
double sqrtN(double x);
/**
 * 检查两个数是否为近似相等;
 */
bool approximateEqual(double x, double y);
/**
 * output:
 * sqrtN(2) = 1.41422
 *  sqrt(2) = 1.41421
 * sqrtN(3) = 1.73205
 *  sqrt(3) = 1.73205
 * sqrtN(4) = 2.00000
 *   sqrt(4) = 2.00000
 */
int main()
{
    double i;
    for (i = 1; i < 50; i++)
    {
        printf("\nsqrtN(%.f) = %.5f", i, sqrtN(i));
        printf("\n  sqrt(%.f) = %.5f", i, sqrt(i));
    }
    return 0;
}

double sqrtN(double x)
{
    // 牛顿连续逼近法，用一个自然数作为猜测数
    // 然后两者相除得到一个余数
    // 猜测数加上余数的平均值作为新的猜测数
    // 依此类推，直到猜测数非常接近平方根
    if (x == 0)
        return 0;

    double g;
    g = x;
    while (!approximateEqual(x, g * g))
    {
        g = (g + x / g) / 2;
    }
    return g;
}

bool approximateEqual(double x, double y)
{
    // abs(x - y) / min(x, y) < precision;
    // 两个数相减的绝对值除以小的那个数，小于设定的精度即近似相等
    int min;
    min = x > y ? y : x;
    return fabs(x - y) / (min) < precision;
}
