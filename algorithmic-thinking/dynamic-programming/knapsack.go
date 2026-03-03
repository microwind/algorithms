package main

import (
	"fmt"
)

/*
* 0-1 背包问题 - 动态规划的经典应用
 *
 * 时间复杂度: O(n * W)
 * 空间复杂度: O(n * W) 或 O(W)
*/

// 返回两个数中的最大值
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// 0-1 背包问题 - 二维 DP
func Knapsack(weights []int, values []int, capacity int) int {
	n := len(weights)

	// dp[i][w] 表示前 i 件物品，容量为 w 时的最大价值
	dp := make([][]int, n+1)
	for i := 0; i <= n; i++ {
		dp[i] = make([]int, capacity+1)
	}

	// 填充 dp 表
	for i := 1; i <= n; i++ {
		weight := weights[i-1]
		value := values[i-1]

		for w := 0; w <= capacity; w++ {
			if weight <= w {
				// 选择或不选择
				dp[i][w] = max(
					dp[i-1][w],
					dp[i-1][w-weight]+value,
				)
			} else {
				// 物品太重
				dp[i][w] = dp[i-1][w]
			}
		}
	}

	return dp[n][capacity]
}

// 0-1 背包问题 - 空间优化版本
func KnapsackOptimized(weights []int, values []int, capacity int) int {
	n := len(weights)

	// dp[w] 表示容量为 w 时的最大价值
	dp := make([]int, capacity+1)

	// 处理每件物品
	for i := 0; i < n; i++ {
		weight := weights[i]
		value := values[i]

		// 从后向前遍历容量
		for w := capacity; w >= weight; w-- {
			dp[w] = max(dp[w], dp[w-weight]+value)
		}
	}

	return dp[capacity]
}

// 测试函数
func main() {
	fmt.Println("=== 0-1 背包问题 ===\n")

	// 测试用例1：基本背包问题
	fmt.Println("1. 基本背包问题")
	weights := []int{2, 3, 4, 5}
	values := []int{3, 4, 5, 6}
	capacity := 8

	fmt.Printf("物品重量: %v\n", weights)
	fmt.Printf("物品价值: %v\n", values)
	fmt.Printf("背包容量: %d\n", capacity)

	maxValue := Knapsack(weights, values, capacity)
	fmt.Printf("最大价值: %d\n\n", maxValue)

	// 测试用例2：空间优化版本
	fmt.Println("2. 空间优化版本")
	maxValueOpt := KnapsackOptimized(weights, values, capacity)
	fmt.Printf("最大价值（优化）: %d\n\n", maxValueOpt)

	// 测试用例3：容量较大
	fmt.Println("3. 容量较大的背包")
	weights2 := []int{1, 2, 3, 4, 5}
	values2 := []int{1, 3, 5, 7, 9}
	capacity2 := 10

	fmt.Printf("物品重量: %v\n", weights2)
	fmt.Printf("物品价值: %v\n", values2)
	fmt.Printf("背包容量: %d\n", capacity2)

	maxValue2 := Knapsack(weights2, values2, capacity2)
	fmt.Printf("最大价值: %d\n", maxValue2)
}
