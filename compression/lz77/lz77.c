/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int offset, length;
    char character;
} Token;

/**
 * 创建LZ77令牌
 * @param offset 偏移量
 * @param length 匹配长度
 * @param character 下一个字符
 * @return 新令牌指针
 */
Token* createToken(int offset, int length, char character) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->offset = offset;
    token->length = length;
    token->character = character;
    return token;
}

/**
 * LZ77压缩算法
 * @param input 输入字符串
 * @param tokenCount 输出令牌数量
 * @return 压缩后的令牌数组
 */
Token* lz77Compress(const char* input, int* tokenCount) {
    printf("LZ77压缩开始...\n");
    int windowSize = 256;
    int position = 0;
    int inputLength = strlen(input);
    
    Token* tokens = malloc(inputLength * sizeof(Token));
    *tokenCount = 0;
    
    while (position < inputLength) {
        int maxLength = windowSize < position ? windowSize : position;
        int windowStart = position - maxLength;
        if (windowStart < 0) windowStart = 0;
        
        int bestLength = 0;
        int bestOffset = 0;
        
        // 在窗口中搜索最长匹配
        for (int i = 0; i < maxLength; i++) {
            int matchLength = 0;
            while (position + matchLength < inputLength &&
                   i + matchLength < maxLength &&
                   input[position + matchLength] == input[windowStart + i + matchLength]) {
                matchLength++;
            }
            
            if (matchLength > bestLength) {
                bestLength = matchLength;
                bestOffset = maxLength - i;
            }
        }
        
        if (bestLength >= 3) { // 最小匹配长度
            char nextChar = (position + bestLength < inputLength) ? 
                           input[position + bestLength] : '\0';
            tokens[*tokenCount] = *createToken(bestOffset, bestLength, nextChar);
            printf("找到匹配: 偏移=%d, 长度=%d\n", bestOffset, bestLength);
            position += bestLength + 1;
        } else {
            tokens[*tokenCount] = *createToken(0, 0, input[position]);
            printf("字面量: %c\n", input[position]);
            position++;
        }
        (*tokenCount)++;
    }
    
    printf("LZ77压缩完成，令牌数: %d\n", *tokenCount);
    return tokens;
}

/**
 * LZ77解压算法
 * @param tokens 压缩令牌数组
 * @param tokenCount 令牌数量
 * @param outputLength 输出字符串长度
 * @return 解压后的字符串
 */
char* lz77Decompress(Token* tokens, int tokenCount, int* outputLength) {
    printf("LZ77解压开始...\n");
    char* output = malloc(1000); // 假设最大输出长度
    *outputLength = 0;
    
    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];
        printf("处理令牌 %d: 偏移=%d, 长度=%d, 字符=%c\n", 
               i, token.offset, token.length, token.character);
        
        if (token.length > 0) {
            int start = *outputLength - token.offset;
            for (int j = 0; j < token.length; j++) {
                output[(*outputLength)++] = output[start + j];
            }
            if (token.character != '\0') {
                output[(*outputLength)++] = token.character;
            }
        } else {
            output[(*outputLength)++] = token.character;
        }
    }
    
    output[*outputLength] = '\0';
    printf("LZ77解压完成，长度: %d\n", *outputLength);
    return output;
}

/**
 * 计算压缩比
 * @param original 原始字符串
 * @param compressed 压缩令牌数组
 * @param tokenCount 令牌数量
 * @return 压缩比
 */
double compressionRatio(const char* original, Token* compressed, int tokenCount) {
    int originalSize = strlen(original) * 8; // 假设每个字符8位
    int compressedSize = 0;
    for (int i = 0; i < tokenCount; i++) {
        compressedSize += 16; // 偏移和长度各8位
        if (compressed[i].length > 0) compressedSize += 8; // 字符8位
    }
    return (double)compressedSize / originalSize;
}

/**
 * 主函数，演示LZ77压缩和解压
 */
int main() {
    const char* input = "ABABABABABAABABABABA";
    printf("=== LZ77算法演示 ===\n");
    printf("原始文本: %s\n", input);
    printf("原始长度: %d\n", strlen(input));
    
    // 压缩
    int tokenCount;
    Token* compressed = lz77Compress(input, &tokenCount);
    
    printf("压缩结果: ");
    for (int i = 0; i < tokenCount; i++) {
        if (compressed[i].length > 0) {
            printf("(%d,%d)", compressed[i].offset, compressed[i].length);
        } else {
            printf("(%c)", compressed[i].character);
        }
    }
    printf("\n");
    
    // 计算压缩比
    double ratio = compressionRatio(input, compressed, tokenCount);
    printf("压缩比: %.2f\n", ratio);
    
    // 解压
    int outputLength;
    char* decompressed = lz77Decompress(compressed, tokenCount, &outputLength);
    printf("解压结果: %s\n", decompressed);
    printf("解压长度: %d\n", outputLength);
    
    // 验证
    int isValid = strcmp(input, decompressed) == 0;
    printf("验证结果: %s\n", isValid ? "✓ 成功" : "✗ 失败");
    printf("=== 演示结束 ===\n");
    
    free(compressed);
    free(decompressed);
    
    return 0;
}
