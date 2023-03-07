
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;
import java.util.stream.Collectors;

class SelectionSort {

  static int[] selectionSort1(final int[] arr) {
    int min;
    int minIdx;
    int tmp;
    int l = arr.length;
    for (int i = 0; i < l - 1; i++) {
      min = arr[i];
      minIdx = i;
      int j = i + 1;
      for (; j < l; j++) {
        // 从待排序列表找到最小值和位置
        if (arr[j] < min) {
          min = arr[j];
          minIdx = j;
        }
      }
      System.out.println("i=" + i + " j=" + j + " min=" + min + "minIdx=" + minIdx + " arr[]" + Arrays.toString(arr));
      // 将待排序里最小值交换到已排序最后面
      if (minIdx != i) {
        tmp = arr[i];
        arr[i] = min;
        arr[minIdx] = tmp;
      }
    }
    return arr;
  }

  // 新建数组版，无需交换
  static int[] selectionSort2(int arr[]) {
    int min;
    int minIdx;
    // int[] to List
    List<Integer> listArr = Arrays.stream(arr).boxed().collect(Collectors.toList());
    int len = listArr.size();
    List<Integer> newArr = new ArrayList<>();
    for (int i = 0; i < len; i++) {
      min = listArr.get(i);
      minIdx = i;
      int j = i + 1;
      for (; j < len; j++) {
        if (listArr.get(j) < min) {
          min = listArr.get(j);
          minIdx = j;
        }
      }
      newArr.add(min);
      listArr.remove(minIdx);
      System.out.println("i=" + i + " j=" + j + " min=" + min + "minIdx=" + minIdx + " listArr[]" + listArr.toString()
          + " newArr[]" + newArr.toString());
      len--;
      i--;
    }
    // convert to int[]
    return newArr.stream().mapToInt(Integer::intValue).toArray();
  }

  // test
  public static void main(String args[]) {
    int arr1[] = { 7, 11, -9, 10, -12, 13, 8 };
    System.out.println("origin arr1:" + Arrays.toString(arr1));
    long startTime1 = System.currentTimeMillis();
    int[] sortedArr1 = SelectionSort.selectionSort1(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime1) + " ms.");
    System.out.println("arr1 sorted:" + Arrays.toString(sortedArr1));

    int arr2[] = { 7, 11, -9, 10, -12, 13, 8 };
    System.out.println("origin arr2:" + Arrays.toString(arr2));
    long startTime2 = System.currentTimeMillis();
    int[] sortedArr2 = SelectionSort.selectionSort1(arr2);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
    System.out.println("arr2 sorted:" + Arrays.toString(sortedArr2));
  }

}

/**
 * jarrys-MacBook-Pro:selectionsort jarry$ javac SelectionSort.java
 * jarry@jarrys-MacBook-Pro selectionsort % java SelectionSort.java
 * origin arr1:[7, 11, -9, 10, -12, 13, 8]
 * i=0 j=7 min=-12minIdx=4 arr[][7, 11, -9, 10, -12, 13, 8]
 * i=1 j=7 min=-9minIdx=2 arr[][-12, 11, -9, 10, 7, 13, 8]
 * i=2 j=7 min=7minIdx=4 arr[][-12, -9, 11, 10, 7, 13, 8]
 * i=3 j=7 min=8minIdx=6 arr[][-12, -9, 7, 10, 11, 13, 8]
 * i=4 j=7 min=10minIdx=6 arr[][-12, -9, 7, 8, 11, 13, 10]
 * i=5 j=7 min=11minIdx=6 arr[][-12, -9, 7, 8, 10, 13, 11]
 * 
 * time:7 ms.
 * arr1 sorted:[-12, -9, 7, 8, 10, 11, 13]
 * origin arr2:[7, 11, -9, 10, -12, 13, 8]
 * i=0 j=7 min=-12minIdx=4 arr[][7, 11, -9, 10, -12, 13, 8]
 * i=1 j=7 min=-9minIdx=2 arr[][-12, 11, -9, 10, 7, 13, 8]
 * i=2 j=7 min=7minIdx=4 arr[][-12, -9, 11, 10, 7, 13, 8]
 * i=3 j=7 min=8minIdx=6 arr[][-12, -9, 7, 10, 11, 13, 8]
 * i=4 j=7 min=10minIdx=6 arr[][-12, -9, 7, 8, 11, 13, 10]
 * i=5 j=7 min=11minIdx=6 arr[][-12, -9, 7, 8, 10, 13, 11]
 * 
 * time:0 ms.
 * arr2 sorted:[-12, -9, 7, 8, 10, 11, 13]
 */