/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - KMP search algorithm
 * Knuth-Morris-Pratt string matching algorithm
 * efficient pattern searching with O(n+m) time complexity
 */

/// KMP search implementation
pub struct KMPSearch {
    pattern: String,
    lps: Vec<usize>, // longest proper prefix which is also suffix
}

impl KMPSearch {
    /// Create new KMP search with pattern
    pub fn new(pattern: &str) -> Self {
        let mut kmp = KMPSearch {
            pattern: pattern.to_string(),
            lps: Vec::new(),
        };
        kmp.compute_lps();
        kmp
    }
    
    /// Compute LPS (Longest Proper Prefix which is also Suffix) array
    /// time complexity: O(m) where m is pattern length
    fn compute_lps(&mut self) {
        let pattern_chars: Vec<char> = self.pattern.chars().collect();
        let m = pattern_chars.len();
        self.lps = vec![0; m];
        
        let mut length = 0; // length of the previous longest prefix suffix
        let mut i = 1;
        
        while i < m {
            if pattern_chars[i] == pattern_chars[length] {
                length += 1;
                self.lps[i] = length;
                i += 1;
            } else {
                if length != 0 {
                    length = self.lps[length - 1];
                } else {
                    self.lps[i] = 0;
                    i += 1;
                }
            }
        }
    }
    
    /// Search for pattern in text
    /// time complexity: O(n) where n is text length
    /// space complexity: O(m) for LPS array
    pub fn search(&self, text: &str) -> Vec<usize> {
        let text_chars: Vec<char> = text.chars().collect();
        let pattern_chars: Vec<char> = self.pattern.chars().collect();
        
        let n = text_chars.len();
        let m = pattern_chars.len();
        
        let mut indices = Vec::new();
        let mut i = 0; // index for text
        let mut j = 0; // index for pattern
        
        while i < n {
            if pattern_chars[j] == text_chars[i] {
                i += 1;
                j += 1;
                
                if j == m {
                    // pattern found at position i - j
                    indices.push(i - j);
                    j = self.lps[j - 1];
                }
            } else {
                if j != 0 {
                    j = self.lps[j - 1];
                } else {
                    i += 1;
                }
            }
        }
        
        indices
    }
    
    /// Check if pattern exists in text
    pub fn contains(&self, text: &str) -> bool {
        !self.search(text).is_empty()
    }
    
    /// Count number of pattern occurrences
    pub fn count_occurrences(&self, text: &str) -> usize {
        self.search(text).len()
    }
    
    /// Get pattern string
    pub fn get_pattern(&self) -> &str {
        &self.pattern
    }
    
    /// Get LPS array (for debugging)
    pub fn get_lps(&self) -> &[usize] {
        &self.lps
    }
}

/// Simple wrapper function for quick KMP search
pub fn kmp_search(text: &str, pattern: &str) -> Vec<usize> {
    let kmp = KMPSearch::new(pattern);
    kmp.search(text)
}

/// Simple wrapper function to check if pattern exists
pub fn kmp_contains(text: &str, pattern: &str) -> bool {
    let kmp = KMPSearch::new(pattern);
    kmp.contains(text)
}

/// Simple wrapper function to count occurrences
pub fn kmp_count(text: &str, pattern: &str) -> usize {
    let kmp = KMPSearch::new(pattern);
    kmp.count_occurrences(text)
}

