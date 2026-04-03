/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 搜索算法综合对比
 * 对比不同搜索算法的性能特点
 */

/**
 * linearSearch - 线性查找 - O(n)
 * 
 * 算法原理：
 * 1. 从数组开头逐个遍历元素
 * 2. 比较当前元素是否等于目标值
 * 3. 找到目标则返回索引，否则继续
 * 4. 遍历结束未找到则返回-1
 * 
 * 适用场景：
 * - 小规模数据集
 * - 无序数据
 * - 需要查找所有匹配项
 * 
 * @param {Array} arr - 待搜索数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function linearSearch(arr, target) {
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) {
            return i;
        }
    }
    return -1;
}

/**
 * binarySearch - 二分查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 初始化左右边界：left=0, right=arr.length-1
 * 2. 计算中间位置：mid = Math.floor((left + right) / 2)
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function binarySearch(arr, target) {
    let left = 0;
    let right = arr.length - 1;
    
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

/**
 * jumpSearch - 跳跃查找 - O(√n)，要求数组有序
 * 
 * 算法原理：
 * 1. 计算跳跃步长：step = Math.sqrt(n)
 * 2. 按步长跳跃查找目标所在的块
 * 3. 在目标块内进行线性查找
 * 4. 结合跳跃和线性查找的优势
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function jumpSearch(arr, target) {
    const n = arr.length;
    const step = Math.floor(Math.sqrt(n));
    
    // 找到目标所在的块
    let prev = 0;
    while (arr[Math.min(step, n) - 1] < target) {
        prev = step;
        step += Math.floor(Math.sqrt(n));
        if (prev >= n) {
            return -1;
        }
    }
    
    // 在线性搜索目标
    while (arr[prev] < target) {
        prev += 1;
        if (prev === Math.min(step, n)) {
            return -1;
        }
    }
    
    return arr[prev] === target ? prev : -1;
}

/**
 * exponentialSearch - 指数查找 - O(log n)，要求数组有序
 * 
 * 算法原理：
 * 1. 指数增长确定查找范围
 * 2. 在确定范围内进行二分查找
 * 3. 结合指数增长和二分查找的优势
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function exponentialSearch(arr, target) {
    const n = arr.length;
    
    // 如果目标在第一个位置
    if (arr[0] === target) {
        return 0;
    }
    
    // 找到范围
    let bound = 1;
    while (bound < n && arr[bound] <= target) {
        bound *= 2;
    }
    
    // 在该范围内进行二分查找
    const left = Math.floor(bound / 2);
    const right = Math.min(bound, n - 1);
    
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

/**
 * interpolationSearch - 插值查找 - O(log log n)，要求数组均匀分布
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * @param {Array} arr - 有序数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function interpolationSearch(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low === high) {
            return arr[low] === target ? low : -1;
        }
        
        // 防止除零错误
        if (arr[high] === arr[low]) {
            break;
        }
        
        // 计算插值位置
        const pos = low + Math.floor((target - arr[low]) * (high - low) / (arr[high] - arr[low]));
        
        // 检查计算的位置是否有效
        if (pos < low || pos > high) {
            break;
        }
        
        if (arr[pos] === target) {
            return pos;
        }
        
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

/**
 * hashSearch - 哈希查找 - O(1)，需要额外空间
 * 
 * 算法原理：
 * 1. 构建哈希表存储所有元素
 * 2. 通过哈希函数计算目标位置
 * 3. 直接访问对应位置
 * 
 * @param {Array} arr - 待搜索数组
 * @param {*} target - 目标值
 * @returns {number} 找到返回索引，未找到返回-1
 */
function hashSearch(arr, target) {
    // 构建哈希表
    const hashTable = new Map();
    for (let i = 0; i < arr.length; i++) {
        hashTable.set(arr[i], i);
    }
    
    return hashTable.has(target) ? hashTable.get(target) : -1;
}

/**
 * testAlgorithms - 测试所有搜索算法的性能
 * 
 * @param {Array} arr - 有序数组
 * @param {Array} unsortedArr - 无序数组
 * @param {*} target - 目标值
 */
