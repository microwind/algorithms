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
func merge_sort1(one []int, two []int) []int {
	var oneLen = len(one)
	var twoLen = len(two)
	var result = make([]int, oneLen+twoLen)
	i := 0
	j := 0
	k := 0
	for i < oneLen && j < twoLen {
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

	for i < oneLen {
		result[k] = one[i]
		k++
		i++
	}

	for j < twoLen {
		result[k] = two[j]
		k++
		j++
	}
	return result
}

func main() {
	var arr1 = []int{3, 7, 9, 10, 11, 15, 16}
	var arr2 = []int{1, 5, 6, 9, 12}
	fmt.Println("merge_sort1:")
	fmt.Println(merge_sort1(arr1, arr2))
}

/*
 jarry@jarrys-MacBook-Pro bubblesort % go version
 go version go1.15 darwin/amd64
 jarry@jarrys-MacBook-Pro mergesort % go run merge_sorted_array.go
 merge_sort1:
 [1 3 5 6 7 9 9 10 11 12 15 16]
*/
