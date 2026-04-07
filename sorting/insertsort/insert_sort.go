/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插入排序算法实现
 * 提供8种不同的实现方式，适合不同场景和性能需求
 */

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

// 测试数据：
var testData = []int{7, 11, 9, 10, 12, 13, 8}

// InsertSort1 插入排序基础版本 - 标准实现
//
// 算法原理：
// 1. 从第二个元素开始，将其作为"当前元素"
// 2. 将当前元素与前面已排序的元素比较
// 3. 找到合适的位置插入当前元素
// 4. 重复步骤1-3，直到所有元素都排序完成
//
// 生活类比：就像整理手中的扑克牌，
// 每次拿起一张新牌，插入到手中已排序牌的合适位置
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定 - 保持相等元素的相对位置
func insertSort1(arr []int) {
	fmt.Println("insertSort1 standard:")

	// 第一步：从第二个元素开始遍历
	for i := 1; i < len(arr); i++ {
		// 关键点：保存当前元素作为待插入元素
		current := arr[i]
		j := i - 1

		// 第二步：向前查找插入位置，同时移动元素
		for j >= 0 && arr[j] > current {
			arr[j+1] = arr[j]
			j--
		}

		// 第三步：插入当前元素
		arr[j+1] = current
	}

	fmt.Println(arr)
}

