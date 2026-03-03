/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

// 标准非递归版本，传递左右区间指针
int binarySearch1(list, target) {
  var left = 0;
  var right = list.length - 1;
  var midIndex, mid;
  // left是左侧，right是最右侧。搜索区间长度小于1时停止
  while (left <= right) {
    midIndex = (left + right) ~/ 2;
    mid = list[midIndex];
    // 中间项等于目标项则返回下标
    if (mid == target) {
      return midIndex;
    } else if (target > mid) {
      // 大于中间项折半查找右侧
      left = midIndex + 1;
    } else {
      // 小于中间项折半查找左侧
      right = midIndex - 1;
    }
  }
  return -1;
}

int binarySearch2(list, target, left, right) {
  left = left == null ? 0 : left;
  right = right == null ? list.length - 1 : right;
  var midIndex = (left + right) ~/ 2;
  var mid = list[midIndex];
  // 中间值等于查找项说明找到了，则返回中间项下标
  if (target == mid) {
    // 如果有重复项，返回第一个位置
    if (list[left] == target) {
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
    return binarySearch2(list, target, midIndex + 1, right);
  } else {
    // 折半左侧部分开始递归查找
    return binarySearch2(list, target, left, midIndex - 1);
  }
}


void main() {
  var list = [2, 3, 9, 10, 23, 34, 45];

  // test binarySearch1
  print(binarySearch1(list, 10)); // 3
  print(binarySearch1(list, 2));  // 0
  print(binarySearch1(list, 4)); // -1 not found

  // test binarySearch2
  print(binarySearch2(list, 10, 0, list.length)); // 3
  print(binarySearch2(list, 2, 0, list.length));  // 0
  print(binarySearch2(list, 4, 0, list.length)); // -1 not found
}

/**
jarry@jarrys-MacBook-Pro factor % dart --version
Dart SDK version: 2.10.2 on "macos_x64"
jarry@jarrys-MacBook-Pro binarysearch % dart binary_search.dart
3
0
-1
3
0
-1
 */