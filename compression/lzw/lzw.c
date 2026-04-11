/*
*
 * LZW压缩算法 - 字典压缩
 *
 * 问题：使用动态字典进行无损数据压缩
 *
 * 核心思想：
 * - 动态构建编码字典
 * - 查找最长匹配字符串
 * - 输出字典索引
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define MAX_CODE_LEN 256

/*
*
 * 字典条目
*/
typedef struct {
    char string[MAX_CODE_LEN];
    int code;
} DictionaryEntry;

/*
*
 * LZW压缩
*/
void lzw_compress(const char* input, int* output, int* output_size) {
    DictionaryEntry dictionary[MAX_DICT_SIZE];
    int dict_size = 256;

    // 初始化字典（单字符）
    for (int i = 0; i < 256; i++) {
        dictionary[i].string[0] = (char)i;
        dictionary[i].string[1] = '\0';
        dictionary[i].code = i;
    }

    char current[MAX_CODE_LEN] = "";
    int output_idx = 0;

    for (int i = 0; i < strlen(input); i++) {
        char next_char = input[i];
        char combined[MAX_CODE_LEN];
        strcpy(combined, current);
        combined[strlen(current)] = next_char;
        combined[strlen(current) + 1] = '\0';

        // 查找combined是否在字典中
        int found = 0;
        for (int j = 0; j < dict_size; j++) {
            if (strcmp(dictionary[j].string, combined) == 0) {
                strcpy(current, combined);
                found = 1;
                break;
            }
        }

        if (!found) {
            // 输出current的编码
            for (int j = 0; j < dict_size; j++) {
                if (strcmp(dictionary[j].string, current) == 0) {
                    output[output_idx++] = dictionary[j].code;
                    break;
                }
            }

            // 将combined加入字典
            if (dict_size < MAX_DICT_SIZE) {
                strcpy(dictionary[dict_size].string, combined);
                dictionary[dict_size].code = dict_size;
                dict_size++;
            }

            // 重置current为next_char
            current[0] = next_char;
            current[1] = '\0';
        }
    }

    // 输出最后一个编码
    for (int j = 0; j < dict_size; j++) {
        if (strcmp(dictionary[j].string, current) == 0) {
            output[output_idx++] = dictionary[j].code;
            break;
        }
    }

    *output_size = output_idx;
}

/*
*
 * LZW解压
*/
void lzw_decompress(const int* input, int input_size, char* output) {
    DictionaryEntry dictionary[MAX_DICT_SIZE];
    int dict_size = 256;

    // 初始化字典（单字符）
    for (int i = 0; i < 256; i++) {
        dictionary[i].string[0] = (char)i;
        dictionary[i].string[1] = '\0';
        dictionary[i].code = i;
    }

    int old_code = input[0];
    strcpy(output, dictionary[old_code].string);
    char* output_ptr = output + strlen(dictionary[old_code].string);

    for (int i = 1; i < input_size; i++) {
        int new_code = input[i];
        char string[MAX_CODE_LEN];

        if (new_code >= dict_size) {
            // 特殊情况：new_code不在字典中
            strcpy(string, dictionary[old_code].string);
            string[strlen(dictionary[old_code].string)] = dictionary[old_code].string[0];
            string[strlen(dictionary[old_code].string) + 1] = '\0';
        } else {
            strcpy(string, dictionary[new_code].string);
        }

        // 输出string
        strcpy(output_ptr, string);
        output_ptr += strlen(string);

        // 将old_string + string[0]加入字典
        if (dict_size < MAX_DICT_SIZE) {
            char new_entry[MAX_CODE_LEN];
            strcpy(new_entry, dictionary[old_code].string);
            new_entry[strlen(dictionary[old_code].string)] = string[0];
            new_entry[strlen(dictionary[old_code].string) + 1] = '\0';
            strcpy(dictionary[dict_size].string, new_entry);
            dictionary[dict_size].code = dict_size;
            dict_size++;
        }

        old_code = new_code;
    }
}

/*
*
 * 主函数
*/
int main() {
    printf("=== LZW压缩算法 ===\n");

    const char* input = "TOBEORNOTTOBEORTOBEORNOT";
    printf("原始文本: %s\n", input);

    int compressed[1000];
    int compressed_size;
    lzw_compress(input, compressed, &compressed_size);

    printf("压缩后编码: ");
    for (int i = 0; i < compressed_size; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");

    char decompressed[1000];
    lzw_decompress(compressed, compressed_size, decompressed);
    printf("解压后文本: %s\n", decompressed);

    printf("验证: %s\n", strcmp(input, decompressed) == 0 ? "成功" : "失败");

    return 0;
}
