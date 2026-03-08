/*
 * 数学基础 - 最大值和最小值计算 (Max and Min Functions)
 * 演示基本比较运算和函数重载概念（C语言中通过不同函数名实现）
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 求两个浮点数的最大值
 * 
 * 参数:
 *     a: 第一个浮点数
 *     b: 第二个浮点数
 * 返回:
 *     两个数中的较大值
 */
double max(double a, double b);

/**
 * 求两个整数的最小值
 * 
 * 参数:
 *     a: 第一个整数
 *     b: 第二个整数
 * 返回:
 *     两个数中的较小值
 */
int min(int a, int b);

/**
 * 最大值和最小值计算演示
 * 
 * 功能：
 * - 获取用户输入的两个整数
 * - 计算并显示它们的最大值（转换为浮点数）
 * - 计算并显示它们的最小值
 * 
 * 输入样例：
 * please input the first number :5
 * please input the second number :6
 * 
 * 输出样例：
 * 5 and 6 max is 6.00
 * 5 and 6 min is 5
 * 
 * 注意事项：
 * - C语言不支持函数重载，需要用不同函数名处理不同类型
 * - 类型转换：整数自动提升为浮点数
 * - 输入验证的重要性
 */
int main()
{
    int a, b;
    
    // 获取第一个整数
    printf("please input the first number :");
    if (scanf("%d", &a) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;
    }
    
    // 获取第二个整数
    printf("please input the second number :");
    if (scanf("%d", &b) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;
    }
    
    // 计算并显示最大值（整数自动转换为浮点数）
    printf("\n%d and %d max is %.2f", a, b, max((double)a, (double)b));
    
    // 计算并显示最小值
    printf("\n%d and %d min is %d", a, b, min(a, b));
    
    // 等待用户按键（在某些系统中需要）
    getchar();
    return 0;
}

/**
 * 求两个浮点数的最大值
 * 使用三元运算符实现简洁的条件判断
 */
double max(double a, double b)
{
    return (a > b) ? a : b;  // 如果a大于b，返回a；否则返回b
}

/**
 * 求两个整数的最小值
 * 使用三元运算符实现简洁的条件判断
 */
int min(int a, int b)
{
    return (a < b) ? a : b;  // 如果a小于b，返回a；否则返回b
}