/*
*
 * 最长递增子序列 (LIS) - 动态规划应用
 *
 * 问题描述：
 * 给定一个无序整数数组，找出其中最长递增子序列的长度
 * 子序列是指从原序列中删除零个或多个元素后得到的序列
 *
 * 例如：[10, 9, 2, 5, 3, 7, 101, 18]
 * 最长递增子序列：[2, 3, 7, 101] 或 [2, 3, 7, 18]
 *
 * 动态规划方程：
 * dp[i] = 1 + max(dp[j]) for all j < i and arr[j] < arr[i]
 *
 * 时间复杂度: O(n²) 基础DP
 * 空间复杂度: O(n)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*
*
 * 最长递增子序列 - 基础DP方案
 *
 * @param arr 整数数组
 * @param n 数组长度
 * @return 最长递增子序列的长度
*/
int longest_increasing_subsequence(int *arr, int n) {
    if (n == 0) return 0;

    // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    // 构建 DP 表
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // 如果 arr[j] < arr[i]，可以扩展以 arr[j] 结尾的 LIS
            if (arr[j] < arr[i]) {
                dp[i] = MAX(dp[i], dp[j] + 1);
            }
        }
    }

    // 找到最大值
    int max_length = dp[0];
    for (int i = 1; i < n; i++) {
        max_length = MAX(max_length, dp[i]);
    }

    free(dp);
    return max_length;
}

/*
*
 * 最长递增子序列 - 返回子序列本身
 *
 * @param arr 整数数组
 * @param n 数组长度
 * @param out_lis 输出数组，存储LIS
 * @return 最长递增子序列的长度
*/
int longest_increasing_subsequence_with_sequence(int *arr, int n, int *out_lis) {
    if (n == 0) return 0;

    // dp[i] 表示以 arr[i] 结尾的最长递增子序列长度
    int *dp = (int *)malloc(n * sizeof(int));
    // parent[i] 表示以 arr[i] 结尾的 LIS 中，前一个元素的索引
    int *parent = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        parent[i] = -1;
    }

    // 构建 DP 表
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }

    // 找到最长序列的结尾位置
    int max_length = dp[0];
    int max_index = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > max_length) {
            max_length = dp[i];
            max_index = i;
        }
    }

    // 反向追踪构建最长子序列
    int idx = max_index;
    int pos = max_length - 1;
    while (idx != -1 && pos >= 0) {
        out_lis[pos] = arr[idx];
        idx = parent[idx];
        pos--;
    }

    free(dp);
    free(parent);
    return max_length;
}

/*
*
 * 测试函数
*/
int main() {
    printf("=== 最长递增子序列 ===\n\n");

    // 测试用例1：基本数组
    printf("1. 基本数组\n");
    int arr1[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("数组: ");
    for (int i = 0; i < n1; i++) printf("%d ", arr1[i]);
    printf("\nLIS 长度: %d\n\n", longest_increasing_subsequence(arr1, n1));

    // 测试用例2：已排序数组
    printf("2. 已排序数组\n");
    int arr2[] = {1, 3, 6, 7, 9, 4, 10, 5, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("数组: ");
    for (int i = 0; i < n2; i++) printf("%d ", arr2[i]);
    printf("\n");

    int *lis = (int *)malloc(n2 * sizeof(int));
    int length = longest_increasing_subsequence_with_sequence(arr2, n2, lis);
    printf("LIS 长度: %d\n");
    printf("一个 LIS: ");
    for (int i = 0; i < length; i++) printf("%d ", lis[i]);
    printf("\n\n");
    free(lis);

    // 测试用例3：包含重复元素
    printf("3. 包含重复元素\n");
    int arr3[] = {1, 3, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("数组: ");
    for (int i = 0; i < n3; i++) printf("%d ", arr3[i]);
    printf("\nLIS 长度: %d\n\n", longest_increasing_subsequence(arr3, n3));

    // 测试用例4：单调递减
    printf("4. 单调递减\n");
    int arr4[] = {5, 4, 3, 2, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("数组: ");
    for (int i = 0; i < n4; i++) printf("%d ", arr4[i]);
    printf("\nLIS 长度: %d\n", longest_increasing_subsequence(arr4, n4));

    return 0;
}
