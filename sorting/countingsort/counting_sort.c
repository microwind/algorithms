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

// 计数排序，支持正负整数
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
  // 数组的数量为最大值减去最小，这是为了减少数量，否则可以取最大值
  int size = max_value - min_value + 1;
  int buckets[size];
  int *output = malloc(len * sizeof(int));
  memset(buckets, FLAG, size * sizeof(int));

  for (int i = 0; i < len; i++)
  {
    // 给对应数字的桶增加标记，代表序号。把下标减去min值，以便减少计数数组的长度
    int idx = arr[i] - min_value;
    buckets[idx] += 1;
  }

  int output_idx = 0;
  for (int i = 0; i < size; i++)
  {
    while (buckets[i] >= 0)
    {
      // 将每个数组的标记按顺序取出，值要加上min_value还原
      output[output_idx] = i + min_value;
      buckets[i] -= 1;
      output_idx++;
    }
  }
  return output;
}

// 计数排序标准版，注意与桶排序区别
int *countingSort2(int arr[], int len)
{
  int max = arr[0];
  int min = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max)
      max = arr[i];
    if (arr[i] < min)
      min = arr[i];
  }

  int real_len = max - min + 1;
  int count_list[real_len];
  for (int i = 0; i < real_len; i++)
    count_list[i] = 0;

  for (int i = 0; i < len; i++)
    count_list[arr[i] - min]++;

  // 输出方式1. 遍历计数数组输出
  // for (int i = 0, j = 0; i < real_len; i++)
  //   while (count_list[i] > 0) {
  //     arr[j++] = i + min;
  //     count_list[i]--;
  //   }
  // return arr;

  // 输出方式2. 把上一项的值个数存入到当前项，还原位置取出
  for (int i = 1; i < real_len; i++)
  {
    count_list[i] += count_list[i - 1];
  }
  int *output = malloc(len * sizeof(int));
  // 按位置还原数据，下一个索引记录了上一个的坐标值
  for (int i = 0; i < len; i++)
  {
    // 当前项来自原始数组减去-min
    int item = arr[i] - min;
    // 根据当前项从计数数组里找到目标位置
    int idx = count_list[item] - 1;
    // 输出数据加上min进行还原
    output[idx] = item + min;
    // 取出一项计数则减少一个
    count_list[item] -= 1;

    printf("\r\n [item=%d, idx=%d, count_list[idx]=%d, output[idx]=%d", item, idx, count_list[idx], output[idx]);
  }

  return output;
}

int main()
{
  int arr[6] = {-2, 7, 11, 9, 2, 56};
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
  // int arr2[5] = {2, 1, 5, 3, 2};
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
origin arr:{ -2, 7, 11, 9, 2, 56 }
countingSort1 start
sorted:{ -2, 2, 7, 9, 11, 56 }
time: 0.045000 ms.
countingSort1 end

countingSort2 start
 [item=15, idx=5, count_list[idx]=1, output[idx]=7
 [item=19, idx=10, count_list[idx]=4, output[idx]=11
 [item=17, idx=8, count_list[idx]=2, output[idx]=9
 [item=10, idx=3, count_list[idx]=1, output[idx]=2
 [item=60, idx=11, count_list[idx]=4, output[idx]=52
 [item=8, idx=1, count_list[idx]=1, output[idx]=0
 [item=0, idx=0, count_list[idx]=0, output[idx]=-8
 [item=16, idx=6, count_list[idx]=1, output[idx]=8
 [item=15, idx=4, count_list[idx]=1, output[idx]=7
 [item=17, idx=7, count_list[idx]=1, output[idx]=9
 [item=10, idx=2, count_list[idx]=1, output[idx]=2
 [item=18, idx=9, count_list[idx]=2, output[idx]=10
sorted:{ -8, 0, 2, 2, 7, 7, 8, 9, 9, 10, 11, 52 }
time: 0.037000 ms.
countingSort2 end
*/