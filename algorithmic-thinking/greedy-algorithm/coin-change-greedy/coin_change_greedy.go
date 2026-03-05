package main

import (
	"fmt"
	"sort"
)


/*
* 零钱兑换问题（贪心算法）
 *
 * 算法思路：
 * - 贪心策略：每次选择不超过剩余金额的最大面值硬币
 * - 不断用最大面值硬币减去剩余金额，直到为0
 * - 注意：贪心算法并不总是最优
*/

	Count int   // 最少硬币数
	Coins []int // 使用的硬币列表
}

// CoinChangeGreedy 贪心法求凑成目标金额的最少硬币数（不一定最优）
func CoinChangeGreedy(coins []int, amount int) CoinChangeResult {
	if amount == 0 {
		return CoinChangeResult{Count: 0, Coins: []int{}}
	}

	// 降序排序硬币面值
	sorted := make([]int, len(coins))
	copy(sorted, coins)
	sort.Sort(sort.Reverse(sort.IntSlice(sorted)))

	count := 0
	coinsUsed := []int{}
	remaining := amount

	for _, coin := range sorted {
		for remaining >= coin {
			remaining -= coin
			coinsUsed = append(coinsUsed, coin)
			count++
		}
	}

	if remaining != 0 {
		return CoinChangeResult{Count: -1, Coins: []int{}}
	}

	return CoinChangeResult{Count: count, Coins: coinsUsed}
}

// CoinChangeDP 动态规划法求最少硬币数（一定最优，供对比）
func CoinChangeDP(coins []int, amount int) CoinChangeResult {
	if amount == 0 {
		return CoinChangeResult{Count: 0, Coins: []int{}}
	}

	dp := make([]int, amount+1)
	parent := make([]int, amount+1)

	for i := 0; i <= amount; i++ {
		dp[i] = amount + 1
		parent[i] = -1
	}
	dp[0] = 0

	for currAmount := 1; currAmount <= amount; currAmount++ {
		for _, coin := range coins {
			if coin <= currAmount && dp[currAmount-coin]+1 < dp[currAmount] {
				dp[currAmount] = dp[currAmount-coin] + 1
				parent[currAmount] = coin
			}
		}
	}

	if dp[amount] > amount {
		return CoinChangeResult{Count: -1, Coins: []int{}}
	}

	// 构造最优解
	coinsUsed := []int{}
	curr := amount
	for curr > 0 {
		coin := parent[curr]
		coinsUsed = append(coinsUsed, coin)
		curr -= coin
	}

	return CoinChangeResult{Count: dp[amount], Coins: coinsUsed}
}

func compareGreedyVsDP(coins []int, amount int) {
	greedy := CoinChangeGreedy(coins, amount)
	dp := CoinChangeDP(coins, amount)

	fmt.Printf("硬币面值: %v, 金额: %d\n", coins, amount)
	fmt.Printf("贪心: %d 枚 - %v\n", greedy.Count, greedy.Coins)
	fmt.Printf("DP:   %d 枚 - %v\n", dp.Count, dp.Coins)
	if greedy.Count != -1 && dp.Count != -1 {
		if greedy.Count == dp.Count {
			fmt.Println("✓ 贪心在本例最优")
		} else {
			fmt.Printf("✗ 贪心非最优（差值: %d）\n", greedy.Count-dp.Count)
		}
	}
	fmt.Println()
}

func testStandardCoins() {
	fmt.Println("\n[测试1] 美元硬币（贪心最优）")
	result := CoinChangeGreedy([]int{1, 5, 10, 25}, 41)
	fmt.Printf("硬币面值: [1, 5, 10, 25], 金额: 41\n")
	fmt.Printf("结果: %d 枚 - %v\n", result.Count, result.Coins)
}

func testGreedyFails1() {
	fmt.Println("\n[测试2] 贪心失败案例")
	compareGreedyVsDP([]int{1, 3, 4}, 6)
}

func testGreedyFails2() {
	fmt.Println("\n[测试3] 另一个贪心失败案例")
	compareGreedyVsDP([]int{1, 7, 10}, 11)
}

func testGreedyOptimal() {
	fmt.Println("\n[测试4] 贪心最优案例")
	compareGreedyVsDP([]int{1, 5, 10, 25}, 30)
}

func testImpossibleAmount() {
	fmt.Println("\n[测试5] 无法凑成（无1分硬币）")
	result := CoinChangeGreedy([]int{5, 10, 25}, 11)
	fmt.Printf("硬币面值: [5, 10, 25], 金额: 11\n")
	fmt.Printf("结果: %d（无法凑成）\n", result.Count)
}

func testZeroAmount() {
	fmt.Println("\n[测试6] 金额为0")
	result := CoinChangeGreedy([]int{1, 5, 10}, 0)
	fmt.Printf("硬币面值: [1, 5, 10], 金额: 0\n")
	fmt.Printf("结果: %d 枚\n", result.Count)
}

func testSingleCoinType() {
	fmt.Println("\n[测试7] 单一硬币类型")
	compareGreedyVsDP([]int{7}, 21)
}

func testLargeAmount() {
	fmt.Println("\n[测试8] 大金额")
	result := CoinChangeGreedy([]int{1, 5, 10, 25, 50}, 158)
	fmt.Printf("硬币面值: [1, 5, 10, 25, 50], 金额: 158\n")
	fmt.Printf("结果: %d 枚\n", result.Count)
	if result.Count > 0 && result.Count <= 10 {
		fmt.Printf("使用的硬币: %v\n", result.Coins)
	}
}

func testNonStandardCoins() {
	fmt.Println("\n[测试9] 非标准硬币体系贪心失败")
	compareGreedyVsDP([]int{1, 3, 4, 5}, 13)
}

func testEdgeCase() {
	fmt.Println("\n[测试10] 更大面值问题")
	compareGreedyVsDP([]int{2, 5, 10}, 11)
}

func main() {
	fmt.Println("==================================================")
	fmt.Println("零钱兑换问题 - 贪心与动态规划对比 (Go)")
	fmt.Println("==================================================")

	testStandardCoins()
	testGreedyFails1()
	testGreedyFails2()
	testGreedyOptimal()
	testImpossibleAmount()
	testZeroAmount()
	testSingleCoinType()
	testLargeAmount()
	testNonStandardCoins()
	testEdgeCase()
}
