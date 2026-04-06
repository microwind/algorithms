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
import java.util.HashMap;
import java.util.Map;

public class Fibonacci {
    
    // 记忆化缓存
    private static Map<Integer, Long> memo = new HashMap<>();
    
    /**
     * 纯递归实现 - 最慢版本
     * 时间复杂度: O(2^n)，空间复杂度: O(n)
     * @param n 要计算的斐波那契数列位置
     * @return 第n个斐波那契数
     */
    public static long fibNaive(int n) {
        // 基本情况
        if (n <= 1) return n;
        
        // 递归调用
        return fibNaive(n - 1) + fibNaive(n - 2);
    }
    
    /**
     * 记忆化递归实现 - 推荐版本
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param n 要计算的斐波那契数列位置
     * @return 第n个斐波那契数
     */
    public static long fibMemo(int n) {
        // 检查缓存
        if (memo.containsKey(n)) return memo.get(n);
        
        // 基本情况
        if (n <= 1) {
            memo.put(n, (long)n);
            return n;
        }
        
        // 计算并缓存结果
        long result = fibMemo(n - 1) + fibMemo(n - 2);
        memo.put(n, result);
        return result;
    }
    
    /**
     * 动态规划实现
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param n 要计算的斐波那契数列位置
     * @return 第n个斐波那契数
     */
    public static long fibDp(int n) {
        // 基本情况
        if (n <= 1) return n;
        
        // DP数组
        long[] dp = new long[n + 1];
        dp[0] = 0;
        dp[1] = 1;
        
        // 填充DP数组
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        
        return dp[n];
    }
    
    /**
     * 优化动态规划实现 - 空间优化
     * 时间复杂度: O(n)，空间复杂度: O(1)
     * @param n 要计算的斐波那契数列位置
     * @return 第n个斐波那契数
     */
    public static long fibOptimized(int n) {
        // 基本情况
        if (n <= 1) return n;
        
        // 前两个数
        long prev = 0, curr = 1;
        
        // 迭代计算
        for (int i = 2; i <= n; i++) {
            long next = prev + curr;
            prev = curr;
            curr = next;
        }
        
        return curr;
    }
    
    /**
     * 主函数 - 性能对比测试
     */
    public static void main(String[] args) {
        int n = 30;
        System.out.printf("计算第 %d 个斐波那契数\n", n);
        
        // 测试记忆化递归
        System.out.printf("记忆化递归: %d\n", fibMemo(n));
        
        // 测试动态规划
        System.out.printf("动态规划: %d\n", fibDp(n));
        
        // 测试优化DP
        System.out.printf("优化DP: %d\n", fibOptimized(n));
    }
}
