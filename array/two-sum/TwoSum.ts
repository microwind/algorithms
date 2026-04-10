/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 两数之和算法 - TypeScript实现
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
 * @param nums - 输入数组
 * @param target - 目标和
 * @returns 返回两个数的索引数组，未找到返回空数组
 */
function twoSum(nums: number[], target: number): number[] {
    // 使用Map存储已遍历的元素及其索引
    const map: Map<number, number> = new Map();

    for (let i = 0; i < nums.length; i++) {
        // 计算补数
        const complement = target - nums[i];

        // 检查补数是否已在哈希表中
        if (map.has(complement)) {
            // 找到答案，返回两个索引
            return [map.get(complement)!, i];
        }

        // 将当前元素及其索引存入哈希表
        map.set(nums[i], i);
    }

    // 未找到答案
    return [];
}

/**
 * 主函数 - 测试两数之和
 */
function main(): void {
    const nums: number[] = [2, 7, 11, 15];
    const target: number = 9;

    const result: number[] = twoSum(nums, target);

    if (result.length > 0) {
        console.log("目标值:", target);
        console.log("结果索引:", result);
        console.log("对应数值:", `${nums[result[0]]} + ${nums[result[1]]} = ${target}`);
    } else {
        console.log("未找到答案");
    }
}

// 执行主函数
main();

/**
 * 输出结果：
 * 目标值: 9
 * 结果索引: [ 0, 1 ]
 * 对应数值: 2 + 7 = 9
 */

export { twoSum };
