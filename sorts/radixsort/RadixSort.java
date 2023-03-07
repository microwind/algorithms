
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

class RadixSort {

  // 基数排序，基于计数排序，按数位从低到高来排序
  public static int[] countingSort(int arr[], int exponent) {
    // 基数exponent按10进位，range为10
    int range = 10;
    int[] countList = new int[range];
    int[] sortedList = new int[arr.length];

    // 设定最小值以支持负数
    int min = arr[0];
    for (int i = 0; i < arr.length; i++) {
      if (arr[i] < min) {
        min = arr[i];
      }
    }

    // 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    for (int i = 0; i < arr.length; i++) {
      int item = arr[i] - min;
      // 根据exponent获得当前位置的数字是几，存入对应计数数组
      int idx = (item / exponent) % range;
      countList[idx] += 1;
    }

    // 根据位置计数，后面的位数为前面的累加之和
    for (int i = 1; i < range; i++) {
      countList[i] += countList[i - 1];
    }
    System.out.println("radixSort1 countingSort countList:" + Arrays.toString(countList));

    // 根据计数数组按顺序取出排序内容
    for (int i = arr.length - 1; i >= 0; i--) {
      int item = arr[i] - min;
      int idx = (item / exponent) % range;
      // 根据计数位置得到顺序
      sortedList[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 最后赋值给原数据
    for (int i = 0; i < arr.length; i++) {
      arr[i] = sortedList[i];
    }
    System.out.println("radixSort1 -> sortedList:" + Arrays.toString(sortedList));
    return sortedList;
  }

  // 基数排序1，按数位大小，基于计数排序实现
  public static int[] radixSort1(int arr[]) {
    int max = arr[0];
    for (int i = 0; i < arr.length; i++) {
      if (arr[i] > max) {
        max = arr[i];
      }
    }
    // 根据最大值，逐个按进位(基数)来应用排序，exponent即数位。
    for (int exponent = 1; (max / exponent) > 0; exponent *= 10) {
      countingSort(arr, exponent);
    }
    return arr;
  }

  // 基数排序2，基于计数排序实现，计数排序写在一个方法内
  public static int[] radixSort2(int arr[]) {
    int arrLen = arr.length;
    // 基数exponent按10进位，range为10
    int range = 10;
    int[] sortedList = new int[arrLen];
    int max = arr[0];
    for (int i = 0; i < arrLen; i++) {
      if (arr[i] > max) {
        max = arr[i];
      }
    }
    // 设定最小值以支持负数
    int min = arr[0];
    for (int i = 0; i < arr.length; i++) {
      if (arr[i] < min) {
        min = arr[i];
      }
    }

    // 根据基数求得当前项目对应位置的数值，并给对应计数数组位置加1
    // 从1开始，每10进位，逐位进行比较和排序，一直到最大减去最小数
    for (int exponent = 1; ((max - min) / exponent) > 0; exponent *= range) {

      // 计数数组，长度为10，0-9一共10个数字
      int[] countList = new int[range];
      // 根据基数得到当前位数，并给计数数组对应位置加1
      for (int i = 0; i < arrLen; i++) {
        int item = arr[i] - min;
        int idx = (item / exponent) % range;
        countList[idx] += 1;
      }

      // 计数排序构建，自前往后，逐个将上一项的值存入当前项
      for (int i = 1; i < range; i++) {
        countList[i] += countList[i - 1];
      }

      System.out.println("radixSort2 -> countList:" + Arrays.toString(countList));

      // 根据计数数组按顺序取出排序内容
      for (int i = arrLen - 1; i >= 0; i--) {
        int item = arr[i] - min;
        int idx = (item / exponent) % range;
        sortedList[countList[idx] - 1] = arr[i];
        countList[idx] -= 1;
      }

      System.out.println("radixSort2 -> sortedList:" + Arrays.toString(sortedList));
      // 将新顺序赋值给原数组
      for (int i = 0; i < arr.length; i++) {
        arr[i] = sortedList[i];
      }
    }

    return sortedList;
  }

  // test
  public static void main(String args[]) {
    int arr1[] = { 7, 11, -9, 10, 12, 13, 8 };
    System.out.println("sort1 start:" + Arrays.toString(arr1));
    long startTime = System.currentTimeMillis();
    arr1 = RadixSort.radixSort1(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sort1 sorted:" + Arrays.toString(arr1));

    int arr2[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
    System.out.println("sort2 start:" + Arrays.toString(arr2));
    long startTime2 = System.currentTimeMillis();
    arr2 = RadixSort.radixSort2(arr2);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
    System.out.println("sort2 sorted:" + Arrays.toString(arr2));
  }
}

/*
 * jarry@jarrys-MacBook-Pro radixsort % javac RadixSort.java
 * jarry@jarrys-MacBook-Pro radixsort % java RadixSort
 * sort1 start:[7, 11, -9, 10, 12, 13, 8]
 * radixSort1 countingSort countList:[2, 3, 4, 4, 4, 4, 5, 6, 6, 7]
 * radixSort1 -> sortedList:[11, -9, 12, 13, 7, 8, 10]
 * radixSort1 countingSort countList:[1, 4, 7, 7, 7, 7, 7, 7, 7, 7]
 * radixSort1 -> sortedList:[-9, 7, 8, 10, 11, 12, 13]
 * 
 * time:0 ms.
 * sort1 sorted:[-9, 7, 8, 10, 11, 12, 13]
 * sort2 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
 * radixSort2 -> countList:[2, 3, 3, 3, 5, 6, 6, 8, 8, 10]
 * radixSort2 -> sortedList:[-4, -323454, 7, 10, 200, 87431, 33, 43, 15, 1235]
 * radixSort2 -> countList:[1, 1, 1, 1, 1, 3, 6, 6, 9, 10]
 * radixSort2 -> sortedList:[-323454, -4, 200, 7, 10, 15, 87431, 33, 1235, 43]
 * radixSort2 -> countList:[1, 1, 1, 1, 7, 7, 9, 9, 10, 10]
 * radixSort2 -> sortedList:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 * radixSort2 -> countList:[2, 2, 2, 9, 10, 10, 10, 10, 10, 10]
 * radixSort2 -> sortedList:[-323454, 87431, -4, 7, 10, 15, 33, 43, 200, 1235]
 * radixSort2 -> countList:[1, 2, 10, 10, 10, 10, 10, 10, 10, 10]
 * radixSort2 -> sortedList:[-323454, 87431, -4, 7, 10, 15, 33, 43, 200, 1235]
 * radixSort2 -> countList:[1, 1, 1, 9, 10, 10, 10, 10, 10, 10]
 * radixSort2 -> sortedList:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 * 
 * time:1 ms.
 * sort2 sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 */
