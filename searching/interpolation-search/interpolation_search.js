/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插值查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * interpolationSearch - 插值查找基础版本 - 非递归实现
 * 
 * 算法原理：
 * 1. 通过公式估算目标位置：pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low])
 * 2. 根据估算位置调整查找范围
 * 3. 重复直到找到目标或确定不存在
 * 
 * 适用场景：
 * - 均匀分布的有序数组
 * - 数值范围较大的数据集
 * 
 * 时间复杂度：平均O(log log n)，最坏O(n)
 * 空间复杂度：O(1)
 * 
 * @param {number[]} arr - 有序数组
 * @param {number} target - 目标值
 * @returns {number} 目标索引，未找到返回-1
 */
function interpolationSearch(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    
    // 检查边界条件
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // 如果范围只有一个元素
        if (low === high) {
            return arr[low] === target ? low : -1;
        }
        
        // 防止除零错误
        if (arr[high] === arr[low]) {
            break;  // 所有元素相同，无法插值
        }
        
        // 计算插值位置
        // 关键公式：根据数值比例估算位置
        const pos = low + Math.floor((target - arr[low]) * (high - low) / (arr[high] - arr[low]));
        
        // 检查计算的位置是否有效
        if (pos < low || pos > high) {
            break;  // 位置超出范围，退出循环
        }
        
        // 检查是否找到目标
        if (arr[pos] === target) {
            return pos; // 找到目标
        }
        
        // 调整查找范围
        if (arr[pos] < target) {
            low = pos + 1; // 目标在右侧
        } else {
            high = pos - 1; // 目标在左侧
        }
    }
    
    return -1; // 未找到
}

/**
 * 插值查找递归版本
 * 
 * 算法思路：
 * 使用递归方式实现插值查找
 * 每次递归缩小查找范围
 * 
 * @param {number[]} arr 有序数组
 * @param {number} target 目标值
 * @param {number} low 左边界
 * @param {number} high 右边界
 * @returns {number} 目标索引，未找到返回-1
 */
function interpolationSearchRecursive(arr, target, low = 0, high = arr.length - 1) {
    // 递归出口条件
    if (low > high || target < arr[low] || target > arr[high]) {
        return -1;
    }
    
    // 如果范围只有一个元素
    if (low === high) {
        return arr[low] === target ? low : -1;
    }
    
    // 防止除零错误
    if (arr[high] === arr[low]) {
        return -1;
    }
    
    // 计算插值位置
    const pos = low + Math.floor((target - arr[low]) * (high - low) / (arr[high] - arr[low]));
    
    // 检查位置有效性
    if (pos < low || pos > high) {
        return -1;
    }
    
    // 检查是否找到目标
    if (arr[pos] === target) {
        return pos;
    }
    
    // 递归调用
    if (arr[pos] < target) {
        return interpolationSearchRecursive(arr, target, pos + 1, high);
    } else {
        return interpolationSearchRecursive(arr, target, low, pos - 1);
    }
}

/**
 * 插值查找优化版本 - 处理边界情况
 * 
 * 算法优化：
 * - 增加边界检查
 * - 处理特殊情况
 * - 提高算法鲁棒性
 * 
 * @param {number[]} arr 有序数组
 * @param {number} target 目标值
 * @returns {number} 目标索引，未找到返回-1
 */
