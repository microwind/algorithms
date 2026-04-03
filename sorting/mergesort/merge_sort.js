/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 归并排序算法实现
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
  const testData = [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4];

  /**
   * 归并排序基础版本 - 递归实现（基于索引范围）
   * 
   * 算法原理：
   * 1. 分解（Divide），把待排序元素的序列分解为两个子序列，以中间2分, 每个子序列包括一半成员。
   * 2. 解决（Conquer），对每个子序列分别调用归并操作, 进行递归或非递归循环操作，完成内部排序。
   * 3. 合并（Combine），合并两个排好序的子序列，生成排序结果。 归并排序的最坏时间复杂度和平均时间复杂度均为O(nlogn)
   * 
   * 时间复杂度：O(n log n)
   * 空间复杂度：O(n) - 需要额外空间存储临时数组
   * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function mergeSort1(arr) {
    console.log('mergeSort1 recursive (index-based):');
    
    /**
     * 将两个有序数组合并为一个新的有序数组
     * @param {number[]} arr - 原数组
     * @param {number} left - 左边界索引
     * @param {number} mid - 中间索引
     * @param {number} right - 右边界索引
     */
    function merge(arr, left, mid, right) {
      // 步骤1：建立临时数组
      // 关键点：临时数组用于存储合并过程中的有序结果
      const temp = [];
      
      // 步骤2：初始化指针
      // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
      let i = left;      // 左侧指针
      let j = mid + 1;   // 右侧指针
      let k = 0;         // 临时数组指针
      
      // 步骤3：合并两个有序子数组
      // 关键点：当左指针小于中间，且右指针不大于最右侧时
      while (i <= mid && j <= right) {
        // 步骤3.1：比较左右子数组的当前元素
        // 关键点：选择较小的元素放入临时数组
        if (arr[i] <= arr[j]) {
          temp[k++] = arr[i++];  // 左侧元素较小，移动到临时数组左侧
        } else {
          temp[k++] = arr[j++];  // 右侧元素较小，移动到临时数组右侧
        }
      }
      
      // 步骤4：处理左子数组剩余元素
      // 关键点：如果左边数组还有数据，就把左侧剩余都放入到原数组后面
      while (i <= mid) {
        temp[k++] = arr[i++];
      }
      
      // 步骤5：处理右子数组剩余元素
      // 关键点：如果右侧数组还有数据，把剩下的数据放入到原数组后面
      while (j <= right) {
        temp[k++] = arr[j++];
      }
      
      // 步骤6：将排序后的元素复制回原数组
      // 关键点：将临时数组的有序结果复制回原数组的对应位置
      let x = 0;
      while (left <= right) {
        arr[left++] = temp[x++];
      }
    }
    
    /**
     * 递归归并排序函数
     * @param {number[]} arr - 待排序数组
     * @param {number} left - 左边界索引
     * @param {number} right - 右边界索引
     * @returns {number[]} 排序后的数组
     */
    function mergeSort(arr, left, right) {
      // 步骤1：计算中间值
      // 关键点：使用Math.floor避免浮点数问题
      const mid = Math.floor((left + right) / 2);
      
      // 步骤2：检查递归终止条件
      // 关键点：只有当左侧小于右侧时才执行合并排序
      if (left < right) {
        // 步骤3：递归排序左半部分
        // 关键点：处理范围 [left, mid]
        mergeSort(arr, left, mid);
        
        // 步骤4：递归排序右半部分
        // 关键点：处理范围 [mid+1, right]
        mergeSort(arr, mid + 1, right);
        
        // 步骤5：合并左右结果
        // 关键点：将两个有序子数组合并为一个更大的有序子数组
        merge(arr, left, mid, right);
      }
      return arr;
    }
    
    const result = mergeSort(arr, 0, arr.length - 1);
    printArray(arr, '排序后数组');
    return result;
  }

  /**
   * 归并排序优化版本 - 利用JS语言特点实现
   * 
   * 算法思路：
   * 利用JavaScript的slice和shift等数组方法，实现更简洁的归并排序
   * 通过函数式编程思想，减少索引操作，提高代码可读性
   * 
   * 优化效果：
   * - 代码更简洁易懂
   * - 充分利用JS语言特性
   * - 函数式编程风格
   * 
   * 时间复杂度：O(n log n)
   * 空间复杂度：O(n) - 需要额外空间存储临时数组
   * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function mergeSort2(arr) {
    console.log('mergeSort2 JavaScript-style:');
    
    /**
     * 递归归并排序函数
     * @param {number[]} arr - 待排序数组
     * @returns {number[]} 排序后的数组
     */
    function mergeSort(arr) {
      // 步骤1：检查递归终止条件
      // 关键点：数组长度小于2时已经有序，直接返回
      const len = arr.length;
      if (len < 2) {
        return arr;
      }
      
      // 步骤2：分解数组
      // 关键点：取得当前数组的中间位置，将数组分为两半
      const mid = Math.floor(len / 2);
      const left = arr.slice(0, mid);   // 左半部分
      const right = arr.slice(mid);     // 右半部分
      
      // 步骤3：递归调用
      // 关键点：递归调用，不断重复直到当前数组拆分剩1项
      // JavaScript特点：使用slice创建新数组，避免修改原数组
      return merge(mergeSort(left), mergeSort(right));
    }
    
    /**
     * 将两个有序数组进行合并为一个新的有序数组
     * @param {number[]} left - 左侧有序数组
     * @param {number[]} right - 右侧有序数组
     * @returns {number[]} 合并后的有序数组
     */
    function merge(left, right) {
      // 步骤1：建立结果数组
      // 关键点：建立一个空数组，用来存放排序结果
      const result = [];
      
      // 步骤2：合并两个有序数组
      // 关键点：左右数组的长度都不为空时，则将两个数组的第一个进行比较
      while (left.length && right.length) {
        // 步骤2.1：比较首元素
        // 关键点：如左侧小于右，则移除左侧的内容到结果数据，反之移动右侧成员
        if (left[0] <= right[0]) {
          result.push(left.shift());  // JavaScript特点：shift移除并返回首元素
        } else {
          result.push(right.shift()); // JavaScript特点：shift移除并返回首元素
        }
      }
      
      // 步骤3：处理左数组剩余元素
      // 关键点：最后把剩余的左或者右侧成员全部添加到结果数组
      while (left.length) {
        result.push(left.shift());
      }
      
      // 步骤4：处理右数组剩余元素
      // 关键点：确保所有元素都被处理
      while (right.length) {
        result.push(right.shift());
      }
      
      // 步骤5：返回合并结果
      // 关键点：这样一趟下来后，两个数组就合并为一个新的排序数组
      return result;
    }
    
    const result = mergeSort(arr);
    printArray(result, '排序后数组');
    return result;
  }

  /**
   * 归并排序 - 迭代版本
   * 
   * 算法思路：
   * 使用迭代方式代替递归，避免递归栈开销
   * 从小规模合并开始，逐步扩大合并规模
   * 
   * 优化效果：
   * - 避免了递归调用的开销
   * - 更好的缓存局部性
   * 
   * 时间复杂度：O(n log n)
   * 空间复杂度：O(n) - 需要临时数组
   * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function mergeSort3(arr) {
    console.log('mergeSort3 iterative:');
    
    /**
     * 合并两个有序子数组
     * @param {number[]} arr - 原数组
     * @param {number[]} temp - 临时数组
     * @param {number} left - 左边界
     * @param {number} mid - 中间索引
     * @param {number} right - 右边界
     */
    function merge(arr, temp, left, mid, right) {
      // 步骤1：初始化索引指针
      // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
      let i = left; // 左子数组索引
      let j = mid + 1; // 右子数组索引
      let k = left; // 临时数组索引
      
      // 步骤2：合并到临时数组
      // 关键点：按顺序将较小的元素放入临时数组
      while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
          temp[k] = arr[i];
          i++;
        } else {
          temp[k] = arr[j];
          j++;
        }
        k++;
      }
      
      // 步骤3：复制左子数组剩余元素
      // 关键点：左子数组可能还有未处理的元素
      while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
      }
      
      // 步骤4：复制右子数组剩余元素
      // 关键点：右子数组可能还有未处理的元素
      while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
      }
      
      // 步骤5：将临时数组复制回原数组
      // 关键点：将合并结果复制回原数组的对应位置
      for (let index = left; index <= right; index++) {
        arr[index] = temp[index];
      }
    }
    
    const n = arr.length;
    const temp = new Array(n);
    
    // 步骤1：初始化合并步长
    // 关键点：从单个元素开始，步长逐步翻倍
    for (let size = 1; size < n; size *= 2) {
      // 步骤2：遍历数组，合并相邻子数组
      // 关键点：每次合并两个大小为size的相邻子数组
      for (let left = 0; left < n - size; left += 2 * size) {
        // 步骤3：计算合并范围
        // 关键点：确定左、中、右边界
        const mid = left + size - 1;
        let right = left + 2 * size - 1;
        if (right >= n) {
          right = n - 1;
        }
        
        // 步骤4：执行合并操作
        // 关键点：将两个有序子数组合并为一个更大的有序子数组
        merge(arr, temp, left, mid, right);
      }
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 归并排序 - 自底向上版本
   * 
   * 算法思路：
   * 先将数组分成单个元素，然后两两合并
   * 逐步扩大合并规模，直到整个数组有序
   * 
   * 优化效果：
   * - 更好的内存访问模式
   * - 适合外部排序（处理大数据）
   * 
   * 时间复杂度：O(n log n)
   * 空间复杂度：O(n) - 需要临时数组
   * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function mergeSort4(arr) {
    console.log('mergeSort4 bottom-up:');
    
    /**
     * 合并两个相邻的有序子数组
     * @param {number[]} arr - 原数组
     * @param {number[]} temp - 临时数组
     * @param {number} left - 左边界
     * @param {number} mid - 中间索引
     * @param {number} right - 右边界
     */
    function merge(arr, temp, left, mid, right) {
      // 步骤1：初始化索引指针
      // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
      let i = left;
      let j = mid;
      let k = left;
      
      // 步骤2：合并两个有序子数组到临时数组
      // 关键点：按顺序将较小的元素放入临时数组
      while (i < mid && j <= right) {
        if (arr[i] <= arr[j]) {
          temp[k] = arr[i];
          i++;
        } else {
          temp[k] = arr[j];
          j++;
        }
        k++;
      }
      
      // 步骤3：复制左子数组剩余元素
      // 关键点：左子数组可能还有未处理的元素
      while (i < mid) {
        temp[k] = arr[i];
        i++;
        k++;
      }
      
      // 步骤4：复制右子数组剩余元素
      // 关键点：右子数组可能还有未处理的元素
      while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
      }
      
      // 步骤5：复制回原数组
      // 关键点：将合并结果复制回原数组的对应位置
      for (let index = left; index <= right; index++) {
        arr[index] = temp[index];
      }
    }
    
    const n = arr.length;
    const temp = new Array(n);
    
    // 步骤1：初始化合并宽度
    // 关键点：从宽度1开始，逐步扩大合并范围
    for (let width = 1; width < n; width *= 2) {
      // 步骤2：按宽度遍历数组
      // 关键点：每次处理2*width大小的区间
      for (let i = 0; i < n; i += 2 * width) {
        // 步骤3：计算当前合并区间的边界
        // 关键点：确定左、中、右边界
        const left = i;
        let mid = i + width;
        if (mid > n) {
          mid = n;
        }
        let right = i + 2 * width;
        if (right > n) {
          right = n;
        }
        
        // 步骤4：检查是否需要合并
        // 关键点：只有当mid < right时才进行合并
        if (mid < right) {
          // 步骤5：执行合并操作
          // 关键点：合并 [left, mid-1] 和 [mid, right-1]
          merge(arr, temp, left, mid, right - 1);
        }
      }
    }
    
    console.log(arr);
    return arr;
  }

  /**
   * 归并排序 - 非递归合并版本
   * 
   * 算法思路：
   * 使用非递归方式进行合并操作，避免递归调用
   * 通过迭代方式处理合并过程，提高内存效率
   * 
   * 优化效果：
   * - 避免递归栈开销
   * - 更好的内存访问模式
   * - 适合大数据处理
   * 
   * 时间复杂度：O(n log n)
   * 空间复杂度：O(n) - 需要临时数组
   * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
   * 
   * @param {number[]} arr - 待排序的数字数组
   * @returns {number[]} 排序后的数组
   */
  function mergeSort5(arr) {
    console.log('mergeSort5 non-recursive merge:');
    
    // 非递归合并两个有序子数组
    const mergeNonRecursive = (arr, temp, left, mid, right) => {
      // 步骤1：初始化索引指针
      // 关键点：i指向左子数组，j指向右子数组，k指向临时数组
      let i = left;      // 左子数组索引
      let j = mid + 1;   // 右子数组索引
      let k = left;      // 临时数组索引
      
      // 步骤2：合并到临时数组
      // 关键点：按顺序合并两个有序子数组
      while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
          temp[k] = arr[i];
          i++;
        } else {
          temp[k] = arr[j];
          j++;
        }
        k++;
      }
      
      // 步骤3：复制左子数组剩余元素
      // 关键点：左子数组可能还有未处理的元素
      while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
      }
      
      // 步骤4：复制右子数组剩余元素
      // 关键点：右子数组可能还有未处理的元素
      while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
      }
      
      // 步骤5：将临时数组复制回原数组
      // 关键点：使用循环逐个复制，确保数据正确性
      // JavaScript特点：也可以使用slice和concat，但循环更直观
      for (let index = left; index <= right; index++) {
        arr[index] = temp[index];
      }
    };
    
    const n = arr.length;
    if (n <= 1) {
      return arr;
    }
    
    // 步骤1：创建临时数组
    // 关键点：临时数组用于存储合并过程中的中间结果
    const temp = new Array(n);
    
    // 步骤2：非递归合并过程
    // 关键点：通过迭代方式模拟递归的合并过程
    for (let size = 1; size < n; size *= 2) {
      // 步骤3：处理所有相邻的子数组对
      // 关键点：每次处理两个大小为size的相邻子数组
      for (let left = 0; left < n - size; left += 2 * size) {
        // 步骤4：计算当前合并的边界
        // 关键点：确定左子数组 [left, mid] 和右子数组 [mid+1, right]
        const mid = left + size - 1;
        let right = left + 2 * size - 1;
        if (right >= n) {
          right = n - 1;
        }
        
        // 步骤5：执行非递归合并
        // 关键点：使用迭代方式合并两个有序子数组
        mergeNonRecursive(arr, temp, left, mid, right);
      }
    }
    
    printArray(arr, '排序后数组');
    return arr;
  }

