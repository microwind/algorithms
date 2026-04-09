/*
 * 数学基础 - 阶乘计算 (Factorial)
 * 计算非负整数的阶乘 n!
 * 支持普通递归、尾递归和迭代实现
 * 时间复杂度: O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 普通递归计算阶乘
 * 
 * 算法原理：
 * - n! = n × (n-1) × (n-2) × ... × 2 × 1
 * - 递归定义: n! = n × (n-1)!
 * - 基准条件: 0! = 1, 1! = 1
 * 
 * 参数:
 *     n: 非负整数
 * 返回:
 *     n! 的结果
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(n) - 递归栈深度
 * 
 * 限制:
 *     n ≤ 20 (64位整数溢出)
 */
unsigned long long factorial_recursive(int n);

/**
 * 迭代计算阶乘
 * 
 * 算法原理：
 * - 使用循环累乘
 * - 从1乘到n
 * 
 * 参数:
 *     n: 非负整数
 * 返回:
 *     n! 的结果
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1) - 常数空间
 */
unsigned long long factorial_iterative(int n);

/**
 * 尾递归优化计算阶乘
 * 
 * 算法原理：
 * - 将累积器作为参数传递
 * - 编译器可优化为循环
 * 
 * 参数:
 *     n: 剩余乘数
 *     accumulator: 累积结果
 * 返回:
 *     n! 的结果
 */
unsigned long long factorial_tail_recursive(int n, unsigned long long accumulator);

/**
 * 主函数 - 阶乘演示程序
 * 
 * 功能：
 * - 演示递归和迭代两种方法
 * - 显示阶乘表
 * - 展示大数阶乘
 */
int main()
{
    int n;
    
    printf("========================================\n");
    printf("    阶乘计算演示 (Factorial n!)\n");
    printf("========================================\n\n");
    
    // 显示阶乘表
    printf("阶乘表 (0! 到 20!):\n");
    printf("----------------------------------------\n");
    printf(" n | 递归结果 | 迭代结果 | 尾递归结果\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i <= 20; i++) {
        unsigned long long result_rec = factorial_recursive(i);
        unsigned long long result_iter = factorial_iterative(i);
        unsigned long long result_tail = factorial_tail_recursive(i, 1);
        
        printf("%2d | %12llu | %12llu | %12llu\n", 
               i, result_rec, result_iter, result_tail);
    }
    
    printf("----------------------------------------\n\n");
    
    // 用户输入
    printf("请输入一个非负整数 (0-20): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 20) {
        printf("错误：请输入0到20之间的整数\n");
        return 1;
    }
    
    // 计算并显示结果
    unsigned long long result = factorial_iterative(n);
    
    printf("\n%d! = ", n);
    
    // 显示展开式
    for (int i = n; i >= 1; i--) {
        printf("%d", i);
        if (i > 1) printf(" × ");
    }
    printf(" = %llu\n", result);
    
    // 数学性质
    printf("\n========================================\n");
    printf("阶乘的数学性质:\n");
    printf("========================================\n");
    printf("• 定义: n! = n × (n-1) × (n-2) × ... × 2 × 1\n");
    printf("• 特例: 0! = 1 (空积的定义)\n");
    printf("• 递推: n! = n × (n-1)!\n");
    printf("• 增长: 阶乘增长快于指数增长\n");
    printf("• 斯特林公式近似: n! ≈ √(2πn) × (n/e)^n\n");
    
    // 应用场景
    printf("\n========================================\n");
    printf("应用场景:\n");
    printf("========================================\n");
    printf("• 排列组合: n个元素的全排列数 = n!\n");
    printf("• 二项式系数: C(n,k) = n! / (k!(n-k)!)\n");
    printf("• 概率论: 生日问题、洗牌算法\n");
    printf("• 泰勒展开: e^x = Σ x^n/n!\n");
    printf("• 数论: 威尔逊定理 (p-1)! ≡ -1 (mod p)\n");
    
    return 0;
}

/**
 * 普通递归实现
 */
unsigned long long factorial_recursive(int n)
{
    // 基准条件
    if (n <= 1) {
        return 1;  // 0! = 1, 1! = 1
    }
    
    // 递归步骤: n! = n × (n-1)!
    return (unsigned long long)n * factorial_recursive(n - 1);
}

/**
 * 迭代实现
 */
unsigned long long factorial_iterative(int n)
{
    unsigned long long result = 1;
    
    // 循环累乘: 1 × 2 × 3 × ... × n
    for (int i = 1; i <= n; i++) {
        result *= (unsigned long long)i;
    }
    
    return result;
}

/**
 * 尾递归实现
 */
unsigned long long factorial_tail_recursive(int n, unsigned long long accumulator)
{
    // 基准条件
    if (n <= 1) {
        return accumulator;
    }
    
    // 尾递归: 累积器保存中间结果
    return factorial_tail_recursive(n - 1, accumulator * (unsigned long long)n);
}
