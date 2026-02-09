/**
 * 0-1 背包问题 - 动态规划的经典应用
 *
 * 问题描述：
 * 给定 n 件物品和一个容量为 W 的背包，每件物品有一个重量和一个价值
 * 在背包容量限制下，选择物品使得总价值最大
 *
 * 动态规划方程：
 * dp[i][w] = max(
 *     dp[i-1][w],
 *     dp[i-1][w-weight[i]] + value[i]
 * )
 *
 * 时间复杂度: O(n * W)
 * 空间复杂度: O(n * W)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * 0-1 背包问题求解
 *
 * @param weights 物品重量数组
 * @param values 物品价值数组
 * @param n 物品数量
 * @param capacity 背包容量
 * @return 背包能容纳的最大价值
 */
int knapsack(int *weights, int *values, int n, int capacity) {
    // 创建 dp 表：dp[i][w] 表示前 i 件物品，容量为 w 时的最大价值
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
        memset(dp[i], 0, (capacity + 1) * sizeof(int));
    }

    // 填充 dp 表
    for (int i = 1; i <= n; i++) {
        int weight = weights[i - 1];
        int value = values[i - 1];

        for (int w = 0; w <= capacity; w++) {
            if (weight <= w) {
                // 选择或不选择
                dp[i][w] = MAX(
                    dp[i - 1][w],
                    dp[i - 1][w - weight] + value
                );
            } else {
                // 物品太重
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][capacity];

    // 释放内存
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

/**
 * 0-1 背包问题 - 空间优化版本
 *
 * @param weights 物品重量数组
 * @param values 物品价值数组
 * @param n 物品数量
 * @param capacity 背包容量
 * @return 背包能容纳的最大价值
 */
int knapsack_optimized(int *weights, int *values, int n, int capacity) {
    // dp[w] 表示容量为 w 时的最大价值
    int *dp = (int *)malloc((capacity + 1) * sizeof(int));
    memset(dp, 0, (capacity + 1) * sizeof(int));

    // 处理每件物品
    for (int i = 0; i < n; i++) {
        int weight = weights[i];
        int value = values[i];

        // 从后向前遍历容量
        for (int w = capacity; w >= weight; w--) {
            dp[w] = MAX(dp[w], dp[w - weight] + value);
        }
    }

    int result = dp[capacity];
    free(dp);

    return result;
}

/**
 * 测试函数
 */
int main() {
    printf("=== 0-1 背包问题 ===\n\n");

    // 测试用例1：基本背包问题
    printf("1. 基本背包问题\n");
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int n = 4;
    int capacity = 8;

    printf("物品重量: ");
    for (int i = 0; i < n; i++) printf("%d ", weights[i]);
    printf("\n物品价值: ");
    for (int i = 0; i < n; i++) printf("%d ", values[i]);
    printf("\n背包容量: %d\n", capacity);

    int max_value = knapsack(weights, values, n, capacity);
    printf("最大价值: %d\n\n", max_value);

    // 测试用例2：空间优化版本
    printf("2. 空间优化版本\n");
    int max_value_opt = knapsack_optimized(weights, values, n, capacity);
    printf("最大价值（优化）: %d\n\n", max_value_opt);

    // 测试用例3：容量较大
    printf("3. 容量较大的背包\n");
    int weights2[] = {1, 2, 3, 4, 5};
    int values2[] = {1, 3, 5, 7, 9};
    int n2 = 5;
    int capacity2 = 10;

    printf("物品重量: ");
    for (int i = 0; i < n2; i++) printf("%d ", weights2[i]);
    printf("\n物品价值: ");
    for (int i = 0; i < n2; i++) printf("%d ", values2[i]);
    printf("\n背包容量: %d\n", capacity2);

    int max_value2 = knapsack(weights2, values2, n2, capacity2);
    printf("最大价值: %d\n", max_value2);

    return 0;
}
