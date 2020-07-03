/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class QuickSort {
  arr: Array<any>;
  constructor(arr: Array<any>) {
    // this.arr = this.quickSort(arr);
    // this.arr = this.quickSort2(arr, 0, arr.length - 1);
    this.arr = this.quickSort3(arr);
  }

  // 1. 方式1, 递归新建数组版本。无需交换，每个分区都是新数组，数量庞大
  quickSort(arr: Array<number>) {
    console.time("time");
    // 数组长度为1就不再分级
    if (arr.length <= 1) {
      return arr;
    }
    console.log("split array:", arr);

    var pivot: number;
    const left = [];
    const right = [];
    // 设置中间数
    var midIndex = Math.floor(arr.length / 2);
    pivot = arr[midIndex];

    for (var i = 0, l = arr.length; i < l; i++) {
      console.log(
        "i=" + i + " midIndex=" + midIndex + " pivot=" + pivot + " arr[]=" + arr
      );
      // 当中间基数等于i时，跳过当前。中间数递归完成时合并
      if (midIndex === i) {
        continue;
      }
      // 当前数组端里面的项小于基数则添加到左侧
      if (arr[i] < pivot) {
        left.push(arr[i]);
        // 大于等于则添加到右侧
      } else {
        right.push(arr[i]);
      }
    }

    console.timeEnd("time");
    arr = this.quickSort(left).concat(pivot, this.quickSort(right));
    console.log("sorted array:", arr);
    // 递归调用遍历左侧和右侧，再将中间值连接起来
    return arr;
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

jarrys-MacBook-Pro:quicksort jarry$ tsc QuickSort.ts -m es2020
jarrys-MacBook-Pro:quicksort jarry$ node QuickSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8 ]
split array: [ 7, 11, 9, 10, 12, 13, 8 ]
i=0 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=1 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=2 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=3 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=4 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=5 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
i=6 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
time: 1.419ms
split array: [ 7, 9, 8 ]
i=0 midIndex=1 pivot=9 arr[]=7,9,8
i=1 midIndex=1 pivot=9 arr[]=7,9,8
i=2 midIndex=1 pivot=9 arr[]=7,9,8
time: 0.388ms
split array: [ 7, 8 ]
i=0 midIndex=1 pivot=8 arr[]=7,8
i=1 midIndex=1 pivot=8 arr[]=7,8
time: 0.133ms
sorted array: [ 7, 8 ]
sorted array: [ 7, 8, 9 ]
split array: [ 11, 12, 13 ]
i=0 midIndex=1 pivot=12 arr[]=11,12,13
i=1 midIndex=1 pivot=12 arr[]=11,12,13
i=2 midIndex=1 pivot=12 arr[]=11,12,13
time: 0.265ms
sorted array: [ 11, 12, 13 ]
sorted array: [ 7, 8, 9, 10, 11, 12, 13 ]

sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 9.166ms
 */

  // 2. 方式2, 标准递归版本。需要左右不断交换，无需新建数组。
  quickSort2(arr: Array<number>, left: number, right: number) {
    console.time("time");
    var i = (left = left ? left : 0);
    var j = (right = right ? right : arr.length - 1);
    var midIndex = Math.floor((i + j) / 2);
    var pivot = arr[midIndex];

    // 当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
      // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
      while (arr[i] < pivot) {
        console.log(
          "arr[i] < pivot:",
          " i=" + i + " j=" + j + " pivot=" + pivot
        );
        i++;
      }
      // 当前右侧大于基准时左移，直到找出比基准值小的位置来
      while (arr[j] > pivot) {
        console.log(
          "arr[j] > pivot:",
          " i=" + i + " j=" + j + " pivot=" + pivot
        );
        j--;
      }

      console.log(
        "  left=" +
          left +
          " right=" +
          right +
          " i=" +
          i +
          " j=" +
          j +
          " midIndex=" +
          midIndex +
          " pivot=" +
          pivot +
          " arr[]=" +
          arr
      );

      // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
      if (i <= j) {
        [arr[i], arr[j]] = [arr[j], arr[i]];
        // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
        i++;
        j--;
      }
    }
    console.timeEnd("time");
    // 左侧小于基数位置，不断递归左边部分
    if (left < j) {
      console.log(
        "left < j:recursion:  left=" +
          left +
          " right=" +
          right +
          " i=" +
          i +
          " j=" +
          j +
          "arr[]" +
          arr
      );
      this.quickSort2(arr, left, j);
    }
    // 基数位置小于右侧，不断递归右侧部分
    if (i < right) {
      console.log(
        "i < right:recursion:  left=" +
          left +
          " right=" +
          right +
          " i=" +
          i +
          " j=" +
          j +
          " arr[]" +
          arr
      );
      this.quickSort2(arr, i, right);
    }

    return arr;
  }

  /**
jarrys-MacBook-Pro:quicksort jarry$ tsc QuickSort.ts -m es2020
jarrys-MacBook-Pro:quicksort jarry$ node QuickSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8 ]
arr[i] < pivot:  i=0 j=6 pivot=10
  left=0 right=6 i=1 j=6 midIndex=3 pivot=10 arr[]=7,11,9,10,12,13,8
arr[i] < pivot:  i=2 j=5 pivot=10
arr[j] > pivot:  i=3 j=5 pivot=10
arr[j] > pivot:  i=3 j=4 pivot=10
  left=0 right=6 i=3 j=3 midIndex=3 pivot=10 arr[]=7,8,9,10,12,13,11
time: 4.339ms
left < j:recursion:  left=0 right=6 i=4 j=2arr[]7,8,9,10,12,13,11
arr[i] < pivot:  i=0 j=2 pivot=8
arr[j] > pivot:  i=1 j=2 pivot=8
  left=0 right=2 i=1 j=1 midIndex=1 pivot=8 arr[]=7,8,9,10,12,13,11
time: 0.118ms
i < right:recursion:  left=0 right=6 i=4 j=2arr[]7,8,9,10,12,13,11
arr[i] < pivot:  i=4 j=6 pivot=13
  left=4 right=6 i=5 j=6 midIndex=5 pivot=13 arr[]=7,8,9,10,12,13,11
time: 0.063ms
left < j:recursion:  left=4 right=6 i=6 j=5arr[]7,8,9,10,12,11,13
  left=4 right=5 i=4 j=5 midIndex=4 pivot=12 arr[]=7,8,9,10,12,11,13
time: 0.038ms

sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 11.355ms
*/

  // 3, 方式3, 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。
  quickSort3(arr: Array<number>) {
    console.time("time");
    let left = 0;
    let right = arr.length - 1;

    var stack = [],
      i: number,
      j: number,
      midIndex: number,
      pivot: number,
      tmp: number;
    // 与标准递归版相同，只是将递归改为遍历栈的方式
    // 先将左右各取一个入栈
    stack.push(left);
    stack.push(right);

    while (stack.length) {
      // 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
      j = right = stack.pop();
      i = left = stack.pop();
      midIndex = Math.floor((i + j) / 2);
      pivot = arr[midIndex];
      while (i <= j) {
        while (arr[i] < pivot) {
          console.log(
            "arr[i] < pivot:",
            " i=" + i + " j=" + j + " pivot=" + pivot + " arr[]=" + arr
          );
          i++;
        }
        while (arr[j] > pivot) {
          console.log(
            "arr[j] > pivot:",
            " i=" + i + " j=" + j + " pivot=" + pivot + " arr[]=" + arr
          );
          j--;
        }

        if (i <= j) {
          tmp = arr[j];
          arr[j] = arr[i];
          arr[i] = tmp;
          i++;
          j--;
        }
      }
      if (left < j) {
        // 与递归版不同，这里添加到栈中，以便继续循环
        console.log(
          "left < j:recursion:  left=" +
            left +
            " right=" +
            right +
            " i=" +
            i +
            " j=" +
            j +
            " arr[]=" +
            arr
        );
        stack.push(left);
        stack.push(j);
      }
      if (i < right) {
        console.log(
          "i < right:recursion:  left=" +
            left +
            " right=" +
            right +
            " i=" +
            i +
            " j=" +
            j +
            " arr[]=" +
            arr
        );
        stack.push(i);
        stack.push(right);
      }
    }
    console.timeEnd("time");
    return arr;
  }
}

