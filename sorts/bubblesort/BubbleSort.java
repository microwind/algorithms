/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

class BubbleSort {

  public void swap(int arr[], int from, int to) {
    Object tmp = arr[from];
    arr[from] = arr[to];
    arr[to] = (int) tmp;
  }

  // ASE
  void sort1(int arr[]) {
    System.out.println("bubbleSort from left to right:");
    int len = arr.length;
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len - i - 1; j++) {
        // 自左往右每两个进行比较，把大的交换到右侧
        // 逐轮冒出最大数，已经排好序的不要再比较
        if (arr[j] > arr[j + 1]) {
          this.swap(arr, j, j + 1);
        }
        System.out.println("i=" + i + " j=" + j + " arr[i]=" + arr[i] + " arr[j=]" + arr[j]);
      }
    }
  }

  // DESC
  void sort2(int arr[]) {
    System.out.println("bubbleSort from right to left:");
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

  // add flag
  void sort(int arr[]) {
    System.out.println("bubbleSort add flag:");
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

  public static void main(String args[]) {

    int arr[] = { 7, 11, 9, 10, 12, 13, 8 };
    for (int item : arr) {
      System.out.print(" " + item);
    }
    System.out.println("\r\nBubbleSort Start:");
    long startTime = System.currentTimeMillis();
    new BubbleSort().sort(arr);
    for (int item : arr) {
      System.out.print(" " + item);
    }
    System.out.println("\r\ntime:" + (System.currentTimeMillis() - startTime) + " ms.");
    System.out.println("\r\nBubbleSort end.");
  }
}

/*
jarrys-MacBook-Pro:bubblesort jarry$ java BubbleSort
 7 11 9 10 12 13 8
BubbleSort Start:
bubbleSort add flag:
no. 0
i=0 j=0 arr[i]=7 arr[j=]7
i=0 j=1 arr[i]=7 arr[j=]9
i=0 j=2 arr[i]=7 arr[j=]10
i=0 j=3 arr[i]=7 arr[j=]11
i=0 j=4 arr[i]=7 arr[j=]12
i=0 j=5 arr[i]=7 arr[j=]8
no. 1
i=1 j=0 arr[i]=9 arr[j=]7
i=1 j=1 arr[i]=9 arr[j=]9
i=1 j=2 arr[i]=9 arr[j=]10
i=1 j=3 arr[i]=9 arr[j=]11
i=1 j=4 arr[i]=9 arr[j=]8
no. 2
i=2 j=0 arr[i]=10 arr[j=]7
i=2 j=1 arr[i]=10 arr[j=]9
i=2 j=2 arr[i]=10 arr[j=]10
i=2 j=3 arr[i]=10 arr[j=]8
no. 3
i=3 j=0 arr[i]=8 arr[j=]7
i=3 j=1 arr[i]=8 arr[j=]9
i=3 j=2 arr[i]=10 arr[j=]8
no. 4
i=4 j=0 arr[i]=11 arr[j=]7
i=4 j=1 arr[i]=11 arr[j=]8
no. 5
i=5 j=0 arr[i]=12 arr[j=]7
 7 8 9 10 11 12 13
time:26 ms.

BubbleSort end.
 */