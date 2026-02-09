#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Permutation Generator using Backtracking (C Implementation)

Algorithm Explanation:
- Generate all permutations of an array using backtracking
- Use in-place swapping to avoid excessive memory allocation
- At each recursion level, try swapping each remaining element
- Backtrack by swapping back to original position

Time Complexity: O(n! * n) - n! permutations, each taking O(n) to copy
Space Complexity: O(n) - recursion depth (not counting output)

Example:
    permute([1, 2, 3]) returns all 6 permutations:
    [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]
*/

typedef struct {
    int* data;
    int size;
} Permutation;

typedef struct {
    Permutation* perms;
    int count;
    int capacity;
} PermutationResult;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void add_permutation(PermutationResult* result, int* arr, int n) {
    if (result->count >= result->capacity) {
        result->capacity *= 2;
        result->perms = (Permutation*)realloc(result->perms,
                                               result->capacity * sizeof(Permutation));
    }

    result->perms[result->count].data = (int*)malloc(n * sizeof(int));
    memcpy(result->perms[result->count].data, arr, n * sizeof(int));
    result->perms[result->count].size = n;
    result->count++;
}

void backtrack(int* arr, int n, int index, PermutationResult* result) {
    // Base case: reached end of array
    if (index == n) {
        add_permutation(result, arr, n);
        return;
    }

    // Try each element from index onwards as the next element
    for (int i = index; i < n; i++) {
        // Choose: swap elements
        swap(&arr[index], &arr[i]);

        // Explore: permute the rest
        backtrack(arr, n, index + 1, result);

        // Unchoose: swap back
        swap(&arr[index], &arr[i]);
    }
}

PermutationResult* permute(int* nums, int n) {
    /*
    Generate all permutations of nums array.

    Args:
        nums: Array of integers
        n: Length of array

    Returns:
        PermutationResult struct containing all permutations
    */
    PermutationResult* result = (PermutationResult*)malloc(sizeof(PermutationResult));
    result->capacity = 1;
    for (int i = 1; i <= n; i++) {
        result->capacity *= i;  // capacity = n!
    }
    result->perms = (Permutation*)malloc(result->capacity * sizeof(Permutation));
    result->count = 0;

    int* arr = (int*)malloc(n * sizeof(int));
    memcpy(arr, nums, n * sizeof(int));

    backtrack(arr, n, 0, result);

    free(arr);
    return result;
}

void free_result(PermutationResult* result) {
    for (int i = 0; i < result->count; i++) {
        free(result->perms[i].data);
    }
    free(result->perms);
    free(result);
}

void print_permutation(Permutation* perm) {
    printf("[");
    for (int i = 0; i < perm->size; i++) {
        printf("%d", perm->data[i]);
        if (i < perm->size - 1) printf(", ");
    }
    printf("]");
}

int main() {
    printf("=== Permutation Backtracking Test Cases ===\n\n");

    // Test Case 1: [1, 2, 3]
    printf("Test 1: permute([1, 2, 3])\n");
    int test1[] = {1, 2, 3};
    PermutationResult* result1 = permute(test1, 3);
    printf("Result (count=%d):\n", result1->count);
    for (int i = 0; i < result1->count; i++) {
        printf("  ");
        print_permutation(&result1->perms[i]);
        printf("\n");
    }
    free_result(result1);
    printf("\n");

    // Test Case 2: [1, 2]
    printf("Test 2: permute([1, 2])\n");
    int test2[] = {1, 2};
    PermutationResult* result2 = permute(test2, 2);
    printf("Result (count=%d):\n", result2->count);
    for (int i = 0; i < result2->count; i++) {
        printf("  ");
        print_permutation(&result2->perms[i]);
        printf("\n");
    }
    free_result(result2);
    printf("\n");

    // Test Case 3: [1]
    printf("Test 3: permute([1])\n");
    int test3[] = {1};
    PermutationResult* result3 = permute(test3, 1);
    printf("Result (count=%d):\n", result3->count);
    for (int i = 0; i < result3->count; i++) {
        printf("  ");
        print_permutation(&result3->perms[i]);
        printf("\n");
    }
    free_result(result3);
    printf("\n");

    // Test Case 4: [10, 20, 30]
    printf("Test 4: permute([10, 20, 30])\n");
    int test4[] = {10, 20, 30};
    PermutationResult* result4 = permute(test4, 3);
    printf("Result (count=%d):\n", result4->count);
    for (int i = 0; i < result4->count; i++) {
        printf("  ");
        print_permutation(&result4->perms[i]);
        printf("\n");
    }
    free_result(result4);
    printf("\n");

    // Test Case 5: [1, 2, 3, 4] (first 6 of 24)
    printf("Test 5: permute([1, 2, 3, 4]) - showing first 6\n");
    int test5[] = {1, 2, 3, 4};
    PermutationResult* result5 = permute(test5, 4);
    printf("Result (count=%d):\n", result5->count);
    for (int i = 0; i < 6 && i < result5->count; i++) {
        printf("  ");
        print_permutation(&result5->perms[i]);
        printf("\n");
    }
    printf("  ... (showing 6 of %d total)\n", result5->count);
    free_result(result5);

    return 0;
}
