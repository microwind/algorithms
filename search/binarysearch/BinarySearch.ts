/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
// 标准非递归版本，传递左右区间指针
class BinarySearch {
  constructor() { }
  search1(arr: Array<number>, target: number) {
    var left = 0
    var right = arr.length - 1
    var midIndex: number, mid: number
    // left是左侧，right是最右侧。搜索区间长度小于1时停止
    while (left <= right) {
      midIndex = Math.floor((left + right) / 2)
      mid = arr[midIndex]
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
    return -1
  }

  // 递归实现，移动左右区间指针
  search2(arr: Array<number>, target: number, left: number = 0, right: number = -1) {
    right = right === -1 ? arr.length - 1 : right
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

  // 解决存在重复项问题，返回第一个出现的位置。传递左右区间，向左查找（向右查找类似）
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
    //  此时left是最左侧目标项
    if (left < arr.length && arr[left] === target) {
      return left
    }

    return -1
  }

  //  二分搜索递归查找，记录下右侧位置
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
      //  如果在右侧，则需要将中间index加上
      return this.search4(arr.splice(midIndex + 1), target, resultIndex + midIndex + 1)
    } else {
      return this.search4(arr.splice(0, midIndex), target, resultIndex)
    }
  }

}

(function () {
  console.time("time");
  const binarySearch = new BinarySearch();
  console.time('time')
  var arr = [2, 3, 8, 10, 10, 13]
  var result = binarySearch.search1(arr, 10) // 4
  console.log('binarySearch.search1(arr, 10)', '=> result:' + result)
  console.timeEnd('time')

  console.time('time')
  arr = [2, 3, 8, 10, 10, 13]
  result = binarySearch.search2(arr, 10) // 3
  console.log('binarySearch.search2(arr, 10)', '=> result:' + result)
  console.timeEnd('time')

  console.time('time')
  arr = [2, 3, 8, 10, 10, 13]
  result = binarySearch.search3(arr, 10) // 3
  console.log('binarySearch.search3(arr, 10)', '=> result:' + result)
  console.timeEnd('time')

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