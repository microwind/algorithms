package main

import (
	"fmt"
)

/*
* 快速排序 - 分治法的高效应用
 *
 * 分治法三个步骤：
 * 1. 分解：选择一个基准元素，将数组分为三部分
 * 2. 求解：递归对左右两部分进行快速排序
 * 3. 合并：基准元素已经在最终位置，无需额外合并
 *
 * 时间复杂度: O(n log n) 平均，O(n²) 最坏
 * 空间复杂度: O(log n)
*/

// 分割函数：使用 Hoare 分割方案
func partition(arr []int, low, high int) int {
	pivot := arr[high]
	i := low - 1

	for j := low; j < high; j++ {
		if arr[j] < pivot {
			i++
			// 交换 arr[i] 和 arr[j]
			arr[i], arr[j] = arr[j], arr[i]
		}
	}

	// 交换 arr[i+1] 和 arr[high]
	arr[i+1], arr[high] = arr[high], arr[i+1]

	return i + 1
}

// 递归进行快速排序
func quickSortHelper(arr []int, low, high int) {
	if low < high {
		// 分割
		pi := partition(arr, low, high)

		// 递归排序左右两部分
		quickSortHelper(arr, low, pi-1)
		quickSortHelper(arr, pi+1, high)
	}
}

// 快速排序入口函数
func QuickSort(arr []int) {
	if len(arr) <= 1 {
		return
	}
	quickSortHelper(arr, 0, len(arr)-1)
}

// 测试函数
func main() {
	fmt.Println("=== 快速排序 ===\n")

	// 测试用例1：随机数组
	arr1 := []int{64, 34, 25, 12, 22, 11, 90}
	fmt.Printf("原数组: %v\n", arr1)
	QuickSort(arr1)
	fmt.Printf("排序后: %v\n\n", arr1)

	// 测试用例2：已排序数组
	arr2 := []int{1, 2, 3, 4, 5}
	fmt.Printf("已排序数组: %v\n", arr2)
	QuickSort(arr2)
	fmt.Printf("排序后: %v\n\n", arr2)

	// 测试用例3：反序数组
	arr3 := []int{5, 4, 3, 2, 1}
	fmt.Printf("反序数组: %v\n", arr3)
	QuickSort(arr3)
	fmt.Printf("排序后: %v\n\n", arr3)

	// 测试用例4：包含重复元素
	arr4 := []int{3, 1, 4, 1, 5, 9, 2, 6}
	fmt.Printf("包含重复: %v\n", arr4)
	QuickSort(arr4)
	fmt.Printf("排序后: %v\n", arr4)
}
