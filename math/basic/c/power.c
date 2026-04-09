/*
 * 数学基础 - 幂运算 (Power/Exponentiation)
 * 计算基数的指数次幂
 * 支持快速幂算法（二分幂）
 * 时间复杂度: O(log n) - 快速幂，O(n) - 普通幂
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 普通幂运算 - 线性算法
 * 
 * 算法原理：
 * - 将基数乘以自身 n 次
 * - result = base × base × ... × base (共n次)
 * 
 * 参数:
 *     base: 基数
 *     exp:  指数（非负整数）
 * 返回:
 *     base^exp 的结果
 * 
 * 时间复杂度: O(n) - 线性复杂度
 * 空间复杂度: O(1) - 常数空间
 */
double power_linear(double base, int exp);

/**
 * 快速幂运算 - 二分算法（二进制分解）
 * 
 * 算法原理：
 * - 利用指数的二进制表示
 * - a^n = a^(2^k1) × a^(2^k2) × ... × a^(2^km)
 * - 通过平方运算快速计算大指数
 * 
 * 示例: 2^13 = 2^8 × 2^4 × 2^1 = 8192
 *       13 = 1101₂
 * 
 * 参数:
 *     base: 基数
 *     exp:  指数（非负整数）
 * 返回:
 *     base^exp 的结果
 * 
 * 时间复杂度: O(log n) - 对数复杂度
 * 空间复杂度: O(1) - 常数空间
 */
double power_fast(double base, int exp);

/**
 * 整数幂运算（返回整数结果）
 * 
 * 参数:
 *     base: 整数基数
 *     exp:  指数（非负整数）
 * 返回:
 *     base^exp 的整数结果
 * 注意:
 *     可能溢出，结果需验证
 */
long long power_int(int base, int exp);

/**
 * 主函数 - 幂运算演示程序
 * 
 * 功能：
 * - 演示普通幂和快速幂算法
 * - 比较两种算法的性能
 * - 展示大数计算
 * 
 * 输入样例：
 * 请输入基数: 2
 * 请输入指数: 10
 * 
 * 输出样例：
 * 2^10 = 1024
 */
int main()
{
    double base;
    int exp;
    
    printf("========================================\n");
    printf("    幂运算演示程序 (Power Calculator)\n");
    printf("========================================\n\n");
    
    // 获取基数输入
    printf("请输入基数 (double): ");
    if (scanf("%lf", &base) != 1) {
        printf("错误：请输入有效的数字\n");
        return 1;
    }
    
    // 获取指数输入
    printf("请输入指数 (非负整数): ");
    if (scanf("%d", &exp) != 1 || exp < 0) {
        printf("错误：请输入非负整数\n");
        return 1;
    }
    
    printf("\n----------------------------------------\n");
    printf("计算结果:\n");
    printf("----------------------------------------\n");
    
    // 使用普通幂算法
    double result_linear = power_linear(base, exp);
    printf("普通幂算法:   %.6f^%d = %.6f\n", base, exp, result_linear);
    
    // 使用快速幂算法
    double result_fast = power_fast(base, exp);
    printf("快速幂算法:   %.6f^%d = %.6f\n", base, exp, result_fast);
    
    // 整数幂计算（如果适用）
    if (base == (int)base && exp >= 0 && exp <= 20) {
        long long result_int = power_int((int)base, exp);
        printf("整数幂结果:   %d^%d = %lld\n", (int)base, exp, result_int);
    }
    
    // 算法说明
    printf("\n----------------------------------------\n");
    printf("算法说明:\n");
    printf("----------------------------------------\n");
    printf("普通幂算法:\n");
    printf("  原理: 连乘法，result = base × base × ... × base\n");
    printf("  复杂度: O(n) 时间, O(1) 空间\n");
    printf("  适用: 小指数计算\n\n");
    
    printf("快速幂算法:\n");
    printf("  原理: 二进制分解，a^n = ∏ a^(2^ki)\n");
    printf("  复杂度: O(log n) 时间, O(1) 空间\n");
    printf("  适用: 大指数计算，效率高\n\n");
    
    // 数学性质
    printf("----------------------------------------\n");
    printf("幂运算数学性质:\n");
    printf("----------------------------------------\n");
    printf("• 同底数幂相乘: a^m × a^n = a^(m+n)\n");
    printf("• 幂的乘方:    (a^m)^n = a^(m×n)\n");
    printf("• 积的乘方:    (a×b)^n = a^n × b^n\n");
    printf("• 任何数的0次方: a^0 = 1 (a ≠ 0)\n");
    printf("• 负指数:      a^(-n) = 1/a^n\n");
    
    // 应用场景
    printf("\n----------------------------------------\n");
    printf("应用场景:\n");
    printf("----------------------------------------\n");
    printf("• 复利计算: 本金 × (1+利率)^年数\n");
    printf("• 人口增长: 初始人口 × 增长率^年数\n");
    printf("• 二进制转换: 2^n 表示二进制位数\n");
    printf("• 密码学: 大数幂运算（RSA加密）\n");
    printf("• 物理公式: 动能 = ½mv²\n");
    
    // 错误处理说明
    printf("\n----------------------------------------\n");
    printf("注意事项:\n");
    printf("----------------------------------------\n");
    printf("• 大指数可能导致数值溢出\n");
    printf("• 负数的非整数指数产生复数（本程序不支持）\n");
    printf("• 浮点数精度限制（双精度约15位有效数字）\n");
    
    return 0;
}

