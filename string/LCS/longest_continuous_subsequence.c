#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
最长公共子序列（LCS）问题有两种方式定义子序列，一种是子序列不要求连续，一种是子序列要求连续。
下面介绍要求子序列必须是连续的情况下，如何用算法解决最长公共子序列问题。

以两个字符串 “abcdea”和“aebcda”为例，如果子序列不要求连续，其最长公共子序列为“abcda”，
如果子序列要求是连续，则其最长公共子序列应为“bcd”。在这种情况下，有可能两个字符串出现多个长度相同的
公共子串，比如“askdfiryetd”和“trkdffirey”两个字符串就存在两个长度为3的公共子串，分别是“kdf”和“fir”，
因此问题的性质发生了变化，需要找出两个字符串所有可能存在公共子串的情况，然后取最长的一个，如果有多个
最长的公共子串，只取其中一个即可。
*/

/**
 * 最长公共子串（连续）求解函数
 * 
 * 功能：找到两个字符串中最长的连续公共子串（字符顺序一致且连续相邻）
 * 
 * 参数：
 *   str1: 第一个输入字符串
 *   str2: 第二个输入字符串
 *   result: 用于存储最长公共子串的指针
 * 
 * 返回值：
 *   最长公共子串的长度
 */
int longest_continuous_subsequence(const char* str1, const char* str2, char* result) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    // 特殊情况处理
    if (len1 == 0 || len2 == 0) {
        result[0] = '\0';
        return 0;
    }
    
    // 创建DP表：dp[i][j]表示以str1[i-1]和str2[j-1]为结尾的最长公共子串长度
    int** dp = (int**)malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int*)calloc(len2 + 1, sizeof(int));
    }
    
    int max_length = 0;  // 记录最长公共子串的长度
    int end_index = 0;   // 记录最长公共子串在str1中的结束索引
    
    // 填充DP表
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i-1] == str2[j-1]) {
                // 当前字符相同，长度 = 前一位的长度 + 1（连续累加）
                dp[i][j] = dp[i-1][j-1] + 1;
                
                // 更新最长长度和结束索引
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                    end_index = i;  // 记录在str1中的结束位置
                }
            } else {
                // 字符不同，连续中断，长度重置为0
                dp[i][j] = 0;
            }
        }
    }
    
    // 提取最长公共子串
    if (max_length > 0) {
        int start_index = end_index - max_length;
        strncpy(result, str1 + start_index, max_length);
        result[max_length] = '\0';
    } else {
        result[0] = '\0';
    }
    
    // 释放内存
    for (int i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return max_length;
}

// 检查字符串是否在字符串数组中
bool is_in_array(const char* str, const char* array[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(str, array[i]) == 0) {
            return true;
        }
    }
    return false;
}

// 测试用例
void test_longest_continuous_subsequence() {
    // 测试用例结构体 - 增大possible_results数组大小以容纳所有测试数据
    typedef struct {
        const char* s1;
        const char* s2;
        int expected_len;
        const char* possible_results[5];  // 增大为5以容纳最多5个可能结果
        int results_count;
    } TestCase;
    
    TestCase test_cases[] = {
        {"ABCBDAB", "BDCAB", 2, {"BC", "AB"}, 2},
        {"HELLO", "HELLO", 5, {"HELLO"}, 1},
        {"ABCDEF", "ACE", 1, {"A", "C", "E"}, 3},
        {"ABCDXYZ", "XYZABCD", 4, {"ABCD"}, 1},
        {"12345", "54321", 1, {"1", "2", "3", "4", "5"}, 5},  // 现在可以容纳5个结果
        {"ABABC", "BABCA", 4, {"ABCA", "BABC"}, 2}
    };
    int test_count = sizeof(test_cases) / sizeof(test_cases[0]);
    
    char result[100];  // 存储测试结果
    
    for (int i = 0; i < test_count; i++) {
        printf("测试用例 %d:\n", i + 1);
        printf("字符串1: %s\n", test_cases[i].s1);
        printf("字符串2: %s\n", test_cases[i].s2);
        
        int actual_len = longest_continuous_subsequence(
            test_cases[i].s1, 
            test_cases[i].s2, 
            result
        );
        
        bool len_match = (actual_len == test_cases[i].expected_len);
        bool result_match = is_in_array(result, test_cases[i].possible_results, test_cases[i].results_count);
        
        printf("预期长度: %d, 实际长度: %d → %s\n",
               test_cases[i].expected_len, actual_len, len_match ? "通过" : "失败");
        printf("预期结果之一: %s, 实际结果: %s → %s\n",
               test_cases[i].possible_results[0], result, result_match ? "通过" : "失败");
        printf("测试结果: %s\n\n", (len_match && result_match) ? "全部通过" : "存在问题");
    }
}

int main() {
    // 示例
    const char* s1 = "ABCBDAB";
    const char* s2 = "BDCAB";
    char result[100];
    int length = longest_continuous_subsequence(s1, s2, result);
    
    printf("示例:\n");
    printf("字符串1: %s\n", s1);
    printf("字符串2: %s\n", s2);
    printf("最长公共子串长度: %d\n", length);
    printf("最长公共子串: %s\n\n", result);
    
    // 运行测试
    test_longest_continuous_subsequence();
    
    return 0;
}

/**
jarry@Mac LCS % gcc longest_continuous_subsequence.c
jarry@Mac LCS % ./a.out 
示例:
字符串1: ABCBDAB
字符串2: BDCAB
最长公共子串长度: 2
最长公共子串: AB

测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 2, 实际长度: 2 → 通过
预期结果之一: BC, 实际结果: AB → 通过
测试结果: 全部通过

测试用例 2:
字符串1: HELLO
字符串2: HELLO
预期长度: 5, 实际长度: 5 → 通过
预期结果之一: HELLO, 实际结果: HELLO → 通过
测试结果: 全部通过

测试用例 3:
字符串1: ABCDEF
字符串2: ACE
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCDXYZ
字符串2: XYZABCD
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCD, 实际结果: ABCD → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 12345
字符串2: 54321
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: 1, 实际结果: 1 → 通过
测试结果: 全部通过

测试用例 6:
字符串1: ABABC
字符串2: BABCA
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: ABCA, 实际结果: BABC → 通过
测试结果: 全部通过
 */