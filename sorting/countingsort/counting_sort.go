// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// CountingSort 计数排序算法实现
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

// 测试数据：包含负数和重复元素的典型数组
var testData = []int{20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80}

// CountingSort1 计数排序基础版本 - 标准实现
//
// 算法原理：
// 1. 统计每个元素出现的次数
// 2. 计算累计计数以确定元素位置
// 3. 根据累计计数将元素放到正确位置
// 4. 从后向前遍历保证稳定性
//
// 生活类比：就像统计班级学生成绩分布，
// 先统计每个分数段有多少人，然后按分数段排序
//
// 时间复杂度：O(n + k)，n为元素个数，k为数据范围
// 空间复杂度：O(k) - 需要计数数组
// 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
func countingSort1(arr []int) {
	fmt.Println("countingSort1 standard:")

	if len(arr) == 0 {
		return
	}

	// 找到最小值和最大值
	min, max := arr[0], arr[0]
	for i := 1; i < len(arr); i++ {
		if arr[i] < min {
			min = arr[i]
		}
		if arr[i] > max {
			max = arr[i]
		}
	}

	dataRange := max - min + 1

	// 创建计数数组
	count := make([]int, dataRange)

	// 统计每个元素出现的次数
	for i := 0; i < len(arr); i++ {
		count[arr[i]-min]++
	}

	// 计算累计计数
	for i := 1; i < len(count); i++ {
		count[i] += count[i-1]
	}

	// 创建输出数组
	output := make([]int, len(arr))

	// 从后向前遍历，保证稳定性
	for i := len(arr) - 1; i >= 0; i-- {
		index := arr[i] - min
		output[count[index]-1] = arr[i]
		count[index]--
	}

	// 复制回原数组
	for i := 0; i < len(arr); i++ {
		arr[i] = output[i]
	}

	fmt.Println(arr)
}

// CountingSort2 计数排序优化版本 - 内存优化
//
// 算法思路：
// 1. 直接在原数组上进行修改，减少内存使用
// 2. 使用原地排序技术
//
// 优化效果：
// - 减少额外空间使用
// - 更好的缓存性能
//
// 时间复杂度：O(n + k)
// 空间复杂度：O(k)
// 稳定性：不稳定 - 原地修改可能影响稳定性
func countingSort2(arr []int) {
	fmt.Println("countingSort2 memory optimized:")

	if len(arr) == 0 {
		return
	}

	// 找到最小值和最大值
	min, max := arr[0], arr[0]
	for i := 1; i < len(arr); i++ {
		if arr[i] < min {
			min = arr[i]
		}
		if arr[i] > max {
			max = arr[i]
		}
	}

	dataRange := max - min + 1

	// 创建计数数组
	count := make([]int, dataRange)

	// 统计每个元素出现的次数
	for i := 0; i < len(arr); i++ {
		count[arr[i]-min]++
	}

	// 直接根据计数重构数组
	index := 0
	for i := 0; i < len(count); i++ {
		for count[i] > 0 {
			arr[index] = i + min
			index++
			count[i]--
		}
	}

	fmt.Println(arr)
}

// CountingSort3 计数排序 - 负数单独处理版本
//
// 算法思路：
// 1. 专门处理包含负数的情况
// 2. 分别处理负数和正数部分
//
// 优化效果：
// - 支持负数排序
// - 保持算法稳定性
//
// 时间复杂度：O(n + k)
// 空间复杂度：O(k)
// 稳定性：稳定
func countingSort3(arr []int) {
	fmt.Println("countingSort3 negative numbers:")

	if len(arr) == 0 {
		return
	}

	// 分离正数和负数
	var negatives, positives []int
	for _, value := range arr {
		if value < 0 {
			negatives = append(negatives, value)
		} else {
			positives = append(positives, value)
		}
	}

	// 排序负数部分（转换为绝对值排序后反转）
	if len(negatives) > 0 {
		absNegatives := make([]int, len(negatives))
		for i, neg := range negatives {
			absNegatives[i] = -neg
		}

		// 使用独立的计数排序逻辑
		if len(absNegatives) > 0 {
			// 找到最小值和最大值
			minAbs, maxAbs := absNegatives[0], absNegatives[0]
			for i := 1; i < len(absNegatives); i++ {
				if absNegatives[i] < minAbs {
					minAbs = absNegatives[i]
				}
				if absNegatives[i] > maxAbs {
					maxAbs = absNegatives[i]
				}
			}

			// 创建计数数组
			absRange := maxAbs - minAbs + 1
			count := make([]int, absRange)

			// 统计每个元素出现的次数
			for i := 0; i < len(absNegatives); i++ {
				count[absNegatives[i]-minAbs]++
			}

			// 计算累计计数
			for i := 1; i < absRange; i++ {
				count[i] += count[i-1]
			}

			// 从后向前遍历，保证稳定性
			output := make([]int, len(absNegatives))
			for i := len(absNegatives) - 1; i >= 0; i-- {
				value := absNegatives[i]
				index := value - minAbs
				output[count[index]-1] = value
				count[index]--
			}

			// 反转并恢复负号
			for i := 0; i < len(output); i++ {
				negatives[i] = -output[len(output)-1-i]
			}
		}
	}

	// 排序正数部分
	if len(positives) > 0 {
		// 使用独立的计数排序逻辑
		if len(positives) > 0 {
			// 找到最小值和最大值
			minPos, maxPos := positives[0], positives[0]
			for i := 1; i < len(positives); i++ {
				if positives[i] < minPos {
					minPos = positives[i]
				}
				if positives[i] > maxPos {
					maxPos = positives[i]
				}
			}

			// 创建计数数组
			posRange := maxPos - minPos + 1
			count := make([]int, posRange)

			// 统计每个元素出现的次数
			for i := 0; i < len(positives); i++ {
				count[positives[i]-minPos]++
			}

			// 计算累计计数
			for i := 1; i < posRange; i++ {
				count[i] += count[i-1]
			}

			// 从后向前遍历，保证稳定性
			output := make([]int, len(positives))
			for i := len(positives) - 1; i >= 0; i-- {
				value := positives[i]
				index := value - minPos
				output[count[index]-1] = value
				count[index]--
			}

			// 复制回正数数组
			for i := 0; i < len(output); i++ {
				positives[i] = output[i]
			}
		}
	}

	// 合并结果
	result := append(negatives, positives...)

	// 复制回原数组
	for i, val := range result {
		arr[i] = val
	}

	fmt.Println(arr)
}

