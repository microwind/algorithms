
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
      // 下标增加1
      counter[idx] += 1;
    }

    // 输出方式1. 根据下标遍历计数数组输出
    // int outpuIdx = 0;
    // for (int i = 0; i < realLen; i++) {
    // int item = counter[i];
    // for (int j = 0; j < item; j++) {
    // // 如果相同则取多次
    // arr[outpuIdx] = i + minValue;
    // outpuIdx++;
    // }
    // }
    // return arr;

    // 输出方式2. 把顺序记录到计数数组中
    // 后一项记录前一项的值，这样得到排序位置
    for (int i = 1; i < realLen; i++) {
      counter[i] += counter[i - 1];
    }

    // 根据位置将计数数组内容添加到返回数组中
    int[] output = new int[realLen];
    for (int i = 0; i < arr.length; i++) {
      int item = arr[i] - minValue;
      // 根据当前项从计数数组得到新数组下标
      int idx = counter[item] - 1;
      // 给返回的下标赋值为当前项
      output[idx] = item + minValue;
      // 取出一项，计数数组则减少一项
      counter[item] -= 1;
    }
    return output;
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
    // int[] arr = { 7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10 };
    int[] arr = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    CountingSort countingSort = new CountingSort();
    System.out.println("\r\ncountingSort1 start:" + Arrays.toString(arr));
    long startTime = System.nanoTime();
    countingSort.countingSort1(arr);
    System.out.println("sorted:" + Arrays.toString(arr));
    System.out.println("\r\ntime:" + (System.nanoTime() - startTime) + " ns.");

    // int[] arr2 = { 20, 11, 9, 30, 15, 13, 80 };
    int[] arr2 = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    System.out.println("\r\ncountingSort2 start:" + Arrays.toString(arr2));
    long startTime2 = System.nanoTime();
    int[] result2 = countingSort.countingSort2(arr2);
    System.out.println("sorted:" + Arrays.toString(result2));
    System.out.println("\r\ntime:" + (System.nanoTime() - startTime2) + " ns.");

    int[] arr3 = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    System.out.println("\r\ncountingSort3 start:" + Arrays.toString(arr3));
    long startTime3 = System.nanoTime();
    int[] result3 = countingSort.countingSort2(arr3);
    System.out.println("sorted:" + Arrays.toString(result3));
    System.out.println("\r\ntime:" + (System.nanoTime() - startTime3) + " ns.");

  }
}

/**
jarry@jarrys-MacBook-Pro countingsort % javac CountingSort.java
jarry@jarrys-MacBook-Pro countingsort % java CountingSort      

countingSort1 start:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
sorted:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

time:129332 ms.
jarry@jarrys-MacBook-Pro countingsort % javac CountingSort.java
jarry@jarrys-MacBook-Pro countingsort % java CountingSort      

countingSort1 start:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
sorted:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

time:148466 ns.

countingSort2 start:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
sorted:[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

time:134693 ns.

countingSort3 start:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
sorted:[-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

time:131103 ns.
 */