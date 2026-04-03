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

// ==================== 辅助函数 ====================

/**
 * 打印数组
 *
 * 参数：
 *   - arr: 要打印的整数数组
 *   - label: 数组的标签说明
 */
func printArray(arr []int, label string) {
	fmt.Printf("%s: [", label)
	for i, v := range arr {
		if i > 0 {
			fmt.Printf(", ")
		}
		fmt.Printf("%d", v)
	}
	fmt.Printf("]\n")
}

/**
 * 性能测试函数
 *
 * 参数：
 *   - sortFunc: 排序函数，接受[]int返回[]int
 *   - arr: 测试用的原始数组
 *   - name: 测试名称，用于输出标识
 */
func performanceTest(sortFunc func([]int) []int, arr []int, name string) {
	// 创建数组副本，避免修改原数组
	testArr := make([]int, len(arr))
	copy(testArr, arr)
	printArray(testArr, name+"原始数组")

	// 开始计时并执行排序
	start := time.Now()
	sortedArr := sortFunc(testArr)
	duration := time.Since(start)

	// 输出结果
	fmt.Printf("%s: %.3fms\n", name, float64(duration.Nanoseconds())/1000000.0)
	printArray(sortedArr, name+"排序结果")
	fmt.Println() // 空行分隔
}

// ==================== 算法实现 ====================

/**
 * 快速排序1 - 递归新建数组版本
 *
 * ## 算法特点
 * - 无需交换，每个分区都是新数组
 * - 使用中间元素作为基准，避免最坏情况
 * - 内存友好：不修改原数组，返回新数组
 * - 稳定排序：保持相等元素的相对位置
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(n log n) - 递归调用栈 + 新数组空间
 * - 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @return 排序后的整数数组
 */
/**
quick_sort1 递归步骤:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([])
  [7]
*/
func quickSort1(arr []int) []int {
	// 第一步：递归终止条件
	// 关键点：数组长度<=1时已经有序，直接返回
	if len(arr) <= 1 {
		return arr
	}

	// 第二步：选择基准并分区
	fmt.Println("split array:", arr)
	left := []int{}
	right := []int{}
	// 关键点：设置中间数作为基准，避免最坏情况
	var midIndex = len(arr) / 2
	var pivot = arr[midIndex]

	// 第三步：遍历数组，按基准值分区
	for i := 0; i < len(arr); i++ {
		// 关键点：跳过基准元素本身，避免重复处理
		if midIndex == i {
			continue
		}
		// 关键点：小于基准的放左边，大于等于的放右边
		if arr[i] < pivot {
			left = append(left, arr[i])
		} else {
			right = append(right, arr[i])
		}
	}

	// 第四步：递归排序并合并
	// 关键点：先递归左数组，再添加基准，最后递归右数组
	arr = append(quickSort1(left), pivot)
	arr = append(arr, quickSort1(right)...)
	fmt.Println("sorted array:", arr)
	return arr
}

/**
 * 标准分区函数
 *
 * 关键点：
 * - 基准选择：选择右侧元素作为基准（Lomuto分区）
 * - 分区指针：partitionIndex记录小于基准区域的边界
 * - 交换策略：找到小于基准的元素就交换到左侧
 * - 基准归位：最后将基准元素放到正确位置
 *
 * @param arr 数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 基准元素的最终位置
 */
func partition(arr []int, left int, right int) int {
	// 第一步：选择基准（这里取右侧）
	var pivotIndex = right
	var pivot = arr[pivotIndex]
	var partitionIndex = left

	// 第二步：遍历数组进行分区
	for i := left; i < right; i++ {
		// 关键点：将小于基准的元素交换到左侧
		if arr[i] < pivot {
			// 关键点：只有当i不等于partitionIndex时才交换，避免不必要的交换
			if partitionIndex != i {
				arr[i], arr[partitionIndex] = arr[partitionIndex], arr[i]
			}
			partitionIndex++
		}
	}

	// 第三步：将基准放到正确位置
	arr[partitionIndex], arr[pivotIndex] = arr[pivotIndex], arr[partitionIndex]
	fmt.Println("partitioned arr=", arr, "partitionIndex:", partitionIndex,
		"left=", arr[left:partitionIndex], "arr[partitionIndex]=", arr[partitionIndex],
		"right=", arr[partitionIndex:right+1], arr)
	return partitionIndex
}

