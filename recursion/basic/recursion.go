package main

import "fmt"

/**
 * 递归算法示例集合
 * 包含阶乘、递归计算、尾递归等示例
 */

// 阶乘递归计算
func factorial(x int) int {
	fmt.Printf("\nx=%d", x)
	if x < 1 {
		return x
	}
	if x == 1 {
		return x
	}
	// 递归调用：x * (x-1) * (x-2) * ... * 1
	return x * factorial(x-1)
}

// 阶乘递归计算（改进版）
func factorial2(x int) int {
	fmt.Printf("\nx=%d", x)
	if x <= 1 {
		return x
	}
	// 递归调用：x * (x-1) * (x-2) * ... * 1
	return x * factorial2(x-1)
}

// 递归计算示例
func recursion(n int) int {
	fmt.Printf("\nbegin: n=%d", n)
	if n >= 15 {
		return n
	}
	n *= 3
	return recursion(n+1) + recursion(n*2)
}

// 尾递归示例（单一递归调用，无后续操作）
func tailRecursion(n int, accumulator int) int {
	if n >= 15 {
		return accumulator + n // 终止时直接返回结果
	}
	return tailRecursion(n*3+1, accumulator) // 最后一步仅递归调用
}

// 递归计算示例2
func recursion2(n int) int {
	fmt.Printf("\nbegin: n=%d", n)
	if n >= 15 {
		return n
	}
	n *= 3
	return recursion2(n+1) - recursion2(n*2)
}

func main() {
	fmt.Printf("\r\nfactorial(5) %d", factorial(5))
	fmt.Println("\r\n===")
	fmt.Printf("\r\nfactorial2(5) %d", factorial2(5))
	fmt.Println("\r\n===")
	fmt.Printf("\r\nrecursion(1) %d", recursion(1))
	fmt.Println("\r\n===")
	fmt.Printf("\r\nrecursion2(1) %d", recursion2(1))
}
