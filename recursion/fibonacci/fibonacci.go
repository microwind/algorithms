// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
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
package main

import "fmt"

// 记忆化缓存
var memo = make(map[int]int)

/**
 * 纯递归实现 - 最慢版本
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
func fibNaive(n int) int {
	// 基本情况
	if n <= 1 {
		return n
	}

	// 递归调用
	return fibNaive(n-1) + fibNaive(n-2)
}

/**
 * 记忆化递归实现 - 推荐版本
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
func fibMemo(n int) int {
	// 检查缓存
	if val, exists := memo[n]; exists {
		return val
	}

	// 基本情况
	if n <= 1 {
		memo[n] = n
		return n
	}

	// 计算并缓存结果
	result := fibMemo(n-1) + fibMemo(n-2)
	memo[n] = result
	return result
}

/**
 * 动态规划实现
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
func fibDp(n int) int {
	// 基本情况
	if n <= 1 {
		return n
	}

	// DP数组
	dp := make([]int, n+1)
	dp[0] = 0
	dp[1] = 1

	// 填充DP数组
	for i := 2; i <= n; i++ {
		dp[i] = dp[i-1] + dp[i-2]
	}

	return dp[n]
}

/**
 * 优化动态规划实现 - 空间优化
 * 时间复杂度: O(n)，空间复杂度: O(1)
 * @param n 要计算的斐波那契数列位置
 * @return 第n个斐波那契数
 */
func fibOptimized(n int) int {
	// 基本情况
	if n <= 1 {
		return n
	}

	// 前两个数
	prev, curr := 0, 1

	// 迭代计算
	for i := 2; i <= n; i++ {
		next := prev + curr
		prev = curr
		curr = next
	}

	return curr
}

/**
 * 主函数 - 性能对比测试
 */
func main() {
	n := 30
	fmt.Printf("计算第 %d 个斐波那契数\n", n)

	// 测试记忆化递归
	fmt.Printf("记忆化递归: %d\n", fibMemo(n))

	// 测试动态规划
	fmt.Printf("动态规划: %d\n", fibDp(n))

	// 测试优化DP
	fmt.Printf("优化DP: %d\n", fibOptimized(n))
}
