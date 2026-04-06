package main

import "fmt"

/**
 * 递归算法示例集合（基于Python版本）
 * 包含阶乘、斐波那契、汉诺塔、二分查找、数组求和、字符串反转等示例
 */

// 1. 阶乘 (Factorial)
// 时间复杂度: O(n), 空间复杂度: O(n)（递归栈深度）
func factorial(n int) int {
	/* 计算 n 的阶乘 */
	if n <= 1 {
		return 1
	}
	return n * factorial(n-1)
}

// 2. 斐波那契数列
// 普通递归: 时间复杂度 O(2^n)，空间复杂度 O(n)
func fibonacci(n int) int {
	/* 计算斐波那契数列第 n 项（普通递归） */
	if n <= 1 {
		return n
	}
	return fibonacci(n-1) + fibonacci(n-2)
}

// 优化版本（记忆化）
func fibonacciMemoHelper(n int, memo map[int]int) int {
	if val, exists := memo[n]; exists {
		return val
	}
	
	if n <= 1 {
		memo[n] = n
	} else {
		memo[n] = fibonacciMemoHelper(n-1, memo) + fibonacciMemoHelper(n-2, memo)
	}
	
	return memo[n]
}

func fibonacciMemo(n int) int {
	/* 计算斐波那契数列第 n 项（带记忆化） */
	memo := make(map[int]int)
	return fibonacciMemoHelper(n, memo)
}

// 3. 汉诺塔问题
// 时间复杂度: O(2^n - 1)，空间复杂度: O(n)
func hanoi(n int, source, target, auxiliary string) {
	/*
	 * 解决汉诺塔问题
	 * 将 n 个盘子从 source 柱移动到 target 柱
	 */
	if n == 1 {
		fmt.Printf("Move disk 1 from %s to %s\n", source, target)
		return
	}
	
	// 将 n-1 个盘子从 source 移动到 auxiliary
	hanoi(n-1, source, auxiliary, target)
	
	// 将最后一个盘子从 source 移动到 target
	fmt.Printf("Move disk %d from %s to %s\n", n, source, target)
	
	// 将 n-1 个盘子从 auxiliary 移动到 target
	hanoi(n-1, auxiliary, target, source)
}

// 4. 二分查找（递归版本）
// 时间复杂度: O(log n)，空间复杂度: O(log n)
func binarySearch(arr []int, target, low, high int) int {
	/* 在排序数组中递归查找目标值 */
	if low > high {
		return -1
	}
	
	mid := (low + high) / 2
	
	if arr[mid] == target {
		return mid
	} else if arr[mid] > target {
		return binarySearch(arr, target, low, mid-1)
	} else {
		return binarySearch(arr, target, mid+1, high)
	}
}

// 5. 数组求和
// 时间复杂度: O(n)，空间复杂度: O(n)
func arraySum(arr []int, index int) int {
	/* 递归计算数组元素和 */
	if index >= len(arr) {
		return 0
	}
	return arr[index] + arraySum(arr, index+1)
}

func arraySumWrapper(arr []int) int {
	return arraySum(arr, 0)
}

// 6. 反转字符串
// 时间复杂度: O(n)，空间复杂度: O(n)
func reverseString(s string) string {
	/* 递归反转字符串 */
	if s == "" {
		return ""
	}
	return reverseString(s[1:]) + string(s[0])
}

func main() {
	fmt.Println("=== 递归算法测试 ===\n")
	
	// 测试阶乘
	fmt.Println("1. 阶乘")
	fmt.Printf("5! = %d\n", factorial(5))
	
	// 测试斐波那契
	fmt.Println("\n2. 斐波那契数列")
	fmt.Printf("fib(10) = %d\n", fibonacci(10))
	fmt.Printf("fib(10) with memo = %d\n", fibonacciMemo(10))
	
	// 测试汉诺塔
	fmt.Println("\n3. 汉诺塔问题 (n=3)")
	hanoi(3, "A", "C", "B")
	
	// 测试二分查找
	fmt.Println("\n4. 二分查找")
	arr := []int{1, 3, 5, 7, 9, 11, 13}
	fmt.Printf("查找 7: 索引 = %d\n", binarySearch(arr, 7, 0, len(arr)-1))
	
	// 测试数组求和
	fmt.Println("\n5. 数组求和")
	sumArr := []int{1, 2, 3, 4, 5}
	fmt.Printf("sum([1,2,3,4,5]) = %d\n", arraySumWrapper(sumArr))
	
	// 测试字符串反转
	fmt.Println("\n6. 字符串反转")
	fmt.Printf("reverse('hello') = %s\n", reverseString("hello"))
}
