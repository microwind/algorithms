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

// ==================== 辅助函数 ====================

/**
 * 打印数组内容的辅助函数
 * @param {Array} arr - 要打印的数组
 * @param {string} label - 数组的标签说明
 */
function printArray(arr, label) {
  console.log(`${label}: [${arr.join(', ')}]`);
}

/**
 * 性能测试辅助函数
 * @param {Function} sortFunc - 排序函数
 * @param {Array} arr - 测试数组
 * @param {string} name - 版本名称
 */
function performanceTest(sortFunc, arr, name) {
  // 创建数组副本，避免修改原数组
  const testArr = arr.slice();
  printArray(testArr, `${name}原始数组`);
  
  // 开始计时
  const startTime = performance.now();
  const result = sortFunc(testArr);
  const endTime = performance.now();
  
  console.log(`${name}: ${(endTime - startTime).toFixed(3)}ms`);
  printArray(result, `${name}排序结果`);
  console.log(''); // 空行分隔
}

// ==================== 计数排序算法实现 ====================

/**
 * 计数排序标准版
 * 
 * 算法思路：
 * 第一步：计算最大值与最小值，确定数据范围
 * 第二步：创建计数数组，统计每个元素出现的次数
 * 第三步：将计数数组转换为累加数组，确定每个元素的最终位置
 * 第四步：从后向前遍历原数组，按位置还原数据（保证稳定性）
 * 
 * 特点：
 * - 支持负数：通过减去min值处理负数
 * - 稳定排序：从后向前遍历保持相等元素的相对位置
 * - 标准实现：符合计数排序的经典算法
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 * 
 * @param {Array<number>} arr - 待排序的整数数组
 * @returns {Array<number>} 排序后的数组
 */
function countingSort1(arr) {
  console.log('countingSort1 standard:');
  
  // 第一步：计算最大值与最小值，确定数据范围
  if (arr.length === 0) return [];
  
  const arrLen = arr.length;
  let min = arr[0];
  let max = arr[0];
  
  // 优化：单次遍历同时找到最小值和最大值
  for (let i = 1; i < arrLen; i++) {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }
  
  // 第二步：创建计数数组，统计每个元素出现的次数
  const countListLen = max - min + 1;
  const countList = new Array(countListLen).fill(0);
  
  // 统计每个元素出现的次数
  for (let i = 0; i < arrLen; i++) {
    // 将元素值转换为计数数组索引（支持负数）
    const idx = arr[i] - min;
    countList[idx] += 1;
  }

  console.log('countList:', countList);
  
  // 第三步：将计数数组转换为累加数组，确定每个元素的最终位置
  for (let i = 1; i < countListLen; i++) {
    countList[i] += countList[i - 1];
  }

  // 第四步：从后向前遍历原数组，按位置还原数据（保证稳定性）
  const output = new Array(arrLen);
  for (let i = arrLen - 1; i >= 0; i--) {
    // 当前项来自原始数组减去min
    const item = arr[i] - min;
    // 根据当前项从计数数组里找到目标位置
    const idx = countList[item] - 1;
    // 输出数据加上min进行还原
    output[idx] = item + min;
    // 取出一项计数则减少一个
    countList[item] -= 1;
  }
  
  console.log('origin arr=', arr, 'output:=', output);
  return output;
}

/**
 * 计数排序优化版 - 内存优化
 * 
 * 算法思路：
 * 第一步：计算最大值与最小值，确定数据范围
 * 第二步：创建计数数组，统计每个元素出现的次数
 * 第三步：直接根据计数重构数组，省去累加步骤
 * 
 * 特点：
 * - 原地修改：直接在原数组上进行修改
 * - 简化流程：省去累加数组步骤
 * - 高效重建：直接按计数重建结果
 * - 空间优化：不需要额外的输出数组
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：不稳定
 * 
 * @param {Array<number>} arr - 待排序的整数数组
 * @returns {Array<number>} 排序后的数组
 */
function countingSort2(arr) {
  console.log('countingSort2 memory optimized:');
  
  // 第一步：计算最大值与最小值，确定数据范围
  if (arr.length === 0) return [];
  
  const arrLen = arr.length;
  let min = arr[0];
  let max = arr[0];
  
  // 优化：单次遍历同时找到最小值和最大值
  for (let i = 1; i < arrLen; i++) {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }
  
  // 第二步：创建计数数组，统计每个元素出现的次数
  const countListLen = max - min + 1;
  const countList = new Array(countListLen).fill(0);
  
  // 统计每个元素出现的次数
  for (let i = 0; i < arrLen; i++) {
    // 将元素值转换为计数数组索引（支持负数）
    const idx = arr[i] - min;
    countList[idx] += 1;
  }

  console.log('countList:', countList);
  
  // 第三步：直接根据计数重构数组，省去累加步骤
  const output = [];
  let outputIndex = 0;
  
  // 遍历计数数组，按顺序输出
  for (let i = 0; i < countListLen; i++) {
    const count = countList[i];
    // 根据计数值重复放入元素
    for (let j = 0; j < count; j++) {
      console.log('i|val:', i, count);
      // 将索引转换回原值并放入输出数组
      output[outputIndex++] = i + min;
    }
  }
  
  console.log('origin arr=', arr, 'output:=', output);
  return output;
}

