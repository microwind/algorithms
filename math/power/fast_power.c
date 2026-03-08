/*
 * 数学算法 - 快速幂 (Fast Power / Binary Exponentiation)
 * 使用二分法高效计算大数幂，时间复杂度 O(log n)
 */

#include <stdio.h>
#include <stdlib.h>

// 常用模数（素数，用于模运算）
#define MOD 1000000007

/**
 * 快速幂算法（迭代实现）
 * 
 * 算法原理：
 * 1. 将指数表示为二进制形式
 * 2. 根据二进制位决定是否乘以当前底数
 * 3. 每次循环底数平方，指数右移一位
 * 
 * 参数:
 *     base: 底数
 *     exponent: 指数
 *     mod: 模数，0表示不取模
 * 返回:
 *     base^exponent % mod
 * 
 * 时间复杂度: O(log exponent)
 * 空间复杂度: O(1)
 */
long long fast_power(long long base, long long exponent, long long mod);

/**
 * 快速幂算法（递归实现）
 * 
 * 递归关系：
 * - base^exponent = (base^(exponent/2))^2 如果exponent是偶数
 * - base^exponent = base * base^(exponent-1) 如果exponent是奇数
 * 
 * 参数:
 *     base: 底数
 *     exponent: 指数
 *     mod: 模数，0表示不取模
 * 返回:
 *     base^exponent % mod
 */
long long fast_power_recursive(long long base, long long exponent, long long mod);

/**
 * 普通幂运算（用于对比）
 * 
 * 参数:
 *     base: 底数
 *     exponent: 指数
 * 返回:
 *     base^exponent
 * 
 * 时间复杂度: O(exponent)
 */
long long slow_power(long long base, long long exponent);

/**
 * 快速幂算法演示程序
 * 
 * 功能：
 * - 演示快速幂算法的效率
 * - 对比迭代和递归实现
 * - 展示大数幂取模的应用
 */
int main()
{
    printf("快速幂算法演示 (Fast Power)\n");
    printf("==========================\n\n");
    
    // 测试用例
    struct {
        long long base;
        long long exponent;
    } test_cases[] = {
        {2, 10},
        {3, 5},
        {5, 3},
        {10, 6},
        {2, 20}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("快速幂计算（迭代法）:\n");
    for (int i = 0; i < num_cases; i++) {
        long long base = test_cases[i].base;
        long long exp = test_cases[i].exponent;
        
        long long result = fast_power(base, exp, 0);
        long long verify = slow_power(base, exp);
        
        printf("  %lld^%lld = %lld (验证: %lld) %s\n", 
               base, exp, result, verify, 
               (result == verify) ? "✓" : "✗");
    }
    
    printf("\n快速幂计算（递归法）:\n");
    for (int i = 0; i < num_cases; i++) {
        long long base = test_cases[i].base;
        long long exp = test_cases[i].exponent;
        
        long long result = fast_power_recursive(base, exp, 0);
        long long verify = slow_power(base, exp);
        
        printf("  %lld^%lld = %lld (验证: %lld) %s\n", 
               base, exp, result, verify, 
               (result == verify) ? "✓" : "✗");
    }
    
    // 大数取模演示
    printf("\n大数幂取模 (模 %lld):\n", MOD);
    printf("  2^100 mod %lld = %lld\n", MOD, fast_power(2, 100, MOD));
    printf("  10^18 mod %lld = %lld\n", MOD, fast_power(10, 18, MOD));
    printf("  123456789^123456789 mod %lld = %lld\n", MOD, 
           fast_power(123456789, 123456789, MOD));
    
    // 性能对比
    printf("\n性能对比:\n");
    printf("  普通方法: O(n) - 需要n次乘法\n");
    printf("  快速幂: O(log n) - 只需要log n次乘法\n");
    printf("  例如：2^1000\n");
    printf("    普通方法需要1000次乘法\n");
    printf("    快速幂只需要约10次乘法\n");
    
    // 应用场景
    printf("\n应用场景:\n");
    printf("  • 密码学（RSA、Diffie-Hellman）\n");
    printf("  • 数论计算\n");
    printf("  • 矩阵快速幂\n");
    printf("  • 组合数学计算\n");
    printf("  • 竞赛编程大数运算\n");
    
    return 0;
}

/**
 * 快速幂算法（迭代实现）
 * 使用二进制分解的思想，高效计算幂运算
 */
long long fast_power(long long base, long long exponent, long long mod)
{
    long long result = 1;
    
    // 如果需要取模，先对底数取模
    if (mod != 0) {
        base = base % mod;
    }
    
    while (exponent > 0)
    {
        // 如果指数是奇数，乘以当前底数
        if (exponent % 2 == 1)
        {
            result = (mod != 0) ? (result * base) % mod : result * base;
        }
        
        // 底数平方
        base = (mod != 0) ? (base * base) % mod : base * base;
        
        // 指数减半（右移一位）
        exponent /= 2;
    }
    
    return result;
}

/**
 * 快速幂算法（递归实现）
 * 使用分治思想，递归计算幂运算
 */
long long fast_power_recursive(long long base, long long exponent, long long mod)
{
    // 基础情况
    if (exponent == 0) return 1;
    if (exponent == 1) return (mod != 0) ? base % mod : base;
    
    // 递归计算 base^(exponent/2)
    long long half = fast_power_recursive(base, exponent / 2, mod);
    
    // 根据指数奇偶性决定计算方式
    if (exponent % 2 == 0)
    {
        // 偶数: (base^(n/2))^2
        long long result = half * half;
        return (mod != 0) ? result % mod : result;
    }
    else
    {
        // 奇数: base * (base^((n-1)/2))^2
        long long half_squared = half * half;
        long long result = half_squared * base;
        return (mod != 0) ? result % mod : result;
    }
}

/**
 * 普通幂运算（用于对比验证）
 * 简单的循环乘法，效率较低但便于理解
 */
long long slow_power(long long base, long long exponent)
{
    long long result = 1;
    
    for (long long i = 0; i < exponent; i++)
    {
        result *= base;
    }
    
    return result;
}
