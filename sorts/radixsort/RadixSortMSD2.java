
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import java.util.*;

// 基数排序，从高到低逐位排序，非递归方式，基于桶排序。具体步骤如下：
// 1. 找出数组中最大的数，确定其位数。
// 2. MSD是从高位开始，依次按照位数的值将数字放入到不同桶中。
// 3. 如果桶里的长度超过1，则通过递归继续按桶排序。当桶里的数据只有1位时添加到原列表对应位置。
// 重复步骤2和3，直到按照最高位排序完成。
class RadixSortMSD2 {
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
    int maxLength = (int) (Math.log10(max - min) + 1);
    // 根据数组最大值的长度，从前往后逐个对比排序。
    System.out.println("maxLength:" + maxLength);
    return bucketSort(arr, len, 1, maxLength);
  }

  // 获取数字第n位的值，不足最大长度时补零。补齐数位，从左往右查找。
  static int getDigitByPosition(int num, int position, int maxLength) {
    if (num == 0) {
      return 0;
    }
    int numberLength = (int) (Math.log10(num) + 1);
    // 查询的位置加上自身长度不足最大长度则返回0
    if ((position + numberLength) < maxLength) {
      return 0;
    }
    int exponent = (int) Math.pow(10, numberLength - position);
    int digit = 0;
    if (exponent > 0) {
      digit = (num / exponent) % 10;
    }
    System.out.println("num=" + num + " position=" + position + " numberLength=" + numberLength + " exponent="
        + exponent + " position=" + position);
    return digit;
  }

  // 递归桶排序实现基数排序
  // arr是数组，len是当前数组长度，position为自前往后的位置，maxLength是最大值的数位
  static int[] bucketSort(int[] arr, int len, int position, int maxLength) {

    System.out.println("origin arr:" + Arrays.toString(arr) + " position:" + position + " maxLength:" + maxLength);
    if (len <= 1 || position > maxLength) {
      return arr;
    }
    System.out.println("prepared arr:" + Arrays.toString(arr) + " position:" + position + " maxLength:" + maxLength);

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
    // Java int数组初始化值为0，因此需要单独记录数组实际插入了多少
    int[] bucketCountList = new int[range];
    for (int i = 0; i < len; i++) {
      int item = arr[i] - min;
      // 根据数位上的值，减去最小值，分配到对应的桶里
      int bucketIdx = getDigitByPosition(item, position, maxLength);
      // 把数据按下标插入到桶里
      int numberIdx = bucketCountList[bucketIdx];
      buckets[bucketIdx][numberIdx] = arr[i];
      bucketCountList[bucketIdx] += 1;
    }

    System.out.println("bucketCountList=" + Arrays.toString(bucketCountList) + "arr=" + Arrays.toString(arr));

    // 将每个桶的数据按顺序逐个取出，重新赋值给原数组
    int sortedIdx = 0;

    for (int i = 0; i < range; i++) {
      int[] bucket = buckets[i];
      int bucketLen = bucketCountList[i];
      // 如果只有一个值，则直接更新到原数组
      if (bucketCountList[i] == 1) {
        arr[sortedIdx] = bucket[0];
        sortedIdx += 1;
      } else if (bucket.length > 0 && bucketLen > 0) {
        // 如果是数组且记录追加大于1则继续递归调用，位置增加1位
        // 递归调用传参时需要传入当前子序列、子序列长度、当前分解的位数基数
        int[] sortedBucket = bucketSort(bucket, bucketLen, position + 1, maxLength);
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
    System.out.println("position:" + position + " sorted arr:" + Arrays.toString(arr));
    return arr;
  }

  // test
  public static void main(String args[]) {
    int arr1[] = { 89, 195, 196, 275, 276, 272, 2343 };
    System.out.println("sort1 start:" + Arrays.toString(arr1));
    long startTime = System.currentTimeMillis();
    arr1 = RadixSortMSD2.radixSort(arr1);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("sort1 sorted:" + Arrays.toString(arr1));

    int arr2[] = { 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 };
    System.out.println("sort2 start:" + Arrays.toString(arr2));
    long startTime2 = System.currentTimeMillis();
    arr1 = RadixSortMSD2.radixSort(arr2);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime2) + " ms.");
    System.out.println("sort2 sorted:" + Arrays.toString(arr2));
  }
}