/**
 * 计数排序 - 负数单独处理版本
 * 
 * 算法思路：
 * 第一步：分离正数和负数，分别处理
 * 第二步：对负数部分转换为绝对值进行排序，然后反转并恢复负号
 * 第三步：对正数部分使用标准计数排序
 * 第四步：合并排序后的负数和正数部分
 * 
 * 特点：
 * - 支持负数：专门处理包含负数的情况
 * - 保持稳定性：使用稳定的排序算法
 * - 功能完整：支持所有整数范围
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 * 
 * @param {Array<number>} arr - 待排序的整数数组
 * @returns {Array<number>} 排序后的数组
 */
function countingSort3(arr) {
  console.log('countingSort3 negative numbers:');
  
  if (arr.length === 0) return [];
  
  // 第一步：分离正数和负数，分别处理
  const negatives = [];
  const positives = [];
  
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] < 0) {
      negatives.push(arr[i]);
    } else {
      positives.push(arr[i]);
    }
  }
  
  // 第二步：对负数部分转换为绝对值进行排序，然后反转并恢复负号
  if (negatives.length > 0) {
    // 转换为绝对值
    const absNegatives = negatives.map(x => -x);
    
    // 使用独立的计数排序逻辑
    if (absNegatives.length > 0) {
      // 找到最小值和最大值
      let min = absNegatives[0];
      let max = absNegatives[0];
      for (let i = 1; i < absNegatives.length; i++) {
        if (absNegatives[i] < min) min = absNegatives[i];
        if (absNegatives[i] > max) max = absNegatives[i];
      }
      
      // 创建计数数组
      const countListLen = max - min + 1;
      const countList = new Array(countListLen).fill(0);
      
      // 统计每个元素出现的次数
      for (let i = 0; i < absNegatives.length; i++) {
        const idx = absNegatives[i] - min;
        countList[idx] += 1;
      }
      
      // 计算累计计数
      for (let i = 1; i < countListLen; i++) {
        countList[i] += countList[i - 1];
      }
      
      // 从后向前遍历，保证稳定性
      const output = new Array(absNegatives.length);
      for (let i = absNegatives.length - 1; i >= 0; i--) {
        const item = absNegatives[i] - min;
        const idx = countList[item] - 1;
        output[idx] = item + min;
        countList[item] -= 1;
      }
      
      // 反转并恢复负号（负数排序后应该是从大到小，所以要反转）
      for (let i = 0; i < output.length; i++) {
        negatives[i] = -output[output.length - 1 - i];
      }
    }
  }
  
  // 第三步：对正数部分使用标准计数排序
  if (positives.length > 0) {
    // 使用独立的计数排序逻辑
    if (positives.length > 0) {
      // 找到最小值和最大值
      let min = positives[0];
      let max = positives[0];
      for (let i = 1; i < positives.length; i++) {
        if (positives[i] < min) min = positives[i];
        if (positives[i] > max) max = positives[i];
      }
      
      // 创建计数数组
      const countListLen = max - min + 1;
      const countList = new Array(countListLen).fill(0);
      
      // 统计每个元素出现的次数
      for (let i = 0; i < positives.length; i++) {
        const idx = positives[i] - min;
        countList[idx] += 1;
      }
      
      // 计算累计计数
      for (let i = 1; i < countListLen; i++) {
        countList[i] += countList[i - 1];
      }
      
      // 从后向前遍历，保证稳定性
      const output = new Array(positives.length);
      for (let i = positives.length - 1; i >= 0; i--) {
        const item = positives[i] - min;
        const idx = countList[item] - 1;
        output[idx] = item + min;
        countList[item] -= 1;
      }
      
      // 复制回正数数组
      for (let i = 0; i < output.length; i++) {
        positives[i] = output[i];
      }
    }
  }
  
  // 第四步：合并排序后的负数和正数部分
  const result = [...negatives, ...positives];
  
  console.log('origin arr=', arr, 'output:=', result);
  return result;
}

/**
 * 计数排序 - 桶优化版本
 * 
 * 算法思路：
 * 第一步：根据数据范围动态计算桶的数量和大小
 * 第二步：使用多个小桶减少单个桶的内存占用，分配元素到桶
 * 第三步：对每个桶进行计数排序
 * 第四步：合并所有桶的结果，得到最终排序数组
 * 
 * 特点：
 * - 桶优化：使用多个小桶减少内存占用
 * - 动态调整：根据数据范围动态计算桶数量
 * - 适用于大数据范围：特别适合数据范围很大的情况
 * - 稳定排序：每个桶内使用稳定排序
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 * 
 * @param {Array<number>} arr - 待排序的整数数组
 * @returns {Array<number>} 排序后的数组
 */
