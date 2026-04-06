/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 斐波那契数列多实现方式教学示例
 * 
 * 包含四种实现：
 * - 纯递归：O(2^n) 时间复杂度
 * - 记忆化递归：O(n) 时间复杂度
 * - 动态规划：O(n) 时间复杂度
 * - 优化DP：O(n) 时间复杂度，O(1) 空间复杂度
 * 
 * 核心公式：F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1
 * 
 * 学习重点：掌握不同优化策略的性能差异
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局缓存数组
int cache[1000] = {0};

/**
 * 纯递归实现 - 最慢版本
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 */
int fib_naive(int n) {
    // 基本情况
    if (n <= 1) return n;
    
    // 递归调用
    return fib_naive(n - 1) + fib_naive(n - 2);
}

/**
 * 记忆化递归实现 - 推荐版本
 * 时间复杂度: O(n)，空间复杂度: O(n)
 */
int fib_memo(int n) {
    // 检查缓存
    if (cache[n] != 0) return cache[n];
    
    // 基本情况
    if (n <= 1) {
        cache[n] = n;
        return n;
    }
    
    // 计算并缓存结果
    cache[n] = fib_memo(n - 1) + fib_memo(n - 2);
    return cache[n];
}

/**
 * 动态规划实现
 * 时间复杂度: O(n)，空间复杂度: O(n)
 */
int fib_dp(int n) {
    // 基本情况
    if (n <= 1) return n;
    
    // DP数组
    int *dp = (int*)malloc((n + 1) * sizeof(int));
    dp[0] = 0;
    dp[1] = 1;
    
    // 填充DP数组
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    int result = dp[n];
    free(dp);
    return result;
}

/**
 * 优化动态规划实现 - 空间优化
 * 时间复杂度: O(n)，空间复杂度: O(1)
 */
int fib_optimized(int n) {
    // 基本情况
    if (n <= 1) return n;
    
    // 前两个数
    int prev = 0, curr = 1;
    
    // 迭代计算
    for (int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    return curr;
}

/**
 * 主函数 - 性能对比测试
 */
int main() {
    int n = 30;
    printf("计算第 %d 个斐波那契数\n", n);
    
    // 测试记忆化递归
    printf("记忆化递归: %d\n", fib_memo(n));
    
    // 测试动态规划
    printf("动态规划: %d\n", fib_dp(n));
    
    // 测试优化DP
    printf("优化DP: %d\n", fib_optimized(n));
    
    return 0;
}
