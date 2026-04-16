// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// BubbleSort 冒泡排序算法实现
// 提供四种不同的实现方式，适合不同场景和性能需求

package main

import (
	"fmt"
	"time"
)

// BubbleSort1 冒泡排序基础版本 - 从左到右
//
// 算法原理：
// 1. 外循环控制排序轮数，每轮确定一个最大值的位置
// 2. 内循环控制比较次数，避免重复比较已排序部分
// 3. 自左往右每两个进行比较，把大的交换到右侧
// 4. 重复直到所有元素排序完成
//
// 生活类比：就像水中的气泡，
// 大的气泡会慢慢浮到水面
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定 - 相等元素不会交换位置
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

// BubbleSort2 冒泡排序基础版本 - 从右到左
//
// 算法原理：
// 1. 外循环控制排序轮数，每轮确定一个最小值的位置
// 2. 内循环从右向左比较，避免重复比较已排序部分
// 3. 自右往左每两个进行比较，把小的交换到左侧
// 4. 重复直到所有元素排序完成
//
// 优化效果：
// - 降序输出：与bubbleSort1方向相反
// - 算法对比：展示不同遍历方向的实现
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定
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

// BubbleSort3 冒泡排序优化版本 - 标志优化
//
// 算法思路：
// 1. 增加一个标志，如果某一轮没有进行任何交换
// 2. 则说明当前数组已排好序，不必继续后面的遍历
// 3. 外循环增加flag条件，当数组已有序时提前终止
//
// 优化效果：
// - 提前终止：当数组已有序时提前结束
// - 减少比较：避免不必要的循环
// - 性能提升：在最好情况下达到O(n)
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定
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

// BubbleSort4 插入思想+交换排序，并非严格冒泡
//
// 算法思路：
// 1. 外循环控制排序轮数，i从1开始
// 2. 第0个元素默认为已排序
// 3. 内循环在已排序区域中查找插入位置
// 4. 如果待插入元素小于已排序区域的某个元素，则交换
//
// 优化效果：
// - 插入思想：结合插入排序的思路
// - 减少交换：只在需要时进行交换
// - 性能稳定：更适合部分有序的数据
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：不稳定 - 插入操作可能改变相对位置
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

// printArray 打印数组内容的辅助函数
func printArray(list []int, label string) {
	fmt.Printf("%s: [%v]\n", label, list)
}

// performanceTest 性能测试辅助函数
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
	// 测试数据：
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
