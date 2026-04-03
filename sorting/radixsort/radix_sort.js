/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */
;(function () {

  /**
   * 打印数组内容的辅助函数
   * @param {number[]} arr - 要打印的数组
   * @param {string} label - 数组的标签说明
   */
  function printArray(arr, label) {
    console.log(`${label}: [${arr.join(', ')}]`);
  }

  /**
   * 性能测试辅助函数
   * @param {Function} sortFunc - 排序函数
   * @param {number[]} arr - 测试数组
   * @param {string} name - 测试名称
   */
  function performanceTest(sortFunc, arr, name) {
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
  
  // 测试数据：包含大数字和负数的典型数组
  const testData = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431];

  /**
   * 获取数字的指定位数
   * @param {number} num - 数字
   * @param {number} exp - 指数（10的幂）
   * @return {number} 指定位数的值
   */
  function getDigit(num, exp) {
    return Math.floor(Math.abs(num) / exp) % 10;
  }

  /**
   * 计数排序辅助函数 - 按位数排序
   * @param {number[]} arr - 待排序数组
   * @param {number} exp - 指数（10的幂）
   */
  function countingSortByDigit(arr, exp) {
    const n = arr.length;
    const output = new Array(n);
    const count = new Array(10).fill(0);
    
    // 统计每个数字的出现次数
    for (let i = 0; i < n; i++) {
      const digit = getDigit(arr[i], exp);
      count[digit]++;
    }
    
    // 计算累计计数
    for (let i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }
    
    // 构建输出数组
    for (let i = n - 1; i >= 0; i--) {
      const digit = getDigit(arr[i], exp);
      output[count[digit] - 1] = arr[i];
      count[digit]--;
    }
    
    // 复制回原数组
    for (let i = 0; i < n; i++) {
      arr[i] = output[i];
    }
  }

  /**
   * 基数排序基础版本 - LSD（最低位优先）
   * 
   * 算法原理：
   * 1. 从个位开始，对每一位进行计数排序
   * 2. 逐步处理十位、百位、千位等
   * 3. 经过所有位数处理后，数组完全有序
   * 
   * 生活类比：就像整理学生成绩，先按个位数排序，
   * 再按十位数排序，最后按百位数排序，最终得到完整排序
   * 
   * 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
   * 空间复杂度：O(n + k) - 需要额外的计数和输出数组
   * 稳定性：稳定 - 计数排序保持相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function radixSort1(arr) {
    console.log('radixSort1 LSD:');
    
    // 找到最大值以确定位数
    const max = Math.max(...arr);
    
    // 对每个位数进行计数排序
    for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
      countingSortByDigit(arr, exp);
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 基数排序优化版本 - MSD（最高位优先）
   * 
   * 算法思路：
   * 从最高位开始排序，使用递归处理子数组
   * 适合处理字符串或变长数据
   * 
   * 优化效果：
   * - 更好的内存局部性
   * - 适合大数据集
   * 
   * 时间复杂度：O(d * (n + k))
   * 空间复杂度：O(n + k)
   * 稳定性：稳定
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function radixSort2(arr) {
    console.log('radixSort2 MSD:');
    
    /**
     * MSD递归排序函数
     * @param {number[]} arr - 待排序数组
     * @param {number} left - 左边界
     * @param {number} right - 右边界
     * @param {number} exp - 当前处理的位数
     */
    function msdSort(arr, left, right, exp) {
      if (left >= right || exp < 1) {
        return;
      }
      
      // 创建桶
      const buckets = Array.from({length: 10}, () => []);
      
      // 分配到桶中
      for (let i = left; i <= right; i++) {
        const digit = getDigit(arr[i], exp);
        buckets[digit].push(arr[i]);
      }
      
      // 重新排序并递归处理每个桶
      let index = left;
      for (let i = 0; i < 10; i++) {
        if (buckets[i].length > 0) {
          // 复制桶中元素回原数组
          for (let j = 0; j < buckets[i].length; j++) {
            arr[index++] = buckets[i][j];
          }
          
          // 递归处理下一个位数
          msdSort(arr, left, index - 1, exp / 10);
          left = index;
        }
      }
    }
    
    // 找到最大值以确定位数
    const max = Math.max(...arr);
    let exp = 1;
    while (Math.floor(max / exp) > 0) {
      exp *= 10;
    }
    
    msdSort(arr, 0, arr.length - 1, exp / 10);
    
    console.log(arr);
    return arr;
  }

  /**
   * 基数排序 - 迭代MSD版本
   * 
   * 算法思路：
   * 使用迭代方式实现MSD排序
   * 使用栈来模拟递归调用
   * 
   * 优化效果：
   * - 避免递归开销
   * - 更好的性能控制
   * 
   * 时间复杂度：O(d * (n + k))
   * 空间复杂度：O(n + k)
   * 稳定性：稳定
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function radixSort3(arr) {
    console.log('radixSort3 iterative MSD:');
    
    // 找到最大值以确定位数
    const max = Math.max(...arr);
    let exp = 1;
    while (Math.floor(max / exp) > 0) {
      exp *= 10;
    }
    
    // 使用栈模拟递归
    const stack = [{left: 0, right: arr.length - 1, exp: exp / 10}];
    
    while (stack.length > 0) {
      const {left, right, exp: currentExp} = stack.pop();
      
      if (left >= right || currentExp < 1) {
        continue;
      }
      
      // 创建桶
      const buckets = Array.from({length: 10}, () => []);
      
      // 分配到桶中
      for (let i = left; i <= right; i++) {
        const digit = getDigit(arr[i], currentExp);
        buckets[digit].push(arr[i]);
      }
      
      // 重新排序并将子问题入栈
      let index = left;
      for (let i = 0; i < 10; i++) {
        if (buckets[i].length > 0) {
          // 复制桶中元素回原数组
          for (let j = 0; j < buckets[i].length; j++) {
            arr[index++] = buckets[i][j];
          }
          
          // 将子问题入栈（逆序处理以保持正确顺序）
          stack.push({left: left, right: index - 1, exp: currentExp / 10});
          left = index;
        }
      }
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 基数排序 - 桶优化版本
   * 
   * 算法思路：
   * 使用动态桶大小，优化内存使用
   * 适合处理稀疏数据
   * 
   * 优化效果：
   * - 减少内存占用
   * - 提高处理效率
   * 
   * 时间复杂度：O(d * (n + k))
   * 空间复杂度：O(n + k)
   * 稳定性：稳定
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function radixSort4(arr) {
    console.log('radixSort4 bucket optimized:');
    
    // 找到最大值以确定位数
    const max = Math.max(...arr);
    
    // 对每个位数进行计数排序
    for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
      const n = arr.length;
      const output = new Array(n);
      
      // 动态确定桶范围
      let minDigit = 9, maxDigit = 0;
      for (let i = 0; i < n; i++) {
        const digit = getDigit(arr[i], exp);
        minDigit = Math.min(minDigit, digit);
        maxDigit = Math.max(maxDigit, digit);
      }
      
      const bucketSize = maxDigit - minDigit + 1;
      const count = new Array(bucketSize).fill(0);
      
      // 统计每个数字的出现次数
      for (let i = 0; i < n; i++) {
        const digit = getDigit(arr[i], exp);
        count[digit - minDigit]++;
      }
      
      // 计算累计计数
      for (let i = 1; i < bucketSize; i++) {
        count[i] += count[i - 1];
      }
      
      // 构建输出数组
      for (let i = n - 1; i >= 0; i--) {
        const digit = getDigit(arr[i], exp);
        output[count[digit - minDigit] - 1] = arr[i];
        count[digit - minDigit]--;
      }
      
      // 复制回原数组
      for (let i = 0; i < n; i++) {
        arr[i] = output[i];
      }
    }
    
    console.log(arr);
    return arr;
  }

  // ==================== 算法测试和性能对比 ====================
  
  // 测试1：LSD版本
  performanceTest(radixSort1, testData, 'LSD版本');

  // 测试2：MSD版本
  performanceTest(radixSort2, testData, 'MSD版本');

  // 测试3：迭代MSD版本
  performanceTest(radixSort3, testData, '迭代MSD版本');

  // 测试4：桶优化版本
  performanceTest(radixSort4, testData, '桶优化版本');

  console.log('=== 算法对比总结 ===');
  console.log('1. LSD版本：经典实现，从低到高');
  console.log('2. MSD版本：高位优先，递归处理');
  console.log('3. 迭代MSD版本：避免递归，性能稳定');
  console.log('4. 桶优化版本：动态桶大小，内存优化');

})();
