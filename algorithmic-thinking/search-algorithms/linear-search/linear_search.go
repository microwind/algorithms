package main

import "fmt"

// 线性搜索（Linear Search）- Go 版本
//
// 顺序扫描切片中的每个元素，直到找到目标或遍历结束。
// 时间复杂度：O(n)
// 空间复杂度：O(1)

// LinearSearch 查找第一个等于 target 的下标，未找到返回 -1
func LinearSearch(arr []int, target int) int {
	for i, v := range arr {
		if v == target {
			return i
		}
	}
	return -1
}

// LinearSearchAll 查找所有等于 target 的下标
func LinearSearchAll(arr []int, target int) []int {
	var indices []int
	for i, v := range arr {
		if v == target {
			indices = append(indices, i)
		}
	}
	return indices
}

func main() {
	fmt.Println("========== Linear Search (Go) ==========")
	arr := []int{5, 2, 8, 1, 9, 3, 7}
	fmt.Println("数组:", arr)
	fmt.Println("查找 8 ->", LinearSearch(arr, 8))
	fmt.Println("查找 10 ->", LinearSearch(arr, 10))

	arr2 := []int{1, 2, 3, 2, 4, 2}
	fmt.Println("数组2:", arr2)
	fmt.Println("查找所有 2 ->", LinearSearchAll(arr2, 2))
}

