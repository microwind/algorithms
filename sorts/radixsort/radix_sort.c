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
void counting_sort(int arr[], int len, int radix)
{
  int output[len];
  int range = 10;
  int count_list[range];
  memset(count_list, 0, range * sizeof(int));
  // 根据数字所在位置进行计数
  for (int i = 0; i < len; i++)
  {
    int item = arr[i];
    int idx = (item / radix) % range;
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
    int idx = (arr[i] / radix) % range;
    output[count_list[idx] - 1] = arr[i];
    count_list[idx]--;
  }

  // 复制输出数组到原始数组
  for (int i = 0; i < len; i++)
  {
    arr[i] = output[i];
  }
}

// 基数排序
int *radix_sort(int arr[], int len)
{
  // 找出最大值
  int max_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
  }

  // 根据最大值，逐个按进位(基数)来应用排序，radix即数位。
  for (int radix = 1; max_value / radix > 0; radix *= 10)
  {
    counting_sort(arr, len, radix);
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

  int arr2[] = {3, 4, 15, 2, 2, 123, 2, 3, 3, 237, 10};
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
 time: 0.016000 ms.
 result1 sorted:{ 2, 24, 45, 66, 75, 90, 170, 802 }

 origin arr2:{ 3, 4, 15, 2, 2, 123, 2, 3, 3, 237, 10 }
 result2 sorted:{ 2, 2, 2, 3, 3, 3, 4, 10, 15, 123, 237 }
 time: 0.005000 ms.%
*/