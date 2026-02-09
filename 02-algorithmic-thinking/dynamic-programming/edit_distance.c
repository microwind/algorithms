/**
 * 编辑距离 (Edit Distance / Levenshtein Distance) - 动态规划应用
 *
 * 问题描述：
 * 给定两个字符串，计算从一个字符串转换到另一个字符串所需的最少编辑操作数
 * 允许的操作：插入、删除、替换
 *
 * 动态规划方程：
 * if s1[i-1] == s2[j-1]:
 *     dp[i][j] = dp[i-1][j-1]
 * else:
 *     dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
 *
 * 时间复杂度: O(m * n)
 * 空间复杂度: O(m * n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define MIN2(a, b) ((a) < (b) ? (a) : (b))

/**
 * 编辑距离 - 求最少操作数
 *
 * @param s1 源字符串
 * @param s2 目标字符串
 * @return 最少编辑操作数
 */
int editDistance(const char *s1, const char *s2) {
    int m = strlen(s1);
    int n = strlen(s2);

    // dp[i][j] 表示将 s1[0:i] 转换到 s2[0:j] 的最少操作数
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // 初始化
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    // 填充 DP 表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // 字符相同，不需要操作
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // 字符不同，选择最少操作数的方案
                dp[i][j] = 1 + MIN(
                    dp[i - 1][j],      // 删除
                    dp[i][j - 1],      // 插入
                    dp[i - 1][j - 1]   // 替换
                );
            }
        }
    }

    int result = dp[m][n];

    // 释放内存
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

/**
 * 编辑距离 - 空间优化版本
 *
 * @param s1 源字符串
 * @param s2 目标字符串
 * @return 最少编辑操作数
 */
int editDistanceOptimized(const char *s1, const char *s2) {
    int m = strlen(s1);
    int n = strlen(s2);

    // 确保 s1 是较短的字符串
    if (m > n) {
        const char *temp = s1;
        s1 = s2;
        s2 = temp;
        int tmp = m;
        m = n;
        n = tmp;
    }

    // 使用两行数组来计算
    int *prev = (int *)malloc((n + 1) * sizeof(int));
    int *curr = (int *)malloc((n + 1) * sizeof(int));

    // 初始化 prev 行
    for (int j = 0; j <= n; j++) {
        prev[j] = j;
    }

    for (int i = 1; i <= m; i++) {
        curr[0] = i;

        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + MIN(prev[j], curr[j - 1], prev[j - 1]);
            }
        }

        // 交换行
        int *temp = prev;
        prev = curr;
        curr = temp;
    }

    int result = prev[n];

    free(prev);
    free(curr);

    return result;
}

/**
 * 测试函数
 */
int main() {
    printf("=== 编辑距离问题 ===\n\n");

    // 测试用例1：基本编辑距离
    printf("1. 基本编辑距离\n");
    const char *s1_1 = "horse";
    const char *s2_1 = "ros";
    printf("字符串1: %s\n", s1_1);
    printf("字符串2: %s\n", s2_1);
    printf("编辑距离: %d\n\n", editDistance(s1_1, s2_1));

    // 测试用例2：相同字符串
    printf("2. 相同字符串\n");
    const char *s1_2 = "hello";
    const char *s2_2 = "hello";
    printf("字符串1: %s\n", s1_2);
    printf("字符串2: %s\n", s2_2);
    printf("编辑距离: %d\n\n", editDistance(s1_2, s2_2));

    // 测试用例3：空字符串
    printf("3. 空字符串\n");
    const char *s1_3 = "abc";
    const char *s2_3 = "";
    printf("字符串1: %s\n", s1_3);
    printf("字符串2: %s\n", s2_3);
    printf("编辑距离: %d\n\n", editDistance(s1_3, s2_3));

    // 测试用例4：不同长度的字符串
    printf("4. 不同长度的字符串\n");
    const char *s1_4 = "intention";
    const char *s2_4 = "execution";
    printf("字符串1: %s\n", s1_4);
    printf("字符串2: %s\n", s2_4);
    printf("编辑距离: %d\n", editDistance(s1_4, s2_4));
    printf("编辑距离（优化）: %d\n", editDistanceOptimized(s1_4, s2_4));

    return 0;
}
