/* KMP简单测试 */
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
package main

import (
  "fmt"
  "time"
)

// @Param pattern string 查找字符串
// @Return 部分匹配表
func makePMT(pattern string) []int {
  patternLen := len(pattern)
  pmt := make([]int, patternLen)
  for i := 0; i < patternLen; i++ {
    subPattern := pattern[0 : i+1]
    pmtValue := 0
    prefixArr := []string{}
    postfixArr := []string{}

    // 遍历当前子字符串的所有可能的前缀和后缀
    for j := 0; j < i; j++ {
      // 获取从头到 j 的前缀
      prefix := pattern[0 : j+1]

      // 获取从 i-j 到当前 i 的后缀
      postfix := pattern[i-j : i+1]

      // 将前缀和后缀加入各自的数组
      prefixArr = append(prefixArr, prefix)
      postfixArr = append(postfixArr, postfix)

      // 检查前缀和后缀是否相等，且长度大于当前 pmtValue
      if prefix == postfix && len(prefix) > pmtValue {
        // 如果相等，且长度更大，更新 pmtValue
        pmtValue = len(prefix)
      }
    }
    pmt[i] = pmtValue
    fmt.Println(i, subPattern, " | ", prefixArr, " | ", postfixArr, " | ", pmtValue)
  }
  fmt.Println("makePMT() pmt:", pmt)
  return pmt
}

// @Param pattern string 查找字符串
// @Return 部分匹配表
func makePMT2(pattern string) []int {
  patternLen := len(pattern)
  pmt := make([]int, patternLen)
  pmtValue := 0
  // 从第二个字符开始，第一个无需对比
  for i := 1; i < patternLen; i++ {
    // 当 pmtValue 大于 0 且当前字符不等于部分匹配的下一个字符时，退回上一个匹配值
    for pmtValue > 0 && pattern[i] != pattern[pmtValue] {
      // 通过前一个部分匹配值进行回退
      pmtValue = pmt[pmtValue-1]
    }

    // 当前字符与部分匹配的下一个字符相同，部分匹配值增加
    if pattern[i] == pattern[pmtValue] {
      pmtValue++
    }

    // 将当前部分匹配值存储在 pmt 中
    pmt[i] = pmtValue

    // 以下为打印前后缀测试[可选]
    subPattern := pattern[0 : i+1]
    prefixArr := []string{}
    postfixArr := []string{}

    for j := 0; j < i; j++ {
      prefix := subPattern[0 : j+1]
      postfix := subPattern[i-j : i+1]
      prefixArr = append(prefixArr, prefix)
      postfixArr = append(postfixArr, postfix)
    }

    fmt.Println(i, subPattern, " | ", prefixArr, " | ", postfixArr, " | ", pmtValue)
  }
  fmt.Println("makePMT2() pmt:", pmt)
  return pmt

}

func kmpSearch(pattern string, text string) []int {
  fmt.Println(" pattern:", pattern, "text:", text)
  // 用于存储匹配到的模式串在文本中的起始位置
  var matches = []int{}
  pmtTable := makePMT(pattern)
  fmt.Println("根据模式串获取pmtTable:", pmtTable)
  j := 0

  // 遍历文本中的每个字符
  for i := 0; i < len(text); i++ {
    // 当模式串索引大于 0 且当前字符与模式串字符不匹配时，回退索引
    for j > 0 && text[i] != pattern[j] {
      j = pmtTable[j-1] // 使用部分匹配表进行回退
    }

    // 如果当前字符与模式串字符匹配，增加模式串索引
    if text[i] == pattern[j] {
      j++
    }

    // 如果模式串索引等于模式串长度，表示找到完整匹配
    if j == len(pattern) {
      // 记录匹配的起始位置
      matches = append(matches, i-j+1)
      // 通过部分匹配表回退，继续查找下一个匹配
      j = pmtTable[j-1]
    }
  }

  fmt.Println("匹配结果：", matches)
  return matches
}

func main() {
  time1 := time.Now()
  fmt.Println("KMP搜索测试：")
  pattern := "ABCABAB"
  fmt.Println("pattern:", pattern)
  makePMT(pattern)
  makePMT2(pattern)
  kmpSearch(pattern, "AAABABCABABCDABABCABAB")   // [4, 15]
  kmpSearch(pattern, "ABAAABABCABABCDABABCABAB") // [6, 17]
  fmt.Println("cost:", time.Since(time1))
}
