/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 1. 希尔排序，基于插入排序进行了分组排序
class ShellSort {
  arr: Array<number>;
  constructor(arr: Array<any>) {
    this.arr = arr;
  }

  shellSort1() {
    const arr = this.arr;
    const len = arr.length;
    //  设置分组间隔
    let gap = Math.floor(len / 2);
    // 如果间隔大于0，则表示还可以继续分
    while (gap > 0) {
      for (let i = 0; i < len; i++) {
        const current = arr[i];
        let j = i;
        console.log("gap=", gap, " j=", j, "arr:", arr);
        // 分组按照插入排序逐个位移
        while (j >= gap && current < arr[j - gap]) {
          arr[j] = arr[j - gap];
          j -= gap;
        }
        // 交换当前项
        arr[j] = current;
        // 调整间距为1/2
      }
      gap = Math.floor(gap / 2);
    }
    return arr;
  }
}

const arr1 = [33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431];
console.time("shellSort1");
console.log("origin shellSort1:", arr1);
const shellSort = new ShellSort(arr1);
console.log("shellSort1 sorted:", shellSort.shellSort1());
console.timeEnd("shellSort1");

/*
jarry@jarrys-MacBook-Pro shellsort % tsc ShellSort.ts -t es2020
jarry@jarrys-MacBook-Pro shellsort % node ShellSort.js         
origin shellSort1: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 0 arr: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 1 arr: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 2 arr: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 3 arr: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 4 arr: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 5 arr: [ 33, 4, 15, 43, 323454, -7, 10.5, 1235, 200, 87431 ]
gap= 5  j= 6 arr: [ -7, 4, 15, 43, 323454, 33, 10.5, 1235, 200, 87431 ]
gap= 5  j= 7 arr: [ -7, 4, 15, 43, 323454, 33, 10.5, 1235, 200, 87431 ]
gap= 5  j= 8 arr: [ -7, 4, 15, 43, 323454, 33, 10.5, 1235, 200, 87431 ]
gap= 5  j= 9 arr: [ -7, 4, 15, 43, 323454, 33, 10.5, 1235, 200, 87431 ]
gap= 2  j= 0 arr: [ -7, 4, 15, 43, 87431, 33, 10.5, 1235, 200, 323454 ]
gap= 2  j= 1 arr: [ -7, 4, 15, 43, 87431, 33, 10.5, 1235, 200, 323454 ]
gap= 2  j= 2 arr: [ -7, 4, 15, 43, 87431, 33, 10.5, 1235, 200, 323454 ]
gap= 2  j= 3 arr: [ -7, 4, 15, 43, 87431, 33, 10.5, 1235, 200, 323454 ]
gap= 2  j= 4 arr: [ -7, 4, 15, 43, 87431, 33, 10.5, 1235, 200, 323454 ]
gap= 2  j= 5 arr: [ -7, 4, 15, 43, 87431, 33, 10.5, 1235, 200, 323454 ]
gap= 2  j= 6 arr: [ -7, 4, 15, 33, 87431, 43, 10.5, 1235, 200, 323454 ]
gap= 2  j= 7 arr: [ -7, 4, 10.5, 33, 15, 43, 87431, 1235, 200, 323454 ]
gap= 2  j= 8 arr: [ -7, 4, 10.5, 33, 15, 43, 87431, 1235, 200, 323454 ]
gap= 2  j= 9 arr: [ -7, 4, 10.5, 33, 15, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 0 arr: [ -7, 4, 10.5, 33, 15, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 1 arr: [ -7, 4, 10.5, 33, 15, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 2 arr: [ -7, 4, 10.5, 33, 15, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 3 arr: [ -7, 4, 10.5, 33, 15, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 4 arr: [ -7, 4, 10.5, 33, 15, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 5 arr: [ -7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 6 arr: [ -7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 7 arr: [ -7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 8 arr: [ -7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454 ]
gap= 1  j= 9 arr: [ -7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454 ]
shellSort1 sorted: [ -7, 4, 10.5, 15, 33, 43, 200, 1235, 87431, 323454 ]
shellSort1: 7.525ms
*/
