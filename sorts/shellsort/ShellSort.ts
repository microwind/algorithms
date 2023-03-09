/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 希尔排序，基于插入排序进行了分组排序
class ShellSort {
  shellSort1(arr: number[]): number[] {
    const len = arr.length
    // 设置分组增量值（步长）为1/2的数组长度
    let gap = Math.floor(len / 2)
    // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
    while (gap > 0) {
      for (let i = 0; i < len; i++) {
        const current = arr[i]
        let j = i
        // 对子序列按照插入排序
        while (j >= gap && current < arr[j - gap]) {
          console.log(
            'gap=' + gap + ' i=' + i + ' j=' + j + ' (j - gap)=' + (j - gap),
            'arr:',
            arr
          )
          arr[j] = arr[j - gap]
          j -= gap
        }
        // 交换当前项
        arr[j] = current
      }
      // 调整步长为1/2
      gap = Math.floor(gap / 2)
    }
    return arr
  }

  /* 2. 希尔排序标准版，基于插入排序进行分组排序，步长按1/2缩减。 */
  shellSort2(arr: number[]): number[] {
    const len = arr.length
    let gap = 1
    // 初始步长按3倍递增，小于1/3数组长度
    while (gap < Math.floor(len / 3)) {
      gap = gap * 3 + 1
    }
    // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
    while (gap > 0) {
      for (let i = gap; i < len; i++) {
        const current = arr[i]
        let j = i - gap
        // 对子序列按照插入排序
        for (; j >= 0 && arr[j] > current; j -= gap) {
          console.log(
            'gap=' + gap + ' i=' + i + ' j=' + j + ' (j + gap)=' + (j + gap),
            'arr:',
            arr
          )
          arr[j + gap] = arr[j]
        }
        arr[j + gap] = current
      }
      // 步长按3倍缩减
      gap = Math.floor(gap / 3)
    }
    return arr
  }
}

;(function () {
  const shellSort = new ShellSort()
  const arr1 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431]
  console.time('shellSort1')
  console.log('origin shellSort1:', arr1)
  console.log('shellSort1 sorted:', shellSort.shellSort1(arr1))
  console.timeEnd('shellSort1')

  const arr2 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431]
  console.time('shellSort2')
  console.log('origin shellSort2:', arr2)
  console.log('shellSort2 sorted:', shellSort.shellSort2(arr2))
  console.timeEnd('shellSort2')
})()

/*
jarry@jarrys-MacBook-Pro shellsort % tsc ShellSort.ts -t es2020
jarry@jarrys-MacBook-Pro shellsort % node ShellSort.js
origin shellSort1: [
     33,      4,  15,
     43, 323454,  -7,
   10.5,   1235, 200,
  87431
]
gap=5 i=5 j=5 (j - gap)=0 arr: [
     33,      4,  15,
     43, 323454,  -7,
   10.5,   1235, 200,
  87431
]
gap=5 i=9 j=9 (j - gap)=4 arr: [
     -7,      4,  15,
     43, 323454,  33,
   10.5,   1235, 200,
  87431
]
gap=2 i=5 j=5 (j - gap)=3 arr: [
      -7,     4,  15,
      43, 87431,  33,
    10.5,  1235, 200,
  323454
]
gap=2 i=6 j=6 (j - gap)=4 arr: [
      -7,     4,  15,
      33, 87431,  43,
    10.5,  1235, 200,
  323454
]
gap=2 i=6 j=4 (j - gap)=2 arr: [
      -7,     4,  15,
      33, 87431,  43,
   87431,  1235, 200,
  323454
]
gap=2 i=8 j=8 (j - gap)=6 arr: [
      -7,    4, 10.5,
      33,   15,   43,
   87431, 1235,  200,
  323454
]
gap=1 i=4 j=4 (j - gap)=3 arr: [
      -7,    4,  10.5,
      33,   15,    43,
     200, 1235, 87431,
  323454
]
shellSort1 sorted: [
      -7,    4,  10.5,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
shellSort1: 10.398ms
origin shellSort2: [
     33,      4,  15,
     43, 323454,  -7,
   10.5,   1235, 200,
  87431
]
gap=4 i=5 j=1 (j + gap)=5 arr: [
     33,      4,  15,
     43, 323454,  -7,
   10.5,   1235, 200,
  87431
]
gap=4 i=6 j=2 (j + gap)=6 arr: [
     33,     -7,  15,
     43, 323454,   4,
   10.5,   1235, 200,
  87431
]
gap=4 i=8 j=4 (j + gap)=8 arr: [
     33,     -7, 10.5,
     43, 323454,    4,
     15,   1235,  200,
  87431
]
gap=1 i=1 j=0 (j + gap)=1 arr: [
     33,   -7,   10.5,
     43,  200,      4,
     15, 1235, 323454,
  87431
]
gap=1 i=2 j=1 (j + gap)=2 arr: [
     -7,   33,   10.5,
     43,  200,      4,
     15, 1235, 323454,
  87431
]
gap=1 i=5 j=4 (j + gap)=5 arr: [
     -7, 10.5,     33,
     43,  200,      4,
     15, 1235, 323454,
  87431
]
gap=1 i=5 j=3 (j + gap)=4 arr: [
     -7, 10.5,     33,
     43,  200,    200,
     15, 1235, 323454,
  87431
]
gap=1 i=5 j=2 (j + gap)=3 arr: [
     -7, 10.5,     33,
     43,   43,    200,
     15, 1235, 323454,
  87431
]
gap=1 i=5 j=1 (j + gap)=2 arr: [
     -7, 10.5,     33,
     33,   43,    200,
     15, 1235, 323454,
  87431
]
gap=1 i=6 j=5 (j + gap)=6 arr: [
     -7,    4,   10.5,
     33,   43,    200,
     15, 1235, 323454,
  87431
]
gap=1 i=6 j=4 (j + gap)=5 arr: [
     -7,    4,   10.5,
     33,   43,    200,
    200, 1235, 323454,
  87431
]
gap=1 i=6 j=3 (j + gap)=4 arr: [
     -7,    4,   10.5,
     33,   43,     43,
    200, 1235, 323454,
  87431
]
gap=1 i=9 j=8 (j + gap)=9 arr: [
     -7,    4,   10.5,
     15,   33,     43,
    200, 1235, 323454,
  87431
]
shellSort2 sorted: [
      -7,    4,  10.5,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
shellSort2: 1.812ms
*/
