/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

void *selectionSort(int arr[], int len)
{
  int min, minIdx, tmp;
  for (int i = 0; i < len - 1; i++)
  {
    min = arr[i];
    minIdx = i;
    int j = i + 1;
    for (; j < len; j++)
    {
      // 从待排序列表找到最小值和位置
      if (arr[j] < min)
      {
        min = arr[j];
        minIdx = j;
      }
    }
    printf("\r\n i=%d j=%d min=%d minIdx=%d", i, j, min, minIdx);
    // 将待排序里最小值交换到已排序最后面
    if (minIdx != i)
    {
      tmp = arr[i];
      arr[i] = min;
      arr[minIdx] = tmp;
    }
  }
  return arr;
}

int removeIndex(int arr[], int len, int idx)
{
  for (int i = idx; i < len; i++)
  {
    arr[i] = arr[i + 1];
  }
  return 1;
}

// 新建数组版，无需交换
void *selectionSort2(int arr[], int len)
{
  int min, minIdx, tmp;
  int static newArr[7] = {};
  int newIdx = 0;
  for (int i = 0; i < len; i++)
  {
    min = arr[i];
    minIdx = i;
    int j = i + 1;
    for (; j < len; j++)
    {
      // 从待排序列表找到最小值和位置
      if (arr[j] < min)
      {
        min = arr[j];
        arr[j] = min;
        minIdx = j;
      }
    }
    printf("\r\n i=%d j=%d min=%d minIdx=%d", i, j, min, minIdx);
    // add to new array
    newArr[newIdx++] = min;
    // remove the min element
    removeIndex(arr, len, minIdx);
    len--;
    i--;
  }
  return newArr;
}

int main()
{
  int arr[7] = {7, 11, 9, 10, 12, 13, 8};
  printf("\r\n selectionSort start\r\n");
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("\r\n origin:");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  float startTime = clock();
  int *newArr = selectionSort2(arr, len);
  printf("\r\n sorted:");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", newArr[i]);
  }

  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\n selectionSort end\n");
}
/**
jarrys-MacBook-Pro:selectionsort jarry$ gcc selection_sort.c
jarrys-MacBook-Pro:selectionsort jarry$ ./a.out 

 selectionSort start

 origin:7 11 9 10 12 13 8 
 i=0 j=7 min=7 minIdx=0
 i=1 j=7 min=8 minIdx=6
 i=2 j=7 min=9 minIdx=2
 i=3 j=7 min=10 minIdx=3
 i=4 j=7 min=11 minIdx=6
 i=5 j=7 min=12 minIdx=6
 sorted:7 8 9 10 11 12 13 
time: 0.013000 ms.
 selectionSort end
 */