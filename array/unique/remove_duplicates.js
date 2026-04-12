/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 数组去重算法 - JavaScript实现
 * 
 * 算法原理：
 * 提供三种不同的去重方法：
 * 1. unique: 去掉数组里的多余重复项，保证成员唯一（每个元素只保留第一次出现）
 * 2. getDuplicates: 获取数组里的重复项（返回所有重复的元素）
 * 3. removeDuplicates: 删除数组里全部的重复项（只保留完全不重复的元素）
 * 
 * 使用 filter 和 indexOf 方法实现去重逻辑。
 * 
 * 时间复杂度：
 * - unique: O(n²) - indexOf 是 O(n)，filter 遍历是 O(n)
 * - getDuplicates: O(n²) - 多次 indexOf 调用
 * - removeDuplicates: O(n²) - 多次 indexOf 调用
 * 空间复杂度：O(n) - 需要额外的结果数组
 */

/**
 * 去掉数组里的多余重复项，保证成员唯一
 * 每个元素只保留第一次出现的位置
 * @param {any[]} arr - 输入数组
 * @returns {any[]} 去重后的数组
 */
function unique(arr) {
    const result = arr.filter((item, index) => {
        // indexOf 返回元素第一次出现的索引
        // 如果当前索引等于第一次出现的索引，说明是第一次遇到该元素
        return arr.indexOf(item) === index
    })
    return result
}

/**
 * 获取数组里的重复项
 * 返回所有出现超过一次的元素
 * @param {any[]} arr - 输入数组
 * @returns {any[]} 包含所有重复元素的数组
 */
function getDuplicates(arr) {
    const result = []
    arr.filter((item, index) => {
        // 如果当前索引不是第一次出现（说明是重复的）
        // 且结果数组中还没有该元素（避免重复添加）
        if (arr.indexOf(item) !== index &&
            result.indexOf(item) === -1) {
            result.push(item)
        }
    })
    return result
}

/**
 * 删除数组里全部的重复项
 * 只保留完全不重复的元素（出现次数为1的元素）
 * @param {any[]} arr - 输入数组
 * @returns {any[]} 只包含不重复元素的数组
 */
function removeDuplicates(arr) {
    const result = arr.filter((item, index) => {
        // 如果当前索引是第一次出现
        if (arr.indexOf(item) === index) {
            // 检查从下一个位置开始是否还能找到该元素
            // 如果找不到，说明该元素只出现一次
            return arr.indexOf(item, index + 1) === -1
        }
    })
    return result
}

// 测试代码
const arr1 = [1, 2, 2, 3, 5, 3, 3, 4]
console.log('unique:', unique(arr1))

const arr2 = [1, 2, 2, 3, 5, 3, 3, 4]
console.log('getDuplicates:', getDuplicates(arr2))

const arr3 = [1, 2, 2, 3, 5, 3, 3, 4]
console.log('removeDuplicates:', removeDuplicates(arr3))

/*
 * 输出结果：
 * unique: [1, 2, 3, 5, 4]
 * getDuplicates: [2, 3]
 * removeDuplicates: [1, 5, 4]
 */
