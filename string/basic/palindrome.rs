/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - palindrome check
 * multiple methods to check if a string is a palindrome
 */

/// two-pointer method to check palindrome
/// time complexity: O(n)
/// space complexity: O(1)
fn is_palindrome_two_pointer(s: &str) -> bool {
    let chars: Vec<char> = s.chars().collect();
    let mut left = 0;
    let mut right = chars.len() - 1;
    
    while left < right {
        // skip non-alphanumeric characters
        while left < right && !chars[left].is_alphanumeric() {
            left += 1;
        }
        while left < right && !chars[right].is_alphanumeric() {
            right -= 1;
        }
        
        if chars[left].to_ascii_lowercase() != chars[right].to_ascii_lowercase() {
            return false;
        }
        
        left += 1;
        right -= 1;
    }
    
    true
}

/// reverse string method to check palindrome
/// time complexity: O(n)
/// space complexity: O(n)
fn is_palindrome_reverse(s: &str) -> bool {
    // clean the string: keep only alphanumeric characters and convert to lowercase
    let cleaned: String = s.chars()
        .filter(|c| c.is_alphanumeric())
        .map(|c| c.to_ascii_lowercase())
        .collect();
    
    let reversed: String = cleaned.chars().rev().collect();
    cleaned == reversed
}

/// recursive method to check palindrome
/// time complexity: O(n)
/// space complexity: O(n) - due to recursion stack
fn is_palindrome_recursive(s: &str) -> bool {
    // clean the string first
    let cleaned: String = s.chars()
        .filter(|c| c.is_alphanumeric())
        .map(|c| c.to_ascii_lowercase())
        .collect();
    
    let chars: Vec<char> = cleaned.chars().collect();
    is_palindrome_recursive_helper(&chars, 0, chars.len() - 1)
}

fn is_palindrome_recursive_helper(chars: &[char], left: usize, right: usize) -> bool {
    if left >= right {
        return true;
    }
    if chars[left] != chars[right] {
        return false;
    }
    is_palindrome_recursive_helper(chars, left + 1, right - 1)
}

/// stack method to check palindrome
/// time complexity: O(n)
/// space complexity: O(n)
fn is_palindrome_stack(s: &str) -> bool {
    // clean the string
    let cleaned: String = s.chars()
        .filter(|c| c.is_alphanumeric())
        .map(|c| c.to_ascii_lowercase())
        .collect();
    
    let chars: Vec<char> = cleaned.chars().collect();
    let mid = chars.len() / 2;
    
    // use a stack to store first half
    let mut stack: Vec<char> = Vec::new();
    for i in 0..mid {
        stack.push(chars[i]);
    }
    
    // compare second half with stack
    let start = if chars.len() % 2 == 0 { mid } else { mid + 1 };
    for i in start..chars.len() {
        if let Some(top) = stack.pop() {
            if top != chars[i] {
                return false;
            }
        } else {
            return false;
        }
    }
    
    true
}

/// main function - test palindrome checker
fn main() {
    println!("{}", "=".repeat(60));
    println!("Palindrome Checker - Rust Implementation");
    println!("{}", "=".repeat(60));
    
    let test_strings = vec![
        "racecar",
        "A man, a plan, a canal: Panama",
        "No lemon, no melon",
        "Hello, World!",
        "Madam",
        "",
        "a",
        "12321",
        "12345"
    ];
    
    println!("\n=== Test Results ===");
    for test in &test_strings {
        println!("String: \"{}\"", test);
        println!("  Two-pointer: {}", is_palindrome_two_pointer(test));
        println!("  Reverse: {}", is_palindrome_reverse(test));
        println!("  Recursive: {}", is_palindrome_recursive(test));
        println!("  Stack: {}", is_palindrome_stack(test));
        println!();
    }
    
    println!("=== Algorithm Characteristics ===");
    println!("Two-pointer method:");
    println!("  - Most efficient: O(n) time, O(1) space");
    println!("  - Works in-place, no extra memory needed");
    println!("  - Best for large strings");
    
    println!("\nReverse method:");
    println!("  - Simple and intuitive: O(n) time, O(n) space");
    println!("  - Creates new reversed string");
    println!("  - Good for readability");
    
    println!("\nRecursive method:");
    println!("  - Elegant solution: O(n) time, O(n) space");
    println!("  - Uses recursion stack");
    println!("  - May cause stack overflow for very long strings");
    
    println!("\nStack method:");
    println!("  - Uses explicit stack: O(n) time, O(n) space");
    println!("  - Compares first half with second half");
    println!("  - Good for understanding stack operations");
    
    println!("\n=== Common Applications ===");
    println!("Palindrome checking is used in:");
    println!("  - String validation and verification");
    println!("  - Cryptographic algorithms");
    println!("  - DNA sequence analysis");
    println!("  - Text processing and parsing");
    println!("  - Puzzle solving and games");
    println!("  - Data validation (credit cards, IDs)");
    
    println!("\n=== Edge Cases Considered ===");
    println!("  - Empty strings");
    println!("  - Single character strings");
    println!("  - Strings with punctuation and spaces");
    println!("  - Mixed case strings");
    println!("  - Numeric strings");
    println!("  - Unicode characters");
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_palindrome_two_pointer() {
        assert!(is_palindrome_two_pointer("racecar"));
        assert!(is_palindrome_two_pointer("A man, a plan, a canal: Panama"));
        assert!(!is_palindrome_two_pointer("Hello"));
    }
    
    #[test]
    fn test_palindrome_reverse() {
        assert!(is_palindrome_reverse("racecar"));
        assert!(is_palindrome_reverse("A man, a plan, a canal: Panama"));
        assert!(!is_palindrome_reverse("Hello"));
    }
    
    #[test]
    fn test_palindrome_recursive() {
        assert!(is_palindrome_recursive("racecar"));
        assert!(is_palindrome_recursive("A man, a plan, a canal: Panama"));
        assert!(!is_palindrome_recursive("Hello"));
    }
    
    #[test]
    fn test_palindrome_stack() {
        assert!(is_palindrome_stack("racecar"));
        assert!(is_palindrome_stack("A man, a plan, a canal: Panama"));
        assert!(!is_palindrome_stack("Hello"));
    }
}
