#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
使用回溯生成组合 (C Implementation)

算法说明:
- 生成从1到n中选取k个元素的所有组合 (C(n,k))
- 使用回溯系统地探索所有选择
- At each step, only consider elements >= current position
- This prevents duplicate combinations
- When we've selected k elements, add to result

时间复杂度：O(C(n,k) * k)，其中C(n,k)是组合数
空间复杂度：O(k)，用于递归深度和当前组合

示例:
    combine(4, 2) 返回 [
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
    // 基本情况：组合已完成
    if (current_len == k) {
        add_combination(result, current, k);
        return;
    }

    // 尝试从start到n的每个数字
    for (int num = start; num <= n; num++) {
        // 选择：将num添加到当前组合
        current[current_len] = num;

        // 探索：构建组合的其余部分
        // 仅数字 >= num+1 以避免重复
        backtrack(n, k, num + 1, current, current_len + 1, result);

        // Unchoose: (implicitly, by overwriting in next iteration)
    }
}

CombinationResult* combine(int n, int k) {
    /*
生成从1到n中选取k个元素的所有组合.

    参数:
        n: 元素的总数（1到n）
        k: 每个组合的大小

    返回:
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

    // 测试用例 1: combine(4, 2)
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

    // 测试用例 2: combine(3, 1)
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

    // 测试用例 3: combine(3, 3)
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

    // 测试用例 4: combine(5, 3)
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

    // 测试用例 5: combine(6, 2)
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
