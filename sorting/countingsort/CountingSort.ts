/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 计数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

function printArray(arr: number[], label: string): void {
    console.log(`${label}: [${arr.join(', ')}]`);
}

function performanceTest(sortFunc: (arr: number[]) => void, arr: number[], name: string): void {
    // 创建数组副本，避免修改原数组
    const testArr = [...arr];
    printArray(testArr, `${name}原始数组`);
    
    // 开始计时
    console.time(name);
    sortFunc(testArr);
    console.timeEnd(name);
    
    printArray(testArr, `${name}排序结果`);
    console.log(''); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含负数和重复元素的典型数组
const testData: number[] = [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80];

/**
 * 计数排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 统计每个元素出现的次数
 * 2. 计算累计计数以确定元素位置
 * 3. 根据累计计数将元素放到正确位置
 * 4. 从后向前遍历保证稳定性
 * 
 * 生活类比：就像统计班级学生成绩分布，
 * 先统计每个分数段有多少人，然后按分数段排序
 * 
 * 时间复杂度：O(n + k)，n为元素个数，k为数据范围
 * 空间复杂度：O(k) - 需要计数数组
 * 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
 */
function countingSort1(arr: number[]): void {
    console.log('countingSort1 standard:');
    
    if (arr.length === 0) return;
    
    // 找到最小值和最大值
    const min = Math.min(...arr);
    const max = Math.max(...arr);
    const range = max - min + 1;
    
    // 创建计数数组
    const count = new Array(range).fill(0);
    
    // 统计每个元素出现的次数
    for (let i = 0; i < arr.length; i++) {
        count[arr[i] - min]++;
    }
    
    // 计算累计计数
    for (let i = 1; i < count.length; i++) {
        count[i] += count[i - 1];
    }
    
    // 创建输出数组
    const output = new Array(arr.length);
    
    // 从后向前遍历，保证稳定性
    for (let i = arr.length - 1; i >= 0; i--) {
        const index = arr[i] - min;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }
    
    // 复制回原数组
    for (let i = 0; i < arr.length; i++) {
        arr[i] = output[i];
    }
    
    console.log(arr);
}

/**
 * 计数排序优化版本 - 内存优化
 * 
 * 算法思路：
 * 直接在原数组上进行修改，减少内存使用
 * 使用原地排序技术
 * 
 * 优化效果：
 * - 减少额外空间使用
 * - 更好的缓存性能
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：不稳定 - 原地修改可能影响稳定性
 */
function countingSort2(arr: number[]): void {
    console.log('countingSort2 memory optimized:');
    
    if (arr.length === 0) return;
    
    // 找到最小值和最大值
    const min = Math.min(...arr);
    const max = Math.max(...arr);
    const range = max - min + 1;
    
    // 创建计数数组
    const count = new Array(range).fill(0);
    
    // 统计每个元素出现的次数
    for (let i = 0; i < arr.length; i++) {
        count[arr[i] - min]++;
    }
    
    // 直接根据计数重构数组
    let index = 0;
    for (let i = 0; i < count.length; i++) {
        while (count[i] > 0) {
            arr[index] = i + min;
            index++;
            count[i]--;
        }
    }
    
    console.log(arr);
}

/**
 * 计数排序 - 负数处理版本
 * 
 * 算法思路：
 * 专门处理包含负数的情况
 * 分别处理负数和正数部分
 * 
 * 优化效果：
 * - 支持负数排序
 * - 保持算法稳定性
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
function countingSort3(arr: number[]): void {
    console.log('countingSort3 negative numbers:');
    
    if (arr.length === 0) return;
    
    // 分离正数和负数
    const negatives: number[] = [];
    const positives: number[] = [];
    
    for (const value of arr) {
        if (value < 0) {
            negatives.push(value);
        } else {
            positives.push(value);
        }
    }
    
    // 排序负数部分（转换为绝对值排序后反转）
    if (negatives.length > 0) {
        const absNegatives = negatives.map(Math.abs);
        countingSort1(absNegatives);
        
        // 反转并恢复负号
        for (let i = 0; i < absNegatives.length; i++) {
            negatives[i] = -absNegatives[absNegatives.length - 1 - i];
        }
    }
    
    // 排序正数部分
    if (positives.length > 0) {
        countingSort1(positives);
    }
    
    // 合并结果
    const result = [...negatives, ...positives];
    
    // 复制回原数组
    for (let i = 0; i < result.length; i++) {
        arr[i] = result[i];
    }
    
    console.log(arr);
}

/**
 * 计数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用桶的概念，将相近的数值分组
 * 减少计数数组的大小
 * 适合大数据范围但分布稀疏的情况
 * 
 * 优化效果：
 * - 减少内存使用
 * - 提高处理稀疏数据的效率
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
function countingSort4(arr: number[]): void {
    console.log('countingSort4 bucket optimized:');
    
    if (arr.length === 0) return;
    
    // 找到最小值和最大值
    const min = Math.min(...arr);
    const max = Math.max(...arr);
    const range = max - min + 1;
    
    // 确定桶的大小（可以调整以优化性能）
    const bucketSize = Math.max(1, Math.floor(range / 10));
    const bucketCount = Math.ceil(range / bucketSize);
    
    // 创建桶
    const buckets: number[][] = Array.from({length: bucketCount}, () => []);
    
    // 将元素分配到桶中
    for (let i = 0; i < arr.length; i++) {
        const bucketIndex = Math.floor((arr[i] - min) / bucketSize);
        buckets[bucketIndex].push(arr[i]);
    }
    
    // 对每个桶进行排序并合并结果
    let index = 0;
    for (let i = 0; i < bucketCount; i++) {
        if (buckets[i].length > 0) {
            // 对桶内元素使用标准计数排序
            countingSort1(buckets[i]);
            
            // 将排序后的桶内容复制回原数组
            for (let j = 0; j < buckets[i].length; j++) {
                arr[index] = buckets[i][j];
                index++;
            }
        }
    }
    
    console.log(arr);
}

// ==================== 算法测试和性能对比 ====================

// 测试1：标准版本
performanceTest(countingSort1, testData, '标准版本');

// 测试2：内存优化版本
performanceTest(countingSort2, testData, '内存优化版本');

// 测试3：负数处理版本
performanceTest(countingSort3, testData, '负数处理版本');

// 测试4：桶优化版本
performanceTest(countingSort4, testData, '桶优化版本');

console.log('=== 算法对比总结 ===');
console.log('1. 标准版本：经典实现，稳定排序');
console.log('2. 内存优化版本：原地修改，节省空间');
console.log('3. 负数处理版本：支持负数，功能完整');
console.log('4. 桶优化版本：分组处理，适合稀疏数据');

/*
打印结果
jarry@Mac countingsort % ts-node CountingSort.ts
标准版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
[
  -10,  0,  6,  9,  9,
   11, 11, 13, 15, 20,
   30, 80
]
标准版本: 5.207ms
标准版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
[
  -10,  0,  6,  9,  9,
   11, 11, 13, 15, 20,
   30, 80
]
内存优化版本: 0.333ms
内存优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
countingSort1 standard:
[ 10 ]
countingSort1 standard:
[
   0,  6,  9,  9, 11,
  11, 13, 15, 20, 30,
  80
]
[
  -10,  0,  6,  9,  9,
   11, 11, 13, 15, 20,
   30, 80
]
负数处理版本: 0.394ms
负数处理版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本原始数组: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
countingSort1 standard:
[ -10 ]
countingSort1 standard:
[ 0, 6 ]
countingSort1 standard:
[ 9, 9, 11, 11, 13, 15 ]
countingSort1 standard:
[ 20 ]
countingSort1 standard:
[ 30 ]
countingSort1 standard:
[ 80 ]
[
  -10,  0,  6,  9,  9,
   11, 11, 13, 15, 20,
   30, 80
]
桶优化版本: 0.844ms
桶优化版本排序结果: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