/**
 * Lomuto分区函数
 *
 * ## 算法特点
 * - 使用最后一个元素作为基准
 * - 单向扫描：从左到右扫描
 * - 分区指针：记录小于基准区域的边界
 * - 基准归位：最后将基准元素放到正确位置
 *
 * ## 复杂度分析
 * - 时间复杂度：O(n) - 单次分区时间
 * - 空间复杂度：O(1) - 原地分区
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param low 起始索引
 * @param high 结束索引
 * @return 基准元素的最终位置
 */
func partitionLomuto(arr []int, low, high int) int {
	// 第一步：初始化基准和指针
	pivot := arr[high] // 最后一个元素作为基准
	i := low - 1       // 小于基准的元素的边界

	// 第二步：遍历数组进行分区
	for j := low; j < high; j++ {
		// 关键点：将小于基准的元素交换到左侧
		if arr[j] < pivot {
			i++
			arr[i], arr[j] = arr[j], arr[i]
		}
	}

	// 第三步：将基准放到正确位置
	arr[i+1], arr[high] = arr[high], arr[i+1]
	return i + 1
}

/**
 * 快速排序2 - 标准递归版本
 *
 * ## 算法特点
 * - 左右不断分区交换，无需新建数组
 * - 使用Lomuto分区方案
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 排序后的整数数组
 */
func quickSort2(arr []int, left int, right int) []int {
	// 第一步：递归终止条件检查
	// 关键点：left < right时还需要排序，否则已经有序
	if left < right {
		// 第二步：分区并获取基准位置
		// 关键点：使用partition函数将数组分为两部分
		var pivot = partition(arr, left, right)

		// 第三步：递归排序左半部分
		// 关键点：排序基准左边的元素
		quickSort2(arr, left, pivot-1)

		// 第四步：递归排序右半部分
		// 关键点：排序基准右边的元素
		quickSort2(arr, pivot+1, right)
	}
	return arr
}

/**
 * 快速排序3 - 双向扫描递归版本
 *
 * ## 算法特点
 * - 需要左右不断交换，无需新建数组
 * - 使用中间元素作为基准
 * - 双向扫描：左右指针相向移动
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 排序后的整数数组
 */
func quickSort3(arr []int, left int, right int) []int {
	// 第一步：初始化指针和基准
	var i = left
	var j = right
	var midIndex = (i + j) / 2
	var pivot = arr[midIndex]

	// 第二步：双向扫描分区
	// 关键点：当左侧小于等于右侧则表示还有值没有对比，需要继续
	for i <= j {
		// 步骤2.1：左指针扫描，找到大于基准的元素
		// 关键点：当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
		for arr[i] < pivot {
			fmt.Println("arr[i] < pivot:", " i=", i, " j=", j, " pivot=", pivot, "arr[]=", arr)
			i++
		}
		// 步骤2.2：右指针扫描，找到小于基准的元素
		// 关键点：当前右侧大于基准时左移，直到找出比基准值小的位置来
		for arr[j] > pivot {
			fmt.Println("arr[j] > pivot:", " i=", i, " j=", j, " pivot=", pivot, "arr[]=", arr)
			j--
		}

		fmt.Println("  left=", left, " right=", right, " i=", i, " j=", j, " midIndex=", midIndex, " pivot=", pivot, " arr[]=", arr)

		// 步骤2.3：交换元素
		// 关键点：当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
		if i <= j {
			arr[i], arr[j] = arr[j], arr[i]
			// 关键点：缩小搜查范围，直到左侧都小于基数，右侧都大于基数
			i++
			j--
		}
	}

	// 第三步：递归处理左右子数组
	// 步骤3.1：递归处理左子数组
	// 关键点：左侧小于基数位置，不断递归左边部分
	if left < j {
		fmt.Println("left < j:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]", arr)
		quickSort3(arr, left, j)
	}
	// 步骤3.2：递归处理右子数组
	// 关键点：基数位置小于右侧，不断递归右侧部分
	if i < right {
		fmt.Println("i < right:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]", arr)
		quickSort3(arr, i, right)
	}

	return arr
}

/**
 * 快速排序4 - 非递归版本
 *
 * ## 算法特点
 * - 需要交换，无需新建数组，利用stack或queue遍历
 * - 使用栈模拟递归调用
 * - 避免递归深度过大导致的栈溢出
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(n) - 显式栈空间
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 排序后的整数数组
 */
