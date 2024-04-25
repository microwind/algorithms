/* KMP简单测试 */
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
	"fmt"
	"math"
	"strings"
	"time"
)

// 暴力求解法
func maxSubarraySum1(arr []int) int {
	maxSum := math.MinInt
	// 遍历数组，找到所有子数组
	for i := 0; i < len(arr); i++ {
		currentSum := arr[i]
		if currentSum > maxSum {
			maxSum = currentSum
		}

		fmt.Printf("第%d位组合:\n", i+1)
		// 内层循环计算子数组和
		// 使用 strings.Builder 构建字符串
		var output strings.Builder
		output.WriteString(fmt.Sprintf("%d", arr[i]))

		// 内层循环，计算子数组和
		for j := i + 1; j < len(arr); j++ {
			currentSum += arr[j]
			output.WriteString(" + ")
			output.WriteString(fmt.Sprintf("%d", arr[j]))

			if currentSum > maxSum {
				maxSum = currentSum
			}

			// 打印结果
			fmt.Println(output.String(), "=", currentSum)
		}
	}

	fmt.Println("maxSubarraySum1->maxSum:", maxSum)
	return maxSum
}

// 动态规划方法
func maxSubarraySum2(arr []int) int {
	// 动态规划数组
	dp := make([]int, len(arr))
	dp[0] = arr[0]

	// 计算每个位置的最大子数组和
	for i := 1; i < len(arr); i++ {
		dp[i] = int(math.Max(float64(dp[i-1]+arr[i]), float64(arr[i])))
	}

	// 找到dp数组中的最大值
	maxSum := math.MinInt
	for _, val := range dp {
		if val > maxSum {
			maxSum = val
		}
	}

	fmt.Println("maxSubarraySum2->maxSum:", maxSum)
	return maxSum
}

// Kadane算法
func maxSubarraySum3(arr []int) int {
	if len(arr) == 0 {
		return 0
	}

	maxSum := arr[0]
	currentSum := arr[0]

	// 迭代计算当前和与最大和
	for i := 1; i < len(arr); i++ {
		currentSum = int(math.Max(float64(arr[i]), float64(currentSum+arr[i])))
		maxSum = int(math.Max(float64(maxSum), float64(currentSum)))
	}

	fmt.Println("maxSubarraySum3->maxSum:", maxSum)
	return maxSum
}

func main() {
	time1 := time.Now()
	fmt.Println("start：")
	var arr = []int{-11, 10, -3, 1, -6, 13, -4}
	maxSubarraySum1(arr)
	maxSubarraySum2(arr)
	maxSubarraySum3(arr)
	fmt.Println("cost:", time.Since(time1))
}

/*
jarry@jarrys-MacBook-Pro bucketsort % go version
go version go1.19.5 darwin/amd64
jarry@jarrys-MacBook-Pro array % go run maximum_subarray.go
start：
第1位组合:
-11 + 10 = -1
-11 + 10 + -3 = -4
-11 + 10 + -3 + 1 = -3
-11 + 10 + -3 + 1 + -6 = -9
-11 + 10 + -3 + 1 + -6 + 13 = 4
-11 + 10 + -3 + 1 + -6 + 13 + -4 = 0
第2位组合:
10 + -3 = 7
10 + -3 + 1 = 8
10 + -3 + 1 + -6 = 2
10 + -3 + 1 + -6 + 13 = 15
10 + -3 + 1 + -6 + 13 + -4 = 11
第3位组合:
-3 + 1 = -2
-3 + 1 + -6 = -8
-3 + 1 + -6 + 13 = 5
-3 + 1 + -6 + 13 + -4 = 1
第4位组合:
1 + -6 = -5
1 + -6 + 13 = 8
1 + -6 + 13 + -4 = 4
第5位组合:
-6 + 13 = 7
-6 + 13 + -4 = 3
第6位组合:
13 + -4 = 9
第7位组合:
maxSubarraySum1->maxSum: 15
maxSubarraySum2->maxSum: 15
maxSubarraySum3->maxSum: 15
cost: 124.165µs
*/
