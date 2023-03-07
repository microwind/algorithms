
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

// 基数排序，从高到低逐位排序，递归方式，基于桶排序。具体步骤如下：
// 1. 找出数组中最大的数，确定其位数。
// 2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中。
// 3. 如果桶里的长度超过1，则通过递归继续按桶排序。当桶里的数据只有1位时添加到原列表对应位置。
// 重复步骤2和3，直到按照最高位排序完成。
class RadixSortMSD {
  static int[] radixSort(int[] arr) {
    int len = arr.length;
    // 获取数组最大项
    int max = arr[0];
    for (int i = 0; i < len; i++) {
      if (max < arr[i]) {
        max = arr[i];
      }
    }

    // 获取数组最小项
    int min = arr[0];
    for (int i = 0; i < len; i++) {
      if (min > arr[i]) {
        min = arr[i];
      }
    }

    // 获取数字一共有几位，减去min得到最大值，以支持负数和减少最大值
    int numberOfDigits = (int) (Math.log10(max - min) + 1);
    int exponent = (int) (Math.pow(10, numberOfDigits - 1));
    // 根据数组最大值，自后向前逐个按数位基数(exponent)比较排序。
    System.out.println("numberOfDigits:" + numberOfDigits + " exponent:" + exponent);
    return bucketSort(arr, len, exponent);
  }

  static int[] bucketSort(int[] arr, int len, int exponent) {

    System.out.println("origin arr:" + Arrays.toString(arr) + " len=" + len + " exponent:" + exponent);
    if (len <= 1 || exponent < 1) {
      return arr;
    }
    System.out.println("prepared arr:" + Arrays.toString(arr) + " len=" + len + " exponent:" + exponent);

    // 获取数组最小项
    int min = arr[0];
    for (int i = 0; i < len; i++) {
      if (min > arr[i]) {
        min = arr[i];
      }
    }

    // 位数按10递进
    int range = 10;
    // 定义桶二维数组，长度为10，放入0-9的数字
    int[][] buckets = new int[range][len];
    // 记录某个桶的最新长度，以便往桶内追加数据。
    int[] bucketsCount = new int[range];
    for (int i = 0; i < len; i++) {
      int item = arr[i] - min;
      // 根据数位上的值，把数据追加到对应的桶里，减去min是支持负数
      int bucketIdx = (item / exponent) % range;
      System.out.println("arr[" + i + "]=" + arr[i] + " item=" + item + " bucketIdx=" + bucketIdx);
      // 把数据按下标插入到桶里
      int numberIndex = bucketsCount[bucketIdx];
      buckets[bucketIdx][numberIndex] = arr[i];
      bucketsCount[bucketIdx] += 1;
    }

    System.out.println("bucketsCount=" + Arrays.toString(bucketsCount) + "arr=" + Arrays.toString(arr));
    // 将每个桶的数据按顺序逐个取出，重新赋值给原数组
    int sortedIdx = 0;

    for (int i = 0; i < range; i++) {
      int[] bucket = buckets[i];
      int bucketLen = bucketsCount[i];
      // 如果只有一个值，则直接更新到原数组
      if (bucketsCount[i] == 1) {
        arr[sortedIdx] = bucket[0];
        sortedIdx += 1;
      } else if (bucket.length > 0 && bucketLen > 0) {
        // 如果是数组且记录大于1则继续递归调用，位数降低1位
        // 递归调用传参时需要传入当前子序列、子序列长度、当前分解的位数基数
        int[] sortedBucket = bucketSort(bucket, bucketLen, (int) (exponent / range));
        // 依照已排序的子序列实际长度，把各个桶里的值按顺序赋给原数组
        for (int j = 0; j < bucketLen; j++) {
          int num = sortedBucket[j];
          System.out.println("bucket:" + Arrays.toString(bucket) + " sortedBucket:" + Arrays.toString(sortedBucket)
              + " sortedIdx:" + sortedIdx
              + " set arr:" + Arrays.toString(arr));
          arr[sortedIdx] = num;
          sortedIdx += 1;
        }
      }
    }
    System.out.println("exponent:" + exponent + " sorted arr:" + Arrays.toString(arr));
    return arr;
  }

