
/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 二分查找算法实现
 * 提供多种实现方式，适合不同场景和性能需求
 */

import java.util.*;

/**
 * 二分查找类
 * 包含多种二分查找实现
 */
public class BinarySearch {
  /**
 * search1 - 标准非递归版本，传递左右区间指针
 * 
 * 算法步骤：
 * 1. 初始化左右边界：left=0, right=arr.length-1
 * 2. 计算中间位置：midIndex = (left + right) / 2
 * 3. 比较中间值与目标值
 * 4. 根据比较结果调整查找范围
 * 5. 重复直到找到目标或范围为空
 * 
 * @param {int[]} arr - 有序数组
 * @param {int} target - 目标值
 * @returns {int} 找到返回索引，未找到返回-1
 */
  int search1(int[] arr, int target) {
    int left = 0;
    int right = arr.length - 1;
    int midIndex, mid;
    // left是左侧，right是最右侧。搜索区间长度小于1时停止
    while (left <= right) {
      midIndex = (left + right) / 2;  // 计算中间位置
      mid = arr[midIndex];               // 获取中间值
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
    // 此时left是最左侧目标项
    if (left < arr.length && arr[left] == target) {
      return left;
    }

    return -1;  // 未找到
  }

  /**
 * search2 - 递归实现，移动左右区间指针
 * 
 * 算法步骤：
 * 1. 处理默认参数，设置初始边界
 * 2. 计算中间位置和中间值
 * 3. 比较中间值与目标值
 * 4. 根据比较结果递归查找对应半区
 * 5. 处理重复项的特殊情况
 * 
 * @param {int[]} arr - 有序数组
 * @param {int} target - 目标值
 * @param {int} left - 左边界（可选）
 * @param {int} right - 右边界（可选）
 * @returns {int} 找到返回索引，未找到返回-1
 */
  int search2(int[] arr, int target, int left, int right) {
    right = right == -1 ? arr.length - 1 : right;  // 默认右边界为末尾
    int midIndex = (left + right) / 2;
    int mid = arr[midIndex];
    // 中间值等于查找项说明找到了，则返回中间项下标
    if (target == mid) {
      // 如果有重复项，返回第一个位置
      if (arr[left] == target) {
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
      return this.search2(arr, target, midIndex + 1, right);
    } else {
      // 折半左侧部分开始递归查找
      return this.search2(arr, target, left, midIndex - 1);
    }
  }

  /**
 * main - 主程序：演示二分查找算法的性能对比
 * 
 * 测试内容：
 * 1. search1 - 标准非递归版本
 * 2. search2 - 递归版本，处理重复项
 * 
 * @param {String[]} args - 命令行参数
 */
  public static void main(final String args[]) {
    // 创建测试数据
    int[] arr = { 2, 3, 8, 10, 10, 13 };
    BinarySearch binarySearch = new BinarySearch();

    // 测试 search1 - 标准非递归版本
    long startTime = System.currentTimeMillis();
    int result = binarySearch.search1(arr, 10); // 3
    System.out.println("binarySearch.search1(arr, 10) => result:" + result);
    result = binarySearch.search1(arr, 3); // 1
    System.out.println("binarySearch.search1(arr, 3) => result:" + result);
    result = binarySearch.search1(arr, 99); // -1
    System.out.println("binarySearch.search1(arr, 99) => result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    // 测试 search2 - 递归版本
    startTime = System.currentTimeMillis();
    result = binarySearch.search2(arr, 10, 0, -1); // 3
    System.out.println("binarySearch.search2(arr, 10) => result:" + result);
    result = binarySearch.search2(arr, 3, 0, -1); // 1
    System.out.println("binarySearch.search2(arr, 3, 0, -1) => result:" + result);
    result = binarySearch.search2(arr, 99, 0, -1); // -1
    System.out.println("binarySearch.search2(arr, 99, 0, -1) => result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
  }
}

/**
jarry@jarrys-MacBook-Pro binarysearch % javac BinarySearch.java
jarry@jarrys-MacBook-Pro binarysearch % java BinarySearch      
binarySearch.search1(arr, 10) => result:3
binarySearch.search1(arr, 3) => result:1
binarySearch.search1(arr, 99) => result:-1

time:13 ms.
binarySearch.search2(arr, 10) => result:3
binarySearch.search2(arr, 3, 0, -1) => result:1
binarySearch.search2(arr, 99, 0, -1) => result:-1

time:1 ms.
 */