/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

merge(List list, int left, int mid, int right) {
  List temp = [];
  temp.length = list.length;
  var i = left;
  var j = mid + 1;
  var k = 0;

  // 合并两个已排序数组。基于中间值，将原数组分为左右两个区间，两个区间是已分别排好序的。
  // 当左侧指针小于中间值(左侧还没有遍历完)且右侧指针小于最右侧(右侧也没有遍历完)
  while (i <= mid && j <= right) {
    // 拿左右的第一个值进行比较，如果左侧小于等于右侧，则将该项移到临时数组中最左侧
    if (list[i] <= list[j]) {
      // 同时左侧指针移动一个位置
      temp[k++] = list[i++];
    } else {
      // 如果右侧的值大于左侧，就把右侧的值添加到临时数组，右侧指针移动一个
      temp[k++] = list[j++];
    }
  }
  print('merge left: $list');
  // 如果左边数组还有剩余数据，就把左侧剩余都放入到原数组后面
  while (i <= mid) {
    temp[k++] = list[i++];
  }
  print('merge right: $list');
  // 如果右侧数组还有剩余数据，把剩下的数据放入到原数组后面
  while (j <= right) {
    temp[k++] = list[j++];
  }

  // 将排序后的元素全部移动到原数组中
  int x = 0;
  while (left <= right) {
    list[left++] = temp[x++];
  }
  print('merge list: $list');
}

mergeSort(List list, int left, int right) {
  // 得到中间值
  int mid = (left + right) ~/ 2;
  // 如果左侧小于右侧则执行合并排序
  if (left < right) {
    // 递归拆分左侧，直到拆分完成
    mergeSort(list, left, mid);
    print('list left: $list');
    // 递归拆分右侧，直到拆分完成
    mergeSort(list, mid + 1, right);
    print('list right: $list');
    // 再合并左右结果
    merge(list, left, mid, right);
  }
  return list;
}

main() {
  print("merge sort start:");
  List data = [4, 3, 2, 1, 5, -1, 10, 39];
  print(mergeSort(data, 0, data.length - 1));
}

/*
// test
jarry@jarrys-MacBook-Pro mergesort % dart --version
Dart SDK version: 2.14.1 (stable) (Wed Sep 8 13:33:08 2021 +0200) on "macos_x64"
jarry@jarrys-MacBook-Pro mergesort % dart merge_sort.dart 
*/