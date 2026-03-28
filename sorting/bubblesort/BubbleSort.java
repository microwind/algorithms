/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class BubbleSort {

  /**
   * 交换数组中两个位置的元素
   * @param arr 目标数组
   * @param from 交换的起始位置
   * @param to 交换的目标位置
   */
  public void swap(int arr[], int from, int to) {
    Object tmp = arr[from];
    arr[from] = arr[to];
    arr[to] = (int) tmp;
  }

  /**
   * 冒泡排序升序，将最大的元素冒泡到最后
   * 时间复杂度：O(n²)，空间复杂度：O(1)，稳定性：稳定
   */
  void sort1(int arr[]) {
    System.out.println("bubbleSort1 from left to right:");
    int len = arr.length;
    // 外层循环控制排序轮数，每轮确定一个最大值的位置
    for (int i = 0; i < len; i++) {
      // 内层循环控制比较次数，len-i-1 避免重复比较已排序部分
      for (int j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          // 交换相邻元素，大的向后移动
          int tmp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = tmp;
        }
        System.out.println("i=" + i + " j=" + j + " arr[i]=" + arr[i] + " arr[j=]" + arr[j]);
      }
    }
  }

  /**
   * 冒泡排序降序，将最小的元素冒泡到最后
   * 从右向左比较，逐轮冒出最小数
   * 时间复杂度：O(n²)，空间复杂度：O(1)，稳定性：稳定
   */
  void sort2(int arr[]) {
    System.out.println("bubbleSort2 from right to left:");
    int len = arr.length;
    // 外层循环控制排序轮数，每轮确定一个最小值的位置
    for (int i = 0; i < len; i++) {
      // 内层循环从右向左比较，j > i 避免重复比较已排序部分
      for (int j = len - 1; j > i; j--) {
        // 自右往左每两个进行比较，把小的交换到右侧
        // 逐轮冒出最小数，已经排好序的不要再比较
        if (arr[j - 1] < arr[j]) {
          // 使用 swap 方法交换元素
          this.swap(arr, j - 1, j);
        }
        System.out.println("i=" + i + " j=" + j + " arr[i]=" + arr[i] + " arr[j=]" + arr[j]);
      }
    }
  }

  /**
   * 冒泡排序升序，增加交换标志优化
   * 当某一轮无交换时提前终止，针对有序情况优化
   * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
   */
  void sort3(int arr[]) {
    System.out.println("bubbleSort3 add flag:");
    // 增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历，
    int len = arr.length;
    boolean flag = true;

    // 外层循环增加 flag 条件，当数组已有序时提前终止
    for (int i = 0; i < len && flag == true; i++) {
      flag = false;  // 每轮开始时重置标志
      System.out.println("no. " + i);
      // 内层循环控制比较次数，len-i-1 避免重复比较已排序部分
      for (int j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          flag = true;  // 发生交换，设置标志为 true
          // 使用 swap 方法交换元素
          this.swap(arr, j, j + 1);
        }
        System.out.println("i=" + i + " j=" + j + " arr[i]=" + arr[i] + " arr[j=]" + arr[j]);
      }
    }
  }

  /* test */
  public static void main(String args[]) {

    BubbleSort bubbleSort = new BubbleSort();
    long startTime;

    // sort1
    int arr1[] = { 7, 11, 9, 10, 12, 13, 8 };
    for (int item : arr1) {
      System.out.print(" " + item);
    }
    System.out.println("\r\nBubbleSort1 Start:");
    startTime = System.currentTimeMillis();
    bubbleSort.sort1(arr1);
    for (int item : arr1) {
      System.out.print(" " + item);
    }
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("\r\nBubbleSort1 end.");

    // sort2
    int arr2[] = { 7, 11, 9, 10, 12, 13, 8 };
    for (int item : arr2) {
      System.out.print(" " + item);
    }
    System.out.println("\r\nBubbleSort2 Start:");
    startTime = System.currentTimeMillis();
    bubbleSort.sort2(arr2);
    for (int item : arr2) {
      System.out.print(" " + item);
    }
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("\r\nBubbleSort2 end.");

    // sort3
    int arr3[] = { 7, 11, 9, 10, 12, 13, 8 };
    for (int item : arr3) {
      System.out.print(" " + item);
    }
    System.out.println("\r\nBubbleSort3 Start:");
    startTime = System.currentTimeMillis();
    bubbleSort.sort3(arr3);
    for (int item : arr3) {
      System.out.print(" " + item);
    }
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("\r\nBubbleSort3 end.");
  }
}

