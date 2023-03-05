/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 基数排序，从低到高逐位对比，基于桶排序，注意与基于计数排序的区别
function radixSortBucket(arr) {

  const min = Math.min.apply(null, arr)
  const max = Math.max.apply(null, arr)
  // 根据最大值，逐个按进位(基数)来应用排序，从个位到高位，exponent即基数。
  for (let exponent = 1; Math.floor((max - min) / exponent) > 0; exponent *= 10) {

    const bucketList = []
    const range = 10
    for (let i = 0, l = arr.length; i < l; i++) {
      // 支持负数减去最小值来分布桶
      const item = arr[i] - min
      // 根据数位上的值，把数据追加到对应的桶里
      const idx = Math.floor((item / exponent) % range)
      if (!bucketList[idx]) {
        bucketList[idx] = []
      }
      bucketList[idx].push(arr[i])
    }
    console.log('bucketList:', bucketList, 'arr:', arr)

    // 将每个桶的数据按顺序逐个取出，重新赋值给原数组
    let sortedIndex = 0
    for (let i = 0; i < range; i++) {
      const item = bucketList[i]
      if (item) {
        item.forEach(number => {
          arr[sortedIndex] = number
          sortedIndex += 1
        })
      }
    }
    console.log('bucketList sorted:', bucketList, 'arr:', arr)
  }
  return arr
}

// test
;
(function () {
  const arr1 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
  console.time('radixSortBucket')
  console.log('origin radixSortBucket:', arr1)
  console.log('radixSortBucket sorted:', radixSortBucket(arr1))
  console.timeEnd('radixSortBucket')
})()

/**
jarry@jarrys-MacBook-Pro radixsort % node radix_sort_bucket.js
origin radixSortBucket: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
bucketList: [
  [ -4, -323454 ],
  [ 7 ],
  <2 empty items>,
  [ 10, 200 ],
  [ 87431 ],
  <1 empty item>,
  [ 33, 43 ],
  <1 empty item>,
  [ 15, 1235 ]
] arr: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
bucketList sorted: [
  [ -4, -323454 ],
  [ 7 ],
  <2 empty items>,
  [ 10, 200 ],
  [ 87431 ],
  <1 empty item>,
  [ 33, 43 ],
  <1 empty item>,
  [ 15, 1235 ]
] arr: [
    -4, -323454,     7,
    10,     200, 87431,
    33,      43,    15,
  1235
]
bucketList: [
  [ -323454 ],
  <4 empty items>,
  [ -4, 200 ],
  [ 7, 10, 15 ],
  <1 empty item>,
  [ 87431, 33, 1235 ],
  [ 43 ]
] arr: [
    -4, -323454,     7,
    10,     200, 87431,
    33,      43,    15,
  1235
]
bucketList sorted: [
  [ -323454 ],
  <4 empty items>,
  [ -4, 200 ],
  [ 7, 10, 15 ],
  <1 empty item>,
  [ 87431, 33, 1235 ],
  [ 43 ]
] arr: [
  -323454, -4,  200,
        7, 10,   15,
    87431, 33, 1235,
       43
]
bucketList: [
  [ -323454 ],
  <3 empty items>,
  [ -4, 7, 10, 15, 33, 43 ],
  <1 empty item>,
  [ 200, 1235 ],
  <1 empty item>,
  [ 87431 ]
] arr: [
  -323454, -4,  200,
        7, 10,   15,
    87431, 33, 1235,
       43
]
bucketList sorted: [
  [ -323454 ],
  <3 empty items>,
  [ -4, 7, 10, 15, 33, 43 ],
  <1 empty item>,
  [ 200, 1235 ],
  <1 empty item>,
  [ 87431 ]
] arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
bucketList: [
  [ -323454, 87431 ],
  <2 empty items>,
  [
    -4,  7,  10, 15,
    33, 43, 200
  ],
  [ 1235 ]
] arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
bucketList sorted: [
  [ -323454, 87431 ],
  <2 empty items>,
  [
    -4,  7,  10, 15,
    33, 43, 200
  ],
  [ 1235 ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList: [
  [ -323454 ],
  [ 87431 ],
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList sorted: [
  [ -323454 ],
  [ 87431 ],
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList: [
  [ -323454 ],
  <2 empty items>,
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ],
  [ 87431 ]
] arr: [
  -323454, 87431,  -4,
        7,    10,  15,
       33,    43, 200,
     1235
]
bucketList sorted: [
  [ -323454 ],
  <2 empty items>,
  [
     -4,    7, 10,
     15,   33, 43,
    200, 1235
  ],
  [ 87431 ]
] arr: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortBucket sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSortBucket: 11.846ms
 */