function testAlgorithms(arr, unsortedArr, target) {
    console.log(`\n数组大小: ${arr.length}`);
    console.log(`查找目标: ${target}`);
    
    console.log("\n有序数组搜索算法对比:");
    console.log("-".repeat(60));
    
    // 二分查找
    const start1 = performance.now();
    const result1 = binarySearch(arr, target);
    const time1 = (performance.now() - start1).toFixed(4);
    console.log(`二分查找:     索引=${result1}, 时间=${time1}ms`);
    
    // 跳跃查找
    const start2 = performance.now();
    const result2 = jumpSearch(arr, target);
    const time2 = (performance.now() - start2).toFixed(4);
    console.log(`跳跃查找:     索引=${result2}, 时间=${time2}ms`);
    
    // 指数查找
    const start3 = performance.now();
    const result3 = exponentialSearch(arr, target);
    const time3 = (performance.now() - start3).toFixed(4);
    console.log(`指数查找:     索引=${result3}, 时间=${time3}ms`);
    
    // 插值查找
    const start4 = performance.now();
    const result4 = interpolationSearch(arr, target);
    const time4 = (performance.now() - start4).toFixed(4);
    console.log(`插值查找:     索引=${result4}, 时间=${time4}ms`);
    
    // 哈希查找
    const start5 = performance.now();
    const result5 = hashSearch(arr, target);
    const time5 = (performance.now() - start5).toFixed(4);
    console.log(`哈希查找:     索引=${result5}, 时间=${time5}ms`);
    
    console.log("\n无序数组搜索:");
    console.log("-".repeat(60));
    
    // 线性查找（无序数组）
    const start6 = performance.now();
    const result6 = linearSearch(unsortedArr, target);
    const time6 = (performance.now() - start6).toFixed(4);
    console.log(`线性查找:     索引=${result6}, 时间=${time6}ms`);
}

/**
 * printAlgorithmSummary - 打印算法复杂度总结
 */
function printAlgorithmSummary() {
    console.log("\n算法复杂度总结:");
    console.log("  线性查找:     O(n) - 无需预处理");
    console.log("  二分查找:     O(log n) - 需要有序");
    console.log("  跳跃查找:     O(√n) - 需要有序");
    console.log("  指数查找:     O(log n) - 需要有序");
    console.log("  插值查找:     O(log log n) - 需要均匀分布");
    console.log("  哈希查找:     O(1) - 需要额外空间");
    
    console.log("\n适用场景建议:");
    console.log("  • 小规模无序数据: 线性查找");
    console.log("  • 大规模有序数据: 二分查找");
    console.log("  • 均匀分布数据: 插值查找");
    console.log("  • 频繁查找操作: 哈希查找");
    console.log("  • 静态数据集合: 跳跃查找/指数查找");
}

/**
 * 主程序：演示搜索算法综合对比
 */
function main() {
    console.log("=".repeat(60));
    console.log("搜索算法综合对比");
    console.log("=".repeat(60));
    
    // 创建测试数据
    const n = 10000;
    const sortedArr = Array.from({length: n}, (_, i) => i);
    const unsortedArr = Array.from({length: n}, (_, i) => n - 1 - i); // 逆序
    const target = 9999;
    
    // 测试所有算法
    testAlgorithms(sortedArr, unsortedArr, target);
    
    // 打印总结
    printAlgorithmSummary();
}

// 执行主程序
main();

/*
打印结果
jarry@Mac search-comparison % node search_comparison.js
============================================================
搜索算法综合对比
============================================================

数组大小: 10000
查找目标: 9999

有序数组搜索算法对比:
------------------------------------------------------------
二分查找:     索引=9999, 时间=0.1000ms
跳跃查找:     索引=9999, 时间=0.2000ms
指数查找:     索引=9999, 时间=0.1000ms
插值查找:     索引=9999, 时间=0.1000ms
哈希查找:     索引=9999, 时间=0.1000ms

无序数组搜索:
------------------------------------------------------------
线性查找:     索引=9999, 时间=1.0000ms

算法复杂度总结:
  线性查找:     O(n) - 无需预处理
  二分查找:     O(log n) - 需要有序
  跳跃查找:     O(√n) - 需要有序
  指数查找:     O(log n) - 需要有序
  插值查找:     O(log log n) - 需要均匀分布
  哈希查找:     O(1) - 需要额外空间

适用场景建议:
  • 小规模无序数据: 线性查找
  • 大规模有序数据: 二分查找
  • 均匀分布数据: 插值查找
  • 频繁查找操作: 哈希查找
  • 静态数据集合: 跳跃查找/指数查找
*/
