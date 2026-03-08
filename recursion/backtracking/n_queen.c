/*
 * 回溯算法 - N皇后问题
 * 在n×n棋盘上放置n个皇后，使其互不攻击
 */
#include <stdio.h>
#include <stdlib.h>

#define N 4  // 棋盘大小

// 打印棋盘
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

// 检查在(row, col)放置皇后是否安全
int isSafe(int board[N][N], int row, int col) {
    // 检查列
    for (int i = 0; i < row; i++) {
        if (board[i][col]) return 0;
    }
    
    // 检查左上对角线
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return 0;
    }
    
    // 检查右上对角线
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) return 0;
    }
    
    return 1;
}

// 使用回溯求解N皇后
int solveNQueen(int board[N][N], int row) {
    // 基础情况：所有皇后都已放置
    if (row >= N) {
        return 1;
    }
    
    // 尝试在当前行的每一列放置皇后
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            // 放置皇后
            board[row][col] = 1;
            
            // 递归：放置下一行的皇后
            if (solveNQueen(board, row + 1)) {
                return 1;
            }
            
            // 回溯：撤销放置
            board[row][col] = 0;
        }
    }
    
    return 0;
}

int main() {
    int board[N][N] = {0};
    
    printf("%d皇后问题求解:\n\n", N);
    
    if (solveNQueen(board, 0)) {
        printf("找到解:\n");
        printBoard(board);
    } else {
        printf("无解\n");
    }
    
    return 0;
}
