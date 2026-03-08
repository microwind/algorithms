/*
 * 字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
 * 计算将一个字符串转换为另一个字符串所需的最少操作次数
 * 操作包括：插入、删除、替换
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

/**
 * 动态规划计算编辑距离
 * 时间复杂度: O(m × n)
 * 空间复杂度: O(m × n)
 * 
 * 参数:
 *     s1: 源字符串
 *     s2: 目标字符串
 * 返回:
 *     编辑距离
 */
int edit_distance_dp(const char* s1, const char* s2) {
    int m = strlen(s1);
    int n = strlen(s2);
    
    // dp[i][j] 表示 s1[0..i-1] 转换为 s2[0..j-1] 的最小操作数
    int dp[MAX_LEN + 1][MAX_LEN + 1];
    
    // 初始化边界
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;  // 需要i次删除
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;  // 需要j次插入
    }
    
    // 填充DP表
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // 字符相同，无需操作
            } else {
                // 取删除、插入、替换中的最小值，加1
                int delete = dp[i - 1][j];      // 删除s1[i-1]
                int insert = dp[i][j - 1];      // 插入s2[j-1]
                int replace = dp[i - 1][j - 1]; // 替换s1[i-1]为s2[j-1]
                
                dp[i][j] = 1 + (delete < insert ? 
                              (delete < replace ? delete : replace) :
                              (insert < replace ? insert : replace));
            }
        }
    }
    
    return dp[m][n];
}

/**
 * 空间优化的编辑距离
 * 只使用两行数组
 * 空间复杂度: O(min(m, n))
 * 
 * 参数:
 *     s1: 源字符串
 *     s2: 目标字符串
 * 返回:
 *     编辑距离
 */
int edit_distance_optimized(const char* s1, const char* s2) {
    const char* shorter = s1;
    const char* longer = s2;
    
    // 确保shorter是较短的字符串
    if (strlen(s1) > strlen(s2)) {
        shorter = s2;
        longer = s1;
    }
    
    int m = strlen(shorter);
    int n = strlen(longer);
    
    // 只使用两行
    int prev[MAX_LEN + 1];
    int curr[MAX_LEN + 1];
    
    // 初始化prev行
    for (int i = 0; i <= m; i++) {
        prev[i] = i;
    }
    
    for (int j = 1; j <= n; j++) {
        curr[0] = j;  // 第一列
        
        for (int i = 1; i <= m; i++) {
            if (shorter[i - 1] == longer[j - 1]) {
                curr[i] = prev[i - 1];
            } else {
                int delete = prev[i];        // 删除
                int insert = curr[i - 1];    // 插入
                int replace = prev[i - 1];   // 替换
                
                curr[i] = 1 + (delete < insert ? 
                              (delete < replace ? delete : replace) :
                              (insert < replace ? insert : replace));
            }
        }
        
        // 交换prev和curr
        for (int i = 0; i <= m; i++) {
            prev[i] = curr[i];
        }
    }
    
    return prev[m];
}

/**
 * 计算字符串相似度
 * 返回值: 0.0 - 1.0，1.0表示完全相同
 */
double similarity_ratio(const char* s1, const char* s2) {
    int max_len = strlen(s1) > strlen(s2) ? strlen(s1) : strlen(s2);
    if (max_len == 0) return 1.0;
    
    int distance = edit_distance_optimized(s1, s2);
    return 1.0 - (double)distance / max_len;
}

/**
 * 打印DP表（用于调试）
 */
void print_dp_table(const char* s1, const char* s2) {
    int m = strlen(s1);
    int n = strlen(s2);
    
    printf("\nDP表 (部分显示):\n");
    printf("    ");
    printf("  ");
    for (int j = 0; j < n; j++) {
        printf("%c ", s2[j]);
    }
    printf("\n");
    
    int dp[MAX_LEN + 1][MAX_LEN + 1];
    
    // 重新计算DP表
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int delete = dp[i - 1][j];
                int insert = dp[i][j - 1];
                int replace = dp[i - 1][j - 1];
                
                dp[i][j] = 1 + (delete < insert ? 
                              (delete < replace ? delete : replace) :
                              (insert < replace ? insert : replace));
            }
        }
    }
    
    // 打印前几行和前几列
    for (int i = 0; i <= (m < 5 ? m : 5); i++) {
        if (i == 0) {
            printf("  ");
        } else {
            printf("%c ", s1[i - 1]);
        }
        for (int j = 0; j <= (n < 5 ? n : 5); j++) {
            printf("%d ", dp[i][j]);
        }
        if (n > 5) printf("...");
        printf("\n");
    }
    if (m > 5) printf("...\n");
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("编辑距离 (Edit Distance)\n");
    printf("==================================================\n");
    
    // 测试用例数组
    struct {
        const char* s1;
        const char* s2;
    } test_cases[] = {
        {"kitten", "sitting"},
        {"sunday", "saturday"},
        {"intention", "execution"},
        {"algorithm", "logarithm"}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("\n编辑距离计算:\n");
    for (int i = 0; i < num_cases; i++) {
        const char* s1 = test_cases[i].s1;
        const char* s2 = test_cases[i].s2;
        
        int dist = edit_distance_optimized(s1, s2);
        double sim = similarity_ratio(s1, s2);
        
        printf("\n  '%s' -> '%s'\n", s1, s2);
        printf("  编辑距离: %d\n", dist);
        printf("  相似度: %.2f%%\n", sim * 100);
        
        // 为第一个测试用例打印DP表
        if (i == 0) {
            print_dp_table(s1, s2);
        }
    }
    
    printf("\n应用场景:\n");
    printf("  • 拼写检查\n");
    printf("  • DNA序列比对\n");
    printf("  • 语音识别\n");
    printf("  • 论文抄袭检测\n");
    printf("  • Git diff算法\n");
    
    printf("\n复杂度分析:\n");
    printf("  • 时间复杂度: O(m × n)\n");
    printf("  • 空间复杂度: O(min(m, n)) (优化版本)\n");
    printf("  • m, n 为字符串长度\n");
    
    return 0;
}
