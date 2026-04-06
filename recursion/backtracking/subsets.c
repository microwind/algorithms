/*
 * 回溯算法 - 子集生成 (Subsets)
 * 使用递归生成数组的所有子集
 */

#include <stdio.h>
#include <stdlib.h>

// 动态数组结构
typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

// 初始化动态数组
void initArray(DynamicArray* arr, int capacity) {
    arr->data = (int*)malloc(capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = capacity;
}

// 添加元素到动态数组
void pushArray(DynamicArray* arr, int value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = value;
}

// 移除动态数组的最后一个元素
void popArray(DynamicArray* arr) {
    if (arr->size > 0) {
        arr->size--;
    }
}

// 释放动态数组
void freeArray(DynamicArray* arr) {
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
}

// 打印动态数组
void printArray(DynamicArray* arr) {
    printf("[");
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// 子集结果结构
typedef struct {
    DynamicArray* subsets;
    int count;
    int capacity;
} SubsetsResult;

// 初始化子集结果
void initSubsetsResult(SubsetsResult* result, int capacity) {
    result->subsets = (DynamicArray*)malloc(capacity * sizeof(DynamicArray));
    result->count = 0;
    result->capacity = capacity;
}

// 添加子集到结果
void addSubset(SubsetsResult* result, DynamicArray* subset) {
    if (result->count >= result->capacity) {
        result->capacity *= 2;
        result->subsets = (DynamicArray*)realloc(result->subsets, result->capacity * sizeof(DynamicArray));
    }
    
    // 复制当前子集
    initArray(&result->subsets[result->count], subset->capacity);
    for (int i = 0; i < subset->size; i++) {
        pushArray(&result->subsets[result->count], subset->data[i]);
    }
    result->count++;
}

// 释放子集结果
void freeSubsetsResult(SubsetsResult* result) {
    for (int i = 0; i < result->count; i++) {
        freeArray(&result->subsets[i]);
    }
    free(result->subsets);
    result->count = 0;
    result->capacity = 0;
}

// 回溯生成子集
void backtrack(int* nums, int numsSize, int start, DynamicArray* current, SubsetsResult* result) {
    // 每次递归都将当前子集加入结果
    addSubset(result, current);
    
    // 从start开始尝试每个元素
    for (int i = start; i < numsSize; i++) {
        // 选择元素
        pushArray(current, nums[i]);
        
        // 递归：继续处理后面的元素
        backtrack(nums, numsSize, i + 1, current, result);
        
        // 回溯：撤销选择
        popArray(current);
    }
}

// 生成数组的所有子集
SubsetsResult subsets(int* nums, int numsSize) {
    SubsetsResult result;
    initSubsetsResult(&result, 16); // 初始容量为16
    
    DynamicArray current;
    initArray(&current, numsSize);
    
    backtrack(nums, numsSize, 0, &current, &result);
    
    freeArray(&current);
    return result;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    
    SubsetsResult result = subsets(nums, numsSize);
    
    printf("数组 [");
    for (int i = 0; i < numsSize; i++) {
        printf("%d", nums[i]);
        if (i < numsSize - 1) {
            printf(", ");
        }
    }
    printf("] 的所有子集:\n");
    printf("共 %d 个子集\n\n", result.count);
    
    for (int i = 0; i < result.count; i++) {
        printf("  %d. ", i + 1);
        printArray(&result.subsets[i]);
        printf("\n");
    }
    
    printf("\n递归过程可视化:\n");
    printf("        []\n");
    printf("       / | \\\n");
    printf("     [1] [2] [3]\n");
    printf("    /  \\      |\n");
    printf("  [1,2] [1,3] [2,3]\n");
    printf("   /\n");
    printf("[1,2,3]\n");
    
    freeSubsetsResult(&result);
    
    return 0;
}
