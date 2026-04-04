/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
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
   * 选择排序基础版本 - 标准版：原地交换
   *
   * 算法原理：
   * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
   * 2. 每次从待排序区域中选择最小元素
   * 3. 将最小元素与待排序区域的第一个元素交换
   * 4. 重复以上过程，直到所有元素排序完成
   *
   * ## 实现步骤
   * 1. 外循环遍历数组，每轮确定一个最小值的位置
   * 2. 内循环在未排序区域中查找最小元素
   * 3. 记录最小值和其索引位置
   * 4. 将最小元素交换到当前轮次的起始位置
   *
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function selectionSort1(arr) {
    console.log('selectionSort1 basic:');
    var min, minIdx, tmp
    var arrLen = arr.length
    
    // 外循环：每轮确定一个最小值
    for (var i = 0; i < arrLen - 1; i++) {
      // 假设当前位置为最小值
      min = arr[i]
      minIdx = i
      var j = i + 1
      
      // 内循环：在未排序区域查找最小值
      for (; j < arrLen; j++) {
        if (arr[j] < min) {
          min = arr[j]
          minIdx = j
        }
      }
      
      // 输出调试信息
      console.log('i=' + i, ' j=' + j, 'min=' + min, 'minIdx=' + minIdx, 'arr[]=', arr)
      
      // 交换最小值到正确位置
      if (minIdx !== i) {
        tmp = arr[i]
        arr[i] = min
        arr[minIdx] = tmp
      }
    }
    return arr
  }

  /**
   * 选择排序新建数组版本 - 无需交换
   *
   * 算法思路：
   * 1. 创建一个新数组来存储排序结果
   * 2. 每次从原数组中找到最小值
   * 3. 将最小值添加到新数组
   * 4. 从原数组中删除该最小值
   * 5. 重复直到原数组为空
   *
   * ## 实现步骤
   * 1. 初始化新数组和索引
   * 2. 外循环控制选择轮数
   * 3. 内循环查找当前最小值
   * 4. 将最小值添加到新数组
   * 5. 从原数组中移除已选择的元素
   * 6. 调整循环变量以适应数组长度变化
   *
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的新数组
   */
  function selectionSort2(arr) {
    console.log('selectionSort2 new array:');
    var min, minIdx
    var newArr = []
    var arrLen = arr.length
    
    // 外循环：每轮选择一个最小值
    for (var i = 0; i < arrLen; i++) {
      // 假设当前位置为最小值
      min = arr[i]
      minIdx = i
      let j = i + 1
      
      // 内循环：在剩余元素中查找最小值
      for (; j < arrLen; j++) {
        if (arr[j] < min) {
          min = arr[j]
          minIdx = j
        }
      }
      
      // 输出调试信息
      console.log('i=' + i, ' j=' + j, 'min=' + min, 'minIdx=' + minIdx, 'arr[]=', arr)
      
      // 添加最小值到新数组
      newArr.push(min)
      
      // 从原数组中移除已选择的元素
      arr.splice(minIdx, 1)
      arrLen--
      i--
    }
    return newArr
  }

  /**
   * 选择排序降序版本
   *
   * 算法思路：
   * 与基础版本相反，每次选择最大元素
   * 将最大元素与待排序区域的第一个元素交换
   *
   * ## 实现步骤
   * 1. 外循环控制排序轮数，每轮确定一个最大值的位置
   * 2. 内循环在未排序区域中查找最大元素
   * 3. 记录最大值和其索引位置
   * 4. 将最大元素交换到当前轮次的起始位置
   *
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function selectionSort3(arr) {
    console.log('selectionSort3 descending:');
    const len = arr.length;
    
    // 外循环：每轮确定一个最大值
    for (let i = 0; i < len - 1; i++) {
      // 假设当前位置为最大值
      let maxIndex = i;
      
      // 内循环：在未排序区域查找最大值
      for (let j = i + 1; j < len; j++) {
        if (arr[j] > arr[maxIndex]) {
          maxIndex = j;
        }
      }
      
      // 交换最大元素到正确位置
      if (maxIndex !== i) {
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
   * ## 实现步骤
   * 1. 初始化左右边界指针
   * 2. 外循环控制排序轮数，同时处理两端
   * 3. 内循环在未排序区域中查找最小和最大元素
   * 4. 交换最小元素到左侧，最大元素到右侧
   * 5. 调整边界指针
   */
  function selectionSort4(arr) {
    console.log('selectionSort4 bidirectional:');
    const len = arr.length;
    let left = 0;
    let right = len - 1;
    
    // 外循环：同时处理左右两端
    while (left < right) {
      let minIndex = left;
      let maxIndex = left;
      
      // 内循环：同时查找最小和最大元素
      for (let i = left; i <= right; i++) {
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
      
      // 处理最大元素位置变化的特殊情况
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
   * ## 实现步骤
   * 1. 构建最大堆
   * 2. 逐个取出堆顶元素（最大值）
   * 3. 将堆顶元素与末尾元素交换
   * 4. 重新调整堆结构
   * 5. 重复直到堆为空
   */
  function selectionSort5(arr) {
    console.log('selectionSort5 heap optimized:');
    const len = arr.length;
    
    // 构建最大堆
    for (let i = Math.floor(len / 2) - 1; i >= 0; i--) {
      heapify(arr, len, i);
    }
    
    // 逐个取出堆顶元素
    for (let i = len - 1; i > 0; i--) {
      // 交换堆顶与末尾元素
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

  console.log('\n=== 算法性能对比 ===');
  
  // 测试1：基础选择版本
  performanceTest(selectionSort1, testData, '基础选择版本');

  // 测试2：新建数组版本
  performanceTest(selectionSort2, testData, '新建数组版本');

  // 测试3：降序版本
  performanceTest(selectionSort3, testData, '降序版本');

  // 测试4：双向选择版本
  performanceTest(selectionSort4, testData, '双向选择版本');

  // 测试5：堆优化版本
  performanceTest(selectionSort5, testData, '堆优化版本');

  console.log('=== 算法对比总结 ===');
  console.log('1. 基础版本：标准版，原地交换，包含详细调试信息');
  console.log('2. 新建数组版本：无需交换，避免交换操作');
  console.log('3. 降序版本：展示算法灵活性，可按需排序');
  console.log('4. 双向版本：同时选择最大最小，效率提升');
  console.log('5. 堆优化版本：利用堆结构，复杂度优化');

})();

/*打印结果
jarry@Mac selectionsort % node selection_sort.js

=== 算法性能对比 ===
基础选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort1 basic:
i=0  j=7 min=7 minIdx=0 arr[]= [
   7, 11, 9, 10,
  12, 13, 8
]
i=1  j=7 min=8 minIdx=6 arr[]= [
   7, 11, 9, 10,
  12, 13, 8
]
i=2  j=7 min=9 minIdx=2 arr[]= [
   7,  8,  9, 10,
  12, 13, 11
]
i=3  j=7 min=10 minIdx=3 arr[]= [
   7,  8,  9, 10,
  12, 13, 11
]
i=4  j=7 min=11 minIdx=6 arr[]= [
   7,  8,  9, 10,
  12, 13, 11
]
i=5  j=7 min=12 minIdx=6 arr[]= [
   7,  8,  9, 10,
  11, 13, 12
]
基础选择版本: 1.087ms
基础选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

新建数组版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort2 new array:
i=0  j=7 min=7 minIdx=0 arr[]= [
   7, 11, 9, 10,
  12, 13, 8
]
i=0  j=6 min=8 minIdx=5 arr[]= [ 11, 9, 10, 12, 13, 8 ]
i=0  j=5 min=9 minIdx=1 arr[]= [ 11, 9, 10, 12, 13 ]
i=0  j=4 min=10 minIdx=1 arr[]= [ 11, 10, 12, 13 ]
i=0  j=3 min=11 minIdx=0 arr[]= [ 11, 12, 13 ]
i=0  j=2 min=12 minIdx=0 arr[]= [ 12, 13 ]
i=0  j=1 min=13 minIdx=0 arr[]= [ 13 ]
新建数组版本: 0.21ms
新建数组版本排序结果: []

降序版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort3 descending:
[
  13, 12, 11, 10,
   9,  8,  7
]
降序版本: 0.052ms
降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort4 bidirectional:
[
   7,  8,  9, 10,
  11, 12, 13
]
双向选择版本: 0.053ms
双向选择版本排序结果: [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: [7, 11, 9, 10, 12, 13, 8]
selectionSort5 heap optimized:
[
   7,  8,  9, 10,
  11, 12, 13
]
堆优化版本: 0.069ms
堆优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：标准版，原地交换，包含详细调试信息
2. 新建数组版本：无需交换，避免交换操作
3. 降序版本：展示算法灵活性，可按需排序
4. 双向版本：同时选择最大最小，效率提升
5. 堆优化版本：利用堆结构，复杂度优化
*/