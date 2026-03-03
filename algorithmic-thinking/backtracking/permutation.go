package main

import (
	"fmt"
	"slices"
)

/*
使用回溯生成排列 (Go Implementation)

算法说明:
- Generate all permutations of a slice using backtracking
- Use slicing and append for building permutations
- At each recursion level, try each unused element
- Backtrack by not including the element in next recursion

Time Complexity: O(n! * n) - n! permutations, each taking O(n) to copy
Space Complexity: O(n) - recursion depth (not counting output)

示例:
    Permute([]int{1, 2, 3}) returns all 6 permutations
*/

// Permute generates all permutations of the input slice.
// Time Complexity: O(n! * n)
// Space Complexity: O(n)
func Permute(nums []int) [][]int {
	result := make([][]int, 0)
	backtrack(&result, []int{}, nums)
	return result
}

// backtrack recursively builds all permutations.
func backtrack(result *[][]int, current, remaining []int) {
	// Base case: all elements used, add copy to result
	if len(remaining) == 0 {
		*result = append(*result, append([]int{}, current...))
		return
	}

	// Try each remaining element as the next element
	for i := 0; i < len(remaining); i++ {
		// Choose: add remaining[i] to current permutation
		current = append(current, remaining[i])

		// Explore: recursively build rest of permutation
		newRemaining := make([]int, 0, len(remaining)-1)
		newRemaining = append(newRemaining, remaining[:i]...)
		newRemaining = append(newRemaining, remaining[i+1:]...)
		backtrack(result, current, newRemaining)

		// Unchoose: remove the element for backtracking
		current = current[:len(current)-1]
	}
}

// PermuteOptimized generates permutations using in-place swapping.
// More efficient as it modifies the input array instead of creating new slices.
// Time Complexity: O(n! * n)
// Space Complexity: O(n)
func PermuteOptimized(nums []int) [][]int {
	result := make([][]int, 0)
	// Make a copy to avoid modifying original
	arr := slices.Clone(nums)
	backtrackSwap(&result, arr, 0)
	return result
}

// backtrackSwap recursively builds permutations using in-place swapping.
func backtrackSwap(result *[][]int, nums []int, index int) {
	// Base case: reached end of slice
	if index == len(nums) {
		*result = append(*result, slices.Clone(nums))
		return
	}

	// Try each element from index onwards as the next element
	for i := index; i < len(nums); i++ {
		// Choose: swap elements
		nums[index], nums[i] = nums[i], nums[index]

		// Explore: permute the rest
		backtrackSwap(result, nums, index+1)

		// Unchoose: swap back
		nums[index], nums[i] = nums[i], nums[index]
	}
}

func main() {
	fmt.Println("=== Permutation Backtracking Test Cases ===\n")

	// 测试用例 1: [1, 2, 3]
	fmt.Println("Test 1: Permute([1, 2, 3])")
	result1 := Permute([]int{1, 2, 3})
	fmt.Printf("Result (count=%d):\n", len(result1))
	for _, perm := range result1 {
		fmt.Printf("  %v\n", perm)
	}
	fmt.Println()

	// 测试用例 2: [1, 2]
	fmt.Println("Test 2: Permute([1, 2])")
	result2 := Permute([]int{1, 2})
	fmt.Printf("Result (count=%d):\n", len(result2))
	for _, perm := range result2 {
		fmt.Printf("  %v\n", perm)
	}
	fmt.Println()

	// 测试用例 3: [1]
	fmt.Println("Test 3: Permute([1])")
	result3 := Permute([]int{1})
	fmt.Printf("Result (count=%d):\n", len(result3))
	for _, perm := range result3 {
		fmt.Printf("  %v\n", perm)
	}
	fmt.Println()

	// 测试用例 4: Optimized version with [1, 2, 3, 4]
	fmt.Println("Test 4: PermuteOptimized([1, 2, 3, 4])")
	result4 := PermuteOptimized([]int{1, 2, 3, 4})
	fmt.Printf("Result (count=%d):\n", len(result4))
	fmt.Println("First 3 permutations:")
	for i := 0; i < 3; i++ {
		fmt.Printf("  %v\n", result4[i])
	}
	fmt.Println("Last 3 permutations:")
	for i := len(result4) - 3; i < len(result4); i++ {
		fmt.Printf("  %v\n", result4[i])
	}
	fmt.Println()

	// 测试用例 5: [10, 20, 30]
	fmt.Println("Test 5: PermuteOptimized([10, 20, 30])")
	result5 := PermuteOptimized([]int{10, 20, 30})
	fmt.Printf("Result (count=%d):\n", len(result5))
	for _, perm := range result5 {
		fmt.Printf("  %v\n", perm)
	}
}
