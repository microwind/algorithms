/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 线性查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * 线性查找基础版本 - 查找第一个匹配项
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
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @returns 找到返回索引，未找到返回-1
 */
function linearSearch<T>(arr: T[], target: T): number {
    // 边界检查
    if (!arr || arr.length === 0) {
        return -1;
    }
    
    // 逐个遍历查找
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) {
            return i; // 找到目标，返回索引
        }
    }
    
    return -1; // 未找到
}

/**
 * 线性查找 - 查找所有匹配项
 * 
 * 算法思路：
 * 遍历整个数组，收集所有匹配项的索引
 * 适合处理重复元素的情况
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @returns 包含所有匹配索引的数组
 */
function linearSearchAll<T>(arr: T[], target: T): number[] {
    const result: number[] = [];
    
    // 边界检查
    if (!arr || arr.length === 0) {
        return result;
    }
    
    // 逐个遍历查找所有匹配项
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) {
            result.push(i);
        }
    }
    
    return result;
}

/**
 * 线性查找 - 带哨兵优化版本
 * 
 * 算法优化：
 * 在数组末尾设置哨兵（目标值）
 * 减少每次循环中的边界检查
 * 可以略微提高性能
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @returns 找到返回索引，未找到返回-1
 */
function linearSearchSentinel<T>(arr: T[], target: T): number {
    // 边界检查
    if (!arr || arr.length === 0) {
        return -1;
    }
    
    const last = arr[arr.length - 1]; // 保存最后一个元素
    arr[arr.length - 1] = target;   // 设置哨兵
    
    let i = 0;
    // 由于有哨兵，循环一定会终止
    while (arr[i] !== target) {
        i++;
    }
    
    arr[arr.length - 1] = last; // 恢复最后一个元素
    
    // 检查是否真的找到目标
    if (i < arr.length - 1 || arr[arr.length - 1] === target) {
        return i;
    }
    
    return -1;
}

/**
 * 线性查找 - 反向查找版本
 * 
 * 算法思路：
 * 从数组末尾开始向前查找
 * 适合查找最后一个匹配项的场景
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @returns 找到返回索引，未找到返回-1
 */
function linearSearchReverse<T>(arr: T[], target: T): number {
    // 边界检查
    if (!arr || arr.length === 0) {
        return -1;
    }
    
    // 从后向前遍历查找
    for (let i = arr.length - 1; i >= 0; i--) {
        if (arr[i] === target) {
            return i; // 找到目标，返回索引
        }
    }
    
    return -1; // 未找到
}

/**
 * 线性查找 - 递归版本
 * 
 * 算法思路：
 * 使用递归方式实现线性查找
 * 每次递归处理一个元素
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @param index 当前索引
 * @returns 找到返回索引，未找到返回-1
 */
function linearSearchRecursive<T>(arr: T[], target: T, index: number = 0): number {
    // 递归出口条件
    if (index >= arr.length) {
        return -1;
    }
    
    // 检查当前元素
    if (arr[index] === target) {
        return index;
    }
    
    // 递归查找下一个元素
    return linearSearchRecursive(arr, target, index + 1);
}

/**
 * 线性查找 - 泛型版本
 * 
 * 算法扩展：
 * 支持任意类型的数组查找
 * 使用泛型提高代码复用性
 * 
 * @param arr 待搜索数组
 * @param target 目标值
 * @returns 找到返回索引，未找到返回-1
 */
function linearSearchGeneric<T>(arr: T[], target: T): number {
    // 边界检查
    if (!arr || arr.length === 0) {
        return -1;
    }
    
    // 逐个遍历查找
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] === target) {
            return i; // 找到目标，返回索引
        }
    }
    
    return -1; // 未找到
}

/**
 * 主程序：演示线性查找功能
 */
