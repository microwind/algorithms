
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.*;

public class BucketSort {
  /**
   * 桶标准排序，支持正负整数
   */
  public int[] bucketSort1(int[] arr) {
    int len = arr.length;
    int[] output = new int[len];
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < len; i++) {
      if (arr[i] > max)
        max = arr[i];
      if (arr[i] < min)
        min = arr[i];
    }
    // 最大最小的下限
    if (max < 2) {
      max = 2;
    }
    if (min < 1) {
      min = 1;
    }

    int bucketSize = (max - min) / min + 1;
    int bucketNumber = (max - min) / bucketSize + 1;
    System.out.println("bucketNumber,bucketSize:" + bucketNumber + "|" + bucketSize);

    int[][] buckets = new int[bucketNumber][];
    int[] bucketsMemberLength = new int[bucketNumber];
    for (int i = 0; i < bucketNumber; i++) {
      buckets[i] = new int[len];
    }
    for (int i = 0; i < len; i++) {
      int item = arr[i];
      int idx = (item - min) / bucketSize;
      if (idx < 0) {
        idx = 0;
      }

      int[] bucket = buckets[idx];
      int bucketLen = bucketsMemberLength[idx];
      // The first member
      System.out.println("i, item, bucketSize, bucketNumber, idx, bucket:" + i + "|" + item + "|" + bucketSize + "|"
      + bucketNumber + "|" + idx + " " + Arrays.toString(bucket));
      if (bucketLen == 0) {
        bucket[bucketLen] = item;
      } else {
        // Insert sort
        while (bucketLen-- > 0) {
          if (item < bucket[bucketLen]) {
            bucket[bucketLen + 1] = bucket[bucketLen];
            if (bucketLen == 0) {
              bucket[bucketLen] = item;
            }
          } else {
            bucket[bucketLen + 1] = item;
            break;
          }
        }
      }
      bucketsMemberLength[idx]++;
    }

    int idx = 0;
    for (int i = 0; i < bucketNumber; i++) {
      // System.out.println(Arrays.toString(buckets[i]));
      for (int j = 0; j < bucketsMemberLength[i]; j++) {
        output[idx] = buckets[i][j];
        idx++;
      }
    }

    return output;
  }


  /**
   * 桶标准排序，支持浮点数
   */
  public float[] bucketSort2(float[] arr) {
    int len = arr.length;
    if (len <= 0)
      return arr;
    // Set the default rate for float Array
    int rate = 100;
    int bucketNumber = len / 3;
    bucketNumber = bucketNumber < 3 ? 3 : bucketNumber;
    int bucketSize = rate / bucketNumber + 1;
    
    @SuppressWarnings("unchecked")
    ArrayList<Float>[] buckets = new ArrayList[bucketNumber];
    System.out.println("bucketNumber,bucketSize:" + bucketNumber + "|" + bucketSize);
    // Create empty buckets
    for (int i = 0; i < bucketNumber; i++)
      buckets[i] = new ArrayList<Float>();

    // Add elements into the buckets
    for (int i = 0; i < len; i++) {
      int bucketIndex = (int) (arr[i] * rate / bucketSize);
      if (bucketIndex < 0) {
        bucketIndex = 0;
      }
      if (bucketIndex > bucketNumber) {
        bucketIndex = bucketNumber;
      }
      buckets[bucketIndex].add(arr[i]);
      System.out.println(
          "i, arr[i], bucketIndex, bucket: " + i + "|" + arr[i] + "|" + bucketIndex + "| " + buckets[bucketIndex]);
    }

    // Sort the elements of each bucket
    for (int i = 0; i < buckets.length; i++) {
      Collections.sort((buckets[i]));
    }

    // Get the sorted array
    int index = 0;
    for (int i = 0; i < buckets.length; i++) {
      for (int j = 0, size = buckets[i].size(); j < size; j++) {
        arr[index++] = buckets[i].get(j);
      }
    }
    return arr;
  }

  /**
   * 桶标准排序，使用ArrayList
   */
  public int[] bucketSort3(int[] arr) {
    int len = arr.length;
    int[] output = new int[len];
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < len; i++) {
      if (arr[i] > max)
        max = arr[i];
      if (arr[i] < min)
        min = arr[i];
    }
    if (max < 2) {
      max = 2;
    }
    if (min < 1) {
      min = 1;
    }
    int bucketSize = (max - min) / min + 1;
    int bucketNumber = (max - min) / bucketSize + 1;
    // Least 3 bucket
    bucketNumber = bucketNumber < 3 ? 3 : bucketNumber;
    List<ArrayList<Integer>> buckets = new ArrayList<ArrayList<Integer>>();
    System.out.println("bucketNumber,bucketSize:" + bucketNumber + "|" + bucketSize);
    // init bucket
    for (int i = 0; i < bucketNumber; i++) {
      buckets.add(new ArrayList<Integer>());
    }
    for (int i = 0; i < len; i++) {
      int item = arr[i];
      int idx = (item - min) / bucketSize;
      if (idx < 0) {
        idx = 0;
      }
      List<Integer> bucket = buckets.get(idx);
      System.out.println("i, item, idx:" + i + "|" + item + "|" + idx + ":" + bucket);
      if (bucket.size() == 0) {
        bucket.add(item);
      } else {
        int bucketLen = bucket.size();
        while (bucketLen-- > 0) {
          if (item >= bucket.get(bucketLen)) {
            bucket.add(item);
            break;
          } else if (bucketLen == 0) {
            bucket.add(bucketLen, item);
          }
        }
      }
    }

    int idx = 0;
    for (int i = 0; i < buckets.size(); i++) {
      for (int j = 0; j < buckets.get(i).size(); j++) {
        output[idx] = buckets.get(i).get(j);
        idx++;
      }
    }
    return output;
  }

  public static void main(final String args[]) {
    BucketSort bucketSort = new BucketSort();
    int[] arr1 = { 20, 11, 9, 30, 15, 13, 80 };
    // int[] arr1 = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    System.out.println("\r\nbucketSort1 start:" + Arrays.toString(arr1));
    long startTime = System.currentTimeMillis();
    int[] result1 = bucketSort.bucketSort1(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sorted:" + Arrays.toString(result1));
    
    float[] arr2 = { 0.7f, 0.11f, -0.9f, 0.011f, 0.034f, 0.62f, 0.93f, 0.68f };
    System.out.println("\r\nbucketSort2 start:" + Arrays.toString(arr2));
    long startTime2 = System.currentTimeMillis();
    float[] result2 = bucketSort.bucketSort2(arr2);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
    System.out.println("sorted:" + Arrays.toString(result2));

    // int[] arr3 = { 20, 21, 19, 23, 22, 19, 22, 19, 23, 22 };
    int[] arr3 = { 20, 11, 0, -10, 9, 6, 30, 15, 13, 80 };
    System.out.println("\r\nbucketSort3 start:" + Arrays.toString(arr3));
    long startTime3 = System.currentTimeMillis();
    int[] result3 = bucketSort.bucketSort3(arr3);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime3) + " ms.");
    System.out.println("sorted:" + Arrays.toString(result3));

  }

}

