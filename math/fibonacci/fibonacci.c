/*
 * 数学算法 - 斐波那契数列 (Fibonacci Sequence)
 * 实现多种斐波那契数列计算方法
 * 迭代法时间复杂度: O(n)，递归法时间复杂度: O(2^n)
 */

#include <stdio.h>
#include <limits.h>

/**
 * 迭代法计算斐波那契数列
 * 
 * 算法原理：
 * F(0) = 0, F(1) = 1
 * F(n) = F(n-1) + F(n-2) for n >= 2
 * 
 * 参数:
 *     n: 要计算的项数
 * 返回:
 *     第n项的斐波那契数
 * 
 * 时间复杂度: O(n) - 线性时间
 * 空间复杂度: O(1) - 常数空间
 */
long fibonacci(int n);

/**
 * 简化版斐波那契数列输出
 * 
 * 参数:
 *     num: 要输出的项数
 */
void fibonacciSimple(int num);

/**
 * 格式化输出斐波那契数列
 * 
 * 参数:
 *     num: 要输出的项数
 */
void printFibonacci(int num);

/**
 * 递归法计算斐波那契数列
 * 
 * 注意：效率较低，仅用于演示递归原理
 * 
 * 参数:
 *     n: 要计算的项数
 * 返回:
 *     第n项的斐波那契数
 * 
 * 时间复杂度: O(2^n) - 指数时间
 * 空间复杂度: O(n) - 递归栈深度
 */
int fibonacciRecursion(int n);

/**
 * 斐波那契数列演示程序
 * 
 * 功能：
 * - 演示多种斐波那契数列计算方法
 * - 比较不同方法的效率
 * - 输出前10项的数列
 * 
 * 输出样例：
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
    printf("斐波那契数列演示\n");
    printf("================\n\n");
    
    printf("方法1：迭代法计算\n");
    printf("F(n) = F(n-1) + F(n-2)\n\n");
    
    // 使用迭代法计算前10项
    int i;
    for (i = 0; i <= 10; i++)
    {
        printf("fibonacci(%d) = %ld\n", i, fibonacci(i));
    }

    printf("\n方法2：格式化输出\n");
    printFibonacci(10);

    printf("\n方法3：简化版输出\n");
    fibonacciSimple(10);
    
    // 性能对比
    printf("\n\n性能对比:\n");
    printf("• 迭代法: O(n) 时间，推荐使用\n");
    printf("• 递归法: O(2^n) 时间，仅适用于小n\n");
    printf("• 动态规划: O(n) 时间，O(n) 空间\n");
    printf("• 矩阵快速幂: O(log n) 时间，适用于大n\n");
    
    // 溢出警告
    printf("\n注意事项:\n");
    printf("• long类型在%d位系统上最大值: %ld\n", 
           (int)(sizeof(long) * 8), LONG_MAX);
    printf("• F(47) = %ld (接近溢出)\n", fibonacci(47));
    printf("• 大数计算需要使用大整数库\n");
    
    return 0;
}

/**
 * 简化版斐波那契数列输出
 * 从1开始输出，使用两个变量交替更新
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
        
        // 更新变量：新结果是前两个数之和
        long temp = result;
        result = first + result;
        first = temp;  // first更新为旧的result
    }
}

/**
 * 迭代法计算斐波那契数列（推荐方法）
 * 使用三个变量循环计算，效率高且空间复杂度低
 */
long fibonacci(int n)
{
    // 边界条件
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    long first = 0;      // F(n-2)
    long second = 1;     // F(n-1)
    long result = 0;     // F(n)
    int i;
    
    // 迭代计算
    for (i = 1; i < n; i++)
    {
        result = first + second;  // F(n) = F(n-2) + F(n-1)
        
        // 更新变量：向前移动
        first = second;      // F(n-2) = F(n-1)
        second = result;     // F(n-1) = F(n)
    }
    
    return result;
}

/**
 * 递归法计算斐波那契数列
 * 直接递归实现，效率较低但便于理解递归原理
 */
int fibonacciRecursion(int n)
{
    // 递归基准条件
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    // 递归关系：F(n) = F(n-1) + F(n-2)
    return fibonacciRecursion(n - 1) + fibonacciRecursion(n - 2);
}

/**
 * 格式化输出斐波那契数列
 * 直接输出每一项，便于查看数列规律
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
