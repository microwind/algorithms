/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 希尔排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */
;(function () {

  /**
   * 打印数组内容的辅助函数
   * @param {number[]} arr - 要打印的数组
   * @param {string} label - 数组的标签说明
   */
  function printArray(arr, label) {
    console.log(`${label}: [${arr.join(', ')}]`)
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
    console.log('') // 空行分隔
  }

  // ==================== 主程序：算法演示和性能测试 ====================
  
  // 测试数据：
  const testData = [7, 11, 9, 10, 12, 13, 8];

  /**
   * 希尔排序基础版本 - 原始Shell序列
   * 
   * 算法原理：
   * 1. 选择一个增量序列，如 n/2, n/4, ..., 1
   * 2. 对每个增量进行插入排序，但只比较相距增量的元素
   * 3. 逐步减小增量，直到增量为1，此时数组基本有序
   * 4. 最后一次插入排序完成整个排序过程
   * 
   * 生活类比：就像整理一副扑克牌，先按间隔几张牌进行分组整理，
   * 然后逐步缩小间隔，最后对相邻的牌进行精细整理
   * 
   * 时间复杂度：平均O(n^1.3)，最坏O(n^2)，取决于增量序列
   * 空间复杂度：O(1) - 原地排序
   * 稳定性：不稳定 - 相距增量的元素交换可能改变相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function shellSort1(arr) {
    console.log('shellSort1 original sequence:')
    const n = arr.length;
    
    // 原始Shell序列：n/2, n/4, ..., 1
    for (let gap = Math.floor(n / 2); gap > 0; gap = Math.floor(gap / 2)) {
      // 对每个增量进行插入排序
      for (let i = gap; i < n; i++) {
        // 关键点：保存当前元素，与前面相距gap的元素比较
        const temp = arr[i];
        let j = i;
        
        // 向前查找插入位置
        while (j >= gap && arr[j - gap] > temp) {
          console.log('gap=' + gap + ' i=' + i + ' j=' + j + ' (j-gap)=' + (j - gap) + ' arr:' + arr)
          arr[j] = arr[j - gap];
          j -= gap;
        }
        
        // 插入元素
        arr[j] = temp;
      }
    }
    
    return arr;
  }

  /**
   * 希尔排序优化版本 - Knuth序列
   * 
   * 算法思路：
   * 使用Knuth提出的增量序列：1, 4, 13, 40, ...
   * 公式：gap = 3 * gap + 1，然后反向递减
   * 
   * 优化效果：
   * - 更好的增量序列，减少比较次数
   * - 理论上更优的时间复杂度
   * 
   * 时间复杂度：平均O(n^1.25)，比原始序列更优
   * 空间复杂度：O(1) - 原地排序
   * 稳定性：不稳定 - 插入排序的不稳定性继承
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function shellSort2(arr) {
    console.log('shellSort2 Knuth sequence:')
    const n = arr.length;
    
    // 计算初始增量（Knuth序列）
    let gap = 1;
    while (gap < n / 3) {
      gap = 3 * gap + 1; // 1, 4, 13, 40, 121, ...
    }
    
    // 反向递减处理
    for (; gap > 0; gap = Math.floor(gap / 3)) {
      // 对每个增量进行插入排序
      for (let i = gap; i < n; i++) {
        const temp = arr[i];
        let j = i - gap;
        
        // 向前查找插入位置
        for (; j >= 0 && arr[j] > temp; j -= gap) {
          console.log('gap=' + gap + ' i=' + i + ' j=' + j + ' (j+gap)=' + (j + gap) + ' arr:' + arr)
          arr[j + gap] = arr[j];
        }
        arr[j + gap] = temp;
      }
    }
    
    return arr;
  }

  /**
   * 希尔排序 - Hibbard序列
   * 
   * 算法思路：
   * 使用Hibbard序列：1, 3, 7, 15, 31, ...
   * 公式：gap = 2^k - 1
   * 
   * 优化效果：
   * - 更好的增量分布
   * - 理论时间复杂度为O(n^(3/2))
   * 
   * 时间复杂度：平均O(n^1.5)
   * 空间复杂度：O(1) - 原地排序
   * 稳定性：不稳定 - 插入排序的不稳定性继承
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function shellSort3(arr) {
    console.log('shellSort3 Hibbard sequence:')
    const n = arr.length;
    
    // 生成Hibbard序列
    const gaps = [];
    let k = 1;
    while ((Math.pow(2, k) - 1) < n) {
      gaps.push(Math.pow(2, k) - 1);
      k++;
    }
    
    // 反向使用序列
    for (let g = gaps.length - 1; g >= 0; g--) {
      const gap = gaps[g];
      
      // 对每个增量进行插入排序
      for (let i = gap; i < n; i++) {
        const temp = arr[i];
        let j;
        
        // 向前查找插入位置
        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
          arr[j] = arr[j - gap];
        }
        
        arr[j] = temp;
      }
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 希尔排序 - Sedgewick序列
   * 
   * 算法思路：
   * 使用Sedgewick序列：1, 5, 19, 41, 109, ...
   * 结合4^k + 3*2^(k-1) + 1和9*2^k - 9*2^(k/2) + 1
   * 
   * 优化效果：
   * - 最优的增量序列之一
   * - 更好的性能表现
   * 
   * 时间复杂度：平均O(n^1.25)，接近最优
   * 空间复杂度：O(1) - 原地排序
   * 稳定性：不稳定 - 插入排序的不稳定性继承
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function shellSort4(arr) {
    console.log('shellSort4 Sedgewick sequence:')
    const n = arr.length;
    
    // 生成Sedgewick序列
    const gaps = [];
    let k = 0;
    
    // 使用简化版本：1, 5, 19, 41, 109, 209, 505, 929, 2161
    const sedgewickGaps = [1, 5, 19, 41, 109, 209, 505, 929, 2161];
    for (let gap of sedgewickGaps) {
      if (gap < n) {
        gaps.push(gap);
      }
    }
    
    // 反向使用序列
    for (let g = gaps.length - 1; g >= 0; g--) {
      const gap = gaps[g];
      
      // 对每个增量进行插入排序
      for (let i = gap; i < n; i++) {
        const temp = arr[i];
        let j;
        
        // 向前查找插入位置
        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
          arr[j] = arr[j - gap];
        }
        
        arr[j] = temp;
      }
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 希尔排序 - 递归版本（尾递归实现）
   * 
   * 算法思路：
   * 递归处理增量（分组）序列，每个增量插入排序
   * 增量序列采用 Math.floor(gap/2)（希尔原始序列）
   * 
   * 递归结构：
   * - 外层尾递归：处理递减的增量序列
   * - 内层循环：对每个位置进行插入排序
   */
  function shellSort5(arr, gap) {
    // 递归终止条件
    if (gap <= 0) {
      return arr;
    }
    
    // 对当前增量（分组）进行插入排序
    const n = arr.length;
    for (let i = gap; i < n; i++) {
      const temp = arr[i];
      let j = i;
      
      // 向前查找插入位置
      while (j >= gap && arr[j - gap] > temp) {
        arr[j] = arr[j - gap];
        j -= gap;
      }
      
      // 插入到对应位置
      arr[j] = temp;
    }
    
    // 尾递归调用：递归是函数的最后操作
    return shellSort5(arr, Math.floor(gap / 2));
  }

  // ==================== 算法测试和性能对比 ====================
  
  // 测试1：原始Shell序列
  performanceTest(shellSort1, testData, '原始Shell序列');

  // 测试2：Knuth序列
  performanceTest(shellSort2, testData, 'Knuth序列');

  // 测试3：Hibbard序列
  performanceTest(shellSort3, testData, 'Hibbard序列');

  // 测试4：Sedgewick序列
  performanceTest(shellSort4, testData, 'Sedgewick序列');

  // 测试5：递归版本（尾递归）
  const result5 = shellSort5([...testData], Math.floor(testData.length / 2));
  console.log(`递归版本: [${result5}]`);

  console.log('=== 算法对比总结 ===')
  console.log('1. 原始Shell序列：简单实现，易于理解')
  console.log('2. Knuth序列：经典优化，性能提升')
  console.log('3. Hibbard序列：数学优化，理论更优')
  console.log('4. Sedgewick序列：最优序列，性能最佳')
  console.log('5. 递归版本：尾递归优化实现')

})();

