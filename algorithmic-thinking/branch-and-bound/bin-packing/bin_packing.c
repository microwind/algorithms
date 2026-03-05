#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
装箱问题 - 分支定界算法 (C Implementation)

算法说明:
- 将 n 个物品装入最少数量的容量相同的箱子中
- 使用分支定界法进行搜索和剪枝
- 首先按降序排列物品以减少搜索空间
- 使用下界函数进行剪枝优化

时间复杂度：指数级（使用剪枝优化）
空间复杂度：O(最优箱子数 * 物品数)

示例:
    items = [7, 5, 5, 3, 3, 3, 2], capacity = 10
    结果: 最少 3 个箱子
*/

typedef struct {
    int *items;
    int n;
    int bin_capacity;
    int min_bins;
    int **best_packing;
    int *best_bin_sizes;
    int **current_bins;
    int *current_bin_sizes;
    int current_bins_count;
} BinPackingSolver;

// 比较函数：用于排序（降序）
int compare_desc(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

// 计算下界
int lower_bound(BinPackingSolver *solver, int item_idx) {
    int total_weight = 0;
    for (int i = item_idx; i < solver->n; i++) {
        total_weight += solver->items[i];
    }
    return (total_weight + solver->bin_capacity - 1) / solver->bin_capacity;
}

// 计算箱子总重
int sum_bin(BinPackingSolver *solver, int bin_idx) {
    int sum = 0;
    for (int i = 0; i < solver->current_bin_sizes[bin_idx]; i++) {
        sum += solver->current_bins[bin_idx][i];
    }
    return sum;
}

// 分支定界搜索
void branch_and_bound(BinPackingSolver *solver, int item_idx) {
    // 剪枝：当前箱数 + 下界 >= 最优箱数
    if (solver->current_bins_count + lower_bound(solver, item_idx) >= solver->min_bins) {
        return;
    }

    // 基础情况：所有物品已装
    if (item_idx == solver->n) {
        if (solver->current_bins_count < solver->min_bins) {
            solver->min_bins = solver->current_bins_count;
            
            // 复制最优装箱方案
            for (int i = 0; i < solver->current_bins_count; i++) {
                solver->best_bin_sizes[i] = solver->current_bin_sizes[i];
                for (int j = 0; j < solver->current_bin_sizes[i]; j++) {
                    solver->best_packing[i][j] = solver->current_bins[i][j];
                }
            }
        }
        return;
    }

    // 尝试把物品放入现有的箱子
    int item = solver->items[item_idx];
    int placed = 0;

    for (int bin_idx = 0; bin_idx < solver->current_bins_count; bin_idx++) {
        if (sum_bin(solver, bin_idx) + item <= solver->bin_capacity) {
            solver->current_bins[bin_idx][solver->current_bin_sizes[bin_idx]] = item;
            solver->current_bin_sizes[bin_idx]++;
            branch_and_bound(solver, item_idx + 1);
            solver->current_bin_sizes[bin_idx]--;
            placed = 1;
            break;
        }
    }

    // 尝试加入一个新箱子
    if (!placed && solver->current_bins_count < solver->n) {
        solver->current_bins[solver->current_bins_count][0] = item;
        solver->current_bin_sizes[solver->current_bins_count] = 1;
        solver->current_bins_count++;
        branch_and_bound(solver, item_idx + 1);
        solver->current_bins_count--;
    }
}

// 初始化装箱求解器
BinPackingSolver *create_solver(int *items, int n, int capacity) {
    BinPackingSolver *solver = (BinPackingSolver *)malloc(sizeof(BinPackingSolver));
    
    solver->items = (int *)malloc(n * sizeof(int));
    memcpy(solver->items, items, n * sizeof(int));
    qsort(solver->items, n, sizeof(int), compare_desc);
    
    solver->n = n;
    solver->bin_capacity = capacity;
    solver->min_bins = n;
    
    solver->best_packing = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        solver->best_packing[i] = (int *)malloc(n * sizeof(int));
    }
    solver->best_bin_sizes = (int *)malloc(n * sizeof(int));
    
    solver->current_bins = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        solver->current_bins[i] = (int *)malloc(n * sizeof(int));
    }
    solver->current_bin_sizes = (int *)malloc(n * sizeof(int));
    memset(solver->current_bin_sizes, 0, n * sizeof(int));
    
    solver->current_bins_count = 0;
    
    return solver;
}

// 解决装箱问题
int solve(BinPackingSolver *solver) {
    branch_and_bound(solver, 0);
    return solver->min_bins;
}

// 释放资源
void free_solver(BinPackingSolver *solver) {
    free(solver->items);
    for (int i = 0; i < solver->n; i++) {
        free(solver->best_packing[i]);
        free(solver->current_bins[i]);
    }
    free(solver->best_packing);
    free(solver->current_bins);
    free(solver->best_bin_sizes);
    free(solver->current_bin_sizes);
    free(solver);
}

int main() {
    printf("装箱问题 - 分支定界算法 (C Implementation)\n");
    printf("================================================\n\n");

    // 测试用例
    int items[] = {7, 5, 5, 3, 3, 3, 2};
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 10;

    printf("物品重量: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", items[i]);
    }
    printf("\n箱子容量: %d\n\n", capacity);

    BinPackingSolver *solver = create_solver(items, n, capacity);
    int min_bins = solve(solver);

    printf("最少箱子数: %d\n\n", min_bins);
    for (int i = 0; i < min_bins; i++) {
        printf("箱子 %d: ", i);
        int bin_sum = 0;
        for (int j = 0; j < solver->best_bin_sizes[i]; j++) {
            printf("%d ", solver->best_packing[i][j]);
            bin_sum += solver->best_packing[i][j];
        }
        printf("(重量: %d)\n", bin_sum);
    }

    free_solver(solver);
    return 0;
}

/*
Output:
装箱问题 - 分支定界算法 (C Implementation)
================================================

物品重量: 7 5 5 3 3 3 2 
箱子容量: 10

最少箱子数: 3

箱子 0: 7 3 (重量: 10)
箱子 1: 5 5 (重量: 10)
箱子 2: 3 3 2 (重量: 8)
*/
