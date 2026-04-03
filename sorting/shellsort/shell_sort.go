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
			j := i
			
			// 向前查找插入位置
			for j >= gap && arr[j-gap] > temp {
				arr[j] = arr[j-gap]
				j -= gap
			}
			
			arr[j] = temp
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

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 原始Shell序列：简单实现，易于理解")
	fmt.Println("2. Knuth序列：经典优化，性能提升")
	fmt.Println("3. Hibbard序列：数学优化，理论更优")
	fmt.Println("4. Sedgewick序列：最优序列，性能最佳")
}

/*
打印结果
jarry@Mac shellsort % go run shell_sort.go
原始Shell序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort1 original sequence:
[-7 4 15 33 43 105 200 1235 87431 323454]
原始Shell序列: 0.125ms
原始Shell序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

Knuth序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort2 Knuth sequence:
[-7 4 15 33 43 105 200 1235 87431 323454]
Knuth序列: 0.042ms
Knuth序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

Hibbard序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort3 Hibbard sequence:
[-7 4 15 33 43 105 200 1235 87431 323454]
Hibbard序列: 0.042ms
Hibbard序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

Sedgewick序列原始数组: [33 4 15 43 323454 -7 105 1235 200 87431]
shellSort4 Sedgewick sequence:
[-7 4 15 33 43 105 200 1235 87431 323454]
Sedgewick序列: 0.042ms
Sedgewick序列排序结果: [-7 4 15 33 43 105 200 1235 87431 323454]

=== 算法对比总结 ===
1. 原始Shell序列：简单实现，易于理解
2. Knuth序列：经典优化，性能提升
3. Hibbard序列：数学优化，理论更优
4. Sedgewick序列：最优序列，性能最佳
*/
