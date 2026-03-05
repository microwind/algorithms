package main

import (
	"fmt"
	"math/rand"
	"time"
)

// 随机快速排序（Randomized QuickSort）- Go 版本
//
// 通过随机选择枢轴，降低退化为 O(n^2) 的概率。

// randomizedPartition 对 nums[left:right] 做原地分区，返回枢轴最终位置
func randomizedPartition(nums []int, left, right int) int {
	// 在 [left, right] 内随机选择一个枢轴位置
	randomIdx := left + rand.Intn(right-left+1)
	nums[randomIdx], nums[right] = nums[right], nums[randomIdx]

	pivot := nums[right]
	i := left - 1

	for j := left; j < right; j++ {
		if nums[j] <= pivot {
			i++
			nums[i], nums[j] = nums[j], nums[i]
		}
	}

	nums[i+1], nums[right] = nums[right], nums[i+1]
	return i + 1
}

// randomizedQuickSort 原地随机快速排序
func randomizedQuickSort(nums []int, left, right int) {
	if left < right {
		pivotIdx := randomizedPartition(nums, left, right)
		randomizedQuickSort(nums, left, pivotIdx-1)
		randomizedQuickSort(nums, pivotIdx+1, right)
	}
}

// randomizedSelect 平均 O(n) 查找第 k 小元素（0-based）
func randomizedSelect(nums []int, left, right, k int) int {
	if left == right {
		return nums[left]
	}
	pivotIdx := randomizedPartition(nums, left, right)
	if k == pivotIdx {
		return nums[k]
	} else if k < pivotIdx {
		return randomizedSelect(nums, left, pivotIdx-1, k)
	} else {
		return randomizedSelect(nums, pivotIdx+1, right, k)
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	fmt.Println("========== Randomized QuickSort (Go) ==========")

	arr := []int{5, 2, 8, 1, 9, 3, 7, 4, 6}
	fmt.Println("原切片:", arr)

	cpy := make([]int, len(arr))
	copy(cpy, arr)
	randomizedQuickSort(cpy, 0, len(cpy)-1)
	fmt.Println("排序后:", cpy)

	k := 3
	cpy2 := make([]int, len(arr))
	copy(cpy2, arr)
	kth := randomizedSelect(cpy2, 0, len(cpy2)-1, k)
	fmt.Printf("第 %d 小元素: %d\n", k, kth)
}

