/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - Boyer-Moore 模式匹配
 * 
 * 算法原理：
 * 1. 采用从右向左的比较方式。
 * 2. 核心规则：坏字符启发式 (Bad Character Heuristic)。
 * 3. 利用不匹配字符在模式串中的位置，最大化跳过步数。
 * 
 * 时间复杂度：平均 O(n / m)，最坏 O(n * m)
 */
const BoyerMoore = (function () {
  const ALPHABET_SIZE = 256

  /**
   * 构建坏字符表
   */
  function buildBadCharTable(pattern) {
    const badChar = new Array(ALPHABET_SIZE).fill(-1)
    for (let i = 0; i < pattern.length; i++) {
      badChar[pattern.charCodeAt(i)] = i
    }
    return badChar
  }

  /**
   * Boyer-Moore 搜索算法
   */
  function search(pattern, text) {
    const m = pattern.length
    const n = text.length
    const matches = []

    if (m === 0 || m > n) return matches

    const badChar = buildBadCharTable(pattern)
    let shift = 0

    while (shift <= (n - m)) {
      let j = m - 1

      // 从右往左比对
      while (j >= 0 && pattern[j] === text[shift + j]) {
        j--
      }

      if (j < 0) {
        // 完全匹配
        matches.push(shift)
        // 使用坏字符规则移动
        shift += (shift + m < n) ? (m - badChar[text.charCodeAt(shift + m)]) : 1
      } else {
        // 坏字符规则位移，确保至少移动1位
        const badCharVal = badChar[text.charCodeAt(shift + j)]
        shift += Math.max(1, j - badCharVal)
      }
    }
    return matches
  }

  function test() {
    console.log("Boyer-Moore 模式匹配 - JavaScript 实现")
    const text = "ABAAABCDABCABCABCAB"
    const pattern = "ABC"
    console.log("文本:", text)
    console.log("模式:", pattern)
    console.log("匹配位置:", search(pattern, text))
  }

  return { search, test }
})()

if (typeof module !== 'undefined' && module.exports) {
  module.exports = BoyerMoore
} else {
  BoyerMoore.test()
}
