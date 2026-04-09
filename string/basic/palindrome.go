/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - palindrome check
 * multiple methods to check if a string is a palindrome
 */

package main

import (
	"fmt"
	"regexp"
	"strings"
	"unicode"
)

/**
 * two-pointer method to check palindrome
 * time complexity: O(n)
 * space complexity: O(1)
 */
func isPalindromeTwoPointer(s string) bool {
	left, right := 0, len(s)-1
	
	for left < right {
		// skip non-alphanumeric characters
		for left < right && !isAlphanumeric(s[left]) {
			left++
		}
		for left < right && !isAlphanumeric(s[right]) {
			right--
		}
		
		if unicode.ToLower(rune(s[left])) != unicode.ToLower(rune(s[right])) {
			return false
		}
		
		left++
		right--
	}
	
	return true
}

// helper function to check if character is alphanumeric
func isAlphanumeric(c byte) bool {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
}

/**
 * reverse string method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n)
 */
func isPalindromeReverse(s string) bool {
	// clean the string: keep only alphanumeric characters and convert to lowercase
	re := regexp.MustCompile(`[^a-zA-Z0-9]`)
	cleaned := re.ReplaceAllString(s, "")
	cleaned = strings.ToLower(cleaned)
	
	// reverse the cleaned string
	reversed := reverseString(cleaned)
	
	return cleaned == reversed
}

func reverseString(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

/**
 * recursive method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n) - due to recursion stack
 */
func isPalindromeRecursive(s string) bool {
	// clean the string first
	re := regexp.MustCompile(`[^a-zA-Z0-9]`)
	cleaned := re.ReplaceAllString(s, "")
	cleaned = strings.ToLower(cleaned)
	
	return isPalindromeRecursiveHelper(cleaned, 0, len(cleaned)-1)
}

func isPalindromeRecursiveHelper(s string, left, right int) bool {
	if left >= right {
		return true
	}
	if s[left] != s[right] {
		return false
	}
	return isPalindromeRecursiveHelper(s, left+1, right-1)
}

/**
 * stack method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n)
 */
func isPalindromeStack(s string) bool {
	// clean the string
	re := regexp.MustCompile(`[^a-zA-Z0-9]`)
	cleaned := re.ReplaceAllString(s, "")
	cleaned = strings.ToLower(cleaned)
	
	// use a stack to store characters
	stack := []rune{}
	
	// push first half of characters
	mid := len(cleaned) / 2
	for i := 0; i < mid; i++ {
		stack = append(stack, rune(cleaned[i]))
	}
	
	// compare second half with stack
	start := mid
	if len(cleaned)%2 != 0 {
		start = mid + 1
	}
	
	for i := start; i < len(cleaned); i++ {
		if len(stack) == 0 {
			return false
		}
		top := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		if top != rune(cleaned[i]) {
			return false
		}
	}
	
	return true
}

/**
 * main function - test palindrome checker
 */
func main() {
	fmt.Println(strings.Repeat("=", 60))
	fmt.Println("Palindrome Checker - Go Implementation")
	fmt.Println(strings.Repeat("=", 60))
	
	testStrings := []string{
		"racecar",
		"A man, a plan, a canal: Panama",
		"No lemon, no melon",
		"Hello, World!",
		"Madam",
		"",
		"a",
		"12321",
		"12345",
	}
	
	fmt.Println("\n=== Test Results ===")
	for _, test := range testStrings {
		fmt.Printf("String: \"%s\"\n", test)
		fmt.Printf("  Two-pointer: %t\n", isPalindromeTwoPointer(test))
		fmt.Printf("  Reverse: %t\n", isPalindromeReverse(test))
		fmt.Printf("  Recursive: %t\n", isPalindromeRecursive(test))
		fmt.Printf("  Stack: %t\n", isPalindromeStack(test))
		fmt.Println()
	}
	
	fmt.Println("=== Algorithm Characteristics ===")
	fmt.Println("Two-pointer method:")
	fmt.Println("  - Most efficient: O(n) time, O(1) space")
	fmt.Println("  - Works in-place, no extra memory needed")
	fmt.Println("  - Best for large strings")
	
	fmt.Println("\nReverse method:")
	fmt.Println("  - Simple and intuitive: O(n) time, O(n) space")
	fmt.Println("  - Creates new reversed string")
	fmt.Println("  - Good for readability")
	
	fmt.Println("\nRecursive method:")
	fmt.Println("  - Elegant solution: O(n) time, O(n) space")
	fmt.Println("  - Uses recursion stack")
	fmt.Println("  - May cause stack overflow for very long strings")
	
	fmt.Println("\nStack method:")
	fmt.Println("  - Uses explicit stack: O(n) time, O(n) space")
	fmt.Println("  - Compares first half with second half")
	fmt.Println("  - Good for understanding stack operations")
	
	fmt.Println("\n=== Common Applications ===")
	fmt.Println("Palindrome checking is used in:")
	fmt.Println("  - String validation and verification")
	fmt.Println("  - Cryptographic algorithms")
	fmt.Println("  - DNA sequence analysis")
	fmt.Println("  - Text processing and parsing")
	fmt.Println("  - Puzzle solving and games")
	fmt.Println("  - Data validation (credit cards, IDs)")
	
	fmt.Println("\n=== Edge Cases Considered ===")
	fmt.Println("  - Empty strings")
	fmt.Println("  - Single character strings")
	fmt.Println("  - Strings with punctuation and spaces")
	fmt.Println("  - Mixed case strings")
	fmt.Println("  - Numeric strings")
	fmt.Println("  - Unicode characters")
}
