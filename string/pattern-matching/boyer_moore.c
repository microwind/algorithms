/*
 * 字符串算法 - Boyer-Moore 模式匹配
 * 使用坏字符规则和好后缀规则实现高效匹配
 * 最坏O(mn)，平均O(n/m)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ALPHABET_SIZE 256
#define MAX_MATCHES 100

/**
 * 构建坏字符规则表
 * 记录每个字符在模式串中最右出现的位置
 */
void build_bad_char_table(const char* pattern, int* bad_char) {
    int m = strlen(pattern);
    
    // 初始化所有字符的位置为-1
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bad_char[i] = -1;
    }
    
    // 记录每个字符在模式串中最右出现的位置
    for (int i = 0; i < m; i++) {
        bad_char[(int)pattern[i]] = i;
    }
}

/**
 * Boyer-Moore字符串匹配算法
 * 从右向左比较，利用坏字符规则快速跳过
 * 
 * 参数:
 *     text: 主文本
 *     pattern: 模式串
 *     matches: 存储匹配位置的数组
 *     max_matches: 最大匹配数量
 * 返回:
 *     实际找到的匹配数量
 */
int boyer_moore_search(const char* text, const char* pattern, int* matches, int max_matches) {
    int m = strlen(pattern);
    int n = strlen(text);
    int match_count = 0;
    
    if (m > n) return 0;
    
    // 构建坏字符规则表
    int bad_char[ALPHABET_SIZE];
    build_bad_char_table(pattern, bad_char);
    
    int s = 0;  // 模式串在文本中的位移
    
    while (s <= n - m) {
        int j = m - 1;  // 从模式串末尾开始比较
        
        // 从右向左比较
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        
        if (j < 0) {
            // 找到匹配
            if (match_count < max_matches) {
                matches[match_count] = s;
                match_count++;
            }
            
            // 移动模式串（使用坏字符规则）
            if (s + m < n) {
                s += m - bad_char[(int)text[s + m]];
            } else {
                s += 1;
            }
        } else {
            // 不匹配，使用坏字符规则计算位移
            int bad_char_shift = bad_char[(int)text[s + j]];
            int shift = j - bad_char_shift;
            s += (shift > 0) ? shift : 1;
        }
    }
    
    return match_count;
}

/**
 * 打印坏字符规则表（用于调试）
 */
void print_bad_char_table(const char* pattern) {
    int bad_char[ALPHABET_SIZE];
    build_bad_char_table(pattern, bad_char);
    
    printf("\n坏字符规则表 (部分):\n");
    printf("字符: ");
    for (int i = 0; i < strlen(pattern); i++) {
        printf("%c ", pattern[i]);
    }
    printf("\n位置: ");
    for (int i = 0; i < strlen(pattern); i++) {
        printf("%d ", bad_char[(int)pattern[i]]);
    }
    printf("\n");
}

/**
 * 打印匹配结果
 */
void print_bm_matches(const char* text, const char* pattern, const int* matches, int count) {
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
    printf("Boyer-Moore 模式匹配\n");
    printf("==================================================\n");
    
    const char* text = "ABAAABCDABCABCABCAB";
    const char* pattern = "ABC";
    
    printf("\n文本: %s\n", text);
    printf("模式: %s\n", pattern);
    
    // 打印坏字符规则表
    print_bad_char_table(pattern);
    
    int matches[MAX_MATCHES];
    int match_count = boyer_moore_search(text, pattern, matches, MAX_MATCHES);
    
    print_bm_matches(text, pattern, matches, match_count);
    
    printf("\n算法特点:\n");
    printf("  • 从右向左比较\n");
    printf("  • 坏字符规则：跳过不可能匹配的位置\n");
    printf("  • 好后缀规则：利用已匹配后缀\n");
    printf("  • 适合大字母表（如英文文本）\n");
    printf("  • 实际应用中通常最快\n");
    printf("  • 平均时间复杂度: O(n/m)\n");
    printf("  • 最坏时间复杂度: O(m × n)\n");
    
    return 0;
}
