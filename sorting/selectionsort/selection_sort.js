/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
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
  
  // 测试数据：
  const testData = [7, 11, 9, 10, 12, 13, 8];

  /**
   * 选择排序基础版本
   * 
   * 算法原理：
   * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
   * 2. 每次从待排序区域中选择最小元素
   * 3. 将最小元素与待排序区域的第一个元素交换
   * 4. 重复以上过程，直到所有元素排序完成
   * 
   * 生活类比：就像在队伍中挑选最矮的人站到最前面，
   * 然后在剩下的人中再挑选最矮的站到第二个位置，依此类推
   * 
   * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
   * 空间复杂度：O(1) - 只使用常数个额外变量
   * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function selectionSort1(arr) {
    console.log('selectionSort1 basic:');
    const len = arr.length;
    // 外循环：控制排序轮数，每轮确定一个最小值的位置
    for (let i = 0; i < len - 1; i++) {
      let minIndex = i; // 记录最小元素的索引
      
      // 内循环：在未排序区域中查找最小元素
      for (let j = i + 1; j < len; j++) {
        // 关键点：找到更小的元素，更新最小值索引
        if (arr[j] < arr[minIndex]) {
          minIndex = j;
        }
      }
      
      // 交换最小元素到当前轮次的起始位置
      if (minIndex !== i) {
        // JS特点：解构赋值交换
        [arr[i], arr[minIndex]] = [arr[minIndex], arr[i]];
      }
    }
    console.log(arr);
    return arr;
  }

  /**
   * 选择排序降序版本
   * 
   * 算法思路：
   * 与基础版本相反，每次选择最大元素
   * 将最大元素与待排序区域的第一个元素交换
   * 
   * 时间复杂度：O(n²) - 需要比较 n*(n-1)/2 次
   * 空间复杂度：O(1) - 只使用常数个额外变量
   * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function selectionSort2(arr) {
    console.log('selectionSort2 descending:');
    const len = arr.length;
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for (let i = 0; i < len - 1; i++) {
      let maxIndex = i; // 记录最大元素的索引
      
      // 内循环：在未排序区域中查找最大元素
      for (let j = i + 1; j < len; j++) {
        // 关键点：找到更大的元素，更新最大值索引
        if (arr[j] > arr[maxIndex]) {
          maxIndex = j;
        }
      }
      
      // 交换最大元素到当前轮次的起始位置
      if (maxIndex !== i) {
        // JS特点：解构赋值交换
        [arr[i], arr[maxIndex]] = [arr[maxIndex], arr[i]];
      }
    }
    console.log(arr);
    return arr;
  }

  /**
   * 选择排序优化版本 - 双向选择
   * 
   * 优化思路：
   * 每轮同时选择最小和最大元素
   * 将最小元素放到左侧，最大元素放到右侧
   * 减少排序轮数，提高效率
   * 
   * 优化效果：
   * - 减少了排序轮数，从n轮减少到n/2轮
   * - 每轮需要进行两次查找，但总体效率提升
     * 
   * 时间复杂度：O(n²)，空间复杂度：O(1)
   * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function selectionSort3(arr) {
    console.log('selectionSort3 bidirectional:');
    const len = arr.length;
    let left = 0;
    let right = len - 1;
    
    // 外循环：控制排序轮数，每轮确定最小和最大值的位置
    while (left < right) {
      let minIndex = left;
      let maxIndex = left;
      
      // 内循环：在未排序区域中查找最小和最大元素
      for (let i = left; i <= right; i++) {
        // 关键点：同时查找最小和最大元素
        if (arr[i] < arr[minIndex]) {
          minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
          maxIndex = i;
        }
      }
      
      // 交换最小元素到左侧
      if (minIndex !== left) {
        [arr[left], arr[minIndex]] = [arr[minIndex], arr[left]];
      }
      
      // 优化点：如果最大元素原本在left位置，经过交换后位置变为minIndex
      if (maxIndex === left) {
        maxIndex = minIndex;
      }
      
      // 交换最大元素到右侧
      if (maxIndex !== right) {
        [arr[right], arr[maxIndex]] = [arr[maxIndex], arr[right]];
      }
      
      left++;
      right--;
    }
    console.log(arr);
    return arr;
  }

  /**
   * 选择排序 - 堆优化版本
   * 
   * 算法思路：
   * 利用堆的性质来快速找到最大/最小元素
   * 每次从堆顶取出最大/最小元素
   * 重新调整堆结构
   * 
   * 时间复杂度：O(n log n)，空间复杂度：O(1)
   * 稳定性：不稳定 - 交换可能改变相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function selectionSort4(arr) {
    console.log('selectionSort4 heap optimized:');
    const len = arr.length;
    
    // 构建最大堆
    for (let i = Math.floor(len / 2) - 1; i >= 0; i--) {
      heapify(arr, len, i);
    }
    
    // 逐个取出堆顶元素
    for (let i = len - 1; i > 0; i--) {
      // 关键点：交换堆顶元素（最大）与末尾元素
      [arr[0], arr[i]] = [arr[i], arr[0]];
      
      // 重新调整堆
      heapify(arr, i, 0);
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 堆化辅助函数
   * @param {number[]} arr - 数组
   * @param {number} n - 堆大小
   * @param {number} i - 当前节点索引
   */
  function heapify(arr, n, i) {
    let largest = i; // 初始化最大元素为根节点
    const left = 2 * i + 1; // 左子节点
    const right = 2 * i + 2; // 右子节点
    
    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest]) {
      largest = left;
    }
    
    // 如果右子节点大于当前最大节点
    if (right < n && arr[right] > arr[largest]) {
      largest = right;
    }
    
    // 如果最大节点不是根节点，交换并继续堆化
    if (largest !== i) {
      [arr[i], arr[largest]] = [arr[largest], arr[i]];
      heapify(arr, n, largest);
    }
  }

  // ==================== 算法测试和性能对比 ====================
  
  // 测试1：基础选择版本
  performanceTest(selectionSort1, testData, '基础选择版本');

  // 测试2：降序版本
  performanceTest(selectionSort2, testData, '降序版本');

  // 测试3：双向选择版本
  performanceTest(selectionSort3, testData, '双向选择版本');

  // 测试4：堆优化版本
  performanceTest(selectionSort4, testData, '堆优化版本');

  console.log('=== 算法对比总结 ===');
  console.log('1. 基础版本：简单易懂，适合学习算法原理');
  console.log('2. 降序版本：展示算法灵活性，可按需排序');
  console.log('3. 双向版本：同时选择最大最小，效率提升');
  console.log('4. 堆优化版本：利用堆结构，复杂度优化');

})();

/* 打印结果
jarry@Mac selectionsort % node selection_sort.js
基础选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort1 basic:
[
   7,  8,  9, 10,
  11, 12, 13
]
基础选择版本: 1.461ms
基础选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort2 descending:
[
  13, 12, 11, 10,
   9,  8,  7
]
降序版本: 0.115ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort3 bidirectional:
[
   7,  8,  9, 10,
  11, 12, 13
]
双向选择版本: 0.104ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort4 heap optimized:
[
   7,  8,  9, 10,
  11, 12, 13
]
堆优化版本: 0.095ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法灵活性，可按需排序
3. 双向版本：同时选择最大最小，效率提升
4. 堆优化版本：利用堆结构，复杂度优化
*/
