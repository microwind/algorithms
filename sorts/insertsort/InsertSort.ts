/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class InsertSort {
  arr: Array<any>;
  constructor(arr: Array<any>) {
    this.arr = this.insertSort6(arr);
  }
  // JS标准版
  insertSort1(arr: Array<number>) {
    let j: number,
      current: number,
      l = arr.length;
    console.time("time");
    // 外循环用于遍历待排序区间，内循环用来遍历已排序区间
    for (let i = 0; i < l; i++) {
      j = i;
      current = arr[i];
      // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项(表示升序)时，将该位置右移
      // 直到遇到小于等于自己的项则停止移动，表示插入成功
      console.log(
        "i=" + i,
        " j=" + j,
        "current=" + current,
        "arr[i]=" + arr[i],
        "arr[j]=" + arr[j],
        "arr[]=",
        arr
      );
      while (j-- > 0 && current < arr[j]) {
        // 逐个位移
        arr[j + 1] = arr[j];
      }
      // 交换为当前项
      arr[j + 1] = current;
    }
    console.timeEnd("time");
    return arr;
  }

  // 标准通用版
  insertSort2(arr: number[]) {
    let j: number,
      current: number,
      l = arr.length;
    console.time("time");
    for (var i = 0; i < l; i++) {
      j = i - 1;
      current = arr[i];
      console.log(
        "i=" + i,
        " j=" + j,
        "current=" + current,
        "arr[i]=" + arr[i],
        "arr[j+1]=" + arr[j + 1],
        "arr[]=",
        arr
      );
      while (j >= 0 && current < arr[j]) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = current;
    }
    console.timeEnd("time");
    return arr;
  }

  // splice版本
  insertSort3<T>(arr: Array<T>) {
    let j: number,
      current: T,
      l = arr.length,
      isMin: boolean;
    console.time("time");
    for (let i = 1; i < l; i++) {
      j = i - 1;
      current = arr.splice(i, 1)[0];
      isMin = true;
      while (j >= 0) {
        if (current > arr[j]) {
          console.log(
            "i=" + i,
            " j=" + j,
            "current=" + current,
            "arr[i]=" + arr[i],
            "arr[j]=" + arr[j],
            "arr[]=",
            arr
          );
          // 利用splice插入
          arr.splice(j + 1, 0, current);
          isMin = false;
          break;
        }
        j--;
      }
      if (isMin) {
        arr.splice(0, 0, current);
      }
    }
    console.timeEnd("time");
    return arr;
  }

  // 新建数组版
  insertSort4(arr: Array<any>) {
    let j: number,
      len: number,
      l = arr.length,
      isMax: boolean;
    const newArr = arr.slice(0, 1);
    console.time("time");
    for (var i = 1; i < l; i++) {
      isMax = true;
      for (let j = 0, len = newArr.length; j < len; j++) {
        console.log(
          "i=" + i,
          " j=" + j,
          "arr[i]=" + arr[i],
          "newArr[j]=" + newArr[j],
          "arr[]=",
          arr
        );
        if (arr[i] < newArr[j]) {
          // 新建数组来插入到某个位置中
          newArr.splice(j, 0, arr[i]);
          isMax = false;
          break;
        }
      }
      if (isMax) {
        newArr.push(arr[i]);
      }
    }
    console.timeEnd("time");
    console.warn("newArr:", newArr);
    return newArr;
  }

  // 新建数组版倒序遍历
  insertSort5(arr: Array<number>) {
    let l = arr.length,
      len: number,
      isMin: boolean;
    const newArr = arr.slice(0, 1);

    for (let i = 1; i < l; i++) {
      isMin = true;
      len = newArr.length;
      while (len--) {
        console.log(
          "i=" + i,
          " len=" + len,
          "arr[i]=" + arr[i],
          "newArr[len]=" + newArr[len],
          "arr[]=",
          arr
        );
        if (arr[i] > newArr[len]) {
          newArr.splice(len + 1, 0, arr[i]);
          isMin = false;
          break;
        }
      }
      if (isMin) {
        newArr.unshift(arr[i]);
      }
    }
    console.warn("newArr:", newArr);
    return newArr;
  }

  // 新建数组版挪动插入版
  insertSort6(arr: Array<number>) {
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
}

(function () {
  const arr = [7, 11, 9, 10, 12, 13, 8];
  console.time("sort");
  console.log("origin:", arr);
  console.log("\r\nsorted:", new InsertSort(arr).arr);
  console.timeEnd("sort");
})();

/**
jarrys-mbp:insertsort jarry$ tsc InsertSort.ts -t es6
jarrys-mbp:insertsort jarry$ node InsertSort.js
origin: [ 7, 11, 9, 10, 12, 13, 8 ]
i=0  j=0 current=7 arr[i]=7 arr[j]=7 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=1  j=1 current=11 arr[i]=11 arr[j]=11 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=2  j=2 current=9 arr[i]=9 arr[j]=9 arr[]= [ 7, 11, 9, 10, 12, 13, 8 ]
i=3  j=3 current=10 arr[i]=10 arr[j]=10 arr[]= [ 7, 9, 11, 10, 12, 13, 8 ]
i=4  j=4 current=12 arr[i]=12 arr[j]=12 arr[]= [ 7, 9, 10, 11, 12, 13, 8 ]
i=5  j=5 current=13 arr[i]=13 arr[j]=13 arr[]= [ 7, 9, 10, 11, 12, 13, 8 ]
i=6  j=6 current=8 arr[i]=8 arr[j]=8 arr[]= [ 7, 9, 10, 11, 12, 13, 8 ]
time: 0.938ms

sorted: [ 7, 8, 9, 10, 11, 12, 13 ]
sort: 5.169ms
   */
