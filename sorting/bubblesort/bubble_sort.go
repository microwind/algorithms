/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

package main

import (
	"fmt"
	"time"
)

/**
 * 冒泡排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

func bubbleSort1(list []int) []int {
	fmt.Println("bubbleSort1 from left to right:")
	length := len(list)
	// 外循环：控制排序轮数，每轮确定一个最大值的位置
	for i := 0; i < length; i++ {
		// 内循环：控制比较次数，length-i-1 避免重复比较已排序部分
		for j := 0; j < length-i-1; j++ {
			// 关键点：自左往右每两个进行比较，把大的交换到右侧
			if list[j] > list[j+1] {
				// Go特点：使用临时变量交换
				tmp := list[j+1]
				list[j+1] = list[j]
				list[j] = tmp
			}
		}
	}
	fmt.Println(list)
	return list
}

func bubbleSort2(list []int) []int {
	fmt.Println("bubbleSort2 from right to left:")
	length := len(list)
	// 外循环：控制排序轮数，每轮确定一个最小值的位置
	for i := 0; i < length; i++ {
		// 内循环：从右向左比较，j > i 避免重复比较已排序部分
		for j := length - 1; j > i; j-- {
			// 关键点：自右往左每两个进行比较，把小的交换到右侧
			if list[j-1] < list[j] {
				// Go特点：使用临时变量交换
				tmp := list[j]
				list[j] = list[j-1]
				list[j-1] = tmp
			}
		}
	}
	fmt.Println(list)
	return list
}

func bubbleSort3(list []int) []int {
	fmt.Println("bubbleSort3 add flag:")
	// 优化点：增加一个标志，如果某一轮没有进行过任何的交换
	// 则说明当前数组已排好序，则不必继续后面的遍历
	length := len(list)
	flag := true

	// 外循环：增加 flag 条件，当数组已有序时提前终止
	for i := 0; i < length && flag == true; i++ {
		flag = false // 每轮开始时重置标志
		// 内循环：控制比较次数，length-i-1 避免重复比较已排序部分
		for j := 0; j < length-i-1; j++ {
			// 关键点：自左往右每两个进行比较，把大的交换到右侧
			if list[j] > list[j+1] {
				flag = true // 发生交换，设置标志
				// Go特点：使用临时变量交换
				tmp := list[j+1]
				list[j+1] = list[j]
				list[j] = tmp
			}
		}
	}
	fmt.Println(list)
	return list
}

func bubbleSort4(list []int) []int {
	fmt.Println("bubbleSort4:")
	length := len(list)
	// 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
	for i := 1; i < length; i++ {
		// 内循环：在已排序区域中查找插入位置
		for j := 0; j < i; j++ {
			// 关键点：如果待插入元素小于已排序区域的某个元素，则交换
			if list[j] > list[i] {
				// Go特点：使用临时变量交换
				tmp := list[i]
				list[i] = list[j]
				list[j] = tmp
			}
		}
	}
	fmt.Println(list)
	return list
}

func printArray(list []int, label string) {
	fmt.Printf("%s: [%v]\n", label, list)
}

func performanceTest(sortFunc func([]int) []int, arr []int, name string) {
	// 创建数组副本，避免修改原数组
	testArr := make([]int, len(arr))
	copy(testArr, arr)
	printArray(testArr, name+"原始数组")
	
	// 开始计时
	start := time.Now()
	sortFunc(testArr)
	elapsed := time.Since(start)
	
	printArray(testArr, name+"排序结果")
	fmt.Printf("%s: %v\n", name, elapsed)
	fmt.Println() // 空行分隔
}

func main() {
	// 测试数据：包含重复元素和无序情况的典型数组
	testData := []int{7, 11, 9, 10, 12, 13, 8}
	
	fmt.Println("=== 冒泡排序算法演示 ===\n")
	
	// 测试1：基础升序版本
	performanceTest(bubbleSort1, testData, "基础升序版本")
	
	// 测试2：基础降序版本
	performanceTest(bubbleSort2, testData, "基础降序版本")
	
	// 测试3：优化版本
	performanceTest(bubbleSort3, testData, "优化版本")
	
	// 测试4：插入式版本
	performanceTest(bubbleSort4, testData, "插入式版本")
	
	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 基础版本：简单易懂，适合学习算法原理")
	fmt.Println("2. 降序版本：展示算法的灵活性，可按需排序")
	fmt.Println("3. 优化版本：通过标志位优化，适合实际应用")
	fmt.Println("4. 插入式版本：结合其他排序思想，性能更稳定")
}

/* 打印结果
jarry@Mac bubblesort % go run bubble_sort.go
=== 冒泡排序算法演示 ===

基础升序版本原始数组: [[7 11 9 10 12 13 8]]
bubbleSort1 from left to right:
[7 8 9 10 11 12 13]
基础升序版本排序结果: [[7 8 9 10 11 12 13]]
基础升序版本: 10.xxxµs

基础降序版本原始数组: [[7 11 9 10 12 13 8]]
bubbleSort2 from right to left:
[13 12 11 10 9 8 7]
基础降序版本排序结果: [[13 12 11 10 9 8 7]]
基础降序版本: 1.xxxµs

优化版本原始数组: [[7 11 9 10 12 13 8]]
bubbleSort3 add flag:
[7 8 9 10 11 12 13]
优化版本排序结果: [[7 8 9 10 11 12 13]]
优化版本: 1.xxxµs

插入式版本原始数组: [[7 11 9 10 12 13 8]]
bubbleSort4:
[7 8 9 10 11 12 13]
插入式版本排序结果: [[7 8 9 10 11 12 13]]
插入式版本: 1.xxxµs

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
*/