/**
 * 普通幂运算实现
 * 使用简单循环连乘
 */
double power_linear(double base, int exp)
{
    // 处理0次幂特殊情况
    if (exp == 0) {
        return 1.0;  // 任何数的0次方等于1
    }
    
    double result = 1.0;
    // 循环乘以基数 exp 次
    for (int i = 0; i < exp; i++) {
        result *= base;  // result = result × base
    }
    
    return result;
}

/**
 * 快速幂运算实现
 * 使用二进制分解方法
 */
double power_fast(double base, int exp)
{
    // 处理0次幂特殊情况
    if (exp == 0) {
        return 1.0;  // 任何数的0次方等于1
    }
    
    double result = 1.0;
    double current_power = base;
    int remaining_exp = exp;
    
    // 使用二进制分解计算幂
    // 示例: 3^13 = 3^(1101₂) = 3^8 × 3^4 × 3^1
    while (remaining_exp > 0) {
        // 如果当前二进制位为1，乘以对应的幂
        if (remaining_exp % 2 == 1) {
            result *= current_power;  // 累乘当前幂
        }
        
        // 计算下一个平方幂
        current_power *= current_power;  // 平方: 3^1 → 3^2 → 3^4 → ...
        remaining_exp /= 2;               // 右移一位（除以2）
    }
    
    return result;
}

/**
 * 整数幂运算实现
 * 返回长整型结果
 */
long long power_int(int base, int exp)
{
    // 处理0次幂特殊情况
    if (exp == 0) {
        return 1LL;  // 返回长整型1
    }
    
    long long result = 1LL;
    long long current_base = base;
    int remaining_exp = exp;
    
    // 使用快速幂算法避免溢出（尽可能）
    while (remaining_exp > 0) {
        if (remaining_exp % 2 == 1) {
            // 检查溢出
            if (result > LLONG_MAX / current_base) {
                printf("警告：整数溢出！\n");
                return 0;
            }
            result *= current_base;
        }
        
        remaining_exp /= 2;
        if (remaining_exp > 0) {
            // 检查溢出
            if (current_base > LLONG_MAX / current_base) {
                printf("警告：整数溢出！\n");
                return 0;
            }
            current_base *= current_base;
        }
    }
    
    return result;
}

/* 示例运行结果:
========================================
    幂运算演示程序 (Power Calculator)
========================================

请输入基数 (double): 2
请输入指数 (非负整数): 10

----------------------------------------
计算结果:
----------------------------------------
普通幂算法:   2.000000^10 = 1024.000000
快速幂算法:   2.000000^10 = 1024.000000
整数幂结果:   2^10 = 1024

----------------------------------------
算法说明:
----------------------------------------
普通幂算法:
  原理: 连乘法
  复杂度: O(n) 时间

快速幂算法:
  原理: 二进制分解
  复杂度: O(log n) 时间
*/
