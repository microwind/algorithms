/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 冒泡排序升序，将最大的冒泡到最后
 */
bubbleSort1(List list) {
  var len = list.length;
  for (var i = 0; i < len; i++) {
    print("no:" + i.toString());
    for (var j = 0; j < len - i - 1; j++) {
      if (list[j] > list[j + 1]) {
        var tmp = list[j + 1];
        list[j + 1] = list[j];
        list[j] = tmp;
      }
      print(j.toString() + " * " + i.toString());
    }
  }
  return list;
}

/**
 * 冒泡排序降序且增加交换标志，针对有序情况优化
 */
bubbleSort2(List list) {
  var len = list.length;
  bool flag = true;
  // 增加一个标志，如果某一轮没有进行过任何的交换
  // 则说明当前数组已排好序，则不必继续后面的遍历，
  for (var i = 0; i < len && flag == true; i++) {
    print("no:" + i.toString());
    flag = false;
    for (var j = len - 1; j > i; j--) {
      if (list[j] > list[j - 1]) {
        flag = true;
        var tmp = list[j - 1];
        list[j - 1] = list[j];
        list[j] = tmp;
      }
      print(j.toString() + " * " + i.toString());
    }
  }
  return list;
}

main() {
  print("bubblesort1 start:");
  List data1 = [3, 2.5, 10, -4, -0.45];
  print("bubblesort1 sorted: ${bubbleSort1(data1)}");
  print("bubblesort2 start:");
  List data2 = [3, 2.5, 10, -4, -0.45];
  print("bubblesort2 sorted: ${bubbleSort2(data2)}");
}

/*
jarry@jarrys-MacBook-Pro flutter_app % dart --version
Dart SDK version: 2.12.2 (stable) on "macos_x64"
jarry@jarrys-MacBook-Pro bubblesort % dart bubble_sort.dart 
bubblesort1 start:
no:0
0 * 0
1 * 0
2 * 0
3 * 0
no:1
0 * 1
1 * 1
2 * 1
no:2
0 * 2
1 * 2
no:3
0 * 3
no:4
bubblesort1 sorted: [-4, -0.45, 2.5, 3, 10]
bubblesort2 start:
no:0
4 * 0
3 * 0
2 * 0
1 * 0
no:1
4 * 1
3 * 1
2 * 1
bubblesort2 sorted: [10, 3, 2.5, -0.45, -4]
*/