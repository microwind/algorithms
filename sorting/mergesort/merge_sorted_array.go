/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import "fmt"

/**
 * @desc 双指针法，新建数组，两两比较移动指针实现已排序数组合并
 */
func mergeSorted1(one []int, two []int) []int {
	var oneLen = len(one)
	var twoLen = len(two)
	var result = make([]int, oneLen+twoLen)
	i := 0
	j := 0
	k := 0
	// 循环遍历两个数组，直到有1个数组项全部被比较过为止
	for i < oneLen && j < twoLen {
		// 从两个数组里逐个取出最小项来进行比较
		// 哪个更小就取出哪个添加到结果数组中去
		// 被取出最小项的数组下标右移1位，结果数组下标也同样移动1位
		// 继续进行两个数组的最小项比较，直到其中一个数组遍历完成
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

	// 如果第1个数组项有剩余，则依次复制剩余的第1个数组项
	for i < oneLen {
		result[k] = one[i]
		k++
		i++
	}

	// 如果第2个数组项有剩余，则依次复制剩余的第2个数组项
	for j < twoLen {
		result[k] = two[j]
		k++
		j++
	}

	return result
}

/**
 * @desc 逐个取出1项插入到另外1个已排序数组中去，相当于选择最小项插入到已排序数组中
 */
func mergeSorted2(one []int, two []int) []int {
	var oneLen = len(one)
	var twoLen = len(two)
	for i := 0; i < oneLen; i++ {
		for k, v := range two {
			// 如果比较项小于数组2的成员项，则插入到数组2中
			if one[i] < v {
				// 追加最后一位到数组2
				two = append(two, two[twoLen-1])
				twoLen++
				// 将数组2中k的位置整体右移1位
				copy(two[k+1:twoLen-1], two[k:twoLen-2])
				// 将比较项插入到空出的位置
				two[k] = one[i]
				break
			} else {
				// 如果全部比较完成，且数组2里面没有比它还大的，则添加到最后
				if k == twoLen-1 {
					two = append(two, one[i])
					twoLen++
					break
				}
			}
		}
	}
	return two
}

/**
 * @desc 先将两个数组合并，然后采用普通排序方式排序
 */
func mergeSorted3(one []int, two []int) []int {
	var oneLen = len(one)
	var twoLen = len(two)
	var result = make([]int, oneLen+twoLen)
	// 合并数组
	for i := range result {
		if i < oneLen {
			result[i] = one[i]
		} else {
			result[i] = two[i-oneLen]
		}
	}

	// 自第二个数组开始按照普通排序算法排序，这里采用冒泡排序
	// 前面数组已排序，从第二数组的第1项开始
	for i := oneLen; i < len(result); i++ {
		// 自后往前把当前项与前一项进行比较
		for j := i; j > 0; j-- {
			// 如果小于前面项则交换位置
			if result[j] < result[j-1] {
				result[j], result[j-1] = result[j-1], result[j]
			}
		}
	}

	return result
}

func main() {
	var arr1 = []int{-3, 7, 9, 10, 11, 15, 16}
	var arr2 = []int{-1, 5, 6, 9, 12}
	fmt.Println("mergeSorted1:")
	fmt.Println("origin:", arr1, arr2)
	fmt.Println(mergeSorted1(arr1, arr2))

	var arr2_1 = []int{-3, 7, 9, 10, 11, 15, 16}
	var arr2_2 = []int{-1, 5, 6, 9, 12}
	fmt.Println("origin:", arr2_1, arr2_2)
	fmt.Println("mergeSorted2:")
	fmt.Println(mergeSorted2(arr2_1, arr2_2))

	var arr3_1 = []int{-3, 7, 9, 10, 11, 15, 16}
	var arr3_2 = []int{-1, 5, 6, 9, 12}
	fmt.Println("origin:", arr3_1, arr3_2)
	fmt.Println("mergeSorted3:")
	fmt.Println(mergeSorted3(arr3_1, arr3_2))
}

/*
 jarry@jarrys-MacBook-Pro mergesort % go version
 go version go1.15 darwin/amd64
 jarry@jarrys-MacBook-Pro mergesort % go run merge_sorted_array.go
mergeSorted1:
origin: [-3 7 9 10 11 15 16] [-1 5 6 9 12]
[-3 -1 5 6 7 9 9 10 11 12 15 16]
origin: [-3 7 9 10 11 15 16] [-1 5 6 9 12]
mergeSorted2:
[-3 -1 5 6 7 9 9 10 11 12 15 16]
origin: [-3 7 9 10 11 15 16] [-1 5 6 9 12]
mergeSorted3:
[-3 -1 5 6 7 9 9 10 11 12 15 16]
*/