/*
jarry@jarrys-MacBook-Pro radixsort % javac RadixSortMSD2.java
jarry@jarrys-MacBook-Pro radixsort % java RadixSortMSD2      
sort1 start:[89, 195, 196, 275, 276, 272, 2343]
maxLength:4
origin arr:[89, 195, 196, 275, 276, 272, 2343] position:1 maxLength:4
prepared arr:[89, 195, 196, 275, 276, 272, 2343] position:1 maxLength:4
num=106 position=1 numberLength=3 exponent=100 position=1
num=107 position=1 numberLength=3 exponent=100 position=1
num=186 position=1 numberLength=3 exponent=100 position=1
num=187 position=1 numberLength=3 exponent=100 position=1
num=183 position=1 numberLength=3 exponent=100 position=1
num=2254 position=1 numberLength=4 exponent=1000 position=1
bucketCountList=[1, 5, 1, 0, 0, 0, 0, 0, 0, 0]arr=[89, 195, 196, 275, 276, 272, 2343]
origin arr:[195, 196, 275, 276, 272, 0, 0] position:2 maxLength:4
prepared arr:[195, 196, 275, 276, 272, 0, 0] position:2 maxLength:4
num=80 position=2 numberLength=2 exponent=1 position=2
num=81 position=2 numberLength=2 exponent=1 position=2
num=77 position=2 numberLength=2 exponent=1 position=2
bucketCountList=[3, 1, 0, 0, 0, 0, 0, 1, 0, 0]arr=[195, 196, 275, 276, 272, 0, 0]
origin arr:[195, 196, 275, 0, 0] position:3 maxLength:4
prepared arr:[195, 196, 275, 0, 0] position:3 maxLength:4
num=1 position=3 numberLength=1 exponent=0 position=3
num=80 position=3 numberLength=2 exponent=0 position=3
bucketCountList=[3, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[195, 196, 275, 0, 0]
origin arr:[195, 196, 275] position:4 maxLength:4
prepared arr:[195, 196, 275] position:4 maxLength:4
num=1 position=4 numberLength=1 exponent=0 position=4
num=80 position=4 numberLength=2 exponent=0 position=4
bucketCountList=[3, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[195, 196, 275]
origin arr:[195, 196, 275] position:5 maxLength:4
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:0 set arr:[195, 196, 275]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:1 set arr:[195, 196, 275]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:2 set arr:[195, 196, 275]
position:4 sorted arr:[195, 196, 275]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:0 set arr:[195, 196, 275, 0, 0]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:1 set arr:[195, 196, 275, 0, 0]
bucket:[195, 196, 275] sortedBucket:[195, 196, 275] sortedIdx:2 set arr:[195, 196, 275, 0, 0]
position:3 sorted arr:[195, 196, 275, 0, 0]
bucket:[195, 196, 275, 0, 0] sortedBucket:[195, 196, 275, 0, 0] sortedIdx:0 set arr:[195, 196, 275, 276, 272, 0, 0]
bucket:[195, 196, 275, 0, 0] sortedBucket:[195, 196, 275, 0, 0] sortedIdx:1 set arr:[195, 196, 275, 276, 272, 0, 0]
bucket:[195, 196, 275, 0, 0] sortedBucket:[195, 196, 275, 0, 0] sortedIdx:2 set arr:[195, 196, 275, 276, 272, 0, 0]
position:2 sorted arr:[195, 196, 275, 276, 272, 0, 0]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:1 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:2 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:3 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:4 set arr:[89, 195, 196, 275, 276, 272, 2343]
bucket:[195, 196, 275, 276, 272, 0, 0] sortedBucket:[195, 196, 275, 276, 272, 0, 0] sortedIdx:5 set arr:[89, 195, 196, 275, 276, 272, 2343]
position:1 sorted arr:[89, 195, 196, 275, 276, 272, 2343]

time:62 ms.
sort1 sorted:[89, 195, 196, 275, 276, 272, 2343]
sort2 start:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
maxLength:6
origin arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] position:1 maxLength:6
prepared arr:[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431] position:1 maxLength:6
num=323487 position=1 numberLength=6 exponent=100000 position=1
num=323450 position=1 numberLength=6 exponent=100000 position=1
num=323469 position=1 numberLength=6 exponent=100000 position=1
num=323497 position=1 numberLength=6 exponent=100000 position=1
num=323461 position=1 numberLength=6 exponent=100000 position=1
num=323464 position=1 numberLength=6 exponent=100000 position=1
num=324689 position=1 numberLength=6 exponent=100000 position=1
num=323654 position=1 numberLength=6 exponent=100000 position=1
num=410885 position=1 numberLength=6 exponent=100000 position=1
bucketCountList=[1, 0, 0, 8, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
origin arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] position:2 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0] position:2 maxLength:6
num=1239 position=2 numberLength=4 exponent=100 position=2
bucketCountList=[7, 0, 1, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
origin arr:[33, -4, 15, 43, 7, 10, 200, 0] position:3 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10, 200, 0] position:3 maxLength:6
num=204 position=3 numberLength=3 exponent=1 position=3
bucketCountList=[6, 0, 0, 0, 1, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 200, 0]
origin arr:[33, -4, 15, 43, 7, 10, 0] position:4 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10, 0] position:4 maxLength:6
num=37 position=4 numberLength=2 exponent=0 position=4
num=19 position=4 numberLength=2 exponent=0 position=4
num=47 position=4 numberLength=2 exponent=0 position=4
num=11 position=4 numberLength=2 exponent=0 position=4
num=14 position=4 numberLength=2 exponent=0 position=4
bucketCountList=[6, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10, 0]
origin arr:[33, -4, 15, 43, 7, 10] position:5 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10] position:5 maxLength:6
num=37 position=5 numberLength=2 exponent=0 position=5
num=19 position=5 numberLength=2 exponent=0 position=5
num=47 position=5 numberLength=2 exponent=0 position=5
num=11 position=5 numberLength=2 exponent=0 position=5
num=14 position=5 numberLength=2 exponent=0 position=5
bucketCountList=[6, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10]
origin arr:[33, -4, 15, 43, 7, 10] position:6 maxLength:6
prepared arr:[33, -4, 15, 43, 7, 10] position:6 maxLength:6
num=37 position=6 numberLength=2 exponent=0 position=6
num=19 position=6 numberLength=2 exponent=0 position=6
num=47 position=6 numberLength=2 exponent=0 position=6
num=11 position=6 numberLength=2 exponent=0 position=6
num=14 position=6 numberLength=2 exponent=0 position=6
bucketCountList=[6, 0, 0, 0, 0, 0, 0, 0, 0, 0]arr=[33, -4, 15, 43, 7, 10]
origin arr:[33, -4, 15, 43, 7, 10] position:7 maxLength:6
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10]
position:6 sorted arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10]
position:5 sorted arr:[33, -4, 15, 43, 7, 10]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10] sortedBucket:[33, -4, 15, 43, 7, 10] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10, 0]
position:4 sorted arr:[33, -4, 15, 43, 7, 10, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 0] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10, 200, 0]
position:3 sorted arr:[33, -4, 15, 43, 7, 10, 200, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:0 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:1 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:2 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:3 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:4 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:5 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 0] sortedIdx:6 set arr:[33, -4, 15, 43, 7, 10, 1235, 200, 0, 0]
position:2 sorted arr:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:1 set arr:[-323454, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:2 set arr:[-323454, 33, 15, 43, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:3 set arr:[-323454, 33, -4, 43, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:4 set arr:[-323454, 33, -4, 15, -323454, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:5 set arr:[-323454, 33, -4, 15, 43, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:6 set arr:[-323454, 33, -4, 15, 43, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:7 set arr:[-323454, 33, -4, 15, 43, 7, 10, 1235, 200, 87431]
bucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedBucket:[33, -4, 15, 43, 7, 10, 200, 1235, 0, 0] sortedIdx:8 set arr:[-323454, 33, -4, 15, 43, 7, 10, 200, 200, 87431]
position:1 sorted arr:[-323454, 33, -4, 15, 43, 7, 10, 200, 1235, 87431]

time:7 ms.
sort2 sorted:[-323454, 33, -4, 15, 43, 7, 10, 200, 1235, 87431]
 */