function interpolationSearchOptimized(arr, target) {
    // 边界检查
    if (!arr || arr.length === 0) {
        return -1;
    }
    
    let low = 0;
    let high = arr.length - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // 处理所有元素相同的情况
        if (arr[high] === arr[low]) {
            if (arr[low] === target) {
                return low; // 所有元素都等于目标
            }
            break; // 所有元素相同但不等于目标
        }
        
        // 计算插值位置，使用更精确的计算
        const ratio = (target - arr[low]) / (arr[high] - arr[low]);
        let pos = low + Math.floor(ratio * (high - low));
        
        // 确保位置在有效范围内
        pos = Math.max(low, Math.min(high, pos));
        
        // 检查是否找到目标
        if (arr[pos] === target) {
            return pos;
        }
        
        // 调整查找范围
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

/**
 * 插值查找 - 浮点数版本
 * 
 * 算法扩展：
 * 支持浮点数数组的插值查找
 * 使用epsilon处理浮点数精度问题
 * 
 * @param {number[]} arr 有序浮点数组
 * @param {number} target 目标值
 * @param {number} epsilon 精度阈值
 * @returns {number} 目标索引，未找到返回-1
 */
function interpolationSearchFloat64(arr, target, epsilon = 0.0001) {
    let low = 0;
    let high = arr.length - 1;
    
    while (low <= high && target >= arr[low] - epsilon && target <= arr[high] + epsilon) {
        if (low === high) {
            return Math.abs(arr[low] - target) <= epsilon ? low : -1;
        }
        
        // 防止除零错误
        if (Math.abs(arr[high] - arr[low]) < epsilon) {
            break;
        }
        
        // 计算插值位置
        const ratio = (target - arr[low]) / (arr[high] - arr[low]);
        let pos = low + Math.floor(ratio * (high - low));
        
        // 确保位置有效
        pos = Math.max(low, Math.min(high, pos));
        
        // 检查是否找到目标（考虑浮点精度）
        if (Math.abs(arr[pos] - target) <= epsilon) {
            return pos;
        }
        
        // 调整查找范围
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    
    return -1;
}

/**
 * 主程序：演示插值查找功能
 */
function main() {
    console.log('=== 插值查找演示 ===\n');
    
    // 测试数据：均匀分布的有序数组
    const arr = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];
    
    console.log('数组 (均匀分布):');
    console.log(arr.join(' '));
    console.log();
    
    // 测试目标值
    const targets = [30, 85, 10, 100, 55];
    
    console.log('=== 非递归版本测试 ===');
    for (const target of targets) {
        const result = interpolationSearch(arr, target);
        if (result !== -1) {
            console.log(`查找 ${target}: 找到于索引 ${result}`);
        } else {
            console.log(`查找 ${target}: 未找到`);
        }
    }
    
    console.log('\n=== 递归版本测试 ===');
    for (const target of targets) {
        const result = interpolationSearchRecursive(arr, target, 0, arr.length - 1);
        if (result !== -1) {
            console.log(`查找 ${target}: 找到于索引 ${result}`);
        } else {
            console.log(`查找 ${target}: 未找到`);
        }
    }
    
    console.log('\n=== 优化版本测试 ===');
    for (const target of targets) {
        const result = interpolationSearchOptimized(arr, target);
        if (result !== -1) {
            console.log(`查找 ${target}: 找到于索引 ${result}`);
        } else {
            console.log(`查找 ${target}: 未找到`);
        }
    }
    
    // 浮点数版本测试
    console.log('\n=== 浮点数版本测试 ===');
    const doubleArr = [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 11.0];
    const doubleTargets = [3.3, 7.7, 1.1, 11.0, 5.5];
    const epsilon = 0.0001;
    
    for (const target of doubleTargets) {
        const result = interpolationSearchFloat64(doubleArr, target, epsilon);
        if (result !== -1) {
            console.log(`查找 ${target}: 找到于索引 ${result}`);
        } else {
            console.log(`查找 ${target}: 未找到`);
        }
    }
    
    // 性能分析
    console.log('\n=== 插值查找特点 ===');
    console.log('• 适用于均匀分布的数据');
    console.log('• 通过公式估算位置，跳过不必要的比较');
    console.log('• 对于均匀数据，性能优于二分查找');
    console.log('• 对于非均匀数据，可能退化为线性查找');
    console.log('• 时间复杂度：平均O(log log n)，最坏O(n)');
    console.log('• 空间复杂度：O(1)');
    
    // 与二分查找对比
    console.log('\n=== 与二分查找对比 ===');
    console.log('• 二分查找：总是取中间位置');
    console.log('• 插值查找：根据值估算位置');
    console.log('• 对于均匀数据，插值查找更快');
    console.log('• 对于非均匀数据，插值查找可能更慢');
}

// 执行主程序
main();

/*
打印结果
jarry@Mac interpolation-search % node interpolation_search.js
=== 插值查找演示 ===

数组 (均匀分布):
10 20 30 40 50 60 70 80 90 100

=== 非递归版本测试 ===
查找 30: 找到于索引 2
查找 85: 未找到
查找 10: 找到于索引 0
查找 100: 找到于索引 9
查找 55: 未找到

=== 递归版本测试 ===
查找 30: 找到于索引 2
查找 85: 未找到
查找 10: 找到于索引 0
查找 100: 找到于索引 9
查找 55: 未找到

=== 优化版本测试 ===
查找 30: 找到于索引 2
查找 85: 未找到
查找 10: 找到于索引 0
查找 100: 找到于索引 9
查找 55: 未找到

=== 浮点数版本测试 ===
查找 3.3: 找到于索引 2
查找 7.7: 找到于索引 6
查找 1.1: 找到于索引 0
查找 11.0: 找到于索引 9
查找 5.5: 找到于索引 4

=== 插值查找特点 ===
• 适用于均匀分布的数据
• 通过公式估算位置，跳过不必要的比较
• 对于均匀数据，性能优于二分查找
• 对于非均匀数据，可能退化为线性查找
• 时间复杂度：平均O(log log n)，最坏O(n)
• 空间复杂度：O(1)

=== 与二分查找对比 ===
• 二分查找：总是取中间位置
• 插值查找：根据值估算位置
• 对于均匀数据，插值查找更快
• 对于非均匀数据，插值查找可能更慢
*/
