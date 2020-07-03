#include <stdio.h>
#include <math.h>

#define precision 0.00001
typedef int bool;

/**
 * 检查两个数是否为近似相等;
 */
bool approximateEqual(double x, double y);
/**
 * output:
 * 1.1110102000 and 1.1110001000 is not approximate
 */
int main()
{
    double x, y;
    x = 1.1110102;
    y = 1.1110001;
    if (approximateEqual(x, y))
    {
        printf("%.10f and %.10f is approximate", x, y);
    }
    else
    {
        printf("%.10f and %.10f is not approximate", x, y);
    }

    printf("\r\n");
    x = 2.3330102;
    y = 2.3330101;
    if (approximateEqual(x, y))
    {
        printf("%.10f and %.10f is approximate", x, y);
    }
    else
    {
        printf("%.10f and %.10f is not approximate", x, y);
    }
    return 0;
}

bool approximateEqual(double x, double y)
{
    // abs(x - y) / min(x, y) < precision;
    // 两个数相减绝对值除以小的那个数，小于设定的精度即近似相等
    int min;
    min = x > y ? y : x;
    return fabs(x - y) / (min) < precision;
}