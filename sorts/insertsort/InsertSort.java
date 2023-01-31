
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.Arrays;

class InsertSort {

  // java插入排序标准版
  static int[] insertSort1(final int[] arr) {
    for (int i = 0; i < arr.length; i++) {
      int j = i;
      // save current item's value before
      final int current = arr[j];
      System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j]=" + arr[j] + " arr[]=" + Arrays.toString(arr));
      while (j-- > 0 && current < arr[j]) {
        // if current less than arr[j], move arr[j] to right one by one
        arr[j + 1] = arr[j];
      }
      // insert current item to ordered queue
      arr[j + 1] = current;
    }
    return arr;
  }

  // java插入排序for循环升序版
  public static int[] insertSort2(final int arr[]) {
    for (int i = 0; i < arr.length; i++) {
      int j = i - 1;
      final int current = arr[i];
      System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
      for (; j >= 0 && current < arr[j]; j--) {
        // 如果当前项比已排序项小，把已比较项逐个右移，空出位置来给当前项
        arr[j + 1] = arr[j];
      }
      arr[j + 1] = current;
    }
    return arr;
  }

  // java插入排序for循环降序版
  static int[] insertSort3(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
      int current = arr[i];
      int j = i - 1;
      System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
      for (; j >= 0; j--) {
        // 当前项比已排序的内容要大，则逐个右移，空出位置
        if (current > arr[j]) {
          arr[j + 1] = arr[j];
        } else {
          // 当小于已排序内容，则跳出循环
          break;
        }
      }
      arr[j + 1] = current;
    }
    return arr;
  }

  public static void main(final String args[]) {
    int arr1[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("\r\nsort1 start:" + Arrays.toString(arr1));
    final long startTime1 = System.currentTimeMillis();
    arr1 = InsertSort.insertSort1(arr1);
    System.out.println("time:" + (System.currentTimeMillis() - startTime1) + " ms.");
    System.out.println("sort1 result:" + Arrays.toString(arr1));

    int arr2[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("\r\nort2 start:" + Arrays.toString(arr2));
    final long startTime2 = System.currentTimeMillis();
    arr2 = InsertSort.insertSort2(arr2);
    System.out.println("time:" + (System.currentTimeMillis() - startTime2) + " ms.");
    System.out.println("sort2 result:" + Arrays.toString(arr2));

    int arr3[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("\r\nsort start:" + Arrays.toString(arr3));
    final long startTime3 = System.currentTimeMillis();
    arr3 = InsertSort.insertSort3(arr3);
    System.out.println("time:" + (System.currentTimeMillis() - startTime3) + " ms.");
    System.out.println("sort3 result:" + Arrays.toString(arr3));
  }

}

/**
jarrys-MacBook-Pro:insertsort jarry$ javac InsertSort.java
jarrys-MacBook-Pro:insertsort jarry$ java InsertSort
sort start:[7, 11, 9, 10, 12, 13, 8]
i=0 j=0 current=7 arr[i]=7 arr[j]=7 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=1 j=1 current=11 arr[i]=11 arr[j]=11 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=2 j=2 current=9 arr[i]=9 arr[j]=9 arr[]=[7, 11, 9, 10, 12, 13, 8]
i=3 j=3 current=10 arr[i]=10 arr[j]=10 arr[]=[7, 9, 11, 10, 12, 13, 8]
i=4 j=4 current=12 arr[i]=12 arr[j]=12 arr[]=[7, 9, 10, 11, 12, 13, 8]
i=5 j=5 current=13 arr[i]=13 arr[j]=13 arr[]=[7, 9, 10, 11, 12, 13, 8]
i=6 j=6 current=8 arr[i]=8 arr[j]=8 arr[]=[7, 9, 10, 11, 12, 13, 8]

time:40 ms.
sorted:[7, 8, 9, 10, 11, 12, 13
 */