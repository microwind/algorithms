
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;
import java.util.stream.Collectors;

class SelectionSort {

  static int[] selectionSort(final int[] arr) {
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

  public static void main(String args[]) {
    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    System.out.println("sort start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    // int[] sortedArr = SelectionSort.selectionSort(arr);
    int[] sortedArr = SelectionSort.selectionSort2(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(sortedArr));
  }

}

/**
 * jarrys-MacBook-Pro:selectionsort jarry$ javac SelectionSort.java
 * jarrys-MacBook-Pro:selectionsort jarry$ java SelectionSort sort start:[7, 11,
 * 9, 10, 12, 13, 8] i=0 j=7 min=7minIdx=0 arr[][7, 11, 9, 10, 12, 13, 8] i=1
 * j=7 min=8minIdx=6 arr[][7, 11, 9, 10, 12, 13, 8] i=2 j=7 min=9minIdx=2
 * arr[][7, 8, 9, 10, 12, 13, 11] i=3 j=7 min=10minIdx=3 arr[][7, 8, 9, 10, 12,
 * 13, 11] i=4 j=7 min=11minIdx=6 arr[][7, 8, 9, 10, 12, 13, 11] i=5 j=7
 * min=12minIdx=6 arr[][7, 8, 9, 10, 11, 13, 12]
 * 
 * time:35 ms. sorted:[7, 8, 9, 10, 11, 12, 13]
 */