/*
使用回溯算法的N皇后问题 (Rust Implementation)

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
- Same column: Check column set
- 对角线（左上到右下）：检查row - col是否相同
- 对角线（右上到左下）：检查row + col是否相同

Time Complexity: O(n!)
Space Complexity: O(n)

示例:
    solve_n_queens(4) returns 2 solutions
*/

use std::collections::HashSet;

// / 使用回溯算法解决N皇后问题.
// /
// / # Arguments
// / * `n` - 棋盘大小（n个皇后放在n×n棋盘上）
// /
// / # 返回
// / Vector of solutions, each solution is a vector of board strings
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

// / 递归地逐行放置皇后.
fn backtrack(
    result: &mut Vec<Vec<String>>,
    n: i32,
    row: i32,
    col_placement: &mut Vec<i32>,
    cols: &mut HashSet<i32>,
    diag1: &mut HashSet<i32>,
    diag2: &mut HashSet<i32>,
) {
    // 基本情况：所有皇后都已放置
    if row == n {
        result.push(build_board(n as usize, col_placement));
        return;
    }

    // 尝试在此行的每一列放置一个皇后
    for col in 0..n {
        let diag1_id = row - col;
        let diag2_id = row + col;

        // Check if column or diagonals have a queen
        if cols.contains(&col) || diag1.contains(&diag1_id) || diag2.contains(&diag2_id) {
            continue;
        }

        // 放置皇后
        col_placement[row as usize] = col;
        cols.insert(col);
        diag1.insert(diag1_id);
        diag2.insert(diag2_id);

        // 探索：尝试在剩余行放置皇后
        backtrack(result, n, row + 1, col_placement, cols, diag1, diag2);

        // 回溯：移除皇后
        cols.remove(&col);
        diag1.remove(&diag1_id);
        diag2.remove(&diag2_id);
    }
}

// / Build the board representation from column placements.
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

// / 计算N皇后问题的解的数量.
// / 比存储所有解更高效.
// /
// / # Arguments
// / * `n` - Size of board
// /
// / # 返回
// / Number of solutions
fn count_n_queens(n: i32) -> i32 {
    let mut count = 0;
    let mut cols = HashSet::new();
    let mut diag1 = HashSet::new();
    let mut diag2 = HashSet::new();

    count_backtrack(n, 0, &mut cols, &mut diag1, &mut diag2, &mut count);
    count
}

// / Recursively count solutions.
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

    // 测试用例 1: 4-Queens
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

    // 测试用例 2: 1-Queen
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

    // 测试用例 3: Solution counts for various sizes
    println!("Test 3: Solution counts for various N:");
    for n in 1..=8 {
        let count = count_n_queens(n);
        println!("  N={}: {} solutions", n, count);
    }
    println!();

    // 测试用例 4: 5-Queens
    println!("Test 4: solve_n_queens(5)");
    let result4 = solve_n_queens(5);
    println!("Found {} solutions for 5-Queens", result4.len());
    println!("First solution:");
    for row in &result4[0] {
        println!("  {}", row);
    }
}

/**
jarry@Mac n-queens % rustc n_queens.rs 
jarry@Mac n-queens % ./n_queens 
=== N-Queens Problem using Backtracking ===

Test 1: solve_n_queens(4)
Found 2 solutions:

Solution 1:
  .Q..
  ...Q
  Q...
  ..Q.

Solution 2:
  ..Q.
  Q...
  ...Q
  .Q..

Test 2: solve_n_queens(1)
Found 1 solution(s):

Solution 1:
  Q

Test 3: Solution counts for various N:
  N=1: 1 solutions
  N=2: 0 solutions
  N=3: 0 solutions
  N=4: 2 solutions
  N=5: 10 solutions
  N=6: 4 solutions
  N=7: 40 solutions
  N=8: 92 solutions

Test 4: solve_n_queens(5)
Found 10 solutions for 5-Queens
First solution:
  Q....
  ..Q..
  ....Q
  .Q...
  ...Q.
  */