func quickSort4(arr []int, left int, right int) []int {
	// 第一步：初始化栈
	// 关键点：使用数组模拟栈结构，避免递归调用
	var stack = make([]int, 0)

	// 第二步：初始入栈
	// 关键点：将整个数组的左右边界入栈，作为初始处理范围
	var midIndex int
	var pivot int
	stack = append(stack, left)
	stack = append(stack, right)

	// 第三步：循环处理栈中的范围
	// 关键点：栈不为空时继续处理，模拟递归调用过程
	for len(stack) > 0 {
		// 步骤3.1：从栈中取出待处理的范围
		// 关键点：后进先出，先取出right，再取出left
		right = stack[len(stack)-1]
		var j = right
		stack = stack[:len(stack)-1]

		left = stack[len(stack)-1]
		var i = left
		stack = stack[:len(stack)-1]

		// 步骤3.2：获取基准位置
		// 关键点：使用中间元素作为基准
		midIndex = int((i + j) / 2)
		pivot = arr[midIndex]

		// 步骤3.3：双向扫描分区
		// 关键点：左右指针相向移动，进行分区
		for i <= j {
			// 步骤3.3.1：左指针扫描，找到大于基准的元素
			// 关键点：当左侧小于基准时查找位置右移
			for arr[i] < pivot {
				fmt.Println("arr[i] < pivot:", " i=", i, " j=", j, " pivot=", pivot, "arr[]=", arr)
				i++
			}

			// 步骤3.3.2：右指针扫描，找到小于基准的元素
			// 关键点：当前右侧大于基准时左移
			for arr[j] > pivot {
				fmt.Println("arr[j] > pivot:", " i=", i, " j=", j, " pivot=", pivot, "arr[]=", arr)
				j--
			}

			// 步骤3.3.3：交换元素
			// 关键点：当左侧位置小于右侧时，将数据交换
			if i <= j {
				var tmp = arr[j]
				arr[j] = arr[i]
				arr[i] = tmp
				i++
				j--
			}
		}

		// 步骤3.4：子范围入栈
		// 关键点：将分区后的子范围重新入栈，继续处理
		if left < j {
			// 关键点：左子数组有数据，入栈待处理
			fmt.Println("left < j:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]", arr)
			stack = append(stack, left)
			stack = append(stack, j)
		}
		if i < right {
			// 关键点：右子数组有数据，入栈待处理
			fmt.Println("i < right:recursion:  left=", left, " right=", right, " i=", i, " j=", j, "arr[]", arr)
			stack = append(stack, i)
			stack = append(stack, right)
		}
	}

	return arr
}

/**
 * 快速排序5 - Lomuto分区递归版本
 *
 * ## 算法特点
 * - 使用Lomuto分区方案
 * - 最后一个元素作为基准
 * - 单向扫描：从左到右扫描
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 排序后的整数数组
 */
func quickSort5(arr []int, left int, right int) []int {
	// 第一步：递归终止条件检查
	if left >= right {
		return arr
	}

	// 第二步：获取基准位置
	var pi = partitionLomuto(arr, left, right)

	// 第三步：递归排序左右子数组
	quickSort5(arr, left, pi-1)
	quickSort5(arr, pi+1, right)

	return arr
}

/**
 * 快速排序6 - Hoare分区递归版本
 *
 * ## 算法特点
 * - 使用Hoare分区方案
 * - 第一个元素作为基准
 * - 双向扫描：左右指针相向移动
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 排序后的整数数组
 */
func quickSort6(arr []int, left int, right int) []int {
	// 第一步：递归终止条件检查
	if left >= right {
		return arr
	}

	// 第二步：初始化指针和基准
	var i = left
	var j = right
	var pivot = arr[left] // 第一个元素作为基准

	// 第三步：双向扫描分区
	for i <= j {
		// 左指针：找到大于基准的元素
		for arr[i] < pivot {
			i++
		}

		// 右指针：找到小于基准的元素
		for arr[j] > pivot {
			j--
		}

		// 交换元素
		if i <= j {
			arr[i], arr[j] = arr[j], arr[i]
			i++
			j--
		}
	}

	// 第四步：递归处理左右子数组
	quickSort6(arr, left, j)
	quickSort6(arr, i, right)

	return arr
}

