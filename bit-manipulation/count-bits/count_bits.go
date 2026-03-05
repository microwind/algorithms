package main

import (
	"fmt"
)

/*
* 计数1位 - Hamming权重
 *
 * 问题：计算整数二进制表示中1的个数
 *
 * 核心思想：
 * - 逐位检查：与1进行AND操作
 * - Brian Kernighan算法：n & (n-1) 移除最右边的1
 * - 预计算查表法（对于频繁调用优化）
 *
 * 时间复杂度: O(log n) 或 O(1) 取决于实现方式
 * 空间复杂度: O(1)
*/

// 逐位检查：循环检查每一位
func CountOnesLoop(n uint32) int {
	count := 0
	for n > 0 {
		count += int(n & 1)
		n >>= 1
	}
	return count
}

// Brian Kernighan算法：移除最右边的1
// // 原理：
// - n & (n-1) 移除n的最右边的1
// - 重复这个操作直到n为0
// - 操作次数就是1的个数
// - 只需O(k)的时间，k是1的个数
func CountOnesKernighan(n uint32) int {
	count := 0
	for n > 0 {
		n &= n - 1  // 移除最右边的1
		count++
	}
	return count
}

// 使用查表法（用于频繁调用的优化）
func CountOnesTable(n uint32) int {
	// 预计算0-255中1的个数
	lookup := [256]int{}
	for i := 0; i < 256; i++ {
		lookup[i] = CountOnesLoop(uint32(i))
	}

	count := 0
	for n > 0 {
		count += lookup[n&0xFF]
		n >>= 8
	}
	return count
}

// 并行计数法（位操作优化）
func CountOnesParallel(n uint32) int {
	n = ((n & 0xaaaaaaaa) >> 1) + (n & 0x55555555)
	n = ((n & 0xcccccccc) >> 2) + (n & 0x33333333)
	n = ((n & 0xf0f0f0f0) >> 4) + (n & 0x0f0f0f0f)
	n = ((n & 0xff00ff00) >> 8) + (n & 0x00ff00ff)
	n = ((n & 0xffff0000) >> 16) + (n & 0x0000ffff)
	return int(n)
}

// 打印二进制表示
func printBinary(n uint32) {
	fmt.Printf("0b")
	for i := 7; i >= 0; i-- {
		fmt.Printf("%d", (n>>i)&1)
	}
}

// 测试函数
func main() {
	fmt.Println("=== 计数1位 (Hamming权重) ===\n")

	// 测试用例1：基本用例
	fmt.Println("1. 基本用例:")
	testNums := []uint32{0, 1, 3, 5, 7, 15, 31, 63, 127, 255}

	for _, num := range testNums {
		count := CountOnesLoop(num)
		fmt.Printf("  %3d ", num)
		printBinary(num)
		fmt.Printf(": %d个1\n", count)
	}
	fmt.Println()

	// 测试用例2：比较不同算法
	fmt.Println("2. 不同算法的结果比较:")
	testNums2 := []uint32{1, 7, 15, 127, 255, 1023}

	for _, num := range testNums2 {
		loop := CountOnesLoop(num)
		kern := CountOnesKernighan(num)
		table := CountOnesTable(num)
		parallel := CountOnesParallel(num)

		fmt.Printf("  n=%4d: loop=%d, kernighan=%d, table=%d, parallel=%d\n",
			num, loop, kern, table, parallel)
	}
	fmt.Println()

	// 测试用例3：大数值
	fmt.Println("3. 大数值:")
	largeNums := []uint32{
		0xFFFF,      // 2^16 - 1
		0xFFFFF,     // 2^20 - 1
		0x3FFFFFFF,  // 2^30 - 1
	}

	for _, num := range largeNums {
		count := CountOnesKernighan(num)
		fmt.Printf("  0x%08X: %d个1\n", num, count)
	}
	fmt.Println()

	// 测试用例4：稀疏1的情况（Kernighan优势明显）
	fmt.Println("4. 稀疏1的情况（Kernighan优势明显）:")
	sparseNums := []uint32{1, 2, 4, 8, 16, 32, 64, 128, 256}

	for _, num := range sparseNums {
		count := CountOnesKernighan(num)
		fmt.Printf("  %3d (2^?): %d个1\n", num, count)
	}
	fmt.Println()

	// 测试用例5：特殊值
	fmt.Println("5. 特殊值:")
	fmt.Printf("  0x00000000: %d个1\n", CountOnesLoop(0x00000000))
	fmt.Printf("  0xFFFFFFFF: %d个1\n", CountOnesLoop(0xFFFFFFFF))
	fmt.Printf("  0x80000000: %d个1\n", CountOnesLoop(0x80000000))
	fmt.Printf("  0x00000001: %d个1\n", CountOnesLoop(0x00000001))
}
