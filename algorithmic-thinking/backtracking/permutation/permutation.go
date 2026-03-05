package main

import (
	"fmt"
	"slices"
)

/*
使用回溯生成排列 (Go Implementation)

算法说明:
- 使用回溯生成切片的所有排列
- 使用切片技术构建排列
- 在每个递归级别，尝试每个未使用的元素
- 通过不在下一个递归中包含该元素来回溯

时间复杂度：O(n! * n) - n! 个排列，每个需要 O(n) 时间复制
空间复杂度：O(n) - 递归深度（不计算输出）

示例:
    Permute([]int{1, 2, 3}) 返回所有 6 个排列
*/

// Permute 结戴所有排列。
// 时间复杂度：O(n! * n)
// 空间复杂度：O(n)
func Permute(nums []int) [][]int {
	result := make([][]int, 0)
	backtrack(&result, []int{}, nums)
	return result
}

// backtrack 递归构建所有排列。
func backtrack(result *[][]int, current, remaining []int) {
	// 基础情况：所有元素都已使用，添加到结果中
	if len(remaining) == 0 {
		*result = append(*result, append([]int{}, current...))
		return
	}

	// 尝试每个剩余元素作为下一个元素
	for i := 0; i < len(remaining); i++ {
		// 选择：将 remaining[i] 添加到当前排列
		current = append(current, remaining[i])

		// 探索：递归构建排列的余下部分
		newRemaining := make([]int, 0, len(remaining)-1)
		newRemaining = append(newRemaining, remaining[:i]...)
		newRemaining = append(newRemaining, remaining[i+1:]...)
		backtrack(result, current, newRemaining)

		// 撤销：移除元素以回溯
		current = current[:len(current)-1]
	}
}

// PermuteOptimized 使用原位置交换来成成排列。
// 需要修改数组或创建新的切片会更为高效。
// 时间复杂度：O(n! * n)
// 空间复杂度：O(n)
func PermuteOptimized(nums []int) [][]int {
	result := make([][]int, 0)
	// 副本以不修改整体
	arr := slices.Clone(nums)
	backtrackSwap(&result, arr, 0)
	return result
}

// backtrackSwap 使用原位置交换来递归构建排列。
func backtrackSwap(result *[][]int, nums []int, index int) {
	// 基础情况：到达切片末尾
	if index == len(nums) {
		*result = append(*result, slices.Clone(nums))
		return
	}

	// 尝试从 index 下来的每个元素作为下一个元素
	for i := index; i < len(nums); i++ {
		// 选择：交换元素
		nums[index], nums[i] = nums[i], nums[index]

		// 探索：排列剩余部分
		backtrackSwap(result, nums, index+1)

		// 撤销：交换回去
		nums[index], nums[i] = nums[i], nums[index]
	}
}

func main() {
	fmt.Println("=== 排列回溯测试用例 ===\n")

	// 测试用例 1: [1, 2, 3]
	fmt.Println("测试 1: Permute([1, 2, 3])")
	result1 := Permute([]int{1, 2, 3})
	fmt.Printf("结果（共 %d 个）:\n", len(result1))
	for _, perm := range result1 {
		fmt.Printf("  %v\n", perm)
	}
	fmt.Println()

	// 测试用例 2: [1, 2]
	fmt.Println("测试 2: Permute([1, 2])")
	result2 := Permute([]int{1, 2})
	fmt.Printf("结果（共 %d 个）:\n", len(result2))
	for _, perm := range result2 {
		fmt.Printf("  %v\n", perm)
	}
	fmt.Println()

	// 测试用例 3: [1]
	fmt.Println("测试 3: Permute([1])")
	result3 := Permute([]int{1})
	fmt.Printf("结果（共 %d 个）:\n", len(result3))
	for _, perm := range result3 {
		fmt.Printf("  %v\n", perm)
	}
	fmt.Println()

	// 测试用例 4: 优化的版本，整数数组 [1, 2, 3, 4]
	fmt.Println("测试 4: PermuteOptimized([1, 2, 3, 4])")
	result4 := PermuteOptimized([]int{1, 2, 3, 4})
	fmt.Printf("结果（共 %d 个）:\n", len(result4))
	fmt.Println("前 3 个排列:")
	for i := 0; i < 3; i++ {
		fmt.Printf("  %v\n", result4[i])
	}
	fmt.Println("后 3 个排列:")
	for i := len(result4) - 3; i < len(result4); i++ {
		fmt.Printf("  %v\n", result4[i])
	}
	fmt.Println()

	// 测试用例 5: [10, 20, 30]
	fmt.Println("测试 5: PermuteOptimized([10, 20, 30])")
	result5 := PermuteOptimized([]int{10, 20, 30})
	fmt.Printf("结果（共 %d 个）:\n", len(result5))
	for _, perm := range result5 {
		fmt.Printf("  %v\n", perm)
	}
}
