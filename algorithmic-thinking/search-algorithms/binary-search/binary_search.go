package main

import "fmt"

// 二分搜索（Binary Search）- Go 版本
//
// 前提：切片必须按升序排序。
// 时间复杂度：O(log n)
// 空间复杂度：O(1)

// BinarySearchIterative 迭代版二分搜索
func BinarySearchIterative(arr []int, target int) int {
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

// BinarySearchRecursive 递归版二分搜索
func BinarySearchRecursive(arr []int, target, left, right int) int {
	if left > right {
		return -1
	}
	mid := left + (right-left)/2
	if arr[mid] == target {
		return mid
	} else if arr[mid] < target {
		return BinarySearchRecursive(arr, target, mid+1, right)
	}
	return BinarySearchRecursive(arr, target, left, mid-1)
}

// FindFirstOccurrence 查找第一个等于 target 的位置
func FindFirstOccurrence(arr []int, target int) int {
	left, right := 0, len(arr)-1
	result := -1
	for left <= right {
		mid := left + (right-left)/2
		if arr[mid] == target {
			result = mid
			right = mid - 1
		} else if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return result
}

// FindLastOccurrence 查找最后一个等于 target 的位置
func FindLastOccurrence(arr []int, target int) int {
	left, right := 0, len(arr)-1
	result := -1
	for left <= right {
		mid := left + (right-left)/2
		if arr[mid] == target {
			result = mid
			left = mid + 1
		} else if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return result
}

// FindInsertPosition 查找插入位置（lower bound）
func FindInsertPosition(arr []int, target int) int {
	left, right := 0, len(arr)
	for left < right {
		mid := left + (right-left)/2
		if arr[mid] < target {
			left = mid + 1
		} else {
			right = mid
		}
	}
	return left
}

func main() {
	fmt.Println("========== Binary Search (Go) ==========")
	arr := []int{1, 3, 5, 7, 9, 11, 13}
	fmt.Println("数组:", arr)
	fmt.Println("迭代查找 7 ->", BinarySearchIterative(arr, 7))
	fmt.Println("递归查找 7 ->", BinarySearchRecursive(arr, 7, 0, len(arr)-1))

	arr2 := []int{1, 3, 5, 5, 5, 7, 9}
	fmt.Println("\n数组2:", arr2)
	fmt.Println("第一个 5 的位置 ->", FindFirstOccurrence(arr2, 5))
	fmt.Println("最后一个 5 的位置 ->", FindLastOccurrence(arr2, 5))
	fmt.Println("插入 6 的位置 ->", FindInsertPosition(arr2, 6))
}

