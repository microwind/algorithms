#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Maximize Number - Remove k digits to get maximum value
 *
 * Algorithm:
 * - Given a digit string and k, remove k digits to maximize the resulting number
 * - Use a greedy stack-based approach:
 *   1. Iterate through digits
 *   2. If current digit is greater than the top of stack, pop smaller digits
 *   3. Add current digit to stack
 *   4. If we still need to delete digits, remove from the end
 *
 * Time Complexity: O(n) - each digit is pushed/popped at most once
 * Space Complexity: O(n) - for the stack
*/

/*
* Remove k digits from the string to get maximum resulting number
 *
 * 参数:
 *   num_str: String of digits
 *   k: Number of digits to remove
 *   result: Buffer to store the result
 *   result_size: Size of result buffer
 *
 * 返回:
 *   Length of the result string
*/
int remove_k_digits(const char *num_str, int k, char *result, int result_size) {
    int n = strlen(num_str);

    if (k >= n) {
        result[0] = '0';
        result[1] = '\0';
        return 1;
    }

    if (k == 0) {
        strncpy(result, num_str, result_size - 1);
        result[result_size - 1] = '\0';
        return n;
    }

    /*
Stack-based greedy approach
*/
    char *stack = (char *)malloc(n + 1);
    int top = 0;
    int to_delete = k;

    for (int i = 0; i < n; i++) {
        char digit = num_str[i];
        /*
Remove smaller digits from stack when we encounter a larger digit
*/
        while (to_delete > 0 && top > 0 && stack[top - 1] < digit) {
            top--;
            to_delete--;
        }
        stack[top] = digit;
        top++;
    }

    /*
If we still have digits to delete, remove from the end
*/
    if (to_delete > 0) {
        top -= to_delete;
    }

    stack[top] = '\0';

    /*
Handle leading zeros
*/
    int start = 0;
    while (start < top && stack[start] == '0') {
        start++;
    }

    if (start == top) {
        result[0] = '0';
        result[1] = '\0';
        free(stack);
        return 1;
    }

    int len = top - start;
    strncpy(result, stack + start, len);
    result[len] = '\0';
    free(stack);

    return len;
}

void test_standard_example() {
    printf("\n[Test 1] Standard example from problem\n");

    char num_str[] = "1432219";
    int k = 3;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '4321'\n");
}

void test_leading_zeros() {
    printf("\n[Test 2] Remove leading zeros\n");

    char num_str[] = "10200";
    int k = 1;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '200'\n");
}

void test_same_digits() {
    printf("\n[Test 3] All same digits\n");

    char num_str[] = "1111";
    int k = 2;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '11'\n");
}

void test_descending_order() {
    printf("\n[Test 4] Descending digits - remove from end\n");

    char num_str[] = "54321";
    int k = 2;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '321'\n");
}

void test_ascending_order() {
    printf("\n[Test 5] Ascending digits - remove from front\n");

    char num_str[] = "12345";
    int k = 2;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '345'\n");
}

void test_remove_all() {
    printf("\n[Test 6] Remove all digits\n");

    char num_str[] = "123";
    int k = 3;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '0'\n");
}

void test_remove_zero() {
    printf("\n[Test 7] Remove zero digits\n");

    char num_str[] = "1234";
    int k = 0;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '1234'\n");
}

void test_multiple_zeros() {
    printf("\n[Test 8] Multiple zeros in middle\n");

    char num_str[] = "100200";
    int k = 2;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
}

void test_mixed() {
    printf("\n[Test 9] Mixed digits\n");

    char num_str[] = "112";
    int k = 1;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
    printf("Expected: '12'\n");
}

void test_large_number() {
    printf("\n[Test 10] Large number\n");

    char num_str[] = "987654321";
    int k = 4;
    char result[100];

    remove_k_digits(num_str, k, result, sizeof(result));

    printf("Input: '%s', k=%d\n", num_str, k);
    printf("Output: '%s'\n", result);
}

int main() {
    printf("==================================================\n");
    printf("MAXIMIZE NUMBER - Remove k Digits (C)\n");
    printf("==================================================\n");

    test_standard_example();
    test_leading_zeros();
    test_same_digits();
    test_descending_order();
    test_ascending_order();
    test_remove_all();
    test_remove_zero();
    test_multiple_zeros();
    test_mixed();
    test_large_number();

    return 0;
}