// test
(function () {
  const arr = [7, 11, 9, 10, 12, 13, 8];
  console.time("sort");
  console.log("origin:", arr);
  console.log("\r\nsorted:", new QuickSort(arr).arr);
  console.timeEnd("sort");
})();

/**
jarrys-MacBook-Pro:quicksort jarry$ tsc QuickSort.ts -m es2020
jarrys-MacBook-Pro:quicksort jarry$ node QuickSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8 ]
arr[i] < pivot:  i=0 j=6 pivot=10 arr[]=7,11,9,10,12,13,8
arr[i] < pivot:  i=2 j=5 pivot=10 arr[]=7,8,9,10,12,13,11
arr[j] > pivot:  i=3 j=5 pivot=10 arr[]=7,8,9,10,12,13,11
arr[j] > pivot:  i=3 j=4 pivot=10 arr[]=7,8,9,10,12,13,11
left < j:recursion:  left=0 right=6 i=4 j=2 arr[]=7,8,9,10,12,13,11
i < right:recursion:  left=0 right=6 i=4 j=2 arr[]=7,8,9,10,12,13,11
arr[i] < pivot:  i=4 j=6 pivot=13 arr[]=7,8,9,10,12,13,11
left < j:recursion:  left=4 right=6 i=6 j=5 arr[]=7,8,9,10,12,11,13
arr[i] < pivot:  i=0 j=2 pivot=8 arr[]=7,8,9,10,11,12,13
arr[j] > pivot:  i=1 j=2 pivot=8 arr[]=7,8,9,10,11,12,13
time: 1.447ms

sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 6.019ms
 */
