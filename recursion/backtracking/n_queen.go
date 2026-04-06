// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
package main

import "fmt"

const N = 4 // 棋盘大小

/**
 * 回溯算法 - N皇后问题
 * 在n×n棋盘上放置n个皇后，使其互不攻击
 */

// 打印棋盘
func printBoard(board [N][N]int) {
	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			if board[i][j] == 1 {
				fmt.Print("Q ")
			} else {
				fmt.Print(". ")
			}
		}
		fmt.Println()
	}
	fmt.Println()
}

// 检查在(row, col)放置皇后是否安全
func isSafe(board [N][N]int, row, col int) bool {
	// 检查列
	for i := 0; i < row; i++ {
		if board[i][col] == 1 {
			return false
		}
	}

	// 检查左上对角线
	for i, j := row-1, col-1; i >= 0 && j >= 0; i, j = i-1, j-1 {
		if board[i][j] == 1 {
			return false
		}
	}

	// 检查右上对角线
	for i, j := row-1, col+1; i >= 0 && j < N; i, j = i-1, j+1 {
		if board[i][j] == 1 {
			return false
		}
	}

	return true
}

// 使用回溯求解N皇后
func solveNQueen(board [N][N]int, row int) bool {
	// 基础情况：所有皇后都已放置
	if row >= N {
		return true
	}

	// 尝试在当前行的每一列放置皇后
	for col := 0; col < N; col++ {
		if isSafe(board, row, col) {
			// 放置皇后
			board[row][col] = 1

			// 递归：放置下一行的皇后
			if solveNQueen(board, row+1) {
				return true
			}

			// 回溯：撤销放置
			board[row][col] = 0
		}
	}

	return false
}

func main() {
	var board [N][N]int

	fmt.Printf("%d皇后问题求解:\n\n", N)

	if solveNQueen(board, 0) {
		fmt.Println("找到解:")
		printBoard(board)
	} else {
		fmt.Println("无解")
	}
}
