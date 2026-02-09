#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
N-Queens Problem using Backtracking (C Implementation)

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
- Same column: Check column array
- Diagonal (top-left to bottom-right): Check if row - col is same
- Diagonal (top-right to bottom-left): Check if row + col is same

Time Complexity: O(n!)
Space Complexity: O(n)

Example:
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

bool is_safe(int row, int col, int* col_placement) {
    for (int r = 0; r < row; r++) {
        int c = col_placement[r];
        // Check same column
        if (c == col) return false;
        // Check diagonals
        if (abs(r - row) == abs(c - col)) return false;
    }
    return true;
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

int count_n_queens(int n) {
    int count = 0;
    int* col_placement = (int*)malloc(n * sizeof(int));

    void backtrack_count(int row) {
        if (row == n) {
            count++;
            return;
        }

        for (int col = 0; col < n; col++) {
            if (is_safe(row, col, col_placement)) {
                col_placement[row] = col;
                backtrack_count(row + 1);
            }
        }
    }

    backtrack_count(0);
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

    // Test Case 1: 4-Queens
    printf("Test 1: solveNQueens(4)\n");
    SolutionResult* result1 = solve_n_queens(4);
    printf("Found %d solutions:\n\n", result1->count);
    for (int i = 0; i < result1->count; i++) {
        printf("Solution %d:\n", i + 1);
        print_solution(&result1->solutions[i]);
        printf("\n");
    }
    free_result(result1);

    // Test Case 2: 1-Queen
    printf("Test 2: solveNQueens(1)\n");
    SolutionResult* result2 = solve_n_queens(1);
    printf("Found %d solution(s):\n\n", result2->count);
    for (int i = 0; i < result2->count; i++) {
        printf("Solution %d:\n", i + 1);
        print_solution(&result2->solutions[i]);
        printf("\n");
    }
    free_result(result2);

    // Test Case 3: Solution counts for various sizes
    printf("Test 3: Solution counts for various N:\n");
    for (int n = 1; n <= 8; n++) {
        int count = count_n_queens(n);
        printf("  N=%d: %d solutions\n", n, count);
    }
    printf("\n");

    // Test Case 4: 5-Queens
    printf("Test 4: solveNQueens(5)\n");
    SolutionResult* result4 = solve_n_queens(5);
    printf("Found %d solutions for 5-Queens\n", result4->count);
    printf("First solution:\n");
    print_solution(&result4->solutions[0]);
    free_result(result4);

    return 0;
}
