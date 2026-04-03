/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

/**
 * binarySearch1 - 标准非递归版本，传递左右区间指针
 * 
 * 算法步骤：
 * 1. 初始化左右边界：left=0, right=list.length-1
 * 2. 计算中间位置：midIndex = (left + right) ~/ 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param {List} list - 有序数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
int binarySearch1(list, target) {
  var left = 0;
  var right = list.length - 1;
  var midIndex, mid;
  // left是左侧，right是最右侧。搜索区间长度小于1时停止
  while (left <= right) {
    midIndex = (left + right) ~/ 2;  // 计算中间位置
    mid = list[midIndex];              // 获取中间值
    // 中间项等于目标项则返回下标
    if (mid == target) {
      return midIndex;
    } else if (target > mid) {
      // 大于中间项折半查找右侧
      left = midIndex + 1;
    } else {
      // 小于中间项折半查找左侧
      right = midIndex - 1;
    }
  }
  return -1;  // 未找到
}

/**
 * binarySearch2 - 递归实现，移动左右区间指针
 * 
 * 算法步骤：
 * 1. 处理默认参数，设置初始边界
 * 2. 计算中间位置和中间值
 * 3. 比较中间值与目标值
 * 4. 根据比较结果递归查找对应半区
 * 5. 处理重复项的特殊情况
 * 
 * @param {List} list - 有序数组
 * @param {int} target - 目标值
 * @param {int} left - 左边界（可选）
 * @param {int} right - 右边界（可选）
 * @returns {int} 找到返回索引，未找到返回-1
 */
int binarySearch2(list, target, left, right) {
  left = left == null ? 0 : left;                    // 默认左边界为0
  right = right == null ? list.length - 1 : right;     // 默认右边界为末尾
  var midIndex = (left + right) ~/ 2;
  var mid = list[midIndex];
  // 中间值等于查找项说明找到了，则返回中间项下标
  if (target == mid) {
    // 如果有重复项，返回第一个位置
    if (list[left] == target) {
      return left;
    }
    return midIndex;
  }
  // 如果左侧与右侧相同，表面查找完毕，返回-1
  if (left >= right) {
    return -1;
  }
  if (target > mid) {
    // 折半右侧部分开始递归查找
    return binarySearch2(list, target, midIndex + 1, right);
  } else {
    // 折半左侧部分开始递归查找
    return binarySearch2(list, target, left, midIndex - 1);
  }
}


/**
 * main - 主程序：演示二分查找算法的性能对比
 * 
 * 测试内容：
 * 1. binarySearch1 - 标准非递归版本
 * 2. binarySearch2 - 递归版本，处理重复项
 */
void main() {
  // 创建测试数据
  var list = [2, 3, 9, 10, 23, 34, 45];

  // 测试 binarySearch1 - 标准非递归版本
  print(binarySearch1(list, 10)); // 3
  print(binarySearch1(list, 2));  // 0
  print(binarySearch1(list, 4)); // -1 not found

  // 测试 binarySearch2 - 递归版本
  print(binarySearch2(list, 10, 0, list.length)); // 3
  print(binarySearch2(list, 2, 0, list.length));  // 0
  print(binarySearch2(list, 4, 0, list.length)); // -1 not found
}

/**
jarry@jarrys-MacBook-Pro factor % dart --version
Dart SDK version: 2.10.2 on "macos_x64"
jarry@jarrys-MacBook-Pro binarysearch % dart binary_search.dart
3
0
-1
3
0
-1
 */