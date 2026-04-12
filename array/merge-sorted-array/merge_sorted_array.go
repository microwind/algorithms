/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 合并有序数组算法 - Go实现
 *
 * 算法原理：
 * 从两个数组的末尾开始向前合并。使用三个指针：
 * - i: 指向nums1有效元素的末尾
 * - j: 指向nums2的末尾
 * - k: 指向合并后数组的末尾
 *
 * 每次比较nums1[i]和nums2[j]，将较大的放到nums1[k]位置。
 * 这样可以避免覆盖nums1中未处理的元素。
 *
 * 时间复杂度：O(m+n) - m和n分别是两个数组的长度
 * 空间复杂度：O(1) - 原地合并
 */

package main

import "fmt"

// mergeSortedArray 合并两个有序数组
// 参数：
//   nums1 - 第一个数组（足够空间容纳两个数组元素）
//   m - nums1中有效元素数量
//   nums2 - 第二个数组
//   n - nums2中元素数量
func mergeSortedArray(nums1 []int, m int, nums2 []int, n int) {
	// 从末尾开始合并
	i := m - 1        // nums1有效元素末尾
	j := n - 1        // nums2末尾
	k := m + n - 1    // 合并后数组末尾

	// 当nums2还有元素时
	for j >= 0 {
		// 如果nums1还有元素且nums1[i]大于nums2[j]
		if i >= 0 && nums1[i] > nums2[j] {
			nums1[k] = nums1[i]
			i--
		} else {
			nums1[k] = nums2[j]
			j--
		}
		k--
	}
	// nums1剩余元素已经在正确位置，无需处理
}

// printArray 打印数组
func printArray(nums []int, size int) {
	fmt.Print("[")
	for i := 0; i < size; i++ {
		fmt.Print(nums[i])
		if i < size-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}

func main() {
	nums1 := []int{1, 2, 3, 0, 0, 0}
	nums2 := []int{2, 5, 6}
	m := 3
	n := 3

	fmt.Print("nums1: ")
	printArray(nums1, m)
	fmt.Print("nums2: ")
	printArray(nums2, n)

	mergeSortedArray(nums1, m, nums2, n)

	fmt.Print("合并后: ")
	printArray(nums1, m+n)
}

/*
 * 输出结果：
 * nums1: [1, 2, 3]
 * nums2: [2, 5, 6]
 * 合并后: [1, 2, 2, 3, 5, 6]
 */