function countingSort4(arr) {
  console.log('countingSort4 bucket optimized:');
  
  if (arr.length === 0) return [];
  
  // 第一步：根据数据范围动态计算桶的数量和大小
  let min = arr[0];
  let max = arr[0];
  
  // 优化：单次遍历同时找到最小值和最大值
  for (let i = 1; i < arr.length; i++) {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }
  
  const range = max - min + 1;
  
  // 参照Go版本：确定桶的大小（可以调整以优化性能）
  let bucketSize = 1;
  if (range > 10) {
    bucketSize = Math.floor(range / 10);
  }
  const bucketCount = Math.ceil(range / bucketSize);
  
  // 第二步：使用多个小桶减少单个桶的内存占用，分配元素到桶
  const buckets = Array.from({ length: bucketCount }, () => []);
  
  // 分配元素到桶
  for (let i = 0; i < arr.length; i++) {
    const bucketIndex = Math.floor((arr[i] - min) / bucketSize);
    buckets[bucketIndex].push(arr[i]);
  }
  
  // 第三步：对每个桶进行计数排序
  // 第四步：合并所有桶的结果，得到最终排序数组
  const output = [];
  
  for (let i = 0; i < bucketCount; i++) {
    if (buckets[i].length > 0) {
      // 使用独立的计数排序逻辑
      const bucket = buckets[i];
      
      // 找到最小值和最大值
      let min = bucket[0];
      let max = bucket[0];
      for (let j = 1; j < bucket.length; j++) {
        if (bucket[j] < min) min = bucket[j];
        if (bucket[j] > max) max = bucket[j];
      }
      
      // 创建计数数组
      const countListLen = max - min + 1;
      const countList = new Array(countListLen).fill(0);
      
      // 统计每个元素出现的次数
      for (let j = 0; j < bucket.length; j++) {
        const idx = bucket[j] - min;
        countList[idx] += 1;
      }
      
      // 计算累计计数
      for (let j = 1; j < countListLen; j++) {
        countList[j] += countList[j - 1];
      }
      
      // 从后向前遍历，保证稳定性
      const sortedBucket = new Array(bucket.length);
      for (let j = bucket.length - 1; j >= 0; j--) {
        const item = bucket[j] - min;
        const idx = countList[item] - 1;
        sortedBucket[idx] = item + min;
        countList[item] -= 1;
      }
      
      // 将排序后的桶内容添加到输出数组
      output.push(...sortedBucket);
    }
  }
  
  return output;
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含负数和重复元素的典型数组
const testData = [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80];

console.log("=== 计数排序算法演示 ===");
console.log("");

// 测试1：标准版本
performanceTest(countingSort1, testData, "countingSort1 standard");

// 测试2：内存优化版本
performanceTest(countingSort2, testData, "countingSort2 memory optimized");

// 测试3：负数处理版本
performanceTest(countingSort3, testData, "countingSort3 negative numbers");

// 测试4：桶优化版本
performanceTest(countingSort4, testData, "countingSort4 bucket optimized");

console.log("=== 算法对比总结 ===");
console.log("1. 标准版本：countingSort1 - 经典实现，稳定排序，支持负数");
console.log("2. 内存优化版本：countingSort2 - 简化流程，高效重建");
console.log("3. 负数处理版本：countingSort3 - 专门处理负数，分离排序");
console.log("4. 桶优化版本：countingSort4 - 多桶策略，适合大数据范围");

/* 打印结果
jarry@Mac countingsort % node counting_sort.js 
=== 计数排序算法演示 ===

countingSort1 standard原始数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
countingSort1 standard:
countList: [
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1
]
origin arr= [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
] output:= [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
countingSort1 standard: 1.625ms
countingSort1 standard排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

countingSort2 memory optimized原始数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
countingSort2 memory optimized:
countList: [
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1
]
i|val: 0 1
i|val: 10 1
i|val: 16 1
i|val: 19 1
i|val: 21 1
i|val: 23 1
i|val: 25 1
i|val: 30 1
i|val: 40 1
i|val: 90 1
origin arr= [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
] output:= [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
countingSort2 memory optimized: 0.264ms
countingSort2 memory optimized排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

countingSort3 negative numbers原始数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
countingSort3 negative numbers:
origin arr= [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
] output:= [
  -10,  0,  6,  9, 11,
   13, 15, 20, 30, 80
]
countingSort3 negative numbers: 0.115ms
countingSort3 negative numbers排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

countingSort4 bucket optimized原始数组: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]
countingSort4 bucket optimized:
countingSort4 bucket optimized: 0.071ms
countingSort4 bucket optimized排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：countingSort1 - 经典实现，稳定排序，支持负数
2. 内存优化版本：countingSort2 - 简化流程，高效重建
3. 负数处理版本：countingSort3 - 专门处理负数，分离排序
4. 桶优化版本：countingSort4 - 多桶策略，适合大数据范围
*/
