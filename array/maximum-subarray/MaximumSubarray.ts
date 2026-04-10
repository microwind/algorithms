/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 最大子数组和算法（Kadane算法） - TypeScript实现
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

/**
 * 最大子数组和（Kadane算法）
 * @param nums - 输入数组
 * @returns 最大子数组和
 */
function maxSubArray(nums: number[]): number {
    if (nums.length === 0) return 0;

    let maxSum = nums[0];       // 全局最大和
    let currentSum = nums[0];   // 当前子数组和

    for (let i = 1; i < nums.length; i++) {
        // 决定是将当前元素加入之前的子数组，还是从当前元素开始新子数组
        currentSum = Math.max(currentSum + nums[i], nums[i]);
        
        // 更新全局最大和
        maxSum = Math.max(maxSum, currentSum);
    }

    return maxSum;
}

/**
 * 扩展版本：同时返回子数组的起止索引
 */
interface Result {
    maxSum: number;
    start: number;
    end: number;
}

function maxSubArrayWithIndices(nums: number[]): Result {
    if (nums.length === 0) {
        return { maxSum: 0, start: 0, end: 0 };
    }

    let maxSum = nums[0];
    let currentSum = nums[0];
    let currentStart = 0;
    let start = 0;
    let end = 0;

    for (let i = 1; i < nums.length; i++) {
        if (currentSum + nums[i] < nums[i]) {
            // 从当前元素开始新子数组
            currentSum = nums[i];
            currentStart = i;
        } else {
            // 将当前元素加入之前的子数组
            currentSum += nums[i];
        }

        // 更新全局最大和及索引
        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = currentStart;
            end = i;
        }
    }

    return { maxSum, start, end };
}

/**
 * 主函数 - 测试最大子数组和
 */
function main(): void {
    const nums: number[] = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
    console.log("输入数组:", nums);

    const result = maxSubArray(nums);
    console.log("最大子数组和:", result);

    const res = maxSubArrayWithIndices(nums);
    console.log("子数组范围: 索引[", res.start, ",", res.end, "]");
    console.log("子数组元素:", nums.slice(res.start, res.end + 1));
}

// 执行主函数
main();

/**
 * 输出结果：
 * 输入数组: [ -2, 1, -3, 4, -1, 2, 1, -5, 4 ]
 * 最大子数组和: 6
 * 子数组范围: 索引[ 3, 6 ]
 * 子数组元素: [ 4, -1, 2, 1 ]
 */

export { maxSubArray, maxSubArrayWithIndices };
