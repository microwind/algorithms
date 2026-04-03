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

import 'dart:io';

/**
 * 打印数组内容的辅助函数
 */
void printArray(List<int> arr, String label) {
  print('$label: [${arr.join(', ')}]');
}

/**
 * 性能测试辅助函数
 */
void performanceTest(Function(List<int>) sortFunc, List<int> arr, String name) {
  // 创建数组副本，避免修改原数组
  List<int> testArr = List.from(arr);
  printArray(testArr, '${name}原始数组');
  
  // 开始计时
  Stopwatch stopwatch = Stopwatch()..start();
  sortFunc(testArr);
  stopwatch.stop();
  
  print('$name: ${stopwatch.elapsedMicroseconds / 1000.0}ms');
  printArray(testArr, '${name}排序结果');
  print(''); // 空行分隔
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
List<int> testData = [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4];

/**
 * 归并排序基础版本 - 递归实现
 * 
 * 算法原理：
 * 1. 将数组递归地分成两半，直到每个子数组只有一个元素
 * 2. 将相邻的两个有序子数组合并成一个更大的有序数组
 * 3. 重复合并过程，直到最终得到一个完全有序的数组
 * 
 * 生活类比：就像整理一副扑克牌，先把牌分成两堆，
 * 每堆分别整理好，然后将两堆有序地合并在一起
 * 
 * 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
 * 空间复杂度：O(n) - 需要额外的数组空间来存储合并结果
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
void mergeSort1(List<int> arr) {
  print('mergeSort1 recursive:');
  
  /**
   * 合并两个有序数组
   * @param left - 左侧有序数组
   * @param right - 右侧有序数组
   * @return 合并后的有序数组
   */
  List<int> merge(List<int> left, List<int> right) {
    List<int> result = [];
    int leftIndex = 0;
    int rightIndex = 0;
    
    // 比较两个数组的元素，按顺序合并
    while (leftIndex < left.length && rightIndex < right.length) {
      // 关键点：选择较小的元素放入结果数组
      if (left[leftIndex] <= right[rightIndex]) {
        result.add(left[leftIndex]);
        leftIndex++;
      } else {
        result.add(right[rightIndex]);
        rightIndex++;
      }
    }
    
    // 将剩余元素添加到结果数组
    // Dart特点：使用addAll处理剩余元素
    while (leftIndex < left.length) {
      result.add(left[leftIndex]);
      leftIndex++;
    }
    while (rightIndex < right.length) {
      result.add(right[rightIndex]);
      rightIndex++;
    }
    
    return result;
  }
  
  /**
   * 递归归并排序函数
   * @param arr - 待排序数组
   * @return 排序后的数组
   */
  List<int> mergeSort(List<int> arr) {
    // 基础情况：数组长度小于等于1时直接返回
    if (arr.length <= 1) {
      return arr;
    }
    
    // 分割数组为两半
    int middle = arr.length ~/ 2;
    List<int> left = arr.sublist(0, middle);
    List<int> right = arr.sublist(middle);
    
    // 递归排序并合并
    return merge(mergeSort(left), mergeSort(right));
  }
  
  List<int> result = mergeSort(arr);
  arr.clear();
  arr.addAll(result);
  printArray(arr, '排序后数组');
}

