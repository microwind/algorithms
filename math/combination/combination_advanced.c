/*
 * 数学算法 - 组合数计算 (Combination / Binomial Coefficient)
 * 计算 C(n,k) = n! / (k! * (n-k)!)
 * 使用多种方法：递归公式、动态规划、乘法公式
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

/**
 * 使用动态规划计算组合数
 * 利用公式：C(n,k) = C(n-1,k-1) + C(n-1,k)
 * 
 * 时间复杂度: O(n*k)
 * 空间复杂度: O(k)
 */
long long combination_dp(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    k = (k < n - k) ? k : n - k;  // 利用对称性减少计算
    
    long long dp[MAX_N + 1] = {0};
    dp[0] = 1;  // C(n,0) = 1
    
    for (int i = 1; i <= n; i++) {
        // 从后往前更新，避免覆盖
        for (int j = (i < k ? i : k); j > 0; j--) {
            dp[j] = dp[j] + dp[j - 1];
        }
    }
    
    return dp[k];
}

/**
 * 使用乘法公式计算组合数
 * C(n,k) = n * (n-1) * ... * (n-k+1) / (k * (k-1) * ... * 1)
 * 
 * 适合计算单个组合数，避免计算阶乘
 */
long long combination_multiplicative(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    
    k = (k < n - k) ? k : n - k;  // 利用对称性
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

/**
 * 生成杨辉三角
 * 每行的数字就是对应的组合数
 */
void pascal_triangle(int n, int triangle[MAX_N][MAX_N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                triangle[i][j] = 1;
            } else {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }
}

/**
 * 打印杨辉三角
 */
void print_pascal_triangle(int n) {
    int triangle[MAX_N][MAX_N] = {0};
    pascal_triangle(n, triangle);
    
    printf("\n杨辉三角 (前%d行):\n", n);
    for (int i = 0; i < n; i++) {
        // 打印前导空格
        for (int space = 0; space < (n - i - 1) * 2; space++) {
            printf(" ");
        }
        
        // 打印数字
        for (int j = 0; j <= i; j++) {
            printf("%4d", triangle[i][j]);
        }
        printf("\n");
    }
}

/**
 * 验证组合数性质
 */
void verify_combination_properties() {
    printf("\n验证组合数性质:\n");
    
    // 性质1: C(n,k) = C(n,n-k)
    int n = 10, k = 3;
    long long c1 = combination_dp(n, k);
    long long c2 = combination_dp(n, n - k);
    printf("  C(%d,%d) = C(%d,%d) = %lld %s\n", 
           n, k, n, n - k, c1, (c1 == c2) ? "✓" : "✗");
    
    // 性质2: C(n,k) + C(n,k+1) = C(n+1,k+1)
    long long c3 = combination_dp(n, k);
    long long c4 = combination_dp(n, k + 1);
    long long c5 = combination_dp(n + 1, k + 1);
    printf("  C(%d,%d) + C(%d,%d) = C(%d,%d) = %lld %s\n",
           n, k, n, k + 1, n + 1, k + 1, c5, 
           (c3 + c4 == c5) ? "✓" : "✗");
    
    // 性质3: Σ C(n,k) = 2^n
    long long sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += combination_dp(n, i);
    }
    printf("  Σ C(%d,k) = %lld, 2^%d = %lld %s\n",
           n, sum, n, 1LL << n, (sum == (1LL << n)) ? "✓" : "✗");
}

/**
 * 计算二项式展开系数
 */
void binomial_expansion(int a, int b, int n) {
    printf("\n二项式展开 (%d + %d)^%d:\n", a, b, n);
    printf("  ");
    
    for (int k = 0; k <= n; k++) {
        long long coeff = combination_dp(n, k);
        
        if (k > 0 && coeff > 0) printf(" + ");
        
        if (coeff != 1) printf("%lld", coeff);
        
        if (k > 0) {
            if (k == 1) {
                printf("%c", 'a' + (k == n ? 1 : 0));  // 简化处理
            } else {
                printf("%c^%d", 'a', k);
            }
        }
        
        if (n - k > 0) {
            if (k > 0) printf("%c", 'b');
            if (n - k > 1) printf("^%d", n - k);
        }
    }
    printf("\n");
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("组合数计算 (Combination)\n");
    printf("==================================================\n");
    
    printf("\n组合数 C(n,k):\n");
    struct {
        int n;
        int k;
    } test_cases[] = {
        {5, 2},
        {10, 3},
        {20, 10},
        {30, 15}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_cases; i++) {
        int n = test_cases[i].n;
        int k = test_cases[i].k;
        
        long long result_dp = combination_dp(n, k);
        long long result_mul = combination_multiplicative(n, k);
        
        printf("  C(%d,%d) = %lld (DP) = %lld (乘法) %s\n", 
               n, k, result_dp, result_mul, 
               (result_dp == result_mul) ? "✓" : "✗");
    }
    
    // 打印杨辉三角
    print_pascal_triangle(8);
    
    // 验证性质
    verify_combination_properties();
    
    // 二项式展开示例
    binomial_expansion(1, 1, 5);
    
    printf("\n应用场景:\n");
    printf("  • 从n个物品中选k个的组合数\n");
    printf("  • 二项式展开系数\n");
    printf("  • 概率计算\n");
    printf("  • 组合数学问题\n");
    printf("  • 动态规划中的状态转移\n");
    
    printf("\n复杂度分析:\n");
    printf("  • DP方法: 时间 O(n×k), 空间 O(k)\n");
    printf("  • 乘法方法: 时间 O(k), 空间 O(1)\n");
    printf("  • 杨辉三角: 时间 O(n²), 空间 O(n²)\n");
    
    return 0;
}
