/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class QuickSort {
  // 1. 方式1, 递归新建数组版本。无需交换，每个分区都是新数组，数量庞大
  quickSort1(arr: Array<number>) {
    // 数组长度为1就不再分级
    if (arr.length <= 1) {
      return arr
    }
    console.log('split array:', arr)

    var pivot: number
    const left = Array<number>()
    const right = Array<number>()
    // 设置中间数
    var midIndex = Math.floor(arr.length / 2)
    pivot = arr[midIndex]

    for (var i = 0, l = arr.length; i < l; i++) {
      console.log(
        'i=' + i + ' midIndex=' + midIndex + ' pivot=' + pivot + ' arr[]=' + arr
      )
      // 当中间基数等于i时，跳过当前。中间数递归完成时合并
      if (midIndex === i) {
        continue
      }
      // 当前数组端里面的项小于基数则添加到左侧
      if (arr[i] < pivot) {
        left.push(arr[i])
        // 大于等于则添加到右侧
      } else {
        right.push(arr[i])
      }
    }

    arr = this.quickSort1(left).concat(pivot, this.quickSort1(right))
    // 递归调用遍历左侧和右侧，再将中间值连接起来
    return arr
  }

  /**

quick_sort recursion step:

      f([7, 11, 9, 10, 12, 13, 8])
            /       10          \
      f([7, 9, 8])           f([11, 12, 13])
        /   9    \             /    12     \
   f([7, 8])    f([])       f([11])       f[13]
   /   8  \
f([7]) f([]) 
  [7]
 */

// 把数组分按照基准值分为左右两部分，小于基准的在左侧，大于基准的在右侧，最后返回基准值的新下标
// 用于交换的基准值可以取右侧或左侧，若取中间则需要基于基准进行左右交换
  partition(arr: number[], left: number, right: number) {
    // pivot基准可以任意挑选，这里取右侧
    var pivotIndex = right
    var pivot = arr[pivotIndex]
    var partitionIndex = left
    for (var i = left; i < right; i++) {
      // 如果小于基准则进行交换，且交换位置右移
      if (arr[i] < pivot) {
        ;[arr[partitionIndex], arr[i]] = [arr[i], arr[partitionIndex]]
        partitionIndex++
      }
    }
    ;[arr[partitionIndex], arr[pivotIndex]] = [arr[pivotIndex], arr[partitionIndex]]
    console.log(
      'partitionIndex:',
      partitionIndex,
      'arr[partitionIndex]',
      arr[partitionIndex],
      arr.slice(left, partitionIndex),
      arr.slice(partitionIndex, right)
    )
    return partitionIndex
  }
  // 方式2, 标准递归版本。左右不断分区交换，无需新建数组。
  quickSort2(arr: number[], left: number, right: number) {
    left = left !== undefined ? left : 0
    right = right !== undefined ? right : arr.length - 1
    if (left < right) {
      var pivot = this.partition(arr, left, right)
      this.quickSort2(arr, left, pivot - 1)
      this.quickSort2(arr, pivot + 1, right)
    }
    return arr
  }

  // 2. 方式3, 标准递归版本。需要左右不断交换，无需新建数组。
  quickSort3(arr: Array<number>, left: number, right: number) {
    var i = (left = left ? left : 0)
    var j = (right = right ? right : arr.length - 1)
    var midIndex = Math.floor((i + j) / 2)
    var pivot = arr[midIndex]

    // 当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
      // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
      while (arr[i] < pivot) {
        console.log(
          'arr[i] < pivot:',
          ' i=' + i + ' j=' + j + ' pivot=' + pivot
        )
        i++
      }
      // 当前右侧大于基准时左移，直到找出比基准值小的位置来
      while (arr[j] > pivot) {
        console.log(
          'arr[j] > pivot:',
          ' i=' + i + ' j=' + j + ' pivot=' + pivot
        )
        j--
      }

      // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
      if (i <= j) {
        ;[arr[i], arr[j]] = [arr[j], arr[i]]
        // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
        i++
        j--
      }
    }

    // 左侧小于基数位置，不断递归左边部分
    if (left < j) {
      this.quickSort3(arr, left, j)
    }
    // 基数位置小于右侧，不断递归右侧部分
    if (i < right) {
      this.quickSort3(arr, i, right)
    }

    return arr
  }

  // 4, 方式4, 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
  quickSort4(arr: Array<number>) {
    let left = 0
    let right = arr.length - 1

    var stack = Array<number>(),
      i: number,
      j: number,
      midIndex: number,
      pivot: number,
      tmp: number
    // 与标准递归版相同，只是将递归改为遍历栈的方式
    // 先将左右各取一个入栈
    stack.push(left)
    stack.push(right)

    while (stack.length > 0 ) {
      // 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
      const lastItem1 = stack.pop()
      const lastItem2 = stack.pop()
      if (lastItem1 === undefined || lastItem2 === undefined) {
        break
      }

      j = right = lastItem1
      i = left = lastItem2

      midIndex = Math.floor((i + j) / 2)
      pivot = arr[midIndex]
      while (i <= j) {
        while (arr[i] < pivot) {
          console.log(
            'arr[i] < pivot:',
            ' i=' + i + ' j=' + j + ' pivot=' + pivot + ' arr[]=' + arr
          )
          i++
        }
        while (arr[j] > pivot) {
          console.log(
            'arr[j] > pivot:',
            ' i=' + i + ' j=' + j + ' pivot=' + pivot + ' arr[]=' + arr
          )
          j--
        }

        if (i <= j) {
          tmp = arr[j]
          arr[j] = arr[i]
          arr[i] = tmp
          i++
          j--
        }
      }
      if (left < j) {
        // 与递归版不同，这里添加到栈中，以便继续循环
        stack.push(left)
        stack.push(j)
      }
      if (i < right) {
        stack.push(i)
        stack.push(right)
      }
    }

    return arr
  }
}

