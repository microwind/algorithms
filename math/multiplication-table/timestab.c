/*
 * 数学基础 - 九九乘法表 (Multiplication Table)
 * 生成标准格式的九九乘法表
 * 时间复杂度: O(n²)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 打印九九乘法表
 * 
 * 算法原理：
 * 1. 使用双重循环，外层控制行数，内层控制列数
 * 2. 只打印下三角部分（j <= i），避免重复
 * 3. 格式化输出，保持对齐
 * 
 * 输出格式：
 * 1×1= 1
 * 1×2= 2   2×2= 4
 * 1×3= 3   2×3= 6   3×3= 9
 * ...
 * 
 * 时间复杂度: O(n²) - n×n次循环
 * 空间复杂度: O(1) - 常数空间
 */
void print_multiplication_table(int max);

/**
 * 九九乘法表演示程序
 * 
 * 功能：
 * - 生成标准九九乘法表
 * - 可自定义大小
 * - 格式化输出
 * 
 * 输出样例：
 * 1×1= 1
 * 1×2= 2   2×2= 4
 * 1×3= 3   2×3= 6   3×3= 9
 * 1×4= 4   2×4= 8   3×4=12   4×4=16
 * ...
 */
int main()
{
    printf("九九乘法表\n");
    printf("==========\n\n");
    
    int max_size = 9;  // 标准九九乘法表
    int min_size = 1;
    
    printf("标准九九乘法表 (%d×%d):\n", max_size, max_size);
    printf("------------------------\n");
    
    // 生成乘法表
    for (int i = min_size; i <= max_size; i++)
    {
        for (int j = min_size; j <= i; j++)
        {
            // 格式化输出：j×i=结果，保持对齐
            printf("%d×%d=%2d   ", j, i, i * j);
        }
        printf("\n");
    }
    
    printf("\n算法说明:\n");
    printf("• 使用双重循环生成乘法表\n");
    printf("• 只打印下三角，避免重复计算\n");
    printf("• 时间复杂度: O(n²)\n");
    printf("• 空间复杂度: O(1)\n");
    
    printf("\n数学规律:\n");
    printf("• 对角线上的数都是完全平方数\n");
    printf("• 每行都是等差数列\n");
    printf("• 乘法交换律：i×j = j×i\n");
    
    printf("\n应用场景:\n");
    printf("• 数学教育基础\n");
    printf("• 算法练习（循环嵌套）\n");
    printf("• 格式化输出练习\n");
    printf("• 数学规律探索\n");
    
    // 等待用户按键（在某些系统中需要）
    getchar();
    return 0;
}

/**
 * 打印自定义大小的乘法表
 * 
 * 参数:
 *     max: 乘法表的最大值
 */
void print_multiplication_table(int max)
{
    printf("自定义乘法表 (%d×%d):\n", max, max);
    printf("------------------------\n");
    
    for (int i = 1; i <= max; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d×%d=%2d   ", j, i, i * j);
        }
        printf("\n");
    }
}
