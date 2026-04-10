/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串算法 - 朴素字符串搜索 (Naive String Search)
 * 
 * 算法原理：
 * 1. 暴力匹配，逐个对比。
 * 2. 将模式串 (pattern) 与主串 (text) 对齐，如果不匹配则右移一位。
 * 
 * 时间复杂度：O(n * m)
 * 空间复杂度：O(1)
 */
pub struct StringSearch;

impl StringSearch {
    /// 朴素搜索实现
    pub fn find(pattern: &str, text: &str) -> Option<usize> {
        let m = pattern.len();
        let n = text.len();
        
        if m == 0 { return Some(0); }
        if m > n { return None; }

        let s_pat: Vec<char> = pattern.chars().collect();
        let s_text: Vec<char> = text.chars().collect();

        // 关键点：限制外层循环到 n - m
        for i in 0..=(s_text.len() - s_pat.len()) {
            let mut j = 0;
            while j < m && s_text[i + j] == s_pat[j] {
                j += 1;
            }
            if j == m {
                return Some(i);
            }
        }
        None
    }

    /// 运行测试
    pub fn run_tests() {
        let test_cases = vec![
            ("ABC", "AABABC", Some(3)),
            ("AAB", "AAAABC", Some(2)),
            ("ABC", "AABAC", None),
        ];

        println!("朴素字符串搜索测试 (Rust):");
        for (i, (p, t, expected)) in test_cases.into_iter().enumerate() {
            let res = Self::find(p, t);
            println!("用例 {}: [{}] in [{}] | 结果: {:?} (预期: {:?}) | 状态: {}",
                i + 1, p, t, res, expected, if res == expected { "OK" } else { "FAIL" });
        }
    }
}

fn main() {
    StringSearch::run_tests();
}
