/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 最长公共子串 (Longest Continuous Subsequence / Common Substring)
 * 
 * 算法原理：
 * 1. 最长公共子串要求子序列中的字符在原字符串中是连续且相邻的。
 * 2. 使用动态规划求解：
 *    - 如果 word1[i-1] == word2[j-1]，则 dp[i][j] = dp[i-1][j-1] + 1
 *    - 否则，dp[i][j] = 0 (连续中断)
 * 3. 在计算过程中记录最大长度和对应的结束位置。
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)，可优化至 O(min(m, n))
 */
export class LongestContinuousSubsequence {

  /**
   * 求解最长连续公共子串
   * 
   * @param s1 第一个字符串
   * @param s2 第二个字符串
   * @returns 包含长度和具体内容的对象
   */
  public static findLCS(s1: string, s2: string): { length: number; content: string } {
    const m = s1.length;
    const n = s2.length;
    
    // dp[i][j] 表示以 s1[i-1] 和 s2[j-1] 结尾的最长公共子串长度
    const dp: number[][] = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0));
    
    let maxLength = 0;
    let endIndex = 0;
    
    for (let i = 1; i <= m; i++) {
      for (let j = 1; j <= n; j++) {
        if (s1[i - 1] === s2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
          if (dp[i][j] > maxLength) {
            maxLength = dp[i][j];
            endIndex = i;
          }
        } else {
          dp[i][j] = 0;
        }
      }
    }
    
    const content = maxLength > 0 ? s1.substring(endIndex - maxLength, endIndex) : "";
    return { length: maxLength, content: content };
  }

  /**
   * 运行测试
   */
  public static runTests(): void {
    const testCases: [string, string, number][] = [
      ["ABCBDAB", "BDCAB", 2],
      ["HELLO", "HELLO", 5],
      ["ABCDEF", "ACE", 1],
      ["ABCDXYZ", "XYZABCD", 4],
      ["ABABC", "BABCA", 4]
    ];

    console.log("最长连续公共子串测试:");
    testCases.forEach(([s1, s2, expectedLen], index) => {
      const result = this.findLCS(s1, s2);
      console.log(`用例 ${index + 1}: [${s1}] vs [${s2}] | 长度: ${result.length} (预期: ${expectedLen}) | 内容: ${result.content} | 状态: ${result.length === expectedLen ? "OK" : "FAIL"}`);
    });
  }
}

// 执行测试
if (require.main === module) {
  LongestContinuousSubsequence.runTests();
}
