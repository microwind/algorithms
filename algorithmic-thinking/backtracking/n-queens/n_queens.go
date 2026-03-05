package main

import (
	"fmt"
)

/*
使用回溯算法的N皇后问题 (Go Implementation)

算法说明:
- 在n×n棋盘上放置n个皇后
- 任意两个皇后不能相互攻击（不在同一行、列或对角线上）
- 使用回溯探索所有可能的放置方案
- 对于每一行，尝试在每一列放置一个皇后
- 检查放置是否安全（不被之前放置的皇后攻击）
- 如果安全，则放置皇后并移到下一行
- 如果所有n个皇后都被放置，则找到一个解
- 如果没有找到解，回溯并尝试下一列

攻击检测:
- Same column: Check column map
- 对角线（左上到右下）：检查row - col是否相同
- 对角线（右上到左下）：检查row + col是否相同

Time Complexity: O(n!)
Space Complexity: O(n)

示例:
    SolveNQueens(4) returns 2 solutions
*/

// SolveNQueens solves the N-Queens problem using backtracking.
// 返回 all solutions as a list of board configurations.
// Time Complexity: O(n!)
// Space Complexity: O(n)
func SolveNQueens(n int) [][]string {
	var result [][]string
	colPlacement := make([]int, n)
	cols := make(map[int]bool)
	diag1 := make(map[int]bool)  // row - col
	diag2 := make(map[int]bool)  // row + col

	backtrack(&result, n, 0, colPlacement, cols, diag1, diag2)
	return result
}

// backtrack recursively places queens row by row.
func backtrack(result *[][]string,
	n int,
	row int,
	colPlacement []int,
	cols, diag1, diag2 map[int]bool) {

	// 基本情况：所有皇后都已放置
	if row == n {
		board := buildBoard(n, colPlacement)
		*result = append(*result, board)
		return
	}

	// 尝试在此行的每一列放置一个皇后
	for col := 0; col < n; col++ {
		diag1ID := row - col
		diag2ID := row + col

		// Check if column or diagonals have a queen
		if cols[col] || diag1[diag1ID] || diag2[diag2ID] {
			continue
		}

		// 放置皇后
		colPlacement[row] = col
		cols[col] = true
		diag1[diag1ID] = true
		diag2[diag2ID] = true

		// 探索：尝试在剩余行放置皇后
		backtrack(result, n, row+1, colPlacement, cols, diag1, diag2)

		// 回溯：移除皇后
		delete(cols, col)
		delete(diag1, diag1ID)
		delete(diag2, diag2ID)
	}
}

// buildBoard builds the board representation from column placements.
func buildBoard(n int, colPlacement []int) []string {
	var board []string
	for row := 0; row < n; row++ {
		var line string
		for col := 0; col < n; col++ {
			if col == colPlacement[row] {
				line += "Q"
			} else {
				line += "."
			}
		}
		board = append(board, line)
	}
	return board
}

// CountNQueens counts the number of solutions to the N-Queens problem.
// 比存储所有解更高效.
// // Time Complexity: O(n!)
// Space Complexity: O(n)
func CountNQueens(n int) int {
	count := 0
	cols := make(map[int]bool)
	diag1 := make(map[int]bool)
	diag2 := make(map[int]bool)

	countBacktrack(n, 0, cols, diag1, diag2, &count)
	return count
}

// countBacktrack recursively counts solutions.
func countBacktrack(n int,
	row int,
	cols, diag1, diag2 map[int]bool,
	count *int) {

	if row == n {
		*count++
		return
	}

	for col := 0; col < n; col++ {
		diag1ID := row - col
		diag2ID := row + col

		if cols[col] || diag1[diag1ID] || diag2[diag2ID] {
			continue
		}

		cols[col] = true
		diag1[diag1ID] = true
		diag2[diag2ID] = true

		countBacktrack(n, row+1, cols, diag1, diag2, count)

		delete(cols, col)
		delete(diag1, diag1ID)
		delete(diag2, diag2ID)
	}
}

func main() {
	fmt.Println("=== N-Queens Problem using Backtracking ===\n")

	// 测试用例 1: 4-Queens
	fmt.Println("Test 1: SolveNQueens(4)")
	result1 := SolveNQueens(4)
	fmt.Printf("Found %d solutions:\n\n", len(result1))
	for idx, solution := range result1 {
		fmt.Printf("Solution %d:\n", idx+1)
		for _, row := range solution {
			fmt.Printf("  %s\n", row)
		}
		fmt.Println()
	}

	// 测试用例 2: 1-Queen
	fmt.Println("Test 2: SolveNQueens(1)")
	result2 := SolveNQueens(1)
	fmt.Printf("Found %d solution(s):\n\n", len(result2))
	for idx, solution := range result2 {
		fmt.Printf("Solution %d:\n", idx+1)
		for _, row := range solution {
			fmt.Printf("  %s\n", row)
		}
		fmt.Println()
	}

	// 测试用例 3: Solution counts for various sizes
	fmt.Println("Test 3: Solution counts for various N:")
	for n := 1; n <= 8; n++ {
		count := CountNQueens(n)
		fmt.Printf("  N=%d: %d solutions\n", n, count)
	}
	fmt.Println()

	// 测试用例 4: 5-Queens
	fmt.Println("Test 4: SolveNQueens(5)")
	result4 := SolveNQueens(5)
	fmt.Printf("Found %d solutions for 5-Queens\n", len(result4))
	fmt.Println("First solution:")
	for _, row := range result4[0] {
		fmt.Printf("  %s\n", row)
	}
}
