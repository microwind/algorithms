// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

// MergeSort 归并排序算法实现
// 提供五种不同的实现方式，适合不同场景和性能需求

package main

import (
	"fmt"
	"time"
)

// printArray 打印数组内容的辅助函数
func printArray(arr []int, label string) {
	fmt.Printf("%s: [%v]\n", label, arr)
}

// performanceTest 性能测试辅助函数
func performanceTest(sortFunc func([]int), arr []int, name string) {
	// 创建数组副本，避免修改原数组
	testArr := make([]int, len(arr))
	copy(testArr, arr)
	printArray(testArr, name+"原始数组")

	// 开始计时
	start := time.Now()
	sortFunc(testArr)
	duration := time.Since(start)

	fmt.Printf("%s: %.3fms\n", name, float64(duration.Nanoseconds())/1000000.0)
	printArray(testArr, name+"排序结果")
	fmt.Println() // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
var testData = []int{7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4}

// 归并排序基础版本 - 递归实现（基于slice分割）
//
// 算法原理：
// 1. 递归地将数组分成两半，直到每个子数组只有一个元素
// 2. 将两个已排序的子数组合并成一个更大的有序数组
// 3. 重复合并过程，直到最终得到一个完全有序的数组
//
// 优化效果：
// - 使用Go的slice特性，代码更简洁
// - 函数式编程风格，避免索引操作
// - 充分利用Go语言特性
//
// 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
// 空间复杂度：O(n) - 需要额外空间存储临时数组
// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
func mergeSort1(arr []int) {
	fmt.Println("mergeSort1 recursive (slice-based):")

	/**
	 * 新建数组，两两比较移动指针实现已排序数组合并
	 * @param {[]int} one - 第一个有序数组
	 * @param {[]int} two - 第二个有序数组
	 * @returns {[]int} 合并后的有序数组
	 */
	merge := func(one []int, two []int) []int {
		// 步骤1：初始化变量和数组
		// 关键点：获取两个数组的长度，预分配结果数组空间
		var oneLen = len(one)
		var twoLen = len(two)
		// 新建一个空数组，用来保存排序后的结果
		// Go特点：使用make预分配内存，提高性能
		var result = make([]int, oneLen+twoLen)

		// 步骤2：初始化指针
		// 关键点：i是第一个数组下标，j是第二个数组下标，k是新数组下标
		i := 0
		j := 0
		k := 0

		// 步骤3：遍历两个数组，比较并合并较小的元素
		// 关键点：当两个数组都还有元素时，比较当前元素并选择较小的
		for i < oneLen && j < twoLen {
			// 步骤3.1：比较两个数组的最小项
			// 关键点：将小的项添加到空数组中，小项指针后移一位
			// Go特点：简洁的条件判断和赋值
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

		// 步骤4：复制剩余的第一个数组项
		// 关键点：当第一个数组还有剩余元素时，直接复制到结果数组
		for i < oneLen {
			result[k] = one[i]
			k++
			i++
		}

		// 步骤5：复制剩余的第二个数组项
		// 关键点：当第二个数组还有剩余元素时，直接复制到结果数组
		for j < twoLen {
			result[k] = two[j]
			k++
			j++
		}

		// 步骤6：返回合并结果
		// 关键点：返回完全有序的合并数组
		return result
	}

	/**
	 * 递归归并排序函数
	 * @param {[]int} arr - 待排序数组
	 * @returns {[]int} 排序后的数组
	 */
	var mergeSort func([]int) []int
	mergeSort = func(arr []int) []int {
		// 步骤1：递归终止条件
		// 关键点：数组长度小于等于1时已经有序，直接返回
		if len(arr) <= 1 {
			return arr
		}

		// 步骤2：分割数组，一分为二
		// 关键点：使用整数除法计算中间位置
		// Go特点：slice操作简洁高效
		mid := (len(arr)) / 2

		// 步骤3：递归排序左右子数组
		// 关键点：分别对左右两部分进行递归排序
		// Go特点：使用slice分割数组，arr[:mid]左半部分，arr[mid:]右半部分
		left := mergeSort(arr[:mid])
		right := mergeSort(arr[mid:])

		// 步骤4：合并两个已排序数组
		// 关键点：将两个有序子数组合并成一个更大的有序数组
		return merge(left, right)
	}

	// 执行排序并打印结果
	result := mergeSort(arr)
	fmt.Println(result)
	printArray(arr, "排序后数组")
}

// 归并排序优化版本 - 原地合并
//
// 优化思路：
// 减少空间复杂度，尝试在原数组上进行合并操作
// 使用索引操作而不是创建新数组
//
// 优化效果：
// - 减少了内存分配
// - 提高了空间效率
//
// 时间复杂度：O(n log n)
// 空间复杂度：O(1) - 原地操作
// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
func mergeSort2(arr []int) {
	fmt.Println("mergeSort2 in-place:")

	// 原地合并两个有序子数组
	mergeInPlace := func(arr []int, left, mid, right int) {
		// 步骤1：创建临时数组存储左半部分
		// 关键点：只复制左半部分，右半部分直接在原数组上访问
		leftArr := make([]int, mid-left+1)
		copy(leftArr, arr[left:mid+1])

		// 步骤2：初始化索引指针
		// 关键点：i指向左临时数组，j指向右子数组，k指向合并位置
		i := 0       // 左数组索引
		j := mid + 1 // 右数组索引
		k := left    // 合并位置索引

		// 步骤3：合并两个有序子数组
		// 关键点：比较左右子数组的元素，选择较小的放入原数组
		for i < len(leftArr) && j <= right {
			if leftArr[i] <= arr[j] {
				arr[k] = leftArr[i]
				i++
			} else {
				arr[k] = arr[j]
				j++
			}
			k++
		}

		// 步骤4：复制左数组剩余元素
		// 关键点：右子数组的剩余元素已经在正确位置，只需处理左数组
		for i < len(leftArr) {
			arr[k] = leftArr[i]
			i++
			k++
		}
	}

	// 递归归并排序函数
	var mergeSort func([]int, int, int)
	mergeSort = func(arr []int, left, right int) {
		// 步骤1：检查递归终止条件
		// 关键点：当左边界不小于右边界时停止递归
		if left >= right {
			return
		}

		// 步骤2：计算中间位置
		// 关键点：使用整数除法计算中点，避免溢出
		mid := (left + right) / 2

		// 步骤3：递归排序左半部分
		// 关键点：处理范围 [left, mid]
		mergeSort(arr, left, mid)

		// 步骤4：递归排序右半部分
		// 关键点：处理范围 [mid+1, right]
		mergeSort(arr, mid+1, right)

		// 步骤5：合并两个有序部分
		// 关键点：将相邻的两个有序子数组合并
		mergeInPlace(arr, left, mid, right)
	}

	mergeSort(arr, 0, len(arr)-1)
	printArray(arr, "排序后数组")
}

// 归并排序 - 迭代版本
//
// 算法思路：
// 使用迭代方式代替递归，避免递归栈开销
// 从小规模合并开始，逐步扩大合并规模
//
// 优化效果：
// - 避免了递归调用的开销
// - 更好的缓存局部性
//
// 时间复杂度：O(n log n)
// 空间复杂度：O(n) - 需要临时数组
// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
func mergeSort3(arr []int) {
	fmt.Println("mergeSort3 iterative:")

	// 合并两个有序子数组
	merge := func(arr, temp []int, left, mid, right int) {
		// 步骤1：初始化索引指针
		// 关键点：i指向左子数组，j指向右子数组，k指向临时数组
		i := left    // 左子数组索引
		j := mid + 1 // 右子数组索引
		k := left    // 临时数组索引

		// 步骤2：合并到临时数组
		// 关键点：按顺序将较小的元素放入临时数组
		for i <= mid && j <= right {
			if arr[i] <= arr[j] {
				temp[k] = arr[i]
				i++
			} else {
				temp[k] = arr[j]
				j++
			}
			k++
		}

		// 步骤3：复制左子数组剩余元素
		// 关键点：左子数组可能还有未处理的元素
		for i <= mid {
			temp[k] = arr[i]
			i++
			k++
		}

		// 步骤4：复制右子数组剩余元素
		// 关键点：右子数组可能还有未处理的元素
		for j <= right {
			temp[k] = arr[j]
			j++
			k++
		}

		// 步骤5：将临时数组复制回原数组
		// 关键点：将合并结果复制回原数组的对应位置
		for i := left; i <= right; i++ {
			arr[i] = temp[i]
		}
	}

	n := len(arr)
	temp := make([]int, n)

	// 步骤1：初始化合并步长
	// 关键点：从单个元素开始，步长逐步翻倍
	for size := 1; size < n; size *= 2 {
		// 步骤2：遍历数组，合并相邻子数组
		// 关键点：每次合并两个大小为size的相邻子数组
		for left := 0; left < n-size; left += 2 * size {
			// 步骤3：计算合并范围
			// 关键点：确定左、中、右边界
			mid := left + size - 1
			right := left + 2*size - 1
			if right >= n {
				right = n - 1
			}

			// 步骤4：执行合并操作
			// 关键点：将两个有序子数组合并为一个更大的有序子数组
			merge(arr, temp, left, mid, right)
		}
	}

	printArray(arr, "排序后数组")
}

// 归并排序 - 自底向上版本
//
// 算法思路：
// 先将数组分成单个元素，然后两两合并
// 逐步扩大合并规模，直到整个数组有序
//
// 优化效果：
// - 更好的内存访问模式
// - 适合外部排序（处理大数据）
//
// 时间复杂度：O(n log n)
// 空间复杂度：O(n) - 需要临时数组
// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
func mergeSort4(arr []int) {
	fmt.Println("mergeSort4 bottom-up:")

	// 合并两个相邻的有序子数组
	merge := func(arr, temp []int, left, mid, right int) {
		// 步骤1：初始化索引指针
		// 关键点：i指向左子数组，j指向右子数组，k指向临时数组
		i := left
		j := mid
		k := left

		// 步骤2：合并两个有序子数组到临时数组
		// 关键点：按顺序将较小的元素放入临时数组
		for i < mid && j <= right {
			if arr[i] <= arr[j] {
				temp[k] = arr[i]
				i++
			} else {
				temp[k] = arr[j]
				j++
			}
			k++
		}

		// 步骤3：复制左子数组剩余元素
		// 关键点：左子数组可能还有未处理的元素
		for i < mid {
			temp[k] = arr[i]
			i++
			k++
		}

		// 步骤4：复制右子数组剩余元素
		// 关键点：右子数组可能还有未处理的元素
		for j <= right {
			temp[k] = arr[j]
			j++
			k++
		}

		// 步骤5：复制回原数组
		// 关键点：将合并结果复制回原数组的对应位置
		for i := left; i <= right; i++ {
			arr[i] = temp[i]
		}
	}

	n := len(arr)
	temp := make([]int, n)

	// 步骤1：初始化合并宽度
	// 关键点：从宽度1开始，逐步扩大合并范围
	for width := 1; width < n; width *= 2 {
		// 步骤2：按宽度遍历数组
		// 关键点：每次处理2*width大小的区间
		for i := 0; i < n; i += 2 * width {
			// 步骤3：计算当前合并区间的边界
			// 关键点：确定左、中、右边界
			left := i
			mid := i + width
			if mid > n {
				mid = n
			}
			right := i + 2*width
			if right > n {
				right = n
			}

			// 步骤4：检查是否需要合并
			// 关键点：只有当mid < right时才进行合并
			if mid < right {
				// 步骤5：执行合并操作
				// 关键点：合并 [left, mid-1] 和 [mid, right-1]
				merge(arr, temp, left, mid, right-1)
			}
		}
	}

	printArray(arr, "排序后数组")
}

// 归并排序 - 非递归合并版本
//
// 算法思路：
// 使用非递归方式进行合并操作，避免递归调用
// 通过迭代方式处理合并过程，提高内存效率
//
// 优化效果：
// - 避免递归栈开销
// - 更好的内存访问模式
// - 适合大数据处理
//
// 时间复杂度：O(n log n)
// 空间复杂度：O(n) - 需要临时数组
// 稳定性：稳定 - 合并过程中保持相等元素的相对位置
func mergeSort5(arr []int) {
	fmt.Println("mergeSort5 non-recursive merge:")

	// 非递归合并两个有序子数组
	mergeNonRecursive := func(arr, temp []int, left, mid, right int) {
		// 步骤1：初始化索引指针
		// 关键点：i指向左子数组，j指向右子数组，k指向临时数组
		i := left    // 左子数组索引
		j := mid + 1 // 右子数组索引
		k := left    // 临时数组索引

		// 步骤2：合并到临时数组
		// 关键点：按顺序合并两个有序子数组
		for i <= mid && j <= right {
			if arr[i] <= arr[j] {
				temp[k] = arr[i]
				i++
			} else {
				temp[k] = arr[j]
				j++
			}
			k++
		}

		// 步骤3：复制左子数组剩余元素
		// 关键点：左子数组可能还有未处理的元素
		for i <= mid {
			temp[k] = arr[i]
			i++
			k++
		}

		// 步骤4：复制右子数组剩余元素
		// 关键点：右子数组可能还有未处理的元素
		for j <= right {
			temp[k] = arr[j]
			j++
			k++
		}

		// 步骤5：将临时数组复制回原数组
		// 关键点：使用循环逐个复制，确保数据正确性
		// Go特点：也可以使用copy函数，但循环更直观
		for index := left; index <= right; index++ {
			arr[index] = temp[index]
		}
	}

	n := len(arr)
	if n <= 1 {
		return
	}

	// 步骤1：创建临时数组
	// 关键点：临时数组用于存储合并过程中的中间结果
	temp := make([]int, n)

	// 步骤2：非递归合并过程
	// 关键点：通过迭代方式模拟递归的合并过程
	for size := 1; size < n; size *= 2 {
		// 步骤3：处理所有相邻的子数组对
		// 关键点：每次处理两个大小为size的相邻子数组
		for left := 0; left < n-size; left += 2 * size {
			// 步骤4：计算当前合并的边界
			// 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
			mid := left + size - 1
			right := left + 2*size - 1
			if right >= n {
				right = n - 1
			}

			// 步骤5：执行非递归合并
			// 关键点：使用迭代方式合并两个有序子数组
			mergeNonRecursive(arr, temp, left, mid, right)
		}
	}

	printArray(arr, "排序后数组")
}

// ==================== 算法测试和性能对比 ====================

func main() {
	// 测试1：递归版本（基于slice分割）
	performanceTest(mergeSort1, testData, "递归版本（基于slice分割）")

	// 测试2：原地合并版本
	performanceTest(mergeSort2, testData, "原地合并版本")

	// 测试3：迭代版本
	performanceTest(mergeSort3, testData, "迭代版本")

	// 测试4：自底向上版本
	performanceTest(mergeSort4, testData, "自底向上版本")

	// 测试5：非递归合并版本
	performanceTest(mergeSort5, testData, "非递归合并版本")

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 递归版本（基于slice分割）：利用Go语言特性，代码简洁")
	fmt.Println("2. 原地版本：空间优化，减少内存使用")
	fmt.Println("3. 迭代版本：避免递归，性能稳定")
	fmt.Println("4. 底向上版本：适合大数据，外部排序")
	fmt.Println("5. 非递归合并版本：迭代合并，高效内存")
}

/*
打印结果
jarry@Mac mergesort % go run merge_sort.go
递归版本（基于slice分割）原始数组: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]
mergeSort1 recursive (slice-based):
[1 2 3 4 5 6 7 8 9 10 11 12 13]
排序后数组: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]
递归版本（基于slice分割）: 0.030ms
递归版本（基于slice分割）排序结果: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]

原地合并版本原始数组: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]
mergeSort2 in-place:
排序后数组: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]
原地合并版本: 0.005ms
原地合并版本排序结果: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]

迭代版本原始数组: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]
mergeSort3 iterative:
排序后数组: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]
迭代版本: 0.005ms
迭代版本排序结果: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]

自底向上版本原始数组: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]
mergeSort4 bottom-up:
排序后数组: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]
自底向上版本: 0.004ms
自底向上版本排序结果: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]

非递归合并版本原始数组: [[7 11 9 10 12 13 8 5 6 1 3 2 4]]
mergeSort5 non-recursive merge:
排序后数组: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]
非递归合并版本: 0.004ms
非递归合并版本排序结果: [[1 2 3 4 5 6 7 8 9 10 11 12 13]]

=== 算法对比总结 ===
1. 递归版本（基于slice分割）：利用Go语言特性，代码简洁
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
*/
