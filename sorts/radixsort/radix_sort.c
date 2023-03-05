/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <time.h>
#include <memory.h>

void print_array(int *arr, int len)
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

// 计数排序，根据基数按位进行计数
void counting_sort(int arr[], int len, int exponent)
{
  int sorted_list[len];
  int range = 10;
  int count_list[range];
  // 找出最小值
  int min_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] < min_value)
      min_value = arr[i];
  }
  memset(count_list, 0, range * sizeof(int));
  // 根据数字所在位置进行计数
  for (int i = 0; i < len; i++)
  {
    int item = arr[i] - min_value;
    int idx = (item / exponent) % range;
    count_list[idx]++;
  }

  // 构建计数排序，当前位置加上左侧位置，后面的位数为前面的累加之和
  for (int i = 1; i < range; i++)
  {
    count_list[i] += count_list[i - 1];
  }

  // 构建输出数组，根据计数数组按顺序取得排序内容
  for (int i = len - 1; i >= 0; i--)
  {
    int item = arr[i] - min_value;
    int idx = (item / exponent) % range;
    // 根据位置重排结果，减去min值还原数据
    sorted_list[count_list[idx] - 1] = arr[i];
    count_list[idx]--;
  }

  // 复制到数组重排原始数组
  for (int i = 0; i < len; i++)
  {
    arr[i] = sorted_list[i];
  }
}

// 基数排序，从个位到高位逐个对比排序
int *radix_sort(int arr[], int len)
{
  // 找出最大值
  int max_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
  }
  // 找出最小值
  int min_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] < min_value)
      min_value = arr[i];
  }

  // 根据最大值，逐个按进位(基数)来应用排序，exponent即数位基数，按个十百千递增。
  for (int exponent = 1; (max_value - min_value) / exponent > 0; exponent *= 10)
  {
    counting_sort(arr, len, exponent);
  }

  return arr;
}

// 测试
int main()
{
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("\r\n origin arr1:");
  print_array(arr, len);
  float startTime = clock();
  int *result1 = radix_sort(arr, len);
  printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\r\n result1 sorted:");
  print_array(result1, len);

  int arr2[] = {33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n\r\n origin arr2:");
  print_array(arr2, len2);
  startTime = clock();
  int *result2 = radix_sort(arr2, len2);
  printf("\r\n result2 sorted:");
  print_array(result2, len2);
  printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  return 0;
}

/*
jarry@jarrys-MacBook-Pro radixsort % gcc radix_sort.c
jarry@jarrys-MacBook-Pro radixsort % ./a.out

 origin arr1:{ 170, 45, 75, 90, 802, 24, 2, 66 }
 time: 0.020000 ms.
 result1 sorted:{ 2, 24, 45, 66, 75, 90, 170, 802 }

 origin arr2:{ 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 }
 result2 sorted:{ -323454, -4, 7, 10, 15, 33, 43, 200, 1235, 87431 }
 time: 0.009000 ms.%
*/