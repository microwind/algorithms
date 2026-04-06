/**
 * 回溯算法 - N皇后问题
 * 在n×n棋盘上放置n个皇后，使其互不攻击
 */

const N: usize = 4; // 棋盘大小

/**
 * 打印棋盘
 */
fn print_board(board: &[[i32; N]; N]) {
    for i in 0..N {
        for j in 0..N {
            if board[i][j] == 1 {
                print!("Q ");
            } else {
                print!(". ");
            }
        }
        println!();
    }
    println!();
}

/**
 * 检查在(row, col)放置皇后是否安全
 */
fn is_safe(board: &[[i32; N]; N], row: usize, col: usize) -> bool {
    // 检查列
    for i in 0..row {
        if board[i][col] == 1 {
            return false;
        }
    }
    
    // 检查左上对角线
    let (mut i, mut j) = (row as i32 - 1, col as i32 - 1);
    while i >= 0 && j >= 0 {
        if board[i as usize][j as usize] == 1 {
            return false;
        }
        i -= 1;
        j -= 1;
    }
    
    // 检查右上对角线
    let (mut i, mut j) = (row as i32 - 1, col as i32 + 1);
    while i >= 0 && j < N as i32 {
        if board[i as usize][j as usize] == 1 {
            return false;
        }
        i -= 1;
        j += 1;
    }
    
    true
}

/**
 * 使用回溯求解N皇后
 */
fn solve_n_queen(board: &mut [[i32; N]; N], row: usize) -> bool {
    // 基础情况：所有皇后都已放置
    if row >= N {
        return true;
    }
    
    // 尝试在当前行的每一列放置皇后
    for col in 0..N {
        if is_safe(board, row, col) {
            // 放置皇后
            board[row][col] = 1;
            
            // 递归：放置下一行的皇后
            if solve_n_queen(board, row + 1) {
                return true;
            }
            
            // 回溯：撤销放置
            board[row][col] = 0;
        }
    }
    
    false
}

fn main() {
    let mut board: [[i32; N]; N] = [[0; N]; N];
    
    println!("{}皇后问题求解:\n", N);
    
    if solve_n_queen(&mut board, 0) {
        println!("找到解:");
        print_board(&board);
    } else {
        println!("无解");
    }
}
