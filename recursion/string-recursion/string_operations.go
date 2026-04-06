// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0

/**
 * 字符串递归操作示例
 *
 * 算法特点：
 * - 演示递归在字符串处理中的应用
 * - 包含字符串反转、回文检查、元音计数
 *
 * 学习重点：理解递归在字符串操作中的使用
 */
package main

import (
	"fmt"
	"strings"
)

// 递归反转字符串
// 时间复杂度: O(n)，空间复杂度: O(n)
// 参数: s 要反转的字符串
// 返回: 反转后的字符串
func reverseString(s string) string {
	// 基础情况：空字符串或单个字符
	if len(s) <= 1 {
		return s
	}

	// 递归：剩余部分反转 + 第一个字符放到末尾
	return reverseString(s[1:]) + s[:1]
}

// 递归检查字符串是否为回文
// 时间复杂度: O(n)，空间复杂度: O(n)
// 参数: s 要检查的字符串
// 返回: 是否为回文
func isPalindrome(s string) bool {
	s = strings.ToLower(s) // 忽略大小写

	// 基础情况：空字符串或单个字符是回文
	if len(s) <= 1 {
		return true
	}

	// 如果首尾字符不同，不是回文
	if s[0] != s[len(s)-1] {
		return false
	}

	// 递归检查去掉首尾后的中间部分
	return isPalindrome(s[1 : len(s)-1])
}

// 递归计算字符串中元音字母的数量
// 时间复杂度: O(n)，空间复杂度: O(n)
// 参数: s 要计算的字符串
// 返回: 元音字母数量
func countVowels(s string) int {
	vowels := "aeiouAEIOU"

	// 基础情况：空字符串
	if len(s) == 0 {
		return 0
	}

	// 检查第一个字符是否是元音
	firstIsVowel := 0
	if strings.ContainsRune(vowels, rune(s[0])) {
		firstIsVowel = 1
	}

	// 递归计算剩余部分
	return firstIsVowel + countVowels(s[1:])
}

// 主函数 - 测试字符串递归操作
func main() {
	// 测试1：字符串反转
	testStr1 := "Hello"
	fmt.Println("1. 字符串反转:")
	fmt.Printf("   原字符串: '%s'\n", testStr1)
	fmt.Printf("   反转后:   '%s'\n", reverseString(testStr1))
	fmt.Println("===")

	// 测试2：回文检查
	fmt.Println("2. 回文检查:")
	testCases := []string{"radar", "hello", "Aba", "level", "aabbaa", "cc", "ddd"}
	for _, s := range testCases {
		result := "是回文"
		if !isPalindrome(s) {
			result = "不是回文"
		}
		fmt.Printf("   '%s' -> %s\n", s, result)
	}
	fmt.Println("===")

	// 测试3：元音计数
	testStr2 := "Hello World"
	fmt.Println("3. 元音计数:")
	fmt.Printf("   字符串: '%s'\n", testStr2)
	fmt.Printf("   元音数量: %d\n", countVowels(testStr2))
	fmt.Println("===")
}

// 打印结果
/*
jarry@Mac string-recursion % go run string_operations.go
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
*/
