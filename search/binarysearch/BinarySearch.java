
/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
import java.util.*;

// 标准非递归版本，传递左右区间指针
class BinarySearch {
  int search1(int[] arr, int target) {
    int left = 0;
    int right = arr.length - 1;
    int midIndex, mid;
    // left是左侧，right是最右侧。搜索区间长度小于1时停止
    while (left <= right) {
      midIndex = (left + right) / 2;
      mid = arr[midIndex];
      // 中间项等于目标项则返回下标
      if (target > mid) {
        // 大于中间项折半查找右侧
        left = midIndex + 1;
      } else {
        // 小于中间项折半查找左侧
        right = midIndex - 1;
      }
    }
    //  此时left是最左侧目标项
    if (left < arr.length && arr[left] == target) {
      return left;
    }

    return -1;
  }

  // 递归实现，移动左右区间指针
  int search2(int[] arr, int target, int left, int right) {
    right = right == -1 ? arr.length - 1 : right;
    int midIndex = (left + right) / 2;
    int mid = arr[midIndex];
    // 中间值等于查找项说明找到了，则返回中间项下标
    if (target == mid) {
      // 如果有重复项，返回第一个位置
      if (arr[left] == target) {
        return left;
      }
      return midIndex;
    }
    // 如果左侧与右侧相同，表面查找完毕，返回-1
    if (left >= right) {
      return -1;
    }
    if (target > mid) {
      // 折半右侧部分开始递归查找
      return this.search2(arr, target, midIndex + 1, right);
    } else {
      // 折半左侧部分开始递归查找
      return this.search2(arr, target, left, midIndex - 1);
    }
  }

  public static void main(final String args[]) {
    int[] arr = { 2, 3, 8, 10, 10, 13 };
    BinarySearch binarySearch = new BinarySearch();

    long startTime = System.currentTimeMillis();
    int result = binarySearch.search1(arr, 10); // 3
    System.out.println("binarySearch.search1(arr, 10) => result:" + result);
    result = binarySearch.search1(arr, 3); // 1
    System.out.println("binarySearch.search1(arr, 3) => result:" + result);
    result = binarySearch.search1(arr, 99); // -1
    System.out.println("binarySearch.search1(arr, 99) => result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

    startTime = System.currentTimeMillis();
    result = binarySearch.search2(arr, 10, 0, -1); // 3
    System.out.println("binarySearch.search2(arr, 10) => result:" + result);
    result = binarySearch.search2(arr, 3, 0, -1); // 1
    System.out.println("binarySearch.search2(arr, 3, 0, -1) => result:" + result);
    result = binarySearch.search2(arr, 99, 0, -1); // -1
    System.out.println("binarySearch.search2(arr, 99, 0, -1) => result:" + result);
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");

  }
}

/**
jarry@jarrys-MacBook-Pro binarysearch % javac BinarySearch.java
jarry@jarrys-MacBook-Pro binarysearch % java BinarySearch      
binarySearch.search1(arr, 10) => result:3
binarySearch.search1(arr, 3) => result:1
binarySearch.search1(arr, 99) => result:-1

time:13 ms.
binarySearch.search2(arr, 10) => result:3
binarySearch.search2(arr, 3, 0, -1) => result:1
binarySearch.search2(arr, 99, 0, -1) => result:-1

time:1 ms.
 */