// BinarySearch 二分查找插入位置
//
// 参数：
//   arr: 数组
//   value: 待插入值
//   left: 左边界
//   right: 右边界
//
// 返回值：
//   int: 插入位置
func binarySearch(arr []int, value, left, right int) int {
	for left <= right {
		mid := left + (right-left)/2

		if arr[mid] == value {
			return mid + 1 // 插入到相同元素后面，保持稳定性
		} else if arr[mid] < value {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	return left
}

// InsertSort2 插入排序优化版本 - 二分查找插入位置
//
// 算法思路：
// 1. 使用二分查找确定插入位置，减少比较次数
// 2. 保持插入操作，但优化查找过程
//
// 优化效果：
// - 减少比较次数：从O(n)到O(log n)
// - 保持插入操作的时间复杂度
//
// 时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定
func insertSort2(arr []int) {
	fmt.Println("insertSort2 binary search:")

	// 第一步：从第二个元素开始遍历
	for i := 1; i < len(arr); i++ {
		current := arr[i]

		// 第二步：使用二分查找确定插入位置
		insertPos := binarySearch(arr, current, 0, i-1)

		// 第三步：移动元素为新元素腾出空间
		for j := i; j > insertPos; j-- {
			arr[j] = arr[j-1]
		}

		// 第四步：插入元素
		arr[insertPos] = current
	}

	fmt.Println(arr)
}

// InsertSort3 插入排序哨兵版本
//
// 算法思路：
// 1. 在数组开头添加哨兵元素，简化边界检查
// 2. 减少循环中的条件判断
// 3. 找到最小值作为哨兵并移到开头
// 4. 从第三个元素开始排序
//
// 优化效果：
// - 减少边界检查
// - 简化代码逻辑
// - 轻微的性能提升
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序（忽略哨兵）
// 稳定性：稳定
func insertSort3(arr []int) {
	fmt.Println("insertSort3 sentinel:")

	if len(arr) == 0 {
		return
	}

	// 第一步：找到最小值作为哨兵
	minIndex := 0
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[minIndex] {
			minIndex = i
		}
	}

	// 第二步：将最小值移到开头作为哨兵
	if minIndex != 0 {
		arr[0], arr[minIndex] = arr[minIndex], arr[0]
	}

	// 第三步：从第三个元素开始排序（第二个元素已经相对于哨兵有序）
	for i := 2; i < len(arr); i++ {
		current := arr[i]
		j := i

		// 向前查找插入位置（哨兵保证不会越界）
		for arr[j-1] > current {
			arr[j] = arr[j-1]
			j--
		}

		arr[j] = current
	}

	fmt.Println(arr)
}

// InsertSort4 插入排序希尔插入版本
//
// 算法思路：
// 1. 结合希尔排序的增量概念
// 2. 对不同间隔的子序列进行插入排序
// 3. 使用希尔增量序列逐步缩小间隔
// 4. 在增量子序列中进行插入排序
//
// 优化效果：
// - 更好的初始数据分布
// - 减少总的移动次数
// - 适合部分有序的数据
//
// 时间复杂度：平均O(n^1.3)，取决于增量序列
// 空间复杂度：O(1) - 原地排序
// 稳定性：不稳定 - 增量排序可能破坏稳定性
func insertSort4(arr []int) {
	fmt.Println("insertSort4 shell insertion:")

	n := len(arr)

	// 第一步：使用希尔增量序列
	for gap := n / 2; gap > 0; gap /= 2 {
		// 第二步：对每个增量进行插入排序
		for i := gap; i < n; i++ {
			current := arr[i]
			j := i

			// 第三步：在增量子序列中进行插入排序
			for j >= gap && arr[j-gap] > current {
				arr[j] = arr[j-gap]
				j -= gap
			}

			arr[j] = current
		}
	}

	fmt.Println(arr)
}

// InsertSort5 插入排序降序版本
//
// 算法思路：
// 1. 从左向右插入，将大的元素向左移动
// 2. 使用相反的比较逻辑实现降序排序
// 3. 从已排序部分的末尾开始向前查找
// 4. 找到合适位置插入当前元素
//
// 优化效果：
// - 降序输出：满足特定排序需求
// - 逻辑对比：展示不同排序方向的实现
// - 算法多样性：提供排序顺序选择
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定
func insertSort5(arr []int) {
	fmt.Println("insertSort5 descending order:")

	// 第一步：从左向右遍历，将大的元素向左移动
	for i := 0; i < len(arr); i++ {
		// 当前项为第i项
		current := arr[i]
		j := i - 1

		// 第二步：从已排序部分的末尾开始，向前查找插入位置
		for j >= 0 {
			// 当前项比已排序的内容要大，则逐个右移，空出位置
			if current > arr[j] {
				arr[j+1] = arr[j]
			} else {
				// 当小于已排序内容，则跳出循环，找到插入位置
				break
			}
			j--
		}

		// 第三步：将当前元素插入到正确位置
		arr[j+1] = current
	}

	fmt.Println(arr)
}

// InsertSort6 插入排序直接插入法 - 利用copy函数
//
// 算法思路：
// 1. 使用Go语言的copy函数进行批量元素移动
// 2. 通过isMin标志判断是否为最小值
// 3. 减少逐个移动的开销
// 4. 利用语言特性提高效率
//
// 优化效果：
// - 批量移动：使用copy提高移动效率
// - 标志优化：通过isMin减少不必要的操作
// - 语言特性：充分利用Go语言特点
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(1) - 原地排序
// 稳定性：稳定
func insertSort6(arr []int) {
	fmt.Println("insertSort6 copy function:")

	// 第一步：遍历数组，逐个处理元素
	for i, current := range arr {
		j := i - 1
		isMin := true
		fmt.Printf("i=%d j=%d current=%d arr[i]=%d arr[j+1]=%d arr[]=%v\n", i, j, current, arr[i], arr[j+1], arr)

		// 第二步：向前查找插入位置
		for j >= 0 {
			// 当前项比已排序的内容要大，则插入其后
			if current > arr[j] {
				// 将j至i全部项整体右移1位
				copy(arr[j+1:i+1], arr[j:i])
				arr[j+1] = current
				isMin = false
				break
			}
			j -= 1
		}

		// 第三步：如果当前项最小则插入到已排序的最前面
		if isMin {
			copy(arr[1:i+1], arr[0:i])
			arr[0] = current
		}
	}

	fmt.Println(arr)
}

// InsertSort7 插入排序新建数组版本 - 插入选择项
//
// 算法思路：
// 1. 新建数组，以第一个元素初始化
// 2. 遍历原数组，将每个元素插入到新数组的正确位置
// 3. 使用插入操作，保持数组有序
// 4. 返回新建的有序数组
//
// 优化效果：
// - 原数组不变：保持原数据完整性
// - 插入操作：利用语言特性简化实现
// - 逻辑清晰：分离插入和排序逻辑
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(n) - 需要新建数组
// 稳定性：稳定 - 插入操作保持相等元素相对位置
func insertSort7(arr []int) []int {
	fmt.Println("insertSort7 new array insert:")

	if len(arr) == 0 {
		return []int{}
	}

	// 第一步：新建数组，以第一个元素初始化
	newArr := []int{arr[0]}

	// 第二步：遍历原数组，从第二个元素开始
	for i := 1; i < len(arr); i++ {
		current := arr[i]
		isMax := true

		// 第三步：在新数组中查找插入位置
		for j := 0; j < len(newArr); j++ {
			fmt.Printf("i=%d j=%d arr[i]=%d newArr[j]=%d newArr=%v\n", i, j, current, newArr[j], newArr)

			// 如果当前元素小于新数组中的某个元素，则插入到该位置
			if current < newArr[j] {
				// 使用Go语言的切片插入操作
				newArr = append(newArr[:j], append([]int{current}, newArr[j:]...)...)
				isMax = false
				break
			}
		}

		// 第四步：如果当前元素最大，则插入到末尾
		if isMax {
			newArr = append(newArr, current)
		}
	}

	fmt.Printf("newArr: %v\n", newArr)
	return newArr
}

// InsertSort8 插入排序新建数组倒序遍历版本
//
// 算法思路：
// 1. 新建数组，以第一个元素初始化
// 2. 倒序遍历新数组，从后向前查找插入位置
// 3. 如果当前元素大于某个元素，则插入到该位置之后
// 4. 如果当前元素最小，则插入到开头
//
// 优化效果：
// - 倒序遍历：与正向遍历不同的实现思路
// - 新建数组：保持原数组不变
// - 插入策略：从后向前查找，优化插入位置
//
// 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
// 空间复杂度：O(n) - 需要新建数组
// 稳定性：稳定 - 插入操作保持相等元素相对位置
func insertSort8(arr []int) []int {
	fmt.Println("insertSort8 new array reverse:")

	if len(arr) == 0 {
		return []int{}
	}

	// 第一步：新建数组，以第一个元素初始化
	newArr := []int{arr[0]}

	// 第二步：遍历原数组，从第二个元素开始
	for i := 1; i < len(arr); i++ {
		current := arr[i]
		isMin := true
		newLen := len(newArr)

		// 第三步：倒序遍历新数组，从后向前查找插入位置
		for newLen > 0 {
			newLen--
			fmt.Printf("i=%d newLen=%d arr[i]=%d newArr[newLen]=%d newArr=%v\n", i, newLen, current, newArr[newLen], newArr)

			// 如果当前元素大于新数组中的某个元素，则插入到该位置之后
			if current > newArr[newLen] {
				// 插入到newLen+1位置
				newArr = append(newArr[:newLen+1], append([]int{current}, newArr[newLen+1:]...)...)
				isMin = false
				break
			}
		}

		// 第四步：如果当前元素最小，则插入到开头
		if isMin {
			newArr = append([]int{current}, newArr...)
		}
	}

	fmt.Printf("newArr: %v\n", newArr)
	return newArr
}

// ==================== 算法测试和性能对比 ====================

func main() {
	// 测试1：标准版本
	performanceTest(insertSort1, testData, "标准版本")

	// 测试2：二分查找版本
	performanceTest(insertSort2, testData, "二分查找版本")

	// 测试3：哨兵版本
	performanceTest(insertSort3, testData, "哨兵版本")

	// 测试4：希尔插入版本
	performanceTest(insertSort4, testData, "希尔插入版本")

	// 测试5：降序版本
	performanceTest(insertSort5, testData, "降序版本")

	// 测试6：copy函数版本
	performanceTest(insertSort6, testData, "Copy函数版本")

	// 测试7：新建数组插入版本
	performanceTest(func(arr []int) {
		result := insertSort7(arr)
		fmt.Println(result)
	}, testData, "新建数组插入版本")

	// 测试8：新建数组倒序遍历版本
	performanceTest(func(arr []int) {
		result := insertSort8(arr)
		fmt.Println(result)
	}, testData, "新建数组倒序版本")

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 标准版本：经典实现，易于理解")
	fmt.Println("2. 二分查找版本：优化查找，减少比较")
	fmt.Println("3. 哨兵版本：简化边界，提升性能")
	fmt.Println("4. 希尔插入版本：增量排序，混合优化")
	fmt.Println("5. 降序版本：相反逻辑，降序输出")
	fmt.Println("6. Copy函数版本：批量移动，语言特性")
	fmt.Println("7. 新建数组插入版本：原数组不变，插入操作")
	fmt.Println("8. 新建数组倒序版本：倒序遍历，不同思路")
}

/*
打印结果
jarry@Mac insertsort % go run insert_sort.go
标准版本原始数组: [7 11 9 10 12 13 8]
insertSort1 standard:
[7 8 9 10 11 12 13]
标准版本: 0.002ms
标准版本排序结果: [7 8 9 10 11 12 13]

二分查找版本原始数组: [7 11 9 10 12 13 8]
insertSort2 binary search:
[7 8 9 10 11 12 13]
二分查找版本: 0.002ms
二分查找版本排序结果: [7 8 9 10 11 12 13]

哨兵版本原始数组: [7 11 9 10 12 13 8]
insertSort3 sentinel:
[7 8 9 10 11 12 13]
哨兵版本: 0.002ms
哨兵版本排序结果: [7 8 9 10 11 12 13]

希尔插入版本原始数组: [7 11 9 10 12 13 8]
insertSort4 shell insertion:
[7 8 9 10 11 12 13]
希尔插入版本: 0.001ms
希尔插入版本排序结果: [7 8 9 10 11 12 13]

降序版本原始数组: [7 11 9 10 12 13 8]
insertSort5 descending order:
[13 12 11 10 9 8 7]
降序版本: 0.002ms
降序版本排序结果: [13 12 11 10 9 8 7]

Copy函数版本原始数组: [7 11 9 10 12 13 8]
insertSort6 copy function:
i=0 j=-1 current=7 arr[i]=7 arr[j+1]=7 arr[]=[7 11 9 10 12 13 8]
i=1 j=0 current=11 arr[i]=11 arr[j+1]=11 arr[]=[7 11 9 10 12 13 8]
i=2 j=1 current=9 arr[i]=9 arr[j+1]=9 arr[]=[7 11 9 10 12 13 8]
i=3 j=2 current=10 arr[i]=10 arr[j+1]=10 arr[]=[7 9 11 10 12 13 8]
i=4 j=3 current=12 arr[i]=12 arr[j+1]=12 arr[]=[7 9 10 11 12 13 8]
i=5 j=4 current=13 arr[i]=13 arr[j+1]=13 arr[]=[7 9 10 11 12 13 8]
i=6 j=5 current=8 arr[i]=8 arr[j+1]=8 arr[]=[7 9 10 11 12 13 8]
[7 8 9 10 11 12 13]
Copy函数版本: 0.008ms
Copy函数版本排序结果: [7 8 9 10 11 12 13]

新建数组插入版本原始数组: [7 11 9 10 12 13 8]
insertSort7 new array insert:
i=1 j=0 arr[i]=11 newArr[j]=7 newArr=[7]
i=2 j=0 arr[i]=9 newArr[j]=7 newArr=[7 11]
i=2 j=1 arr[i]=9 newArr[j]=11 newArr=[7 11]
i=3 j=0 arr[i]=10 newArr[j]=7 newArr=[7 9 11]
i=3 j=1 arr[i]=10 newArr[j]=9 newArr=[7 9 11]
i=3 j=2 arr[i]=10 newArr[j]=11 newArr=[7 9 11]
i=4 j=0 arr[i]=12 newArr[j]=7 newArr=[7 9 10 11]
i=4 j=1 arr[i]=12 newArr[j]=9 newArr=[7 9 10 11]
i=4 j=2 arr[i]=12 newArr[j]=10 newArr=[7 9 10 11]
i=4 j=3 arr[i]=12 newArr[j]=11 newArr=[7 9 10 11]
i=5 j=0 arr[i]=13 newArr[j]=7 newArr=[7 9 10 11 12]
i=5 j=1 arr[i]=13 newArr[j]=9 newArr=[7 9 10 11 12]
i=5 j=2 arr[i]=13 newArr[j]=10 newArr=[7 9 10 11 12]
i=5 j=3 arr[i]=13 newArr[j]=11 newArr=[7 9 10 11 12]
i=5 j=4 arr[i]=13 newArr[j]=12 newArr=[7 9 10 11 12]
i=6 j=0 arr[i]=8 newArr[j]=7 newArr=[7 9 10 11 12 13]
i=6 j=1 arr[i]=8 newArr[j]=9 newArr=[7 9 10 11 12 13]
newArr: [7 8 9 10 11 12 13]
[7 8 9 10 11 12 13]
新建数组插入版本: 0.102ms
新建数组插入版本排序结果: [7 11 9 10 12 13 8]

新建数组倒序版本原始数组: [7 11 9 10 12 13 8]
insertSort8 new array reverse:
i=1 newLen=0 arr[i]=11 newArr[newLen]=7 newArr=[7]
i=2 newLen=1 arr[i]=9 newArr[newLen]=11 newArr=[7 11]
i=2 newLen=0 arr[i]=9 newArr[newLen]=7 newArr=[7 11]
i=3 newLen=2 arr[i]=10 newArr[newLen]=11 newArr=[7 9 11]
i=3 newLen=1 arr[i]=10 newArr[newLen]=9 newArr=[7 9 11]
i=4 newLen=3 arr[i]=12 newArr[newLen]=11 newArr=[7 9 10 11]
i=5 newLen=4 arr[i]=13 newArr[newLen]=12 newArr=[7 9 10 11 12]
i=6 newLen=5 arr[i]=8 newArr[newLen]=13 newArr=[7 9 10 11 12 13]
i=6 newLen=4 arr[i]=8 newArr[newLen]=12 newArr=[7 9 10 11 12 13]
i=6 newLen=3 arr[i]=8 newArr[newLen]=11 newArr=[7 9 10 11 12 13]
i=6 newLen=2 arr[i]=8 newArr[newLen]=10 newArr=[7 9 10 11 12 13]
i=6 newLen=1 arr[i]=8 newArr[newLen]=9 newArr=[7 9 10 11 12 13]
i=6 newLen=0 arr[i]=8 newArr[newLen]=7 newArr=[7 9 10 11 12 13]
newArr: [7 8 9 10 11 12 13]
[7 8 9 10 11 12 13]
新建数组倒序版本: 0.034ms
新建数组倒序版本排序结果: [7 11 9 10 12 13 8]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. 二分查找版本：优化查找，减少比较
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
5. 降序版本：相反逻辑，降序输出
6. Copy函数版本：批量移动，语言特性
7. 新建数组插入版本：原数组不变，插入操作
8. 新建数组倒序版本：倒序遍历，不同思路
*/
