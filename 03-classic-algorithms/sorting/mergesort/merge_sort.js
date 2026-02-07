/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
/**
 * 归并排序 ，采用分而治之(divide - conquer)的步骤
 * 1. 分解（Divide），把待排序元素的序列分解为两个子序列，以中间2分, 每个子序列包括一半成员。
 * 2. 解决（Conquer），对每个子序列分别调用归并操作, 进行递归或非递归循环操作，完成内部排序。
 * 3. 合并（Combine），合并两个排好序的子序列，生成排序结果。 归并排序的最坏时间复杂度和平均时间复杂度均为O(nlogn)
 */
(function () {
  // 将两个有序数组合并为一个新的有序数组
  function merge (arr, left, mid, right) {
    // 先建立一个长度等于原数组的临时数组
    const temp = []
    // 左侧指针
    let i = left
    // 右侧指针
    let j = mid + 1
    // 临时数组指针
    let k = 0
    // 当左指针小于中间，且右指针不大于最右侧时
    while (i <= mid && j <= right) {
      // 如果左侧小于右侧，将数移到临时数组中左侧
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++]
        // 否则移动到临时数组右侧
      } else {
        temp[k++] = arr[j++]
      }
    }

    // 如果左边数组还有数据，就把左侧剩余都放入到原数组后面
    while (i <= mid) {
      temp[k++] = arr[i++]
    }
    // 如果右侧数组还有数据，把剩下的数据放入到原数组后面
    while (j <= right) {
      temp[k++] = arr[j++]
    }

    // 将排序后的元素全部移动到原数组中
    let x = 0
    while (left <= right) {
      arr[left++] = temp[x++]
    }
    console.log('arr:', arr)
  }

  function mergeSort (arr, left, right) {
    // 得到中间值
    const mid = Math.floor((left + right) / 2)
    // 如果左侧小于右侧则执行合并排序
    if (left < right) {
      // 递归合并左侧
      mergeSort(arr, left, mid)
      // 递归合并右侧
      mergeSort(arr, mid + 1, right)
      // 合并左右结果
      merge(arr, left, mid, right)
    }
    return arr
  }

  // test
  const arr = [7, 11, 9, 10, 12, 13, 8, -2, 0, 8]
  console.time('sort')
  console.log('origin:', arr)
  console.log('\r\nsorted:', mergeSort(arr, 0, arr.length - 1))
  console.timeEnd('sort')
})();

// 第二种写法，利用JS语言特点实现
(function () {
  function mergeSort (arr) {
    const len = arr.length
    if (len < 2) {
      return arr
    }
    // 取得当前数组的中间位置
    const mid = Math.floor(len / 2)
    const left = arr.slice(0, mid)
    const right = arr.slice(mid)
    console.log('mergeSort arr:', arr, left, right)
    // 递归调用，不断重复直到当前数组拆分剩1项
    return merge(mergeSort(left), mergeSort(right))
  }

  // 将两个有序数组进行合并为一个新的有序数组
  function merge (left, right) {
    // 建立一个空数组，用来存放排序结果
    const result = []
    // 左右数组的长度都不为空时，则将两个数组的第一个进行比较
    // 如左侧小于右，则移除左侧的内容到结果数据，反之移动右侧成员
    while (left.length && right.length) {
      if (left[0] <= right[0]) {
        result.push(left.shift())
      } else {
        result.push(right.shift())
      }
    }
    // 最后把剩余的左或者右侧成员全部添加到结果数组
    while (left.length) {
      result.push(left.shift())
    }

    while (right.length) {
      result.push(right.shift())
    }
    // 这样一趟下来后，两个数组就合并为一个新的排序数组
    return result
  }
  // test
  console.log('\n\r==== sort 2 === \r\n')
  const arr = [7, 6, 9, 10, 12, 13, 8, -32, 10, 8]
  console.time('sort')
  console.log('origin:', arr)
  console.log('\r\nsorted:', mergeSort(arr, 0, arr.length - 1))
  console.timeEnd('sort')
})()

/**
jarry@jarrys-mbp mergesort % node merge_sort.js
origin: [ 7, 11, 9, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 11, 9, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 11, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 11, 10, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, 13, 8, -2, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, 8, 13, -2, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, -2, 8, 13, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, -2, 8, 13, 0, 8 ]
arr: [ 7, 9, 10, 11, 12, -2, 0, 8, 8, 13 ]
arr: [ -2, 0, 7, 8, 8, 9, 10, 11, 12, 13 ]

sorted: [ -2, 0, 7, 8, 8, 9, 10, 11, 12, 13 ]
sort: 5.446ms

==== sort 2 === 

origin: [ 7, 6, 9, 10, 12, 13, 8, -32, 10, 8 ]
arr: [ 7, 6, 9, 10, 12, 13, 8, -32, 10, 8 ]
arr: [ 7, 6, 9, 10, 12 ]
arr: [ 7, 6 ]
arr: [ 9, 10, 12 ]
arr: [ 10, 12 ]
arr: [ 13, 8, -32, 10, 8 ]
arr: [ 13, 8 ]
arr: [ -32, 10, 8 ]
arr: [ 10, 8 ]

sorted: [ -32, 6, 7, 8, 8, 9, 10, 10, 12, 13 ]
sort: 4.276ms
*/