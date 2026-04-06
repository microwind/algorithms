// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
package main

import "fmt"

/**
 * 回溯算法 - 子集生成 (Subsets)
 * 使用递归生成数组的所有子集
 */

// 生成数组的所有子集
func subsets(nums []int) [][]int {
	var result [][]int

	// 回溯生成子集
	var backtrack func(start int, current []int)
	backtrack = func(start int, current []int) {
		// 每次递归都将当前子集加入结果
		temp := make([]int, len(current))
		copy(temp, current)
		result = append(result, temp)

		// 从start开始尝试每个元素
		for i := start; i < len(nums); i++ {
			// 选择元素
			current = append(current, nums[i])

			// 递归：继续处理后面的元素
			backtrack(i+1, current)

			// 回溯：撤销选择
			current = current[:len(current)-1]
		}
	}

	backtrack(0, []int{})
	return result
}

func main() {
	nums := []int{1, 2, 3}
	result := subsets(nums)

	fmt.Printf("数组 %v 的所有子集:\n", nums)
	fmt.Printf("共 %d 个子集\n\n", len(result))

	for i, subset := range result {
		fmt.Printf("  %d. %v\n", i+1, subset)
	}

	fmt.Println("\n递归过程可视化:")
	fmt.Println("        []")
	fmt.Println("       / | \\")
	fmt.Println("     [1] [2] [3]")
	fmt.Println("    /  \\      |")
	fmt.Println("  [1,2] [1,3] [2,3]")
	fmt.Println("   /")
	fmt.Println("[1,2,3]")
}
