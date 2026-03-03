/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
  "fmt"
  "time"
)

// 非递归二分查找
func binarySearch1(arr []int, item int) int {
	left := 0
	right := len(arr) - 1

	for left <= right {
		midIndex := (left + right) / 2
		middle := arr[midIndex]

		if item > middle {
			left = midIndex + 1
		} else {
			right = midIndex - 1
		}
	}

	if left < len(arr) && arr[left] == item {
		return left
	}
	return -1
}

// 递归二分查找
func binarySearch2(arr []int, item, left, right int) int {
	if left > right {
		return -1
	}

	midIndex := (left + right) / 2
	middle := arr[midIndex]

	if middle == item {
		return midIndex
	}

	if item > middle {
		return binarySearch2(arr, item, midIndex+1, right)
	} else {
		return binarySearch2(arr, item, left, midIndex-1)
	}
}

func main() {
	arr := []int{2, 3, 8, 10, 10, 13}
	len := len(arr)

	// 测试非递归二分查找
	startTime := time.Now()
	fmt.Println("search start:")

	result := binarySearch1(arr, 3) // 1
	fmt.Printf("\nbinarySearch1(arr, 3), %d\n", result)

	result = binarySearch1(arr, 10) // 3
	fmt.Printf("\nbinarySearch1(arr, 10), %d\n", result)

	result = binarySearch1(arr, 111) // -1
	fmt.Printf("\nbinarySearch1(arr, 111), %d\n", result)

	fmt.Printf("time: %f ms.\n", float64(time.Since(startTime).Milliseconds()))

	// 测试递归二分查找
	startTime = time.Now()
	fmt.Println("search start:")

	result = binarySearch2(arr, 3, 0, len-1) // 1
	fmt.Printf("\nbinarySearch2(arr, 3), %d\n", result)

	result = binarySearch2(arr, 10, 0, len-1) // 3
	fmt.Printf("\nbinarySearch2(arr, 10), %d\n", result)

	result = binarySearch2(arr, 111, 0, len-1) // -1
	fmt.Printf("\nbinarySearch2(arr, 111), %d\n", result)

	fmt.Printf("time: %f ms.\n", float64(time.Since(startTime).Milliseconds()))
}

/*
jarry@jarrys-MacBook-Pro bucketsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro bucketsort % go run binary_search.go
*/
