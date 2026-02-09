/*
N-Queens Problem using Backtracking (Rust Implementation)

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
- Same column: Check column set
- Diagonal (top-left to bottom-right): Check if row - col is same
- Diagonal (top-right to bottom-left): Check if row + col is same

Time Complexity: O(n!)
Space Complexity: O(n)

Example:
    solve_n_queens(4) returns 2 solutions
*/

use std::collections::HashSet;

/// Solve the N-Queens problem using backtracking.
///
/// # Arguments
/// * `n` - Size of the chessboard (n queens on n×n board)
///
/// # Returns
/// Vector of solutions, each solution is a vector of board strings
fn solve_n_queens(n: i32) -> Vec<Vec<String>> {
    let mut result = Vec::new();
    let mut col_placement = vec![0; n as usize];
    let mut cols = HashSet::new();
    let mut diag1 = HashSet::new();  // row - col
    let mut diag2 = HashSet::new();  // row + col

    backtrack(
        &mut result,
        n,
        0,
        &mut col_placement,
        &mut cols,
        &mut diag1,
        &mut diag2,
    );
    result
}

/// Recursively place queens row by row.
fn backtrack(
    result: &mut Vec<Vec<String>>,
    n: i32,
    row: i32,
    col_placement: &mut Vec<i32>,
    cols: &mut HashSet<i32>,
    diag1: &mut HashSet<i32>,
    diag2: &mut HashSet<i32>,
) {
    // Base case: all queens placed
    if row == n {
        result.push(build_board(n as usize, col_placement));
        return;
    }

    // Try placing a queen in each column of this row
    for col in 0..n {
        let diag1_id = row - col;
        let diag2_id = row + col;

        // Check if column or diagonals have a queen
        if cols.contains(&col) || diag1.contains(&diag1_id) || diag2.contains(&diag2_id) {
            continue;
        }

        // Place queen
        col_placement[row as usize] = col;
        cols.insert(col);
        diag1.insert(diag1_id);
        diag2.insert(diag2_id);

        // Explore: try to place queens in remaining rows
        backtrack(result, n, row + 1, col_placement, cols, diag1, diag2);

        // Backtrack: remove queen
        cols.remove(&col);
        diag1.remove(&diag1_id);
        diag2.remove(&diag2_id);
    }
}

/// Build the board representation from column placements.
fn build_board(n: usize, col_placement: &[i32]) -> Vec<String> {
    let mut board = Vec::new();
    for row in 0..n {
        let mut line = String::new();
        for col in 0..n {
            if col as i32 == col_placement[row] {
                line.push('Q');
            } else {
                line.push('.');
            }
        }
        board.push(line);
    }
    board
}

/// Count the number of solutions to the N-Queens problem.
/// More efficient than storing all solutions.
///
/// # Arguments
/// * `n` - Size of board
///
/// # Returns
/// Number of solutions
fn count_n_queens(n: i32) -> i32 {
    let mut count = 0;
    let mut cols = HashSet::new();
    let mut diag1 = HashSet::new();
    let mut diag2 = HashSet::new();

    count_backtrack(n, 0, &mut cols, &mut diag1, &mut diag2, &mut count);
    count
}

/// Recursively count solutions.
fn count_backtrack(
    n: i32,
    row: i32,
    cols: &mut HashSet<i32>,
    diag1: &mut HashSet<i32>,
    diag2: &mut HashSet<i32>,
    count: &mut i32,
) {
    if row == n {
        *count += 1;
        return;
    }

    for col in 0..n {
        let diag1_id = row - col;
        let diag2_id = row + col;

        if cols.contains(&col) || diag1.contains(&diag1_id) || diag2.contains(&diag2_id) {
            continue;
        }

        cols.insert(col);
        diag1.insert(diag1_id);
        diag2.insert(diag2_id);

        count_backtrack(n, row + 1, cols, diag1, diag2, count);

        cols.remove(&col);
        diag1.remove(&diag1_id);
        diag2.remove(&diag2_id);
    }
}

fn main() {
    println!("=== N-Queens Problem using Backtracking ===\n");

    // Test Case 1: 4-Queens
    println!("Test 1: solve_n_queens(4)");
    let result1 = solve_n_queens(4);
    println!("Found {} solutions:\n", result1.len());
    for (idx, solution) in result1.iter().enumerate() {
        println!("Solution {}:", idx + 1);
        for row in solution {
            println!("  {}", row);
        }
        println!();
    }

    // Test Case 2: 1-Queen
    println!("Test 2: solve_n_queens(1)");
    let result2 = solve_n_queens(1);
    println!("Found {} solution(s):\n", result2.len());
    for (idx, solution) in result2.iter().enumerate() {
        println!("Solution {}:", idx + 1);
        for row in solution {
            println!("  {}", row);
        }
        println!();
    }

    // Test Case 3: Solution counts for various sizes
    println!("Test 3: Solution counts for various N:");
    for n in 1..=8 {
        let count = count_n_queens(n);
        println!("  N={}: {} solutions", n, count);
    }
    println!();

    // Test Case 4: 5-Queens
    println!("Test 4: solve_n_queens(5)");
    let result4 = solve_n_queens(5);
    println!("Found {} solutions for 5-Queens", result4.len());
    println!("First solution:");
    for row in &result4[0] {
        println!("  {}", row);
    }
}
