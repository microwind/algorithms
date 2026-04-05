// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// ShellSort 希尔排序算法实现
// 提供四种不同的实现方式，适合不同场景和性能需求

package main

import (
	"fmt"
	"time"
)

// printArray 打印数组内容的辅助函数
func printArray(arr []int, label string) {
	fmt.Printf("%s: %v\n", label, arr)
}

// performanceTest 性能测试辅助函数
func performanceTest(sortFunc func([]int), arr []int, name string) {
	// 创建数组副本，避免修改原数组
	testArr := make([]int, len(arr))
	copy(testArr, arr)
	printArray(testArr, name+"原始数组")

	// 开始计时
	startTime := time.Now()
	sortFunc(testArr)
	endTime := time.Now()

	duration := endTime.Sub(startTime)
	fmt.Printf("%s: %.3fms\n", name, float64(duration.Nanoseconds())/1000000.0)
	printArray(testArr, name+"排序结果")
	fmt.Println("") // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
var testData = []int{33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431}

/**
 * 希尔排序基础版本 - 原始Shell序列
 *
 * 算法原理：
 * 1. 选择一个增量序列，如 n/2, n/4, ..., 1
 * 2. 对每个增量进行插入排序，但只比较相距增量的元素
 * 3. 逐步减小增量，直到增量为1，此时数组基本有序
 * 4. 最后一次插入排序完成整个排序过程
 *
 * 生活类比：就像整理一副扑克牌，先按间隔几张牌进行分组整理，
 * 然后逐步缩小间隔，最后对相邻的牌进行精细整理
 *
 * 时间复杂度：平均O(n^1.3)，最坏O(n^2)，取决于增量序列
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 相距增量的元素交换可能改变相等元素的相对位置
 */
func shellSort1(arr []int) {
	fmt.Println("shellSort1 original sequence:")
	n := len(arr)

	// 原始Shell序列：n/2, n/4, ..., 1
	for gap := n / 2; gap > 0; gap /= 2 {
		// 对每个增量进行插入排序
		for i := gap; i < n; i++ {
			// 关键点：保存当前元素，与前面相距gap的元素比较
			temp := arr[i]
			j := i

			// 向前查找插入位置
			for j >= gap && arr[j-gap] > temp {
				fmt.Printf("gap=%d i=%d j-gap=%d j=%d arr=%v\n", gap, i, j-gap, j, arr)
				arr[j] = arr[j-gap]
				j -= gap
			}

			// 插入元素
			arr[j] = temp
		}
	}

	fmt.Println(arr)
}

/**
 * 希尔排序优化版本 - Knuth序列
 *
 * 算法思路：
 * 使用Knuth提出的增量序列：1, 4, 13, 40, ...
 * 公式：gap = 3 * gap + 1，然后反向递减
 *
 * 优化效果：
 * - 更好的增量序列，减少比较次数
 * - 理论上更优的时间复杂度
 *
 * 时间复杂度：平均O(n^1.25)，比原始序列更优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
func shellSort2(arr []int) {
	fmt.Println("shellSort2 Knuth sequence:")
	n := len(arr)

	// 计算初始增量（Knuth序列）
	gap := 1
	for gap < n/3 {
		gap = 3*gap + 1 // 1, 4, 13, 40, 121, ...
	}

	// 反向递减处理
	for gap > 0 {
		// 对每个增量进行插入排序
		for i := gap; i < n; i++ {
			temp := arr[i]
			j := i - gap

			// 向前查找插入位置
			for ; j >= 0 && arr[j] > temp; j-- {
				fmt.Printf("gap=%d i=%d j=%d j+gap=%d arr=%v\n", gap, i, j, j+gap, arr)
				arr[j+gap] = arr[j]
			}
			arr[j+gap] = temp
		}
		gap /= 3
	}

	fmt.Println(arr)
}

/**
 * 希尔排序 - Hibbard序列
 *
 * 算法思路：
 * 使用Hibbard序列：1, 3, 7, 15, 31, ...
 * 公式：gap = 2^k - 1
 *
 * 优化效果：
 * - 更好的增量分布
 * 理论时间复杂度为O(n^(3/2))
 *
 * 时间复杂度：平均O(n^1.5)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
func shellSort3(arr []int) {
	fmt.Println("shellSort3 Hibbard sequence:")
	n := len(arr)

	// 生成Hibbard序列
	var gaps []int
	k := 1
	for {
		gap := (1 << uint(k)) - 1 // 2^k - 1
		if gap >= n {
			break
		}
		gaps = append(gaps, gap)
		k++
	}

	// 反向使用序列
	for g := len(gaps) - 1; g >= 0; g-- {
		gap := gaps[g]

		// 对每个增量进行插入排序
		for i := gap; i < n; i++ {
			temp := arr[i]
			j := i

			// 向前查找插入位置
			for j >= gap && arr[j-gap] > temp {
				arr[j] = arr[j-gap]
				j -= gap
			}

			arr[j] = temp
		}
	}

	fmt.Println(arr)
}

/**
 * 希尔排序 - Sedgewick序列
 *
 * 算法思路：
 * 使用Sedgewick序列：1, 5, 19, 41, 109, ...
 * 结合4^k + 3*2^(k-1) + 1和9*2^k - 9*2^(k/2) + 1
 *
 * 优化效果：
 * - 最优的增量序列之一
 * - 更好的性能表现
 *
 * 时间复杂度：平均O(n^1.25)，接近最优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
func shellSort4(arr []int) {
	fmt.Println("shellSort4 Sedgewick sequence:")
	n := len(arr)

	// 生成Sedgewick序列
	// 使用简化版本：1, 5, 19, 41, 109, 209, 505, 929, 2161
	sedgewickGaps := []int{1, 5, 19, 41, 109, 209, 505, 929, 2161}
	var gaps []int
	for _, gap := range sedgewickGaps {
		if gap < n {
			gaps = append(gaps, gap)
		}
	}

	// 反向使用序列
	for g := len(gaps) - 1; g >= 0; g-- {
		gap := gaps[g]

		// 对每个增量进行插入排序
		for i := gap; i < n; i++ {
			temp := arr[i]
			j := i

			// 向前查找插入位置
			for j >= gap && arr[j-gap] > temp {
				arr[j] = arr[j-gap]
				j -= gap
			}

			arr[j] = temp
		}
	}

	fmt.Println(arr)
}

// shellSort5 递归版本（尾递归实现）
// 希尔排序 - 递归版本（尾递归实现）
//
// 算法思路：
// 递归处理增量（分组）序列，每个增量插入排序
// 增量序列采用 gap/2（希尔原始序列）
//
// 递归结构：
// - 外层尾递归：处理递减的增量序列
// - 内层循环：对每个位置进行插入排序
func shellSort5(arr []int, gap int) {
	// 递归终止条件
	if gap <= 0 {
		return
	}

	// 对当前增量（分组）进行插入排序
	n := len(arr)
	for i := gap; i < n; i++ {
		temp := arr[i]
		j := i

		// 向前查找插入位置
		for j >= gap && arr[j-gap] > temp {
			arr[j] = arr[j-gap]
			j -= gap
		}

		// 插入到对应位置
		arr[j] = temp
	}

	// 尾递归调用：递归是函数的最后操作
	shellSort5(arr, gap/2)
}

// ==================== 算法测试和性能对比 ====================

func main() {
	// 测试1：原始Shell序列
	performanceTest(shellSort1, testData, "原始Shell序列")

	// 测试2：Knuth序列
	performanceTest(shellSort2, testData, "Knuth序列")

	// 测试3：Hibbard序列
	performanceTest(shellSort3, testData, "Hibbard序列")

	// 测试4：Sedgewick序列
	performanceTest(shellSort4, testData, "Sedgewick序列")

	// 测试5：递归版本（尾递归）
	testDataCopy := make([]int, len(testData))
	copy(testDataCopy, testData)
	shellSort5(testDataCopy, len(testDataCopy)/2)
	fmt.Printf("递归版本: %v\n", testDataCopy)

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 原始Shell序列：简单实现，易于理解")
	fmt.Println("2. Knuth序列：经典优化，性能提升")
	fmt.Println("3. Hibbard序列：数学优化，理论更优")
	fmt.Println("4. Sedgewick序列：最优序列，性能最佳")
	fmt.Println("5. 递归版本：尾递归优化实现")
}

/*
打印结果
jarry@Mac shellsort % go run shell_sort.go
原始Shell序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort1 original sequence:
gap=5 i=5 j-gap=0 j=5 arr=[33 4 15 43 323454 -7 105 1235 200 87431]
gap=5 i=9 j-gap=4 j=9 arr=[-7 4 15 43 323454 33 105 1235 200 87431]
gap=2 i=5 j-gap=3 j=5 arr=[-7 4 15 43 87431 33 105 1235 200 323454]
gap=2 i=6 j-gap=4 j=6 arr=[-7 4 15 33 87431 43 105 1235 200 323454]
gap=2 i=8 j-gap=6 j=8 arr=[-7 4 15 33 105 43 87431 1235 200 323454]
gap=1 i=5 j-gap=4 j=5 arr=[-7 4 15 33 105 43 200 1235 87431 323454]
[-7 4 15 33 43 105 200 1235 87431 323454]
原始Shell序列: 0.011ms
原始Shell序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

Knuth序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort2 Knuth sequence:
gap=4 i=5 j=1 j+gap=5 arr=[33 4 15 43 323454 -7 105 1235 200 87431]
gap=4 i=5 j=0 j+gap=4 arr=[33 4 15 43 323454 4 105 1235 200 87431]
gap=1 i=1 j=0 j+gap=1 arr=[33 4 15 -7 33 4 105 1235 200 87431]
gap=1 i=2 j=1 j+gap=2 arr=[4 33 15 -7 33 4 105 1235 200 87431]
gap=1 i=3 j=2 j+gap=3 arr=[4 15 33 -7 33 4 105 1235 200 87431]
gap=1 i=3 j=1 j+gap=2 arr=[4 15 33 33 33 4 105 1235 200 87431]
gap=1 i=3 j=0 j+gap=1 arr=[4 15 15 33 33 4 105 1235 200 87431]
gap=1 i=5 j=4 j+gap=5 arr=[-7 4 15 33 33 4 105 1235 200 87431]
gap=1 i=5 j=3 j+gap=4 arr=[-7 4 15 33 33 33 105 1235 200 87431]
gap=1 i=5 j=2 j+gap=3 arr=[-7 4 15 33 33 33 105 1235 200 87431]
gap=1 i=8 j=7 j+gap=8 arr=[-7 4 4 15 33 33 105 1235 200 87431]
[-7 4 4 15 33 33 105 200 1235 87431]
Knuth序列: 0.014ms
Knuth序列排序结果: [-7 4 4 15 33 33 105 200 1235 87431]

Hibbard序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort3 Hibbard sequence:
[-7 4 15 33 43 105 200 1235 87431 323454]
Hibbard序列: 0.002ms
Hibbard序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

Sedgewick序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort4 Sedgewick sequence:
[-7 4 15 33 43 105 200 1235 87431 323454]
Sedgewick序列: 0.002ms
Sedgewick序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

递归版本: [-7 4 15 33 43 105 200 1235 87431 323454]
=== 算法对比总结 ===
1. 原始Shell序列：简单实现，易于理解
2. Knuth序列：经典优化，性能提升
3. Hibbard序列：数学优化，理论更优
4. Sedgewick序列：最优序列，性能最佳
5. 递归版本：尾递归优化实现
*/
