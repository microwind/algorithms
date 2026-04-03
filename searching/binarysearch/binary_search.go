/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */
package main

import (
	"fmt"
	"time"
)

/**
 * binarySearch1 - 标准非递归版本，传递左右区间指针
 *
 * 算法步骤：
 * 1. 初始化左右边界：left=0, right=len(arr)-1
 * 2. 计算中间位置：midIndex = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 *
 * @param {[]int} arr - 有序数组
 * @param {int} item - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func binarySearch1(arr []int, item int) int {
	left := 0
	right := len(arr) - 1
	var midIndex, middle int

	// left是左侧，right是最右侧。搜索区间长度小于1时停止
	for left <= right {
		midIndex = (left + right) / 2 // 计算中间位置
		middle = arr[midIndex]        // 获取中间值
		// 中间项等于目标项则返回下标
		if middle == item {
			return midIndex
		} else if item > middle {
			// 大于中间项折半查找右侧
			left = midIndex + 1
		} else {
			// 小于中间项折半查找左侧
			right = midIndex - 1
		}
	}
	// 此时left是最左侧目标项
	if left < len(arr) && arr[left] == item {
		return left
	}
	return -1 // 未找到
}

/**
 * binarySearch2 - 递归实现，移动左右区间指针
 *
 * 算法步骤：
 * 1. 处理边界条件
 * 2. 计算中间位置和中间值
 * 3. 比较中间值与目标值
 * 4. 根据比较结果递归查找对应半区
 * 5. 处理重复项的特殊情况
 *
 * @param {[]int} arr - 有序数组
 * @param {int} item - 目标值
 * @param {int} left - 左边界
 * @param {int} right - 右边界
 * @returns {int} 找到返回索引，未找到返回-1
 */
func binarySearch2(arr []int, item, left, right int) int {
	// 如果左侧与右侧相同，表面查找完毕，返回-1
	if left > right {
		return -1
	}

	midIndex := (left + right) / 2
	middle := arr[midIndex]

	// 中间值等于查找项说明找到了，则返回中间项下标
	if middle == item {
		// 如果有重复项，返回第一个位置
		if arr[left] == item {
			return left
		}
		return midIndex
	}

	if item > middle {
		// 折半右侧部分开始递归查找
		return binarySearch2(arr, item, midIndex+1, right)
	} else {
		// 折半左侧部分开始递归查找
		return binarySearch2(arr, item, left, midIndex-1)
	}
}

/**
 * main - 主程序：演示二分查找算法的性能对比
 *
 * 测试内容：
 * 1. binarySearch1 - 标准非递归版本
 * 2. binarySearch2 - 递归版本，处理重复项
 */
func main() {
	// 创建测试数据
	arr := []int{2, 3, 8, 10, 10, 13}
	len := len(arr)

	// 测试 binarySearch1 - 标准非递归版本
	startTime := time.Now()
	fmt.Println("search start:")

	result := binarySearch1(arr, 3) // 1
	fmt.Printf("\nbinarySearch1(arr, 3), %d\n", result)

	result = binarySearch1(arr, 10) // 3
	fmt.Printf("\nbinarySearch1(arr, 10), %d\n", result)

	result = binarySearch1(arr, 111) // -1
	fmt.Printf("\nbinarySearch1(arr, 111), %d\n", result)

	fmt.Printf("time: %f ms.\n", float64(time.Since(startTime).Milliseconds()))

	// 测试 binarySearch2 - 递归版本
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
