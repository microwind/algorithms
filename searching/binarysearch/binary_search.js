/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * binarySearch1 - 标准非递归版本，传递左右区间指针
 * 
 * 算法步骤：
 * 1. 初始化左右边界：left=0, right=arr.length-1
 * 2. 计算中间位置：midIndex = Math.floor((left + right) / 2)
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function binarySearch1(arr, target) {
    var left = 0
    var right = arr.length - 1
    var midIndex, mid
    // left是左侧，right是最右侧。搜索区间长度小于1时停止
    while (left <= right) {
        midIndex = Math.floor((left + right) / 2)  // 计算中间位置
        mid = arr[midIndex]                           // 获取中间值
        // 中间项等于目标项则返回下标
        if (mid === target) {
            return midIndex
        } else if (target > mid) {
            // 大于中间项折半查找右侧
            left = midIndex + 1
        } else {
            // 小于中间项折半查找左侧
            right = midIndex - 1
        }
    }
    return -1  // 未找到
}

/**
 * binarySearch2 - 递归实现，移动左右区间指针
 * 
 * 算法步骤：
 * 1. 处理默认参数，设置初始边界
 * 2. 计算中间位置和中间值
 * 3. 比较中间值与目标值
 * 4. 根据比较结果递归查找对应半区
 * 5. 处理重复项的特殊情况
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @param {number} left - 左边界（可选）
 * @param {number} right - 右边界（可选）
 * @returns {number} 找到返回索引，未找到返回-1
 */
function binarySearch2(arr, target, left, right) {
    left = left === undefined ? 0 : left                    // 默认左边界为0
    right = right === undefined ? arr.length - 1 : right       // 默认右边界为末尾
    var midIndex = Math.floor((left + right) / 2)
    var mid = arr[midIndex]
    // 中间值等于查找项说明找到了，则返回中间项下标
    if (target === mid) {
        // 如果有重复项，返回第一个位置
        if (arr[left] === target) {
            return left
        }
        return midIndex
    }
    // 如果左侧与右侧相同，表面查找完毕，返回-1
    if (left >= right) {
        return -1
    }
    if (target > mid) {
        // 折半右侧部分开始递归查找
        return binarySearch2(arr, target, midIndex + 1, right)
    } else {
        // 折半左侧部分开始递归查找
        return binarySearch2(arr, target, left, midIndex - 1)
    }
}

/**
 * binarySearch3 - 解决存在重复项问题，返回第一个出现的位置。传递左右区间，向左查找（向右查找类似）
 * 
 * 算法思路：
 * 1. 使用非递归方式，但处理重复项的特殊情况
 * 2. 当找到目标时，继续向左查找第一个出现的位置
 * 3. 通过缩小右边界来确保找到第一个匹配项
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @returns {number} 第一个匹配项的索引，未找到返回-1
 */
function binarySearch3(arr, target) {
    var left = 0
    var right = arr.length - 1
    var midIndex, mid
    // 搜索区间小于等于1停止搜索
    while (left <= right) {
        // 找到中间值
        midIndex = Math.floor((left + right) / 2)
        mid = arr[midIndex]

        if (target > mid) {
            // 大于中间项折半查找右侧
            left = midIndex + 1
        } else {
            // 小于等于中间项则折半查找左侧，同时缩小右侧范围
            right = midIndex - 1
        }
    }
    // 此时left是最左侧目标项
    if (left <= arr.length && arr[left] === target) {
        return left
    }

    return -1  // 未找到
}

/**
 * binarySearch4 - 二分搜索递归查找，记录下右侧位置
 * 
 * 算法思路：
 * 1. 使用递归方式，但通过参数累积已跳过的元素数量
 * 2. 通过resultIndex参数记录相对位置
 * 3. 找到目标时，返回累积的索引位置
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @param {number} resultIndex - 累积的索引位置（内部使用）
 * @returns {number} 找到返回索引，未找到返回-1
 */
function binarySearch4(arr, target, resultIndex) {
    if (arr.length <= 1 && target !== arr[0]) {
        return -1  // 数组为空或只有一个元素且不匹配
    }
    var midIndex = Math.floor((arr.length - 1) / 2)
    var mid = arr[midIndex]
    resultIndex = resultIndex === undefined ? 0 : resultIndex  // 初始化累积索引
    if (target === mid) {
        return resultIndex + midIndex  // 返回累积的索引位置
    } else if (target > mid) {
        // 如果在右侧，则需要将中间index加上
        return binarySearch4(arr.slice(midIndex + 1), target, resultIndex + midIndex + 1)
        // 或者使用splice修改原数组，性能略低
        // return binarySearch4(arr.splice(midIndex + 1), target, resultIndex + midIndex + 1)
    } else {
        return binarySearch4(arr.slice(0, midIndex), target, resultIndex)
        // 或者使用splice修改原数组，性能略低
        // return binarySearch4(arr.splice(0, midIndex), target, resultIndex)
    }
    
}


/**
 * 主程序：演示四种二分查找算法的性能对比
 * 
 * 测试内容：
 * 1. binarySearch1 - 标准非递归版本
 * 2. binarySearch2 - 递归版本，处理重复项
 * 3. binarySearch3 - 非递归版本，专门查找第一个匹配项
 * 4. binarySearch4 - 递归版本，记录累积索引
 */
console.time('time')
var arr = [2, 3, 8, 10, 10, 13]  // 包含重复项的测试数组
var result = binarySearch1(arr, 10) // 期望返回4（第一个10的位置）
console.log('binarySearch1(arr, 10)', '=> result:' + result)
console.timeEnd('time')

console.time('time')
arr = [2, 3, 8, 10, 10, 13]
result = binarySearch2(arr, 10) // 期望返回3（第一个10的位置）
console.log('binarySearch2(arr, 10)', '=> result:' + result)
console.timeEnd('time')

console.time('time')
arr = [2, 3, 8, 10, 10, 13]
result = binarySearch3(arr, 10) // 期望返回3（第一个10的位置）
console.log('binarySearch3(arr, 10)', '=> result:' + result)
console.timeEnd('time')

console.time('time')
arr = [2, 3, 8, 10, 10, 13]
result = binarySearch4(arr, 10) // 期望返回4（第一个10的位置）
console.log('binarySearch4(arr, 10)', '=> result:' + result)
console.timeEnd('time')

/**
jarry@jarrys-MacBook-Pro binarysearch % node binary_search.js
binarySearch1(arr, 10) => result:4
time: 2.280ms
binarySearch2(arr, 10) => result:3
time: 0.194ms
binarySearch3(arr, 10) => result:3
time: 0.080ms
binarySearch4(arr, 10) => result:4
time: 0.106ms
 */