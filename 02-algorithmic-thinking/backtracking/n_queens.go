package main

import (
	"fmt"
)

/*
N-Queens Problem using Backtracking (Go Implementation)

Algorithm Explanation:
- Place n queens on an n×n chessboard
- No two queens can attack each other (same row, column, or diagonal)
- Use backtracking to explore all possible placements
- For each row, try placing a queen in each column
- Check if placement is safe (not attacked by previously placed queens)
- If safe, place queen and move to next row
- If we place all n queens, we found a solution
- Backtrack and try next column if no solution found

Attack detection:
- Same column: Check column map
- Diagonal (top-left to bottom-right): Check if row - col is same
- Diagonal (top-right to bottom-left): Check if row + col is same

Time Complexity: O(n!)
Space Complexity: O(n)

Example:
    SolveNQueens(4) returns 2 solutions
*/

// SolveNQueens solves the N-Queens problem using backtracking.
// Returns all solutions as a list of board configurations.
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

	// Base case: all queens placed
	if row == n {
		board := buildBoard(n, colPlacement)
		*result = append(*result, board)
		return
	}

	// Try placing a queen in each column of this row
	for col := 0; col < n; col++ {
		diag1ID := row - col
		diag2ID := row + col

		// Check if column or diagonals have a queen
		if cols[col] || diag1[diag1ID] || diag2[diag2ID] {
			continue
		}

		// Place queen
		colPlacement[row] = col
		cols[col] = true
		diag1[diag1ID] = true
		diag2[diag2ID] = true

		// Explore: try to place queens in remaining rows
		backtrack(result, n, row+1, colPlacement, cols, diag1, diag2)

		// Backtrack: remove queen
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
// More efficient than storing all solutions.
//
// Time Complexity: O(n!)
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

	// Test Case 1: 4-Queens
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

	// Test Case 2: 1-Queen
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

	// Test Case 3: Solution counts for various sizes
	fmt.Println("Test 3: Solution counts for various N:")
	for n := 1; n <= 8; n++ {
		count := CountNQueens(n)
		fmt.Printf("  N=%d: %d solutions\n", n, count)
	}
	fmt.Println()

	// Test Case 4: 5-Queens
	fmt.Println("Test 4: SolveNQueens(5)")
	result4 := SolveNQueens(5)
	fmt.Printf("Found %d solutions for 5-Queens\n", len(result4))
	fmt.Println("First solution:")
	for _, row := range result4[0] {
		fmt.Printf("  %s\n", row)
	}
}
