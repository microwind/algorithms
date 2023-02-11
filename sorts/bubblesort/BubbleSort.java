/**
 * Copyright © https://github.com/jarry All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class BubbleSort {

  public void swap(int arr[], int from, int to) {
    Object tmp = arr[from];
    arr[from] = arr[to];
    arr[to] = (int) tmp;
  }

  /**
   * 冒泡排序升序，将最大的冒泡到最后
   */
  void sort1(int arr[]) {
    System.out.println("bubbleSort1 from left to right:");
    int len = arr.length;
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          int tmp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = tmp;
        }
        System.out.println("i=" + i + " j=" + j + " arr[i]=" + arr[i] + " arr[j=]" + arr[j]);
      }
    }
  }

  /**
   * 冒泡排序降序，将最小的冒泡到最后
   */
  void sort2(int arr[]) {
    System.out.println("bubbleSort2 from right to left:");
    int len = arr.length;
    for (int i = 0; i < len; i++) {
      for (int j = len - 1; j > i; j--) {
        // 自右往左每两个进行比较，把小的交换到右侧
        // 逐轮冒出最小数，已经排好序的不要再比较
        if (arr[j - 1] < arr[j]) {
          this.swap(arr, j - 1, j);
        }
        System.out.println("i=" + i + " j=" + j + " arr[i]=" + arr[i] + " arr[j=]" + arr[j]);
      }
    }
  }

  /**
   * 冒泡排序增加交换标志，针对有序情况优化
   */
  void sort3(int arr[]) {
    System.out.println("bubbleSort3 add flag:");
    // 增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历，
    int len = arr.length;
    boolean flag = true;

    for (int i = 0; i < len && flag == true; i++) {
      flag = false;
      System.out.println("no. " + i);
      for (int j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          flag = true;
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