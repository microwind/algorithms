/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */
package main

import (
	"fmt"
	"math"
	"time"
)

/**
 * linearSearch - 线性查找 - O(n)
 *
 * 算法原理：
 * 1. 从数组开头逐个遍历元素
 * 2. 比较当前元素是否等于目标值
 * 3. 找到目标则返回索引，否则继续
 * 4. 遍历结束未找到则返回-1
 *
 * 适用场景：
 * - 小规模数据集
 * - 无序数据
 * - 需要查找所有匹配项
 *
 * @param {[]int} arr - 待搜索数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func linearSearch(arr []int, target int) int {
	for i := 0; i < len(arr); i++ {
		if arr[i] == target {
			return i
		}
	}
	return -1
}

/**
 * binarySearch - 二分查找 - O(log n)，要求数组有序
 *
 * 算法原理：
 * 1. 初始化左右边界：left=0, right=len(arr)-1
 * 2. 计算中间位置：mid = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 *
 * @param {[]int} arr - 有序数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func binarySearch(arr []int, target int) int {
	left := 0
	right := len(arr) - 1

	for left <= right {
		mid := (left + right) / 2
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

/**
 * jumpSearch - 跳跃查找 - O(√n)，要求数组有序
 *
 * 算法原理：
 * 1. 计算跳跃步长：step = sqrt(n)
 * 2. 按步长跳跃查找目标所在的块
 * 3. 在目标块内进行线性查找
 * 4. 结合跳跃和线性查找的优势
 *
 * @param {[]int} arr - 有序数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func jumpSearch(arr []int, target int) int {
	n := len(arr)
	step := int(math.Sqrt(float64(n)))

	// 找到目标所在的块
	prev := 0
	for arr[min(step, n)-1] < target {
		prev = step
		step += int(math.Sqrt(float64(n)))
		if prev >= n {
			return -1
		}
	}

	// 在线性搜索目标
	for arr[prev] < target {
		prev += 1
		if prev == min(step, n) {
			return -1
		}
	}

	if arr[prev] == target {
		return prev
	}
	return -1
}

/**
 * exponentialSearch - 指数查找 - O(log n)，要求数组有序
 *
 * 算法原理：
 * 1. 指数增长确定查找范围
 * 2. 在确定范围内进行二分查找
 * 3. 结合指数增长和二分查找的优势
 *
 * @param {[]int} arr - 有序数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func exponentialSearch(arr []int, target int) int {
	n := len(arr)

	// 如果目标在第一个位置
	if arr[0] == target {
		return 0
	}

	// 找到范围
	bound := 1
	for bound < n && arr[bound] <= target {
		bound *= 2
	}

	// 在该范围内进行二分查找
	left := bound / 2
	right := min(bound, n-1)

	for left <= right {
		mid := (left + right) / 2
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

/**
 * interpolationSearch - 插值查找 - O(log log n)，要求数组均匀分布
 *
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 *
 * @param {[]int} arr - 有序数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func interpolationSearch(arr []int, target int) int {
	low := 0
	high := len(arr) - 1

	for low <= high && target >= arr[low] && target <= arr[high] {
		if low == high {
			if arr[low] == target {
				return low
			}
			return -1
		}

		// 防止除零错误
		if arr[high] == arr[low] {
			break
		}

		// 计算插值位置
		pos := low + (target-arr[low])*(high-low)/(arr[high]-arr[low])

		// 检查计算的位置是否有效
		if pos < low || pos > high {
			break
		}

		if arr[pos] == target {
			return pos
		}

		if arr[pos] < target {
			low = pos + 1
		} else {
			high = pos - 1
		}
	}

	return -1
}

/**
 * hashSearch - 哈希查找 - O(1)，需要额外空间
 *
 * 算法原理：
 * 1. 构建哈希表存储所有元素
 * 2. 通过哈希函数计算目标位置
 * 3. 直接访问对应位置
 *
 * @param {[]int} arr - 待搜索数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
func hashSearch(arr []int, target int) int {
	// 构建哈希表
	hashTable := make(map[int]int)
	for i, val := range arr {
		hashTable[val] = i
	}

	if result, exists := hashTable[target]; exists {
		return result
	}
	return -1
}

/**
 * testAlgorithms - 测试所有搜索算法的性能
 *
 * @param {[]int} arr - 有序数组
 * @param {[]int} unsortedArr - 无序数组
 * @param {int} target - 目标值
 */
