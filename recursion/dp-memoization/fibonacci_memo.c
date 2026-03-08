/*
 * 记忆化搜索 - 斐波那契数列优化
 * 使用缓存避免重复计算
 */
#include <stdio.h>

#define MAX_N 100

// 记忆化数组，-1表示未计算
long long memo[MAX_N];

// 初始化记忆化数组
void initMemo() {
    for (int i = 0; i < MAX_N; i++) {
        memo[i] = -1;
    }
}

// 记忆化版本斐波那契
long long fibonacciMemo(int n) {
    // 基础情况
    if (n <= 1) return n;
    
    // 如果已计算过，直接返回缓存结果
    if (memo[n] != -1) {
        return memo[n];
    }
    
    // 递归计算并缓存结果
    memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
    return memo[n];
}

// 普通递归版本（用于对比）
long long fibonacciNaive(int n) {
    if (n <= 1) return n;
    return fibonacciNaive(n - 1) + fibonacciNaive(n - 2);
}

int main() {
    int n = 40;
    
    printf("斐波那契数列对比 (n=%d):\n\n", n);
    
    // 普通递归（很慢）
    printf("普通递归: ");
    printf("F(%d) = %lld\n", n, fibonacciNaive(n));
    printf("  （时间复杂度: O(2^n)，有大量重复计算）\n\n");
    
    // 记忆化版本（很快）
    initMemo();
    printf("记忆化搜索: ");
    printf("F(%d) = %lld\n", n, fibonacciMemo(n));
    printf("  （时间复杂度: O(n)，每个值只计算一次）\n\n");
    
    printf("性能提升: 从指数级 O(2^n) 降到线性 O(n)\n");
    printf("当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作\n");
    printf("记忆化版本只需要 40 次计算\n");
    
    return 0;
}