  // test
  public static void main(String args[]) {
    int arr1[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
    System.out.println("sort1 start:" + Arrays.toString(arr1));
    long startTime = System.currentTimeMillis();
    arr1 = RadixSortMSD.radixSort(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sort1 sorted:" + Arrays.toString(arr1));
  }
}

/*
 * jarry@jarrys-MacBook-Pro radixsort % javac RadixSortLSD.java
 * jarry@jarrys-MacBook-Pro radixsort % java RadixSortLSD
 * sort1 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
 * numberOfDigits:6 exponent:100000
 * origin arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] len=10
 * exponent:100000
 * prepared arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] len=10
 * exponent:100000
 * arr[0]=33 item=323487 bucketIdx=3
 * arr[1]=-4 item=323450 bucketIdx=3
 * arr[2]=15 item=323469 bucketIdx=3
 * arr[3]=43 item=323497 bucketIdx=3
 * arr[4]=-323454 item=0 bucketIdx=0
 * arr[5]=7 item=323461 bucketIdx=3
 * arr[6]=10 item=323464 bucketIdx=3
 * arr[7]=1235 item=324689 bucketIdx=3
 * arr[8]=200 item=323654 bucketIdx=3
 * arr[9]=87431 item=410885 bucketIdx=4
 * bucketsCount=[1, 0, 0, 8, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, -323454, 7,
 * 10, 1235, 200, 87431]
 * origin arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] len=8 exponent:10000
 * prepared arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] len=8 exponent:10000
 * arr[0]=33 item=37 bucketIdx=0
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=0
 * arr[3]=43 item=47 bucketIdx=0
 * arr[4]=7 item=11 bucketIdx=0
 * arr[5]=10 item=14 bucketIdx=0
 * arr[6]=1235 item=1239 bucketIdx=0
 * arr[7]=200 item=204 bucketIdx=0
 * bucketsCount=[8, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 1235,
 * 200, 0, 0]
 * origin arr:[33, -4, 15, 43, 7, 10, 1235, 200] len=8 exponent:1000
 * prepared arr:[33, -4, 15, 43, 7, 10, 1235, 200] len=8 exponent:1000
 * arr[0]=33 item=37 bucketIdx=0
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=0
 * arr[3]=43 item=47 bucketIdx=0
 * arr[4]=7 item=11 bucketIdx=0
 * arr[5]=10 item=14 bucketIdx=0
 * arr[6]=1235 item=1239 bucketIdx=1
 * arr[7]=200 item=204 bucketIdx=0
 * bucketsCount=[7, 1, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 1235,
 * 200]
 * origin arr:[33, -4, 15, 43, 7, 10, 200, 0] len=7 exponent:100
 * prepared arr:[33, -4, 15, 43, 7, 10, 200, 0] len=7 exponent:100
 * arr[0]=33 item=37 bucketIdx=0
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=0
 * arr[3]=43 item=47 bucketIdx=0
 * arr[4]=7 item=11 bucketIdx=0
 * arr[5]=10 item=14 bucketIdx=0
 * arr[6]=200 item=204 bucketIdx=2
 * bucketsCount=[6, 0, 1, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 200,
 * 0]
 * origin arr:[33, -4, 15, 43, 7, 10, 0] len=6 exponent:10
 * prepared arr:[33, -4, 15, 43, 7, 10, 0] len=6 exponent:10
 * arr[0]=33 item=37 bucketIdx=3
 * arr[1]=-4 item=0 bucketIdx=0
 * arr[2]=15 item=19 bucketIdx=1
 * arr[3]=43 item=47 bucketIdx=4
 * arr[4]=7 item=11 bucketIdx=1
 * arr[5]=10 item=14 bucketIdx=1
 * bucketsCount=[1, 3, 0, 1, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 0]
 * origin arr:[15, 7, 10, 0, 0, 0] len=3 exponent:1
 * prepared arr:[15, 7, 10, 0, 0, 0] len=3 exponent:1
 * arr[0]=15 item=8 bucketIdx=8
 * arr[1]=7 item=0 bucketIdx=0
 * arr[2]=10 item=3 bucketIdx=3
 * bucketsCount=[1, 0, 0, 1, 0, 0, 0, 0, 1, 0]arr=[15, 7, 10, 0, 0, 0]
 * exponent:1 sorted arr:[7, 10, 15, 0, 0, 0]
 * bucket:[7, 10, 15, 0, 0, 0] sortedBucket:[7, 10, 15, 0, 0, 0] sortedIdx:1 set
 * arr:[-4, -4, 15, 43, 7, 10, 0]
 * bucket:[7, 10, 15, 0, 0, 0] sortedBucket:[7, 10, 15, 0, 0, 0] sortedIdx:2 set
 * arr:[-4, 7, 15, 43, 7, 10, 0]
 * bucket:[7, 10, 15, 0, 0, 0] sortedBucket:[7, 10, 15, 0, 0, 0] sortedIdx:3 set
 * arr:[-4, 7, 10, 43, 7, 10, 0]
 * exponent:10 sorted arr:[-4, 7, 10, 15, 33, 43, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:1 set arr:[-4, -4, 15, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:2 set arr:[-4, 7, 15, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:3 set arr:[-4, 7, 10, 43, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:4 set arr:[-4, 7, 10, 15, 7, 10, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 0] sortedBucket:[-4, 7, 10, 15, 33, 43, 0]
 * sortedIdx:5 set arr:[-4, 7, 10, 15, 33, 10, 200, 0]
 * exponent:100 sorted arr:[-4, 7, 10, 15, 33, 43, 200, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:1 set arr:[-4, -4, 15, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:2 set arr:[-4, 7, 15, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:3 set arr:[-4, 7, 10, 43, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:4 set arr:[-4, 7, 10, 15, 7, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:5 set arr:[-4, 7, 10, 15, 33, 10, 1235, 200]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 0] sortedBucket:[-4, 7, 10, 15, 33, 43,
 * 200, 0] sortedIdx:6 set arr:[-4, 7, 10, 15, 33, 43, 1235, 200]
 * exponent:1000 sorted arr:[-4, 7, 10, 15, 33, 43, 200, 1235]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:1 set arr:[-4, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:2 set arr:[-4, 7, 15, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:3 set arr:[-4, 7, 10, 43, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:4 set arr:[-4, 7, 10, 15, 7, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:5 set arr:[-4, 7, 10, 15, 33, 10, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:6 set arr:[-4, 7, 10, 15, 33, 43, 1235, 200, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235] sortedBucket:[-4, 7, 10, 15, 33,
 * 43, 200, 1235] sortedIdx:7 set arr:[-4, 7, 10, 15, 33, 43, 200, 200, 0, 0]
 * exponent:10000 sorted arr:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:1 set arr:[-323454, -4, 15, 43, -323454,
 * 7, 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:2 set arr:[-323454, -4, 15, 43, -323454,
 * 7, 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:3 set arr:[-323454, -4, 7, 43, -323454, 7,
 * 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:4 set arr:[-323454, -4, 7, 10, -323454, 7,
 * 10, 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:5 set arr:[-323454, -4, 7, 10, 15, 7, 10,
 * 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:6 set arr:[-323454, -4, 7, 10, 15, 33, 10,
 * 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:7 set arr:[-323454, -4, 7, 10, 15, 33, 43,
 * 1235, 200, 87431]
 * bucket:[-4, 7, 10, 15, 33, 43, 200, 1235, 0, 0] sortedBucket:[-4, 7, 10, 15,
 * 33, 43, 200, 1235, 0, 0] sortedIdx:8 set arr:[-323454, -4, 7, 10, 15, 33, 43,
 * 200, 200, 87431]
 * exponent:100000 sorted arr:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 * 
 * time:49 ms.
 * sort1 sorted:[-323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431]
 */
