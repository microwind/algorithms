/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 两数之和算法 - JavaScript实现
 * 
 * 算法原理：
 * 使用哈希表辅助查找。遍历数组时，对于每个元素，计算目标值与当前元素的差值（补数），
 * 检查补数是否已在哈希表中。如果在，则找到答案；否则将当前元素存入哈希表。
 * 
 * 时间复杂度：O(n) - 只需遍历数组一次
 * 空间复杂度：O(n) - 哈希表存储
 */

/**
 * 两数之和
 * 使用哈希表查找补数
 * @param {number[]} nums - 输入数组
 * @param {number} target - 目标和
 * @returns {number[]} 两个数的索引数组
 */
function twoSum(nums, target) {
    const seen = new Map(); // 哈希表，存储元素值到索引的映射

    for (let i = 0; i < nums.length; i++) {
        const need = target - nums[i]; // 计算补数
        // 检查补数是否已在哈希表中
        if (seen.has(need)) {
            return [seen.get(need), i]; // 找到答案，返回两个索引
        }
        seen.set(nums[i], i); // 将当前元素存入哈希表
    }

    return []; // 未找到答案
}

// 测试代码
const nums = [2, 7, 11, 15];
const target = 9;

const result = twoSum(nums, target);

if (result.length > 0) {
    console.log(`目标值: ${target}`);
    console.log(`结果索引: [${result[0]}, ${result[1]}]`);
    console.log(`对应数值: ${nums[result[0]]} + ${nums[result[1]]} = ${target}`);
} else {
    console.log("未找到答案");
}

/*
 * 输出结果：
 * 目标值: 9
 * 结果索引: [0, 1]
 * 对应数值: 2 + 7 = 9
 */
