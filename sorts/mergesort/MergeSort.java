
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

/**
 * 归并排序 ，采用分而治之(divide - conquer)的步骤
 * 1. 分解（Divide），把待排序元素的序列分解为两个子序列，以中间2分, 每个子序列包括一半成员。
 * 2. 解决（Conquer），对每个子序列分别调用归并操作, 进行递归或非递归循环操作，完成内部排序。
 * 3. 合并（Combine），合并两个排好序的子序列，生成排序结果。 归并排序的最坏时间复杂度和平均时间复杂度均为O(nlogn)
 */
class MergeSort {

  static void merge(int arr[], int left, int mid, int right) {
    // 先建立一个长度等于原数组的临时数组
    int[] temp = new int[right - left + 1];
    // 左侧指针
    int i = left;
    // 右侧指针
    int j = mid + 1;
    // 临时数组指针
    int k = 0;
    // 当左指针小于中间，且右指针不大于最右侧时
    while (i <= mid && j <= right) {
      // 如果左侧小于右侧，将数移到临时数组中左侧
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
      // 否则移动到临时数组右侧
      } else {
        temp[k++] = arr[j++];
      }
    }

    // 如果左边数组还有数据，就把左侧剩余都放入到新数组后面
    while (i <= mid) {
      temp[k++] = arr[i++];
    }
    // 如果右侧数组还有数据，把剩下的数据放入到新数组后面
    while (j <= right) {
      temp[k++] = arr[j++];
    }

    // 将排序后的元素全部移动到原数组中
    int x = 0;
    while (left <= right) {
      arr[left++] = temp[x++];
    }
    System.out.println("arr:" + Arrays.toString(arr));
  }

  static int[] mergeSort(int[] arr, int left, int right) {
    // 得到中间值
    int mid = (left + right) / 2;
    // 如果左侧小于右侧则执行合并排序
    System.out.println("mergeSort left=" + left + " right=" + right);
    if (left < right) {
      System.out.println("mergeSort left<right left=" + left + " right=" + right);
      // 递归合并左侧
      mergeSort(arr, left, mid);
      // 递归合并右侧
      mergeSort(arr, mid + 1, right);
      // 合并排序
      merge(arr, left, mid, right);
    }
    return arr;
  }

  public static void main(final String args[]) {
    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("sort start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    int[] sortedArr = MergeSort.mergeSort(arr, 0, arr.length - 1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(sortedArr));

    int arr2[] = { -27, 4, 9, 120, 122, 13, 8, 4, 0, 20 };
    System.out.println("sort start:" + Arrays.toString(arr2));
    startTime = System.currentTimeMillis();
    int[] sortedArr2 = MergeSort.mergeSort(arr2, 0, arr2.length - 1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(sortedArr2));
  }

}

/**
jarry@jarrys-mbp mergesort % javac MergeSort.java
jarry@jarrys-mbp mergesort % java MergeSort      
sort start:[7, 11, 9, 10, 12, 13, 8]
arr:[7, 11, 9, 10, 12, 13, 8]
arr:[7, 11, 9, 10, 12, 13, 8]
arr:[7, 9, 10, 11, 12, 13, 8]
arr:[7, 9, 10, 11, 12, 13, 8]
arr:[7, 9, 10, 11, 8, 12, 13]
arr:[7, 8, 9, 10, 11, 12, 13]

time:0 ms.
sorted:[7, 8, 9, 10, 11, 12, 13]
sort start:[-27, 4, 9, 120, 122, 13, 8, 4, 0, 20]
arr:[-27, 4, 9, 120, 122, 13, 8, 4, 0, 20]
arr:[-27, 4, 9, 120, 122, 13, 8, 4, 0, 20]
arr:[-27, 4, 9, 120, 122, 13, 8, 4, 0, 20]
arr:[-27, 4, 9, 120, 122, 13, 8, 4, 0, 20]
arr:[-27, 4, 9, 120, 122, 8, 13, 4, 0, 20]
arr:[-27, 4, 9, 120, 122, 4, 8, 13, 0, 20]
arr:[-27, 4, 9, 120, 122, 4, 8, 13, 0, 20]
arr:[-27, 4, 9, 120, 122, 0, 4, 8, 13, 20]
arr:[-27, 0, 4, 4, 8, 9, 13, 20, 120, 122]

time:0 ms.
sorted:[-27, 0, 4, 4, 8, 9, 13, 20, 120, 122]
 */