func testAlgorithms(arr []int, unsortedArr []int, target int) {
	fmt.Printf("\n数组大小: %d", len(arr))
	fmt.Printf("\n查找目标: %d", target)

	fmt.Println("\n有序数组搜索算法对比:")
	fmt.Println("------------------------------------------------------------")

	// 二分查找
	startTime := time.Now()
	result := binarySearch(arr, target)
	elapsedTime := time.Since(startTime)
	fmt.Printf("二分查找:     索引=%d, 时间=%vms\n", result, elapsedTime.Milliseconds())

	// 跳跃查找
	startTime = time.Now()
	result = jumpSearch(arr, target)
	elapsedTime = time.Since(startTime)
	fmt.Printf("跳跃查找:     索引=%d, 时间=%vms\n", result, elapsedTime.Milliseconds())

	// 指数查找
	startTime = time.Now()
	result = exponentialSearch(arr, target)
	elapsedTime = time.Since(startTime)
	fmt.Printf("指数查找:     索引=%d, 时间=%vms\n", result, elapsedTime.Milliseconds())

	// 插值查找
	startTime = time.Now()
	result = interpolationSearch(arr, target)
	elapsedTime = time.Since(startTime)
	fmt.Printf("插值查找:     索引=%d, 时间=%vms\n", result, elapsedTime.Milliseconds())

	// 哈希查找
	startTime = time.Now()
	result = hashSearch(arr, target)
	elapsedTime = time.Since(startTime)
	fmt.Printf("哈希查找:     索引=%d, 时间=%vms\n", result, elapsedTime.Milliseconds())

	fmt.Println("\n无序数组搜索:")
	fmt.Println("------------------------------------------------------------")

	// 线性查找（无序数组）
	startTime = time.Now()
	result = linearSearch(unsortedArr, target)
	elapsedTime = time.Since(startTime)
	fmt.Printf("线性查找:     索引=%d, 时间=%vms\n", result, elapsedTime.Milliseconds())
}

/**
 * printAlgorithmSummary - 打印算法复杂度总结
 */
func printAlgorithmSummary() {
	fmt.Println("\n\n算法复杂度总结:")
	fmt.Println("  线性查找:     O(n) - 无需预处理")
	fmt.Println("  二分查找:     O(log n) - 需要有序")
	fmt.Println("  跳跃查找:     O(√n) - 需要有序")
	fmt.Println("  指数查找:     O(log n) - 需要有序")
	fmt.Println("  插值查找:     O(log log n) - 需要均匀分布")
	fmt.Println("  哈希查找:     O(1) - 需要额外空间")

	fmt.Println("\n适用场景建议:")
	fmt.Println("  • 小规模无序数据: 线性查找")
	fmt.Println("  • 大规模有序数据: 二分查找")
	fmt.Println("  • 均匀分布数据: 插值查找")
	fmt.Println("  • 频繁查找操作: 哈希查找")
	fmt.Println("  • 静态数据集合: 跳跃查找/指数查找")
}

/**
 * 主程序：演示搜索算法综合对比
 */
func main() {
	fmt.Println("============================================================")
	fmt.Println("搜索算法综合对比")
	fmt.Println("============================================================")

	// 创建测试数据
	n := 10000
	sortedArr := make([]int, n)
	unsortedArr := make([]int, n)

	for i := 0; i < n; i++ {
		sortedArr[i] = i
		unsortedArr[i] = n - 1 - i // 逆序
	}

	target := 9999

	// 测试所有算法
	testAlgorithms(sortedArr, unsortedArr, target)

	// 打印总结
	printAlgorithmSummary()
}

// 辅助函数
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

/*
打印结果
jarry@Mac search-comparison % go run search_comparison.go
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999
有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0ms
跳跃查找:     索引=9999, 时间=0ms
指数查找:     索引=9999, 时间=0ms
插值查找:     索引=9999, 时间=0ms
哈希查找:     索引=9999, 时间=1ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=0, 时间=0ms


算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
*/
