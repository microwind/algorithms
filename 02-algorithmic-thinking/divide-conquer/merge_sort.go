package main

import (
	"fmt"
)

/*
 * 归并排序 - 分治法的典型应用
 *
 * 分治法三个步骤：
 * 1. 分解：将数组分成两个子数组
 * 2. 求解：递归对子数组进行归并排序
 * 3. 合并：将两个已排序的子数组合并
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
 */

// 合并两个已排序的数组
func merge(arr []int, left, mid, right int) {
	// 创建临时数组
	temp := make([]int, right-left+1)

	i := left
	j := mid + 1
	k := 0

	// 比较两个子数组的元素
	for i <= mid && j <= right {
		if arr[i] <= arr[j] {
			temp[k] = arr[i]
			i++
		} else {
			temp[k] = arr[j]
			j++
		}
		k++
	}

	// 复制左侧剩余元素
	for i <= mid {
		temp[k] = arr[i]
		i++
		k++
	}

	// 复制右侧剩余元素
	for j <= right {
		temp[k] = arr[j]
		j++
		k++
	}

	// 将临时数组复制回原数组
	for i, v := range temp {
		arr[left+i] = v
	}
}

// 递归进行归并排序
func mergeSortHelper(arr []int, left, right int) {
	if left < right {
		mid := left + (right-left)/2

		// 递归排序左半部分
		mergeSortHelper(arr, left, mid)

		// 递归排序右半部分
		mergeSortHelper(arr, mid+1, right)

		// 合并两个已排序的部分
		merge(arr, left, mid, right)
	}
}

// 归并排序入口函数
func MergeSort(arr []int) {
	if len(arr) <= 1 {
		return
	}
	mergeSortHelper(arr, 0, len(arr)-1)
}

// 测试函数
func main() {
	fmt.Println("=== 归并排序 ===\n")

	// 测试用例1：随机数组
	arr1 := []int{64, 34, 25, 12, 22, 11, 90}
	fmt.Printf("原数组: %v\n", arr1)
	MergeSort(arr1)
	fmt.Printf("排序后: %v\n\n", arr1)

	// 测试用例2：已排序数组
	arr2 := []int{1, 2, 3, 4, 5}
	fmt.Printf("已排序数组: %v\n", arr2)
	MergeSort(arr2)
	fmt.Printf("排序后: %v\n\n", arr2)

	// 测试用例3：反序数组
	arr3 := []int{5, 4, 3, 2, 1}
	fmt.Printf("反序数组: %v\n", arr3)
	MergeSort(arr3)
	fmt.Printf("排序后: %v\n\n", arr3)

	// 测试用例4：包含重复元素
	arr4 := []int{3, 1, 4, 1, 5, 9, 2, 6}
	fmt.Printf("包含重复: %v\n", arr4)
	MergeSort(arr4)
	fmt.Printf("排序后: %v\n", arr4)
}
