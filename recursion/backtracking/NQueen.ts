/**
 * 回溯算法 - N皇后问题
 * 在n×n棋盘上放置n个皇后，使其互不攻击
 */

const N: number = 4; // 棋盘大小

/**
 * 打印棋盘
 * @param board 棋盘数组
 */
function printBoard(board: number[][]): void {
    for (let i = 0; i < N; i++) {
        let row: string = '';
        for (let j = 0; j < N; j++) {
            row += board[i][j] === 1 ? 'Q ' : '. ';
        }
        console.log(row);
    }
    console.log();
}

/**
 * 检查在(row, col)放置皇后是否安全
 * @param board 棋盘数组
 * @param row 行
 * @param col 列
 * @returns 是否安全
 */
function isSafe(board: number[][], row: number, col: number): boolean {
    // 检查列
    for (let i = 0; i < row; i++) {
        if (board[i][col] === 1) return false;
    }
    
    // 检查左上对角线
    for (let i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] === 1) return false;
    }
    
    // 检查右上对角线
    for (let i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] === 1) return false;
    }
    
    return true;
}

/**
 * 使用回溯求解N皇后
 * @param board 棋盘数组
 * @param row 当前行
 * @returns 是否找到解
 */
function solveNQueen(board: number[][], row: number): boolean {
    // 基础情况：所有皇后都已放置
    if (row >= N) {
        return true;
    }
    
    // 尝试在当前行的每一列放置皇后
    for (let col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            // 放置皇后
            board[row][col] = 1;
            
            // 递归：放置下一行的皇后
            if (solveNQueen(board, row + 1)) {
                return true;
            }
            
            // 回溯：撤销放置
            board[row][col] = 0;
        }
    }
    
    return false;
}

// 主程序
function main(): void {
    const board: number[][] = Array(N).fill(0).map(() => Array(N).fill(0));
    
    console.log(`${N}皇后问题求解:\n`);
    
    if (solveNQueen(board, 0)) {
        console.log("找到解:");
        printBoard(board);
    } else {
        console.log("无解");
    }
}

main();
