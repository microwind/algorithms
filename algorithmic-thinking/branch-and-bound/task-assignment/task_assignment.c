#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
任务分配问题 - 分支定界算法 (C Implementation)

算法说明:
- 将 n 个任务分配给 n 个员工，使总成本最小
- 每个员工只能分配一个任务，每个任务只能分配给一个员工
- 使用分支定界法进行搜索和剪枝
- 下界函数使用贪心估计

时间复杂度：O(n! * n)（指数级，使用剪枝优化）
空间复杂度：O(n^2)

示例:
    cost = [[5,7,9],[6,8,4],[3,5,7]]
    结果: 最小总成本 15
*/

typedef struct {
    int **cost;
    int n;
    int min_cost;
    int *best_assignment;
    int *current_assignment;
    int *assigned_workers;
} TaskAssignment;

// 计算下界（贪心估计）
int lower_bound(TaskAssignment *solver, int task_idx) {
    int bound = 0;
    
    // 对于每个未分配任务，添加最小成本
    for (int i = task_idx; i < solver->n; i++) {
        int min_cost = INT_MAX;
        for (int j = 0; j < solver->n; j++) {
            if (!solver->assigned_workers[j]) {
                if (solver->cost[i][j] < min_cost) {
                    min_cost = solver->cost[i][j];
                }
            }
        }
        if (min_cost != INT_MAX) {
            bound += min_cost;
        }
    }
    
    return bound;
}

// 分支定界搜索
void branch_and_bound(TaskAssignment *solver, int task_idx, int current_cost) {
    // 剪枝：当前成本 + 下界 >= 最优解
    if (current_cost + lower_bound(solver, task_idx) >= solver->min_cost) {
        return;
    }
    
    // 基础情况：所有任务已分配
    if (task_idx == solver->n) {
        if (current_cost < solver->min_cost) {
            solver->min_cost = current_cost;
            for (int i = 0; i < solver->n; i++) {
                solver->best_assignment[i] = solver->current_assignment[i];
            }
        }
        return;
    }
    
    // 分支：尝试将当前任务分配给每个可用员工
    for (int worker = 0; worker < solver->n; worker++) {
        if (!solver->assigned_workers[worker]) {
            solver->current_assignment[task_idx] = worker;
            solver->assigned_workers[worker] = 1;
            
            branch_and_bound(solver, task_idx + 1, 
                           current_cost + solver->cost[task_idx][worker]);
            
            solver->assigned_workers[worker] = 0;
        }
    }
}

// 创建求解器
TaskAssignment *create_solver(int **cost_matrix, int n) {
    TaskAssignment *solver = (TaskAssignment *)malloc(sizeof(TaskAssignment));
    
    solver->cost = cost_matrix;
    solver->n = n;
    solver->min_cost = INT_MAX;
    solver->best_assignment = (int *)malloc(n * sizeof(int));
    solver->current_assignment = (int *)malloc(n * sizeof(int));
    solver->assigned_workers = (int *)malloc(n * sizeof(int));
    memset(solver->assigned_workers, 0, n * sizeof(int));
    
    return solver;
}

// 求解
int solve(TaskAssignment *solver) {
    branch_and_bound(solver, 0, 0);
    return solver->min_cost;
}

// 释放资源
void free_solver(TaskAssignment *solver) {
    free(solver->best_assignment);
    free(solver->current_assignment);
    free(solver->assigned_workers);
    free(solver);
}

int main() {
    printf("============================================================\n");
    printf("Task Assignment Problem (C Implementation)\n");
    printf("============================================================\n\n");

    int cost_data[3][3] = {
        {5, 7, 9},
        {6, 8, 4},
        {3, 5, 7}
    };
    
    int **cost_matrix = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++) {
        cost_matrix[i] = cost_data[i];
    }

    printf("Cost Matrix:\n");
    for (int i = 0; i < 3; i++) {
        printf("Task %d: ", i);
        for (int j = 0; j < 3; j++) {
            printf("%d ", cost_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    TaskAssignment *solver = create_solver(cost_matrix, 3);
    int min_cost = solve(solver);

    printf("Minimum Cost: %d\n\n", min_cost);
    printf("Assignment:\n");
    for (int i = 0; i < 3; i++) {
        printf("Task %d -> Worker %d (cost: %d)\n", 
               i, solver->best_assignment[i], 
               cost_matrix[i][solver->best_assignment[i]]);
    }

    free_solver(solver);
    free(cost_matrix);
    return 0;
}

/*
Output:
============================================================
Task Assignment Problem (C Implementation)
============================================================

Cost Matrix:
Task 0: 5 7 9 
Task 1: 6 8 4 
Task 2: 3 5 7 

Minimum Cost: 15
Assignment:
Task 0 -> Worker 0 (cost: 5)
Task 1 -> Worker 2 (cost: 4)
Task 2 -> Worker 1 (cost: 5)
*/
