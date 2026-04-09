/*
 * 数学基础 - 绝对值计算 (Absolute Value)
 * 计算整数的绝对值
 * 时间复杂度: O(1)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 计算整数的绝对值
 * 
 * 算法原理：
 * - 正数：绝对值就是其本身
 * - 负数：绝对值是其相反数
 * - 零：绝对值是零
 * 
 * 参数:
 *     n: 要求绝对值的整数
 * 返回:
 *     n的绝对值
 * 
 * 时间复杂度: O(1) - 常数时间
 * 空间复杂度: O(1) - 常数空间
 */
int absolute_value(int n);

/**
 * 绝对值计算演示程序
 * 
 * 功能：
 * - 获取用户输入的整数
 * - 计算并显示其绝对值
 * - 演示正数、负数、零的处理
 * 
 * 输入样例：
 * please input one number to get absolute value: -42
 * 
 * 输出样例：
 * your input is -42, it's absolute value = 42
 */
int main()
{
    int number;
    
    printf("绝对值计算演示\n");
    printf("================\n\n");
    printf("请输入一个整数（可以是正数、负数或零）: ");
    
    // 读取用户输入
    if (scanf("%d", &number) != 1) {
        printf("输入错误：请输入有效的整数\n");
        return 1;
    }
    
    // 计算绝对值
    int abs_value = absolute_value(number);
    
    // 显示结果
    printf("输入数字: %d\n", number);
    printf("绝对值: %d\n", abs_value);
    
    // 显示计算原理
    printf("\n计算原理:\n");
    if (number > 0) {
        printf("• %d 是正数，绝对值就是其本身: |%d| = %d\n", 
               number, number, number);
    } else if (number < 0) {
        printf("• %d 是负数，绝对值是其相反数: |%d| = -%d = %d\n", 
               number, number, number, abs_value);
    } else {
        printf("• 0 的绝对值是 0: |0| = 0\n");
    }
    
    printf("\n数学性质:\n");
    printf("• 非负性: |x| ≥ 0\n");
    printf("• 正定性: |x| = 0 当且仅当 x = 0\n");
    printf("• 三角不等式: |x + y| ≤ |x| + |y|\n");
    
    printf("\n应用场景:\n");
    printf("• 距离计算\n");
    printf("• 误差分析\n");
    printf("• 数值比较\n");
    printf("• 物理量计算\n");
    
    // 等待用户按键（在某些系统中需要）
    getchar(); // 清除输入缓冲区
    getchar(); // 等待按键
    return 0;
}

/**
 * 绝对值计算实现
 * 使用简单的条件判断实现
 */
int absolute_value(int n)
{
    if (n > 0)
    {
        return n;      // 正数：直接返回
    }
    else
    {
        return -n;     // 负数或零：返回相反数
    }
}