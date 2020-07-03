/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
class SelectionSort {
  arr: Array<number>;
  constructor(arr) {
    this.arr = this.selectionSort2(arr);
  }
  // 标准版
  selectionSort(arr: Array<number>) {
    console.time("time");
    let min: number, minIdx: number, tmp: number;
    let l = arr.length;
    for (let i = 0; i < l - 1; i++) {
      min = arr[i];
      minIdx = i;
      let j = i + 1;
      for (; j < l; j++) {
        // 从待排序列表找到最小值和位置
        if (arr[j] < min) {
          min = arr[j];
          minIdx = j;
        }
      }
      console.log(
        "i=" + i,
        " j=" + j,
        "min=" + min,
        "minIdx=" + minIdx,
        "arr[]=",
        arr
      );
      // 将待排序里最小值交换到已排序最后面
      if (minIdx !== i) {
        tmp = arr[i];
        arr[i] = min;
        arr[minIdx] = tmp;
      }
    }
    console.timeEnd("time");
    return arr;
  }

  // 新建数组版，无需交换
  selectionSort2(arr: Array<number>) {
    console.time("time");
    let min: number, minIdx: number, newArr: number[] = [];
    let l = arr.length;
    for (let i = 0; i < l; i++) {
      min = arr[i];
      minIdx = i;
      let j = i + 1;
      for (; j < l; j++) {
        // 找到并记录下最小值和位置
        if (arr[j] < min) {
          min = arr[j];
          minIdx = j;
        }
      }
      console.log(
        "i=" + i,
        " j=" + j,
        "min=" + min,
        "minIdx=" + minIdx,
        "arr[]=",
        arr
      );
      // 将待排序里最小值添加到新数组中去
      newArr.push(min);
      // 原数组中删除对应的项
      arr.splice(minIdx, 1);
      l--;
      i--;
    }
    console.timeEnd("time");
    return newArr;
  }
}

(function () {
  const arr = [7, 11, 9, 10, 12, 13, 8];
  console.time("sort");
  console.log("origin:", arr);
  console.log("\r\nsorted:", new SelectionSort(arr).arr);
  console.timeEnd("sort");
})();
/**
jarrys-MacBook-Pro:selectionsort jarry$ tsc SelectionSort.ts -m es6
jarrys-MacBook-Pro:selectionsort jarry$ node SelectionSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8 ]
i=0  j=7 min=7 minIdx=0 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=1  j=7 min=8 minIdx=6 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=2  j=7 min=9 minIdx=2 arr[]= [ 7, 8, 9, 10, 12, 13, 11 ]
i=3  j=7 min=10 minIdx=3 arr[]= [ 7, 8, 9, 10, 12, 13, 11 ]
i=4  j=7 min=11 minIdx=6 arr[]= [ 7, 8, 9, 10, 12, 13, 11 ]
i=5  j=7 min=12 minIdx=6 arr[]= [ 7, 8, 9, 10, 11, 13, 12 ]
time: 1.027ms

sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 5.681ms
 */
