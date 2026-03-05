// 0-1背包分支限界法

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 32

int n, capacity;
int weights[MAX_N], values[MAX_N];
int best_items[MAX_N], cur_items[MAX_N];
int max_profit = 0;

// 按价值/重量比降序排序
void sort_items(int *order) {
    double ratio[MAX_N];
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)values[i] / weights[i];
        order[i] = i;
    }
    // 简单冒泡排序按价值/重量比降序
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // 交换 order[i] 和 order[j] 以按 ratio 降序排序
            if (ratio[order[i]] < ratio[order[j]]) {
                int tmp = order[i]; order[i] = order[j]; order[j] = tmp;
            }
        }
    }
}

// 上界估计（分数背包）
int upper_bound(int idx, int weight, int profit, int *order) {
    if (weight >= capacity) return profit;
    double bound = profit;
    int remain = capacity - weight;
    // 计算分数背包的上界
    for (int i = idx; i < n; i++) {
        int k = order[i];
        // 若当前物品重量不超过剩余容量，则直接加入
        if (weights[k] <= remain) {
            bound += values[k];
            remain -= weights[k];
        // 否则加入剩余容量的分数部分
        } else {
            bound += (double)values[k] * remain / weights[k];
            break;
        }
    }
    return (int)bound;
}

void branch_and_bound(int idx, int weight, int profit, int *order) {
    // 剪枝：若当前上界不超过最大利润，则无需继续搜索
    if (upper_bound(idx, weight, profit, order) <= max_profit) return;
    // 基础情况：到达物品列表末尾
    if (idx == n) {
        if (profit > max_profit) {
            max_profit = profit;
            memcpy(best_items, cur_items, sizeof(int) * n);
        }
        return;
    }
    int k = order[idx];
    // 分支1：选当前物品
    if (weight + weights[k] <= capacity) {
        cur_items[k] = 1;
        branch_and_bound(idx + 1, weight + weights[k], profit + values[k], order);
        cur_items[k] = 0;
    }
    // 分支2：不选当前物品
    branch_and_bound(idx + 1, weight, profit, order);
}

int main() {
    printf("==============================\n");
    printf("0-1 Knapsack Optimization (C)\n");
    printf("==============================\n\n");
    // Test case 1
    n = 4; capacity = 8;
    int w1[4] = {2, 3, 4, 5};
    int v1[4] = {3, 4, 5, 6};
    memcpy(weights, w1, sizeof(w1));
    memcpy(values, v1, sizeof(v1));
    int order[MAX_N];
    sort_items(order);
    memset(cur_items, 0, sizeof(cur_items));
    max_profit = 0;
    branch_and_bound(0, 0, 0, order);
    printf("Test Case 1:\n");
    printf("Weights: "); for (int i = 0; i < n; i++) printf("%d ", weights[i]); printf("\n");
    printf("Values:  "); for (int i = 0; i < n; i++) printf("%d ", values[i]); printf("\n");
    printf("Capacity: %d\n", capacity);
    printf("Maximum Profit: %d\n", max_profit);
    printf("Selected Items: ");
    int wsum = 0;
    for (int i = 0; i < n; i++) if (best_items[i]) { printf("%d ", i); wsum += weights[i]; }
    printf("\nTotal Weight: %d\n", wsum);
    // Test case 2
    printf("\n==============================\n");
    n = 5; capacity = 10;
    int w2[5] = {5, 4, 3, 4, 2};
    int v2[5] = {10, 40, 30, 50, 35};
    memcpy(weights, w2, sizeof(w2));
    memcpy(values, v2, sizeof(v2));
    sort_items(order);
    memset(cur_items, 0, sizeof(cur_items));
    max_profit = 0;
    branch_and_bound(0, 0, 0, order);
    printf("Test Case 2:\n");
    printf("Weights: "); for (int i = 0; i < n; i++) printf("%d ", weights[i]); printf("\n");
    printf("Values:  "); for (int i = 0; i < n; i++) printf("%d ", values[i]); printf("\n");
    printf("Capacity: %d\n", capacity);
    printf("Maximum Profit: %d\n", max_profit);
    printf("Selected Items: ");
    wsum = 0;
    for (int i = 0; i < n; i++) if (best_items[i]) { printf("%d ", i); wsum += weights[i]; }
    printf("\nTotal Weight: %d\n", wsum);
    return 0;
}
