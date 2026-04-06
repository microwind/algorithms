/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串递归操作示例
 * 
 * 算法特点：
 * - 演示递归在字符串处理中的应用
 * - 包含字符串反转、回文检查、元音计数
 * 
 * 学习重点：理解递归在字符串操作中的使用
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * 递归反转字符串
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param s 要反转的字符串
 * @param start 起始位置
 * @param end 结束位置
 * @return 反转后的字符串
 */
void reverseString(char *s, int start, int end) {
    // 基础情况：字符串长度小于等于1
    if (start >= end) {
        return;
    }
    
    // 交换首尾字符
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    
    // 递归处理中间部分
    reverseString(s, start + 1, end - 1);
}

/**
 * 递归检查字符串是否为回文
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param s 要检查的字符串
 * @param left 左边界
 * @param right 右边界
 * @return 是否为回文
 */
int isPalindrome(char *s, int left, int right) {
    // 基础情况：左边界大于等于右边界
    if (left >= right) {
        return 1; // 是回文
    }
    
    // 转换为小写比较
    if (tolower(s[left]) != tolower(s[right])) {
        return 0; // 不是回文
    }
    
    // 递归检查中间部分
    return isPalindrome(s, left + 1, right - 1);
}

/**
 * 递归计算字符串中元音字母的数量
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param s 要计算的字符串
 * @param index 当前索引
 * @return 元音字母数量
 */
int countVowels(char *s, int index) {
    // 基础情况：字符串结束
    if (s[index] == '\0') {
        return 0;
    }
    
    // 检查当前字符是否是元音
    char c = tolower(s[index]);
    int isVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    
    // 递归计算剩余部分
    return isVowel + countVowels(s, index + 1);
}

/**
 * 主函数 - 测试字符串递归操作
 */
int main() {
    printf("========================================\n");
    printf("字符串递归操作示例\n");
    printf("========================================\n");
    
    // 测试1：字符串反转
    char testStr1[] = "Hello";
    printf("\n1. 字符串反转:\n");
    printf("   原字符串: '%s'\n", testStr1);
    reverseString(testStr1, 0, strlen(testStr1) - 1);
    printf("   反转后:   '%s'\n", testStr1);
    printf("===\n");
    
    // 测试2：回文检查
    printf("2. 回文检查:\n");
    char *testCases[] = {"radar", "hello", "Aba", "level", "aabbaa", "cc", "ddd"};
    int testCasesLen = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < testCasesLen; i++) {
        char *s = testCases[i];
        int result = isPalindrome(s, 0, strlen(s) - 1);
        printf("   '%s' -> %s\n", s, result ? "是回文" : "不是回文");
    }
    printf("===\n");
    
    // 测试3：元音计数
    printf("3. 元音计数:\n");
    char testStr2[] = "Hello World";
    printf("   字符串: '%s'\n", testStr2);
    printf("   元音数量: %d\n", countVowels(testStr2, 0));
    printf("===\n");
    
    printf("\n========================================\n");
    
    return 0;
}

/*打印结果
jarry@Mac string-recursion % gcc string_operations.c -o string_operations && ./string_operations
========================================
字符串递归操作示例
========================================

1. 字符串反转:
   原字符串: 'Hello'
   反转后:   'olleH'
===
2. 回文检查:
   'radar' -> 是回文
   'hello' -> 不是回文
   'Aba' -> 是回文
   'level' -> 是回文
   'aabbaa' -> 是回文
   'cc' -> 是回文
   'ddd' -> 是回文
===
3. 元音计数:
   字符串: 'Hello World'
   元音数量: 3
===

========================================
*/
