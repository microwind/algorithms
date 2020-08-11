/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class RadixSort {
  constructor() {}

  // 基数排序，基于计数排序的基础上，按数字的每个位置来排序
  countingSort(arr: Array<number>, exp: number) {
    const countList = [];
    const size = 10;
    countList.length = size;
    countList.fill(0);
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i];
      // 取得数字的最后一位，并给对应计数数组加1
      const idx = Math.floor((item / exp) % size);
      countList[idx] += 1;
    }
    console.log("countingSort countList:", countList);

    // 根据位置计数，后面的位数为前面的累加之和
    for (let i = 1; i < size; i++) {
      countList[i] += countList[i - 1];
      // console.log("add position:", countList[i], countList);
    }

    const output = [];
    // 根据计数数组按顺序取出排序内容
    for (let i = arr.length - 1; i >= 0; i--) {
      const idx = Math.floor((arr[i] / exp) % size);
      output[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
      // console.log("set order:", idx, countList[idx], i, countList, output);
    }

    // 最后赋值给原数据
    for (let i = 0; i < arr.length; i++) {
      arr[i] = output[i];
    }
    console.log("set output:", arr, output);
    return output;
  }

  sort(arr: Array<number>) {
    let output = [];
    const max = Math.max.apply(null, arr);
    for (let radix = 1; Math.floor(max / radix) > 0; radix *= 10) {
      output = this.countingSort(arr, radix);
    }
    return output;
  }
}

// test
(function () {
  const arr1 = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431];
  console.time("radixSort");
  console.log("origin radixSort:", arr1);
  const radixSort = new RadixSort();
  console.log("radixSort sorted:", radixSort.sort(arr1));
  console.timeEnd("radixSort");
})();

/**
jarry@jarrys-MacBook-Pro radixsort % tsc RadixSort.ts -t es2020
jarry@jarrys-MacBook-Pro radixsort % node RadixSort.js         
origin radixSort: [ 33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431 ]
countingSort countList: [ 2, 1, 0, 2, 2, 2, 0, 1, 0, 0 ]
set output: [ 10, 200, 87431, 33, 43, 4, 323454, 15, 1235, 7 ] [ 10, 200, 87431, 33, 43, 4, 323454, 15, 1235, 7 ]
countingSort countList: [ 3, 2, 0, 3, 1, 1, 0, 0, 0, 0 ]
set output: [ 200, 4, 7, 10, 15, 87431, 33, 1235, 43, 323454 ] [ 200, 4, 7, 10, 15, 87431, 33, 1235, 43, 323454 ]
countingSort countList: [ 6, 0, 2, 0, 2, 0, 0, 0, 0, 0 ]
set output: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
countingSort countList: [ 7, 1, 0, 1, 0, 0, 0, 1, 0, 0 ]
set output: [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ]
countingSort countList: [ 8, 0, 1, 0, 0, 0, 0, 0, 1, 0 ]
set output: [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ]
countingSort countList: [ 9, 0, 0, 1, 0, 0, 0, 0, 0, 0 ]
set output: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort sorted: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort: 6.963ms
 */
