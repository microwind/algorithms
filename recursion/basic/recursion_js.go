package main

import "fmt"

/**
 * 递归算法示例集合（基于JavaScript版本）
 * 包含阶乘、递归计算等示例
 */

// 阶乘递归计算（版本1）
func factorial(x int) int {
	fmt.Printf("x= %d\n", x)
	if x < 1 {
		return 0
	}
	if x == 1 {
		return 1
	}
	// 递归调用：x * (x-1) * (x-2) * ... * 1
	return x * factorial(x-1)
}

// 阶乘递归计算（版本2）
func factorial2(x int) int {
	fmt.Printf("x= %d\n", x)
	if x <= 1 {
		return x
	}
	// 递归调用：x * (x-1) * (x-2) * ... * 1
	return x * factorial2(x-1)
}

// 递归计算示例
func recursion(n int) int {
	fmt.Printf("begin: n= %d\n", n)
	if n >= 15 {
		return n
	}
	n *= 3
	// 递归调用：recursion(n + 1) + recursion(n * 2)
	return recursion(n+1) + recursion(n*2)
}

// 递归计算示例2
func recursion2(n int) int {
	fmt.Printf("begin: n= %d\n", n)
	if n >= 15 {
		return n
	}
	n *= 3
	return recursion2(n+1) - recursion2(n*2)
}

func main() {
	fmt.Println("factorial(5)", factorial(5))
	fmt.Println("recursion(1)=", recursion(1))
	fmt.Println("recursion2(1)=", recursion2(1))
}
