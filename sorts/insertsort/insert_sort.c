/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

int *insertSort1(int arr[], int len)
{
  int j;
  int current;
  // 外循环用于遍历待排序区间，内循环用来遍历已排序区间
  for (int i = 0; i < len; i++)
  {
    int j = i;
    current = arr[i];
    // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项(表示升序)时，将该位置右移
    // 直到遇到小于等于自己的项则停止移动，表示插入成功
    printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
    while (j-- > 0 && current < arr[j])
    {
      // 逐个位移
      arr[j + 1] = arr[j];
    }
    // 交换为当前项
    arr[j + 1] = current;
  }
  return arr;
}

// 标准通用版
int *insertSort2(int arr[], int len)
{
  int j, current;
  for (int i = 0; i < len; i++)
  {
    j = i - 1;
    current = arr[i];
    printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
    while (j >= 0 && current < arr[j])
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = current;
  }
  return arr;
}

// 倒序版
int *insertSort(int arr[], int len)
{
  for (int i = 0; i < len; i++)
  {
    int current = arr[i];
    int j = i - 1;
    printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
    for (; j >= 0; j--)
    {
      // 如果比较项大于已排序项，则逐个右移动
      if (current > arr[j])
        arr[j + 1] = arr[j];
      // 如果遇到不大于该项则跳出，继续下一项对比
      else
        break;
    }
    arr[j + 1] = current;
  }
  return arr;
}

int main()
{
  int arr[7] = {7, 11, 9, 10, 12, 13, 8};
  int len = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  float startTime = clock();
  insertSort(arr, len);
  printf("\nsort end:\n");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  return 0;
}

/**
jarrys-mbp:insertsort jarry$ gcc insert_sort.c
jarrys-mbp:insertsort jarry$ ./a.out 
7 11 9 10 12 13 8 
i=0, j=0, arr[i]=7, arr[j+1]=11
i=1, j=1, arr[i]=11, arr[j+1]=9
i=2, j=2, arr[i]=9, arr[j+1]=10
i=3, j=3, arr[i]=10, arr[j+1]=12
i=4, j=4, arr[i]=12, arr[j+1]=13
i=5, j=5, arr[i]=13, arr[j+1]=8
i=6, j=6, arr[i]=8, arr[j+1]=0
sort end:
7 8 9 10 11 12 13 
time: 0.022000 ms.
 */