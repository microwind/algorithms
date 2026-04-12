/**
 * 游程编码(RLE)实现 - C语言
 * 核心思想：连续重复字符编码为"字符+计数"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 压缩：连续字符转为"字符+计数"
char* compress(const char* text) {
    if (!text || *text == '\0') {
        return strdup(text);
    }
    
    int compressed_size = strlen(text) * 2 + 1; // 最坏情况：每个字符都变2字符
    char* compressed = (char*)malloc(compressed_size);
    int compressed_index = 0;
    
    char current_char = text[0];
    int count = 1;
    
    // 遍历统计连续字符
    for (int i = 1; text[i] != '\0'; i++) {
        if (text[i] == current_char) {
            count++;  // 连续相同字符，计数+1
        } else {
            compressed[compressed_index++] = current_char;
            if (count > 1) {
                compressed_index += sprintf(compressed + compressed_index, "%d", count);
            }
            current_char = text[i];
            count = 1;
        }
    }
    
    // 处理最后一个字符
    compressed[compressed_index++] = current_char;
    if (count > 1) {
        compressed_index += sprintf(compressed + compressed_index, "%d", count);
    }
    
    compressed[compressed_index] = '\0';
    return compressed;
}

// 解压：解析"字符+计数"还原原始字符串
char* decompress(const char* compressed) {
    if (!compressed || *compressed == '\0') {
        return strdup(compressed);
    }
    
    // 估算解压后大小（数字最大999999999）
    int decompressed_size = strlen(compressed) * 10;
    char* decompressed = (char*)malloc(decompressed_size);
    int decompressed_index = 0;
    
    int i = 0;
    while (compressed[i] != '\0') {
        char current_char = compressed[i++];
        char count_str[20] = "";
        int count_index = 0;
        
        // 解析数字
        while (compressed[i] != '\0' && isdigit(compressed[i])) {
            count_str[count_index++] = compressed[i++];
        }
        count_str[count_index] = '\0';
        
        int count = count_str[0] != '\0' ? atoi(count_str) : 1;
        
        // 添加字符
        for (int j = 0; j < count; j++) {
            decompressed[decompressed_index++] = current_char;
        }
    }
    
    decompressed[decompressed_index] = '\0';
    return decompressed;
}

double compression_ratio(const char* original, const char* compressed) {
    return (double)strlen(compressed) / strlen(original);
}

int main() {
    const char* text = "AAAABBBCCDAA";
    printf("原始文本: %s\n", text);
    
    char* compressed = compress(text);
    printf("压缩后: %s\n", compressed);
    
    char* decompressed = decompress(compressed);
    printf("解压后: %s\n", decompressed);
    
    printf("压缩比: %.2f\n", compression_ratio(text, compressed));
    printf("验证: %d\n", strcmp(text, decompressed) == 0);
    
    free(compressed);
    free(decompressed);
    
    return 0;
}
