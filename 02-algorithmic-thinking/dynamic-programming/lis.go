package main

import (
	"fmt"
	"sort"
)

/*
 * 最长递增子序列 (LIS) - 动态规划应用
 *
 * 问题描述：
 * 给定一个无序整数数组，找出其中最长递增子序列的长度
 *
 * 动态规划方程：
 * dp[i] = 1 + max(dp[j]) for all j < i and arr[j] < arr[i]
 *
 * 时间复杂度: O(n²) 基础DP
 * 空间复杂度: O(n)
 */

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// 最长递增子序列 - 基础DP方案
func LongestIncreasingSubsequence(arr []int) int {
	if len(arr) == 0 {
		return 0
	}

	n := len(arr)

	// dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
	dp := make([]int, n)
	for i := 0; i < n; i++ {
		dp[i] = 1
	}

	// 构建 DP 表
	for i := 1; i < n; i++ {
		for j := 0; j < i; j++ {
			// 如果 arr[j] < arr[i]，可以扩展以 arr[j] 结尾的 LIS
			if arr[j] < arr[i] {
				dp[i] = max(dp[i], dp[j]+1)
			}
		}
	}

	// 找到最大值
	maxLength := dp[0]
	for i := 1; i < n; i++ {
		maxLength = max(maxLength, dp[i])
	}
	return maxLength
}

// 最长递增子序列 - 优化方案 (O(n log n))
func LongestIncreasingSubsequenceOptimized(arr []int) int {
	if len(arr) == 0 {
		return 0
	}

	// tails[i] 是长度为 i+1 的递增子序列的最小末尾元素
	var tails []int

	for _, num := range arr {
		// 使用二分查找找到应该替换的位置
		pos := sort.SearchInts(tails, num)

		if pos == len(tails) {
			// 找到了更长的递增子序列
			tails = append(tails, num)
		} else {
			// 替换较大的元素，保持 tails 的最小性
			tails[pos] = num
		}
	}

	return len(tails)
}

// 最长递增子序列 - 返回子序列本身
func LongestIncreasingSubsequenceWithSequence(arr []int) (int, []int) {
	if len(arr) == 0 {
		return 0, []int{}
	}

	n := len(arr)

	// dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
	dp := make([]int, n)
	// parent[i] 表示以 arr[i] 结尾的 LIS 中，前一个元素的索引
	parent := make([]int, n)

	for i := 0; i < n; i++ {
		dp[i] = 1
		parent[i] = -1
	}

	// 构建 DP 表
	for i := 1; i < n; i++ {
		for j := 0; j < i; j++ {
			if arr[j] < arr[i] && dp[j]+1 > dp[i] {
				dp[i] = dp[j] + 1
				parent[i] = j
			}
		}
	}

	// 找到最长序列的结尾位置
	maxLength := dp[0]
	maxIndex := 0
	for i := 1; i < n; i++ {
		if dp[i] > maxLength {
			maxLength = dp[i]
			maxIndex = i
		}
	}

	// 反向追踪构建最长子序列
	lis := make([]int, 0, maxLength)
	idx := maxIndex
	for idx != -1 {
		lis = append([]int{arr[idx]}, lis...)
		idx = parent[idx]
	}

	return maxLength, lis
}

// 测试函数
func main() {
	fmt.Println("=== 最长递增子序列 ===\n")

	// 测试用例1：基本数组
	fmt.Println("1. 基本数组")
	arr1 := []int{10, 9, 2, 5, 3, 7, 101, 18}
	fmt.Printf("数组: %v\n", arr1)
	fmt.Printf("LIS 长度（DP）: %d\n", LongestIncreasingSubsequence(arr1))
	fmt.Printf("LIS 长度（优化）: %d\n\n", LongestIncreasingSubsequenceOptimized(arr1))

	// 测试用例2：已排序数组
	fmt.Println("2. 已排序数组")
	arr2 := []int{1, 3, 6, 7, 9, 4, 10, 5, 8}
	fmt.Printf("数组: %v\n", arr2)
	length, lis := LongestIncreasingSubsequenceWithSequence(arr2)
	fmt.Printf("LIS 长度: %d\n", length)
	fmt.Printf("一个 LIS: %v\n\n", lis)

	// 测试用例3：包含重复元素
	fmt.Println("3. 包含重复元素")
	arr3 := []int{1, 3, 3, 4, 5}
	fmt.Printf("数组: %v\n", arr3)
	fmt.Printf("LIS 长度: %d\n\n", LongestIncreasingSubsequence(arr3))

	// 测试用例4：单调递减
	fmt.Println("4. 单调递减")
	arr4 := []int{5, 4, 3, 2, 1}
	fmt.Printf("数组: %v\n", arr4)
	fmt.Printf("LIS 长度: %d\n", LongestIncreasingSubsequence(arr4))
}
