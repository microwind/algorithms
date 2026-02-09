package main

import (
	"fmt"
)

/*
 * 单数问题 - 使用XOR技巧找到单个数字
 *
 * 问题：给定一个整数数组，其中除了一个元素出现一次外，
 * 其他元素都出现两次。找到只出现一次的那个元素。
 *
 * 核心思想：
 * - XOR 的性质：a ^ a = 0, a ^ 0 = a
 * - 对所有元素进行XOR操作，两个相同的数会相消，留下单个数字
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */

// 使用XOR技巧找到单个数字
//
// 原理：
// - 0 ^ x = x
// - x ^ x = 0
// - XOR满足交换律和结合律
// - 对所有数字XOR，重复数字相消，留下单个数字
func SingleNumberXor(nums []int) int {
	result := 0
	for _, num := range nums {
		result ^= num
	}
	return result
}

// 使用哈希表统计频数（备选方案）
func SingleNumberHash(nums []int) int {
	count := make(map[int]int)
	for _, num := range nums {
		count[num]++
	}

	for num, cnt := range count {
		if cnt == 1 {
			return num
		}
	}

	return -1
}

// 排序后相邻比较（备选方案）
func SingleNumberSort(nums []int) int {
	// 简单的排序（使用Go标准库会更好）
	for i := 0; i < len(nums)-1; i++ {
		for j := 0; j < len(nums)-i-1; j++ {
			if nums[j] > nums[j+1] {
				nums[j], nums[j+1] = nums[j+1], nums[j]
			}
		}
	}

	for i := 0; i < len(nums)-1; i += 2 {
		if nums[i] != nums[i+1] {
			return nums[i]
		}
	}

	return nums[len(nums)-1]
}

// 测试函数
func main() {
	fmt.Println("=== 单数问题 ===\n")

	// 测试用例1：基本用例
	fmt.Println("1. 基本用例:")
	nums1 := []int{2, 2, 1}
	fmt.Printf("  数组: %v\n", nums1)
	fmt.Printf("  单数: %d\n\n", SingleNumberXor(nums1))

	// 测试用例2：较大数组
	fmt.Println("2. 较大数组:")
	nums2 := []int{4, 1, 2, 1, 2}
	fmt.Printf("  数组: %v\n", nums2)
	fmt.Printf("  单数: %d\n\n", SingleNumberXor(nums2))

	// 测试用例3：负数
	fmt.Println("3. 包含负数:")
	nums3 := []int{-1, -1, 5, 5, 3}
	fmt.Printf("  数组: %v\n", nums3)
	fmt.Printf("  单数: %d\n\n", SingleNumberXor(nums3))

	// 测试用例4：单个元素
	fmt.Println("4. 单个元素:")
	nums4 := []int{42}
	fmt.Printf("  数组: %v\n", nums4)
	fmt.Printf("  单数: %d\n\n", SingleNumberXor(nums4))

	// 性能对比
	fmt.Println("5. 不同方法的结果比较:")
	nums5 := []int{7, 7, 8, 8, 9}
	fmt.Printf("  数组: %v\n", nums5)
	fmt.Printf("  XOR方法: %d\n", SingleNumberXor(nums5))

	// 使用副本进行哈希和排序测试
	nums5Hash := make([]int, len(nums5))
	copy(nums5Hash, nums5)
	fmt.Printf("  哈希方法: %d\n", SingleNumberHash(nums5Hash))

	nums5Sort := make([]int, len(nums5))
	copy(nums5Sort, nums5)
	fmt.Printf("  排序方法: %d\n", SingleNumberSort(nums5Sort))
}
