/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 基数排序，基于计数排序的基础上，按数字的每个位置来排序
function radixSort1(arr) {

  function countingSort(arr, exp) {
    const countList = []
    const size = 10
    countList.length = size
    countList.fill(0)
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i]
      // 取得数字的最后一位，并给对应计数数组加1
      const idx = Math.floor((item / exp) % size)
      countList[idx] += 1
    }
    console.log('countingSort countList:', countList)

    // 后面的位数为前面的累加之和
    for (let i = 1; i < size; i++) {
      countList[i] += countList[i - 1]
      console.log('add position:', countList[i], countList)
    }

    const output = []
    // 根据计数数组按顺序取得排序内容
    for (let i = arr.length - 1; i >= 0; i--) {
      const idx = Math.floor((arr[i] / exp) % size)
      output[countList[idx] - 1] = arr[i]
      countList[idx] -= 1
      console.log('set order:', idx, countList[idx], i, countList, output)
    }

    for (let i = 0; i < arr.length; i++) {
      arr[i] = output[i]
    }
    console.log('set output:', arr, output)
    return output
  }

  let output = []
  const max = Math.max.apply(null, arr)
  for (let radix = 1; Math.floor(max / radix) > 0; radix *= 10) {
    output = countingSort(arr, radix)
  }
  return output
}


// 2. 实例2，利用JS语言数组特性
function radixSort2(arr) {
  // 数组展开，循环调用
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

  // 与flatten一样，递归调用
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

  const maxLength = Math.max.apply(null, arr).toString().length
  for (let i = 0; i < maxLength; i++) {
    const buckets = Array.from({
      length: 10
    }, () => [])
    for (let j = 0, l = arr.length; j < l; j++) {
      const item = arr[j].toString()
      const numStr = item.charAt(item.length - 1 - i)
      const num = Number(numStr)
      // console.log(arr, i, item, num)
      if (num !== undefined) {
        buckets[num].push(arr[j])
      }
    }
    if (buckets.flat) {
      arr = buckets.flat()
    } else {
      // arr = flat(buckets)
      arr = flatten(buckets)
    }
  }
  console.log(arr)
  return arr
}

// test
(function () {
  // 定义Prototype来实现数组扁平
  Object.defineProperty(Array.prototype, 'flat', {
    value: function (depth = 1) {
      return this.reduce(function (flat, toFlatten) {
        return flat.concat((Array.isArray(toFlatten) && (depth > 1)) ? toFlatten.flat(depth - 1) : toFlatten)
      }, [])
    }
  })

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
radixSort1 sorted: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort1: 27.512ms
origin radixSort2: [ 33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431 ]
[ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort2 sorted: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort2: 1.001ms
 */