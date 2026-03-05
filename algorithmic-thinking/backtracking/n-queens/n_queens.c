#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
使用回溯算法的N皇后问题 (C Implementation)

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
- 同列：检查列数组
- 对角线（左上到右下）：检查row - col是否相同
- 对角线（右上到左下）：检查row + col是否相同

Time Complexity: O(n!)
Space Complexity: O(n)

示例:
    solveNQueens(4) returns 2 solutions
*/

typedef struct {
    char** board;
    int n;
} Solution;

typedef struct {
    Solution* solutions;
    int count;
    int capacity;
} SolutionResult;

void add_solution(SolutionResult* result, int n, int* col_placement) {
    if (result->count >= result->capacity) {
        result->capacity *= 2;
        result->solutions = (Solution*)realloc(result->solutions,
                                               result->capacity * sizeof(Solution));
    }

    Solution* sol = &result->solutions[result->count];
    sol->n = n;
    sol->board = (char**)malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        sol->board[i] = (char*)malloc((n + 1) * sizeof(char));
        for (int j = 0; j < n; j++) {
            sol->board[i][j] = (j == col_placement[i]) ? 'Q' : '.';
        }
        sol->board[i][n] = '\0';
    }

    result->count++;
}

/**
 * @brief 
 * 判断在 (row, col) 放皇后是否安全
 * 
 * @param row 要检查的行
 * @param col 要检查的列
 * @param col_placement 已放置的皇后列数组
 * @return true 安全
 * @return false 不安全
 */
// bool is_safe(int row, int col, int* col_placement) {
//     for (int r = 0; r < row; r++) {
//         int c = col_placement[r];
//         // Check same column
//         if (c == col) return false;
//         // Check diagonals
//         if (abs(r - row) == abs(c - col)) return false;
//     }
//     return true;
// }

/**
 * @brief 
 * 判断在 (row, col) 放皇后是否安全
 * 
 * @param row 要检查的行
 * @param col 要检查的列
 * @param col_placement 已放置的皇后列数组
 * @return int 安全返回1，不安全返回0
 */
int is_safe(int row, int col, int col_placement[]) {
    for (int i = 0; i < row; i++) {
        int placed_col = col_placement[i];

        if (placed_col == col)           // 同列冲突
            return 0;

        if (abs(placed_col - col) == row - i) // 对角线冲突
            return 0;
    }
    return 1;
}


void backtrack(int n, int row, int* col_placement, SolutionResult* result) {
    if (row == n) {
        add_solution(result, n, col_placement);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (is_safe(row, col, col_placement)) {
            col_placement[row] = col;
            backtrack(n, row + 1, col_placement, result);
        }
    }
}

SolutionResult* solve_n_queens(int n) {
    SolutionResult* result = (SolutionResult*)malloc(sizeof(SolutionResult));
    result->capacity = 100;
    result->solutions = (Solution*)malloc(result->capacity * sizeof(Solution));
    result->count = 0;

    int* col_placement = (int*)malloc(n * sizeof(int));
    backtrack(n, 0, col_placement, result);
    free(col_placement);

    return result;
}

// 回溯统计解的数量
void backtrack_count(int row, int n, int col_placement[], int *count) {
    if (row == n) {        // 找到一种合法摆放
        (*count)++;
        return;
    }

    for (int col = 0; col < n; col++) {   // 尝试当前行的每一列
        if (is_safe(row, col, col_placement)) {
            col_placement[row] = col;     // 放置皇后
            backtrack_count(row + 1, n, col_placement, count); // 递归下一行
        }
    }
}

int count_n_queens(int n) {
    int count = 0;
    int* col_placement = (int*)malloc(n * sizeof(int));

    backtrack_count(0, n, col_placement, &count);

    free(col_placement);
    return count;
}

void free_result(SolutionResult* result) {
    for (int i = 0; i < result->count; i++) {
        for (int j = 0; j < result->solutions[i].n; j++) {
            free(result->solutions[i].board[j]);
        }
        free(result->solutions[i].board);
    }
    free(result->solutions);
    free(result);
}

void print_solution(Solution* sol) {
    for (int i = 0; i < sol->n; i++) {
        printf("  %s\n", sol->board[i]);
    }
}

int main() {
    printf("=== N-Queens Problem using Backtracking ===\n\n");

    // 测试用例 1: 4-Queens
    printf("Test 1: solveNQueens(4)\n");
    SolutionResult* result1 = solve_n_queens(4);
    printf("Found %d solutions:\n\n", result1->count);
    for (int i = 0; i < result1->count; i++) {
        printf("Solution %d:\n", i + 1);
        print_solution(&result1->solutions[i]);
        printf("\n");
    }
    free_result(result1);

    // 测试用例 2: 1-Queen
    printf("Test 2: solveNQueens(1)\n");
    SolutionResult* result2 = solve_n_queens(1);
    printf("Found %d solution(s):\n\n", result2->count);
    for (int i = 0; i < result2->count; i++) {
        printf("Solution %d:\n", i + 1);
        print_solution(&result2->solutions[i]);
        printf("\n");
    }
    free_result(result2);

    // 测试用例 3: Solution counts for various sizes
    printf("Test 3: Solution counts for various N:\n");
    for (int n = 1; n <= 8; n++) {
        int count = count_n_queens(n);
        printf("  N=%d: %d solutions\n", n, count);
    }
    printf("\n");

    // 测试用例 4: 5-Queens
    printf("Test 4: solveNQueens(5)\n");
    SolutionResult* result4 = solve_n_queens(5);
    printf("Found %d solutions for 5-Queens\n", result4->count);
    printf("First solution:\n");
    print_solution(&result4->solutions[0]);
    free_result(result4);

    return 0;
}
