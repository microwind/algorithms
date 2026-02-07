package main

import (
  "fmt"
)

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
 *
 * 返回值：
 *   最长公共子串的长度和内容
 */
func longestContinuousSubsequence(str1, str2 string) (int, string) {
  len1 := len(str1)
  len2 := len(str2)

  // 特殊情况处理
  if len1 == 0 || len2 == 0 {
    return 0, ""
  }

  // 创建DP表：dp[i][j]表示以str1[i-1]和str2[j-1]为结尾的最长公共子串长度
  dp := make([][]int, len1+1)
  for i := range dp {
    dp[i] = make([]int, len2+1)
  }

  maxLength := 0 // 记录最长公共子串的长度
  endIndex := 0  // 记录最长公共子串在str1中的结束索引

  // 填充DP表
  for i := 1; i <= len1; i++ {
    for j := 1; j <= len2; j++ {
      if str1[i-1] == str2[j-1] {
        // 当前字符相同，长度 = 前一位的长度 + 1（连续累加）
        dp[i][j] = dp[i-1][j-1] + 1

        // 更新最长长度和结束索引
        if dp[i][j] > maxLength {
          maxLength = dp[i][j]
          endIndex = i // 记录在str1中的结束位置
        }
      } else {
        // 字符不同，连续中断，长度重置为0
        dp[i][j] = 0
      }
    }
  }

  // 提取最长公共子串
  longestSubstring := ""
  if maxLength > 0 {
    startIndex := endIndex - maxLength
    longestSubstring = str1[startIndex:endIndex]
  }

  return maxLength, longestSubstring
}

// 检查字符串是否在字符串切片中
func isInSlice(str string, slice []string) bool {
  for _, s := range slice {
    if str == s {
      return true
    }
  }
  return false
}

// 测试用例
func testLongestContinuousSubsequence() {
  // 测试用例结构体
  type testCase struct {
    s1              string
    s2              string
    expectedLen     int
    possibleResults []string
  }

  testCases := []testCase{
    {"ABCBDAB", "BDCAB", 2, []string{"BC", "AB"}},
    {"HELLO", "HELLO", 5, []string{"HELLO"}},
    {"ABCDEF", "ACE", 1, []string{"A", "C", "E"}},
    {"ABCDXYZ", "XYZABCD", 4, []string{"ABCD"}},
    {"12345", "54321", 1, []string{"1", "2", "3", "4", "5"}},
    {"ABABC", "BABCA", 4, []string{"ABCA", "BABC"}},
  }

  for i, tc := range testCases {
    fmt.Printf("测试用例 %d:\n", i+1)
    fmt.Printf("字符串1: %s\n", tc.s1)
    fmt.Printf("字符串2: %s\n", tc.s2)

    actualLen, actualResult := longestContinuousSubsequence(tc.s1, tc.s2)

    lenMatch := actualLen == tc.expectedLen
    resultMatch := isInSlice(actualResult, tc.possibleResults)

    fmt.Printf("预期长度: %d, 实际长度: %d → %s\n",
      tc.expectedLen, actualLen, map[bool]string{true: "通过", false: "失败"}[lenMatch])
    fmt.Printf("预期结果之一: %s, 实际结果: %s → %s\n",
      tc.possibleResults[0], actualResult, map[bool]string{true: "通过", false: "失败"}[resultMatch])
    fmt.Printf("测试结果: %s\n\n", map[bool]string{true: "全部通过", false: "存在问题"}[lenMatch && resultMatch])
  }
}

func main() {
  // 示例
  s1 := "ABCBDAB"
  s2 := "BDCAB"
  length, substring := longestContinuousSubsequence(s1, s2)

  fmt.Println("示例:")
  fmt.Printf("字符串1: %s\n", s1)
  fmt.Printf("字符串2: %s\n", s2)
  fmt.Printf("最长公共子串长度: %d\n", length)
  fmt.Printf("最长公共子串: %s\n\n", substring)

  // 运行测试
  testLongestContinuousSubsequence()
}

/*
jarry@Mac LCS % go run longest_continuous_subsequence.go
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
