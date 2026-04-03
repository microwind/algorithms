/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 合并两个已排序数组算法实现
 * 提供三种不同的合并策略，适合不同场景和性能需求
 *
 * 算法思路：
 * 1. 双指针法：同时遍历两个数组，逐个比较并合并
 * 2. 插入法：将一个数组的元素逐个插入到另一个数组中
 * 3. 合并排序法：先合并数组再进行排序
 *
 * 时间复杂度：O(n+m) - 双指针法最优
 * 空间复杂度：O(n+m) - 需要额外空间存储结果
 * 稳定性：稳定 - 保持相等元素的相对位置
 */
package main

import "fmt"

/**
 * 合并两个已排序数组 - 双指针法
 *
 * 算法思路：
 * 使用两个指针分别指向两个数组的起始位置，同时遍历比较
 * 将较小的元素放入结果数组，并移动相应指针，直到其中一个数组遍历完成
 * 最后将剩余数组元素直接复制到结果数组中
 *
 * 步骤说明：
 * 1. 初始化结果数组和指针
 * 2. 同时遍历两个数组，比较并合并
 * 3. 处理剩余元素
 *
 * 关键点：
 * - 使用三个指针分别跟踪两个输入数组和一个结果数组
 * - 比较当前元素，选择较小的放入结果数组
 * - 保持算法的稳定性
 *
 * 时间复杂度：O(n+m) - 每个元素只被访问一次
 * 空间复杂度：O(n+m) - 需要额外空间存储结果
 * 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param one 第一个已排序数组
 * @param two 第二个已排序数组
 * @return 合并后的有序数组
 */
