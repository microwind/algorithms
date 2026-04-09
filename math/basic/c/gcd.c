/*
 * 数学基础 - 最大公约数 (GCD - Greatest Common Divisor)
 * 使用欧几里得算法计算两个整数的最大公约数
 * 时间复杂度: O(log min(a,b))
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 欧几里得算法（辗转相除法）- 递归版
 * 
 * 算法原理：
 * - gcd(a, b) = gcd(b, a mod b)
 * - 基准条件: gcd(a, 0) = a
 * 
 * 数学定理：
 * 对于任意整数 a, b (b ≠ 0)，有 gcd(a, b) = gcd(b, a % b)
 * 
 * 参数:
 *     a, b: 两个整数（可为0）
 * 返回:
 *     a 和 b 的最大公约数
 * 
 * 时间复杂度: O(log min(a,b))
 * 空间复杂度: O(log min(a,b)) - 递归栈
 */
int gcd_recursive(int a, int b);

/**
 * 欧几里得算法 - 迭代版
 * 
 * 参数:
 *     a, b: 两个整数
 * 返回:
 *     a 和 b 的最大公约数
 * 
 * 时间复杂度: O(log min(a,b))
 * 空间复杂度: O(1)
 */
int gcd_iterative(int a, int b);

/**
 * 扩展欧几里得算法
 * 
 * 功能：
 * 找到整数 x, y 使得: ax + by = gcd(a, b)
 * 
 * 参数:
 *     a, b: 两个整数
 *     x, y: 输出参数，贝祖系数
 * 返回:
 *     gcd(a, b)
 */
int gcd_extended(int a, int b, int *x, int *y);

/**
 * 最小公倍数 (LCM)
 * 
 * 公式: lcm(a, b) = |a × b| / gcd(a, b)
 * 
 * 参数:
 *     a, b: 两个非零整数
 * 返回:
 *     a 和 b 的最小公倍数
 */
long long lcm(int a, int b);

/**
 * 主函数 - GCD演示程序
 */
int main()
{
    int a, b;
    
    printf("========================================\n");
    printf("  最大公约数计算 (GCD) - 欧几里得算法\n");
    printf("========================================\n\n");
    
    // 获取输入
    printf("请输入第一个整数: ");
    if (scanf("%d", &a) != 1) {
        printf("错误：请输入有效的整数\n");
        return 1;
    }
    
    printf("请输入第二个整数: ");
    if (scanf("%d", &b) != 1) {
        printf("错误：请输入有效的整数\n");
        return 1;
    }
    
    // 处理负数
    int abs_a = a < 0 ? -a : a;
    int abs_b = b < 0 ? -b : b;
    
    printf("\n----------------------------------------\n");
    printf("计算结果:\n");
    printf("----------------------------------------\n");
    
    // 计算GCD
    int result_recursive = gcd_recursive(abs_a, abs_b);
    int result_iterative = gcd_iterative(abs_a, abs_b);
    
    printf("gcd(%d, %d) = %d (递归算法)\n", a, b, result_recursive);
    printf("gcd(%d, %d) = %d (迭代算法)\n", a, b, result_iterative);
    
    // 扩展欧几里得算法
    int x, y;
    int gcd_ext = gcd_extended(abs_a, abs_b, &x, &y);
    printf("\n扩展欧几里得算法:\n");
    printf("  %d × (%d) + %d × (%d) = %d\n", abs_a, x, abs_b, y, gcd_ext);
    printf("  验证: %d + %d = %d\n", abs_a * x, abs_b * y, abs_a * x + abs_b * y);
    
    // 计算LCM
    if (a != 0 && b != 0) {
        long long result_lcm = lcm(abs_a, abs_b);
        printf("\nlcm(%d, %d) = %lld\n", a, b, result_lcm);
    }
    
    // 算法步骤演示
    printf("\n----------------------------------------\n");
    printf("欧几里得算法步骤演示:\n");
    printf("----------------------------------------\n");
    int temp_a = abs_a, temp_b = abs_b;
    int step = 1;
    while (temp_b != 0) {
        int remainder = temp_a % temp_b;
        printf("步骤 %d: gcd(%d, %d) = gcd(%d, %d %% %d) = gcd(%d, %d)\n",
               step++, temp_a, temp_b, temp_b, temp_a, temp_b, temp_b, remainder);
        temp_a = temp_b;
        temp_b = remainder;
    }
    printf("最终结果: %d\n", temp_a);
    
    // 数学性质
    printf("\n========================================\n");
    printf("数学性质:\n");
    printf("========================================\n");
    printf("• 交换律: gcd(a, b) = gcd(b, a)\n");
    printf("• 结合律: gcd(a, gcd(b, c)) = gcd(gcd(a, b), c)\n");
    printf("• 分配律: gcd(a, b) × lcm(a, b) = |a × b|\n");
    printf("• gcd(a, 0) = |a|\n");
    printf("• gcd(a, 1) = 1\n");
    printf("• 贝祖定理: 存在整数x,y使得 ax + by = gcd(a,b)\n");
    
    // 应用场景
    printf("\n========================================\n");
    printf("应用场景:\n");
    printf("========================================\n");
    printf("• 分数约分: 分子分母同除以gcd\n");
    printf("• 密码学: RSA算法中的密钥生成\n");
    printf("• 数论: 同余方程求解\n");
    printf("• 音乐理论: 计算和谐音程\n");
    printf("• 计算机图形: 简化比例\n");
    printf("• 调度算法: 计算任务周期\n");
    
    return 0;
}

/**
 * 欧几里得算法 - 递归实现
 */
int gcd_recursive(int a, int b)
{
    // 基准条件: b为0时，a就是gcd
    if (b == 0) {
        return a;
    }
    
    // 递归步骤: gcd(a, b) = gcd(b, a % b)
    return gcd_recursive(b, a % b);
}

/**
 * 欧几里得算法 - 迭代实现
 */
int gcd_iterative(int a, int b)
{
    // 循环直到余数为0
    while (b != 0) {
        int temp = b;      // 保存当前的b
        b = a % b;         // 计算新的余数
        a = temp;          // a变为原来的b
    }
    
    return a;  // 最后的非零余数就是gcd
}

/**
 * 扩展欧几里得算法
 * 返回gcd(a,b)，并设置x,y使得 ax + by = gcd(a,b)
 */
int gcd_extended(int a, int b, int *x, int *y)
{
    // 基准条件
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    // 递归计算
    int x1, y1;
    int gcd = gcd_extended(b, a % b, &x1, &y1);
    
    // 更新系数
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

/**
 * 最小公倍数计算
 */
long long lcm(int a, int b)
{
    // LCM = |a × b| / GCD(a, b)
    // 为避免溢出，先除后乘
    return ((long long)a / gcd_iterative(a, b)) * (long long)b;
}
