/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
class SelectionSort {
  arr: Array<number>
  constructor() {}
  // 标准版
  selectionSort1(arr: Array<number>) {
    let min: number, minIdx: number, tmp: number
    let l = arr.length
    for (let i = 0; i < l - 1; i++) {
      min = arr[i]
      minIdx = i
      let j = i + 1
      for (; j < l; j++) {
        // 从待排序列表找到最小值和位置
        if (arr[j] < min) {
          min = arr[j]
          minIdx = j
        }
      }
      console.log(
        'i=' + i,
        ' j=' + j,
        'min=' + min,
        'minIdx=' + minIdx,
        'arr[]=',
        arr
      )
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
  selectionSort2(arr: Array<number>) {
    let min: number,
      minIdx: number,
      newArr: number[] = []
    let l = arr.length
    for (let i = 0; i < l; i++) {
      min = arr[i]
      minIdx = i
      let j = i + 1
      for (; j < l; j++) {
        // 找到并记录下最小值和位置
        if (arr[j] < min) {
          min = arr[j]
          minIdx = j
        }
      }
      console.log(
        'i=' + i,
        ' j=' + j,
        'min=' + min,
        'minIdx=' + minIdx,
        'arr[]=',
        arr
      )
      // 将待排序里最小值添加到新数组中去
      newArr.push(min)
      // 原数组中删除对应的项
      arr.splice(minIdx, 1)
      l--
      i--
    }

    return newArr
  }
}

;(function () {
  const selectionSort = new SelectionSort()
  const arr1 = [7, 11, -9, 10, -12, 13, 8]
  console.time('sort1')
  console.log('origin arr1:', arr1)
  console.log('\r\narr1 sorted:', selectionSort.selectionSort1(arr1))
  console.timeEnd('sort1')

  const arr2 = [7, 11, -9, 10, -12, 13, 8]
  console.time('sort2')
  console.log('origin arr2:', arr2)
  console.log('\r\narr2 sorted:', selectionSort.selectionSort1(arr2))
  console.timeEnd('sort2')
})()
/**
jarry@jarrys-MacBook-Pro selectionsort % tsc SelectionSort.ts
jarry@jarrys-MacBook-Pro selectionsort % node SelectionSort.js
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
sort1: 8.069ms
origin arr2: [
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

arr2 sorted: [
  -12, -9,  7, 8,
   10, 11, 13
]
sort2: 1.083ms
 */
