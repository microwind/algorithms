/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import "fmt"

/**
 * @desc 新建数组，两两比较移动指针实现已排序数组合并
 */
func merge(one []int, two []int) []int {
	var oneLen = len(one)
	var twoLen = len(two)
	// 新建一个空数组，用来保存排序后的结果
	var result = make([]int, oneLen+twoLen)
	// i是第一个数组下标
	i := 0
	// j是第二个数组下标
	j := 0
	// k是新数组下标
	k := 0
	// 第一步：遍历两个数组，比较并合并较小的元素
	for i < oneLen && j < twoLen {
		// 比较两个数组的最小项，将小的项添加到空数组中
		// 小项指针后移一位，继续比较最小项，直到一个数组完成
		if one[i] < two[j] {
			result[k] = one[i]
			k++
			i++
		} else {
			result[k] = two[j]
			k++
			j++
		}
	}
	// 第二步：复制剩余的第一个数组项
	for i < oneLen {
		result[k] = one[i]
		k++
		i++
	}
	// 第三步：复制剩余的第二个数组项
	for j < twoLen {
		result[k] = two[j]
		k++
		j++
	}
	return result
}

func merge_sort(arr []int) []int {
	// 第一步：递归终止条件
	if len(arr) <= 1 {
		return arr
	}
	// 第二步：分割数组，一分为二
	mid := (len(arr)) / 2
	// 第三步：递归排序左右子数组
	left := merge_sort(arr[:mid])
	right := merge_sort(arr[mid:])
	// 第四步：合并两个已排序数组
	return merge(left, right)
}

func main() {
	var arr1 = []int{7, 11, 9, 10, 12, 13, 8}
	var arr2 = []int{-27, 4, 9, 120, 122, 13, 8, 4, 0, 20}
	fmt.Println("merge_sort arr1:")
	fmt.Println(merge_sort(arr1))

	fmt.Println("merge_sort arr2:")
	fmt.Println(merge_sort(arr2))
}

/*
jarry@jarrys-MacBook-Pro mergesort % go run merge_sort.go
merge_sort arr1:
[7 8 9 10 11 12 13]
merge_sort arr2:
[-27 0 4 4 8 9 13 20 120 122]
*/
