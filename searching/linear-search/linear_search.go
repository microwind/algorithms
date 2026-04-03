/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 线性查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

package main

import "fmt"

/**
 * 线性查找基础版本 - 查找第一个匹配项
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
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
func linearSearch(arr []int, target int) int {
	// 逐个遍历查找
	for i, value := range arr {
		if value == target {
			return i // 找到目标，返回索引
		}
	}
	
	return -1 // 未找到
}

/**
 * 线性查找 - 查找所有匹配项
 * 
 * 算法思路：
 * 遍历整个数组，收集所有匹配项的索引
 * 适合处理重复元素的情况
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 包含所有匹配索引的切片
 */
func linearSearchAll(arr []int, target int) []int {
	var result []int
	
	// 逐个遍历查找所有匹配项
	for i, value := range arr {
		if value == target {
			result = append(result, i)
		}
	}
	
	return result
}

/**
 * 线性查找 - 带哨兵优化版本
 * 
 * 算法优化：
 * 在数组末尾设置哨兵（目标值）
 * 减少每次循环中的边界检查
 * 可以略微提高性能
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
func linearSearchSentinel(arr []int, target int) int {
	if len(arr) == 0 {
		return -1
	}
	
	last := arr[len(arr)-1]      // 保存最后一个元素
	arr[len(arr)-1] = target     // 设置哨兵
	
	i := 0
	// 由于有哨兵，循环一定会终止
	for arr[i] != target {
		i++
	}
	
	arr[len(arr)-1] = last // 恢复最后一个元素
	
	// 检查是否真的找到目标
	if i < len(arr)-1 || arr[len(arr)-1] == target {
		return i
	}
	
	return -1
}

/**
 * 线性查找 - 反向查找版本
 * 
 * 算法思路：
 * 从数组末尾开始向前查找
 * 适合查找最后一个匹配项的场景
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
func linearSearchReverse(arr []int, target int) int {
	// 从后向前遍历查找
	for i := len(arr) - 1; i >= 0; i-- {
		if arr[i] == target {
			return i // 找到目标，返回索引
		}
	}
	
	return -1 // 未找到
}

/**
 * 线性查找 - 递归版本
 * 
 * 算法思路：
 * 使用递归方式实现线性查找
 * 每次递归处理一个元素
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @param index 当前索引
 * @return 找到返回索引，未找到返回-1
 */
func linearSearchRecursive(arr []int, target, index int) int {
	// 递归出口条件
	if index >= len(arr) {
		return -1
	}
	
	// 检查当前元素
	if arr[index] == target {
		return index
	}
	
	// 递归查找下一个元素
	return linearSearchRecursive(arr, target, index+1)
}

/**
 * 线性查找 - 递归版本（公共接口）
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @return 找到返回索引，未找到返回-1
 */
func linearSearchRecursivePublic(arr []int, target int) int {
	if len(arr) == 0 {
		return -1
	}
	
	return linearSearchRecursive(arr, target, 0)
}

/**
 * 主程序：演示线性查找功能
 */
