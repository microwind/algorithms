/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class InsertSort {
  arr: Array<any>
  constructor(arr: Array<any>) {
    this.insertSort1(arr.slice(0))
    this.insertSort2(arr.slice(0))
    this.insertSort3(arr.slice(0))
    this.insertSort4(arr.slice(0))
    this.insertSort5(arr.slice(0))
    this.arr = this.insertSort6(arr)
  }
  // TS标准版
  insertSort1(arr: Array<number>) {
    console.time('time')
    let j: number,
      current: number,
      l = arr.length
    // 外循环用于遍历待排序区间，内循环用来遍历已排序区间
    for (let i = 0; i < l; i++) {
      j = i
      current = arr[i]
      // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项(表示升序)时，将该位置右移
      // 直到遇到小于等于自己的项则停止移动，表示插入成功
      // console.log(
      //   'i=' + i,
      //   ' j=' + j,
      //   'current=' + current,
      //   'arr[i]=' + arr[i],
      //   'arr[j]=' + arr[j],
      //   'arr[]=',
      //   arr
      // )
      while (j-- > 0 && current < arr[j]) {
        // 逐个位移
        arr[j + 1] = arr[j]
      }
      // 交换为当前项
      arr[j + 1] = current
    }
    console.log('sort1:', arr)
    console.timeEnd('time')
    return arr
  }

  // 标准通用版
  insertSort2(arr: number[]) {
    console.time('time')
    let j: number,
      current: number,
      l = arr.length
    for (var i = 0; i < l; i++) {
      j = i - 1
      current = arr[i]
      // console.log(
      //   'i=' + i,
      //   ' j=' + j,
      //   'current=' + current,
      //   'arr[i]=' + arr[i],
      //   'arr[j+1]=' + arr[j + 1],
      //   'arr[]=',
      //   arr
      // )
      while (j >= 0 && current < arr[j]) {
        arr[j + 1] = arr[j]
        j--
      }
      arr[j + 1] = current
    }
    console.log('sort2:', arr)
    console.timeEnd('time')
    return arr
  }

  // splice版本
  insertSort3<T>(arr: Array<T>) {
    console.time('time')
    let j: number,
      current: T,
      l = arr.length,
      isMin: boolean
    for (let i = 1; i < l; i++) {
      j = i - 1
      current = arr.splice(i, 1)[0]
      isMin = true
      while (j >= 0) {
        if (current > arr[j]) {
          // console.log(
          //   'i=' + i,
          //   ' j=' + j,
          //   'current=' + current,
          //   'arr[i]=' + arr[i],
          //   'arr[j]=' + arr[j],
          //   'arr[]=',
          //   arr
          // )
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
    console.log('sort3:', arr)
    console.timeEnd('time')
    return arr
  }

  // 新建数组版
  insertSort4(arr: Array<any>) {
    console.time('time')
    let j: number,
      len: number,
      l = arr.length,
      isMax: boolean
    const newArr = arr.slice(0, 1)
    for (var i = 1; i < l; i++) {
      isMax = true
      for (let j = 0, len = newArr.length; j < len; j++) {
        // console.log(
        //   'i=' + i,
        //   ' j=' + j,
        //   'arr[i]=' + arr[i],
        //   'newArr[j]=' + newArr[j],
        //   'arr[]=',
        //   arr
        // )
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
    console.warn('sort4 newArr:', newArr)
    console.timeEnd('time')
    return newArr
  }

  // 新建数组版倒序遍历
  insertSort5(arr: Array<number>) {
    console.time('time')
    let l = arr.length,
      len: number,
      isMin: boolean
    const newArr = arr.slice(0, 1)
    for (let i = 1; i < l; i++) {
      isMin = true
      len = newArr.length
      while (len--) {
        // console.log(
        //   'i=' + i,
        //   ' len=' + len,
        //   'arr[i]=' + arr[i],
        //   'newArr[len]=' + newArr[len],
        //   'arr[]=',
        //   arr
        // )
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
    console.warn('sort5 newArr:', newArr)
    console.timeEnd('time')
    return newArr
  }

  // 新建数组版挪动插入版
  insertSort6(arr: Array<number>) {
    console.time('time')
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
    console.log('sort6:', arr)
    console.timeEnd('time')
    return newArr
  }
}

;(function () {
  const arr = [7, 11, 9, 10, 12, 13, 8]
  console.time('sort-all')
  console.log('origin:', arr)
  console.log('\r\nsorted:', new InsertSort(arr).arr)
  console.timeEnd('sort-all')
})()

/**
jarrys-mbp:insertsort jarry$ tsc InsertSort.ts -t es6
jarrys-mbp:insertsort jarry$ node InsertSort.js
origin: [
   7, 11, 9, 10,
  12, 13, 8
]
sort1: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.274ms
sort2: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.264ms
sort3: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.163ms
sort4 newArr: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 3.699ms
sort5 newArr: [
   7,  8,  9, 10,
  11, 12, 13
]
time: 0.121ms
sort6: [
   7, 11, 9, 10,
  12, 13, 8
]
time: 0.128ms

sorted: [
   7,  8,  9, 10,
  11, 12, 13
]
sort-all: 13.866ms
*/
