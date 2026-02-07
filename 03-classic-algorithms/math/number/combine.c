#include <stdio.h>
#include <stdlib.h>
/**
 * 递阶相乘，返回乘积
 */
int factorial(int n);
/**
 * 组合函数
 * 几种可能
 */
int combine(int n, int k);
/**
 * output:
 * (5 , 1) , (1 , 120) combine 5
 * (5 , 2) , (2 , 120) combine 10
 * (5 , 3) , (6 , 120) combine 10
 * (5 , 4) , (24 , 120) combine 5
 * (5 , 5) , (120 , 120) combine 1
 */
int main()
{
    int n, k, i;
    n = 5;
    for (i = 1; i <= n; i++)
    {
        k = i;
        printf("\n(%d , %d) , (%d , %d) combine %d", n, k, factorial(k), factorial(n), combine(n, k));
    }
    return 0;
}

int combine(int n, int k)
{
    //m = n! / k! * (n - k)!
    // 组合公式
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int factorial(int n)
{
    int i, product;
    product = 1;
    for (i = 1; i <= n; i++)
    {
        product *= i;
    }
    return product;
}
