
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

class ShellSort {

  /* 1. 希尔排序标准版，基于插入排序进行分组排序，步长按1/2缩减。 */
  static int[] shellSort1(int arr[]) {
    int len = arr.length;
    // 设置分组增量值（步长）为1/2的数组长度
    int gap = len / 2;

    // 根据步长得到子序列如果间隔大于0，则表示还可以继续分组
    while (gap > 0) {
      for (int i = gap; i < len; i++) {
        int current = arr[i];
        int j = i;
        // 根据步长得到子序列，对子序列按照插入排序
        while (j >= gap && current < arr[j - gap]) {
          System.out.println("gap=" + gap + " i=" + i + " j=" + j + " arr:" + Arrays.toString(arr));
          arr[j] = arr[j - gap];
          j -= gap;
        }
        // 交换当前项
        arr[j] = current;
      }
      // 缩短一半步长
      gap = gap / 2;
    }
    return arr;
  }

  /* 2. 希尔排序，基于插入排序进行分组排序，步长按3倍递减。 */
  public static int[] shellSort2(int[] arr) {

    int len = arr.length;
    int gap = 1;
    // 初始步长按3倍递增，小于1/3数组长度
    while (gap < len / 3) {
      gap = gap * 3 + 1;
    }

    // 如果间隔大于0，则表示还可以继续分组
    while (gap > 0) {
      for (int i = gap; i < len; i++) {
        int current = arr[i];
        int j = i - gap;
        // 根据步长得到子序列，对子序列按照插入排序
        for (; j >= 0 && arr[j] > current; j -= gap) {
          System.out.println("gap=" + gap + " i=" + i + " j=" + j + " arr:" + Arrays.toString(arr));
          arr[j + gap] = arr[j];
        }
        arr[j + gap] = current;
      }
      // 步长按3倍缩减
      gap /= 3;
    }

    return arr;
  }

  // test
  public static void main(String args[]) {
    int arr[] = { 33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431 };
    System.out.println("arr1 start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    arr = ShellSort.shellSort1(arr);
    System.out.println("arr1 sorted:" + Arrays.toString(arr));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    int arr2[] = { 33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431 };
    System.out.println("arr2 start:" + Arrays.toString(arr2));
    long startTime2 = System.currentTimeMillis();
    arr = ShellSort.shellSort2(arr2);
    System.out.println("arr2 sorted:" + Arrays.toString(arr2));
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
  }
}

/**
 * jarry@jarrys-MacBook-Pro shellsort % javac ShellSort.java
 * jarry@jarrys-MacBook-Pro shellsort % java ShellSort
 * arr1 start:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
 * gap=5 i=5 j=5 arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
 * gap=5 i=9 j=9 arr:[-7, 4, 15, 43, 323454, 33, 10, 1235, 200, 87431]
 * gap=2 i=5 j=5 arr:[-7, 4, 15, 43, 87431, 33, 10, 1235, 200, 323454]
 * gap=2 i=6 j=6 arr:[-7, 4, 15, 33, 87431, 43, 10, 1235, 200, 323454]
 * gap=2 i=6 j=4 arr:[-7, 4, 15, 33, 87431, 43, 87431, 1235, 200, 323454]
 * gap=2 i=8 j=8 arr:[-7, 4, 10, 33, 15, 43, 87431, 1235, 200, 323454]
 * gap=1 i=4 j=4 arr:[-7, 4, 10, 33, 15, 43, 200, 1235, 87431, 323454]
 * arr1 sorted:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
 * 
 * time:19 ms.
 * arr2 start:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
 * gap=4 i=5 j=1 arr:[33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431]
 * gap=4 i=6 j=2 arr:[33, -7, 15, 43, 323454, 4, 10, 1235, 200, 87431]
 * gap=4 i=8 j=4 arr:[33, -7, 10, 43, 323454, 4, 15, 1235, 200, 87431]
 * gap=1 i=1 j=0 arr:[33, -7, 10, 43, 200, 4, 15, 1235, 323454, 87431]
 * gap=1 i=2 j=1 arr:[-7, 33, 10, 43, 200, 4, 15, 1235, 323454, 87431]
 * gap=1 i=5 j=4 arr:[-7, 10, 33, 43, 200, 4, 15, 1235, 323454, 87431]
 * gap=1 i=5 j=3 arr:[-7, 10, 33, 43, 200, 200, 15, 1235, 323454, 87431]
 * gap=1 i=5 j=2 arr:[-7, 10, 33, 43, 43, 200, 15, 1235, 323454, 87431]
 * gap=1 i=5 j=1 arr:[-7, 10, 33, 33, 43, 200, 15, 1235, 323454, 87431]
 * gap=1 i=6 j=5 arr:[-7, 4, 10, 33, 43, 200, 15, 1235, 323454, 87431]
 * gap=1 i=6 j=4 arr:[-7, 4, 10, 33, 43, 200, 200, 1235, 323454, 87431]
 * gap=1 i=6 j=3 arr:[-7, 4, 10, 33, 43, 43, 200, 1235, 323454, 87431]
 * gap=1 i=9 j=8 arr:[-7, 4, 10, 15, 33, 43, 200, 1235, 323454, 87431]
 * arr2 sorted:[-7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454]
 * 
 * time:1 ms.
 * jarry@jarrys-MacBook-Pro shellsort %
 */
