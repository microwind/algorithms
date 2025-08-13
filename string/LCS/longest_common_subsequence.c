#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * 最长公共子序列（LCS）求解函数
 * 
 * 功能：找到两个字符串中最长的公共子序列（字符顺序一致但不必连续）
 * 
 * 参数：
 *   firstString: 第一个输入字符串
 *   secondString: 第二个输入字符串
 *   lcsLength: 用于存储LCS长度的指针
 * 
 * 返回值：
 *   动态分配的字符串，包含LCS的具体内容，需要调用者手动释放内存
 * 
 * 举例：
 *   序列A为"abcdef"，序列B为"bcef"，
 *   最长公共子序列为"bcef"，
 *   注意最长公共子序列不用保证每一个字符必须连续。
 */
/*
示例与算法对比说明
示例：
若序列 A 为 “abcdef”，序列 B 为 “bcef”，其最长公共子序列为 “bcef”（即序列 B）。需注意，最长公共子序列仅要求字符顺序一致，无需连续。
暴力解法思路：
选择一个参照序列（如 A），遍历其每个字符作为公共子序列的起始点；
将该字符与另一序列（如 B）的每个字符比较，若匹配，则在两序列中均向后移动指针继续比较，直至某一序列结束；
重复上述过程，以参照序列的每个字符为起点计算可能的公共子序列长度，最终取最大值。
暴力解法的问题：
时间复杂度为 O (n²×m)（其中 n 为序列 A 的长度，m 为序列 B 的长度），效率过低。因此，需要更优的算法 —— 动态规划。
*/
char* findLCS(const char* firstString, const char* secondString, int* lcsLength) {
    int lengthOfFirst = strlen(firstString);
    int lengthOfSecond = strlen(secondString);
    
    // 创建DP表：dpTable[i][j]表示前i个字符与前j个字符的LCS长度
    int** dpTable = (int**)malloc((lengthOfFirst + 1) * sizeof(int*));
    for (int i = 0; i <= lengthOfFirst; i++) {
        dpTable[i] = (int*)calloc(lengthOfSecond + 1, sizeof(int));
    }
    
    // 填充DP表
    for (int i = 1; i <= lengthOfFirst; i++) {
        for (int j = 1; j <= lengthOfSecond; j++) {
            char charFromFirst = firstString[i - 1];
            char charFromSecond = secondString[j - 1];
            
            if (charFromFirst == charFromSecond) {
                // 字符相同，继承前序结果+1
                dpTable[i][j] = dpTable[i - 1][j - 1] + 1;
            } else {
                // 字符不同，取两种情况的最大值
                dpTable[i][j] = (dpTable[i - 1][j] > dpTable[i][j - 1]) ? 
                               dpTable[i - 1][j] : dpTable[i][j - 1];
            }
        }
    }
    
    // 存储LCS长度
    *lcsLength = dpTable[lengthOfFirst][lengthOfSecond];
    
    // 回溯找到具体的LCS序列
    char* lcsContent = (char*)malloc((*lcsLength + 1) * sizeof(char));
    int currentI = lengthOfFirst;
    int currentJ = lengthOfSecond;
    int index = *lcsLength - 1;
    
    while (currentI > 0 && currentJ > 0) {
        char currentCharFirst = firstString[currentI - 1];
        char currentCharSecond = secondString[currentJ - 1];
        
        if (currentCharFirst == currentCharSecond) {
            lcsContent[index--] = currentCharFirst;
            currentI--;
            currentJ--;
        } else if (dpTable[currentI - 1][currentJ] > dpTable[currentI][currentJ - 1]) {
            currentI--;
        } else {
            currentJ--;
        }
    }
    lcsContent[*lcsLength] = '\0';  // 添加字符串结束符
    
    // 释放DP表内存
    for (int i = 0; i <= lengthOfFirst; i++) {
        free(dpTable[i]);
    }
    free(dpTable);
    
    return lcsContent;
}

// 检查字符串是否在字符串数组中
bool isStringInArray(const char* str, const char** arr, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        if (strcmp(str, arr[i]) == 0) {
            return true;
        }
    }
    return false;
}