func main() {
	fmt.Println("=== 线性查找演示 ===\n")
	
	// 测试数据
	arr := []int{64, 34, 25, 12, 22, 11, 90, 22}
	target := 22
	
	fmt.Println("数组:")
	for i, val := range arr {
		fmt.Printf("%d ", val)
		if i == len(arr)-1 {
			fmt.Println()
		}
	}
	fmt.Printf("目标元素: %d\n\n", target)
	
	// 基本查找测试
	fmt.Println("=== 基本查找测试 ===")
	index := linearSearch(arr, target)
	if index != -1 {
		fmt.Printf("基本查找: 找到于索引 %d\n", index)
	} else {
		fmt.Println("基本查找: 未找到")
	}
	
	// 查找所有匹配项
	fmt.Println("\n=== 查找所有匹配项 ===")
	allIndices := linearSearchAll(arr, target)
	fmt.Print("所有匹配位置: ")
	for i, idx := range allIndices {
		fmt.Printf("%d ", idx)
		if i == len(allIndices)-1 {
			fmt.Printf("(共%d个)\n", len(allIndices))
		}
	}
	
	// 反向查找测试
	fmt.Println("\n=== 反向查找测试 ===")
	reverseIndex := linearSearchReverse(arr, target)
	if reverseIndex != -1 {
		fmt.Printf("反向查找: 找到于索引 %d\n", reverseIndex)
	} else {
		fmt.Println("反向查找: 未找到")
	}
	
	// 哨兵查找测试
	fmt.Println("\n=== 哨兵查找测试 ===")
	sentinelIndex := linearSearchSentinel(arr, target)
	if sentinelIndex != -1 {
		fmt.Printf("哨兵查找: 找到于索引 %d\n", sentinelIndex)
	} else {
		fmt.Println("哨兵查找: 未找到")
	}
	
	// 递归查找测试
	fmt.Println("\n=== 递归查找测试 ===")
	recursiveIndex := linearSearchRecursivePublic(arr, target)
	if recursiveIndex != -1 {
		fmt.Printf("递归查找: 找到于索引 %d\n", recursiveIndex)
	} else {
		fmt.Println("递归查找: 未找到")
	}
	
	// 查找不存在的元素
	fmt.Println("\n=== 查找不存在的元素 ===")
	notFound := linearSearch(arr, 100)
	fmt.Printf("查找100: %t\n", notFound != -1)
	
	// 字符串查找测试
	fmt.Println("\n=== 字符串查找测试 ===")
	strArr := []string{"apple", "banana", "cherry", "date", "banana"}
	strTarget := "banana"
	
	fmt.Println("字符串数组:")
	for i, val := range strArr {
		fmt.Printf("%s ", val)
		if i == len(strArr)-1 {
			fmt.Println()
		}
	}
	fmt.Printf("目标字符串: %s\n", strTarget)
	
	var strIndex int = -1
	var strAllIndices []int
	for i, val := range strArr {
		if val == strTarget {
			if strIndex == -1 {
				strIndex = i
			}
			strAllIndices = append(strAllIndices, i)
		}
	}
	
	if strIndex != -1 {
		fmt.Printf("字符串查找: 找到于索引 %d\n", strIndex)
	} else {
		fmt.Println("字符串查找: 未找到")
	}
	
	fmt.Print("所有匹配位置: ")
	for i, idx := range strAllIndices {
		fmt.Printf("%d ", idx)
		if i == len(strAllIndices)-1 {
			fmt.Printf("(共%d个)\n", len(strAllIndices))
		}
	}
	
	// 性能分析
	fmt.Println("\n=== 线性查找特点 ===")
	fmt.Println("• 算法简单，易于实现")
	fmt.Println("• 适用于小规模数据和无序数据")
	fmt.Println("• 时间复杂度：O(n)")
	fmt.Println("• 空间复杂度：O(1)")
	fmt.Println("• 可以查找所有匹配项")
	fmt.Println("• 适合处理重复元素")
	
	// 与其他查找算法对比
	fmt.Println("\n=== 与其他查找算法对比 ===")
	fmt.Println("• 二分查找：O(log n)，但要求数组有序")
	fmt.Println("• 哈希查找：O(1)，但需要额外空间")
	fmt.Println("• 线性查找：O(n)，但无需预处理")
	fmt.Println("• 选择算法取决于数据规模和是否有序")
}

/*
打印结果
jarry@Mac linear-search % go run linear_search.go
=== 线性查找演示 ===

数组:
64 34 25 12 22 11 90 22 
目标元素: 22

=== 基本查找测试 ===
基本查找: 找到于索引 4

=== 查找所有匹配项 ===
所有匹配位置: 4 7 (共2个)

=== 反向查找测试 ===
反向查找: 找到于索引 7

=== 哨兵查找测试 ===
哨兵查找: 找到于索引 4

=== 递归查找测试 ===
递归查找: 找到于索引 4

=== 查找不存在的元素 ===
查找100: false

=== 字符串查找测试 ===
字符串数组:
apple banana cherry date banana 
目标字符串: banana
字符串查找: 找到于索引 1
所有匹配位置: 1 4 (共2个)

=== 线性查找特点 ===
• 算法简单，易于实现
• 适用于小规模数据和无序数据
• 时间复杂度：O(n)
• 空间复杂度：O(1)
• 可以查找所有匹配项
• 适合处理重复元素

=== 与其他查找算法对比 ===
• 二分查找：O(log n)，但要求数组有序
• 哈希查找：O(1)，但需要额外空间
• 线性查找：O(n)，但无需预处理
• 选择算法取决于数据规模和是否有序
*/
