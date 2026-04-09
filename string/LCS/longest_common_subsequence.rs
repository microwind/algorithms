/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - longest common subsequence (LCS)
 * dynamic programming solution for finding longest common subsequence
 * time complexity: O(n*m) where n and m are lengths of input strings
 */

use std::cmp::max;

/// LCS implementation with dynamic programming
pub struct LongestCommonSubsequence {
    text1: String,
    text2: String,
    dp: Vec<Vec<usize>>,
}

impl LongestCommonSubsequence {
    /// Create new LCS instance
    pub fn new(text1: &str, text2: &str) -> Self {
        let mut lcs = LongestCommonSubsequence {
            text1: text1.to_string(),
            text2: text2.to_string(),
            dp: Vec::new(),
        };
        lcs.compute_dp();
        lcs
    }
    
    /// Compute DP table for LCS
    /// time complexity: O(n*m)
    /// space complexity: O(n*m)
    fn compute_dp(&mut self) {
        let n = self.text1.len();
        let m = self.text2.len();
        
        // initialize DP table with zeros
        self.dp = vec![vec![0; m + 1]; n + 1];
        
        // fill DP table
        for i in 1..=n {
            for j in 1..=m {
                let text1_chars: Vec<char> = self.text1.chars().collect();
                let text2_chars: Vec<char> = self.text2.chars().collect();
                
                if text1_chars[i - 1] == text2_chars[j - 1] {
                    self.dp[i][j] = self.dp[i - 1][j - 1] + 1;
                } else {
                    self.dp[i][j] = max(self.dp[i - 1][j], self.dp[i][j - 1]);
                }
            }
        }
    }
    
    /// Get LCS length
    pub fn lcs_length(&self) -> usize {
        let n = self.text1.len();
        let m = self.text2.len();
        self.dp[n][m]
    }
    
    /// Reconstruct LCS string from DP table
    /// time complexity: O(n+m)
    /// space complexity: O(n+m) for the result
    pub fn get_lcs(&self) -> String {
        let text1_chars: Vec<char> = self.text1.chars().collect();
        let text2_chars: Vec<char> = self.text2.chars().collect();
        
        let mut i = self.text1.len();
        let mut j = self.text2.len();
        let mut lcs_chars: Vec<char> = Vec::new();
        
        while i > 0 && j > 0 {
            if text1_chars[i - 1] == text2_chars[j - 1] {
                lcs_chars.push(text1_chars[i - 1]);
                i -= 1;
                j -= 1;
            } else if self.dp[i - 1][j] > self.dp[i][j - 1] {
                i -= 1;
            } else {
                j -= 1;
            }
        }
        
        lcs_chars.reverse();
        lcs_chars.into_iter().collect()
    }
    
    /// Space-optimized DP method
    /// time complexity: O(n*m)
    /// space complexity: O(min(n,m))
    pub fn lcs_length_optimized(&self) -> usize {
        let text1_chars: Vec<char> = self.text1.chars().collect();
        let text2_chars: Vec<char> = self.text2.chars().collect();
        
        let n = text1_chars.len();
        let m = text2_chars.len();
        
        // ensure text2 is the shorter string for space optimization
        if n < m {
            return self.lcs_length_optimized_helper(&text2_chars, &text1_chars);
        }
        self.lcs_length_optimized_helper(&text1_chars, &text2_chars)
    }
    
