#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Combination Generator using Backtracking (C Implementation)

Algorithm Explanation:
- Generate all combinations of k elements from 1 to n (C(n,k))
- Use backtracking to systematically explore all choices
- At each step, only consider elements >= current position
- This prevents duplicate combinations
- When we've selected k elements, add to result

Time Complexity: O(C(n,k) * k) where C(n,k) is the number of combinations
Space Complexity: O(k) for recursion depth and current combination

Example:
    combine(4, 2) returns [
        [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
    ]
*/

typedef struct {
    int* data;
    int size;
} Combination;

typedef struct {
    Combination* combos;
    int count;
    int capacity;
} CombinationResult;

void add_combination(CombinationResult* result, int* arr, int k) {
    if (result->count >= result->capacity) {
        result->capacity *= 2;
        result->combos = (Combination*)realloc(result->combos,
                                                result->capacity * sizeof(Combination));
    }

    result->combos[result->count].data = (int*)malloc(k * sizeof(int));
    memcpy(result->combos[result->count].data, arr, k * sizeof(int));
    result->combos[result->count].size = k;
    result->count++;
}

void backtrack(int n, int k, int start, int* current, int current_len,
               CombinationResult* result) {
    // Base case: combination is complete
    if (current_len == k) {
        add_combination(result, current, k);
        return;
    }

    // Try each number from start to n
    for (int num = start; num <= n; num++) {
        // Choose: add num to current combination
        current[current_len] = num;

        // Explore: build rest of combination
        // Only numbers >= num+1 to avoid duplicates
        backtrack(n, k, num + 1, current, current_len + 1, result);

        // Unchoose: (implicitly, by overwriting in next iteration)
    }
}

CombinationResult* combine(int n, int k) {
    /*
    Generate all combinations of k elements from 1 to n.

    Args:
        n: Total number of elements (1 to n)
        k: Size of each combination

    Returns:
        CombinationResult struct containing all combinations
    */
    CombinationResult* result = (CombinationResult*)malloc(sizeof(CombinationResult));
    result->capacity = 1000;
    result->combos = (Combination*)malloc(result->capacity * sizeof(Combination));
    result->count = 0;

    int* current = (int*)malloc(k * sizeof(int));
    backtrack(n, k, 1, current, 0, result);
    free(current);

    return result;
}

void free_result(CombinationResult* result) {
    for (int i = 0; i < result->count; i++) {
        free(result->combos[i].data);
    }
    free(result->combos);
    free(result);
}

void print_combination(Combination* combo) {
    printf("[");
    for (int i = 0; i < combo->size; i++) {
        printf("%d", combo->data[i]);
        if (i < combo->size - 1) printf(", ");
    }
    printf("]");
}

int main() {
    printf("=== Combination Backtracking Test Cases ===\n\n");

    // Test Case 1: combine(4, 2)
    printf("Test 1: combine(4, 2)\n");
    CombinationResult* result1 = combine(4, 2);
    printf("Result (count=%d):\n", result1->count);
    for (int i = 0; i < result1->count; i++) {
        printf("  ");
        print_combination(&result1->combos[i]);
        printf("\n");
    }
    free_result(result1);
    printf("\n");

    // Test Case 2: combine(3, 1)
    printf("Test 2: combine(3, 1)\n");
    CombinationResult* result2 = combine(3, 1);
    printf("Result (count=%d):\n", result2->count);
    for (int i = 0; i < result2->count; i++) {
        printf("  ");
        print_combination(&result2->combos[i]);
        printf("\n");
    }
    free_result(result2);
    printf("\n");

    // Test Case 3: combine(3, 3)
    printf("Test 3: combine(3, 3)\n");
    CombinationResult* result3 = combine(3, 3);
    printf("Result (count=%d):\n", result3->count);
    for (int i = 0; i < result3->count; i++) {
        printf("  ");
        print_combination(&result3->combos[i]);
        printf("\n");
    }
    free_result(result3);
    printf("\n");

    // Test Case 4: combine(5, 3)
    printf("Test 4: combine(5, 3)\n");
    CombinationResult* result4 = combine(5, 3);
    printf("Result (count=%d):\n", result4->count);
    for (int i = 0; i < result4->count; i++) {
        printf("  ");
        print_combination(&result4->combos[i]);
        printf("\n");
    }
    free_result(result4);
    printf("\n");

    // Test Case 5: combine(6, 2)
    printf("Test 5: combine(6, 2)\n");
    CombinationResult* result5 = combine(6, 2);
    printf("Result (count=%d):\n", result5->count);
    for (int i = 0; i < result5->count; i++) {
        printf("  ");
        print_combination(&result5->combos[i]);
        printf("\n");
    }
    free_result(result5);

    return 0;
}
