/*
 * 数学基础 - 乘法运算练习 (Multiplication Practice)
 * 演示基本的乘法运算和乘法表生成
 * 时间复杂度: O(n²)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 打印乘法表（下三角部分）
 * 
 * 功能：
 * - 生成指定大小的乘法表
 * - 只打印下三角，避免重复
 * - 格式化输出
 * 
 * 参数:
 *     size: 乘法表的大小
 */
void print_multiplication_table(int size);

/**
 * 打印平方数表
 * 
 * 功能：
 * - 生成指定范围的平方数
 * - 展示平方数的规律
 * 
 * 参数:
 *     start: 起始数字
 *     end: 结束数字
 */
void print_square_numbers(int start, int end);

/**
 * 乘法运算演示程序
 * 
 * 功能：
 * - 演示乘法表的生成
 * - 展示平方数的计算
 * - 提供乘法练习
 * 
 * 输出样例：
 * 1 * 1 = 1
 * 2 * 1 = 2  2 * 2 = 4
 * 3 * 1 = 3  3 * 2 = 6  3 * 3 = 9
 * ...
 * 
 * 平方数：
 * 10 * 10 = 100
 * 11 * 11 = 121
 * 12 * 12 = 144
 * ...
 */
int main()
{
    printf("乘法运算练习\n");
    printf("==============\n\n");
    
    // 乘法表演示
    printf("乘法表（1-9）:\n");
    printf("=============\n");
    print_multiplication_table(10);
    
    // 平方数演示
    printf("\n\n重要平方数（10-16）:\n");
    printf("==================\n");
    print_square_numbers(10, 16);
    
    // 数学说明
    printf("\n\n数学规律:\n");
    printf("• 乘法交换律: a × b = b × a\n");
    printf("• 乘法结合律: (a × b) × c = a × (b × c)\n");
    printf("• 分配律: a × (b + c) = a × b + a × c\n");
    printf("• 平方数: n × n = n²\n");
    
    printf("\n重要平方数记忆:\n");
    printf("• 10² = 100\n");
    printf("• 11² = 121\n");
    printf("• 12² = 144\n");
    printf("• 13² = 169\n");
    printf("• 14² = 196\n");
    printf("• 15² = 225\n");
    printf("• 16² = 256\n");
    
    printf("\n应用场景:\n");
    printf("• 数学基础学习\n");
    printf("• 面积计算\n");
    printf("• 工程计算\n");
    printf("• 日常生活应用\n");
    
    return 0;
}

/**
 * 打印乘法表实现
 * 生成下三角乘法表，避免重复计算
 */
void print_multiplication_table(int size)
{
    for (int i = 1; i < size; i++)
    {
        printf("%2d: ", i);  // 行号
        
        for (int j = 1; j <= i; j++)
        {
            // 格式化输出乘法表达式
            printf("%d×%d=%-3d ", i, j, i * j);
        }
        printf("\n");
    }
}

/**
 * 打印平方数实现
 * 展示常用平方数的计算和结果
 */
void print_square_numbers(int start, int end)
{
    printf("数字  平方数   计算过程\n");
    printf("----  ------  ----------\n");
    
    for (int i = start; i <= end; i++)
    {
        int square = i * i;
        printf("%2d    %-4d    %d × %d = %d\n", i, square, i, i, square);
    }
}