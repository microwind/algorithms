/*
 * 回溯算法 - 全排列 (Permutations)
 * 使用递归生成数组的所有排列
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// 排列结果结构
typedef struct {
    DynamicArray* permutations;
    int count;
    int capacity;
} PermutationsResult;

// 初始化排列结果
void initPermutationsResult(PermutationsResult* result, int capacity) {
    result->permutations = (DynamicArray*)malloc(capacity * sizeof(DynamicArray));
    result->count = 0;
    result->capacity = capacity;
}

// 添加排列到结果
void addPermutation(PermutationsResult* result, DynamicArray* permutation) {
    if (result->count >= result->capacity) {
        result->capacity *= 2;
        result->permutations = (DynamicArray*)realloc(result->permutations, result->capacity * sizeof(DynamicArray));
    }
    
    // 复制当前排列
    initArray(&result->permutations[result->count], permutation->capacity);
    for (int i = 0; i < permutation->size; i++) {
        pushArray(&result->permutations[result->count], permutation->data[i]);
    }
    result->count++;
}

// 释放排列结果
void freePermutationsResult(PermutationsResult* result) {
    for (int i = 0; i < result->count; i++) {
        freeArray(&result->permutations[i]);
    }
    free(result->permutations);
    result->count = 0;
    result->capacity = 0;
}

// 检查元素是否在数组中
bool contains(DynamicArray* arr, int value) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return true;
        }
    }
    return false;
}

// 回溯生成排列
void backtrack(int* nums, int numsSize, DynamicArray* current, PermutationsResult* result) {
    // 基础情况：当前排列长度等于输入数组长度
    if (current->size == numsSize) {
        addPermutation(result, current);
        return;
    }
    
    // 递归情况：尝试每个元素
    for (int i = 0; i < numsSize; i++) {
        // 如果元素已经在当前排列中，跳过
        if (contains(current, nums[i])) {
            continue;
        }
        
        // 选择元素
        pushArray(current, nums[i]);
        
        // 递归：继续处理
        backtrack(nums, numsSize, current, result);
        
        // 回溯：撤销选择
        popArray(current);
    }
}

// 生成数组的所有排列
PermutationsResult permutations(int* nums, int numsSize) {
    PermutationsResult result;
    initPermutationsResult(&result, 16); // 初始容量为16
    
    DynamicArray current;
    initArray(&current, numsSize);
    
    backtrack(nums, numsSize, &current, &result);
    
    freeArray(&current);
    return result;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    
    PermutationsResult result = permutations(nums, numsSize);
    
    printf("数组 [");
    for (int i = 0; i < numsSize; i++) {
        printf("%d", nums[i]);
        if (i < numsSize - 1) {
            printf(", ");
        }
    }
    printf("] 的所有排列:\n");
    
    for (int i = 0; i < result.count; i++) {
        printf("  %d. ", i + 1);
        printArray(&result.permutations[i]);
        printf("\n");
    }
    
    printf("\n共 %d 种排列\n", result.count);
    
    freePermutationsResult(&result);
    
    return 0;
}
