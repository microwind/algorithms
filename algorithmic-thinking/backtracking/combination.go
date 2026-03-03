package main

import (
	"fmt"
)

/*
使用回溯生成组合 (Go Implementation)

算法说明:
- 生成从1到n中选取k个元素的所有组合 (C(n,k))
- 使用回溯系统地探索所有选择
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

时间复杂度：O(C(n,k) * k)，其中C(n,k)是组合数
空间复杂度：O(k)，用于递归深度和当前组合

示例:
    Combine(4, 2) returns [
        [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
    ]
*/

// Combine generates all combinations of k elements from 1 to n.
// Time Complexity: O(C(n,k) * k)
// Space Complexity: O(k)
func Combine(n, k int) [][]int {
	result := make([][]int, 0)
	backtrack(&result, []int{}, 1, n, k)
	return result
}

// backtrack recursively builds all combinations.
func backtrack(result *[][]int, current []int, start, n, k int) {
	// 基本情况：组合已完成
	if len(current) == k {
		*result = append(*result, append([]int{}, current...))
		return
	}

	// 尝试从start到n的每个数字
	for num := start; num <= n; num++ {
		// 选择：将num添加到当前组合
		current = append(current, num)

		// 探索：构建组合的其余部分
		// 仅数字 >= num+1 以避免重复
		backtrack(result, current, num+1, n, k)

		// 取消选择：移除num以进行回溯
		current = current[:len(current)-1]
	}
}

// CombineOptimized generates combinations with early termination.
// 剪枝不可能产生k个元素的分支.
// // Time Complexity: O(C(n,k) * k)
// Space Complexity: O(k)
func CombineOptimized(n, k int) [][]int {
	result := make([][]int, 0)
	backtrackOptimized(&result, []int{}, 1, n, k)
	return result
}

// backtrackOptimized recursively builds combinations with pruning.
func backtrackOptimized(result *[][]int, current []int, start, n, k int) {
	// 基本情况：组合已完成
	if len(current) == k {
		*result = append(*result, append([]int{}, current...))
		return
	}

	// 优化：提前终止
	// Remaining slots needed: k - len(current)
	// 可用的元素：n - start + 1
	// 如果没有足够的可用元素，则停止
	remaining := k - len(current)
	available := n - start + 1
	if available < remaining {
		return
	}

	// 尝试从start到n的每个数字
	for num := start; num <= n; num++ {
		current = append(current, num)
		backtrackOptimized(result, current, num+1, n, k)
		current = current[:len(current)-1]
	}
}

func main() {
	fmt.Println("=== Combination Backtracking Test Cases ===\n")

	// 测试用例 1: Combine(4, 2)
	fmt.Println("Test 1: Combine(4, 2)")
	result1 := Combine(4, 2)
	fmt.Printf("Result (count=%d):\n", len(result1))
	for _, combo := range result1 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// 测试用例 2: Combine(3, 1)
	fmt.Println("Test 2: Combine(3, 1)")
	result2 := Combine(3, 1)
	fmt.Printf("Result (count=%d):\n", len(result2))
	for _, combo := range result2 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// 测试用例 3: Combine(3, 3)
	fmt.Println("Test 3: Combine(3, 3)")
	result3 := Combine(3, 3)
	fmt.Printf("Result (count=%d):\n", len(result3))
	for _, combo := range result3 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// 测试用例 4: Combine(5, 3)
	fmt.Println("Test 4: Combine(5, 3)")
	result4 := Combine(5, 3)
	fmt.Printf("Result (count=%d):\n", len(result4))
	for _, combo := range result4 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// 测试用例 5: CombineOptimized(6, 2)
	fmt.Println("Test 5: CombineOptimized(6, 2)")
	result5 := CombineOptimized(6, 2)
	fmt.Printf("Result (count=%d):\n", len(result5))
	for _, combo := range result5 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// 测试用例 6: CombineOptimized(5, 4)
	fmt.Println("Test 6: CombineOptimized(5, 4)")
	result6 := CombineOptimized(5, 4)
	fmt.Printf("Result (count=%d):\n", len(result6))
	for _, combo := range result6 {
		fmt.Printf("  %v\n", combo)
	}
}
