/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 合并有序数组算法 - C实现
 * 
 * 算法原理：
 * 从两个数组的末尾开始向前合并。使用三个指针：
 * - i: 指向nums1有效元素的末尾
 * - j: 指向nums2的末尾
 * - k: 指向合并后数组的末尾
 * 
 * 每次比较nums1[i]和nums2[j]，将较大的放到nums1[k]位置。
 * 这样可以避免覆盖nums1中未处理的元素。
 * 
 * 时间复杂度：O(m+n) - m和n分别是两个数组的长度
 * 空间复杂度：O(1) - 原地合并
 */

#include <stdio.h>

/**
 * 合并两个有序数组
 * @param nums1 - 第一个数组（足够空间容纳两个数组元素）
 * @param nums1Size - nums1的大小（合并后）
 * @param m - nums1中有效元素数量
 * @param nums2 - 第二个数组
 * @param nums2Size - nums2的大小
 * @param n - nums2中元素数量
 */
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    // 从末尾开始合并
    int i = m - 1;        // nums1有效元素末尾
    int j = n - 1;        // nums2末尾
    int k = m + n - 1;    // 合并后数组末尾

    // 当两个数组都还有元素时
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }

    // 如果nums2还有剩余元素，复制到nums1前面
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
    // nums1剩余元素已经在正确位置，无需处理
}

void printArray(int* nums, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", nums[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int nums1[6] = {1, 2, 3, 0, 0, 0};
    int nums2[] = {2, 5, 6};
    int m = 3;
    int n = 3;

    printf("nums1: ");
    printArray(nums1, m);
    printf("nums2: ");
    printArray(nums2, n);

    merge(nums1, 6, m, nums2, 3, n);

    printf("合并后: ");
    printArray(nums1, m + n);

    return 0;
}

/*
 * 输出结果：
 * nums1: [1, 2, 3]
 * nums2: [2, 5, 6]
 * 合并后: [1, 2, 2, 3, 5, 6]
 */
