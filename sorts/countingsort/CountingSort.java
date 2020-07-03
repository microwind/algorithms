
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.*;


public class CountingSort {

  public int[] countingSort1(int[] arr) {
    
    int minValue = arr[0];
    int maxValue = arr[0];
    for (int item : arr) {
      if (item > maxValue) {
        maxValue = item;
      }
      if (item < minValue) {
        minValue = item;
      }
    }

    int realLen = maxValue - minValue + 1;
    // 计数数组的长度在最大和最小差值+1
    int[] counter = new int[realLen];
    for (int item : arr) {
      int idx = item - minValue;
      // 有值下标增加1
      counter[idx] += 1;
    }

    int outpuIdx = 0;
    for (int i = 0; i < realLen; i++) {
      int item = counter[i];
      for (int j = 0; j < item; j++) {
        // 如果相同则取多次
        arr[outpuIdx] = i + minValue;
        outpuIdx++;
      }
    }
    return arr;
  }

  int[] countingSort2(int[] arr) {
    int minValue = arr[0];
    int maxValue = arr[0];
    for (int item : arr) {
      if (item > maxValue) {
        maxValue = item;
      }
      if (item < minValue) {
        minValue = item;
      }
    }
    int realLen = maxValue - minValue + 1;
    int[] counter = new int[realLen];

    int len = arr.length;
    for (int item : arr) {
        counter[item - minValue]++;
    }

    int j = 0;
    for (int i = 0; i < realLen; i++) {
      while (counter[i] > 0) {
        arr[j++] = i + minValue;
        counter[i]--;
      }
    }
    return arr;
  }

  public static void main(final String args[]) {
    int[] arr = { 7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10 };
    CountingSort countingSort = new CountingSort();
    System.out.println("\r\ncountingSort1 start:" + Arrays.toString(arr));
    long startTime = System.currentTimeMillis();
    countingSort.countingSort1(arr);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(arr));

    int[] arr2 = { 20, 11, 9, 30, 15, 13, 80 };
    // int[] arr2 = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    System.out.println("\r\ncountingSort2 start:" + Arrays.toString(arr2));
    long startTime2 = System.currentTimeMillis();
    int[] result2 = countingSort.countingSort2(arr2);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
    System.out.println("sorted:" + Arrays.toString(result2));

    int[] arr3 = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    System.out.println("\r\ncountingSort3 start:" + Arrays.toString(arr3));
    long startTime3 = System.currentTimeMillis();
    int[] result3 = countingSort.countingSort2(arr3);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime3) + " ms.");
    System.out.println("sorted:" + Arrays.toString(result3));

  }
}