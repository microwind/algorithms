/**
 * Copyright https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
;(function () {
  /**
   * 冒泡排序升序，将最大的元素冒泡到最后
   * 时间复杂度：O(n²)，空间复杂度：O(1)，稳定性：稳定
   */
  function bubbleSort1(arr) {
    console.log('bubbleSort1 from left to right:')
    const len = arr.length
    // 外层循环控制排序轮数，每轮确定一个最大值的位置
    for (var i = 0; i < len; i++) {
      // 内层循环控制比较次数，len-i-1 避免重复比较已排序部分
      for (var j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          // 解构赋值交换，更简洁
          ;[arr[j], arr[j + 1]] = [arr[j + 1], arr[j]]
        }
        // console.log('i=' + i, 'j=' + j, arr)
      }
    }
    console.log(arr)
  }

  /**
   * 冒泡排序降序，将最小的元素冒泡到最后
   * 从右向左比较，逐轮冒出最小数
   * 时间复杂度：O(n²)，空间复杂度：O(1)，稳定性：稳定
   */
  function bubbleSort2(arr) {
    console.log('bubbleSort2 from right to left:')
    const len = arr.length
    // 外层循环控制排序轮数，每轮确定一个最小值的位置
    for (var i = 0; i < len; i++) {
      // 内层循环从右向左比较，j > i 避免重复比较已排序部分
      for (var j = len - 1; j > i; j--) {
        // 自右往左每两个进行比较，把小的交换到右侧
        // 逐轮冒出最小数，已经排好序的不要再比较
        if (arr[j - 1] < arr[j]) {
          // 解构赋值交换相邻元素
          ;[arr[j - 1], arr[j]] = [arr[j], arr[j - 1]]
        }
        // console.log('i=' + i, 'j=' + j, arr)
      }
    }
    console.log(arr)
  }

  /**
   * 冒泡排序升序，增加交换标志优化
   * 当某一轮无交换时提前终止，针对有序情况优化
   * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
   */
  function bubbleSort3(arr) {
    console.log('bubbleSort3 add flag:')
    // 增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历，
    const len = arr.length
    var flag = true

    // 外层循环增加 flag 条件，当数组已有序时提前终止
    for (var i = 0; i < len && flag === true; i++) {
      flag = false  // 每轮开始时重置标志
      // console.warn('no. ' + i)
      // 内层循环控制比较次数，len-i-1 避免重复比较已排序部分
      for (var j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          flag = true  // 发生交换，设置标志
          // 解构赋值交换，更简洁
          ;[arr[j], arr[j + 1]] = [arr[j + 1], arr[j]]
        }
        // console.log('i=' + i, 'j=' + j, arr)
      }
    }
    console.log(arr)
  }

  /**
   * 插入冒泡排序法，分为左右两个序列，左侧为已排序，将待排项与左侧逐个对比并交换位置
   */
  function bubbleSort4(arr) {
    console.log('bubbleSort4:')
    const len = arr.length
    // 外层循环控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
    for (let i = 1; i < len; i++) {
      // 内层循环在已排序区域中查找插入位置
      for (let j = 0; j < i; j++) {
        // 如果待插入元素小于已排序区域的某个元素，则交换
        if (arr[j] > arr[i]) {
          ;[arr[i], arr[j]] = [arr[j], arr[i]]
        }
      }
    }
    console.log(arr)
    return arr
  }

  /* test */
  const arr1 = [7, 11, 9, 10, 12, 13, 8]
  console.time('bubbleSort1')
  bubbleSort1(arr1)
  console.timeEnd('bubbleSort1')

  const arr2 = [7, 11, 9, 10, 12, 13, 8]
  console.time('bubbleSort2')
  bubbleSort2(arr2)
  console.timeEnd('bubbleSort2')

  const arr3 = [7, 11, 9, 10, 12, 13, 8]
  console.time('bubbleSort3')
  bubbleSort3(arr3)
  console.timeEnd('bubbleSort3')

  const arr4 = [7, 11, 9, 10, 12, 13, 8]
  console.time('bubbleSort4')
  bubbleSort4(arr4)
  console.timeEnd('bubbleSort4')
})()

/*
jarrys-MacBook-Pro:bubblesort jarry$ node bubble_sort.js 
bubbleSort1 from left to right:
[
   7,  8,  9, 10,
  11, 12, 13
]
bubbleSort1: 8.089ms
bubbleSort2 from right to left:
[
  13, 12, 11, 10,
   9,  8,  7
]
bubbleSort2: 0.374ms
bubbleSort3 add flag:
[
   7,  8,  9, 10,
  11, 12, 13
]
bubbleSort3: 0.346ms
bubbleSort4:
[
   7,  8,  9, 10,
  11, 12, 13
]
bubbleSort4: 0.355ms
*/
