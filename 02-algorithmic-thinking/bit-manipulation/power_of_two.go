package main

import (
	"fmt"
)

/*
 * 2的幂 - 位运算和数字性质
 *
 * 问题：
 * 1. 检查一个数是否是2的幂
 * 2. 计算2的幂相关的位操作
 *
 * 核心思想：
 * - 2的幂在二进制表示中只有一个1（1, 2, 4, 8, 16, ...）
 * - n & (n-1) == 0 可以判断是否为2的幂
 * - 利用位运算的性质进行快速计算
 *
 * 时间复杂度: O(1)
 * 空间复杂度: O(1)
 */

// 判断一个数是否是2的幂
//
// 原理：
// - 2的幂的二进制表示只有一个1，其余为0
// - 例如：8 = 1000 (二进制)
// - n-1 = 0111 (二进制)
// - n & (n-1) = 0
func IsPowerOfTwo(n int) bool {
	return n > 0 && (n&(n-1)) == 0
}

// 使用位计数判断（备选方案）
func IsPowerOfTwoBuiltin(n int) bool {
	if n <= 0 {
		return false
	}

	count := 0
	for n > 0 {
		count += n & 1
		n >>= 1
	}
	return count == 1
}

// 计算2的幂中的位置（幂的指数）
func PowerOfTwoExponent(n int) int {
	if !IsPowerOfTwo(n) {
		return -1
	}

	exp := 0
	for (n & 1) == 0 {
		n >>= 1
		exp++
	}
	return exp
}

// 找到大于等于n的最小2的幂
func NextPowerOfTwo(n int) int {
	if n <= 1 {
		return 1
	}

	// 如果已经是2的幂，直接返回
	if IsPowerOfTwo(n) {
		return n
	}

	// 找到下一个2的幂
	n--
	n |= n >> 1
	n |= n >> 2
	n |= n >> 4
	n |= n >> 8
	n |= n >> 16
	return n + 1
}

// 获取一个2的幂是2的几次方
func GetExponent(n int) int {
	if !IsPowerOfTwo(n) {
		return -1
	}

	exp := 0
	for (n & 1) == 0 {
		exp++
		n >>= 1
	}
	return exp
}

// 打印二进制表示
func printBinary(n int) {
	fmt.Printf("0b")
	for i := 15; i >= 0; i-- {
		fmt.Printf("%d", (n>>i)&1)
	}
}

// 测试函数
func main() {
	fmt.Println("=== 2的幂 ===\n")

	// 测试用例1：判断是否为2的幂
	fmt.Println("1. 判断是否为2的幂:")
	testNums := []int{1, 2, 3, 4, 5, 8, 16, 17, 32, 100}

	for _, num := range testNums {
		if IsPowerOfTwo(num) {
			fmt.Printf("  %3d: 是2的幂\n", num)
		} else {
			fmt.Printf("  %3d: 不是2的幂\n", num)
		}
	}
	fmt.Println()

	// 测试用例2：获取幂的指数
	fmt.Println("2. 获取2的幂中的指数:")
	powerNums := []int{1, 2, 4, 8, 16, 32, 64, 128, 256}

	for _, num := range powerNums {
		exp := GetExponent(num)
		fmt.Printf("  2^%d = %d\n", exp, num)
	}
	fmt.Println()

	// 测试用例3：找下一个2的幂
	fmt.Println("3. 找大于等于n的最小2的幂:")
	testNums2 := []int{1, 3, 5, 7, 8, 9, 15, 16, 17, 100}

	for _, num := range testNums2 {
		next := NextPowerOfTwo(num)
		fmt.Printf("  n=%3d -> %d\n", num, next)
	}
	fmt.Println()

	// 测试用例4：边界情况
	fmt.Println("4. 边界情况:")
	if IsPowerOfTwo(0) {
		fmt.Println("  0 是2的幂: 是")
	} else {
		fmt.Println("  0 是2的幂: 否")
	}
	if IsPowerOfTwo(1) {
		fmt.Println("  1 是2的幂: 是")
	} else {
		fmt.Println("  1 是2的幂: 否")
	}
	if IsPowerOfTwo(-8) {
		fmt.Println("  -8 是2的幂: 是")
	} else {
		fmt.Println("  -8 是2的幂: 否")
	}
	fmt.Println()

	// 测试用例5：二进制表示
	fmt.Println("5. 2的幂的二进制表示:")
	for i := 0; i <= 4; i++ {
		num := 1 << uint(i)
		fmt.Printf("  2^%d = %2d = ", i, num)
		printBinary(num)
		fmt.Println()
	}
}
