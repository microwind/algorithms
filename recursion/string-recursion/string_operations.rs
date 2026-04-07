/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 字符串递归操作示例
 * 
 * 算法特点：
 * - 演示递归在字符串处理中的应用
 * - 包含字符串反转、回文检查、元音计数
 * 
 * 学习重点：理解递归在字符串操作中的使用
 */

/**
 * 递归反转字符串
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param s 要反转的字符串
 * @return 反转后的字符串
 */
fn reverse_string(s: &str) -> String {
    // 基础情况：空字符串或单个字符
    if s.len() <= 1 {
        return s.to_string();
    }
    
    // 递归：剩余部分反转 + 第一个字符放到末尾
    let first_char = s.chars().next().unwrap();
    let remaining = &s[1..];
    reverse_string(remaining) + &first_char.to_string()
}

/**
 * 递归检查字符串是否为回文
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param s 要检查的字符串
 * @return 是否为回文
 */
fn is_palindrome(s: &str) -> bool {
    let s_lower = s.to_lowercase(); // 忽略大小写
    
    // 基础情况：空字符串或单个字符是回文
    if s_lower.len() <= 1 {
        return true;
    }
    
    // 如果首尾字符不同，不是回文
    let first_char = s_lower.chars().next().unwrap();
    let last_char = s_lower.chars().last().unwrap();
    if first_char != last_char {
        return false;
    }
    
    // 递归检查去掉首尾后的中间部分
    let remaining = &s_lower[1..s_lower.len()-1];
    is_palindrome(remaining)
}

/**
 * 递归计算字符串中元音字母的数量
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param s 要计算的字符串
 * @return 元音字母数量
 */
fn count_vowels(s: &str) -> i32 {
    let vowels = "aeiouAEIOU";
    
    // 基础情况：空字符串
    if s.is_empty() {
        return 0;
    }
    
    // 检查第一个字符是否是元音
    let first_char = s.chars().next().unwrap();
    let first_is_vowel = if vowels.contains(first_char) { 1 } else { 0 };
    
    // 递归计算剩余部分
    let remaining = &s[1..];
    first_is_vowel + count_vowels(remaining)
}

/**
 * 主函数 - 测试字符串递归操作
 */
fn main() {
    // 测试1：字符串反转
    let test_str1 = "Hello";
    println!("1. 字符串反转:");
    println!("   原字符串: '{}'", test_str1);
    println!("   反转后:   '{}'", reverse_string(test_str1));
    println!("===");
    
    // 测试2：回文检查
    println!("2. 回文检查:");
    let test_cases = ["radar", "hello", "Aba", "level", "aabbaa", "cc", "ddd"];
    for s in test_cases.iter() {
        let result = if is_palindrome(s) { "是回文" } else { "不是回文" };
        println!("   '{}' -> {}", s, result);
    }
    println!("===");
    
    // 测试3：元音计数
    let test_str2 = "Hello World";
    println!("3. 元音计数:");
    println!("   字符串: '{}'", test_str2);
    println!("   元音数量: {}", count_vowels(test_str2));
    println!("===");
}

/*打印结果
jarry@Mac string-recursion % rustc string_operations.rs && ./string_operations
1. 字符串反转:
   原字符串: 'Hello'
   反转后:   'olleH'
===
2. 回文检查:
   'radar' -> 是回文
   'hello' -> 不是回文
   'Aba' -> 是回文
   'level' -> 是回文
   'aabbaa' -> 是回文
   'cc' -> 是回文
   'ddd' -> 是回文
===
3. 元音计数:
   字符串: 'Hello World'
   元音数量: 3
===
*/
