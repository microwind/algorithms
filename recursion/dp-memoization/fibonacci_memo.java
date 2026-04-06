/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 动态规划记忆化搜索示例
 * 
 * 算法特点：
 * - 使用缓存避免重复计算
 * - 时间复杂度从 O(2^n) 优化到 O(n)
 * 
 * 学习重点：理解记忆化搜索的优化原理
 */
public class FibonacciMemo {
    
    private static final int MAX_N = 100;
    private static long[] memo = new long[MAX_N];
    
    /**
     * 初始化记忆化数组
     */
    private static void initMemo() {
        for (int i = 0; i < MAX_N; i++) {
            memo[i] = -1;
        }
    }
    
    /**
     * 记忆化版本斐波那契
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param n 要计算的斐波那契数列位置
     * @return 第n个斐波那契数
     */
    public static long fibonacciMemo(int n) {
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
    
    /**
     * 普通递归版本（用于对比）
     * 时间复杂度: O(2^n)，空间复杂度: O(n)
     * @param n 要计算的斐波那契数列位置
     * @return 第n个斐波那契数
     */
    public static long fibonacciNaive(int n) {
        if (n <= 1) return n;
        return fibonacciNaive(n - 1) + fibonacciNaive(n - 2);
    }
    
    /**
     * 主函数 - 测试记忆化搜索性能对比
     */
    public static void main(String[] args) {
        int n = 40;
        
        // 测试1：输出对比标题
        System.out.printf("斐波那契数列对比 (n=%d):\n\n", n);
        
        // 测试2：普通递归（很慢）
        System.out.printf("普通递归: ");
        System.out.printf("F(%d) = %d\n", n, fibonacciNaive(n));
        System.out.printf("  （时间复杂度: O(2^n)，有大量重复计算）\n\n");
        
        // 测试3：记忆化版本（很快）
        initMemo();
        System.out.printf("记忆化搜索: ");
        System.out.printf("F(%d) = %d\n", n, fibonacciMemo(n));
        System.out.printf("  （时间复杂度: O(n)，每个值只计算一次）\n\n");
        
        // 输出性能提升说明
        System.out.printf("性能提升: 从指数级 O(2^n) 降到线性 O(n)\n");
        System.out.printf("当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作\n");
        System.out.printf("记忆化版本只需要 40 次计算\n");
    }
}

/*打印结果
jarry@Mac dp-memoization % javac FibonacciMemo.java && java FibonacciMemo
斐波那契数列对比 (n=40):

普通递归: F(40) = 102334155
  （时间复杂度: O(2^n)，有大量重复计算）

记忆化搜索: F(40) = 102334155
  （时间复杂度: O(n)，每个值只计算一次）

性能提升: 从指数级 O(2^n) 降到线性 O(n)
当 n=40 时，普通递归需要约 2^40 ≈ 1万亿次操作
记忆化版本只需要 40 次计算
*/
