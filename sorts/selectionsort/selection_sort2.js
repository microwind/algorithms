/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 选择排序优化版，同时找出最小和最大值进行交换，可减少1半遍历
// 把数列分为前中后三个区间，分别代表最小已排序、中间待排序以及最大已排序区间
// 遍历中间待排序同时找最大和最小值，分别交换到最小值区间和最大值区间
function selectionSort(arr) {
  let minValue, maxValue, minIdx, maxIdx
  let minListIdx, maxListIdx
  const arrLen = arr.length
  // 外循环，从第1项开始与后面待排序项逐个对比，最后1位无需再比较
  for (let i = 0; i < arrLen - 1; i++) {
    // 待排序里面初始最小值和下标
    minIdx = i
    minValue = arr[minIdx]
    // 待排序里面初始最大值和下标
    maxIdx = i
    maxValue = arr[maxIdx]
    // 最小和最大序列里最新待交换的下标
    // 最小序列的下标从0开始，自前往后递加
    minListIdx = minIdx
    // 最大序列的下标从数组最后1位开始，自后往前递减
    maxListIdx = arrLen - 1 - i
    // 如果最小和最大下标相同，说明只剩下1个数字，则终止循环
    if (minListIdx === maxListIdx) {
      break
    }

    // 逐一遍历待排序区间，找出最小和最大值
    // 待排序区间在最小值序列和和最大值序列之间
    // 待比较区间的下标j从i+1开始，到最大已排序前结束
    for (let j = i + 1; j < arrLen - i; j++) {
      // 从待排序列表中分别找到最小值和最大值
      if (arr[j] < minValue) {
        minIdx = j
        minValue = arr[minIdx]
      } else if (arr[j] > maxValue) {
        maxIdx = j
        maxValue = arr[maxIdx]
      }
    }

    // 如果最小值等于最小序列待交换的值，且最大值等于最大序列里待交换的值，则跳过
    if (arr[minIdx] === arr[minListIdx] && arr[maxIdx] === arr[maxListIdx]) {
      continue
    }
    console.log('minValue=', minValue, 'maxValue=', maxValue, 'minIdx=', minIdx, 'maxIdx=', maxIdx, 'minListIdx=', minListIdx, 'maxListIdx=', maxListIdx)
    // 先交换小值，再交换大值
    ;[arr[minListIdx], arr[minIdx]] = [arr[minIdx], arr[minListIdx]]
    // 如果最大值被交换了，则需要更新最大值的下标
    if (arr[minIdx] === maxValue) {
      maxIdx = minIdx
    }
    ;[arr[maxListIdx], arr[maxIdx]] = [arr[maxIdx], arr[maxListIdx]]
  }

  return arr
}

// test
;
(function () {
  const arr1 = [7, 11, -9, 10, -12, 13, 8]
  console.time('sort1')
  console.log('origin arr1:', arr1)
  console.log('\r\narr1 sorted:', selectionSort(arr1))
  console.timeEnd('sort1')

  const arr2 = [7, 11, 121, -9, 545, 110, -210, 12.45, -132, 192, 153, 19, 8]
  console.time('sort2')
  console.log('origin arr2:', arr2)
  console.log('\r\narr2 sorted:', selectionSort(arr2))
  console.timeEnd('sort2')

  const arr3 = [57, 311, 131, -9, 415, 10, 1330, 1245, -12, 1942, 123, 129, 80]
  console.time('sort3')
  console.log('origin arr3:', arr3)
  console.log('\r\narr3 sorted:', selectionSort(arr3))
  console.timeEnd('sort3')
})()
/**
jarry@jarrys-MacBook-Pro selectionsort % node selection_sort2.js
origin arr1: [
    7, 11, -9, 10,
  -12, 13,  8
]
minValue= -12 maxValue= 13 minIdx= 4 maxIdx= 5 minListIdx= 0 maxListIdx= 6
minValue= -9 maxValue= 11 minIdx= 2 maxIdx= 1 minListIdx= 1 maxListIdx= 5
minValue= 7 maxValue= 10 minIdx= 4 maxIdx= 3 minListIdx= 2 maxListIdx= 4

arr1 sorted: [
  -12, -9,  7, 8,
   10, 11, 13
]
sort1: 8.097ms
origin arr2: [
     7,  11,  121,    -9,
   545, 110, -210, 12.45,
  -132, 192,  153,    19,
     8
]
minValue= -210 maxValue= 545 minIdx= 6 maxIdx= 4 minListIdx= 0 maxListIdx= 12
minValue= -132 maxValue= 192 minIdx= 8 maxIdx= 9 minListIdx= 1 maxListIdx= 11
minValue= -9 maxValue= 153 minIdx= 3 maxIdx= 10 minListIdx= 2 maxListIdx= 10
minValue= 7 maxValue= 121 minIdx= 6 maxIdx= 3 minListIdx= 3 maxListIdx= 9
minValue= 8 maxValue= 110 minIdx= 4 maxIdx= 5 minListIdx= 4 maxListIdx= 8
minValue= 11 maxValue= 19 minIdx= 5 maxIdx= 6 minListIdx= 5 maxListIdx= 7

arr2 sorted: [
  -210, -132,    -9,   7,
     8,   11, 12.45,  19,
   110,  121,   153, 192,
   545
]
sort2: 1.405ms
origin arr3: [
   57,  311,  131,   -9,
  415,   10, 1330, 1245,
  -12, 1942,  123,  129,
   80
]
minValue= -12 maxValue= 1942 minIdx= 8 maxIdx= 9 minListIdx= 0 maxListIdx= 12
minValue= -9 maxValue= 1330 minIdx= 3 maxIdx= 6 minListIdx= 1 maxListIdx= 11
minValue= 10 maxValue= 1245 minIdx= 5 maxIdx= 7 minListIdx= 2 maxListIdx= 10
minValue= 57 maxValue= 415 minIdx= 8 maxIdx= 4 minListIdx= 3 maxListIdx= 9
minValue= 123 maxValue= 131 minIdx= 7 maxIdx= 5 minListIdx= 5 maxListIdx= 7

arr3 sorted: [
   -12,  -9,   10,   57,
    80, 123,  129,  131,
   311, 415, 1245, 1330,
  1942
]
sort3: 0.81ms
 */