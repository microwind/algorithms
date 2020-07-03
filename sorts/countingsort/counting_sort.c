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

int count(int arr[], int len, int number) {
  int count = 0;
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == number) 
      count++;
  }
  return count;
}

void printArray(int *arr, int len)
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

// 计数排序，仅支持正整数
void *countingSort1(int arr[], int len)
{
  int max_value = arr[0];
  int min_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
    if (arr[i] < min_value)
      min_value = arr[i];
  }
  // 数组初始值
  int FLAG = -1;
  // 桶的数量为最大值减去最小，这里是为了减少桶的数量，否则可以取最大值
  int size = max_value - min_value + 1;
  int buckets[size];
  int* output = malloc(len * sizeof(int));
  memset(buckets, FLAG, size * sizeof(int));

  for (int i = 0; i < len; i++)
  {
    // 给对应数字的桶增加标记，代表桶序号。把下标减去min值，以便减少计数数组的长度
    int idx = arr[i] - min_value;
    buckets[idx] += 1;
  }

  int output_idx = 0;
  for (int i = 0; i < size; i++)
  {
    while (buckets[i] >= 0)
    {
      // 将每个桶的标记按顺序取出，值要加上min_value还原
      output[output_idx] = i + min_value;
      buckets[i] -= 1;
      output_idx++;
    }
  }
  return output;
}

// 计数排序，注意与桶排序区别
void *countingSort2(int arr[], int len)
{
  int max = arr[0];
  int min = arr[0];
  for (int i = 1; i < len; i++) {
    if (arr[i] > max)
      max = arr[i];
    if (arr[i] < min)
      min = arr[i];
  }

  int real_len = max - min + 1;
  int buckets[real_len];
  for (int i = 0; i < real_len; i++)
    buckets[i] = -1;

  for (int i = 0; i < len; i++)
    buckets[arr[i] - min]++;

  for (int i = 0, j = 0; i < real_len; i++)
    while (buckets[i] >= 0) {
      arr[j++] = i + min;
      buckets[i]--;
    }
  return arr;
}

int main()
{
  int arr[6] = {-1, 7, 11, 9, 2, 56};
  // int arr[12] = {7, 11, 9, 2, 52, 13, 8, 8, 7, 9, 2, 10};
  int len = sizeof(arr) / sizeof(arr[0]);
  // float arr2[11] = {3, 4.3, 15, -2.1, -2, -2.1, 2, 3.2, 3, -7, 10};
  // int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("origin arr:");
  printArray(arr, len);
  printf("\r\ncountingSort1 start");
  float startTime = clock();
  int *result = countingSort1(arr, len);
  printf("\r\nsorted:");
  printArray(result, len);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\ncountingSort1 end\n");

  // int arr2[6] = {-1, 7, 11, 9, 2, 56};
  int arr2[12] = {7, 11, 9, 2, 52, 0, -8, 8, 7, 9, 2, 10};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\ncountingSort2 start");
  startTime = clock();
  int *result2 = countingSort2(arr2, len2);
  printf("\r\nsorted:");
  printArray(result2, len2);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\ncountingSort2 end\n");
}

/*
jarry@192 countingsort % gcc counting_sort.c 
jarry@192 countingsort % ./a.out
origin arr:{ 7, 11, 9, 2, 52, 13, 8, 8, 7, 9, 2, 10 }
countingSort1 start
sorted:{ 2, 2, 7, 7, 8, 8, 9, 9, 10, 11, 13, 52 }
time: 0.032000 ms.
countingSort1 end

countingSort2 start
sorted:{ 2, 2, 7, 7, 8, 8, 9, 9, 10, 11, 13, 52 }
time: 0.006000 ms.
countingSort2 end
*/