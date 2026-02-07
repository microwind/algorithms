/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

// 选择排序优化版，同时找出最小和最大值进行交换，可减少1半遍历
// 把数列分为前中后三个区间，分别代表最小已排序、中间待排序以及最大已排序区间
// 遍历中间待排序同时找最大和最小值，分别交换到最小值区间和最大值区间
void *selection_sort(int arr[], int len)
{
  int min_value, max_value, min_idx, max_idx;
  int min_list_idx, max_list_idx;
  for (int i = 0; i < len - 1; i++)
  {
    // 待排序里面初始最小值和下标
    min_idx = i;
    min_value = arr[min_idx];
    // 待排序里面初始最大值和下标
    max_idx = i;
    max_value = arr[max_idx];
    // 最小和最大序列里最新待交换的下标
    // 最小序列的下标从0开始，自前往后递加
    min_list_idx = min_idx;
    // 最大序列的下标从数组最后1位开始，自后往前递减
    max_list_idx = len - 1 - i;
    // 如果最小和最大下标相同，说明只剩下1个数字，则终止循环
    if (min_list_idx == max_list_idx)
    {
      break;
    }

    // 逐一遍历待排序区间，找出最小和最大值
    // 待排序区间在最小值序列和和最大值序列之间
    // 待比较区间的下标j从i+1开始，到最大已排序前结束
    for (int j = i + 1; j < len - i; j++)
    {
      // 从待排序列表中分别找到最小值和最大值
      if (arr[j] < min_value)
      {
        min_idx = j;
        min_value = arr[min_idx];
      }
      else if (arr[j] > max_value)
      {
        max_idx = j;
        max_value = arr[max_idx];
      }
    }

    // 如果最小值等于最小序列待交换的值，且最大值等于最大序列里待交换的值，则跳过
    if (arr[min_idx] == arr[min_list_idx] && arr[max_idx] == arr[max_list_idx])
    {
      continue;
    }

    printf("\r\nmin_value=%d max_value=%d min_idx=%d max_idx=%d min_list_idx=%d max_list_idx=%d",
           min_value, max_value, min_idx, max_idx, min_list_idx, max_list_idx);

    // 先交换小值，再交换大值
    arr[min_idx] = arr[min_list_idx];
    arr[min_list_idx] = min_value;
    // 如果最大值被交换了，则需要更新最大值的下标
    if (arr[min_idx] == max_value)
    {
      max_idx = min_idx;
    }
    arr[max_idx] = arr[max_list_idx];
    arr[max_list_idx] = max_value;
  }
  return arr;
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
  printf("\r\n arr1 start\r\n");
  int len1 = sizeof(arr1) / sizeof(arr1[0]);
  printf("\r\n arr1 origin:");
  print_array(arr1, len1);
  float time1 = clock();
  int *new_arr1 = selection_sort(arr1, len1);
  printf("\r\n arr1 sorted:");
  print_array(new_arr1, len1);
  printf("\ntime: %f ms.", ((clock() - time1) / CLOCKS_PER_SEC * 1000));
  printf("\n arr1 end\n");

  int arr2[13] = {7, 11, 121, -9, 545, 110, -210, 1245, -132, 192, 153, 19, 8};
  printf("\r\n arr2 start\r\n");
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n arr2 origin:");
  print_array(arr2, len2);
  float time2 = clock();
  int *new_arr2 = selection_sort(arr2, len2);
  printf("\r\n arr2 sorted:");
  print_array(new_arr2, len2);
  printf("\ntime: %f ms.", ((clock() - time2) / CLOCKS_PER_SEC * 1000));
  printf("\n arr2 end\n");

  int arr3[] = {57, 311, 131, -9, 415, 10, 1330, 1245, -12, 1942, 123, 129, 80};
  printf("\r\n selection_sort start\r\n");
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  printf("\r\n arr3 origin:");
  print_array(arr3, len3);
  float time3 = clock();
  int *new_arr3 = selection_sort(arr3, len3);
  printf("\r\n arr3 sorted:");
  print_array(new_arr3, len3);
  printf("\ntime: %f ms.", ((clock() - time3) / CLOCKS_PER_SEC * 1000));
  printf("\n arr3 end\n");
}
/**
jarry@jarrys-MacBook-Pro selectionsort % gcc selection_sort2.c
jarry@jarrys-MacBook-Pro selectionsort % ./a.out              

 arr1 start

 arr1 origin:
{ 7, 11, -9, 10, -12, 13, 8 }
min_value=-12 max_value=13 min_idx=4 max_idx=5 min_list_idx=0 max_list_idx=6
min_value=-9 max_value=11 min_idx=2 max_idx=1 min_list_idx=1 max_list_idx=5
min_value=7 max_value=10 min_idx=4 max_idx=3 min_list_idx=2 max_list_idx=4
 arr1 sorted:
{ -12, -9, 7, 8, 10, 11, 13 }
time: 0.017000 ms.
 arr1 end

 arr2 start

 arr2 origin:
{ 7, 11, 121, -9, 545, 110, -210, 1245, -132, 192, 153, 19, 8 }
min_value=-210 max_value=1245 min_idx=6 max_idx=7 min_list_idx=0 max_list_idx=12
min_value=-132 max_value=545 min_idx=8 max_idx=4 min_list_idx=1 max_list_idx=11
min_value=-9 max_value=192 min_idx=3 max_idx=9 min_list_idx=2 max_list_idx=10
min_value=7 max_value=153 min_idx=6 max_idx=9 min_list_idx=3 max_list_idx=9
min_value=8 max_value=121 min_idx=7 max_idx=6 min_list_idx=4 max_list_idx=8
min_value=11 max_value=110 min_idx=6 max_idx=5 min_list_idx=5 max_list_idx=7
 arr2 sorted:
{ -210, -132, -9, 7, 8, 11, 19, 110, 121, 153, 192, 545, 1245 }
time: 0.025000 ms.
 arr2 end

 selection_sort start

 arr3 origin:
{ 57, 311, 131, -9, 415, 10, 1330, 1245, -12, 1942, 123, 129, 80 }
min_value=-12 max_value=1942 min_idx=8 max_idx=9 min_list_idx=0 max_list_idx=12
min_value=-9 max_value=1330 min_idx=3 max_idx=6 min_list_idx=1 max_list_idx=11
min_value=10 max_value=1245 min_idx=5 max_idx=7 min_list_idx=2 max_list_idx=10
min_value=57 max_value=415 min_idx=8 max_idx=4 min_list_idx=3 max_list_idx=9
min_value=123 max_value=131 min_idx=7 max_idx=5 min_list_idx=5 max_list_idx=7
 arr3 sorted:
{ -12, -9, 10, 57, 80, 123, 129, 131, 311, 415, 1245, 1330, 1942 }
time: 0.035000 ms.
 arr3 end
 */