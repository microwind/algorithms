/*
 * 字符串算法 - Rabin-Karp 模式匹配
 * 使用滚动哈希实现高效的字符串匹配
 * 平均时间复杂度 O(m+n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATCHES 100
#define ALPHABET_SIZE 256  // 字符集大小
#define PRIME 101         // 用于取模的素数

/**
 * Rabin-Karp字符串匹配算法
 * 使用哈希值快速筛选可能的匹配位置
 * 
 * 参数:
 *     text: 主文本
 *     pattern: 模式串
 *     matches: 存储匹配位置的数组
 *     max_matches: 最大匹配数量
 * 返回:
 *     实际找到的匹配数量
 */
int rabin_karp_search(const char* text, const char* pattern, int* matches, int max_matches) {
    int n = strlen(text);
    int m = strlen(pattern);
    int match_count = 0;
    
    if (m > n) return 0;
    
    int pattern_hash = 0;    // 模式串的哈希值
    int text_hash = 0;       // 文本当前窗口的哈希值
    int h = 1;              // h = d^(m-1) % prime
    
    // 计算 h = ALPHABET_SIZE^(m-1) % PRIME
    for (int i = 0; i < m - 1; i++) {
        h = (ALPHABET_SIZE * h) % PRIME;
    }
    
    // 计算模式串和文本第一个窗口的哈希值
    for (int i = 0; i < m; i++) {
        pattern_hash = (ALPHABET_SIZE * pattern_hash + pattern[i]) % PRIME;
        text_hash = (ALPHABET_SIZE * text_hash + text[i]) % PRIME;
    }
    
    // 滑动窗口
    for (int i = 0; i <= n - m; i++) {
        // 哈希值匹配，需要逐个字符验证
        if (pattern_hash == text_hash) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m && match_count < max_matches) {
                matches[match_count] = i;
                match_count++;
            }
        }
        
        // 计算下一个窗口的哈希值
        if (i < n - m) {
            text_hash = (ALPHABET_SIZE * (text_hash - text[i] * h) + text[i + m]) % PRIME;
            // 处理负数情况
            if (text_hash < 0) {
                text_hash += PRIME;
            }
        }
    }
    
    return match_count;
}

/**
 * 打印匹配结果
 */
void print_rk_matches(const char* text, const char* pattern, const int* matches, int count) {
    printf("\n匹配位置: [");
    for (int i = 0; i < count; i++) {
        printf("%d", matches[i]);
        if (i < count - 1) printf(", ");
    }
    printf("]\n");
    
    if (count > 0) {
        printf("\n匹配可视化:\n");
        for (int i = 0; i < count; i++) {
            printf("  位置 %d: %s\n", matches[i], text);
            printf("           %*s%s\n", matches[i], "", pattern);
        }
    }
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("Rabin-Karp 模式匹配\n");
    printf("==================================================\n");
    
    const char* text = "ABABDABACDABABCABAB";
    const char* pattern = "ABABCABAB";
    
    printf("\n文本: %s\n", text);
    printf("模式: %s\n", pattern);
    
    int matches[MAX_MATCHES];
    int match_count = rabin_karp_search(text, pattern, matches, MAX_MATCHES);
    
    print_rk_matches(text, pattern, matches, match_count);
    
    printf("\n算法特点:\n");
    printf("  • 使用滚动哈希快速筛选\n");
    printf("  • 哈希冲突时逐个字符验证\n");
    printf("  • 适合多模式匹配场景\n");
    printf("  • 平均时间复杂度: O(m + n)\n");
    printf("  • 最坏时间复杂度: O(m × n)\n");
    
    return 0;
}
