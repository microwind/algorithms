/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - Rabin-Karp 模式匹配
 * 
 * 算法原理：
 * 1. 它是基于哈希的匹配算法。
 * 2. 核心在于滚动哈希 (Rolling Hash)，在移动窗口时避免重新计算整个哈希。
 * 3. 使用一个较大的基数 D 和一个素数 Q。
 * 
 * 时间复杂度：平均 O(n + m)，最坏 O(n * m)
 */
const RabinKarp = (function () {
  const D = 256
  const Q = 101

  /**
   * Rabin-Karp 搜索算法
   */
  function search(pattern, text) {
    const m = pattern.length
    const n = text.length
    const matches = []

    if (m === 0 || m > n) return matches

    let p = 0 // 模式串哈希值
    let t = 0 // 窗口哈希值
    let h = 1

    // h = D^(m-1) % Q
    for (let i = 0; i < m - 1; i++) {
      h = (h * D) % Q
    }

    // 计算初始哈希值
    for (let i = 0; i < m; i++) {
      p = (D * p + pattern.charCodeAt(i)) % Q
      t = (D * t + text.charCodeAt(i)) % Q
    }

    for (let i = 0; i <= n - m; i++) {
      if (p === t) {
        // 哈希匹配后，再进行字符比对
        let match = true
        for (let j = 0; j < m; j++) {
          if (text[i + j] !== pattern[j]) {
            match = false
            break
          }
        }
        if (match) matches.push(i)
      }

      // 计算下一个滚动哈希
      if (i < n - m) {
        t = (D * (t - text.charCodeAt(i) * h) + text.charCodeAt(i + m)) % Q
        if (t < 0) t += Q
      }
    }
    return matches
  }

  function test() {
    console.log("Rabin-Karp 模式匹配 - JavaScript 实现")
    const text = "ABABDABACDABABCABAB"
    const pattern = "ABABCABAB"
    console.log("文本:", text)
    console.log("模式:", pattern)
    console.log("匹配位置:", search(pattern, text))
  }

  return { search, test }
})()

if (typeof module !== 'undefined' && module.exports) {
  module.exports = RabinKarp
} else {
  RabinKarp.test()
}
