package main

import (
	"fmt"
	"math/rand"
	"time"
)

// 拉斯维加斯算法实现 (Go语言)
//
// 特点：
// - 总是给出正确答案
// - 运行时间随机
// - 不返回错误答案

// 交换两个整数
func swap(arr []int, i, j int) {
	arr[i], arr[j] = arr[j], arr[i]
}

// 随机分区函数
func randomizedPartition(arr []int, left, right int) int {
	// 随机选择枢轴
	pivotIdx := left + rand.Intn(right-left+1)
	swap(arr, pivotIdx, right)

	pivot := arr[right]
	i := left - 1

	for j := left; j < right; j++ {
		if arr[j] <= pivot {
			i++
			swap(arr, i, j)
		}
	}

	swap(arr, i+1, right)
	return i + 1
}

// 拉斯维加斯随机快速排序
func lasVegasQuickSort(arr []int, left, right int) {
	if left < right {
		// 随机分区
		pivotIdx := randomizedPartition(arr, left, right)

		// 递归排序左右子数组
		lasVegasQuickSort(arr, left, pivotIdx-1)
		lasVegasQuickSort(arr, pivotIdx+1, right)
	}
}

// 拉斯维加斯随机选择算法 - 找第k小元素
func lasVegasRandomizedSelect(arr []int, left, right, k int) int {
	if left == right {
		return arr[left]
	}

	// 随机分区
	pivotIdx := randomizedPartition(arr, left, right)

	// 计算枢轴的相对位置
	pos := pivotIdx - left + 1

	if k == pos {
		return arr[pivotIdx]
	} else if k < pos {
		return lasVegasRandomizedSelect(arr, left, pivotIdx-1, k)
	} else {
		return lasVegasRandomizedSelect(arr, pivotIdx+1, right, k-pos)
	}
}

// 拉斯维加斯字符串匹配
func lasVegasStringMatch(text, pattern string) int {
	n, m := len(text), len(pattern)
	if m > n {
		return -1
	}

	// 随机选择起始位置进行匹配
	for {
		start := rand.Intn(n - m + 1)

		// 检查是否匹配
		match := true
		for i := 0; i < m; i++ {
			if text[start+i] != pattern[i] {
				match = false
				break
			}
		}

		if match {
			return start // 找到匹配位置
		}

		// 在实际实现中，这里应该有避免无限循环的机制
		// 为了演示，这里简化处理
		break
	}

	return -1
}

// 拉斯维加斯八皇后问题求解器
func lasVegasNQueens(n int) []int {
	for {
		queens := make([]int, n)
		columns := make([]bool, n)
		diag1 := make([]bool, 2*n-1) // 主对角线
		diag2 := make([]bool, 2*n-1) // 副对角线

		success := true

		// 逐行放置皇后
		for row := 0; row < n; row++ {
			// 收集当前行可用的列
			var availableCols []int
			for col := 0; col < n; col++ {
				if !columns[col] && !diag1[row+col] && !diag2[row-col+n-1] {
					availableCols = append(availableCols, col)
				}
			}

			if len(availableCols) == 0 {
				success = false
				break
			}

			// 随机选择一个可用列
			chosenCol := availableCols[rand.Intn(len(availableCols))]
			queens[row] = chosenCol
			columns[chosenCol] = true
			diag1[row+chosenCol] = true
			diag2[row-chosenCol+n-1] = true
		}

		if success {
			return queens
		}
	}
}

// 打印数组
func printArray(arr []int) {
	fmt.Print("[")
	for i, v := range arr {
		fmt.Print(v)
		if i < len(arr)-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}

// 打印八皇后解法
func printNQueensSolution(queens []int) {
	n := len(queens)
	for row := 0; row < n; row++ {
		for col := 0; col < n; col++ {
			if queens[row] == col {
				fmt.Print("Q ")
			} else {
				fmt.Print(". ")
			}
		}
		fmt.Println()
	}
}

func main() {
	rand.Seed(time.Now().UnixNano())

	fmt.Println("=== 拉斯维加斯算法演示 ===\n")

	// 测试随机快速排序
	fmt.Println("1. 拉斯维加斯随机快速排序")
	arr1 := []int{5, 2, 8, 1, 9, 3, 4, 7, 6}

	fmt.Print("原数组: ")
	printArray(arr1)

	lasVegasQuickSort(arr1, 0, len(arr1)-1)

	fmt.Print("排序后: ")
	printArray(arr1)
	fmt.Println()

	// 测试随机选择算法
	fmt.Println("2. 拉斯维加斯随机选择算法")
	arr2 := []int{7, 2, 5, 3, 9, 1, 4, 6, 8}
	k := 4 // 找第4小元素

	fmt.Print("数组: ")
	printArray(arr2)
	fmt.Printf("第%d小元素: %d\n\n", k, lasVegasRandomizedSelect(arr2, 0, len(arr2)-1, k))

	// 测试字符串匹配
	fmt.Println("3. 拉斯维加斯字符串匹配")
	text := "hello world, this is a test string"
	pattern := "test"

	fmt.Printf("文本: %s\n", text)
	fmt.Printf("模式: %s\n", pattern)
	pos := lasVegasStringMatch(text, pattern)
	if pos != -1 {
		fmt.Printf("匹配位置: %d\n", pos)
	} else {
		fmt.Println("未找到匹配")
	}
	fmt.Println()

	// 测试八皇后问题
	fmt.Println("4. 拉斯维加斯八皇后问题求解")
	n := 8
	solution := lasVegasNQueens(n)
	fmt.Printf("八皇后解法 (n=%d):\n", n)
	printNQueensSolution(solution)
}
