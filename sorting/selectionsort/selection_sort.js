/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 标准版，找出最小或最大
function selectionSort1(arr) {
  var min, minIdx, tmp
  var arrLen = arr.length
  for (var i = 0; i < arrLen - 1; i++) {
    min = arr[i]
    minIdx = i
    var j = i + 1
    for (; j < arrLen; j++) {
      // 从待排序列表中找到最小值和位置，用作交换
      if (arr[j] < min) {
        min = arr[j]
        minIdx = j
      }
    }
    console.log('i=' + i, ' j=' + j, 'min=' + min, 'minIdx=' + minIdx, 'arr[]=', arr)
    // 将待排序里最小值交换到已排序最后面
    if (minIdx !== i) {
      tmp = arr[i]
      arr[i] = min
      arr[minIdx] = tmp
    }
  }
  return arr
}

// 新建数组版，无需交换
function selectionSort2(arr) {
  var min, minIdx
  var newArr = []
  var arrLen = arr.length
  for (var i = 0; i < arrLen; i++) {
    min = arr[i]
    minIdx = i
    let j = i + 1
    for (; j < arrLen; j++) {
      // 找到并记录下最小值和位置
      if (arr[j] < min) {
        min = arr[j]
        minIdx = j
      }
    }
    console.log('i=' + i, ' j=' + j, 'min=' + min, 'minIdx=' + minIdx, 'arr[]=', arr)
    // 将待排序里最小值添加到新数组中去
    newArr.push(min)
    // 原数组中删除对应的项
    arr.splice(minIdx, 1)
    arrLen--
    i--
  }
  return newArr
}

// test
;
(function () {
  const arr1 = [7, 11, -9, 10, -12, 13, 8]
  console.time('sort1')
  console.log('origin arr1:', arr1)
  console.log('\r\narr1 sorted:', selectionSort1(arr1))
  console.timeEnd('sort1')

  const arr2 = [7, 11, -9, 10, -12, 13, 8]
  console.time('sort2')
  console.log('origin arr2:', arr2)
  console.log('\r\narr2 sorted:', selectionSort2(arr2))
  console.timeEnd('sort2')

})()
/**
jarry@jarrys-MacBook-Pro selectionsort % node selection_sort.js
origin arr1: [
    7, 11, -9, 10,
  -12, 13,  8
]
i=0  j=7 min=-12 minIdx=4 arr[]= [
    7, 11, -9, 10,
  -12, 13,  8
]
i=1  j=7 min=-9 minIdx=2 arr[]= [
  -12, 11, -9, 10,
    7, 13,  8
]
i=2  j=7 min=7 minIdx=4 arr[]= [
  -12, -9, 11, 10,
    7, 13,  8
]
i=3  j=7 min=8 minIdx=6 arr[]= [
  -12, -9, 7, 10,
   11, 13, 8
]
i=4  j=7 min=10 minIdx=6 arr[]= [
  -12, -9,  7, 8,
   11, 13, 10
]
i=5  j=7 min=11 minIdx=6 arr[]= [
  -12, -9,  7, 8,
   10, 13, 11
]

arr1 sorted: [
  -12, -9,  7, 8,
   10, 11, 13
]
sort1: 8.913ms
origin arr2: [
    7, 11, -9, 10,
  -12, 13,  8
]
i=0  j=7 min=-12 minIdx=4 arr[]= [
    7, 11, -9, 10,
  -12, 13,  8
]
i=0  j=6 min=-9 minIdx=2 arr[]= [ 7, 11, -9, 10, 13, 8 ]
i=0  j=5 min=7 minIdx=0 arr[]= [ 7, 11, 10, 13, 8 ]
i=0  j=4 min=8 minIdx=3 arr[]= [ 11, 10, 13, 8 ]
i=0  j=3 min=10 minIdx=1 arr[]= [ 11, 10, 13 ]
i=0  j=2 min=11 minIdx=0 arr[]= [ 11, 13 ]
i=0  j=1 min=13 minIdx=0 arr[]= [ 13 ]

arr2 sorted: [
  -12, -9,  7, 8,
   10, 11, 13
]
sort2: 1.339ms
 */