func mergeSorted1(one []int, two []int) []int {
	// 步骤1：初始化结果数组和指针
	// 关键点：结果数组长度为两个数组长度之和
	var oneLen = len(one)
	var twoLen = len(two)
	var result = make([]int, oneLen+twoLen)
	i := 0 // 数组1下标
	j := 0 // 数组2下标
	k := 0 // 新数组下标

	// 步骤2：同时遍历两个数组，比较并合并
	// 关键点：当两个数组都还有元素时继续比较
	for i < oneLen && j < twoLen {
		// 步骤2.1：比较当前元素并选择较小的
		// 关键点：两两比较，把小的项追加到新数组中，同时移动小的那个数组指针
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

	// 步骤3：处理剩余元素
	// 关键点：将未处理完的数组元素直接复制到结果数组
	// 复制数组1剩余的项目
	for i < oneLen {
		result[k] = one[i]
		k++
		i++
	}
	// 复制数组2剩余的项目
	for j < twoLen {
		result[k] = two[j]
		k++
		j++
	}

	return result
}

/**
 * 合并两个已排序数组 - 插入法
 *
 * 算法思路：
 * 将一个数组的元素逐个插入到另一个数组中
 * 利用Go的slice动态插入特性，在找到合适位置后插入元素
 *
 * 步骤说明：
 * 1. 遍历第一个数组的每个元素
 * 2. 在第二个数组中找到插入位置
 * 3. 插入元素并移动后续元素
 *
 * 关键点：
 * - 利用Go的slice动态插入特性
 * - 需要移动后续元素，时间复杂度较高
 * - 原地操作，空间复杂度低
 *
 * 时间复杂度：O(n*m) - 最坏情况下每个元素需要遍历整个第二个数组
 * 空间复杂度：O(1) - 在原数组基础上操作
 * 稳定性：稳定 - 保持相等元素的相对位置
 *
 * @param one 第一个已排序数组
 * @param two 第二个已排序数组
 * @return 合并后的有序数组
 */
func mergeSorted2(one []int, two []int) []int {
	// 步骤1：初始化变量
	// 关键点：获取数组长度，用于边界检查
	var oneLen = len(one)
	var twoLen = len(two)

	// 步骤2：遍历第一个数组的每个元素
	// 关键点：将每个元素插入到第二个数组合适位置
	for i := 0; i < oneLen; i++ {
		// 步骤2.1：在第二个数组中找到插入位置
		// 关键点：遍历第二个数组，找到第一个大于等于当前元素的位置
		for k, v := range two {
			// 步骤2.2：比较并插入
			// 关键点：如果当前元素小于数组2的成员项，则插入到数组2中
			if one[i] < v {
				// 步骤2.2.1：扩展数组容量
				// 关键点：追加最后一位到数组2，为插入腾出空间
				two = append(two, two[twoLen-1])
				twoLen++
				// 步骤2.2.2：移动后续元素
				// 关键点：将数组2中k的位置整体右移1位
				copy(two[k+1:twoLen-1], two[k:twoLen-2])
				// 步骤2.2.3：插入元素
				// 关键点：将比较项插入到空出的位置
				two[k] = one[i]
				break
			} else {
				// 步骤2.3：处理边界情况
				// 关键点：如果全部比较完成，且数组2里面没有比它还大的，则添加到最后
				if k == twoLen-1 {
					two = append(two, one[i])
					twoLen++
					break
				}
			}
		}
	}
	return two
}

/**
 * 合并两个已排序数组 - 合并排序法
 *
 * 算法思路：
 * 先将两个数组合并成一个数组，然后使用插入排序进行排序
 * 利用第一个数组已排序的特性，从第二个数组开始位置进行排序
 *
 * 步骤说明：
 * 1. 合并两个数组
 * 2. 从第二个数组开始位置进行插入排序
 * 3. 逐个插入元素到已排序部分
 *
 * 关键点：
 * - 先合并后排序，实现简单
 * - 利用已排序部分的特性
 * - 使用插入排序，适合小数据量
 *
 * 时间复杂度：O((n+m)²) - 插入排序的时间复杂度
 * 空间复杂度：O(n+m) - 需要额外空间存储结果
 * 稳定性：稳定 - 插入排序保持相等元素的相对位置
 *
 * @param one 第一个已排序数组
 * @param two 第二个已排序数组
 * @return 合并后的有序数组
 */
func mergeSorted3(one []int, two []int) []int {
	// 步骤1：初始化变量
	// 关键点：获取数组长度，预分配结果数组空间
	var oneLen = len(one)
	var twoLen = len(two)
	var result = make([]int, oneLen+twoLen)

	// 步骤2：合并数组
	// 关键点：将两个数组的元素复制到结果数组中
	for i := range result {
		if i < oneLen {
			result[i] = one[i]
		} else {
			result[i] = two[i-oneLen]
		}
	}

	// 步骤3：插入排序
	// 关键点：从第二个数组开始位置进行排序，利用第一个数组已排序的特性
	for i := oneLen; i < len(result); i++ {
		// 步骤3.1：逐个插入元素到已排序部分
		// 关键点：自后往前把当前项与前一项进行比较
		for j := i; j > 0; j-- {
			// 步骤3.2：比较并交换
			// 关键点：如果小于前面项则交换位置
			if result[j] < result[j-1] {
				result[j], result[j-1] = result[j-1], result[j]
			}
		}
	}

	return result
}

/**
 * 主函数 - 算法测试和演示
 */
func main() {
	// 测试数据
	var arr1 = []int{-3, 7, 9, 10, 11, 15, 16}
	var arr2 = []int{-1, 5, 6, 9, 12}

	fmt.Println("=== mergeSorted1 双指针法 ===")
	fmt.Println("原始数组1:", arr1)
	fmt.Println("原始数组2:", arr2)
	fmt.Println("合并结果:", mergeSorted1(arr1, arr2))

	var arr2_1 = []int{-3, 7, 9, 10, 11, 15, 16}
	var arr2_2 = []int{-1, 5, 6, 9, 12}
	fmt.Println("\n=== mergeSorted2 插入法 ===")
	fmt.Println("原始数组1:", arr2_1)
	fmt.Println("原始数组2:", arr2_2)
	fmt.Println("合并结果:", mergeSorted2(arr2_1, arr2_2))

	var arr3_1 = []int{-3, 7, 9, 10, 11, 15, 16}
	var arr3_2 = []int{-1, 5, 6, 9, 12}
	fmt.Println("\n=== mergeSorted3 合并排序法 ===")
	fmt.Println("原始数组1:", arr3_1)
	fmt.Println("原始数组2:", arr3_2)
	fmt.Println("合并结果:", mergeSorted3(arr3_1, arr3_2))

	fmt.Println("\n=== 算法对比总结 ===")
	fmt.Println("1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择")
	fmt.Println("2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量")
	fmt.Println("3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单")
}

/*
jarry@Mac mergesort % go run merge_sorted_array.go
=== mergeSorted1 双指针法 ===
原始数组1: [-3 7 9 10 11 15 16]
原始数组2: [-1 5 6 9 12]
合并结果: [-3 -1 5 6 7 9 9 10 11 12 15 16]

=== mergeSorted2 插入法 ===
原始数组1: [-3 7 9 10 11 15 16]
原始数组2: [-1 5 6 9 12]
合并结果: [-3 -1 5 6 7 9 9 10 11 12 15 16]

=== mergeSorted3 合并排序法 ===
原始数组1: [-3 7 9 10 11 15 16]
原始数组2: [-1 5 6 9 12]
合并结果: [-3 -1 5 6 7 9 9 10 11 12 15 16]

=== 算法对比总结 ===
1. 双指针法：时间复杂度O(n+m)，空间复杂度O(n+m)，最优选择
2. 插入法：时间复杂度O(n*m)，空间复杂度O(1)，适合小数据量
3. 合并排序法：时间复杂度O((n+m)²)，空间复杂度O(n+m)，逻辑简单
*/
