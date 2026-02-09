package main

import (
	"fmt"
)

/*
Combination Generator using Backtracking (Go Implementation)

Algorithm Explanation:
- Generate all combinations of k elements from 1 to n (C(n,k))
- Use backtracking to systematically explore all choices
- At each step, only consider elements >= current start position
- This prevents duplicate combinations
- When we've selected k elements, add to result

Time Complexity: O(C(n,k) * k) where C(n,k) is the number of combinations
Space Complexity: O(k) for recursion depth and current combination

Example:
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
	// Base case: combination is complete
	if len(current) == k {
		*result = append(*result, append([]int{}, current...))
		return
	}

	// Try each number from start to n
	for num := start; num <= n; num++ {
		// Choose: add num to current combination
		current = append(current, num)

		// Explore: build rest of combination
		// Only numbers >= num+1 to avoid duplicates
		backtrack(result, current, num+1, n, k)

		// Unchoose: remove num for backtracking
		current = current[:len(current)-1]
	}
}

// CombineOptimized generates combinations with early termination.
// Prunes branches that can't possibly yield k elements.
//
// Time Complexity: O(C(n,k) * k)
// Space Complexity: O(k)
func CombineOptimized(n, k int) [][]int {
	result := make([][]int, 0)
	backtrackOptimized(&result, []int{}, 1, n, k)
	return result
}

// backtrackOptimized recursively builds combinations with pruning.
func backtrackOptimized(result *[][]int, current []int, start, n, k int) {
	// Base case: combination is complete
	if len(current) == k {
		*result = append(*result, append([]int{}, current...))
		return
	}

	// Optimization: early termination
	// Remaining slots needed: k - len(current)
	// Elements available: n - start + 1
	// If not enough elements available, stop
	remaining := k - len(current)
	available := n - start + 1
	if available < remaining {
		return
	}

	// Try each number from start to n
	for num := start; num <= n; num++ {
		current = append(current, num)
		backtrackOptimized(result, current, num+1, n, k)
		current = current[:len(current)-1]
	}
}

func main() {
	fmt.Println("=== Combination Backtracking Test Cases ===\n")

	// Test Case 1: Combine(4, 2)
	fmt.Println("Test 1: Combine(4, 2)")
	result1 := Combine(4, 2)
	fmt.Printf("Result (count=%d):\n", len(result1))
	for _, combo := range result1 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// Test Case 2: Combine(3, 1)
	fmt.Println("Test 2: Combine(3, 1)")
	result2 := Combine(3, 1)
	fmt.Printf("Result (count=%d):\n", len(result2))
	for _, combo := range result2 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// Test Case 3: Combine(3, 3)
	fmt.Println("Test 3: Combine(3, 3)")
	result3 := Combine(3, 3)
	fmt.Printf("Result (count=%d):\n", len(result3))
	for _, combo := range result3 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// Test Case 4: Combine(5, 3)
	fmt.Println("Test 4: Combine(5, 3)")
	result4 := Combine(5, 3)
	fmt.Printf("Result (count=%d):\n", len(result4))
	for _, combo := range result4 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// Test Case 5: CombineOptimized(6, 2)
	fmt.Println("Test 5: CombineOptimized(6, 2)")
	result5 := CombineOptimized(6, 2)
	fmt.Printf("Result (count=%d):\n", len(result5))
	for _, combo := range result5 {
		fmt.Printf("  %v\n", combo)
	}
	fmt.Println()

	// Test Case 6: CombineOptimized(5, 4)
	fmt.Println("Test 6: CombineOptimized(5, 4)")
	result6 := CombineOptimized(5, 4)
	fmt.Printf("Result (count=%d):\n", len(result6))
	for _, combo := range result6 {
		fmt.Printf("  %v\n", combo)
	}
}
