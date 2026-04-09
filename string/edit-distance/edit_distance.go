/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

package main

import (
	"fmt"
	"math"
)

/**
 * 字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
 * 
 * 算法原理：
 * 1. 计算将一个字符串转换为另一个字符串所需的最少操作次数。
 * 2. 允许的操作包括：插入、删除、替换。
 * 3. 采用动态规划（DP）思想求解。
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)，可优化至 O(min(m, n))
 */

// Min returns the minimum of the provided integers
func Min(vars ...int) int {
	min := vars[0]
	for _, i := range vars {
		if i < min {
			min = i
		}
	}
	return min
}

// EditDistance 计算编辑距离 (基础DP版本)
func EditDistance(word1, word2 string) int {
	n, m := len(word1), len(word2)
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
	}

	for i := 0; i <= n; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= m; j++ {
		dp[0][j] = j
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if word1[i-1] == word2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				dp[i][j] = 1 + Min(
					dp[i-1][j],    // 删除
					dp[i][j-1],    // 插入
					dp[i-1][j-1],  // 替换
				)
			}
		}
	}
	return dp[n][m]
}

// EditDistanceOptimized 空间优化后的编辑距离计算
func EditDistanceOptimized(word1, word2 string) int {
	if len(word1) < len(word2) {
		word1, word2 = word2, word1
	}
	n, m := len(word1), len(word2)
	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	for i := 1; i <= n; i++ {
		curr[0] = i
		for j := 1; j <= m; j++ {
			if word1[i-1] == word2[j-1] {
				curr[j] = prev[j-1]
			} else {
				curr[j] = 1 + Min(prev[j], curr[j-1], prev[j-1])
			}
		}
		copy(prev, curr)
	}
	return prev[m]
}

// EditDistanceRecursive 递归加记忆化计算编辑距离
func EditDistanceRecursive(word1, word2 string) int {
	memo := make(map[string]int)
	var helper func(int, int) int
	helper = func(i, j int) int {
		if i == 0 { return j }
		if j == 0 { return i }
		key := fmt.Sprintf("%d-%d", i, j)
		if v, ok := memo[key]; ok {
			return v
		}

		var res int
		if word1[i-1] == word2[j-1] {
			res = helper(i-1, j-1)
		} else {
			res = 1 + Min(
				helper(i-1, j),
				helper(i, j-1),
				helper(i-1, j-1),
			)
		}
		memo[key] = res
		return res
	}
	return helper(len(word1), len(word2))
}

// GetEditOperations 获取具体的编辑步骤
func GetEditOperations(word1, word2 string) []string {
	n, m := len(word1), len(word2)
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
	}
	for i := 0; i <= n; i++ { dp[i][0] = i }
	for j := 0; j <= m; j++ { dp[0][j] = j }
	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if word1[i-1] == word2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				dp[i][j] = 1 + Min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
			}
		}
	}

	var ops []string
	i, j := n, m
	for i > 0 || j > 0 {
		if i > 0 && j > 0 && word1[i-1] == word2[j-1] {
			i--; j--
		} else if i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1]+1 {
			ops = append([]string{fmt.Sprintf("替换 '%c' 为 '%c'", word1[i-1], word2[j-1])}, ops...)
			i--; j--
		} else if i > 0 && dp[i][j] == dp[i-1][j]+1 {
			ops = append([]string{fmt.Sprintf("删除 '%c'", word1[i-1])}, ops...)
			i--
		} else {
			ops = append([]string{fmt.Sprintf("插入 '%c'", word2[j-1])}, ops...)
			j--
		}
	}
	return ops
}

// GetSimilarityRatio 计算相似度
func GetSimilarityRatio(word1, word2 string) float64 {
	dist := EditDistance(word1, word2)
	maxLen := math.Max(float64(len(word1)), float64(len(word2)))
	if maxLen == 0 { return 1.0 }
	return 1.0 - float64(dist)/maxLen
}

func main() {
	fmt.Println("====================================================")
	fmt.Println("编辑距离 (Edit Distance) - Go 实现")
	fmt.Println("====================================================")

	testCases := [][]string{
		{"kitten", "sitting"},
		{"sunday", "saturday"},
		{"abc", ""},
		{"", "abc"},
		{"same", "same"},
	}

	for _, tc := range testCases {
		s1, s2 := tc[0], tc[1]
		fmt.Printf("\n源字符串: \"%s\"\n", s1)
		fmt.Printf("目标字符串: \"%s\"\n", s2)
		fmt.Printf("最小编辑距离 (DP): %d\n", EditDistance(s1, s2))
		fmt.Printf("最小编辑距离 (优化DP): %d\n", EditDistanceOptimized(s1, s2))
		fmt.Printf("最小编辑距离 (递归): %d\n", EditDistanceRecursive(s1, s2))
		fmt.Printf("相似度: %.2f%%\n", GetSimilarityRatio(s1, s2)*100)
		if len(s1) < 10 && len(s2) < 10 {
			fmt.Printf("操作步骤: %v\n", GetEditOperations(s1, s2))
		}
	}
}
