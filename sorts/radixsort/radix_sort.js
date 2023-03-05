/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 基数排序LSD版，基于计数排序的基础，按数字的每个位置来排序
function radixSort1(arr) {

  const min = Math.min.apply(null, arr)
  const max = Math.max.apply(null, arr)
  // 根据最大值，逐个按进位(基数)来应用排序，exponent即基数。
  // 最大减去最小得到数位，最小按0来计算，这样可以支持负数。
  for (let exponent = 1; Math.floor((max - min) / exponent) > 0; exponent *= 10) {
    const countList = []
    const range = 10
    countList.length = range
    countList.fill(0)

    for (let i = 0, l = arr.length; i < l; i++) {
      // 减去最小值以支持负数，这样桶不会出现负数
      const item = arr[i] - min
      // 根据基数取得数位上的值，并给对应计数数组加1
      const idx = Math.floor((item / exponent) % range)
      countList[idx] += 1
    }
    console.log('countingSort countList:', countList)

    // 后面的位数为前面的累加之和
    for (let i = 1; i < range; i++) {
      countList[i] += countList[i - 1]
    }

    const sortedList = []
    // 补齐位数，根据计数数组按顺序取得排序内容
    for (let i = arr.length - 1; i >= 0; i--) {
      const item = arr[i] - min
      const idx = Math.floor((item / exponent) % range)
      sortedList[countList[idx] - 1] = arr[i]
      countList[idx] -= 1
    }

    // 根据新顺序重新调整原数组
    for (let i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i]
    }
  }
  return arr
}

// test
;(function () {
  const arr1 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
  console.time('radixSort1')
  console.log('origin radixSort1:', arr1)
  console.log('radixSort1 sorted:', radixSort1(arr1))
  console.timeEnd('radixSort1')
})()

/**
jarry@jarrys-MacBook-Pro radixsort % node radix_sort.js  
origin radixSort1: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
countingSort countList: [
  2, 1, 0, 0, 2,
  1, 0, 2, 0, 2
]
countingSort countList: [
  1, 0, 0, 0, 0,
  2, 3, 0, 3, 1
]
countingSort countList: [
  1, 0, 0, 0, 6,
  0, 2, 0, 1, 0
]
countingSort countList: [
  2, 0, 0, 7, 1,
  0, 0, 0, 0, 0
]
countingSort countList: [
  1, 1, 8, 0, 0,
  0, 0, 0, 0, 0
]
countingSort countList: [
  1, 0, 0, 8, 1,
  0, 0, 0, 0, 0
]
radixSort1 sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSort1: 9.595ms
 */