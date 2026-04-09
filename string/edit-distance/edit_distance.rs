/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

use std::cmp;
use std::collections::HashMap;

/**
 * 字符串算法 - 编辑距离 (Edit Distance / Levenshtein Distance)
 * 
 * 算法原理：
 * 1. 计算将一个字符串转换为另一个字符串所需的最少操作次数。
 * 2. 操作包括：插入、删除、替换。
 * 
 * 时间复杂度：O(m * n)
 * 空间复杂度：O(m * n)，可优化至 O(min(m, n))
 */

pub struct EditDistance;

impl EditDistance {
    /// 动态规划版本 - 计算编辑距离
    pub fn edit_distance(word1: &str, word2: &str) -> usize {
        let n = word1.len();
        let m = word2.len();
        let s1: Vec<char> = word1.chars().collect();
        let s2: Vec<char> = word2.chars().collect();
        
        let mut dp = vec![vec![0; m + 1]; n + 1];

        for i in 0..=n { dp[i][0] = i; }
        for j in 0..=m { dp[0][j] = j; }

        for i in 1..=n {
            for j in 1..=m {
                if s1[i - 1] == s2[j - 1] {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + cmp::min(
                        dp[i - 1][j], // 删除
                        cmp::min(dp[i][j - 1], // 插入
                                dp[i - 1][j - 1]) // 替换
                    );
                }
            }
        }
        dp[n][m]
    }

    /// 空间优化后的动态规划版本
    pub fn edit_distance_optimized(word1: &str, word2: &str) -> usize {
        let (w1, w2) = if word1.len() < word2.len() {
            (word2, word1)
        } else {
            (word1, word2)
        };
        
        let n = w1.len();
        let m = w2.len();
        let s1: Vec<char> = w1.chars().collect();
        let s2: Vec<char> = w2.chars().collect();
        
        let mut prev = (0..=m).collect::<Vec<usize>>();
        let mut curr = vec![0; m + 1];

        for i in 1..=n {
            curr[0] = i;
            for j in 1..=m {
                if s1[i - 1] == s2[j - 1] {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + cmp::min(prev[j], cmp::min(curr[j - 1], prev[j - 1]));
                }
            }
            prev.copy_from_slice(&curr);
        }
        prev[m]
    }

    /// 递归版本（结合记忆化）
    pub fn edit_distance_recursive(word1: &str, word2: &str) -> usize {
        let s1: Vec<char> = word1.chars().collect();
        let s2: Vec<char> = word2.chars().collect();
        let mut memo = HashMap::new();

        fn helper(i: usize, j: usize, s1: &[char], s2: &[char], memo: &mut HashMap<(usize, usize), usize>) -> usize {
            if i == 0 { return j; }
            if j == 0 { return i; }
            if let Some(&res) = memo.get(&(i, j)) {
                return res;
            }

            let res = if s1[i - 1] == s2[j - 1] {
                helper(i - 1, j - 1, s1, s2, memo)
            } else {
                1 + cmp::min(
                    helper(i - 1, j, s1, s2, memo),
                    cmp::min(helper(i, j - 1, s1, s2, memo),
                            helper(i - 1, j - 1, s1, s2, memo))
                )
            };
            memo.insert((i, j), res);
            res
        }

        helper(s1.len(), s2.len(), &s1, &s2, &mut memo)
    }

    /// 获取编辑操作步骤
    pub fn get_edit_operations(word1: &str, word2: &str) -> Vec<String> {
        let n = word1.len();
        let m = word2.len();
        let s1: Vec<char> = word1.chars().collect();
        let s2: Vec<char> = word2.chars().collect();
        let mut dp = vec![vec![0; m + 1]; n + 1];

        for i in 0..=n { dp[i][0] = i; }
        for j in 0..=m { dp[0][j] = j; }
        for i in 1..=n {
            for j in 1..=m {
                if s1[i - 1] == s2[j - 1] {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + cmp::min(dp[i - 1][j], cmp::min(dp[i][j - 1], dp[i - 1][j - 1]));
                }
            }
        }

        let mut ops = Vec::new();
        let (mut i, mut j) = (n, m);
        while i > 0 || j > 0 {
            if i > 0 && j > 0 && s1[i - 1] == s2[j - 1] {
                i -= 1; j -= 1;
            } else if i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1 {
                ops.insert(0, format!("替换 '{}' 为 '{}'", s1[i - 1], s2[j - 1]));
                i -= 1; j -= 1;
            } else if i > 0 && dp[i][j] == dp[i - 1][j] + 1 {
                ops.insert(0, format!("删除 '{}'", s1[i - 1]));
                i -= 1;
            } else {
                ops.insert(0, format!("插入 '{}'", s2[j - 1]));
                j -= 1;
            }
        }
        ops
    }

    /// 计算相似度
    pub fn get_similarity_ratio(word1: &str, word2: &str) -> f64 {
        let distance = Self::edit_distance(word1, word2);
        let max_len = cmp::max(word1.len(), word2.len());
        if max_len == 0 { return 1.0; }
        1.0 - (distance as f64) / (max_len as f64)
    }
}

fn main() {
    println!("====================================================");
    println!("编辑距离 (Edit Distance) - Rust 实现");
    println!("====================================================");

    let test_cases = vec![
        ("kitten", "sitting"),
        ("sunday", "saturday"),
        ("abc", ""),
        ("", "abc"),
        ("same", "same"),
    ];

    for (s1, s2) in test_cases {
        println!("\n源字符串: \"{}\"", s1);
        println!("目标字符串: \"{}\"", s2);
        println!("最小编辑距离 (DP): {}", EditDistance::edit_distance(s1, s2));
        println!("最小编辑距离 (优化DP): {}", EditDistance::edit_distance_optimized(s1, s2));
        println!("最小编辑距离 (递归): {}", EditDistance::edit_distance_recursive(s1, s2));
        println!("相似度: {:.2}%", EditDistance::get_similarity_ratio(s1, s2) * 100.0);
        if s1.len() < 10 && s2.len() < 10 {
            println!("操作步骤: {:?}", EditDistance::get_edit_operations(s1, s2));
        }
    }
}
