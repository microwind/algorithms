
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

class RadixSortMSD {
  // 基数排序，由高位到低位，基于计数排序
  static int[] radixSort(int[] arr) {
    return counting(arr, arr.length - 1, maxBit(arr));
  }

  // maxBit函数：计算数组的最大位数
  static int maxBit(int[] arr) {
    int max = arr[0];
    for (int i = 0; i < arr.length; i++) {
      if (max < arr[i])
        max = arr[i];
    }
    int digit = 0;
    while (max != 0) {
      digit++;
      max /= 10;
    }
    return digit;
  }

  // 计数排序
  static int[] counting(int[] arr, int len, int digit) {
    final int radix = 10;
    int j = 0;
    int[] count = new int[radix];
    int[] bucket = new int[len + 1];

    for (int d = 1; d <= digit; d++) {
      for (int i = 0; i < radix; i++) {
        count[i] = 0;
      }

      for (int i = 0; i <= len; i++) {
        j = getDigit(arr[i], d);
        count[j]++;
      }

      for (int i = 1; i < radix; i++) {
        count[i] += count[i - 1];
      }

      for (int i = len; i >= 0; i--) {
        j = getDigit(arr[i], d);
        bucket[count[j] - 1] = arr[i];
        count[j]--;
      }

      j = 0;
      for (int i = 0; i <= len; i++, j++) {
        arr[i] = bucket[j];
      }
    }
    return arr;
  }

  // getDigit函数
  // 返回数字x中第d位的数值.比如x=31, d=1时，返回1（31中第1位的数值为1）
  static int getDigit(int x, int d) {
    return (x / ((int) Math.pow(10, d - 1))) % 10;
  }

  // test
  public static void main(String args[]) {
    // int arr1[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
    int arr1[] = { 33, 7, 10, 1235, 200, 87431 };
    System.out.println("sort1 start:" + Arrays.toString(arr1));
    long startTime = System.currentTimeMillis();
    arr1 = RadixSortMSD.radixSort(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sort1 sorted:" + Arrays.toString(arr1));
  }
}

/*
jarry@jarrys-MacBook-Pro radixsort % javac RadixSortMSD.java
jarry@jarrys-MacBook-Pro radixsort % java RadixSortMSD      
sort1 start:[33, 7, 10, 1235, 200, 87431]

time:0 ms.
sort1 sorted:[7, 10, 33, 200, 1235, 87431]
 */