// CountingSort4 计数排序 - 桶优化版本
//
// 算法思路：
// 1. 使用桶的概念，将相近的数值分组
// 2. 减少计数数组的大小
// 3. 适合大数据范围但分布稀疏的情况
//
// 优化效果：
// - 减少内存使用
// - 提高处理稀疏数据的效率
//
// 时间复杂度：O(n + k)
// 空间复杂度：O(k)
// 稳定性：稳定
func countingSort4(arr []int) {
	fmt.Println("countingSort4 bucket optimized:")

	if len(arr) == 0 {
		return
	}

	// 找到最小值和最大值
	min, max := arr[0], arr[0]
	for i := 1; i < len(arr); i++ {
		if arr[i] < min {
			min = arr[i]
		}
		if arr[i] > max {
			max = arr[i]
		}
	}

	dataRange := max - min + 1

	// 确定桶的大小（可以调整以优化性能）
	bucketSize := 1
	if dataRange > 10 {
		bucketSize = dataRange / 10
	}
	bucketCount := (dataRange + bucketSize - 1) / bucketSize

	// 创建桶
	buckets := make([][]int, bucketCount)

	// 将元素分配到桶中
	for i := 0; i < len(arr); i++ {
		bucketIndex := (arr[i] - min) / bucketSize
		buckets[bucketIndex] = append(buckets[bucketIndex], arr[i])
	}

	// 对每个桶进行排序并合并结果
	index := 0
	for i := 0; i < bucketCount; i++ {
		if len(buckets[i]) > 0 {
			// 使用独立的计数排序逻辑对桶内元素进行排序
			bucket := buckets[i]

			// 找到桶内最小值和最大值
			minBucket, maxBucket := bucket[0], bucket[0]
			for j := 1; j < len(bucket); j++ {
				if bucket[j] < minBucket {
					minBucket = bucket[j]
				}
				if bucket[j] > maxBucket {
					maxBucket = bucket[j]
				}
			}

			// 创建计数数组
			bucketRange := maxBucket - minBucket + 1
			count := make([]int, bucketRange)

			// 统计每个元素出现的次数
			for j := 0; j < len(bucket); j++ {
				count[bucket[j]-minBucket]++
			}

			// 计算累计计数
			for j := 1; j < bucketRange; j++ {
				count[j] += count[j-1]
			}

			// 从后向前遍历，保证稳定性
			output := make([]int, len(bucket))
			for j := len(bucket) - 1; j >= 0; j-- {
				value := bucket[j]
				bucketIndex := value - minBucket
				output[count[bucketIndex]-1] = value
				count[bucketIndex]--
			}

			// 将排序后的桶内容复制回原数组
			for j := 0; j < len(output); j++ {
				arr[index] = output[j]
				index++
			}
		}
	}

	fmt.Println(arr)
}

// ==================== 算法测试和性能对比 ====================

func main() {
	// 测试1：标准版本
	performanceTest(countingSort1, testData, "标准版本")

	// 测试2：内存优化版本
	performanceTest(countingSort2, testData, "内存优化版本")

	// 测试3：负数处理版本
	performanceTest(countingSort3, testData, "负数处理版本")

	// 测试4：桶优化版本
	performanceTest(countingSort4, testData, "桶优化版本")

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 标准版本：经典实现，稳定排序")
	fmt.Println("2. 内存优化版本：原地修改，节省空间")
	fmt.Println("3. 负数处理版本：支持负数，功能完整")
	fmt.Println("4. 桶优化版本：分组处理，适合稀疏数据")
}

/*
打印结果
jarry@Mac countingsort % go run counting_sort.go
标准版本原始数组: [20 11 0 -10 9 9 6 30 11 15 13 80]
countingSort1 standard:
[-10 0 6 9 9 11 11 13 15 20 30 80]
标准版本: 0.006ms
标准版本排序结果: [-10 0 6 9 9 11 11 13 15 20 30 80]

内存优化版本原始数组: [20 11 0 -10 9 9 6 30 11 15 13 80]
countingSort2 memory optimized:
[-10 0 6 9 9 11 11 13 15 20 30 80]
内存优化版本: 0.004ms
内存优化版本排序结果: [-10 0 6 9 9 11 11 13 15 20 30 80]

负数处理版本原始数组: [20 11 0 -10 9 9 6 30 11 15 13 80]
countingSort3 negative numbers:
[-10 0 6 9 9 11 11 13 15 20 30 80]
负数处理版本: 0.006ms
负数处理版本排序结果: [-10 0 6 9 9 11 11 13 15 20 30 80]

桶优化版本原始数组: [20 11 0 -10 9 9 6 30 11 15 13 80]
countingSort4 bucket optimized:
[-10 0 6 9 9 11 11 13 15 20 30 80]
桶优化版本: 0.008ms
桶优化版本排序结果: [-10 0 6 9 9 11 11 13 15 20 30 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
