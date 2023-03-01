/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 基数排序，基于计数排序的基础上，按数字的每个位置来排序
function radixSortMSD(arr, exponent) {
  if (!arr || arr.length <= 1 || exponent < 1) {
    return arr
  }
  const max = Math.max.apply(null, arr)
  const min = Math.min.apply(null, arr)

  const range = 10
  const amount = 10
  // 根据最大值，逐个按进位(基数)来应用排序，从高位到低位，exponent即基数。
  if (!exponent) {
    const numberOfDigits = Math.floor(Math.log10(max))
    exponent = Math.pow(amount, numberOfDigits)
  }
  console.log('origin arr:', arr, 'exponent:', exponent)

  const buckets = []
  for (let i = 0, l = arr.length; i < l; i++) {
    const item = arr[i] - min
    // 根据数位上的值，把数据追加到对应的桶里
    const idx = Math.floor((item / exponent) % range)
    if (!buckets[idx]) {
      buckets[idx] = []
    }
    buckets[idx].push(arr[i])
  }
  console.log('append to buckets:', buckets)

  // 将每个桶的数据按顺序逐个取出，重新赋值给原数组
  let sortedIdx = 0

  for (let i = 0; i < range; i++) {
    const bukcket = buckets[i]
    if (bukcket && bukcket.length > 0) {
      // 如果是数组则继续递归调用，位数减去1位
      const sortedBucket = radixSortMSD(bukcket, Math.floor(exponent / amount))
      // 把各个桶里的值按顺序赋给原数组
      sortedBucket.forEach(num => {
        arr[sortedIdx] = num
        console.log('bukcket:', bukcket, 'sortedBucket:', sortedBucket, 'sortedIdx:', sortedIdx, 'set arr:', arr)
        sortedIdx += 1
      })
    }
  }

  console.log('exponent:', exponent, 'sorted arr:', arr)

  return arr
}

// test
;
(function () {
  // const arr1 = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
  const arr1 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
  console.time('radixSortMSD')
  console.log('origin radixSortMSD:', arr1)
  console.log('radixSortMSD sorted:', radixSortMSD(arr1))
  console.timeEnd('radixSortMSD')
})()

/**
jarry@jarrys-MacBook-Pro radixsort % node radix_sort.js
origin radixSortMSD: [
     33,      4,  15,
     43, 323454,   7,
     10,   1235, 200,
  87431
]
countingSort buckets: [
  2, 1, 0, 2, 2,
  2, 0, 1, 0, 0
]
countingSort buckets: [
  3, 2, 0, 3, 1,
  1, 0, 0, 0, 0
]
countingSort buckets: [
  6, 0, 2, 0, 2,
  0, 0, 0, 0, 0
]
countingSort buckets: [
  7, 1, 0, 1, 0,
  0, 0, 1, 0, 0
]
countingSort buckets: [
  8, 0, 1, 0, 0,
  0, 0, 0, 1, 0
]
countingSort buckets: [
  9, 0, 0, 1, 0,
  0, 0, 0, 0, 0
]
radixSortMSD sorted: [
       4,    7,    10,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
radixSortMSD: 9.418ms
origin radixSort2: [
     33,      4,  15,
     43, 323454,   7,
     10,   1235, 200,
  87431
]
radixSort2 sorted: [
       4,    7,    10,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
radixSort2: 0.652ms
 */