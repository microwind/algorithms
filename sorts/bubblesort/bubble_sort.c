/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

// #define BOOL int
// #define TRUE 1
// #define FALSE 0

typedef enum
{
  true = 1,
  false = 0
} bool;

void swap(int arr[], int a, int b)
{
  int tmp = arr[b];
  arr[b] = arr[a];
  arr[a] = tmp;
}

// ASE
void bubbleSort1(int arr[], int len)
{
  printf("bubbleSort from left to right:");
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < len - i - 1; j++)
    {
      // 自左往右每两个进行比较，把大的交换到右侧
      // 逐轮冒出最大数，已经排好序的不要再比较
      if (arr[j] > arr[j + 1])
      {
        swap(arr, j, j + 1);
      }
      printf("\r\n i=%d j=%d", i, j);
    }
  }
}

// DESC
int bubbleSort2(int arr[], int len)
{
  printf("bubbleSort from right to left:");
  for (int i = 0; i < len; i++)
  {
    for (int j = len; j > i; j--)
    {
      // 自右往左每两个进行比较，把小的交换到右侧
      // 逐轮冒出最小数，已经排好序的不要再比较
      if (arr[j - 1] < arr[j])
      {
        swap(arr, j, j - 1);
      }
      printf("\r\n i=%d j=%d", i, j);
    }
  }
  return 0;
}

// add flag
void bubbleSort(int arr[], int len)
{
  printf("bubbleSort add flag:");
  // 增加一个标志，如果某一轮没有进行过任何的交换
  // 则说明当前数组已排好序，则不必继续后面的遍历，
  bool flag = true;

  for (int i = 0; i < len && flag == true; i++)
  {
    flag = false;
    printf("\r\nno. %d", i);
    for (int j = 0; j < len - i - 1; j++)
    {
      // 自左往右每两个进行比较，把大的交换到右侧
      // 逐轮冒出最大数，已经排好序的不要再比较
      if (arr[j] > arr[j + 1])
      {
        flag = true;
        swap(arr, j, j + 1);
      }
      printf("\r\n i=%d j=%d", i, j);
    }
  }
}

int main()
{
  int arr[7] = {7, 11, 9, 10, 12, 13, 8};
  printf("\r\nbubbleSort start\r\n");
  float startTime = clock();
  int len = sizeof(arr) / sizeof(arr[0]);
  bubbleSort(arr, len);
  printf("\r\nsorted:");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\nbubbleSort end\n");
}
/*
jarrys-MacBook-Pro:bubblesort jarry$ gcc bubble_sort.c
jarrys-MacBook-Pro:bubblesort jarry$ ./a.out 

bubbleSort start
bubbleSort add flag:
no. 0
 i=0 j=0
 i=0 j=1
 i=0 j=2
 i=0 j=3
 i=0 j=4
 i=0 j=5
no. 1
 i=1 j=0
 i=1 j=1
 i=1 j=2
 i=1 j=3
 i=1 j=4
no. 2
 i=2 j=0
 i=2 j=1
 i=2 j=2
 i=2 j=3
no. 3
 i=3 j=0
 i=3 j=1
 i=3 j=2
no. 4
 i=4 j=0
 i=4 j=1
no. 5
 i=5 j=0
sorted:7 8 9 10 11 12 13 
time: 0.046000 ms.
bubbleSort end
*/