
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

class RadixSortLSD {
  // 基数排序，由低位到高位，基于计数排序，非递归版
  static int[] radixSort(int[] arr) {
    int len = arr.length;
    // 获取数组最大项
    int max = arr[0];
    for (int i = 0; i < len; i++) {
      if (max < arr[i]) {
        max = arr[i];
      }
    }

    // 获取数组最小项
    int min = arr[0];
    for (int i = 0; i < len; i++) {
      if (min > arr[i]) {
        min = arr[i];
      }
    }

    // maxNumber设为最大减去最小，以便支持负数和减少数位
    int maxNumber = max - min;

    // 计算数组里最大项数字的位数
    int maxLength = 0;
    while (maxNumber > 0) {
      maxLength++;
      maxNumber /= 10;
    }
    // 或者通过log10求取
    // int maxLength = (int) (Math.log10(max - min) + 1);

    // 位数基准为10
    int range = 10;
    // 计数数组，长度也是10，分别放数字0-9
    int[] countList = new int[range];
    // 桶数组，长度是原数组长度
    int[] buckets = new int[len];

    // 逐位计算和排序，从低位到高位，从个位到高位
    for (int j = 1; j <= maxLength; j++) {

      // 计数数组清零
      for (int i = 0; i < range; i++) {
        countList[i] = 0;
      }

      // 根据基数得到当前位数，并给计数数组对应位置加1
      for (int i = 0; i < len; i++) {
        int item = arr[i] - min;
        // 逐位获取数组项的值，先除以数位得到当前数位上的值，再除以10取余
        // int idx = item / ((int)Math.pow(range, j - 1)) % range;
        int idx = getDigitByPosition(item, j);
        countList[idx]++;
      }

      System.out.println("countList counted:" + Arrays.toString(countList));

      // 计数排序构建，自前往后，逐个将上一项的值存入当前项
      for (int i = 1; i < range; i++) {
        countList[i] += countList[i - 1];
      }

      System.out.println("countList sorted:" + Arrays.toString(countList));

      // 根据计数数组按顺序取出排序内容
      for (int i = len - 1; i >= 0; i--) {
        int item = arr[i] - min;
        int idx = getDigitByPosition(item, j);
        buckets[countList[idx] - 1] = arr[i];
        countList[idx]--;
      }

      
      // 将新顺序赋值给原数组
      int i = 0;
      while (i < len) {
        arr[i] = buckets[i];
        i++;
      }
    }
    System.out.println("arr sorted:" + Arrays.toString(arr));
    return arr;
  }

  // 获取数字倒数第n位的值
  // 当num=1234, position=1时，返回4，position=2时，返回3
  static int getDigitByPosition(int num, int position) {
    return (num / ((int) Math.pow(10, position - 1))) % 10;
  }

  // test
  public static void main(String args[]) {
    int arr1[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
    // int arr1[] = { 33, 7, 10, 1235, 200, 87431 };
    System.out.println("sort1 start:" + Arrays.toString(arr1));
    long startTime = System.currentTimeMillis();
    arr1 = RadixSortLSD.radixSort(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sort1 sorted:" + Arrays.toString(arr1));
  }
}

/*
jarry@jarrys-MacBook-Pro radixsort % javac RadixSortLSD.java
jarry@jarrys-MacBook-Pro radixsort % java RadixSortLSD      
sort1 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
countList counted:[2, 1, 0, 0, 2, 1, 0, 2, 0, 2]
countList sorted:[2, 3, 3, 3, 5, 6, 6, 8, 8, 10]
countList counted:[1, 0, 0, 0, 0, 2, 3, 0, 3, 1]
countList sorted:[1, 1, 1, 1, 1, 3, 6, 6, 9, 10]
countList counted:[1, 0, 0, 0, 6, 0, 2, 0, 1, 0]
countList sorted:[1, 1, 1, 1, 7, 7, 9, 9, 10, 10]
countList counted:[2, 0, 0, 7, 1, 0, 0, 0, 0, 0]
countList sorted:[2, 2, 2, 9, 10, 10, 10, 10, 10, 10]
countList counted:[1, 1, 8, 0, 0, 0, 0, 0, 0, 0]
countList sorted:[1, 2, 10, 10, 10, 10, 10, 10, 10, 10]
countList counted:[1, 0, 0, 8, 1, 0, 0, 0, 0, 0]
countList sorted:[1, 1, 1, 9, 10, 10, 10, 10, 10, 10]
arr sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]

time:1 ms.
sort1 sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 */
