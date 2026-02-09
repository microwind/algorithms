package main

import (
	"fmt"
)

/*
 * 二分查找 - 分治法的查询应用
 *
 * 前置条件：数组必须已排序
 *
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1)
 */

// 二分查找（迭代版本）
func BinarySearch(arr []int, target int) int {
	left, right := 0, len(arr)-1

	for left <= right {
		mid := left + (right-left)/2

		if arr[mid] == target {
			return mid
		} else if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	return -1
}

// 二分查找（递归版本）
func BinarySearchRecursive(arr []int, left, right, target int) int {
	if left > right {
		return -1
	}

	mid := left + (right-left)/2

	if arr[mid] == target {
		return mid
	} else if arr[mid] < target {
		return BinarySearchRecursive(arr, mid+1, right, target)
	} else {
		return BinarySearchRecursive(arr, left, mid-1, target)
	}
}

// 查找第一个 >= target 的元素位置（左边界）
func BinarySearchLeft(arr []int, target int) int {
	left, right := 0, len(arr)-1
	result := -1

	for left <= right {
		mid := left + (right-left)/2

		if arr[mid] >= target {
			result = mid
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	return result
}

// 测试函数
func main() {
	fmt.Println("=== 二分查找 ===\n")

	arr := []int{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}
	fmt.Printf("数组: %v\n\n", arr)

	// 测试用例1：迭代版本
	fmt.Println("1. 迭代版本:")
	fmt.Printf("  查找 7: %d\n", BinarySearch(arr, 7))
	fmt.Printf("  查找 20: %d\n", BinarySearch(arr, 20))
	fmt.Println()

	// 测试用例2：递归版本
	fmt.Println("2. 递归版本:")
	fmt.Printf("  查找 9: %d\n", BinarySearchRecursive(arr, 0, len(arr)-1, 9))
	fmt.Printf("  查找 2: %d\n", BinarySearchRecursive(arr, 0, len(arr)-1, 2))
	fmt.Println()

	// 测试用例3：查找边界
	arrDup := []int{1, 2, 2, 2, 3, 4, 5, 5, 5, 6}
	fmt.Printf("3. 查找边界 (数组: %v):\n", arrDup)
	fmt.Printf("  左边界 2: %d\n", BinarySearchLeft(arrDup, 2))
	fmt.Printf("  左边界 5: %d\n", BinarySearchLeft(arrDup, 5))
	fmt.Println()

	// 测试用例4：查找不存在的元素
	fmt.Println("4. 查找不存在的元素:")
	fmt.Printf("  查找 100: %d\n", BinarySearch(arr, 100))
	fmt.Printf("  查找 0: %d\n", BinarySearch(arr, 0))
}
