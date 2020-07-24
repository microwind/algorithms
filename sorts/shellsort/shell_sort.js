/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 希尔排序，基于插入排序进行了分组排序
function shellSort1(arr) {
  const len = arr.length
  //  设置分组间隔
  let gap = Math.floor(len / 2)
  // 如果间隔大于0，则表示还可以继续分
  while (gap > 0) {
    for (let i = 0; i < len; i++) {
      const current = arr[i]
      let j = i
      console.log('gap=', gap, ' j=', j, 'arr:', arr)
      // 分组按照插入排序逐个位移
      while (j >= gap && current < arr[j - gap]) {
        arr[j] = arr[j - gap]
        j -= gap
      }
      // 交换当前项
      arr[j] = current
      // 调整间距为1/2
    }
    gap = Math.floor(gap / 2)
  }
  return arr
}

const arr1 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431]
console.time('shellSort1')
console.log('origin shellSort1:', arr1)
console.log('shellSort1 sorted:', shellSort1(arr1))
console.timeEnd('shellSort1')

/*
jarry@jarrys-MacBook-Pro shellsort % node shell_sort.js
*/
