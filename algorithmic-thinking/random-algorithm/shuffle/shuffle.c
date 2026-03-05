#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 洗牌算法（Shuffle）- C 版本
 *
 * 使用 Fisher–Yates 洗牌算法，对整数数组进行等概率随机打乱。
 * 提供两个函数：
 * 1. shuffle_in_place：原地洗牌，直接修改数组
 * 2. shuffled_copy：生成打乱后的新数组
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1) 原地；O(n) 新数组版本
 */

// 原地洗牌：对数组 arr 进行随机打乱
void shuffle_in_place(int *arr, int n) {
    // 从最后一个元素开始，逐个与前面随机位置的元素交换
    for (int i = n - 1; i > 0; i--) {
        // 生成 [0, i] 范围的随机整数
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

// 生成打乱后的新数组，原数组不变
int *shuffled_copy(const int *arr, int n) {
    int *copy = (int *)malloc(sizeof(int) * n);
    if (!copy) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    shuffle_in_place(copy, n);
    return copy;
}

// 打印数组的小工具函数
void print_array(const int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    // 使用当前时间初始化随机数种子
    srand((unsigned int)time(NULL));

    printf("========== Shuffle (C) ==========\n");

    int original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = (int)(sizeof(original) / sizeof(original[0]));

    printf("原数组: ");
    print_array(original, n);

    int arr1[9];
    for (int i = 0; i < n; i++) {
        arr1[i] = original[i];
    }
    shuffle_in_place(arr1, n);
    printf("原地洗牌结果: ");
    print_array(arr1, n);

    int *arr2 = shuffled_copy(original, n);
    if (arr2) {
        printf("新数组洗牌结果: ");
        print_array(arr2, n);
        free(arr2);
    }

    printf("原数组保持不变: ");
    print_array(original, n);

    return 0;
}

