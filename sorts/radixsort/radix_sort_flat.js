/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 基数排序2，从低到高逐个数位对比排序，利用JS数组展开来还原数组
function radixSort2(arr) {

  // 倒数获取数字指定位置的数
  function getDigit(num, position) {
    const digit = Math.floor(num / Math.pow(10, position - 1)) % 10
    return digit
  }

  // 获取数组最大数字的位数
  function getMaxLength(num) {
    let maxLength = 0
    while (num > 0) {
      maxLength++
      num /= 10
    }
    return maxLength
  }

  const max = Math.max.apply(null, arr)
  const min = Math.min.apply(null, arr)
  // 找出数组中最大数的长度，可以通过计算或直接换成字符串求长度，减去min以便支持负数
  // const maxLength = (max - min).toString().length
  const maxLength = getMaxLength(max - min)

  for (let i = 0; i < maxLength; i++) {
    // 每个数位准备10个空数组，用于放数字0-9
    const buckets = Array.from({
      length: 10
    }, () => [])

    // 遍历数组将数位上的数放入对应桶里
    for (let j = 0, l = arr.length; j < l; j++) {
      const item = (arr[j] - min)
      // 从后往前获取数位上的数字，通过字符串方式或计算的方式
      // const numStr = item.toString().charAt(item.length - 1 - i)
      // const num = Number(numStr)

      // 从后往前获取第x位置的数，通过计算的方式
      const num = getDigit(item, i + 1)
      // 当前位数如果不为空则添加到基数桶中
      // console.log('radixSort2:', 'i=', i, 'j=', j, 'item=', item, 'num=', num, 'buckets=', buckets)
      if (num !== isNaN) {
        buckets[num].push((arr[j]))
      }
    }

    // 将桶逐级展开取出数字，如果支持flat则直接使用数组的flat()
    if (buckets.flat) {
      arr = buckets.flat()
    } else {
      // arr = flat(buckets)
      arr = flatten(buckets)
    }
  }

  return arr
}

// 1. 自定义数组展开函数，与默认flatten功能一样，循环调用，非递归写法
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

// 2. 数组展开，与flatten功能一样，这是递归实现
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

// 如果没有flat，还可以通过定义Prototype来实现数组扁平，扩展Array.prototype不可取
// Object.defineProperty(Array.prototype, 'flat', {
//   value: function (depth = 1) {
//     return this.reduce(function (flat, toFlatten) {
//       return flat.concat((Array.isArray(toFlatten) && (depth > 1)) ? toFlatten.flat(depth - 1) : toFlatten)
//     }, [])
//   }
// })

// test
;
(function () {
  const arr2 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
  console.time('radixSort2')
  console.log('origin radixSort2:', arr2)
  console.log('radixSort2 sorted:', radixSort2(arr2))
  console.timeEnd('radixSort2')
})()

/**
jarry@jarrys-MacBook-Pro radixsort % node radix_sort_flat.js
origin radixSort2: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
radixSort2 sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSort2: 10.908ms
 */