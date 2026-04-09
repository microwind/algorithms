/*
 * 数学基础 - 斐波那契数列 (Fibonacci Sequence)
 * 计算斐波那契数列的第n项
 * 支持递归、迭代、矩阵快速幂和通项公式多种算法
 * 时间复杂度: O(2^n) - 朴素递归, O(n) - 迭代, O(log n) - 矩阵快速幂
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 斐波那契数列定义：
 * F(0) = 0, F(1) = 1
 * F(n) = F(n-1) + F(n-2) (n ≥ 2)
 * 
 * 数列: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144...
 */

/**
 * 朴素递归算法
 * 
 * 直接根据定义实现
 * 
 * 时间复杂度: O(2^n) - 指数级，存在大量重复计算
 * 空间复杂度: O(n) - 递归栈深度
 */
unsigned long long fib_recursive(int n);

/**
 * 记忆化递归（Memoization）
 * 
 * 用数组存储已计算的结果，避免重复计算
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
 */
unsigned long long fib_memoization(int n, unsigned long long *memo);

/**
 * 迭代算法
 * 
 * 自底向上计算，保存前两个值
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(1) - 只使用常数空间
 */
unsigned long long fib_iterative(int n);

/**
 * 矩阵快速幂算法
 * 
 * 利用矩阵乘法：
 * | F(n+1)  F(n)   |   | 1  1 | ^n
 * | F(n)    F(n-1) | = | 1  0 |
 * 
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1)
 */
unsigned long long fib_matrix(int n);

/**
 * 通项公式（比内公式）
 * 
 * F(n) = (φ^n - ψ^n) / √5
 * 其中 φ = (1+√5)/2 ≈ 1.618（黄金比例）
 *      ψ = (1-√5)/2 ≈ -0.618
 * 
 * 由于浮点精度限制，仅适用于小n
 * 
 * 时间复杂度: O(1)
 */
double fib_formula(int n);

// 矩阵乘法辅助函数
void matrix_multiply(unsigned long long a[2][2], unsigned long long b[2][2]);
void matrix_power(unsigned long long mat[2][2], int n);

/**
 * 主函数 - 斐波那契数列演示
 */
int main()
{
    int n;
    
    printf("========================================\n");
    printf("    斐波那契数列 (Fibonacci Sequence)\n");
    printf("========================================\n\n");
    
    // 显示斐波那契数列前20项
    printf("斐波那契数列前20项:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < 20; i++) {
        printf("F(%2d) = %10llu\n", i, fib_iterative(i));
    }
    
    // 黄金比例近似
    printf("\n----------------------------------------\n");
    printf("黄金比例近似:\n");
    printf("----------------------------------------\n");
    for (int i = 2; i <= 15; i++) {
        double ratio = (double)fib_iterative(i) / fib_iterative(i-1);
        printf("F(%d)/F(%d) = %.10f\n", i, i-1, ratio);
    }
    printf("真实黄金比例 φ = %.10f\n", (1 + sqrt(5)) / 2);
    
    // 用户输入
    printf("\n请输入要计算的项数n (0-92, 受限于64位整数): ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 92) {
        printf("错误：请输入0到92之间的整数\n");
        return 1;
    }
    
    printf("\n----------------------------------------\n");
    printf("计算 F(%d):\n", n);
    printf("----------------------------------------\n");
    
    // 迭代法（推荐）
    unsigned long long result_iter = fib_iterative(n);
    printf("迭代法:        F(%d) = %llu\n", n, result_iter);
    
    // 记忆化递归
    unsigned long long memo[93] = {0};
    memo[1] = 1;
    unsigned long long result_memo = fib_memoization(n, memo);
    printf("记忆化递归:    F(%d) = %llu\n", n, result_memo);
    
    // 矩阵快速幂
    unsigned long long result_matrix = fib_matrix(n);
    printf("矩阵快速幂:    F(%d) = %llu\n", n, result_matrix);
    
    // 通项公式（小n时）
    if (n <= 70) {
        double result_formula = fib_formula(n);
        printf("通项公式:      F(%d) = %.0f\n", n, result_formula);
    }
    
    // 算法性能比较
    if (n <= 40) {
        printf("\n----------------------------------------\n");
        printf("朴素递归结果:  F(%d) = ", n);
        fflush(stdout);
        unsigned long long result_rec = fib_recursive(n);
        printf("%llu\n", result_rec);
        printf("(注: n>40时递归会很慢)\n");
    }
    
    // 数学性质
    printf("\n========================================\n");
    printf("数学性质:\n");
    printf("========================================\n");
    printf("• 定义: F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)\n");
    printf("• 黄金比例: lim F(n+1)/F(n) = φ = (1+√5)/2 ≈ 1.618\n");
    printf("• 求和性质: ΣF(i) [i=0 to n] = F(n+2) - 1\n");
    printf("• 平方和: ΣF(i)² [i=0 to n] = F(n) × F(n+1)\n");
    printf("• 卡西尼恒等式: F(n-1)×F(n+1) - F(n)² = (-1)^n\n");
    printf("• 组合公式: F(n) = C(n-1,0) + C(n-2,1) + C(n-3,2) + ...\n");
    
    // 应用场景
    printf("\n========================================\n");
    printf("应用场景:\n");
    printf("========================================\n");
    printf("• 自然界: 向日葵种子排列、鹦鹉螺壳螺旋\n");
    printf("• 艺术设计: 黄金分割、构图比例\n");
    printf("• 金融分析: 斐波那契回撤、技术分析\n");
    printf("• 算法分析: AVL树的最少节点数\n");
    printf("• 数据结构: 斐波那契堆\n");
    printf("• 生物数学: 兔子繁殖模型\n");
    
    return 0;
}

/**
 * 朴素递归
 */
unsigned long long fib_recursive(int n)
{
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

/**
 * 记忆化递归
 */
unsigned long long fib_memoization(int n, unsigned long long *memo)
{
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];
    
    memo[n] = fib_memoization(n - 1, memo) + fib_memoization(n - 2, memo);
    return memo[n];
}

/**
 * 迭代算法
 */
unsigned long long fib_iterative(int n)
{
    if (n <= 1) return n;
    
    unsigned long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

/**
 * 矩阵乘法
 */
void matrix_multiply(unsigned long long a[2][2], unsigned long long b[2][2])
{
    unsigned long long temp[2][2];
    temp[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    temp[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    temp[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    temp[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            a[i][j] = temp[i][j];
}

/**
 * 矩阵快速幂
 */
void matrix_power(unsigned long long mat[2][2], int n)
{
    if (n <= 1) return;
    
    unsigned long long base[2][2] = {{1, 1}, {1, 0}};
    matrix_power(mat, n / 2);
    matrix_multiply(mat, mat);
    
    if (n % 2 == 1)
        matrix_multiply(mat, base);
}

/**
 * 矩阵快速幂计算斐波那契
 */
unsigned long long fib_matrix(int n)
{
    if (n <= 1) return n;
    
    unsigned long long mat[2][2] = {{1, 1}, {1, 0}};
    matrix_power(mat, n - 1);
    return mat[0][0];
}

/**
 * 通项公式（比内公式）
 */
double fib_formula(int n)
{
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;  // 黄金比例
    double psi = (1 - sqrt5) / 2;
    
    return (pow(phi, n) - pow(psi, n)) / sqrt5;
}