// ==================== 算法测试和性能对比 ====================
  function main() {
    // 测试1：递归版本（基于索引范围）
    performanceTest(mergeSort1, testData, '递归版本（基于索引范围）');

    // 测试2：JavaScript风格版本
    performanceTest(mergeSort2, testData, 'JavaScript风格版本');

    // 测试3：迭代版本
    performanceTest(mergeSort3, testData, '迭代版本');

    // 测试4：自底向上版本
    performanceTest(mergeSort4, testData, '自底向上版本');

    // 测试5：非递归合并版本
    performanceTest(mergeSort5, testData, '非递归合并版本');

    console.log('=== 算法对比总结 ===');
    console.log('1. 递归版本（基于索引范围）：经典实现，基于索引操作');
    console.log('2. JavaScript风格版本：利用JS语言特性，代码简洁');
    console.log('3. 迭代版本：避免递归，性能稳定');
    console.log('4. 底向上版本：适合大数据，外部排序');
    console.log('5. 非递归合并版本：迭代合并，高效内存');
  }

  main();

})();

/* 打印结果
jarry@Mac mergesort % node merge_sort.js
递归版本（基于索引范围）原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort1 recursive (index-based):
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
递归版本（基于索引范围）: 0.125ms
递归版本（基于索引范围）排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

JavaScript风格版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort2 JavaScript-style:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
JavaScript风格版本: 0.083ms
JavaScript风格版本排序结果: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort3 iterative:
[
   1, 2, 3,  4,  5,  6,
   7, 8, 9, 10, 11, 12,
  13
]
迭代版本: 0.455ms
迭代版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort4 bottom-up:
[
   1, 2, 3,  4,  5,  6,
   7, 8, 9, 10, 11, 12,
  13
]
自底向上版本: 0.088ms
自底向上版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

非递归合并版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort5 non-recursive merge:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
非递归合并版本: 0.051ms
非递归合并版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本（基于索引范围）：经典实现，基于索引操作
2. JavaScript风格版本：利用JS语言特性，代码简洁
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 非递归合并版本：迭代合并，高效内存
*/