/*打印结果
jarry@Mac shellsort % node shell_sort.js
原始Shell序列原始数组: [7, 11, 9, 10, 12, 13, 8]
shellSort1 original sequence:
gap=3 i=6 j=6 (j-gap)=3 arr:7,11,9,10,12,13,8
gap=1 i=2 j=2 (j-gap)=1 arr:7,11,9,8,12,13,10
gap=1 i=3 j=3 (j-gap)=2 arr:7,9,11,8,12,13,10
gap=1 i=3 j=2 (j-gap)=1 arr:7,9,11,11,12,13,10
gap=1 i=6 j=6 (j-gap)=5 arr:7,8,9,11,12,13,10
gap=1 i=6 j=5 (j-gap)=4 arr:7,8,9,11,12,13,13
gap=1 i=6 j=4 (j-gap)=3 arr:7,8,9,11,12,12,13
原始Shell序列: 0.106ms
原始Shell序列排序结果: [7, 8, 9, 10, 11, 12, 13]

Knuth序列原始数组: [7, 11, 9, 10, 12, 13, 8]
shellSort2 Knuth sequence:
gap=4 i=6 j=2 (j+gap)=6 arr:7,11,9,10,12,13,8
gap=1 i=2 j=1 (j+gap)=2 arr:7,11,8,10,12,13,9
gap=1 i=3 j=2 (j+gap)=3 arr:7,8,11,10,12,13,9
gap=1 i=6 j=5 (j+gap)=6 arr:7,8,10,11,12,13,9
gap=1 i=6 j=4 (j+gap)=5 arr:7,8,10,11,12,13,13
gap=1 i=6 j=3 (j+gap)=4 arr:7,8,10,11,12,12,13
gap=1 i=6 j=2 (j+gap)=3 arr:7,8,10,11,11,12,13
Knuth序列: 0.051ms
Knuth序列排序结果: [7, 8, 9, 10, 11, 12, 13]

Hibbard序列原始数组: [7, 11, 9, 10, 12, 13, 8]
shellSort3 Hibbard sequence:
[
   7,  8,  9, 10,
  11, 12, 13
]
Hibbard序列: 0.223ms
Hibbard序列排序结果: [7, 8, 9, 10, 11, 12, 13]

Sedgewick序列原始数组: [7, 11, 9, 10, 12, 13, 8]
shellSort4 Sedgewick sequence:
[
   7,  8,  9, 10,
  11, 12, 13
]
Sedgewick序列: 0.066ms
Sedgewick序列排序结果: [7, 8, 9, 10, 11, 12, 13]

递归版本: [7,8,9,10,11,12,13]
=== 算法对比总结 ===
1. 原始Shell序列：简单实现，易于理解
2. Knuth序列：经典优化，性能提升
3. Hibbard序列：数学优化，理论更优
4. Sedgewick序列：最优序列，性能最佳
5. 递归版本：尾递归优化实现
 */
