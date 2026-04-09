/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
 * 
 * 算法原理：
 * 1. 计算将一个字符串转换为另一个字符串所需的最少操作次数。
 * 2. 允许的操作包括：插入、删除、替换。
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)，可优化至 O(min(m, n))
 */
export class EditDistance {

  /**
   * 动态规划版本 - 计算编辑距离
   */
  public static editDistance(word1: string, word2: string): number {
    const n = word1.length;
    const m = word2.length;
    const dp: number[][] = Array.from({ length: n + 1 }, () => Array(m + 1).fill(0));

    for (let i = 0; i <= n; i++) dp[i][0] = i;
    for (let j = 0; j <= m; j++) dp[0][j] = j;

    for (let i = 1; i <= n; i++) {
      for (let j = 1; j <= m; j++) {
        if (word1[i - 1] === word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = 1 + Math.min(
            dp[i - 1][j],    // 删除
            dp[i][j - 1],    // 插入
            dp[i - 1][j - 1] // 替换
          );
        }
      }
    }
    return dp[n][m];
  }

  /**
   * 空间优化后的动态规划版本
   */
  public static editDistanceOptimized(word1: string, word2: string): number {
    if (word1.length < word2.length) [word1, word2] = [word2, word1];
    const n = word1.length;
    const m = word2.length;
    let prev: number[] = Array.from({ length: m + 1 }, (_, i) => i);
    let curr: number[] = Array(m + 1).fill(0);

    for (let i = 1; i <= n; i++) {
      curr[0] = i;
      for (let j = 1; j <= m; j++) {
        if (word1[i - 1] === word2[j - 1]) {
          curr[j] = prev[j - 1];
        } else {
          curr[j] = 1 + Math.min(prev[j], curr[j - 1], prev[j - 1]);
        }
      }
      prev = [...curr];
    }
    return prev[m];
  }

  /**
   * 递归版本（结合记忆化）
   */
  public static editDistanceRecursive(word1: string, word2: string): number {
    const memo: Map<string, number> = new Map();

    const helper = (i: number, j: number): number => {
      if (i === 0) return j;
      if (j === 0) return i;
      const key = `${i}-${j}`;
      if (memo.has(key)) return memo.get(key)!;

      let res: number;
      if (word1[i - 1] === word2[j - 1]) {
        res = helper(i - 1, j - 1);
      } else {
        res = 1 + Math.min(
          helper(i - 1, j),    // 删除
          helper(i, j - 1),    // 插入
          helper(i - 1, j - 1) // 替换
        );
      }
      memo.set(key, res);
      return res;
    };

    return helper(word1.length, word2.length);
  }

  /**
   * 获取具体的编辑操作步骤
   */
  public static getEditOperations(word1: string, word2: string): string[] {
    const n = word1.length;
    const m = word2.length;
    const dp: number[][] = Array.from({ length: n + 1 }, () => Array(m + 1).fill(0));

    for (let i = 0; i <= n; i++) dp[i][0] = i;
    for (let j = 0; j <= m; j++) dp[0][j] = j;
    for (let i = 1; i <= n; i++) {
      for (let j = 1; j <= m; j++) {
        if (word1[i - 1] === word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
        else dp[i][j] = 1 + Math.min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
      }
    }

    const ops: string[] = [];
    let i = n, j = m;
    while (i > 0 || j > 0) {
      if (i > 0 && j > 0 && word1[i - 1] === word2[j - 1]) {
        i--; j--;
      } else if (i > 0 && j > 0 && dp[i][j] === dp[i - 1][j - 1] + 1) {
        ops.unshift(`替换 '${word1[i - 1]}' 为 '${word2[j - 1]}'`);
        i--; j--;
      } else if (i > 0 && dp[i][j] === dp[i - 1][j] + 1) {
        ops.unshift(`删除 '${word1[i - 1]}'`);
        i--;
      } else {
        ops.unshift(`插入 '${word2[j - 1]}'`);
        j--;
      }
    }
    return ops;
  }

  /**
   * 计算相似度
   */
  public static getSimilarityRatio(word1: string, word2: string): number {
    const distance = this.editDistance(word1, word2);
    const maxLen = Math.max(word1.length, word2.length);
    return maxLen === 0 ? 1 : 1 - distance / maxLen;
  }
}

// 测试代码
(function test() {
  console.log("====================================================");
  console.log("编辑距离 (Edit Distance) - TypeScript 实现");
  console.log("====================================================");

  const testCases: [string, string][] = [
    ["kitten", "sitting"],
    ["sunday", "saturday"],
    ["abc", ""],
    ["", "abc"],
    ["same", "same"]
  ];

  testCases.forEach(([s1, s2]) => {
    console.log(`\n源字符串: "${s1}"`);
    console.log(`目标字符串: "${s2}"`);
    console.log(`最小编辑距离 (DP): ${EditDistance.editDistance(s1, s2)}`);
    console.log(`最小编辑距离 (优化DP): ${EditDistance.editDistanceOptimized(s1, s2)}`);
    console.log(`最小编辑距离 (递归): ${EditDistance.editDistanceRecursive(s1, s2)}`);
    console.log(`相似度: ${(EditDistance.getSimilarityRatio(s1, s2) * 100).toFixed(2)}%`);
    if (s1.length < 10 && s2.length < 10) {
      console.log("操作步骤:", EditDistance.getEditOperations(s1, s2).join(" -> "));
    }
  });
})();
