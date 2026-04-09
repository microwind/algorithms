/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - palindrome check
 * multiple methods to check if a string is a palindrome
 */

/**
 * two-pointer method to check palindrome
 * time complexity: O(n)
 * space complexity: O(1)
 */
function isPalindromeTwoPointer(s) {
    let left = 0;
    let right = s.length - 1;
    
    while (left < right) {
        // skip non-alphanumeric characters
        while (left < right && !isAlphanumeric(s[left])) {
            left++;
        }
        while (left < right && !isAlphanumeric(s[right])) {
            right--;
        }
        
        if (s[left].toLowerCase() !== s[right].toLowerCase()) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

// helper function to check if character is alphanumeric
function isAlphanumeric(c) {
    return /[a-zA-Z0-9]/.test(c);
}

/**
 * reverse string method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n)
 */
function isPalindromeReverse(s) {
    // clean the string: keep only alphanumeric characters and convert to lowercase
    const cleaned = s.replace(/[^a-zA-Z0-9]/g, '').toLowerCase();
    const reversed = cleaned.split('').reverse().join('');
    return cleaned === reversed;
}

/**
 * recursive method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n) - due to recursion stack
 */
function isPalindromeRecursive(s) {
    // clean the string first
    const cleaned = s.replace(/[^a-zA-Z0-9]/g, '').toLowerCase();
    return isPalindromeRecursiveHelper(cleaned, 0, cleaned.length - 1);
}

function isPalindromeRecursiveHelper(s, left, right) {
    if (left >= right) {
        return true;
    }
    if (s[left] !== s[right]) {
        return false;
    }
    return isPalindromeRecursiveHelper(s, left + 1, right - 1);
}

/**
 * stack method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n)
 */
function isPalindromeStack(s) {
    // clean the string
    const cleaned = s.replace(/[^a-zA-Z0-9]/g, '').toLowerCase();
    
    // use a stack to store characters
    const stack = [];
    
    // push first half of characters
    const mid = Math.floor(cleaned.length / 2);
    for (let i = 0; i < mid; i++) {
        stack.push(cleaned[i]);
    }
    
    // compare second half with stack
    const start = cleaned.length % 2 === 0 ? mid : mid + 1;
    for (let i = start; i < cleaned.length; i++) {
        if (stack.pop() !== cleaned[i]) {
            return false;
        }
    }
    
    return true;
}

/**
 * main function - test palindrome checker
 */
function testPalindromeChecker() {
    console.log("=".repeat(60));
    console.log("Palindrome Checker - JavaScript Implementation");
    console.log("=".repeat(60));
    
    const testStrings = [
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
    
    console.log("\n=== Test Results ===");
    for (const test of testStrings) {
        console.log(`String: "${test}"`);
        console.log(`  Two-pointer: ${isPalindromeTwoPointer(test)}`);
        console.log(`  Reverse: ${isPalindromeReverse(test)}`);
        console.log(`  Recursive: ${isPalindromeRecursive(test)}`);
        console.log(`  Stack: ${isPalindromeStack(test)}`);
        console.log();
    }
    
    console.log("=== Algorithm Characteristics ===");
    console.log("Two-pointer method:");
    console.log("  - Most efficient: O(n) time, O(1) space");
    console.log("  - Works in-place, no extra memory needed");
    console.log("  - Best for large strings");
    
    console.log("\nReverse method:");
    console.log("  - Simple and intuitive: O(n) time, O(n) space");
    console.log("  - Creates new reversed string");
    console.log("  - Good for readability");
    
    console.log("\nRecursive method:");
    console.log("  - Elegant solution: O(n) time, O(n) space");
    console.log("  - Uses recursion stack");
    console.log("  - May cause stack overflow for very long strings");
    
    console.log("\nStack method:");
    console.log("  - Uses explicit stack: O(n) time, O(n) space");
    console.log("  - Compares first half with second half");
    console.log("  - Good for understanding stack operations");
    
    console.log("\n=== Common Applications ===");
    console.log("Palindrome checking is used in:");
    console.log("  - String validation and verification");
    console.log("  - Cryptographic algorithms");
    console.log("  - DNA sequence analysis");
    console.log("  - Text processing and parsing");
    console.log("  - Puzzle solving and games");
    console.log("  - Data validation (credit cards, IDs)");
    
    console.log("\n=== Edge Cases Considered ===");
    console.log("  - Empty strings");
    console.log("  - Single character strings");
    console.log("  - Strings with punctuation and spaces");
    console.log("  - Mixed case strings");
    console.log("  - Numeric strings");
    console.log("  - Unicode characters");
}

// run test if this file is executed directly
if (require.main === module) {
    testPalindromeChecker();
}

module.exports = {
    isPalindromeTwoPointer,
    isPalindromeReverse,
    isPalindromeRecursive,
    isPalindromeStack
};
