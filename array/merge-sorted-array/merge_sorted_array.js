/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 合并有序数组算法 - JavaScript实现
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

/**
 * 合并两个有序数组
 * @param {number[]} nums1 - 第一个数组（足够空间容纳两个数组元素）
 * @param {number} m - nums1中有效元素数量
 * @param {number[]} nums2 - 第二个数组
 * @param {number} n - nums2中元素数量
 * @returns {number[]} 合并后的数组
 */
function mergeSortedArray(nums1, m, nums2, n) {
    // 从末尾开始合并
    let i = m - 1;        // nums1有效元素末尾
    let j = n - 1;        // nums2末尾
    let k = m + n - 1;    // 合并后数组末尾

    // 当nums2还有元素时
    while (j >= 0) {
        // 如果nums1还有元素且nums1[i]大于nums2[j]
        if (i >= 0 && nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    // nums1剩余元素已经在正确位置，无需处理

    return nums1;
}

/**
 * 打印数组
 * @param {number[]} nums - 要打印的数组
 * @param {number} size - 要打印的元素数量
 */
function printArray(nums, size) {
    process.stdout.write("[");
    for (let i = 0; i < size; i++) {
        process.stdout.write(nums[i].toString());
        if (i < size - 1) {
            process.stdout.write(", ");
        }
    }
    console.log("]");
}

// 测试代码
const nums1 = [1, 2, 3, 0, 0, 0];
const nums2 = [2, 5, 6];
const m = 3;
const n = 3;

console.log("nums1: ");
printArray(nums1, m);
console.log("nums2: ");
printArray(nums2, n);

mergeSortedArray(nums1, m, nums2, n);

console.log("合并后: ");
printArray(nums1, m + n);

/*
 * 输出结果：
 * nums1: [1, 2, 3]
 * nums2: [2, 5, 6]
 * 合并后: [1, 2, 2, 3, 5, 6]
 */
