package main

import (
	"fmt"
	"math"
)

/*
 * 硬币兑换问题 (Coin Change) - 动态规划应用
 *
 * 问题描述：
 * 给定不同面值的硬币和一个金额，找出使用最少数量的硬币凑出该金额
 *
 * 动态规划方程：
 * dp[i] = min(dp[i], dp[i-coin] + 1) for each coin
 *
 * 时间复杂度: O(n * amount)
 * 空间复杂度: O(amount)
 */

// 硬币兑换 - 求最少硬币数量
func CoinChange(coins []int, amount int) int {
	if amount == 0 {
		return 0
	}

	// dp[i] 表示凑出金额 i 需要的最少硬币数
	dp := make([]int, amount+1)
	for i := 1; i <= amount; i++ {
		dp[i] = math.MaxInt32
	}
	dp[0] = 0

	// 对每个金额进行处理
	for i := 1; i <= amount; i++ {
		// 尝试使用每枚硬币
		for _, coin := range coins {
			if coin <= i && dp[i-coin] != math.MaxInt32 {
				// 如果可以使用该硬币，更新最少数量
				if dp[i-coin]+1 < dp[i] {
					dp[i] = dp[i-coin] + 1
				}
			}
		}
	}

	if dp[amount] == math.MaxInt32 {
		return -1
	}
	return dp[amount]
}

// 硬币兑换 - 返回具体的硬币组合
func CoinChangeWithCoins(coins []int, amount int) (int, []int) {
	if amount == 0 {
		return 0, []int{}
	}

	// dp[i] 表示凑出金额 i 需要的最少硬币数
	dp := make([]int, amount+1)
	// parent[i] 表示凑出金额 i 时使用的硬币面值
	parent := make([]int, amount+1)

	for i := 1; i <= amount; i++ {
		dp[i] = math.MaxInt32
		parent[i] = -1
	}
	dp[0] = 0

	// 对每个金额进行处理
	for i := 1; i <= amount; i++ {
		// 尝试使用每枚硬币
		for _, coin := range coins {
			if coin <= i && dp[i-coin] != math.MaxInt32 && dp[i-coin]+1 < dp[i] {
				dp[i] = dp[i-coin] + 1
				parent[i] = coin
			}
		}
	}

	if dp[amount] == math.MaxInt32 {
		return -1, []int{}
	}

	// 反向追踪构建硬币组合
	result := make([]int, 0)
	idx := amount
	for idx > 0 {
		coin := parent[idx]
		result = append(result, coin)
		idx -= coin
	}

	return dp[amount], result
}

// 测试函数
func main() {
	fmt.Println("=== 硬币兑换问题 ===\n")

	// 测试用例1：基本硬币兑换
	fmt.Println("1. 基本硬币兑换")
	coins1 := []int{1, 2, 5}
	amount1 := 5
	fmt.Printf("硬币面值: %v\n", coins1)
	fmt.Printf("需要凑出的金额: %d\n", amount1)
	fmt.Printf("最少硬币数: %d\n\n", CoinChange(coins1, amount1))

	// 测试用例2：返回具体的硬币组合
	fmt.Println("2. 返回具体的硬币组合")
	coins2 := []int{1, 2, 5}
	amount2 := 7
	fmt.Printf("硬币面值: %v\n", coins2)
	fmt.Printf("需要凑出的金额: %d\n", amount2)
	count, combination := CoinChangeWithCoins(coins2, amount2)
	fmt.Printf("最少硬币数: %d\n", count)
	fmt.Printf("硬币组合: %v\n\n", combination)

	// 测试用例3：无法凑出的金额
	fmt.Println("3. 无法凑出的金额")
	coins3 := []int{2, 5}
	amount3 := 3
	fmt.Printf("硬币面值: %v\n", coins3)
	fmt.Printf("需要凑出的金额: %d\n", amount3)
	fmt.Printf("最少硬币数: %d\n\n", CoinChange(coins3, amount3))

	// 测试用例4：更大的金额
	fmt.Println("4. 更大的金额")
	coins4 := []int{1, 3, 4}
	amount4 := 10
	fmt.Printf("硬币面值: %v\n", coins4)
	fmt.Printf("需要凑出的金额: %d\n", amount4)
	count4, combination4 := CoinChangeWithCoins(coins4, amount4)
	fmt.Printf("最少硬币数: %d\n", count4)
	fmt.Printf("硬币组合: %v\n", combination4)
}
