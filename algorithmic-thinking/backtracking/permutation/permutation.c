#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
使用回溯生成排列 (C Implementation)

算法说明:
- 使用回溯生成数组的所有排列
- 使用原地交换以避免过度的内存分配
- 在每个递归级别，尝试交换每个剩余元素
- 通过交换回原位置来回溯

时间复杂度：O(n! * n) - n! 个排列，每个需要 O(n) 时间复制
空间复杂度：O(n) - 递归深度（不计算输出）

示例：
    permute([1, 2, 3]) 返回所有 6 个排列：
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
    // 基础情况：到达数组末尾
    if (index == n) {
        add_permutation(result, arr, n);
        return;
    }

    // 尝试从 index 开始的每个元素作为下一个元素
    for (int i = index; i < n; i++) {
        // 选择：交换元素
        swap(&arr[index], &arr[i]);

        // 探索：排列其余部分
        backtrack(arr, n, index + 1, result);

        // 撤销：交换回去
        swap(&arr[index], &arr[i]);
    }
}

PermutationResult* permute(int* nums, int n) {
    /*
生成 nums 数组的所有排列。

    参数:
        nums: 整数数组
        n: 数组长度

    返回:
        包含所有排列的 PermutationResult 结构体
*/
    PermutationResult* result = (PermutationResult*)malloc(sizeof(PermutationResult));
    result->capacity = 1;
    for (int i = 1; i <= n; i++) {
        result->capacity *= i;  // 容量 = n!
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
    printf("=== 排列回溯测试用例 ===\n\n");

    // 测试用例 1: [1, 2, 3]
    printf("测试 1: permute([1, 2, 3])\n");
    int test1[] = {1, 2, 3};
    PermutationResult* result1 = permute(test1, 3);
    printf("结果（共 %d 个）：\n", result1->count);
    for (int i = 0; i < result1->count; i++) {
        printf("  ");
        print_permutation(&result1->perms[i]);
        printf("\n");
    }
    free_result(result1);
    printf("\n");

    // 测试用例 2: [1, 2]
    printf("测试 2: permute([1, 2])\n");
    int test2[] = {1, 2};
    PermutationResult* result2 = permute(test2, 2);
    printf("结果（共 %d 个）：\n", result2->count);
    for (int i = 0; i < result2->count; i++) {
        printf("  ");
        print_permutation(&result2->perms[i]);
        printf("\n");
    }
    free_result(result2);
    printf("\n");

    // 测试用例 3: [1]
    printf("测试 3: permute([1])\n");
    int test3[] = {1};
    PermutationResult* result3 = permute(test3, 1);
    printf("结果（共 %d 个）：\n", result3->count);
    for (int i = 0; i < result3->count; i++) {
        printf("  ");
        print_permutation(&result3->perms[i]);
        printf("\n");
    }
    free_result(result3);
    printf("\n");

    // 测试用例 4: [10, 20, 30]
    printf("测试 4: permute([10, 20, 30])\n");
    int test4[] = {10, 20, 30};
    PermutationResult* result4 = permute(test4, 3);
    printf("结果（共 %d 个）：\n", result4->count);
    for (int i = 0; i < result4->count; i++) {
        printf("  ");
        print_permutation(&result4->perms[i]);
        printf("\n");
    }
    free_result(result4);
    printf("\n");

    // 测试用例 5: [1, 2, 3, 4]（显示前 6 个）
    printf("测试 5: permute([1, 2, 3, 4]) - 显示前 6 个\n");
    int test5[] = {1, 2, 3, 4};
    PermutationResult* result5 = permute(test5, 4);
    printf("结果（共 %d 个）：\n", result5->count);
    for (int i = 0; i < 6 && i < result5->count; i++) {
        printf("  ");
        print_permutation(&result5->perms[i]);
        printf("\n");
    }
    printf("  ... （显示 6 个，共 %d 个）\n", result5->count);
    free_result(result5);

    return 0;
}