/*
 * jarrys-MacBook-Pro:bubblesort jarry$ java BubbleSort
 * 7 11 9 10 12 13 8
 * BubbleSort1 Start:
 * bubbleSort from left to right:
 * i=0 j=0 arr[i]=7 arr[j=]7
 * i=0 j=1 arr[i]=7 arr[j=]9
 * i=0 j=2 arr[i]=7 arr[j=]10
 * i=0 j=3 arr[i]=7 arr[j=]11
 * i=0 j=4 arr[i]=7 arr[j=]12
 * i=0 j=5 arr[i]=7 arr[j=]8
 * i=1 j=0 arr[i]=9 arr[j=]7
 * i=1 j=1 arr[i]=9 arr[j=]9
 * i=1 j=2 arr[i]=9 arr[j=]10
 * i=1 j=3 arr[i]=9 arr[j=]11
 * i=1 j=4 arr[i]=9 arr[j=]8
 * i=2 j=0 arr[i]=10 arr[j=]7
 * i=2 j=1 arr[i]=10 arr[j=]9
 * i=2 j=2 arr[i]=10 arr[j=]10
 * i=2 j=3 arr[i]=10 arr[j=]8
 * i=3 j=0 arr[i]=8 arr[j=]7
 * i=3 j=1 arr[i]=8 arr[j=]9
 * i=3 j=2 arr[i]=10 arr[j=]8
 * i=4 j=0 arr[i]=11 arr[j=]7
 * i=4 j=1 arr[i]=11 arr[j=]8
 * i=5 j=0 arr[i]=12 arr[j=]7
 * 7 8 9 10 11 12 13
 * time:11 ms.
 * 
 * BubbleSort1 end.
 * 7 11 9 10 12 13 8
 * BubbleSort2 Start:
 * bubbleSort from right to left:
 * i=0 j=6 arr[i]=7 arr[j=]8
 * i=0 j=5 arr[i]=7 arr[j=]12
 * i=0 j=4 arr[i]=7 arr[j=]10
 * i=0 j=3 arr[i]=7 arr[j=]9
 * i=0 j=2 arr[i]=7 arr[j=]11
 * i=0 j=1 arr[i]=13 arr[j=]7
 * i=1 j=6 arr[i]=7 arr[j=]8
 * i=1 j=5 arr[i]=7 arr[j=]10
 * i=1 j=4 arr[i]=7 arr[j=]9
 * i=1 j=3 arr[i]=7 arr[j=]11
 * i=1 j=2 arr[i]=12 arr[j=]7
 * i=2 j=6 arr[i]=7 arr[j=]8
 * i=2 j=5 arr[i]=7 arr[j=]9
 * i=2 j=4 arr[i]=7 arr[j=]10
 * i=2 j=3 arr[i]=11 arr[j=]7
 * i=3 j=6 arr[i]=7 arr[j=]8
 * i=3 j=5 arr[i]=7 arr[j=]9
 * i=3 j=4 arr[i]=10 arr[j=]7
 * i=4 j=6 arr[i]=7 arr[j=]8
 * i=4 j=5 arr[i]=9 arr[j=]7
 * i=5 j=6 arr[i]=8 arr[j=]7
 * 13 12 11 10 9 8 7
 * time:2 ms.
 * 
 * BubbleSort2 end.
 * 7 11 9 10 12 13 8
 * BubbleSort3 Start:
 * bubbleSort add flag:
 * no. 0
 * i=0 j=0 arr[i]=7 arr[j=]7
 * i=0 j=1 arr[i]=7 arr[j=]9
 * i=0 j=2 arr[i]=7 arr[j=]10
 * i=0 j=3 arr[i]=7 arr[j=]11
 * i=0 j=4 arr[i]=7 arr[j=]12
 * i=0 j=5 arr[i]=7 arr[j=]8
 * no. 1
 * i=1 j=0 arr[i]=9 arr[j=]7
 * i=1 j=1 arr[i]=9 arr[j=]9
 * i=1 j=2 arr[i]=9 arr[j=]10
 * i=1 j=3 arr[i]=9 arr[j=]11
 * i=1 j=4 arr[i]=9 arr[j=]8
 * no. 2
 * i=2 j=0 arr[i]=10 arr[j=]7
 * i=2 j=1 arr[i]=10 arr[j=]9
 * i=2 j=2 arr[i]=10 arr[j=]10
 * i=2 j=3 arr[i]=10 arr[j=]8
 * no. 3
 * i=3 j=0 arr[i]=8 arr[j=]7
 * i=3 j=1 arr[i]=8 arr[j=]9
 * i=3 j=2 arr[i]=10 arr[j=]8
 * no. 4
 * jarry@jarrys-MacBook-Pro bubblesort % javac BubbleSort.java
 * jarry@jarrys-MacBook-Pro bubblesort % java BubbleSort
 * 7 11 9 10 12 13 8
 * BubbleSort1 Start:
 * bubbleSort1 from left to right:
 * i=0 j=0 arr[i]=7 arr[j=]7
 * i=0 j=1 arr[i]=7 arr[j=]9
 * i=0 j=2 arr[i]=7 arr[j=]10
 * i=0 j=3 arr[i]=7 arr[j=]11
 * i=0 j=4 arr[i]=7 arr[j=]12
 * i=0 j=5 arr[i]=7 arr[j=]8
 * i=1 j=0 arr[i]=9 arr[j=]7
 * i=1 j=1 arr[i]=9 arr[j=]9
 * i=1 j=2 arr[i]=9 arr[j=]10
 * i=1 j=3 arr[i]=9 arr[j=]11
 * i=1 j=4 arr[i]=9 arr[j=]8
 * i=2 j=0 arr[i]=10 arr[j=]7
 * i=2 j=1 arr[i]=10 arr[j=]9
 * i=2 j=2 arr[i]=10 arr[j=]10
 * i=2 j=3 arr[i]=10 arr[j=]8
 * i=3 j=0 arr[i]=8 arr[j=]7
 * i=3 j=1 arr[i]=8 arr[j=]9
 * i=3 j=2 arr[i]=10 arr[j=]8
 * i=4 j=0 arr[i]=11 arr[j=]7
 * i=4 j=1 arr[i]=11 arr[j=]8
 * i=5 j=0 arr[i]=12 arr[j=]7
 * 7 8 9 10 11 12 13
 * time:11 ms.
 * 
 * BubbleSort1 end.
 * 7 11 9 10 12 13 8
 * BubbleSort2 Start:
 * bubbleSort2 from right to left:
 * i=0 j=6 arr[i]=7 arr[j=]8
 * i=0 j=5 arr[i]=7 arr[j=]12
 * i=0 j=4 arr[i]=7 arr[j=]10
 * i=0 j=3 arr[i]=7 arr[j=]9
 * i=0 j=2 arr[i]=7 arr[j=]11
 * i=0 j=1 arr[i]=13 arr[j=]7
 * i=1 j=6 arr[i]=7 arr[j=]8
 * i=1 j=5 arr[i]=7 arr[j=]10
 * i=1 j=4 arr[i]=7 arr[j=]9
 * i=1 j=3 arr[i]=7 arr[j=]11
 * i=1 j=2 arr[i]=12 arr[j=]7
 * i=2 j=6 arr[i]=7 arr[j=]8
 * i=2 j=5 arr[i]=7 arr[j=]9
 * i=2 j=4 arr[i]=7 arr[j=]10
 * i=2 j=3 arr[i]=11 arr[j=]7
 * i=3 j=6 arr[i]=7 arr[j=]8
 * i=3 j=5 arr[i]=7 arr[j=]9
 * i=3 j=4 arr[i]=10 arr[j=]7
 * i=4 j=6 arr[i]=7 arr[j=]8
 * i=4 j=5 arr[i]=9 arr[j=]7
 * i=5 j=6 arr[i]=8 arr[j=]7
 * 13 12 11 10 9 8 7
 * time:2 ms.
 * 
 * BubbleSort2 end.
 * 7 11 9 10 12 13 8
 * BubbleSort3 Start:
 * bubbleSort3 add flag:
 * no. 0
 * i=0 j=0 arr[i]=7 arr[j=]7
 * i=0 j=1 arr[i]=7 arr[j=]9
 * i=0 j=2 arr[i]=7 arr[j=]10
 * i=0 j=3 arr[i]=7 arr[j=]11
 * i=0 j=4 arr[i]=7 arr[j=]12
 * i=0 j=5 arr[i]=7 arr[j=]8
 * no. 1
 * i=1 j=0 arr[i]=9 arr[j=]7
 * i=1 j=1 arr[i]=9 arr[j=]9
 * i=1 j=2 arr[i]=9 arr[j=]10
 * i=1 j=3 arr[i]=9 arr[j=]11
 * i=1 j=4 arr[i]=9 arr[j=]8
 * no. 2
 * i=2 j=0 arr[i]=10 arr[j=]7
 * i=2 j=1 arr[i]=10 arr[j=]9
 * i=2 j=2 arr[i]=10 arr[j=]10
 * i=2 j=3 arr[i]=10 arr[j=]8
 * no. 3
 * i=3 j=0 arr[i]=8 arr[j=]7
 * i=3 j=1 arr[i]=8 arr[j=]9
 * i=3 j=2 arr[i]=10 arr[j=]8
 * no. 4
 * i=4 j=0 arr[i]=11 arr[j=]7
 * i=4 j=1 arr[i]=11 arr[j=]8
 * no. 5
 * i=5 j=0 arr[i]=12 arr[j=]7
 * 7 8 9 10 11 12 13
 * time:1 ms.
 * 
 * BubbleSort3 end.
 */