/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
;(function () {
  // 1. ASE
  function bubbleSort1(arr) {
    console.log('bubbleSort1 from left to right:')
    const len = arr.length
    for (var i = 0; i < len; i++) {
      for (var j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          ;[arr[j], arr[j + 1]] = [arr[j + 1], arr[j]]
        }
        // console.log('i=' + i, 'j=' + j, arr)
      }
    }
    console.log(arr)
  }

  // 2. DESC
  function bubbleSort2(arr) {
    console.log('bubbleSort2 from right to left:')
    const len = arr.length
    for (var i = 0; i < len; i++) {
      for (var j = len - 1; j > i; j--) {
        // 自右往左每两个进行比较，把小的交换到右侧
        // 逐轮冒出最小数，已经排好序的不要再比较
        if (arr[j - 1] < arr[j]) {
          ;[arr[j - 1], arr[j]] = [arr[j], arr[j - 1]]
        }
        // console.log('i=' + i, 'j=' + j, arr)
      }
    }
    console.log(arr)
  }

  // 3. add flag
  function bubbleSort3(arr) {
    console.log('bubbleSort3 add flag:')
    // 增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历，
    const len = arr.length
    var flag = true

    for (var i = 0; i < len && flag === true; i++) {
      flag = false
      // console.warn('no. ' + i)
      for (var j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          flag = true
          ;[arr[j], arr[j + 1]] = [arr[j + 1], arr[j]]
        }
        // console.log('i=' + i, 'j=' + j, arr)
      }
    }
    console.log(arr)
  }

  // 4. 分为左右两列，左列已排序，右侧待排序。自左往右循环左列，逐个与待排序项比较并交换，外循环针对待排序项。
  function bubbleSort4(arr) {
    console.log('bubbleSort4:')
    const len = arr.length
    for (let i = 1; i < len; i++) {
      for (let j = 0; j < i; j++) {
        if (arr[j] > arr[i]) {
          ;[arr[i], arr[j]] = [arr[j], arr[i]]
        }
      }
    }
    console.log(arr)
    return arr
  }

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
