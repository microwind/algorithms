
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.Arrays;

class InsertSort {

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

  public static int[] insertSort2(final int arr[]) {
    for (int i = 0; i < arr.length; i++) {
      int j = i - 1;
      final int current = arr[i];
      System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
      for (; j >= 0 && current < arr[j]; j--) {
        arr[j + 1] = arr[j];
      }
      arr[j + 1] = current;
    }
    return arr;
  }

  // ASE
  static int[] insertSort(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
      int current = arr[i];
      int j = i - 1;
      System.out.println("i=" + i + " j=" + j + " current=" + current + " arr[i]=" + arr[i] + " arr[j + 1]=" + arr[j + 1] + " arr[]=" + Arrays.toString(arr));
      for (; j >= 0; j--) {
        if (current > arr[j]) {
          arr[j + 1] = arr[j];
        } else {
          break;
        }
      }
      arr[j + 1] = current;
    }
    return arr;
  }

  public static void main(final String args[]) {
    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("sort start:" + Arrays.toString(arr));
    final long startTime = System.currentTimeMillis();
    arr = InsertSort.insertSort(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(arr));
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