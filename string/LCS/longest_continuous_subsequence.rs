/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::cmp;

/**
 * 字符串算法 - 最长公共子串 (Longest Continuous Subsequence / Common Substring)
 * 
 * 算法原理：
 * 1. 要求子序列必须是连续且相邻的。
 * 2. 动态规划状态转移：
 *    - 当 str1[i-1] == str2[j-1] 时，dp[i][j] = dp[i-1][j-1] + 1
 *    - 否则，dp[i][j] = 0
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)
 */
pub struct LongestContinuousSubsequence;

impl LongestContinuousSubsequence {
    /// 求解最长连续公共子串
    pub fn find_lcs(s1: &str, s2: &str) -> (usize, String) {
        let m = s1.len();
        let n = s2.len();
        let chars1: Vec<char> = s1.chars().collect();
        let chars2: Vec<char> = s2.chars().collect();
        
        // dp[i][j] 存储以 chars1[i-1] 和 chars2[j-1] 结尾的最长公共子串长度
        let mut dp = vec![vec![0; n + 1]; m + 1];
        let mut max_length = 0;
        let mut end_index = 0;

        for i in 1..=m {
            for j in 1..=n {
                if chars1[i - 1] == chars2[j - 1] {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if dp[i][j] > max_length {
                        max_length = dp[i][j];
                        end_index = i;
                    }
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        let content = if max_length > 0 {
            let start = end_index - max_length;
            // 处理 UTF-8 字符截取
            chars1[start..end_index].iter().collect()
        } else {
            String::new()
        };

        (max_length, content)
    }

    /// 运行测试
    pub fn run_tests() {
        let test_cases = vec![
            ("ABCBDAB", "BDCAB", 2),
            ("HELLO", "HELLO", 5),
            ("ABCDEF", "ACE", 1),
            ("ABCDXYZ", "XYZABCD", 4),
            ("ABABC", "BABCA", 4),
        ];

        println!("最长连续公共子串测试 (Rust):");
        for (i, (s1, s2, expected)) in test_cases.into_iter().enumerate() {
            let (len, content) = Self::find_lcs(s1, s2);
            println!("用例 {}: [{}] vs [{}] | 长度: {} (预期: {}) | 内容: {} | 状态: {}",
                i + 1, s1, s2, len, expected, content, if len == expected { "OK" } else { "FAIL" });
        }
    }
}

fn main() {
    LongestContinuousSubsequence::run_tests();
}
