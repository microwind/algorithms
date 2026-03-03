/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
// 计数排序标准版
function countingSort1(arr) {
  // 计算最大值与最小值
  const arrLen = arr.length
  const min = Math.min.apply(null, arr)
  const max = Math.max.apply(null, arr)
  // 计数数组的长度在最大和最小差值+1
  const countListLen = max - min + 1
  const countList = Array(countListLen).fill(0)
  for (let i = 0, l = arrLen; i < l; i++) {
    // 把下标减去min值，可以支持负数
    // 最小的数的坐标为0，以此累加
    const idx = arr[i] - min
    // 根据待排序项给对应下标的位置增加1个标记
    countList[idx] += 1
  }

  console.log('countList:', countList)
  // 将上一项的值添加到下一项中
  for (let i = 1; i < countListLen; i++) {
    countList[i] += countList[i - 1]
  }

  // 按位置还原数据，下一个索引记录了上一个的坐标值
  const output = []
  for (let i = 0; i < arrLen; i++) {
    // 当前项来自原始数组减去-min
    const item = arr[i] - min
    // 根据当前项从计数数组里找到目标位置
    const idx = countList[item] - 1
    // 输出数据加上min进行还原
    output[idx] = item + min
    // 取出一项计数则减少一个
    countList[item] -= 1
  }
  // 原数组和新数组
  console.log('origin arr=', arr, 'output:=', output)
  return output
}

// 计数排序，数组下标为负
function countingSort2(arr) {
  const countList = []
  // 用一个计数器来计数，长度为数组最大值+1
  const min = Math.min(...arr)
  countList.length = Math.max.apply(null, arr) - min + 1
  // 根据待排序项给对应下标的位置增加标记，多个相同的则需要递增
  // 适合正整数, 如果是负数和小数就不可以。此写法JS可支持负数，把数组当对象使用。
  arr.forEach(val => {
    countList[val] = countList[val] || 0
    countList[val]++
  })
  console.log('countList:', countList)
  const output = []
  // 遍历全部，从最小数开始遍历，JS数组支持下标为负
  for (var i = min, l = countList.length; i < l; i++) {
    var val = countList[i]
    console.log('i|val:', i, val)
    // 下标若大于0，则取出来，如果相同则取多次
    for (var j = 0; j < val; j++) {
      output.push(i)
    }
  }
  return output
}

// 计数排序
function countingSort3(arr) {
  // 计算最大值与最小值
  const min = Math.min.apply(null, arr)
  const max = Math.max.apply(null, arr)
  // 计数数组的长度在最大和最小差值+1
  const countList = Array(max - min + 1).fill(0)
  for (var i = 0, l = arr.length; i < l; i++) {
    // 把下标减去min值，以便减少计数数组的长度，同时可以支持负数
    // 最小的数的坐标为0，以此累加即可
    const idx = arr[i] - min
    // 根据待排序项给对应下标的位置增加1个标记
    if (!countList[idx]) {
      countList[idx] += 1
    }
  }
  console.log('countList:', countList)
  const output = []
  // 遍历计数数组
  let idx = 0
  countList.forEach(
    (val, i) => {
      // 下标若大于0，则取出来，如果相同则取多次
      for (var j = 0; j < val; j++) {
        console.log('i|val:', i, val)
        if (val && val > 0) {
          // 取出的值要+min还原
          // 输出新数组或覆盖原数组
          arr[idx++] = i + min
          output.push(i + min)
        }
      }
    }
  )
  // 原数组和新数组
  console.log('origin arr=', arr, 'output:=', output)
  return output
}

// test
const arr1 = [3, 4, 15, 3, 3, 7, 10, -2, -1]
// const arr1 = [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10]
console.time('countingSort1')
console.log('origin:', arr1)
console.log('countingSort1 sorted:', countingSort1(arr1))
console.timeEnd('countingSort1')

const arr2 = [3, 4, 15, 3, 3, 7, 10, -2, -1]
// const arr2 = [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10]
console.time('countingSort2')
console.log('origin:', arr2)
console.log('countingSort2 sorted:', countingSort2(arr2))
console.timeEnd('countingSort2')

const arr3 = [3, 4, 15, 3, 3, 7, 10, -2, -1]
// const arr3 = [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10]
console.time('countingSort3')
console.log('origin:', arr3)
console.log('countingSort3 sorted:', countingSort3(arr3))
console.timeEnd('countingSort3')

/**
jarry@jarrys-MacBook-Pro countingsort % node counting_sort.js
origin: [
  3,  4, 15,  3, 3,
  7, 10, -2, -1
]
countList: [
  1, 1, 0, 0, 0, 3, 1,
  0, 0, 1, 0, 0, 1, 0,
  0, 0, 0, 1
]
origin arr= [
  3,  4, 15,  3, 3,
  7, 10, -2, -1
] output:= [
  -2, -1,  3,  3, 3,
   4,  7, 10, 15
]
countingSort1 sorted: [
  -2, -1,  3,  3, 3,
   4,  7, 10, 15
]
countingSort1: 9.108ms
origin: [
  3,  4, 15,  3, 3,
  7, 10, -2, -1
]
countList: [
  <3 empty items>, 3,
  1,               <2 empty items>,
  1,               <2 empty items>,
  1,               <4 empty items>,
  1,               <2 empty items>,
  '-2': 1,         '-1': 1
]
i|val: -2 1
i|val: -1 1
i|val: 0 undefined
i|val: 1 undefined
i|val: 2 undefined
i|val: 3 3
i|val: 4 1
i|val: 5 undefined
i|val: 6 undefined
i|val: 7 1
i|val: 8 undefined
i|val: 9 undefined
i|val: 10 1
i|val: 11 undefined
i|val: 12 undefined
i|val: 13 undefined
i|val: 14 undefined
i|val: 15 1
i|val: 16 undefined
i|val: 17 undefined
countingSort2 sorted: [
  -2, -1,  3,  3, 3,
   4,  7, 10, 15
]
countingSort2: 2.204ms
origin: [
  3,  4, 15,  3, 3,
  7, 10, -2, -1
]
countList: [
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 1, 0, 0, 1, 0,
  0, 0, 0, 1
]
i|val: 0 1
i|val: 1 1
i|val: 5 1
i|val: 6 1
i|val: 9 1
i|val: 12 1
i|val: 17 1
origin arr= [
  -2, -1,  3,  4, 7,
  10, 15, -2, -1
] output:= [
  -2, -1,  3, 4,
   7, 10, 15
]
countingSort3 sorted: [
  -2, -1,  3, 4,
   7, 10, 15
]
countingSort3: 0.841ms
 */