/**
 * 快速排序7 - 三路分区递归版本
 *
 * ## 算法特点
 * - 使用第一个元素作为基准
 * - 三路分区：处理重复元素，提高效率
 * - 递归优化：减少递归调用次数
 * - 原地排序：不需要额外空间
 *
 * ## 复杂度分析
 * - 时间复杂度：平均O(n log n)，最坏O(n²)
 * - 空间复杂度：O(log n) - 递归调用栈
 * - 稳定性：不稳定 - 分区过程可能改变相等元素的相对位置
 *
 * @param arr 待排序的整数数组
 * @param left 起始索引
 * @param right 结束索引
 * @return 排序后的整数数组
 */
func quickSort7(arr []int, left int, right int) []int {
	// 第一步：递归终止条件检查
	if left >= right {
		return arr
	}

	// 第二步：初始化基准和三路指针
	pivot := arr[left] // 第一个元素作为基准
	lt := left         // 小于基准的右边界
	i := left + 1      // 当前遍历指针
	gt := right        // 大于基准的左边界

	// 第三步：三路分区
	for i <= gt {
		if arr[i] < pivot {
			// 步骤3.1：小于基准，交换到左边
			arr[lt], arr[i] = arr[i], arr[lt]
			lt++
			i++
		} else if arr[i] > pivot {
			// 步骤3.2：大于基准，交换到右边
			arr[i], arr[gt] = arr[gt], arr[i]
			gt--
		} else {
			// 步骤3.3：等于基准，直接跳过
			i++
		}
	}

	// 第四步：递归处理左右子数组
	if lt > left {
		leftArr := make([]int, lt-left)
		copy(leftArr, arr[left:lt])
		quickSort7(leftArr, 0, lt-left-1)
		for i := 0; i < lt-left; i++ {
			arr[left+i] = leftArr[i]
		}
	}
	if gt < right {
		rightArr := make([]int, right-gt)
		copy(rightArr, arr[gt+1:right+1])
		quickSort7(rightArr, 0, right-gt-1)
		for i := 0; i < right-gt; i++ {
			arr[gt+1+i] = rightArr[i]
		}
	}

	return arr
}

// ==================== 算法测试和性能对比 ====================

func main() {
	// 测试数据
	testData := []int{7, 11, 9, 10, 12, 13, 8}

	// 测试1：递归新建数组版本
	performanceTest(quickSort1, testData, "递归新建数组版本")

	// 测试2：标准递归版本
	performanceTest(func(arr []int) []int { return quickSort2(arr, 0, len(arr)-1) }, testData, "标准递归版本")

	// 测试3：双向扫描递归版本
	performanceTest(func(arr []int) []int { return quickSort3(arr, 0, len(arr)-1) }, testData, "双向扫描递归版本")

	// 测试4：非递归版本
	performanceTest(func(arr []int) []int { return quickSort4(arr, 0, len(arr)-1) }, testData, "非递归版本")

	// 测试5：Lomuto分区递归版本
	performanceTest(func(arr []int) []int { return quickSort5(arr, 0, len(arr)-1) }, testData, "Lomuto分区递归版本")

	// 测试6：Hoare分区递归版本
	performanceTest(func(arr []int) []int { return quickSort6(arr, 0, len(arr)-1) }, testData, "Hoare分区递归版本")

	// 测试7：三路分区递归版本
	performanceTest(func(arr []int) []int { return quickSort7(arr, 0, len(arr)-1) }, testData, "三路分区递归版本")

	fmt.Println("=== 算法对比总结 ===")
	fmt.Println("1. 递归新建数组版本：中间基准，新建数组，稳定排序")
	fmt.Println("2. 标准递归版本：右侧基准，原地交换，Lomuto分区")
	fmt.Println("3. 双向扫描递归版本：中间基准，双向扫描，原地交换")
	fmt.Println("4. 非递归版本：栈模拟，避免递归，双向扫描")
	fmt.Println("5. Lomuto分区递归版本：最后基准，单向扫描")
	fmt.Println("6. Hoare分区递归版本：第一个基准，双向扫描")
	fmt.Println("7. 三路分区递归版本：第一个基准，三路分区")
}