/**
 * 归并排序优化版本 - 原地合并
 * 
 * 优化思路：
 * 减少空间复杂度，尝试在原数组上进行合并操作
 * 使用索引操作而不是创建新数组
 * 
 * 优化效果：
 * - 减少了内存分配
 * - 提高了空间效率
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(log n) - 仅递归栈空间
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
void mergeSort2(List<int> arr) {
  print('mergeSort2 in-place:');
  
  /**
   * 原地合并两个有序子数组
   * @param arr - 原数组
   * @param left - 左子数组起始索引
   * @param mid - 中间索引
   * @param right - 右子数组结束索引
   */
  void mergeInPlace(List<int> arr, int left, int mid, int right) {
    // 创建临时数组存储左半部分
    List<int> leftArr = arr.sublist(left, mid + 1);
    int i = 0; // 左数组索引
    int j = mid + 1; // 右数组索引
    int k = left; // 合并位置索引
    
    // 合并两个有序子数组
    while (i < leftArr.length && j <= right) {
      // 关键点：选择较小的元素放入结果数组
      if (leftArr[i] <= arr[j]) {
        arr[k] = leftArr[i];
        i++;
      } else {
        arr[k] = arr[j];
        j++;
      }
      k++;
    }
    
    // 复制左数组剩余元素
    while (i < leftArr.length) {
      arr[k] = leftArr[i];
      i++;
      k++;
    }
  }
  
  /**
   * 递归归并排序函数
   * @param arr - 待排序数组
   * @param left - 左边界
   * @param right - 右边界
   */
  void mergeSort(List<int> arr, int left, int right) {
    if (left < right) {
      int mid = (left + right) ~/ 2;
      
      // 递归排序左半部分
      mergeSort(arr, left, mid);
      
      // 递归排序右半部分
      mergeSort(arr, mid + 1, right);
      
      // 合并两个有序部分
      mergeInPlace(arr, left, mid, right);
    }
  }
  
  if (arr.isNotEmpty) {
    mergeSort(arr, 0, arr.length - 1);
  }
  printArray(arr, '排序后数组');
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
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
void mergeSort3(List<int> arr) {
  print('mergeSort3 iterative:');
  
  /**
   * 合并两个有序子数组
   * @param arr - 原数组
   * @param temp - 临时数组
   * @param left - 左边界
   * @param mid - 中间索引
   * @param right - 右边界
   */
  void merge(List<int> arr, List<int> temp, int left, int mid, int right) {
    int i = left; // 左子数组索引
    int j = mid + 1; // 右子数组索引
    int k = left; // 临时数组索引
    
    // 合并到临时数组
    while (i <= mid && j <= right) {
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
      } else {
        temp[k++] = arr[j++];
      }
    }
    
    // 复制左子数组剩余元素
    while (i <= mid) {
      temp[k++] = arr[i++];
    }
    
    // 复制右子数组剩余元素
    while (j <= right) {
      temp[k++] = arr[j++];
    }
    
    // 将临时数组复制回原数组
    for (int index = left; index <= right; index++) {
      arr[index] = temp[index];
    }
  }
  
  int n = arr.length;
  List<int> temp = List.filled(n, 0);
  
  // 迭代合并，步长从1开始翻倍
  for (int size = 1; size < n; size *= 2) {
    // 每次合并两个大小为size的子数组
    for (int left = 0; left < n - size; left += 2 * size) {
      int mid = left + size - 1;
      int right = (left + 2 * size - 1).clamp(0, n - 1);
      merge(arr, temp, left, mid, right);
    }
  }
  
  printArray(arr, '排序后数组');
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
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
void mergeSort4(List<int> arr) {
  print('mergeSort4 bottom-up:');
  
  /**
   * 合并两个相邻的有序子数组
   * @param arr - 原数组
   * @param temp - 临时数组
   * @param left - 起始位置
   * @param mid - 中间位置
   * @param right - 结束位置
   */
  void merge(List<int> arr, List<int> temp, int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;
    
    // 合并两个有序子数组到临时数组
    while (i < mid && j <= right) {
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
      } else {
        temp[k++] = arr[j++];
      }
    }
    
    // 复制剩余元素
    while (i < mid) {
      temp[k++] = arr[i++];
    }
    while (j <= right) {
      temp[k++] = arr[j++];
    }
    
    // 复制回原数组
    for (int index = left; index <= right; index++) {
      arr[index] = temp[index];
    }
  }
  
  int n = arr.length;
  List<int> temp = List.filled(n, 0);
  
  // 自底向上合并
  for (int width = 1; width < n; width *= 2) {
    for (int i = 0; i < n; i += 2 * width) {
      int left = i;
      int mid = (i + width).clamp(0, n);
      int right = (i + 2 * width).clamp(0, n);
      
      if (mid < right) {
        merge(arr, temp, left, mid, right - 1);
      }
    }
  }
  
  printArray(arr, '排序后数组');
}

