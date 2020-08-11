
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

class ShellSort {

  /* 1. 希尔排序，基于插入排序进行了分组排序 */
  static int[] shellSort(int arr[]) {
    int len = arr.length;
    // 设置分组间隔
    int gap = len / 2;
    // 如果间隔大于0，则表示还可以继续分
    while (gap > 0) {
      for (int i = 0; i < len; i++) {
        int current = arr[i];
        int j = i;
        System.out.println("gap=" + gap + " j=" + j + "arr:" + Arrays.toString(arr));
        // 分组按照插入排序逐个位移
        while (j >= gap && current < arr[j - gap]) {
          arr[j] = arr[j - gap];
          j -= gap;
        }
        // 交换当前项
        arr[j] = current;
        // 调整间距为1/2
      }
      gap = gap / 2;
    }
    return arr;
  }

  // test
  public static void main(String args[]) {
    int arr[] = { 33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431 };
    System.out.println("sort start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    arr = ShellSort.shellSort(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(arr));
  }
}

/**
jarry@jarrys-MacBook-Pro shellsort % javac ShellSort.java
jarry@jarrys-MacBook-Pro shellsort % java ShellSort 
sort start:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=0arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=1arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=2arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=3arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=4arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=5arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
gap=5 j=6arr:[-7, 4, 15, 43, 323454, 33, 10, 1235, 200, 87431]
gap=5 j=7arr:[-7, 4, 15, 43, 323454, 33, 10, 1235, 200, 87431]
gap=5 j=8arr:[-7, 4, 15, 43, 323454, 33, 10, 1235, 200, 87431]
gap=5 j=9arr:[-7, 4, 15, 43, 323454, 33, 10, 1235, 200, 87431]
gap=2 j=0arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
gap=2 j=1arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
gap=2 j=2arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
gap=2 j=3arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
gap=2 j=4arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
gap=2 j=5arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
gap=2 j=6arr:[-7, 4, 15, 33, 87431, 43, 10, 1235, 200, 323454]
gap=2 j=7arr:[-7, 4, 10, 33, 15, 43, 87431, 1235, 200, 323454]
gap=2 j=8arr:[-7, 4, 10, 33, 15, 43, 87431, 1235, 200, 323454]
gap=2 j=9arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
gap=1 j=0arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
gap=1 j=1arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
gap=1 j=2arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
gap=1 j=3arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
gap=1 j=4arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
gap=1 j=5arr:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
gap=1 j=6arr:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
gap=1 j=7arr:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
gap=1 j=8arr:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
gap=1 j=9arr:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]

time:15 ms.
sorted:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
 */
