/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;
class RadixSort {
  RadixSort() {

  }

  // 基数排序，基于计数排序的基础上，按数字的每个位置来排序
  public static int[] countingSort(int arr[], int exp) {
    int[] countList = new int[10];
    int size = 10;
    for (int i = 0; i < arr.length; i++) {
      int item = arr[i];
      // 取得数字的最后一位，并给对应计数数组加1
      int idx = (item / exp) % size;
      countList[idx] += 1;
    }
    System.out.println("countingSort countList:" + Arrays.toString(countList));

    // 根据位置计数，后面的位数为前面的累加之和
    for (int i = 1; i < size; i++) {
      countList[i] += countList[i - 1];
    }

    int[] output = new int[arr.length];
    // 根据计数数组按顺序取出排序内容
    for (int i = arr.length - 1; i >= 0; i--) {
      int idx = (arr[i] / exp) % size;
      output[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 最后赋值给原数据
    for (int i = 0; i < arr.length; i++) {
      System.out.println("countingSort arr:" + Arrays.toString(arr));
      arr[i] = output[i];
    }
    return output;
  }

  public static int[] sort(int arr[]) {
    int[] output = new int[arr.length];
    int max = arr[0];
    for (int i  = 0; i < arr.length; i++) {
      if (arr[i] > max) {
        max = arr[i];
      }
    }
    // 根据最大值，逐个按进位(基数)来应用排序
    for (int radix = 1; (max / radix) > 0; radix *= 10) {
      System.out.println("radix:" + radix);
      output = countingSort(arr, radix);
    }
    return output;
  }
  // test
  public static void main(String args[]) {
    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("sort start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    arr = RadixSort.sort(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(arr));
  }
}

/*
jarry@jarrys-MacBook-Pro radixsort % javac RadixSort.java
jarry@jarrys-MacBook-Pro radixsort % java RadixSort
sort start:[7, 11, 9, 10, 12, 13, 8]
radix:1
countingSort countList:[1, 1, 1, 1, 0, 0, 0, 1, 1, 1]
countingSort arr:[7, 11, 9, 10, 12, 13, 8]
countingSort arr:[10, 11, 9, 10, 12, 13, 8]
countingSort arr:[10, 11, 9, 10, 12, 13, 8]
countingSort arr:[10, 11, 12, 10, 12, 13, 8]
countingSort arr:[10, 11, 12, 13, 12, 13, 8]
countingSort arr:[10, 11, 12, 13, 7, 13, 8]
countingSort arr:[10, 11, 12, 13, 7, 8, 8]
radix:10
countingSort countList:[3, 4, 0, 0, 0, 0, 0, 0, 0, 0]
countingSort arr:[10, 11, 12, 13, 7, 8, 9]
countingSort arr:[7, 11, 12, 13, 7, 8, 9]
countingSort arr:[7, 8, 12, 13, 7, 8, 9]
countingSort arr:[7, 8, 9, 13, 7, 8, 9]
countingSort arr:[7, 8, 9, 10, 7, 8, 9]
countingSort arr:[7, 8, 9, 10, 11, 8, 9]
countingSort arr:[7, 8, 9, 10, 11, 12, 9]

time:8 ms.
sorted:[7, 8, 9, 10, 11, 12, 13]
 */
