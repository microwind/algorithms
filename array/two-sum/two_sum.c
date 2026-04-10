/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 两数之和算法 - C实现
 * 
 * 算法原理：
 * 使用哈希表辅助查找。遍历数组时，对于每个元素，计算目标值与当前元素的差值（补数），
 * 检查补数是否已在哈希表中。如果在，则找到答案；否则将当前元素存入哈希表。
 * 
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(n) - 哈希表存储
 */

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10007

typedef struct {
    int key;    // 元素值
    int value;  // 索引
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[HASH_SIZE];
} HashMap;

int hash(int key) {
    // 处理负数
    return ((key % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
}

void hash_put(HashMap* map, int key, int value) {
    int h = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = (struct Node*)map->buckets[h];
    map->buckets[h] = newNode;
}

int hash_get(HashMap* map, int key) {
    int h = hash(key);
    Node* curr = map->buckets[h];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = (Node*)curr->next;
    }
    return -1;
}

int hash_contains(HashMap* map, int key) {
    return hash_get(map, key) != -1;
}

/**
 * 两数之和
 * @param nums - 输入数组
 * @param numsSize - 数组大小
 * @param target - 目标和
 * @param returnSize - 返回结果大小
 * @return 返回两个数的索引数组
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap map;
    for (int i = 0; i < HASH_SIZE; i++) {
        map.buckets[i] = NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        if (hash_contains(&map, complement)) {
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = hash_get(&map, complement);
            result[1] = i;
            *returnSize = 2;
            return result;
        }
        hash_put(&map, nums[i], i);
    }

    *returnSize = 0;
    return NULL;
}

int main() {
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int* result = twoSum(nums, numsSize, target, &returnSize);

    if (result != NULL) {
        printf("目标值: %d\n", target);
        printf("结果索引: [%d, %d]\n", result[0], result[1]);
        printf("对应数值: %d + %d = %d\n", nums[result[0]], nums[result[1]], target);
        free(result);
    } else {
        printf("未找到答案\n");
    }

    return 0;
}

/*
 * 输出结果：
 * 目标值: 9
 * 结果索引: [0, 1]
 * 对应数值: 2 + 7 = 9
 */