    fn lcs_length_optimized_helper(&self, longer: &[char], shorter: &[char]) -> usize {
        let n = longer.len();
        let m = shorter.len();
        
        let mut prev = vec![0; m + 1];
        let mut curr = vec![0; m + 1];
        
        for i in 1..=n {
            for j in 1..=m {
                if longer[i - 1] == shorter[j - 1] {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            std::mem::swap(&mut prev, &mut curr);
        }
        
        prev[m]
    }
    
    /// Get similarity ratio
    pub fn get_similarity_ratio(&self) -> f64 {
        let lcs_length = self.lcs_length();
        let max_length = max(self.text1.len(), self.text2.len());
        if max_length == 0 {
            1.0
        } else {
            lcs_length as f64 / max_length as f64
        }
    }
    
    /// Print DP table for debugging
    pub fn print_dp_table(&self) {
        println!("DP Table:");
        let text2_chars: Vec<char> = self.text2.chars().collect();
        print!("    ");
        for ch in &text2_chars {
            print!("{} ", ch);
        }
        println!();
        
        let text1_chars: Vec<char> = self.text1.chars().collect();
        for i in 0..=self.text1.len() {
            if i == 0 {
                print!("  ");
            } else {
                print!("{} ", text1_chars[i - 1]);
            }
            
            for j in 0..=self.text2.len() {
                print!("{} ", self.dp[i][j]);
            }
            println!();
        }
    }
}

/// Convenience functions
pub fn lcs_length(text1: &str, text2: &str) -> usize {
    let lcs = LongestCommonSubsequence::new(text1, text2);
    lcs.lcs_length()
}

pub fn get_lcs(text1: &str, text2: &str) -> String {
    let lcs = LongestCommonSubsequence::new(text1, text2);
    lcs.get_lcs()
}

pub fn lcs_similarity(text1: &str, text2: &str) -> f64 {
    let lcs = LongestCommonSubsequence::new(text1, text2);
    lcs.get_similarity_ratio()
}

/// main function - test LCS algorithm
fn main() {
    println!("{}", "=".repeat(70));
    println!("Longest Common Subsequence - Rust Implementation");
    println!("{}", "=".repeat(70));
    
    let test_cases = vec![
        ("AGGTAB", "GXTXAYB", "GTAB"),
        ("ABCBDAB", "BDCAB", "BCAB"),
        ("XMJYAUZ", "MZJAWXU", "MJAU"),
        ("HELLO", "WORLD", "LO"),
        ("", "ABC", ""),
        ("ABC", "", ""),
        ("SAME", "SAME", "SAME"),
    ];
    
    println!("\n=== Test Results ===");
    for (text1, text2, expected) in test_cases {
        let lcs = LongestCommonSubsequence::new(text1, text2);
        let lcs_string = lcs.get_lcs();
        let lcs_length = lcs.lcs_length();
        let similarity = lcs.get_similarity_ratio();
        
        println!("Text1: \"{}\"", text1);
        println!("Text2: \"{}\"", text2);
        println!("LCS: \"{}\" (Length: {})", lcs_string, lcs_length);
        println!("Similarity: {:.2}%", similarity * 100.0);
        println!("Expected: \"{}\"", expected);
        println!("Match: {}", if lcs_string == expected { "YES" } else { "NO" });
        println!();
    }
    
    println!("=== Algorithm Comparison ===");
    let text1 = "ABCDGH";
    let text2 = "AEDFHR";
    let lcs = LongestCommonSubsequence::new(text1, text2);
    
    println!("Text1: \"{}\", Text2: \"{}\"", text1, text2);
    println!("DP Method: {}", lcs.lcs_length());
    println!("Optimized DP: {}", lcs.lcs_length_optimized());
    println!("LCS String: \"{}\"", lcs.get_lcs());
    
    println!("\n=== DP Table Example ===");
    let example = LongestCommonSubsequence::new("ABC", "ABC");
    example.print_dp_table();
    
    println!("\n=== Algorithm Characteristics ===");
    println!("Dynamic Programming Approach:");
    println!("  - Time Complexity: O(n*m)");
    println!("  - Space Complexity: O(n*m) or O(min(n,m)) optimized");
    println!("  - Guarantees optimal solution");
    println!("  - Suitable for moderate string lengths");
    
    println!("\n=== Common Applications ===");
    println!("LCS is used in:");
    println!("  - DNA sequence analysis and comparison");
    println!("  - File comparison tools (diff)");
    println!("  - Plagiarism detection");
    println!("  - Version control systems");
    println!("  - Bioinformatics and computational biology");
    println!("  - Data compression algorithms");
    println!("  - Spell checking and auto-correction");
    
    println!("\n=== Variations and Extensions ===");
    println!("Related problems:");
    println!("  - Longest Common Substring (continuous)");
    println!("  - Shortest Common Supersequence");
    println!("  - Edit Distance (Levenshtein distance)");
    println!("  - Longest Palindromic Subsequence");
    println!("  - Sequence alignment in bioinformatics");
    
    println!("\n=== Performance Tips ===");
    println!("Optimization strategies:");
    println!("  - Use space-optimized DP for large strings");
    println!("  - Consider early termination for exact matches");
    println!("  - Use rolling hash for specific patterns");
    println!("  - Parallel processing for multiple comparisons");
    
    println!("\n=== Edge Cases ===");
    println!("  - Empty strings");
    println!("  - Identical strings");
    println!("  - Strings with no common characters");
    println!("  - Very long strings (consider memory limits)");
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_basic_lcs() {
        assert_eq!(lcs_length("AGGTAB", "GXTXAYB"), 4);
        assert_eq!(get_lcs("AGGTAB", "GXTXAYB"), "GTAB");
    }
    
    #[test]
    fn test_empty_strings() {
        assert_eq!(lcs_length("", "ABC"), 0);
        assert_eq!(lcs_length("ABC", ""), 0);
        assert_eq!(get_lcs("", "ABC"), "");
        assert_eq!(get_lcs("ABC", ""), "");
    }
    
    #[test]
    fn test_identical_strings() {
        assert_eq!(lcs_length("SAME", "SAME"), 4);
        assert_eq!(get_lcs("SAME", "SAME"), "SAME");
        assert_eq!(lcs_similarity("SAME", "SAME"), 1.0);
    }
    
    #[test]
    fn test_no_common_characters() {
        assert_eq!(lcs_length("ABC", "XYZ"), 0);
        assert_eq!(get_lcs("ABC", "XYZ"), "");
        assert_eq!(lcs_similarity("ABC", "XYZ"), 0.0);
    }
    
    #[test]
    fn test_optimized_dp() {
        let lcs = LongestCommonSubsequence::new("ABCDEF", "FBDAMN");
        assert_eq!(lcs.lcs_length(), lcs.lcs_length_optimized());
    }
}