/**
 * 归并排序 - 原地范围版本
 * 
 * 算法思路：
 * 使用索引范围进行原地合并操作
 * 直接在原数组上进行分割和合并
 * 
 * 优化效果：
 * - 减少内存分配
 * - 更好的缓存局部性
 * - 空间效率更高
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时子数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 * 
 * @param arr - 待排序的数字数组
 * @return 排序后的数组
 */
void mergeSort5(List<int> arr) {
  print('mergeSort5 in-place range:');
  
  /**
   * 原地范围合并两个有序子数组
   * @param arr - 原数组
   * @param left - 左子数组起始索引
   * @param mid - 中间索引
   * @param right - 右子数组结束索引
   */
  void mergeInPlaceRange(List<int> arr, int left, int mid, int right) {
    // 创建临时数组存储左半部分
    List<int> leftArr = arr.sublist(left, mid + 1);
    int i = 0; // 左数组索引
    int j = mid + 1; // 右数组索引
    int k = left; // 合并位置索引
    
    // 合并两个有序子数组
    while (i < leftArr.length && j <= right) {
      // 关键点：选择较小的元素放入结果数组
      if (leftArr[i] <= arr[j]) {
        arr[k] = leftArr[i];
        i++;
      } else {
        arr[k] = arr[j];
        j++;
      }
      k++;
    }
    
    // 复制左数组剩余元素
    while (i < leftArr.length) {
      arr[k] = leftArr[i];
      i++;
      k++;
    }
  }
  
  /**
   * 递归归并排序函数
   * @param arr - 待排序数组
   * @param left - 左边界
   * @param right - 右边界
   */
  void mergeSort(List<int> arr, int left, int right) {
    // 基础情况检查：当左边界不小于右边界时停止递归
    // 关键点：单个元素或空数组已经有序
    if (left >= right) {
      return;
    }
    
    // 步骤1：计算中间位置
    // 使用 left + (right - left) / 2 防止整数溢出
    int mid = left + (right - left) ~/ 2;
    
    // 步骤2：递归排序左半部分
    // 处理范围：[left, mid]
    mergeSort(arr, left, mid);
    
    // 步骤3：递归排序右半部分
    // 处理范围：[mid+1, right]
    mergeSort(arr, mid + 1, right);
    
    // 步骤4：合并两个有序部分
    // 关键步骤：将两个相邻的有序子数组合并
    mergeInPlaceRange(arr, left, mid, right);
  }
  
  if (arr.isNotEmpty) {
    mergeSort(arr, 0, arr.length - 1);
  }
  printArray(arr, '排序后数组');
}

// ==================== 算法测试和性能对比 ====================

void main() {
  // 测试1：递归版本
  performanceTest(mergeSort1, testData, '递归版本');

  // 测试2：原地合并版本
  performanceTest(mergeSort2, testData, '原地合并版本');

  // 测试3：迭代版本
  performanceTest(mergeSort3, testData, '迭代版本');

  // 测试4：自底向上版本
  performanceTest(mergeSort4, testData, '自底向上版本');

  // 测试5：原地范围版本
  performanceTest(mergeSort5, testData, '原地范围版本');

  print('=== 算法对比总结 ===');
  print('1. 递归版本：经典实现，易于理解');
  print('2. 原地版本：空间优化，减少内存使用');
  print('3. 迭代版本：避免递归，性能稳定');
  print('4. 底向上版本：适合大数据，外部排序');
  print('5. 原地范围版本：索引操作，高效合并');
}

/*
打印结果
jarry@Mac mergesort % dart merge_sort.dart
递归版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort1 recursive:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
递归版本: 0.645ms
递归版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

原地合并版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort2 in-place:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0.135ms
原地合并版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

迭代版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort3 iterative:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.191ms
迭代版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

自底向上版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort4 bottom-up:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.139ms
自底向上版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

原地范围版本原始数组: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort5 in-place range:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
原地范围版本: 0.123ms
原地范围版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本：经典实现，易于理解
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 原地范围版本：索引操作，高效合并
*/
