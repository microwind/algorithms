package main

import (
	"fmt"
	"sort"
)

/*
* Coin Change - Greedy Approach
 *
 * Algorithm:
 * - Use greedy approach: always select the largest coin possible
 * - Keep subtracting the largest coin until amount is 0
 * - Does NOT always give optimal solution
*/

type CoinChangeResult struct {
	Count int
	Coins []int
}

// CoinChangeGreedy finds minimum coins using greedy approach (not always optimal)
func CoinChangeGreedy(coins []int, amount int) CoinChangeResult {
	if amount == 0 {
		return CoinChangeResult{Count: 0, Coins: []int{}}
	}

	// Sort coins in descending order
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

// CoinChangeDP finds minimum coins using Dynamic Programming (always optimal)
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

	// Reconstruct the solution
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

	fmt.Printf("Coins: %v, Amount: %d\n", coins, amount)
	fmt.Printf("Greedy: %d coins - %v\n", greedy.Count, greedy.Coins)
	fmt.Printf("DP:     %d coins - %v\n", dp.Count, dp.Coins)
	if greedy.Count != -1 && dp.Count != -1 {
		if greedy.Count == dp.Count {
			fmt.Println("✓ Greedy is optimal for this input")
		} else {
			fmt.Printf("✗ Greedy is suboptimal (difference: %d)\n", greedy.Count-dp.Count)
		}
	}
	fmt.Println()
}

func testStandardCoins() {
	fmt.Println("\n[Test 1] US Coins (greedy optimal)")
	result := CoinChangeGreedy([]int{1, 5, 10, 25}, 41)
	fmt.Printf("Coins: [1, 5, 10, 25], Amount: 41\n")
	fmt.Printf("Result: %d coins - %v\n", result.Count, result.Coins)
}

func testGreedyFails1() {
	fmt.Println("\n[Test 2] Greedy fails case")
	compareGreedyVsDP([]int{1, 3, 4}, 6)
}

func testGreedyFails2() {
	fmt.Println("\n[Test 3] Another greedy fails case")
	compareGreedyVsDP([]int{1, 7, 10}, 11)
}

func testGreedyOptimal() {
	fmt.Println("\n[Test 4] Greedy optimal case")
	compareGreedyVsDP([]int{1, 5, 10, 25}, 30)
}

func testImpossibleAmount() {
	fmt.Println("\n[Test 5] Impossible amount (no 1-cent coin)")
	result := CoinChangeGreedy([]int{5, 10, 25}, 11)
	fmt.Printf("Coins: [5, 10, 25], Amount: 11\n")
	fmt.Printf("Result: %d (impossible)\n", result.Count)
}

func testZeroAmount() {
	fmt.Println("\n[Test 6] Zero amount")
	result := CoinChangeGreedy([]int{1, 5, 10}, 0)
	fmt.Printf("Coins: [1, 5, 10], Amount: 0\n")
	fmt.Printf("Result: %d coins\n", result.Count)
}

func testSingleCoinType() {
	fmt.Println("\n[Test 7] Single coin type")
	compareGreedyVsDP([]int{7}, 21)
}

func testLargeAmount() {
	fmt.Println("\n[Test 8] Large amount")
	result := CoinChangeGreedy([]int{1, 5, 10, 25, 50}, 158)
	fmt.Printf("Coins: [1, 5, 10, 25, 50], Amount: 158\n")
	fmt.Printf("Result: %d coins\n", result.Count)
	if result.Count > 0 && result.Count <= 10 {
		fmt.Printf("Coins used: %v\n", result.Coins)
	}
}

func testNonStandardCoins() {
	fmt.Println("\n[Test 9] Non-standard coins where greedy fails")
	compareGreedyVsDP([]int{1, 3, 4, 5}, 13)
}

func testEdgeCase() {
	fmt.Println("\n[Test 10] Larger denomination problem")
	compareGreedyVsDP([]int{2, 5, 10}, 11)
}

func main() {
	fmt.Println("==================================================")
	fmt.Println("COIN CHANGE - Greedy vs DP Comparison (Go)")
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
