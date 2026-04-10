/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 最大子数组和算法（Kadane算法） - C实现
 * 
 * 算法原理：
 * Kadane算法是一种动态规划方法。对于每个位置，我们决定：
 * 1. 将当前元素加入之前的子数组
 * 2. 从当前元素开始一个新的子数组
 * 取两者中的较大值作为当前最大子数组和。
 * 
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(1) - 仅使用常数额外空间
 */

#include <stdio.h>
#include <limits.h>

/**
 * 最大子数组和（Kadane算法）
 * @param nums - 输入数组
 * @param numsSize - 数组大小
 * @return 最大子数组和
 */
int maxSubArray(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int max_sum = nums[0];      // 全局最大和
    int current_sum = nums[0]; // 当前子数组和

    for (int i = 1; i < numsSize; i++) {
        // 决定是将当前元素加入之前的子数组，还是从当前元素开始新子数组
        current_sum = (current_sum + nums[i] > nums[i]) ? 
                       (current_sum + nums[i]) : nums[i];
        
        // 更新全局最大和
        max_sum = (current_sum > max_sum) ? current_sum : max_sum;
    }

    return max_sum;
}

/**
 * 扩展版本：同时返回子数组的起止索引
 */
typedef struct {
    int max_sum;
    int start;
    int end;
} Result;

Result maxSubArrayWithIndices(int* nums, int numsSize) {
    Result res = {INT_MIN, 0, 0};
    if (numsSize == 0) return res;

    int current_sum = nums[0];
    int current_start = 0;
    res.max_sum = nums[0];
    res.start = 0;
    res.end = 0;

    for (int i = 1; i < numsSize; i++) {
        if (current_sum + nums[i] < nums[i]) {
            // 从当前元素开始新子数组
            current_sum = nums[i];
            current_start = i;
        } else {
            // 将当前元素加入之前的子数组
            current_sum += nums[i];
        }

        // 更新全局最大和及索引
        if (current_sum > res.max_sum) {
            res.max_sum = current_sum;
            res.start = current_start;
            res.end = i;
        }
    }

    return res;
}

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    printf("输入数组: ");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    int result = maxSubArray(nums, numsSize);
    printf("最大子数组和: %d\n", result);

    Result res = maxSubArrayWithIndices(nums, numsSize);
    printf("子数组范围: 索引[%d, %d]\n", res.start, res.end);
    printf("子数组元素: ");
    for (int i = res.start; i <= res.end; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}

/*
 * 输出结果：
 * 输入数组: -2 1 -3 4 -1 2 1 -5 4
 * 最大子数组和: 6
 * 子数组范围: 索引[3, 6]
 * 子数组元素: 4 -1 2 1
 */
