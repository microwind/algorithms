/*
 * 数学算法 - 最大公约数计算 (Greatest Common Divisor)
 * 实现多种GCD算法：欧几里得算法和暴力枚举法
 * 欧几里得算法时间复杂度：O(log min(a,b))
 * 暴力枚举法时间复杂度：O(min(a,b))
 */

#include <stdio.h>
#include <stdbool.h>

// 布尔类型定义（兼容性考虑）
#define true 1
#define false 0

/**
 * 欧几里得算法（辗转相除法）
 * 
 * 算法原理：
 * 1. gcd(a,b) = gcd(b,a mod b)
 * 2. 当 b = 0 时，a 就是最大公约数
 * 3. 基于量木棍理论：用较短的木棍去量较长的木棍
 * 
 * 参数:
 *     x: 第一个正整数
 *     y: 第二个正整数
 * 返回:
 *     x和y的最大公约数
 * 
 * 时间复杂度: O(log min(x,y)) - 非常高效
 * 空间复杂度: O(1)
 */
int gcdx(int x, int y);

/**
 * 暴力枚举法（Brute Force）
 * 
 * 算法原理：
 * 1. 从min(x,y)开始向下递减
 * 2. 找到第一个能同时整除x和y的数
 * 
 * 参数:
 *     x: 第一个正整数
 *     y: 第二个正整数
 * 返回:
 *     x和y的最大公约数
 * 
 * 时间复杂度: O(min(x,y)) - 效率较低
 * 空间复杂度: O(1)
 */
int gcd(int x, int y);

/**
 * 打印两个数的所有公约数
 * 
 * 功能：
 * - 遍历1到max(x,y)的所有整数
 * - 找出所有能同时整除x和y的数
 * - 按顺序打印所有公约数
 * 
 * 参数:
 *     x: 第一个正整数
 *     y: 第二个正整数
 */
void printGCD(int x, int y);

/**
 * 最大公约数算法演示和比较
 * 
 * 功能：
 * - 测试1-10与10的最大公约数
 * - 比较欧几里得算法和暴力枚举法的结果
 * - 显示所有公约数
 * 
 * 输出样例：
 * [x=1, y=10 gcd=1]
 *     max : gcdx=1, gcd=1
 * [x=2, y=10 gcd=1]
 * [x=2, y=10 gcd=2]
 *     max : gcdx=2, gcd=2
 * 
 * 算法对比：
 * - 欧几里得算法：高效，基于数学原理
 * - 暴力枚举法：简单直观，但效率低
 */
int main()
{
    int x, y, i;
    y = 10;  // 固定第二个数为10
    
    printf("最大公约数算法比较 (1-10 vs 10)\n");
    printf("================================\n");
    
    for (i = 1; i <= 10; i++)
    {
        x = i;
        printf("\n测试 %d 和 %d:\n", x, y);
        
        // 打印所有公约数
        printGCD(x, y);
        
        // 比较两种算法的结果
        int result_euclid = gcdx(x, y);
        int result_brute = gcd(x, y);
        
        printf("\n    最大公约数: gcdx=%d, gcd=%d", result_euclid, result_brute);
        
        // 验证结果一致性
        if (result_euclid == result_brute) {
            printf(" ");
        } else {
            printf(" 算法结果不一致！");
        }
    }
    
    printf("\n\n算法复杂度对比:\n");
    printf("• 欧几里得算法: O(log n) - 推荐使用\n");
    printf("• 暴力枚举法: O(n) - 仅适用于小数字\n");
    
    return 0;
}

/**
 * 欧几里得算法实现
 * 使用循环而非递归，避免栈溢出
 */
int gcdx(int x, int y)
{
    int remainder;
    
    // 确保x >= y，如果不是则交换
    if (x < y) {
        int temp = x;
        x = y;
        y = temp;
    }
    
    while (true)
    {
        remainder = x % y;  // 计算余数
        
        // 余数为0时，y就是最大公约数
        if (remainder == 0) {
            break;
        }
        
        // 更新x和y，继续下一轮
        x = y;      // x = 原来的除数
        y = remainder;  // y = 余数
    }
    
    return y;
}

/**
 * 暴力枚举法实现
 * 从较小的数开始向下递减查找
 */
int gcd(int x, int y)
{
    int gcd_candidate;
    
    // 从较小的数开始
    gcd_candidate = x < y ? x : y;
    
    // 递减查找第一个能同时整除两个数的数
    while (x % gcd_candidate != 0 || y % gcd_candidate != 0)
    {
        gcd_candidate--;
        
        // 如果递减到1，直接返回1（1是所有整数的公约数）
        if (gcd_candidate == 1) {
            break;
        }
    }
    
    return gcd_candidate;
}

/**
 * 打印所有公约数
 * 遍历检查1到max(x,y)的所有整数
 */
void printGCD(int x, int y)
{
    int divisor = 1;
    int max_val = x > y ? x : y;
    
    printf("  所有公约数: ");
    int found_any = false;
    
    while (divisor <= max_val)
    {
        if (x % divisor == 0 && y % divisor == 0)
        {
            printf("%d ", divisor);
            found_any = true;
        }
        divisor++;
    }
    
    if (!found_any) {
        printf("无");
    }
}