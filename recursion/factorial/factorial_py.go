package main

import "fmt"

/**
 * 阶乘递归示例
 * n! = n × (n-1) × (n-2) × ... × 1
 */

// 方法1: 递归版本
func factorialRecursive(n int) int64 {
	/* 递归计算阶乘，O(n) 时间复杂度，O(n) 空间复杂度 */
	if n <= 1 {
		return 1
	}
	return int64(n) * factorialRecursive(n-1)
}

// 方法2: 迭代版本
func factorialIterative(n int) int64 {
	/* 迭代计算阶乘，O(n) 时间复杂度，O(1) 空间复杂度 */
	var result int64 = 1
	for i := 2; i <= n; i++ {
		result *= int64(i)
	}
	return result
}

// 方法3: 尾递归
func factorialTail(n int, acc int64) int64 {
	/* 尾递归版本 */
	if n <= 1 {
		return acc
	}
	return factorialTail(n-1, int64(n)*acc)
}

func factorialTailWrapper(n int) int64 {
	return factorialTail(n, 1)
}

func main() {
	fmt.Println("=== 阶乘计算 ===\n")
	
	testValues := []int{5, 10, 20}
	
	for _, n := range testValues {
		fmt.Printf("%d! = %d\n", n, factorialRecursive(n))
		fmt.Printf("迭代版本: %d! = %d\n", n, factorialIterative(n))
		fmt.Printf("尾递归版本: %d! = %d\n", n, factorialTailWrapper(n))
		fmt.Println()
	}
}
