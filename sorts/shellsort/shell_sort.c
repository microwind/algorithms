/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

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

int count(int arr[], int len, int number)
{
  int count = 0;
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == number)
      count++;
  }
  return count;
}

void print_array(float *arr, int len)
{
  printf("{ ");
  for (int i = 0; i < len; i++)
  {
    printf("%.1f", arr[i]);
    if (i < len - 1)
    {
      printf(", ");
    }
  }
  printf(" }");
}

void print_int_array(int *arr, int len)
{
  printf("{ ");
  for (int i = 0; i < len; i++)
  {
    printf("%d", arr[i]);
    if (i < len - 1)
    {
      printf(", ");
    }
  }
  printf(" }");
}

/* 1. 希尔排序标准版，基于插入排序进行分组排序，步长按1/2缩减。 */
float *shell_sort1(float arr[], int len)
{
  // 设置分组增量值（步长）为1/2的数组长度
  int gap = len / 2;
  // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
  while (gap > 0)
  {
    for (int i = 0; i < len; i++)
    {
      float current = arr[i];
      int j = i;
      // 对子序列按照插入排序
      while (j >= gap && current < arr[j - gap])
      {
        printf("\r\n gap=%d, i=%d, (j-gap)=%d, j=%d", gap, i, (j - gap), j);
        arr[j] = arr[j - gap];
        j -= gap;
      }
      // 交换当前项
      arr[j] = current;
    }
    // 调整步长为1/2
    gap = gap / 2;
  }
  return arr;
}

/* 2. 希尔排序，基于插入排序进行分组排序，步长按3倍递减。 */
int *shell_sort2(int arr[], int len)
{
  // 设置分组增量值（步长）为1/2的数组长度
  int gap = 1;
  // 初始步长按3倍递增，小于1/3数组长度
  while (gap < len / 3)
  {
    gap = gap * 3 + 1;
  }
  // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
  while (gap > 0)
  {
    for (int i = 0; i < len; i++)
    {
      int current = arr[i];
      int j = i - gap;
      // 对子序列按照插入排序
      for (; j >= 0 && arr[j] > current; j -= gap)
      {
        printf("\r\n gap=%d, i=%d, j=%d, (j+gap)=%d", gap, i, j, (j + gap));
        arr[j + gap] = arr[j];
      }
      arr[j + gap] = current;
    }
    // 步长按3倍缩减
    gap = (gap / 3);
  }
  return arr;
}

// test
int main()
{
  float arr[] = {3.3, 4, 1.5, 43, 323.454, -0.7, 10.5, 1235, 200, 87.431};
  int len = sizeof(arr) / sizeof(arr[0]);
  float time1 = clock();
  printf("\r\n origin arr1:");
  print_array(arr, len);
  float *result1 = shell_sort1(arr, len);
  printf("\r\n sorted:");
  print_array(result1, len);
  printf("\r\n time: %f ms.", ((clock() - time1) / CLOCKS_PER_SEC * 1000));

  int arr2[] = {33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  float time2 = clock();
  printf("\r\n origin arr2:");
  print_int_array(arr2, len2);
  int *result2 = shell_sort2(arr2, len2);
  printf("\r\n sorted:");
  print_int_array(result2, len2);
  printf("\r\n time: %f ms.", ((clock() - time2) / CLOCKS_PER_SEC * 1000));
  return 0;
}

/*
jarry@jarrys-MacBook-Pro shellsort % gcc shell_sort.c
jarry@jarrys-MacBook-Pro shellsort % ./a.out

origin arr1:{ 3.3, 4.0, 1.5, 43.0, 323.5, -0.7, 10.5, 1235.0, 200.0, 87.4 }
 gap=5, i=5, (j-gap)=0, j=5
 gap=5, i=9, (j-gap)=4, j=9
 gap=2, i=5, (j-gap)=3, j=5
 gap=2, i=5, (j-gap)=1, j=3
 gap=2, i=6, (j-gap)=4, j=6
 gap=2, i=9, (j-gap)=7, j=9
 gap=1, i=2, (j-gap)=1, j=2
 gap=1, i=8, (j-gap)=7, j=8
 sorted:{ -0.7, 1.5, 3.3, 4.0, 10.5, 43.0, 87.4, 200.0, 323.5, 1235.0 }
 time: 0.132000 ms.
 origin arr2:{ 33, 4, 15, 43, 323454, -7, 10, 1235, 200, 87431 }
 gap=4, i=5, j=1, (j+gap)=5
 gap=4, i=6, j=2, (j+gap)=6
 gap=4, i=8, j=4, (j+gap)=8
 gap=1, i=1, j=0, (j+gap)=1
 gap=1, i=2, j=1, (j+gap)=2
 gap=1, i=5, j=4, (j+gap)=5
 gap=1, i=5, j=3, (j+gap)=4
 gap=1, i=5, j=2, (j+gap)=3
 gap=1, i=5, j=1, (j+gap)=2
 gap=1, i=6, j=5, (j+gap)=6
 gap=1, i=6, j=4, (j+gap)=5
 gap=1, i=6, j=3, (j+gap)=4
 gap=1, i=9, j=8, (j+gap)=9
 sorted:{ -7, 4, 10, 15, 33, 43, 200, 1235, 87431, 323454 }
 time: 0.036000 ms.% 
*/