/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

void *selection_sort1(int arr[], int len)
{
  int min_value, min_idx, tmp;
  for (int i = 0; i < len - 1; i++)
  {
    min_value = arr[i];
    min_idx = i;
    int j = i + 1;
    for (; j < len; j++)
    {
      // 从待排序列表找到最小值和位置
      if (arr[j] < min_value)
      {
        min_value = arr[j];
        min_idx = j;
      }
    }
    printf("\r\n i=%d j=%d min_value=%d min_idx=%d", i, j, min_value, min_idx);
    // 将待排序里最小值交换到已排序最后面
    if (min_idx != i)
    {
      tmp = arr[i];
      arr[i] = min_value;
      arr[min_idx] = tmp;
    }
  }
  return arr;
}

// 根据下标移除数组项目
int remove_index(int arr[], int len, int idx)
{
  for (int i = idx; i < len; i++)
  {
    arr[i] = arr[i + 1];
  }
  return 1;
}

// 新建数组版，无需交换
void *selection_sort2(int arr[], int len)
{
  int min_value, min_idx, tmp;
  int static new_arr[7] = {};
  int new_idx = 0;
  for (int i = 0; i < len; i++)
  {
    min_value = arr[i];
    min_idx = i;
    int j = i + 1;
    for (; j < len; j++)
    {
      // 从待排序列表找到最小值和位置
      if (arr[j] < min_value)
      {
        min_value = arr[j];
        arr[j] = min_value;
        min_idx = j;
      }
    }
    printf("\r\n i=%d j=%d min_value=%d min_idx=%d", i, j, min_value, min_idx);
    // 添加到新数组
    new_arr[new_idx++] = min_value;
    // 从待排序中删除刚选出的最小项，下标同时减少1位
    remove_index(arr, len, min_idx);
    len--;
    i--;
  }
  return new_arr;
}

void print_array(int *arr, int len)
{
  printf("\r\n{ ");
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

int main()
{
  int arr1[7] = {7, 11, -9, 10, -12, 13, 8};
  printf("\r\n selection_sort start\r\n");
  int len1 = sizeof(arr1) / sizeof(arr1[0]);
  printf("\r\n arr1 origin:");
  print_array(arr1, len1);
  float time1 = clock();
  int *new_arr1 = selection_sort1(arr1, len1);
  print_array(new_arr1, len1);
  printf("\ntime: %f ms.", ((clock() - time1) / CLOCKS_PER_SEC * 1000));
  printf("\n selection_sort1 end\n");

  int arr2[7] = {7, 11, -9, 10, -12, 13, 8};
  printf("\r\n selection_sort start\r\n");
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n arr2 origin:");
  print_array(arr2, len2);
  float time2 = clock();
  int *new_arr2 = selection_sort1(arr2, len2);
  print_array(new_arr2, len2);
  printf("\ntime: %f ms.", ((clock() - time2) / CLOCKS_PER_SEC * 1000));
  printf("\n selection_sort2 end\n");
}
/**
jarry@jarrys-MacBook-Pro selectionsort % gcc selection_sort.c
jarry@jarrys-MacBook-Pro selectionsort % ./a.out

 selection_sort start

 arr1 origin:
{ 7, 11, -9, 10, -12, 13, 8 }
 i=0 j=7 min_value=-12 min_idx=4
 i=1 j=7 min_value=-9 min_idx=2
 i=2 j=7 min_value=7 min_idx=4
 i=3 j=7 min_value=8 min_idx=6
 i=4 j=7 min_value=10 min_idx=6
 i=5 j=7 min_value=11 min_idx=6
{ -12, -9, 7, 8, 10, 11, 13 }
time: 0.022000 ms.
 selection_sort1 end

 selection_sort start

 arr2 origin:
{ 7, 11, -9, 10, -12, 13, 8 }
 i=0 j=7 min_value=-12 min_idx=4
 i=1 j=7 min_value=-9 min_idx=2
 i=2 j=7 min_value=7 min_idx=4
 i=3 j=7 min_value=8 min_idx=6
 i=4 j=7 min_value=10 min_idx=6
 i=5 j=7 min_value=11 min_idx=6
{ -12, -9, 7, 8, 10, 11, 13 }
time: 0.023000 ms.
 selection_sort2 end
 */