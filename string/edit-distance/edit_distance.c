/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * 字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
 * 
 * 算法原理：
 * 1. 计算将一个字符串转换为另一个字符串所需的最少操作次数。
 * 2. 操作包括：插入、删除、替换。
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)，可优化至 O(min(m, n))
 */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) MIN(a, MIN(b, c))

/**
 * 动态规划版本 - 计算编辑距离
 */
int edit_distance(const char* s1, const char* s2) {
    int n = strlen(s1);
    int m = strlen(s2);
    
    // 创建二维数组
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((m + 1) * sizeof(int));
    }

    // 初始化边界
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + MIN3(
                    dp[i - 1][j],    // 删除
                    dp[i][j - 1],    // 插入
                    dp[i - 1][j - 1] // 替换
                );
            }
        }
    }

    int result = dp[n][m];

    // 释放内存
    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);

    return result;
}

/**
 * 空间优化后的动态规划版本
 */
int edit_distance_optimized(const char* s1, const char* s2) {
    int n = strlen(s1);
    int m = strlen(s2);
    
    if (n < m) {
        const char* tmp = s1;
        s1 = s2;
        s2 = tmp;
        int t = n;
        n = m;
        m = t;
    }

    int* prev = (int*)malloc((m + 1) * sizeof(int));
    int* curr = (int*)malloc((m + 1) * sizeof(int));

    for (int j = 0; j <= m; j++) prev[j] = j;

    for (int i = 1; i <= n; i++) {
        curr[0] = i;
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + MIN3(prev[j], curr[j - 1], prev[j - 1]);
            }
        }
        memcpy(prev, curr, (m + 1) * sizeof(int));
    }

    int result = prev[m];
    free(prev);
    free(curr);
    return result;
}

/**
 * 计算相似度
 */
double get_similarity_ratio(const char* s1, const char* s2) {
    int dist = edit_distance_optimized(s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int max_len = len1 > len2 ? len1 : len2;
    if (max_len == 0) return 1.0;
    return 1.0 - (double)dist / max_len;
}

/**
 * 打印编辑操作步骤
 */
void print_edit_operations(const char* s1, const char* s2) {
    int n = strlen(s1);
    int m = strlen(s2);
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((m + 1) * sizeof(int));
    }
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + MIN3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }

    printf("操作步骤: ");
    int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && s1[i - 1] == s2[j - 1]) {
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            printf("替换 '%c' 为 '%c' <- ", s1[i - 1], s2[j - 1]);
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            printf("删除 '%c' <- ", s1[i - 1]);
            i--;
        } else {
            printf("插入 '%c' <- ", s2[j - 1]);
            j--;
        }
    }
    printf("开始\n");

    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);
}

int main() {
    printf("====================================================\n");
    printf("编辑距离 (Edit Distance) - C 实现\n");
    printf("====================================================\n");

    const char* test_cases[][2] = {
        {"kitten", "sitting"},
        {"sunday", "saturday"},
        {"abc", ""},
        {"", "abc"},
        {"same", "same"}
    };

    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_cases; i++) {
        const char* s1 = test_cases[i][0];
        const char* s2 = test_cases[i][1];
        printf("\n源字符串: \"%s\"\n", s1);
        printf("目标字符串: \"%s\"\n", s2);
        printf("最小编辑距离 (DP): %d\n", edit_distance(s1, s2));
        printf("最小编辑距离 (优化DP): %d\n", edit_distance_optimized(s1, s2));
        printf("相似度: %.2f%%\n", get_similarity_ratio(s1, s2) * 100);
        if (strlen(s1) < 10 && strlen(s2) < 10) {
            print_edit_operations(s1, s2);
        }
    }

    return 0;
}