/*打印结果
jarry@Mac quicksort % go run quick_sort.go
递归新建数组版本原始数组: [7, 11, 9, 10, 12, 13, 8]
split array: [7 11 9 10 12 13 8]
split array: [7 9 8]
split array: [7 8]
sorted array: [7 8]
sorted array: [7 8 9]
split array: [11 12 13]
sorted array: [11 12 13]
sorted array: [7 8 9 10 11 12 13]
递归新建数组版本: 0.128ms
递归新建数组版本排序结果: [7, 8, 9, 10, 11, 12, 13]

标准递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
partitioned arr= [7 8 9 10 12 13 11] partitionIndex: 1 left= [7] arr[partitionIndex]= 8 right= [8 9 10 12 13 11] [7 8 9 10 12 13 11]
partitioned arr= [7 8 9 10 11 13 12] partitionIndex: 4 left= [9 10] arr[partitionIndex]= 11 right= [11 13 12] [7 8 9 10 11 13 12]
partitioned arr= [7 8 9 10 11 13 12] partitionIndex: 3 left= [9] arr[partitionIndex]= 10 right= [10] [7 8 9 10 11 13 12]
partitioned arr= [7 8 9 10 11 12 13] partitionIndex: 5 left= [] arr[partitionIndex]= 12 right= [12 13] [7 8 9 10 11 12 13]
标准递归版本: 0.016ms
标准递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

双向扫描递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot:  i= 0  j= 6  pivot= 10 arr[]= [7 11 9 10 12 13 8]
  left= 0  right= 6  i= 1  j= 6  midIndex= 3  pivot= 10  arr[]= [7 11 9 10 12 13 8]
arr[i] < pivot:  i= 2  j= 5  pivot= 10 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 3  j= 5  pivot= 10 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 3  j= 4  pivot= 10 arr[]= [7 8 9 10 12 13 11]
  left= 0  right= 6  i= 3  j= 3  midIndex= 3  pivot= 10  arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 0  right= 6  i= 4  j= 2 arr[] [7 8 9 10 12 13 11]
arr[i] < pivot:  i= 0  j= 2  pivot= 8 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 1  j= 2  pivot= 8 arr[]= [7 8 9 10 12 13 11]
  left= 0  right= 2  i= 1  j= 1  midIndex= 1  pivot= 8  arr[]= [7 8 9 10 12 13 11]
i < right:recursion:  left= 0  right= 6  i= 4  j= 2 arr[] [7 8 9 10 12 13 11]
arr[i] < pivot:  i= 4  j= 6  pivot= 13 arr[]= [7 8 9 10 12 13 11]
  left= 4  right= 6  i= 5  j= 6  midIndex= 5  pivot= 13  arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 4  right= 6  i= 6  j= 5 arr[] [7 8 9 10 12 11 13]
  left= 4  right= 5  i= 4  j= 5  midIndex= 4  pivot= 12  arr[]= [7 8 9 10 12 11 13]
双向扫描递归版本: 0.077ms
双向扫描递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

非递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot:  i= 0  j= 6  pivot= 10 arr[]= [7 11 9 10 12 13 8]
arr[i] < pivot:  i= 2  j= 5  pivot= 10 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 3  j= 5  pivot= 10 arr[]= [7 8 9 10 12 13 11]
arr[j] > pivot:  i= 3  j= 4  pivot= 10 arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 0  right= 6  i= 4  j= 2 arr[] [7 8 9 10 12 13 11]
i < right:recursion:  left= 0  right= 6  i= 4  j= 2 arr[] [7 8 9 10 12 13 11]
arr[i] < pivot:  i= 4  j= 6  pivot= 13 arr[]= [7 8 9 10 12 13 11]
left < j:recursion:  left= 4  right= 6  i= 6  j= 5 arr[] [7 8 9 10 12 11 13]
arr[i] < pivot:  i= 0  j= 2  pivot= 8 arr[]= [7 8 9 10 11 12 13]
arr[j] > pivot:  i= 1  j= 2  pivot= 8 arr[]= [7 8 9 10 11 12 13]
非递归版本: 0.017ms
非递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Lomuto分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Lomuto分区递归版本: 0.000ms
Lomuto分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

Hoare分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
Hoare分区递归版本: 0.000ms
Hoare分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

三路分区递归版本原始数组: [7, 11, 9, 10, 12, 13, 8]
三路分区递归版本: 0.001ms
三路分区递归版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归新建数组版本：中间基准，新建数组，稳定排序
2. 标准递归版本：右侧基准，原地交换，Lomuto分区
3. 双向扫描递归版本：中间基准，双向扫描，原地交换
4. 非递归版本：栈模拟，避免递归，双向扫描
5. Lomuto分区递归版本：最后基准，单向扫描
6. Hoare分区递归版本：第一个基准，双向扫描
7. 三路分区递归版本：第一个基准，三路分区
*/