/*
jarry@jarrys-MacBook-Pro bucketsort % javac BucketSort.java
jarry@jarrys-MacBook-Pro bucketsort % java BucketSort 

bucketSort1 start:[20, 11, 9, 30, 15, 13, 80]
bucketNumber,bucketSize:9|8
i, item, bucketSize, bucketNumber, idx, bucket:0|20|8|9|1 [0, 0, 0, 0, 0, 0, 0]
i, item, bucketSize, bucketNumber, idx, bucket:1|11|8|9|0 [0, 0, 0, 0, 0, 0, 0]
i, item, bucketSize, bucketNumber, idx, bucket:2|9|8|9|0 [11, 0, 0, 0, 0, 0, 0]
i, item, bucketSize, bucketNumber, idx, bucket:3|30|8|9|2 [0, 0, 0, 0, 0, 0, 0]
i, item, bucketSize, bucketNumber, idx, bucket:4|15|8|9|0 [9, 11, 0, 0, 0, 0, 0]
i, item, bucketSize, bucketNumber, idx, bucket:5|13|8|9|0 [9, 11, 15, 0, 0, 0, 0]
i, item, bucketSize, bucketNumber, idx, bucket:6|80|8|9|8 [0, 0, 0, 0, 0, 0, 0]

time:20 ms.
sorted:[9, 11, 13, 15, 20, 30, 80]

bucketSort2 start:[0.7, 0.11, -0.9, 0.011, 0.034, 0.62, 0.93, 0.68]
bucketNumber,bucketSize:3|34
i, arr[i], bucketIndex, bucket: 0|0.7|2| [0.7]
i, arr[i], bucketIndex, bucket: 1|0.11|0| [0.11]
i, arr[i], bucketIndex, bucket: 2|-0.9|0| [0.11, -0.9]
i, arr[i], bucketIndex, bucket: 3|0.011|0| [0.11, -0.9, 0.011]
i, arr[i], bucketIndex, bucket: 4|0.034|0| [0.11, -0.9, 0.011, 0.034]
i, arr[i], bucketIndex, bucket: 5|0.62|1| [0.62]
i, arr[i], bucketIndex, bucket: 6|0.93|2| [0.7, 0.93]
i, arr[i], bucketIndex, bucket: 7|0.68|2| [0.7, 0.93, 0.68]

time:9 ms.
sorted:[-0.9, 0.011, 0.034, 0.11, 0.62, 0.68, 0.7, 0.93]

bucketSort3 start:[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]
bucketNumber,bucketSize:3|80
i, item, idx:0|20|0:[]
i, item, idx:1|11|0:[20]
i, item, idx:2|0|0:[11, 20]
i, item, idx:3|-10|0:[0, 11, 20]
i, item, idx:4|9|0:[-10, 0, 11, 20]
i, item, idx:5|6|0:[-10, 0, 11, 20, 9]
i, item, idx:6|30|0:[-10, 0, 11, 20, 9, 6]
i, item, idx:7|15|0:[-10, 0, 11, 20, 9, 6, 30]
i, item, idx:8|13|0:[-10, 0, 11, 20, 9, 6, 30, 15]
i, item, idx:9|80|0:[-10, 0, 11, 20, 9, 6, 30, 15, 13]

time:8 ms.
sorted:[-10, 0, 11, 20, 9, 6, 30, 15, 13, 80]
 */