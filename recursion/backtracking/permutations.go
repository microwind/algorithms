// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
package main

import "fmt"

/**
 * 回溯算法 - 全排列 (Permutations)
 * 使用递归生成数组的所有排列
 */

// 生成数组的所有排列
func permutations(nums []int) [][]int {
	var result [][]int

	// 回溯生成排列
	var backtrack func(current []int, used []bool)
	backtrack = func(current []int, used []bool) {
		// 基础情况：当前排列长度等于输入数组长度
		if len(current) == len(nums) {
			temp := make([]int, len(current))
			copy(temp, current)
			result = append(result, temp)
			return
		}

		// 递归情况：尝试每个元素
		for i := 0; i < len(nums); i++ {
			// 如果元素已经被使用，跳过
			if used[i] {
				continue
			}

			// 选择元素
			current = append(current, nums[i])
			used[i] = true

			// 递归：继续处理
			backtrack(current, used)

			// 回溯：撤销选择
			current = current[:len(current)-1]
			used[i] = false
		}
	}

	used := make([]bool, len(nums))
	backtrack([]int{}, used)
	return result
}

func main() {
	nums := []int{1, 2, 3}
	result := permutations(nums)

	fmt.Printf("数组 %v 的所有排列:\n", nums)

	for i, perm := range result {
		fmt.Printf("  %d. %v\n", i+1, perm)
	}

	fmt.Printf("\n共 %d 种排列\n", len(result))
}
