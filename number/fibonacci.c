#include <stdio.h>
long fibonacci(int n);
void fibonacciSimple(int num);
void printFibonacci(int num);
/**
 * output:
 * F(0) =   0
 * F(1) =   1
 * F(2) =   1
 * F(3) =   2
 * F(4) =   3
 * F(5) =   5
 * F(6) =   8
 * F(7) =   13
 */
int main()
{
    int n, first, second;
    first = 0, second = 1;
    int i;
    for (i = 0; i <= 10; i++)
    {
        printf("fibonacci(%d) = %ld\n", i, fibonacci(i));
    }

    printFibonacci(10);

    fibonacciSimple(10);
    return 0;
}

/**
 * 从1开始输出，结果等于两个数的和，第一个数等于结果减去自身
 */
void fibonacciSimple(int num)
{
    long first = 1, result = 1;
    int i;
    printf("\nf[%d] = %d", 0, 0);
    printf("\nf[%d] = %ld", 1, result);
    for (i = 2; i < num + 1; i++)
    {
        printf("\nf[%d] = %ld", i, result);
        result = first + result;
        first = result - first;
    }
}

/**
 * 简单高效
 */
long fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    long first = 0;
    long second = 1;
    long result = 0;
    int i;
    for (i = 1; i < n; i++)
    {
        result = first + second;
        // 新结果是前2个数之和
        first = second;
        // 第一个数等于第二个数
        second = result;
        // 第二个数是新的结果
    }
    return result;
}

/**
 * 递归实现,效率较低
 */
int fibonacciRecursion(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    // n = n - 1 + n - 2;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/**
 * 直接输出
 */
void printFibonacci(int num)
{
    int n, i, first, second, result;
    first = 0, second = 1;
    printf("F(%d) =   %d\n", 0, 0);
    printf("F(%d) =   %d\n", 1, 1);
    for (i = 2; i <= num; i++)
    {
        result = first + second;
        printf("F(%d) =   %d\n", i, result);
        first = second;
        second = result;
    }
}
