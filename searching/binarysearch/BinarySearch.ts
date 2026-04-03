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
 * 二分查找类
 * 包含多种二分查找实现
 */
class BinarySearch {
  constructor() { }

  /**
   * search1 - 标准非递归版本，传递左右区间指针
   * 
   * 算法步骤：
   * 1. 初始化左右边界：left=0, right=arr.length-1
   * 2. 计算中间位置：midIndex = Math.floor((left + right) / 2)
   * 3. 比较中间值与目标值
   * 4. 根据比较结果调整查找范围
   * 5. 重复直到找到目标或范围为空
   * 
   * @param {Array<number>} arr - 有序数组
   * @param {number} target - 目标值
   * @returns {number} 找到返回索引，未找到返回-1
   */
  search1(arr: Array<number>, target: number) {
    var left = 0
    var right = arr.length - 1
    var midIndex: number, mid: number
    // left是左侧，right是最右侧。搜索区间长度小于1时停止
    while (left <= right) {
      midIndex = Math.floor((left + right) / 2)  // 计算中间位置
      mid = arr[midIndex]                           // 获取中间值
      // 中间项等于目标项则返回下标
      if (mid === target) {
        return midIndex
      } else if (target > mid) {
        // 大于中间项折半查找右侧
        left = midIndex + 1
      } else {
        // 小于中间项折半查找左侧
        right = midIndex - 1
      }
    }
    return -1  // 未找到
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
   * @param {Array<number>} arr - 有序数组
   * @param {number} target - 目标值
   * @param {number} left - 左边界（可选）
   * @param {number} right - 右边界（可选）
   * @returns {number} 找到返回索引，未找到返回-1
   */
  search2(arr: Array<number>, target: number, left: number = 0, right: number = -1) {
    right = right === -1 ? arr.length - 1 : right       // 默认右边界为末尾
    var midIndex = Math.floor((left + right) / 2)
    var mid = arr[midIndex]
    // 中间值等于查找项说明找到了，则返回中间项下标
    if (target === mid) {
      // 如果有重复项，返回第一个位置
      if (arr[left] === target) {
        return left
      }
      return midIndex
    }
    // 如果左侧与右侧相同，表面查找完毕，返回-1
    if (left >= right) {
      return -1
    }
    if (target > mid) {
      // 折半右侧部分开始递归查找
      return this.search2(arr, target, midIndex + 1, right)
    } else {
      // 折半左侧部分开始递归查找
      return this.search2(arr, target, left, midIndex - 1)
    }
  }

  /**
   * search3 - 解决存在重复项问题，返回第一个出现的位置。传递左右区间，向左查找（向右查找类似）
   * 
   * 算法思路：
   * 1. 使用非递归方式，但处理重复项的特殊情况
   * 2. 当找到目标时，继续向左查找第一个出现的位置
   * 3. 通过缩小右边界来确保找到第一个匹配项
   * 
   * @param {Array<number>} arr - 有序数组
   * @param {number} target - 目标值
   * @returns {number} 第一个匹配项的索引，未找到返回-1
   */
  search3(arr: Array<number>, target: number) {
    var left = 0
    var right = arr.length - 1
    var midIndex: number, mid: number
    // 搜索区间小于等于1停止搜索
    while (left <= right) {
      // 找到中间值
      midIndex = Math.floor((left + right) / 2)
      mid = arr[midIndex]

      if (target > mid) {
        // 大于中间项折半查找右侧
        left = midIndex + 1
      } else {
        // 小于等于中间项则折半查找左侧，同时缩小右侧范围
        right = midIndex - 1
      }
    }
    // 此时left是最左侧目标项
    if (left < arr.length && arr[left] === target) {
      return left
    }

    return -1
  }

  /**
   * search4 - 二分搜索递归查找，记录下右侧位置
   * 
   * 算法步骤：
   * 1. 处理边界条件，数组长度小于等于1时特殊处理
   * 2. 计算中间位置和中间值
   * 3. 比较中间值与目标值
   * 4. 根据比较结果递归查找对应半区
   * 5. 累积索引位置，确保返回正确的绝对位置
   * 
   * @param {Array<number>} arr - 有序数组
   * @param {number} target - 目标值
   * @param {number} resultIndex - 累积的右侧位置（内部使用）
   * @returns {number} 找到返回索引，未找到返回-1
   */
  search4(arr: Array<number>, target: number, resultIndex: number = 0) {
    if (arr.length <= 1 && target !== arr[0]) {
      return -1
    }
    let midIndex = Math.floor((arr.length - 1) / 2)
    let mid = arr[midIndex]
    resultIndex = resultIndex === undefined ? 0 : resultIndex
    if (target === mid) {
      return resultIndex + midIndex
    } else if (target > mid) {
      // 如果在右侧，则需要将中间index加上
      return this.search4(arr.splice(midIndex + 1), target, resultIndex + midIndex + 1)
    } else {
      return this.search4(arr.splice(0, midIndex), target, resultIndex)
    }
  }

}

/**
 * 主程序：演示二分查找算法的性能对比
 * 
 * 测试内容：
 * 1. search1 - 标准非递归版本
 * 2. search2 - 递归版本，处理重复项
 * 3. search3 - 查找第一个匹配项
 * 4. search4 - 递归版本，累积索引位置
 */
(function () {
  // 创建测试数据
  const binarySearch = new BinarySearch();
  var arr = [2, 3, 8, 10, 10, 13]
  
  // 测试 search1 - 标准非递归版本
  console.time('time')
  var result = binarySearch.search1(arr, 10) // 4
  console.log('binarySearch.search1(arr, 10)', '=> result:' + result)
  console.timeEnd('time')

  // 测试 search2 - 递归版本
  console.time('time')
  arr = [2, 3, 8, 10, 10, 13]
  result = binarySearch.search2(arr, 10) // 3
  console.log('binarySearch.search2(arr, 10)', '=> result:' + result)
  console.timeEnd('time')

  // 测试 search3 - 查找第一个匹配项
  console.time('time')
  arr = [2, 3, 8, 10, 10, 13]
  result = binarySearch.search3(arr, 10) // 3
  console.log('binarySearch.search3(arr, 10)', '=> result:' + result)
  console.timeEnd('time')

  // 测试 search4 - 递归版本，累积索引位置
  console.time('time')
  arr = [2, 3, 8, 10, 10, 13]
  result = binarySearch.search4(arr, 10) // 4
  console.log('binarySearch.search4(arr, 10)', '=> result:' + result)
  console.timeEnd('time')
})();


/**
jarry@jarrys-MacBook-Pro binarysearch % tsc BinarySearch.ts
jarry@jarrys-MacBook-Pro binarysearch % node BinarySearch.js
binarySearch.search1(arr, 10) => result:4
time: 2.151ms
binarySearch.search2(arr, 10) => result:3
time: 0.195ms
binarySearch.search3(arr, 10) => result:3
time: 0.081ms
binarySearch.search4(arr, 10) => result:4
time: 0.099ms
 */