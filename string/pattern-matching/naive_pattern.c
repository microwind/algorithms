/*
 * 字符串算法 - 朴素模式匹配 (Naive Pattern Matching)
 * 逐个字符比较，时间复杂度 O(m*n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 朴素字符串匹配算法
 * 逐个位置比较文本和模式串
 * 
 * 参数:
 *     text: 主文本字符串
 *     pattern: 要查找的模式串
 *     matches: 存储匹配位置的数组
 *     max_matches: 最大匹配数量
 * 返回:
 *     实际找到的匹配数量
 */
int naive_search(const char* text, const char* pattern, int* matches, int max_matches) {
    int n = strlen(text);
    int m = strlen(pattern);
    int match_count = 0;
    
    // 遍历文本的每个可能位置
    for (int i = 0; i <= n - m; i++) {
        int j;
        // 比较从位置i开始的m个字符
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;  // 不匹配，跳出内层循环
            }
        }
        
        // 如果j等于m，说明完全匹配
        if (j == m && match_count < max_matches) {
            matches[match_count] = i;
            match_count++;
        }
    }
    
    return match_count;
}

/**
 * 统计匹配次数
 */
int naive_search_count(const char* text, const char* pattern) {
    int matches[100];  // 假设最多100个匹配
    return naive_search(text, pattern, matches, 100);
}

/**
 * 打印匹配可视化
 */
void print_matches(const char* text, const char* pattern, const int* matches, int count) {
    if (count == 0) {
        printf("没有找到匹配\n");
        return;
    }
    
    printf("\n匹配可视化:\n");
    for (int i = 0; i < count; i++) {
        printf("  位置 %d: %s\n", matches[i], text);
        printf("           %*s%s\n", matches[i], "", pattern);
    }
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("朴素模式匹配 (Naive Pattern Matching)\n");
    printf("==================================================\n");
    
    const char* text = "ABABDABACDABABCABAB";
    const char* pattern = "ABABCABAB";
    
    printf("\n文本: %s\n", text);
    printf("模式: %s\n", pattern);
    
    int matches[100];
    int match_count = naive_search(text, pattern, matches, 100);
    
    printf("\n匹配位置: [");
    for (int i = 0; i < match_count; i++) {
        printf("%d", matches[i]);
        if (i < match_count - 1) printf(", ");
    }
    printf("]\n");
    
    print_matches(text, pattern, matches, match_count);
    
    printf("\n复杂度分析:\n");
    printf("  时间复杂度: O(m × n)\n");
    printf("  空间复杂度: O(1)\n");
    printf("  m = 模式串长度, n = 文本长度\n");
    
    return 0;
}