/// main function - test KMP search algorithm
fn main() {
    println!("{}", "=".repeat(70));
    println!("KMP Search Algorithm - Rust Implementation");
    println!("{}", "=".repeat(70));
    
    let text = "ABABDABACDABABCABABABACDABABCABAB";
    let pattern = "ABABCABAB";
    
    println!("\n=== Basic Search Test ===");
    println!("Text: {}", text);
    println!("Pattern: {}", pattern);
    
    let kmp = KMPSearch::new(pattern);
    let indices = kmp.search(text);
    
    println!("Pattern found at positions: {:?}", indices);
    println!("Number of occurrences: {}", kmp.count_occurrences(text));
    println!("Pattern exists in text: {}", kmp.contains(text));
    
    println!("\n=== LPS Array ===");
    println!("Pattern: {}", pattern);
    println!("LPS array: {:?}", kmp.get_lps());
    
    println!("\n=== Multiple Pattern Test ===");
    let test_cases = vec![
        ("AAAAA", "AAA"),
        ("HELLO WORLD", "WORLD"),
        ("MISSISSIPPI", "ISSI"),
        ("BANANA", "ANA"),
        ("CHOCOLATE", "LATE"),
        ("PROGRAMMING", "GRAM"),
    ];
    
    for (text, pattern) in test_cases {
        let indices = kmp_search(text, pattern);
        println!("Text: \"{}\", Pattern: \"{}\" -> {:?}", text, pattern, indices);
    }
    
    println!("\n=== Edge Cases Test ===");
    let edge_cases = vec![
        ("", ""),           // empty text, empty pattern
        ("A", ""),          // non-empty text, empty pattern
        ("", "A"),          // empty text, non-empty pattern
        ("A", "A"),         // single character match
        ("A", "B"),         // single character no match
        ("AAAA", "AA"),     // overlapping matches
        ("ABC", "ABC"),     // exact match
        ("ABC", "ABCD"),    // pattern longer than text
    ];
    
    for (text, pattern) in edge_cases {
        let contains = kmp_contains(text, pattern);
        let count = if pattern.is_empty() { 0 } else { kmp_count(text, pattern) };
        println!("Text: \"{}\", Pattern: \"{}\" -> contains: {}, count: {}", 
                text, pattern, contains, count);
    }
    
    println!("\n=== Algorithm Characteristics ===");
    println!("KMP Algorithm:");
    println!("  - Preprocessing time: O(m) where m is pattern length");
    println!("  - Searching time: O(n) where n is text length");
    println!("  - Space complexity: O(m) for LPS array");
    println!("  - Total time complexity: O(n + m)");
    println!("  - Worst case: O(n * m) for naive algorithm");
    println!("  - Best case: O(n) for KMP algorithm");
    
    println!("\n=== Key Features ===");
    println!("  - No character comparison is repeated");
    println!("  - Uses failure function (LPS array) to skip comparisons");
    println!("  - Handles overlapping patterns efficiently");
    println!("  - Suitable for large texts and patterns");
    
    println!("\n=== Common Applications ===");
    println!("KMP search is used in:");
    println!("  - Text editors and word processors");
    println!("  - DNA sequence analysis");
    println!("  - Plagiarism detection");
    println!("  - Network intrusion detection");
    println!("  - Bioinformatics and computational biology");
    println!("  - Search engines and information retrieval");
    
    println!("\n=== Comparison with Other Algorithms ===");
    println!("KMP vs Naive Search:");
    println!("  - Naive: O(n * m) worst case");
    println!("  - KMP: O(n + m) worst case");
    println!("  - KMP is more efficient for patterns with repeating prefixes");
    
    println!("\nKMP vs Boyer-Moore:");
    println!("  - Boyer-Moore: O(n / m) average case for English text");
    println!("  - KMP: O(n + m) worst case");
    println!("  - Boyer-Moore is better for long patterns");
    println!("  - KMP is better for patterns with repeating prefixes");
    
    println!("\nKMP vs Rabin-Karp:");
    println!("  - Rabin-Karp: O(n + m) average, O(n * m) worst case");
    println!("  - KMP: O(n + m) worst case");
    println!("  - Rabin-Karp uses hashing, good for multiple patterns");
    println!("  - KMP uses LPS array, good for single pattern");
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_basic_search() {
        let text = "ABABDABACDABABCABABABACDABABCABAB";
        let pattern = "ABABCABAB";
        let indices = kmp_search(text, pattern);
        assert_eq!(indices, vec![10, 26]);
    }
    
    #[test]
    fn test_contains() {
        assert!(kmp_contains("HELLO WORLD", "WORLD"));
        assert!(!kmp_contains("HELLO WORLD", "BYE"));
    }
    
    #[test]
    fn test_count_occurrences() {
        assert_eq!(kmp_count("AAAAA", "AA"), 4);
        assert_eq!(kmp_count("MISSISSIPPI", "ISSI"), 2);
    }
    
    #[test]
    fn test_empty_pattern() {
        let indices = kmp_search("HELLO", "");
        assert_eq!(indices, vec![0, 1, 2, 3, 4, 5]);
    }
    
    #[test]
    fn test_empty_text() {
        let indices = kmp_search("", "A");
        assert!(indices.is_empty());
    }
    
    #[test]
    fn test_lps_computation() {
        let kmp = KMPSearch::new("ABABCABAB");
        let expected_lps = vec![0, 0, 1, 1, 2, 0, 1, 2, 3];
        assert_eq!(kmp.get_lps(), &expected_lps);
    }
}