function main(): void {
    console.log('=== 线性查找演示 ===\n');
    
    // 测试数据
    const arr = [64, 34, 25, 12, 22, 11, 90, 22];
    const target = 22;
    
    console.log('数组:');
    console.log(arr.join(' '));
    console.log(`目标元素: ${target}\n`);
    
    // 基本查找测试
    console.log('=== 基本查找测试 ===');
    const index = linearSearch(arr, target);
    if (index !== -1) {
        console.log(`基本查找: 找到于索引 ${index}`);
    } else {
        console.log('基本查找: 未找到');
    }
    
    // 查找所有匹配项
    console.log('\n=== 查找所有匹配项 ===');
    const allIndices = linearSearchAll(arr, target);
    console.log(`所有匹配位置: ${allIndices.join(' ')} (共${allIndices.length}个)`);
    
    // 反向查找测试
    console.log('\n=== 反向查找测试 ===');
    const reverseIndex = linearSearchReverse(arr, target);
    if (reverseIndex !== -1) {
        console.log(`反向查找: 找到于索引 ${reverseIndex}`);
    } else {
        console.log('反向查找: 未找到');
    }
    
    // 哨兵查找测试
    console.log('\n=== 哨兵查找测试 ===');
    const sentinelIndex = linearSearchSentinel([...arr], target);
    if (sentinelIndex !== -1) {
        console.log(`哨兵查找: 找到于索引 ${sentinelIndex}`);
    } else {
        console.log('哨兵查找: 未找到');
    }
    
    // 递归查找测试
    console.log('\n=== 递归查找测试 ===');
    const recursiveIndex = linearSearchRecursive(arr, target);
    if (recursiveIndex !== -1) {
        console.log(`递归查找: 找到于索引 ${recursiveIndex}`);
    } else {
        console.log('递归查找: 未找到');
    }
    
    // 查找不存在的元素
    console.log('\n=== 查找不存在的元素 ===');
    const notFound = linearSearch(arr, 100);
    console.log(`查找100: ${notFound !== -1 ? '找到' : '未找到'}`);
    
    // 泛型查找测试
    console.log('\n=== 泛型查找测试 ===');
    const strArr = ['apple', 'banana', 'cherry', 'date', 'banana'];
    const strTarget = 'banana';
    
    console.log('字符串数组:');
    console.log(strArr.join(' '));
    console.log(`目标字符串: ${strTarget}`);
    
    const strIndex = linearSearchGeneric(strArr, strTarget);
    if (strIndex !== -1) {
        console.log(`泛型查找: 找到于索引 ${strIndex}`);
    } else {
        console.log('泛型查找: 未找到');
    }
    
    const strAllIndices = linearSearchAll(strArr, strTarget);
    console.log(`所有匹配位置: ${strAllIndices.join(' ')} (共${strAllIndices.length}个)`);
    
    // 性能分析
    console.log('\n=== 线性查找特点 ===');
    console.log('• 算法简单，易于实现');
    console.log('• 适用于小规模数据和无序数据');
    console.log('• 时间复杂度：O(n)');
    console.log('• 空间复杂度：O(1)');
    console.log('• 可以查找所有匹配项');
    console.log('• 适合处理重复元素');
    
    // 与其他查找算法对比
    console.log('\n=== 与其他查找算法对比 ===');
    console.log('• 二分查找：O(log n)，但要求数组有序');
    console.log('• 哈希查找：O(1)，但需要额外空间');
    console.log('• 线性查找：O(n)，但无需预处理');
    console.log('• 选择算法取决于数据规模和是否有序');
    
    // 性能测试
    console.log('\n=== 性能测试 ===');
    const largeArr = Array.from({length: 10000}, (_, i) => i);
    const testTarget = 9999;
    
    const startTime = Date.now();
    const perfIndex = linearSearch(largeArr, testTarget);
    const endTime = Date.now();
    
    console.log(`数组大小: ${largeArr.length}`);
    console.log(`查找目标: ${testTarget}`);
    console.log(`查找结果: ${perfIndex !== -1 ? '找到' : '未找到'}`);
    console.log(`执行时间: ${endTime - startTime}ms`);
}

// 执行主程序
main();

/*
打印结果
jarry@Mac linear-search % npx tsc linear_search.ts && node linear_search.js
=== 线性查找演示 ===

数组:
64 34 25 12 22 11 90 22 
目标元素: 22

=== 基本查找测试 ===
基本查找: 找到于索引 4

=== 查找所有匹配项 ===
所有匹配位置: 4 7 (共2个)

=== 反向查找测试 ===
反向查找: 找到于索引 7

=== 哨兵查找测试 ===
哨兵查找: 找到于索引 4

=== 递归查找测试 ===
递归查找: 找到于索引 4

=== 查找不存在的元素 ===
查找100: 未找到

=== 泛型查找测试 ===
字符串数组:
apple banana cherry date banana 
目标字符串: banana
泛型查找: 找到于索引 1
所有匹配位置: 1 4 (共2个)

=== 线性查找特点 ===
• 算法简单，易于实现
• 适用于小规模数据和无序数据
• 适用于小规模数据和无序数据
• 时间复杂度：O(n)
• 空间复杂度：O(1)
• 可以查找所有匹配项
• 适合处理重复元素

=== 与其他查找算法对比 ===
• 二分查找：O(log n)，但要求数组有序
• 哈希查找：O(1)，但需要额外空间
• 线性查找：O(n)，但无需预处理
• 选择算法取决于数据规模和是否有序

=== 性能测试 ===
数组大小: 10000
查找目标: 9999
查找结果: 找到
执行时间: 0ms
*/
