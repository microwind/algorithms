/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
class RadixSort {
    // 基数排序，基于计数排序的基础上，按数字的每个位置来排序
    countingSort(arr, exponent) {
        const countList = Array();
        const range = 10;
        countList.length = range;
        countList.fill(0);
        const min = Math.min.apply(null, arr);
        for (let i = 0, l = arr.length; i < l; i++) {
            const item = arr[i] - min;
            // 取得数字的最后一位，并给对应计数数组加1
            const idx = Math.floor((item / exponent) % range);
            countList[idx] += 1;
        }
        console.log('countingSort countList:', countList);
        // 根据位置计数，后面的位数为前面的累加之和
        for (let i = 1; i < range; i++) {
            countList[i] += countList[i - 1];
        }
        const sortedList = Array();
        // 根据计数数组按顺序取出排序内容
        for (let i = arr.length - 1; i >= 0; i--) {
            const item = arr[i] - min;
            const idx = Math.floor((item / exponent) % range);
            sortedList[countList[idx] - 1] = arr[i];
            countList[idx] -= 1;
        }
        // 最后赋值给原数据
        for (let i = 0; i < arr.length; i++) {
            arr[i] = sortedList[i];
        }
        return sortedList;
    }
    // 基数排序LSD版，基于计数排序的基础，支持负数，按数字的每个位置来排序
    radixSort(arr) {
        let sortedList = Array();
        const max = Math.max.apply(null, arr);
        const min = Math.min.apply(null, arr);
        for (let exponent = 1; Math.floor((max - min) / exponent) > 0; exponent *= 10) {
            sortedList = this.countingSort(arr, exponent);
        }
        return sortedList;
    }
}
// test
;
(function () {
    const arr1 = [33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431];
    console.time('radixSort');
    console.log('origin radixSort:', arr1);
    const radixSort = new RadixSort();
    console.log('radixSort sorted:', radixSort.radixSort(arr1));
    console.timeEnd('radixSort');
})();
/**
jarry@jarrys-MacBook-Pro radixsort % tsc RadixSort.ts -t es2020
jarry@jarrys-MacBook-Pro radixsort % node RadixSort.js
origin radixSort: [
     33,      -4,  15,
     43, -323454,   7,
     10,    1235, 200,
  87431
]
countingSort countList: [
  2, 1, 0, 0, 2,
  1, 0, 2, 0, 2
]
countingSort countList: [
  1, 0, 0, 0, 0,
  2, 3, 0, 3, 1
]
countingSort countList: [
  1, 0, 0, 0, 6,
  0, 2, 0, 1, 0
]
countingSort countList: [
  2, 0, 0, 7, 1,
  0, 0, 0, 0, 0
]
countingSort countList: [
  1, 1, 8, 0, 0,
  0, 0, 0, 0, 0
]
countingSort countList: [
  1, 0, 0, 8, 1,
  0, 0, 0, 0, 0
]
radixSort sorted: [
  -323454,  -4,    7,
       10,  15,   33,
       43, 200, 1235,
    87431
]
radixSort: 8.439ms
 */
