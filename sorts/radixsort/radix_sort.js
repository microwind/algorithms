/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 基数排序，基于计数排序的基础上，按数字的每个位置来排序
function radixSort1(arr) {

  function countingSort(arr, radix) {
    const countList = []
    const range = 10
    countList.length = range
    countList.fill(0)
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i]
      // 根据基数取得数位上的值，并给对应计数数组加1
      const idx = Math.floor((item / radix) % range)
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
      const idx = Math.floor((arr[i] / radix) % range)
      sortedList[countList[idx] - 1] = arr[i]
      countList[idx] -= 1
    }

    // 根据新顺序重新调整原数组
    for (let i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i]
    }

    return sortedList
  }

  const max = Math.max.apply(null, arr)
  // 根据最大值，逐个按进位(基数)来应用排序，radix即数位。
  for (let radix = 1; Math.floor(max / radix) > 0; radix *= 10) {
    countingSort(arr, radix)
  }
  return arr
}

// 2. 基数排序2，把数字按字符串处理，利用JS语言的数组特性进行排序
function radixSort2(arr) {
  // 数组展开，循环调用，非递归写法
  const flatten = (input) => {
    const stack = [...input]
    const res = []
    while (stack.length) {
      const next = stack.pop()
      if (Array.isArray(next)) {
        stack.push(...next)
      } else {
        res.push(next)
      }
    }
    return res.reverse()
  }

  // 与flatten功能一样，这是递归实现
  const flat = (input, depth = 1, stack = []) => {
    for (const item of input) {
      if (Array.isArray(item) && depth > 0) {
        flat(item, depth - 1, stack)
      } else {
        stack.push(item)
      }
    }
    return stack
  }
  // 找出数组中最大数的长度
  const maxLength = Math.max.apply(null, arr).toString().length
  for (let i = 0; i < maxLength; i++) {
    // 填充10个空数组，用于放数字0-9
    const buckets = Array.from({
      length: 10
    }, () => [])

    for (let j = 0, l = arr.length; j < l; j++) {
      // 遍历数组，把每一项的数字都按字符处理
      const item = arr[j].toString()
      const numStr = item.charAt(item.length - 1 - i)

      // 当前位数如果不为空则添加到基数桶中
      const num = Number(numStr)
      // console.log('radixSort2:', 'i=', i, 'j=', j, 'item=', item, 'num=', num, 'buckets=', buckets)
      if (num !== undefined) {
        buckets[num].push(arr[j])
      }
    }

    // 将桶逐级展开取出数字
    if (buckets.flat) {
      arr = buckets.flat()
    } else {
      // arr = flat(buckets)
      arr = flatten(buckets)
    }
  }

  return arr
}

// 定义Prototype来实现数组扁平，这里扩展了prototype，不可取
Object.defineProperty(Array.prototype, 'flat', {
  value: function (depth = 1) {
    return this.reduce(function (flat, toFlatten) {
      return flat.concat((Array.isArray(toFlatten) && (depth > 1)) ? toFlatten.flat(depth - 1) : toFlatten)
    }, [])
  }
})

// test
;(function () {
  const arr1 = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
  console.time('radixSort1')
  console.log('origin radixSort1:', arr1)
  console.log('radixSort1 sorted:', radixSort1(arr1))
  console.timeEnd('radixSort1')

  const arr2 = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
  console.time('radixSort2')
  console.log('origin radixSort2:', arr2)
  console.log('radixSort2 sorted:', radixSort2(arr2))
  console.timeEnd('radixSort2')
})()

/**
jarry@jarrys-MacBook-Pro radixsort % node radix_sort.js
origin radixSort1: [
     33,      4,  15,
     43, 323454,   7,
     10,   1235, 200,
  87431
]
countingSort countList: [
  2, 1, 0, 2, 2,
  2, 0, 1, 0, 0
]
countingSort countList: [
  3, 2, 0, 3, 1,
  1, 0, 0, 0, 0
]
countingSort countList: [
  6, 0, 2, 0, 2,
  0, 0, 0, 0, 0
]
countingSort countList: [
  7, 1, 0, 1, 0,
  0, 0, 1, 0, 0
]
countingSort countList: [
  8, 0, 1, 0, 0,
  0, 0, 0, 1, 0
]
countingSort countList: [
  9, 0, 0, 1, 0,
  0, 0, 0, 0, 0
]
radixSort1 sorted: [
       4,    7,    10,
      15,   33,    43,
     200, 1235, 87431,
  323454
]
radixSort1: 9.418ms
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