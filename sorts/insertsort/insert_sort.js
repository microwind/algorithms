/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
;(function () {
  // 标准版
  function insertSort1(arr) {
    let j
    let current
    const len = arr.length
    // 外循环用于遍历待排序区间，内循环用来遍历已排序区间
    for (let i = 0; i < len; i++) {
      j = i
      current = arr[i]
      // 将该项与已排序项逐个对比，当遇到比自己大的项时，逐项右移
      // 直到遇到小于等于自己的项则停止移动
      // console.log('i=' + i, ' j=' + j, 'current=' + current, 'arr[i]=' + arr[i], 'arr[j]=' + arr[j], 'arr[]=', arr)
      while (j-- > 0 && current < arr[j]) {
        // 将大于比较项的数逐个位移，以便空出位置
        arr[j + 1] = arr[j]
      }
      // 插入到指定位置
      arr[j + 1] = current
    }
    return arr
  }

  // 标准版2，j递减时机不同
  function insertSort2(arr) {
    var j
    var current
    var len = arr.length
    for (var i = 0; i < len; i++) {
      j = i - 1
      current = arr[i]
      // console.log('i=' + i, ' j=' + j, 'current=' + current, 'arr[i]=' + arr[i], 'arr[j+1]=' + arr[j + 1], 'arr[]=', arr)
      while (j >= 0 && current < arr[j]) {
        arr[j + 1] = arr[j]
        j--
      }
      arr[j + 1] = current
    }
    return arr
  }

  // splice版本
  function insertSort3(arr) {
    var j
    var current
    var len = arr.length
    var isMin
    for (var i = 1; i < len; i++) {
      j = i - 1
      current = arr.splice(i, 1)[0]
      isMin = true
      while (j >= 0) {
        if (current > arr[j]) {
          // console.log('i=' + i, ' j=' + j, 'current=' + current, 'arr[i]=' + arr[i], 'arr[j]=' + arr[j], 'arr[]=', arr)
          // 利用splice插入
          arr.splice(j + 1, 0, current)
          isMin = false
          break
        }
        j--
      }
      if (isMin) {
        arr.splice(0, 0, current)
      }
    }
    return arr
  }

  // 新建数组版
  function insertSort4(arr) {
    var j
    var len = arr.length
    var isMax
    var newArr = arr.slice(0, 1)
    for (var i = 1; i < len; i++) {
      isMax = true
      for (var j = 0, newLen = newArr.length; j < newLen; j++) {
        // console.log('i=' + i, ' j=' + j, 'arr[i]=' + arr[i], 'newArr[j]=' + newArr[j], 'arr[]=', arr)
        if (arr[i] < newArr[j]) {
          // 新建数组来插入到某个位置中
          newArr.splice(j, 0, arr[i])
          isMax = false
          break
        }
      }
      if (isMax) {
        newArr.push(arr[i])
      }
    }
    return newArr
  }

  // 新建数组版倒序遍历
  function insertSort5(arr) {
    var l = arr.length
    var len
    var isMin
    var newArr = arr.slice(0, 1)

    for (var i = 1; i < l; i++) {
      isMin = true
      len = newArr.length
      while (len--) {
        // console.log('i=' + i, ' len=' + len, 'arr[i]=' + arr[i], 'newArr[len]=' + newArr[len], 'arr[]=', arr)
        if (arr[i] > newArr[len]) {
          newArr.splice(len + 1, 0, arr[i])
          isMin = false
          break
        }
      }
      if (isMin) {
        newArr.unshift(arr[i])
      }
    }
    console.warn('newArr:', newArr)
    return newArr
  }

  // 新建数组版挪动插入版
  function insertSort6(arr) {
    const len = arr.length
    const newArr = [arr[0]]
    for (let i = 1; i < len; i++) {
      let l = newArr.length
      while (l--) {
        if (arr[i] < newArr[l]) {
          newArr[l + 1] = newArr[l]
          if (l === 0) {
            newArr[0] = arr[i]
          }
        } else {
          newArr[l + 1] = arr[i]
          break
        }
      }
    }
    return newArr
  }

  const arr = [7, 11, 9, 10, 12, 13, 8]
  const arr2 = [3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10]
  console.log('arr origin:', arr)
  console.log('arr2 origin:', arr2)

  console.time('sort1')
  console.log('\r\ninsertSort1 sorted:', insertSort1(arr.slice(0, arr.length)))
  console.timeEnd('sort1')
  console.time('sort1-2')
  console.log('\r\ninsertSort1 sorted:', insertSort1(arr2.slice(0, arr.length)))
  console.timeEnd('sort1-2')

  console.time('sort2')
  console.log('\r\ninsertSort2 sorted:', insertSort2(arr.slice(0, arr.length)))
  console.timeEnd('sort2')
  console.time('sort2-1')
  console.log('\r\ninsertSort2 sorted:', insertSort2(arr2.slice(0, arr.length)))
  console.timeEnd('sort2-1')

  console.time('sort3')
  console.log('\r\ninsertSort3 sorted:', insertSort3(arr.slice(0, arr.length)))
  console.timeEnd('sort3')
  console.time('sort3-1')
  console.log('\r\ninsertSort3 sorted:', insertSort3(arr2.slice(0, arr.length)))
  console.timeEnd('sort3-1')

  console.time('sort4')
  console.log('\r\ninsertSort4 sorted:', insertSort4(arr.slice(0, arr.length)))
  console.timeEnd('sort4')
  console.time('sort4-1')
  console.log('\r\ninsertSort4 sorted:', insertSort4(arr2.slice(0, arr.length)))
  console.timeEnd('sort4-1')

  console.time('sort5')
  console.log('\r\ninsertSort5 sorted:', insertSort5(arr.slice(0, arr.length)))
  console.timeEnd('sort5')
  console.time('sort5-1')
  console.log('\r\ninsertSort5 sorted:', insertSort5(arr2.slice(0, arr.length)))
  console.timeEnd('sort5-1')

  console.time('sort6')
  console.log('\r\ninsertSort6 sorted:', insertSort6(arr.slice(0, arr.length)))
  console.timeEnd('sort6')
  console.time('sort6-1')
  console.log('\r\ninsertSort6 sorted:', insertSort6(arr2.slice(0, arr.length)))
  console.timeEnd('sort6-1')
})()

/**
jarrys-MacBook-Pro:insertsort jarry$ node insert_sort.js
arr origin: [ 7, 11, 9, 10, 12, 13, 8 ]
arr2 origin: [ 3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10 ]

insertSort1 sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 0.449ms

insertSort1 sorted: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]
sort: 0.295ms

insertSort2 sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 0.223ms

insertSort2 sorted: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]
sort: 0.121ms

insertSort3 sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 0.193ms

insertSort3 sorted: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]
sort: 0.105ms

insertSort4 sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 0.209ms

insertSort4 sorted: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]
sort: 0.098ms
newArr: [ 7, 8, 9, 10, 11, 12, 13 ]

insertSort5 sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 0.396ms
newArr: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]

insertSort5 sorted: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]
sort: 5.252ms

insertSort6 sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 0.386ms

insertSort6 sorted: [ -2.1, -2.1, -2, 2, 3, 4.3, 15 ]
sort: 0.111ms
 */
