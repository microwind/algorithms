/*
 * 数学算法 - 扩展欧几里得算法 (Extended Euclidean Algorithm)
 * 计算 gcd(a,b) 以及满足 ax + by = gcd(a,b) 的整数 x, y
 * 用于求解模逆元、线性同余方程等
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 扩展欧几里得算法
 * 计算 gcd(a,b) 以及满足 ax + by = gcd(a,b) 的整数 x, y
 * 
 * 参数:
 *     a: 第一个数
 *     b: 第二个数
 *     x: 存储系数x的指针
 *     y: 存储系数y的指针
 * 返回:
 *     a和b的最大公约数
 */
long long extended_gcd(long long a, long long b, long long* x, long long* y) {
    // 基本情况
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, &x1, &y1);
    
    // 更新 x 和 y
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

/**
 * 计算模逆元
 * 计算 a 在模 m 下的乘法逆元
 * 仅当 gcd(a,m) = 1 时存在
 * 
 * 参数:
 *     a: 要求逆元的数
 *     m: 模数
 * 返回:
 *     逆元值，如果不存在返回-1
 */
long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long gcd = extended_gcd(a, m, &x, &y);
    
    if (gcd != 1) {
        return -1;  // 逆元不存在
    }
    
    // 确保结果是正数
    return (x % m + m) % m;
}

/**
 * 求解线性同余方程 ax ≡ b (mod m)
 * 
 * 参数:
 *     a: 系数
 *     b: 右边常数
 *     m: 模数
 *     solutions: 存储解的数组
 *     max_solutions: 最大解的数量
 * 返回:
 *     解的数量
 */
int solve_linear_congruence(long long a, long long b, long long m, 
                          long long* solutions, int max_solutions) {
    long long x, y;
    long long gcd = extended_gcd(a, m, &x, &y);
    
    if (b % gcd != 0) {
        return 0;  // 无解
    }
    
    // 简化方程
    long long a_prime = a / gcd;
    long long b_prime = b / gcd;
    long long m_prime = m / gcd;
    
    // 特解
    long long x0 = (x * b_prime) % m_prime;
    if (x0 < 0) x0 += m_prime;
    
    // 所有解: x = x0 + k * m_prime, k = 0, 1, ..., gcd-1
    int num_solutions = (gcd < max_solutions) ? gcd : max_solutions;
    for (int k = 0; k < num_solutions; k++) {
        solutions[k] = (x0 + k * m_prime) % m;
    }
    
    return num_solutions;
}

/**
 * 验证扩展欧几里得算法的正确性
 */
void verify_extended_gcd() {
    printf("\n验证扩展欧几里得算法:\n");
    
    struct {
        long long a;
        long long b;
    } test_cases[] = {
        {240, 46},
        {99, 78},
        {56, 15},
        {123456, 7890}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        long long a = test_cases[i].a;
        long long b = test_cases[i].b;
        long long x, y;
        
        long long gcd = extended_gcd(a, b, &x, &y);
        
        printf("  %lld×%lld + %lld×%lld = %lld (gcd=%lld) %s\n",
               a, x, b, y, a * x + b * y, gcd,
               (a * x + b * y == gcd) ? "✓" : "✗");
    }
}

/**
 * 演示模逆元的计算
 */
void demonstrate_mod_inverse() {
    printf("\n模逆元计算:\n");
    
    struct {
        long long a;
        long long m;
    } test_cases[] = {
        {3, 7},
        {10, 17},
        {25, 12},
        {17, 3120}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        long long a = test_cases[i].a;
        long long m = test_cases[i].m;
        
        long long inv = mod_inverse(a, m);
        
        if (inv != -1) {
            printf("  %lld^(-1) mod %lld = %lld", a, m, inv);
            printf(" (验证: %lld×%lld mod %lld = %lld) ✓\n", 
                   a, inv, m, (a * inv) % m);
        } else {
            printf("  %lld 在模 %lld 下无逆元 (gcd≠1) ✗\n", a, m);
        }
    }
}

/**
 * 演示线性同余方程的求解
 */
void demonstrate_linear_congruence() {
    printf("\n线性同余方程求解:\n");
    
    struct {
        long long a;
        long long b;
        long long m;
    } test_cases[] = {
        {14, 30, 100},
        {35, 10, 50},
        {12, 8, 18}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        long long a = test_cases[i].a;
        long long b = test_cases[i].b;
        long long m = test_cases[i].m;
        
        long long solutions[10];
        int num_solutions = solve_linear_congruence(a, b, m, solutions, 10);
        
        printf("  %lldx ≡ %lld (mod %lld): ", a, b, m);
        
        if (num_solutions == 0) {
            printf("无解 ✗\n");
        } else {
            printf("解 = [");
            for (int j = 0; j < num_solutions; j++) {
                printf("%lld", solutions[j]);
                if (j < num_solutions - 1) printf(", ");
            }
            printf("] ✓\n");
        }
    }
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("扩展欧几里得算法 (Extended Euclidean Algorithm)\n");
    printf("==================================================\n");
    
    // 验证算法正确性
    verify_extended_gcd();
    
    // 演示模逆元
    demonstrate_mod_inverse();
    
    // 演示线性同余方程
    demonstrate_linear_congruence();
    
    printf("\n应用场景:\n");
    printf("  • 计算模逆元 (RSA加密算法)\n");
    printf("  • 求解线性同余方程\n");
    printf("  • 中国剩余定理\n");
    printf("  • Diophantine方程求解\n");
    printf("  • 密码学中的密钥生成\n");
    
    printf("\n算法特点:\n");
    printf("  • 时间复杂度: O(log min(a,b))\n");
    printf("  • 空间复杂度: O(log min(a,b)) (递归栈)\n");
    printf("  • 可以迭代实现以优化空间\n");
    printf("  • 是数论算法的基础\n");
    
    return 0;
}
