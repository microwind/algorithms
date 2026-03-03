/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 基数排序，从高到低逐位排序，递归方式，基于桶排序。具体步骤如下：
// 1. 找出数组中最大的数，确定其位数。
// 2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中。
// 3. 如果桶里的长度超过1，则通过递归继续按桶排序。当桶里的数据只有1位时添加到原列表对应位置。
// 重复步骤2和3，直到按照最高位排序完成。
function radixSortMSD(arr) {

  function bucketSort(arr, exponent) {
    console.log('origin arr:', arr, 'exponent:', exponent)
    if (!arr || arr.length <= 1 || exponent < 1) {
      return arr
    }
    const min = Math.min.apply(null, arr)
    const range = 10

    console.log('prepared arr:', arr, 'exponent:', exponent)

    // 定义桶二维数组，长度为10，放入0-9的数字
    const buckets = []
    for (let i = 0; i < range; i++) {
      buckets[i] = []
    }
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i] - min
      // 根据数位上的值，把数据追加到对应的桶里，减去min是支持负数
      const bucketIdx = Math.floor(item / exponent % range)
      // 提前填充空桶或使用时再填充
      if (!buckets[bucketIdx]) {
        buckets[bucketIdx] = []
      }
      buckets[bucketIdx].push(arr[i])
    }
    console.log('append to buckets:', buckets)

    // 将每个桶的数据按顺序逐个取出，重新赋值给原数组
    let sortedIdx = 0

    for (let i = 0; i < range; i++) {
      const bucket = buckets[i]
      if (bucket && bucket.length > 0) {
        // 如果是数组则继续递归调用，位数降低1位
        const sortedBucket = bucketSort(bucket, Math.floor(exponent / range))
        // 把各个桶里的值按顺序赋给原数组
        sortedBucket.forEach(num => {
          arr[sortedIdx] = num
          // console.log('bucket:', bucket, 'sortedBucket:', sortedBucket, 'sortedIdx:', sortedIdx, 'set arr:', arr)
          sortedIdx += 1
        })
      }
    }
    console.log('exponent:', exponent, 'sorted arr:', arr)
    return arr
  }

  const max = Math.max.apply(null, arr)
  const min = Math.min.apply(null, arr)
  // 获取数字一共有几位，减去min得到最大值，以支持负数和减少最大值
  const numberOfDigits = Math.floor(Math.log10(max - min) + 1)
  const exponent = Math.pow(10, numberOfDigits - 1)
  // 根据数组最大值，自后向前逐个按数位基数(exponent)比较排序。
  return bucketSort(arr, exponent)
}

// test
;
(function () {
  const arr1 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
  console.time('radixSortMSD')
  console.log('origin radixSortMSD:', arr1)
  console.log('radixSortMSD sorted:', radixSortMSD(arr1))
  console.timeEnd('radixSortMSD')
})()

/**
jarry@jarrys-MacBook-Pro radixsort % node radix_sort_msd.js
origin radixSortMSD: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
origin arr: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
] exponent: 100000
prepared arr: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
] exponent: 100000
append to buckets: [
  [ -323454 ],
  <2 empty items>,
  [
      33,  -4, 15,
      43,   7, 10,
    1235, 200
  ],
  [ 87431 ]
]
origin arr: [ -323454 ] exponent: 10000
origin arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 10000
prepared arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 10000
append to buckets: [
  [
      33,  -4, 15,
      43,   7, 10,
    1235, 200
  ]
]
origin arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 1000
prepared arr: [
    33,  -4, 15,
    43,   7, 10,
  1235, 200
] exponent: 1000
append to buckets: [
  [
    33, -4,  15, 43,
     7, 10, 200
  ],
  [ 1235 ]
]
origin arr: [
  33, -4,  15, 43,
   7, 10, 200
] exponent: 100
prepared arr: [
  33, -4,  15, 43,
   7, 10, 200
] exponent: 100
append to buckets: [ [ 33, -4, 15, 43, 7, 10 ], <1 empty item>, [ 200 ] ]
origin arr: [ 33, -4, 15, 43, 7, 10 ] exponent: 10
prepared arr: [ 33, -4, 15, 43, 7, 10 ] exponent: 10
append to buckets: [ [ -4 ], [ 15, 7, 10 ], <1 empty item>, [ 33 ], [ 43 ] ]
origin arr: [ -4 ] exponent: 1
origin arr: [ 15, 7, 10 ] exponent: 1
prepared arr: [ 15, 7, 10 ] exponent: 1
append to buckets: [ [ 7 ], <2 empty items>, [ 10 ], <4 empty items>, [ 15 ] ]
origin arr: [ 7 ] exponent: 0
origin arr: [ 10 ] exponent: 0
origin arr: [ 15 ] exponent: 0
exponent: 1 sorted arr: [ 7, 10, 15 ]
origin arr: [ 33 ] exponent: 1
origin arr: [ 43 ] exponent: 1
exponent: 10 sorted arr: [ -4, 7, 10, 15, 33, 43 ]
origin arr: [ 200 ] exponent: 10
exponent: 100 sorted arr: [
  -4,  7,  10, 15,
  33, 43, 200
]
origin arr: [ 1235 ] exponent: 100
exponent: 1000 sorted arr: [
   -4,    7, 10,
   15,   33, 43,
  200, 1235
]
exponent: 10000 sorted arr: [
   -4,    7, 10,
   15,   33, 43,
  200, 1235
]
origin arr: [ 87431 ] exponent: 10000
exponent: 100000 sorted arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortMSD sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortMSD: 11.673ms
 */