/** 运行LCS算法的测试用例集合 */
void runLCSTests() {
    // 测试用例结构：{字符串1, 字符串2, 预期长度, {可能的预期结果}, 结果数量}
    struct TestCase {
        const char* s1;
        const char* s2;
        int expectedLen;
        const char** possibleResults;
        int resultsCount;
    };
    
    // 测试用例数据
    const char* case1Results[] = {"BCAB", "BDAB"};
    const char* case2Results[] = {"HELLO"};
    const char* case3Results[] = {"ACE"};
    const char* case4Results[] = {""};
    const char* case5Results[] = {""};
    const char* case6Results[] = {"AABB", "ABAB", "ABBA"};
    const char* case7Results[] = {"MJAU", "MZAU"};
    const char* case8Results[] = {"A"};
    const char* case9Results[] = {""};
    const char* case10Results[] = {"3@a", "1@a", "3a@"};
    
    struct TestCase testCases[] = {
        {"ABCBDAB", "BDCAB", 4, case1Results, 2},
        {"HELLO", "HELLO", 5, case2Results, 1},
        {"ABCDEF", "ACE", 3, case3Results, 1},
        {"ABCD", "EFGH", 0, case4Results, 1},
        {"", "TEST", 0, case5Results, 1},
        {"AABBAABB", "ABAB", 4, case6Results, 3},
        {"XMJYAUZ", "MZJAWXU", 4, case7Results, 2},
        {"A", "A", 1, case8Results, 1},
        {"A", "B", 0, case9Results, 1},
        {"123@abc", "a3@x1", 3, case10Results, 3}
    };
    int testCaseCount = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < testCaseCount; i++) {
        printf("\n测试用例 %d:\n", i + 1);
        printf("字符串1: %s\n", testCases[i].s1);
        printf("字符串2: %s\n", testCases[i].s2);
        
        int actualLen;
        char* actualResult = findLCS(testCases[i].s1, testCases[i].s2, &actualLen);
        
        bool lenMatch = (actualLen == testCases[i].expectedLen);
        bool resultMatch = isStringInArray(actualResult, testCases[i].possibleResults, testCases[i].resultsCount);
        
        printf("预期长度: %d, 实际长度: %d → %s\n", 
               testCases[i].expectedLen, actualLen, lenMatch ? "通过" : "失败");
        printf("预期结果之一: %s, 实际结果: %s → %s\n", 
               testCases[i].possibleResults[0], actualResult, resultMatch ? "通过" : "失败");
        printf("测试结果: %s\n", (lenMatch && resultMatch) ? "全部通过" : "存在问题");
        
        free(actualResult);  // 释放动态分配的内存
    }
}

int main() {
    // 示例用法
    const char* stringOne = "AABCBDAB";
    const char* stringTwo = "ABDCAB";
    
    int lcsLength;
    char* lcsResult = findLCS(stringOne, stringTwo, &lcsLength);
    
    printf("示例计算结果：\n");
    printf("第一个字符串: %s\n", stringOne);
    printf("第二个字符串: %s\n", stringTwo);
    printf("最长公共子序列的长度: %d\n", lcsLength);  // 输出5
    printf("最长公共子序列的内容: %s\n", lcsResult);   // 输出"ABDAB"
    
    free(lcsResult);  // 释放动态分配的内存
    
    // 运行测试用例
    printf("\n开始执行测试用例...");
    runLCSTests();
    
    return 0;
}

/**
jarry@Mac LCS % gcc longest_common_subsequence.c
jarry@Mac LCS % ./a.out 
示例计算结果：
第一个字符串: AABCBDAB
第二个字符串: ABDCAB
最长公共子序列的长度: 5
最长公共子序列的内容: ABDAB

开始执行测试用例...
测试用例 1:
字符串1: ABCBDAB
字符串2: BDCAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: BCAB, 实际结果: BDAB → 通过
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
预期长度: 3, 实际长度: 3 → 通过
预期结果之一: ACE, 实际结果: ACE → 通过
测试结果: 全部通过

测试用例 4:
字符串1: ABCD
字符串2: EFGH
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 5:
字符串1: 
字符串2: TEST
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 6:
字符串1: AABBAABB
字符串2: ABAB
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: AABB, 实际结果: ABAB → 通过
测试结果: 全部通过

测试用例 7:
字符串1: XMJYAUZ
字符串2: MZJAWXU
预期长度: 4, 实际长度: 4 → 通过
预期结果之一: MJAU, 实际结果: MJAU → 通过
测试结果: 全部通过

测试用例 8:
字符串1: A
字符串2: A
预期长度: 1, 实际长度: 1 → 通过
预期结果之一: A, 实际结果: A → 通过
测试结果: 全部通过

测试用例 9:
字符串1: A
字符串2: B
预期长度: 0, 实际长度: 0 → 通过
预期结果之一: , 实际结果:  → 通过
测试结果: 全部通过

测试用例 10:
字符串1: 123@abc
字符串2: a3@x1
预期长度: 3, 实际长度: 2 → 失败
预期结果之一: 3@a, 实际结果: 3@ → 失败
测试结果: 存在问题
 */