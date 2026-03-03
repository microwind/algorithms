package main

import (
	"fmt"
)

/*
* 编辑距离 (Edit Distance / Levenshtein Distance) - 动态规划应用
 *
 * 问题描述：
 * 给定两个字符串，计算从一个字符串转换到另一个字符串所需的最少编辑操作数
 *
 * 动态规划方程：
 * if s1[i-1] == s2[j-1]:
 *     dp[i][j] = dp[i-1][j-1]
 * else:
 *     dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
 *
 * 时间复杂度: O(m * n)
 * 空间复杂度: O(m * n)
*/

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func min3(a, b, c int) int {
	return min(min(a, b), c)
}

// 编辑距离 - 求最少操作数
func EditDistance(s1, s2 string) int {
	m := len(s1)
	n := len(s2)

	// dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
	dp := make([][]int, m+1)
	for i := 0; i <= m; i++ {
		dp[i] = make([]int, n+1)
	}

	// 初始化
	for j := 0; j <= n; j++ {
		dp[0][j] = j
	}
	for i := 0; i <= m; i++ {
		dp[i][0] = i
	}

	// 填充 DP 表
	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if s1[i-1] == s2[j-1] {
				// 字符相同，不需要操作
				dp[i][j] = dp[i-1][j-1]
			} else {
				// 字符不同，选择最少操作数的方案
				dp[i][j] = 1 + min3(
					dp[i-1][j],      // 删除
					dp[i][j-1],      // 插入
					dp[i-1][j-1],    // 替换
				)
			}
		}
	}

	return dp[m][n]
}

// 编辑距离 - 空间优化版本
func EditDistanceOptimized(s1, s2 string) int {
	m := len(s1)
	n := len(s2)

	// 确保 s1 是较短的字符串
	if m > n {
		s1, s2 = s2, s1
		m, n = n, m
	}

	// 使用两行数组来计算
	prev := make([]int, n+1)
	curr := make([]int, n+1)

	// 初始化 prev 行
	for j := 0; j <= n; j++ {
		prev[j] = j
	}

	for i := 1; i <= m; i++ {
		curr[0] = i

		for j := 1; j <= n; j++ {
			if s1[i-1] == s2[j-1] {
				curr[j] = prev[j-1]
			} else {
				curr[j] = 1 + min3(prev[j], curr[j-1], prev[j-1])
			}
		}

		// 交换行
		prev, curr = curr, prev
	}

	return prev[n]
}

// 测试函数
func main() {
	fmt.Println("=== 编辑距离问题 ===\n")

	// 测试用例1：基本编辑距离
	fmt.Println("1. 基本编辑距离")
	s1_1 := "horse"
	s2_1 := "ros"
	fmt.Printf("字符串1: %s\n", s1_1)
	fmt.Printf("字符串2: %s\n", s2_1)
	fmt.Printf("编辑距离: %d\n\n", EditDistance(s1_1, s2_1))

	// 测试用例2：相同字符串
	fmt.Println("2. 相同字符串")
	s1_2 := "hello"
	s2_2 := "hello"
	fmt.Printf("字符串1: %s\n", s1_2)
	fmt.Printf("字符串2: %s\n", s2_2)
	fmt.Printf("编辑距离: %d\n\n", EditDistance(s1_2, s2_2))

	// 测试用例3：空字符串
	fmt.Println("3. 空字符串")
	s1_3 := "abc"
	s2_3 := ""
	fmt.Printf("字符串1: %s\n", s1_3)
	fmt.Printf("字符串2: %s\n", s2_3)
	fmt.Printf("编辑距离: %d\n\n", EditDistance(s1_3, s2_3))

	// 测试用例4：不同长度的字符串
	fmt.Println("4. 不同长度的字符串")
	s1_4 := "intention"
	s2_4 := "execution"
	fmt.Printf("字符串1: %s\n", s1_4)
	fmt.Printf("字符串2: %s\n", s2_4)
	fmt.Printf("编辑距离: %d\n", EditDistance(s1_4, s2_4))
	fmt.Printf("编辑距离（优化）: %d\n", EditDistanceOptimized(s1_4, s2_4))
}
