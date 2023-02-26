/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class RadixSort {
  // 基数排序，基于计数排序的基础上，按数字的每个位置来排序
  countingSort(arr: Array<number>, radix: number) {
    const countList = Array<number>()
    const range = 10;
    countList.length = range;
    countList.fill(0);
    for (let i = 0, l = arr.length; i < l; i++) {
      const item = arr[i];
      // 取得数字的最后一位，并给对应计数数组加1
      const idx = Math.floor((item / radix) % range);
      countList[idx] += 1;
    }
    console.log("countingSort countList:", countList);

    // 根据位置计数，后面的位数为前面的累加之和
    for (let i = 1; i < range; i++) {
      countList[i] += countList[i - 1];
    }

    const sortedList = Array<number>();
    // 根据计数数组按顺序取出排序内容
    for (let i = arr.length - 1; i >= 0; i--) {
      const idx = Math.floor((arr[i] / radix) % range);
      sortedList[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 最后赋值给原数据
    for (let i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i];
    }
    return sortedList;
  }

  radixSort(arr: Array<number>) {
    let sortedList = Array<number>();
    const max = Math.max.apply(null, arr);
    for (let radix = 1; Math.floor(max / radix) > 0; radix *= 10) {
      sortedList = this.countingSort(arr, radix);
    }
    return sortedList;
  }
}

// test
(function () {
  const arr1 = [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431];
  console.time("radixSort");
  console.log("origin radixSort:", arr1);
  const radixSort = new RadixSort();
  console.log("radixSort sorted:", radixSort.radixSort(arr1));
  console.timeEnd("radixSort");
})();

/**
jarry@jarrys-MacBook-Pro radixsort % tsc RadixSort.ts -t es2020
jarry@jarrys-MacBook-Pro radixsort % node RadixSort.js         
origin radixSort: [ 33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431 ]
countingSort countList: [ 2, 1, 0, 2, 2, 2, 0, 1, 0, 0 ]
set sortedList: [ 10, 200, 87431, 33, 43, 4, 323454, 15, 1235, 7 ] [ 10, 200, 87431, 33, 43, 4, 323454, 15, 1235, 7 ]
countingSort countList: [ 3, 2, 0, 3, 1, 1, 0, 0, 0, 0 ]
set sortedList: [ 200, 4, 7, 10, 15, 87431, 33, 1235, 43, 323454 ] [ 200, 4, 7, 10, 15, 87431, 33, 1235, 43, 323454 ]
countingSort countList: [ 6, 0, 2, 0, 2, 0, 0, 0, 0, 0 ]
set sortedList: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
countingSort countList: [ 7, 1, 0, 1, 0, 0, 0, 1, 0, 0 ]
set sortedList: [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ]
countingSort countList: [ 8, 0, 1, 0, 0, 0, 0, 0, 1, 0 ]
set sortedList: [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 323454, 87431 ]
countingSort countList: [ 9, 0, 0, 1, 0, 0, 0, 0, 0, 0 ]
set sortedList: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ] [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort sorted: [ 4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454 ]
radixSort: 6.963ms
 */
