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


// 分为左右两个序列，左侧为已排序，将待排项与左侧逐个对比并交换位置
int *bubbleSort3(int arr[], int len)
{
  for (int i = 1; i < len; i++)
  {
    int j = i - 1;
    int current = i;
    while (j >= 0)
    {
      if (arr[current] < arr[j]) {
        printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
        int temp = arr[current];
        arr[current] = arr[j];
        arr[j] = temp;
      }
      current = j;
      j--;
    }
  }
  
  return arr;
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

  // 1
  int arr1[7] = {7, 11, -9, 10, 12, 13, 8};
  int len1 = sizeof(arr1) / sizeof(arr1[0]);
  bubbleSort1(arr1, len1);
  printf("\n bubbleSort1 end:\n");
  for (int i = 0; i < len1; i++)
  {
    printf("%d ", arr1[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  // 2
  int arr2[7] = {7, 11, -9, 10, 12, 13, 8};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  bubbleSort2(arr2, len2);
  printf("\n bubbleSort2 end:\n");
  for (int i = 0; i < len2; i++)
  {
    printf("%d ", arr2[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  // 3
  int arr3[7] = {7, 11, -9, 10, 12, 13, 8};
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  bubbleSort3(arr3, len3);
  printf("\n bubbleSort3 end:\n");
  for (int i = 0; i < len3; i++)
  {
    printf("%d ", arr3[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
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
time: 0.041000 ms.
bubbleSort end
bubbleSort from left to right:
 i=0 j=0
 i=0 j=1
 i=0 j=2
 i=0 j=3
 i=0 j=4
 i=0 j=5
 i=1 j=0
 i=1 j=1
 i=1 j=2
 i=1 j=3
 i=1 j=4
 i=2 j=0
 i=2 j=1
 i=2 j=2
 i=2 j=3
 i=3 j=0
 i=3 j=1
 i=3 j=2
 i=4 j=0
 i=4 j=1
 i=5 j=0
 bubbleSort1 end:
-9 7 8 10 11 12 13 
time: 0.088000 ms.bubbleSort from right to left:
 i=0 j=7
 i=0 j=6
 i=0 j=5
 i=0 j=4
 i=0 j=3
 i=0 j=2
 i=0 j=1
 i=1 j=7
 i=1 j=6
 i=1 j=5
 i=1 j=4
 i=1 j=3
 i=1 j=2
 i=2 j=7
 i=2 j=6
 i=2 j=5
 i=2 j=4
 i=2 j=3
 i=3 j=7
 i=3 j=6
 i=3 j=5
 i=3 j=4
 i=4 j=7
 i=4 j=6
 i=4 j=5
 i=5 j=7
 i=5 j=6
 i=6 j=7
 bubbleSort2 end:
13 12 11 10 8 7 0 
time: 0.140000 ms.
i=2, j=1, arr[i]=-9, arr[j+1]=-9
i=2, j=0, arr[i]=11, arr[j+1]=-9
i=3, j=2, arr[i]=10, arr[j+1]=10
i=6, j=5, arr[i]=8, arr[j+1]=8
i=6, j=4, arr[i]=13, arr[j+1]=8
i=6, j=3, arr[i]=13, arr[j+1]=8
i=6, j=2, arr[i]=13, arr[j+1]=8
 bubbleSort3 end:
-9 7 8 10 11 12 13 
time: 0.161000 ms.%  
*/