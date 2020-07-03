
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

class QuickSort {

  /* 方式1,标准递归版本。需要左右不断交换，无需新建数组。 */
  static int[] quickSort(int arr[], int low, int high) {
    int i = low > 0 ? low : 0;
    int j = high;
    int midIndex = (i + j) / 2;
    int pivot = arr[midIndex];

    System.out.println(
        " i=" + i + ", j=" + j + ", midIndex=" + midIndex + ", pivot=" + pivot + "  arr[]=" + Arrays.toString(arr));

    // 当左侧小于等于右侧则表示还有值没有对比，需要继续
    while (i <= j) {
      // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
      while (arr[i] < pivot) {
        System.out.println("arr[i] < pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
        i++;
      }
      // 当前右侧大于基准时左移，直到找出比基准值小的位置来
      while (arr[j] > pivot) {
        System.out.println("arr[i] > pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
        j--;
      }

      System.out.println("low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", pivot=" + pivot);

      // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
      if (i <= j) {
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
        // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
        i++;
        j--;
      }
    }
    // 左侧小于基数位置，不断递归左边部分
    if (low < j) {
      System.out.println("  low < j:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", midIndex="
          + midIndex + ", pivot=" + pivot);
      quickSort(arr, low, j);
    }
    // 基数位置小于右侧，不断递归右侧部分
    if (i < high) {
      System.out.println("  i < high:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", midIndex="
          + midIndex + ", pivot=" + pivot);
      quickSort(arr, i, high);
    }

    return arr;
  }

  /**
   * jarrys-MacBook-Pro:quicksort jarry$ javac QuickSort.java
   * jarrys-MacBook-Pro:quicksort jarry$ java QuickSort sort start:[7, 11, 9, 10,
   * 12, 13, 8] i=0, j=6, midIndex=3, pivot=10 arr[][7, 11, 9, 10, 12, 13, 8]
   * arr[i] < pivot: i=0, j=6, pivot=10 low=0, high=6, i=1, j=6, pivot=10 arr[i] <
   * pivot: i=2, j=5, pivot=10 arr[i] > pivot: i=3, j=5, pivot=10 arr[i] > pivot:
   * i=3, j=4, pivot=10 jarrys-MacBook-Pro:quicksort jarry$ javac QuickSort.java
   * jarrys-MacBook-Pro:quicksort jarry$ java QuickSort sort start:[7, 11, 9, 10,
   * 12, 13, 8] i=0, j=6, midIndex=3, pivot=10 arr[]=[7, 11, 9, 10, 12, 13, 8]
   * arr[i] < pivot: i=0, j=6, pivot=10 low=0, high=6, i=1, j=6, pivot=10 arr[i] <
   * pivot: i=2, j=5, pivot=10 arr[i] > pivot: i=3, j=5, pivot=10 arr[i] > pivot:
   * i=3, j=4, pivot=10 low=0, high=6, i=3, j=3, pivot=10 low < j:recursion:
   * low=0, high=6, i=4, j=2, midIndex=3, pivot=10 i=0, j=2, midIndex=1, pivot=8
   * arr[]=[7, 8, 9, 10, 12, 13, 11] arr[i] < pivot: i=0, j=2, pivot=8 arr[i] >
   * pivot: i=1, j=2, pivot=8 low=0, high=2, i=1, j=1, pivot=8 i < high:recursion:
   * low=0, high=6, i=4, j=2, midIndex=3, pivot=10 i=4, j=6, midIndex=5, pivot=13
   * arr[]=[7, 8, 9, 10, 12, 13, 11] arr[i] < pivot: i=4, j=6, pivot=13 low=4,
   * high=6, i=5, j=6, pivot=13 low < j:recursion: low=4, high=6, i=6, j=5,
   * midIndex=5, pivot=13 i=4, j=5, midIndex=4, pivot=12 arr[]=[7, 8, 9, 10, 12,
   * 11, 13] low=4, high=5, i=4, j=5, pivot=12
   * 
   * time:78 ms. sorted:[7, 8, 9, 10, 11, 12, 13]
   */

  /* 方式2,非递归版本。需要交换，无需新建数组，利用stack或queue遍历。 */
  static int[] quickSortNotRecurion(int arr[], int low, int high) {

    Stack<Integer> stack = new Stack<Integer>();
    int i, j, midIndex, pivot, tmp;
    // 与标准递归版相同，只是将递归改为遍历栈的方式
    // 先将左右各取一个入栈
    stack.add(low);
    stack.add(high);

    // return arr;
    while (!stack.isEmpty()) {
      // 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
      j = high = (int) stack.pop();
      i = low = (int) stack.pop();

      midIndex = (i + j) / 2;
      pivot = arr[midIndex];

      while (i <= j) {
        while (arr[i] < pivot) {
          System.out.println("arr[i] < pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
          i++;
        }
        while (arr[j] > pivot) {
          System.out.println("arr[i] > pivot: i=" + i + ", j=" + j + ", pivot=" + pivot);
          j--;
        }

        System.out.println("low=" + low + ", high=" + high + ", i=" + i + ", j=" + j + ", pivot=" + pivot);

        if (i <= j) {
          tmp = arr[j];
          arr[j] = arr[i];
          arr[i] = tmp;
          i++;
          j--;
        }
      }
      if (low < j) {

        // 与递归版不同，这里添加到栈中，以便继续循环
        System.out.println("  low < j:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j
            + ", midIndex=" + midIndex + ", pivot=" + pivot);
        stack.add(low);
        stack.add(j);
      }
      if (i < high) {

        System.out.println("  i < high:recursion: low=" + low + ", high=" + high + ", i=" + i + ", j=" + j
            + ", midIndex=" + midIndex + ", pivot=" + pivot);

        stack.add(i);
        stack.add(high);
      }
    }
    return arr;
  }

  // test
  public static void main(String args[]) {
    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("sort start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    // arr = QuickSort.quickSort(arr, 0, arr.length - 1);
    arr = QuickSort.quickSortNotRecurion(arr, 0, arr.length - 1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(arr));
  }
}

/** 
 // 递归
 jarrys-MacBook-Pro:quicksort jarry$ javac QuickSort.java
jarrys-MacBook-Pro:quicksort jarry$ java QuickSort
sort start:[7, 11, 9, 10, 12, 13, 8]
 i=0, j=6, midIndex=3, pivot=10  arr[]=[7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=0, j=2, midIndex=1, pivot=8  arr[]=[7, 8, 9, 10, 12, 13, 11]
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
low=0, high=2, i=1, j=1, pivot=8
  i < high:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=4, j=6, midIndex=5, pivot=13  arr[]=[7, 8, 9, 10, 12, 13, 11]
arr[i] < pivot: i=4, j=6, pivot=13
low=4, high=6, i=5, j=6, pivot=13
  low < j:recursion: low=4, high=6, i=6, j=5, midIndex=5, pivot=13
 i=4, j=5, midIndex=4, pivot=12  arr[]=[7, 8, 9, 10, 12, 11, 13]
low=4, high=5, i=4, j=5, pivot=12

time:76 ms.
sorted:[7, 8, 9, 10, 11, 12, 13]
 */

/**
// 非递归
jarrys-MacBook-Pro:quicksort jarry$ javac QuickSort.java
jarrys-MacBook-Pro:quicksort jarry$ java QuickSort
sort start:[7, 11, 9, 10, 12, 13, 8]
 i=0, j=6, midIndex=3, pivot=10  arr[]=[7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
 i=0, j=2, midIndex=1, pivot=8  arr[]=[7, 8, 9, 10, 12, 13, 11]
jarrys-MacBook-Pro:quicksort jarry$ 
jarrys-MacBook-Pro:quicksort jarry$ javac QuickSort.java
jarrys-MacBook-Pro:quicksort jarry$ java QuickSort
sort start:[7, 11, 9, 10, 12, 13, 8]
arr[i] < pivot: i=0, j=6, pivot=10
low=0, high=6, i=1, j=6, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
low=0, high=6, i=3, j=3, pivot=10
  low < j:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  i < high:recursion: low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=4, j=6, pivot=13
low=4, high=6, i=5, j=6, pivot=13
  low < j:recursion: low=4, high=6, i=6, j=5, midIndex=5, pivot=13
low=4, high=5, i=4, j=5, pivot=12
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
low=0, high=2, i=1, j=1, pivot=8

time:66 ms.
sorted:[7, 8, 9, 10, 11, 12, 13]
*/
