/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  string algorithms - palindrome check
 * multiple methods to check if a string is a palindrome
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * two-pointer method to check palindrome
 * time complexity: O(n)
 * space complexity: O(1)
 */
bool is_palindrome_two_pointer(const char *s) {
    int left = 0;
    int right = strlen(s) - 1;
    
    while (left < right) {
        // skip non-alphanumeric characters
        while (left < right && !isalnum(s[left])) {
            left++;
        }
        while (left < right && !isalnum(s[right])) {
            right--;
        }
        
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

/**
 * reverse string method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n)
 */
bool is_palindrome_reverse(const char *s) {
    int len = strlen(s);
    char *cleaned = malloc(len + 1);
    int clean_index = 0;
    
    // clean the string: keep only alphanumeric characters and convert to lowercase
    for (int i = 0; i < len; i++) {
        if (isalnum(s[i])) {
            cleaned[clean_index++] = tolower(s[i]);
        }
    }
    cleaned[clean_index] = '\0';
    
    // reverse the cleaned string
    char *reversed = malloc(clean_index + 1);
    for (int i = 0; i < clean_index; i++) {
        reversed[i] = cleaned[clean_index - 1 - i];
    }
    reversed[clean_index] = '\0';
    
    // compare cleaned with reversed
    bool result = strcmp(cleaned, reversed) == 0;
    
    free(cleaned);
    free(reversed);
    
    return result;
}

/**
 * recursive method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n) - due to recursion stack
 */
bool is_palindrome_recursive_helper(const char *s, int left, int right) {
    if (left >= right) {
        return true;
    }
    if (s[left] != s[right]) {
        return false;
    }
    return is_palindrome_recursive_helper(s, left + 1, right - 1);
}

bool is_palindrome_recursive(const char *s) {
    int len = strlen(s);
    char *cleaned = malloc(len + 1);
    int clean_index = 0;
    
    // clean the string
    for (int i = 0; i < len; i++) {
        if (isalnum(s[i])) {
            cleaned[clean_index++] = tolower(s[i]);
        }
    }
    cleaned[clean_index] = '\0';
    
    bool result = is_palindrome_recursive_helper(cleaned, 0, clean_index - 1);
    free(cleaned);
    
    return result;
}

/**
 * stack method to check palindrome
 * time complexity: O(n)
 * space complexity: O(n)
 */
typedef struct Stack {
    char *data;
    int top;
    int capacity;
} Stack;

Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, char c) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = c;
    }
}

char pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

void free_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}

bool is_palindrome_stack(const char *s) {
    int len = strlen(s);
    char *cleaned = malloc(len + 1);
    int clean_index = 0;
    
    // clean the string
    for (int i = 0; i < len; i++) {
        if (isalnum(s[i])) {
            cleaned[clean_index++] = tolower(s[i]);
        }
    }
    cleaned[clean_index] = '\0';
    
    // use stack to store first half
    Stack *stack = create_stack(clean_index);
    int mid = clean_index / 2;
    
    for (int i = 0; i < mid; i++) {
        push(stack, cleaned[i]);
    }
    
    // compare second half with stack
    int start = clean_index % 2 == 0 ? mid : mid + 1;
    bool result = true;
    
    for (int i = start; i < clean_index; i++) {
        if (pop(stack) != cleaned[i]) {
            result = false;
            break;
        }
    }
    
    free(cleaned);
    free_stack(stack);
    
    return result;
}

/**
 * main function - test palindrome checker
 */
int main() {
    printf("============================================================\n");
    printf("Palindrome Checker - C Implementation\n");
    printf("============================================================\n");
    
    const char *test_strings[] = {
        "racecar",
        "A man, a plan, a canal: Panama",
        "No lemon, no melon",
        "Hello, World!",
        "Madam",
        "",
        "a",
        "12321",
        "12345"
    };
    
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    printf("\n=== Test Results ===\n");
    for (int i = 0; i < num_tests; i++) {
        printf("String: \"%s\"\n", test_strings[i]);
        printf("  Two-pointer: %s\n", is_palindrome_two_pointer(test_strings[i]) ? "true" : "false");
        printf("  Reverse: %s\n", is_palindrome_reverse(test_strings[i]) ? "true" : "false");
        printf("  Recursive: %s\n", is_palindrome_recursive(test_strings[i]) ? "true" : "false");
        printf("  Stack: %s\n", is_palindrome_stack(test_strings[i]) ? "true" : "false");
        printf("\n");
    }
    
    printf("=== Algorithm Characteristics ===\n");
    printf("Two-pointer method:\n");
    printf("  - Most efficient: O(n) time, O(1) space\n");
    printf("  - Works in-place, no extra memory needed\n");
    printf("  - Best for large strings\n");
    
    printf("\nReverse method:\n");
    printf("  - Simple and intuitive: O(n) time, O(n) space\n");
    printf("  - Creates new reversed string\n");
    printf("  - Good for readability\n");
    
    printf("\nRecursive method:\n");
    printf("  - Elegant solution: O(n) time, O(n) space\n");
    printf("  - Uses recursion stack\n");
    printf("  - May cause stack overflow for very long strings\n");
    
    printf("\nStack method:\n");
    printf("  - Uses explicit stack: O(n) time, O(n) space\n");
    printf("  - Compares first half with second half\n");
    printf("  - Good for understanding stack operations\n");
    
    printf("\n=== Common Applications ===\n");
    printf("Palindrome checking is used in:\n");
    printf("  - String validation and verification\n");
    printf("  - Cryptographic algorithms\n");
    printf("  - DNA sequence analysis\n");
    printf("  - Text processing and parsing\n");
    printf("  - Puzzle solving and games\n");
    printf("  - Data validation (credit cards, IDs)\n");
    
    printf("\n=== Edge Cases Considered ===\n");
    printf("  - Empty strings\n");
    printf("  - Single character strings\n");
    printf("  - Strings with punctuation and spaces\n");
    printf("  - Mixed case strings\n");
    printf("  - Numeric strings\n");
    printf("  - Unicode characters\n");
    
    return 0;
}
