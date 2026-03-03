package main

import (
  "fmt"
)

/**
 * 最长公共子序列（LCS）求解函数
 *
 * 功能：找到两个字符串中最长的公共子序列（字符顺序一致但不必连续）
 *
 * 参数：
 *   firstString 第一个输入字符串
 *   secondString 第二个输入字符串
 *
 * 返回值：
 *   LCS的长度和LCS的具体内容
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
func findLCS(firstString, secondString string) (int, string) {
  lengthOfFirst := len(firstString)
  lengthOfSecond := len(secondString)

  // 创建DP表：dpTable[i][j]表示前i个字符与前j个字符的LCS长度
  dpTable := make([][]int, lengthOfFirst+1)
  for i := range dpTable {
    dpTable[i] = make([]int, lengthOfSecond+1)
  }

  // 填充DP表
  for i := 1; i <= lengthOfFirst; i++ {
    for j := 1; j <= lengthOfSecond; j++ {
      charFromFirst := firstString[i-1]
      charFromSecond := secondString[j-1]

      if charFromFirst == charFromSecond {
        // 字符相同，继承前序结果+1
        dpTable[i][j] = dpTable[i-1][j-1] + 1
      } else {
        // 字符不同，取两种情况的最大值
        if dpTable[i-1][j] > dpTable[i][j-1] {
          dpTable[i][j] = dpTable[i-1][j]
        } else {
          dpTable[i][j] = dpTable[i][j-1]
        }
      }
    }
  }

  // 回溯找到具体的LCS序列
  lcsCharacters := make([]rune, 0, dpTable[lengthOfFirst][lengthOfSecond])
  currentI, currentJ := lengthOfFirst, lengthOfSecond

  for currentI > 0 && currentJ > 0 {
    currentCharFirst := firstString[currentI-1]
    currentCharSecond := secondString[currentJ-1]

    if currentCharFirst == currentCharSecond {
      lcsCharacters = append(lcsCharacters, rune(currentCharFirst))
      currentI--
      currentJ--
    } else if dpTable[currentI-1][currentJ] > dpTable[currentI][currentJ-1] {
      currentI--
    } else {
      currentJ--
    }
  }

  // 反转得到正确顺序
  for i, j := 0, len(lcsCharacters)-1; i < j; i, j = i+1, j-1 {
    lcsCharacters[i], lcsCharacters[j] = lcsCharacters[j], lcsCharacters[i]
  }

  return dpTable[lengthOfFirst][lengthOfSecond], string(lcsCharacters)
}

// 检查字符串是否在字符串切片中
func isStringInSlice(str string, slice []string) bool {
  for _, s := range slice {
    if str == s {
      return true
    }
  }
  return false
}

/** 运行LCS算法的测试用例集合 */
func runLCSTests() {
  // 测试用例结构体
  type TestCase struct {
    s1              string
    s2              string
    expectedLen     int
    possibleResults []string
  }

  // 测试用例数据
  testCases := []TestCase{
    {"ABCBDAB", "BDCAB", 4, []string{"BCAB", "BDAB"}},
    {"HELLO", "HELLO", 5, []string{"HELLO"}},
    {"ABCDEF", "ACE", 3, []string{"ACE"}},
    {"ABCD", "EFGH", 0, []string{""}},
    {"", "TEST", 0, []string{""}},
    {"AABBAABB", "ABAB", 4, []string{"AABB", "ABAB", "ABBA"}},
    {"XMJYAUZ", "MZJAWXU", 4, []string{"MJAU", "MZAU"}},
    {"A", "A", 1, []string{"A"}},
    {"A", "B", 0, []string{""}},
    {"123@abc", "a3@x1", 3, []string{"3@a", "1@a", "3a@"}},
  }

  for i, testCase := range testCases {
    fmt.Printf("\n测试用例 %d:\n", i+1)
    fmt.Printf("字符串1: %s\n", testCase.s1)
    fmt.Printf("字符串2: %s\n", testCase.s2)

    actualLen, actualResult := findLCS(testCase.s1, testCase.s2)

    lenMatch := actualLen == testCase.expectedLen
    resultMatch := isStringInSlice(actualResult, testCase.possibleResults)

    fmt.Printf("预期长度: %d, 实际长度: %d → %s\n",
      testCase.expectedLen, actualLen, map[bool]string{true: "通过", false: "失败"}[lenMatch])
    fmt.Printf("预期结果之一: %s, 实际结果: %s → %s\n",
      testCase.possibleResults[0], actualResult, map[bool]string{true: "通过", false: "失败"}[resultMatch])
    fmt.Printf("测试结果: %s\n", map[bool]string{true: "全部通过", false: "存在问题"}[lenMatch && resultMatch])
  }
}

func main() {
  // 示例用法
  stringOne := "AABCBDAB"
  stringTwo := "ABDCAB"

  lcsLength, lcsResult := findLCS(stringOne, stringTwo)

  fmt.Println("示例计算结果：")
  fmt.Printf("第一个字符串: %s\n", stringOne)
  fmt.Printf("第二个字符串: %s\n", stringTwo)
  fmt.Printf("最长公共子序列的长度: %d\n", lcsLength) // 输出5
  fmt.Printf("最长公共子序列的内容: %s\n", lcsResult) // 输出"ABDAB"

  // 运行测试用例
  fmt.Println("\n开始执行测试用例...")
  runLCSTests()
}

/*
jarry@Mac LCS % go run longest_common_subsequence.go
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