// test
;(function () {
  const quickSort = new QuickSort()
  const arr = [7, 11, 9, 10, 12, 13, 8]
  console.time('sort1')
  const arr1 = arr.slice(0)
  console.log('sort1 origin:', arr1)
  console.log('\r\nquickSort1 sorted:', quickSort.quickSort1(arr1))
  console.timeEnd('sort1')

  console.time('sort2')
  const arr2 = arr.slice(0)
  console.log('sort2 origin:', arr2)
  console.log('\r\nquickSort2 sorted:', quickSort.quickSort2(arr2, 0, arr2.length - 1))
  console.timeEnd('sort2')

  console.time('sort3')
  const arr3 = arr.slice(0)
  console.log('sort3 origin:', arr3)
  console.log('\r\nquickSort3 sorted:', quickSort.quickSort3(arr3, 0, arr3.length - 1))
  console.timeEnd('sort3')

  console.time('sort4')
  const arr4 = arr.slice(0)
  console.log('sort4 origin:', arr4)
  console.log('\r\nquickSort4 sorted:', quickSort.quickSort4(arr4))
  console.timeEnd('sort4')
})()

/**
jarrys-MacBook-Pro:quicksort jarry$ tsc QuickSort.ts -m es2022
jarry@jarrys-MacBook-Pro quicksort % node QuickSort.js
sort1 origin: [
   7, 11, 9, 10,
  12, 13, 8
]
split array: [
   7, 11, 9, 10,
  12, 13, 8
]
i=0 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=1 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=2 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=3 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=4 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=5 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=6 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
split array: [ 7, 9, 8 ]
i=0 midIndex=1 pivot=9 arr[]=7,9,8
i=1 midIndex=1 pivot=9 arr[]=7,9,8
i=2 midIndex=1 pivot=9 arr[]=7,9,8
split array: [ 7, 8 ]
i=0 midIndex=1 pivot=8 arr[]=7,8
i=1 midIndex=1 pivot=8 arr[]=7,8
split array: [ 11, 12, 13 ]
i=0 midIndex=1 pivot=12 arr[]=11,12,13
i=1 midIndex=1 pivot=12 arr[]=11,12,13
i=2 midIndex=1 pivot=12 arr[]=11,12,13

quickSort1 sorted: [
   7,  8,  9, 10,
  11, 12, 13
]
sort1: 10.698ms
sort2 origin: [
   7, 11, 9, 10,
  12, 13, 8
]
partitionIndex: 1 arr[partitionIndex] 8 [ 7 ] [ 8, 9, 10, 12, 13 ]
partitionIndex: 4 arr[partitionIndex] 11 [ 9, 10 ] [ 11, 13 ]
partitionIndex: 3 arr[partitionIndex] 10 [ 9 ] []
partitionIndex: 5 arr[partitionIndex] 12 [] [ 12 ]

quickSort2 sorted: [
   7,  8,  9, 10,
  11, 12, 13
]
sort2: 1.16ms
sort3 origin: [
   7, 11, 9, 10,
  12, 13, 8
]
arr[i] < pivot:  i=0 j=6 pivot=10
arr[i] < pivot:  i=2 j=5 pivot=10
arr[j] > pivot:  i=3 j=5 pivot=10
arr[j] > pivot:  i=3 j=4 pivot=10
arr[i] < pivot:  i=0 j=2 pivot=8
arr[j] > pivot:  i=1 j=2 pivot=8
arr[i] < pivot:  i=4 j=6 pivot=13

quickSort3 sorted: [
   7,  8,  9, 10,
  11, 12, 13
]
sort3: 0.631ms
sort4 origin: [
   7, 11, 9, 10,
  12, 13, 8
]
arr[i] < pivot:  i=0 j=6 pivot=10 arr[]=7,11,9,10,12,13,8
arr[i] < pivot:  i=2 j=5 pivot=10 arr[]=7,8,9,10,12,13,11
arr[j] > pivot:  i=3 j=5 pivot=10 arr[]=7,8,9,10,12,13,11
arr[j] > pivot:  i=3 j=4 pivot=10 arr[]=7,8,9,10,12,13,11
arr[i] < pivot:  i=4 j=6 pivot=13 arr[]=7,8,9,10,12,13,11
arr[i] < pivot:  i=0 j=2 pivot=8 arr[]=7,8,9,10,11,12,13
arr[j] > pivot:  i=1 j=2 pivot=8 arr[]=7,8,9,10,11,12,13

quickSort4 sorted: [
   7,  8,  9, 10,
  11, 12, 13
]
sort4: 0.378ms
 */
