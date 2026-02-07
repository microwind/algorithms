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

int find(int *arr, int len, int item)
{
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == item)
      return i;
  }
  return -1;
}

// 自后往前按顺序插入到已排序序列中
void insert(int arr[], int item, int len)
{
  if (len == 0)
  {
    arr[len] = item;
    return;
  }
  while (len-- > 0)
  {
    // printf("\r\n len=%d arr[len]=%d item=%d\r\n", len, arr[len], item);
    if (item < arr[len])
    {
      arr[len + 1] = arr[len];
      if (len == 0)
      {
        arr[len] = item;
      }
    }
    else
    {
      arr[len + 1] = item;
      break;
    }
  }
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

/**
 * 桶标准排序，支持正负整数
 * 记录每个桶实际使用长度
 * 通过插入排序来实现桶内排序
 */
void *bucketSort1(int arr[], int len)
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
  if (max_value < 1)
    max_value = 2;
  if (min_value < 1)
    min_value = 1;

  // 桶的间隔为最大值减去最小再除以最小值
  int bucket_size = (max_value - min_value) / min_value + 1;
  // 一共分为几个桶
  int bucket_number = (max_value - min_value) / bucket_size + 1;

  printf("bucket_size=%d len=%d bucket_number=%d", bucket_size, len, bucket_number);
  // 每个桶申请与原数组一样长空间
  int **buckets = (int **)calloc(bucket_number, sizeof(int *));
  // 记录每个桶内容的实际长度，取出数据时不超过次长度
  int *buckets_real_length = malloc(bucket_number * sizeof(int));
  // 给数组填充一个默认值，初始为0
  memset(buckets_real_length, 0, 1 * sizeof(int));

  for (int i = 0; i < bucket_number; i++)
  {
    // 给每个桶设置长度为数组的长度
    buckets[i] = (int *)malloc(len * sizeof(int));
  }

  for (int i = 0; i < len; i++)
  {
    int item = arr[i];
    // 获得桶的下标，再将数据插入到所分配桶里的相应位置
    int idx = (item - min_value) / bucket_size;
    printf("\r\n i=%d item=%d idx=%d buckets_real_length[idx]=%d", i, item, idx, buckets_real_length[idx]);
    insert(buckets[idx], item, buckets_real_length[idx]);
    buckets_real_length[idx]++;
  }

  for (int i = 0; i < bucket_number; i++)
  {
    printArray(buckets[i], len);
  }

  int *output = malloc(len * sizeof(int));
  int output_idx = 0;
  for (int i = 0; i < bucket_number; i++)
  {
    for (int j = 0; j < buckets_real_length[i]; j++)
    {
      // 根据每个桶实际的长度，将桶内的数据按顺序取出
      output[output_idx] = buckets[i][j];
      output_idx++;
    }
    free(buckets[i]);
  }
  free(buckets);
  return output;
}

/**
 * 桶排序，设置一个标志作为填充，标志位的数会被忽略
 */
void *bucketSort2(int arr[], int len)
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
  if (max_value < 1)
    max_value = 2;
  if (min_value < 1)
    min_value = 1;

  // 设置一个默认值，用来标记替换
  int FLAG = -1;
  // 桶的间隔为最大值减去最小再除以最小值
  int bucket_size = (max_value - min_value) / min_value + 1;
  // 一共分为几个桶
  int bucket_number = (max_value - min_value) / bucket_size + 1;

  printf("bucket_size=%d len=%d bucket_number=%d", bucket_size, len, bucket_number);
  int **buckets = (int **)calloc(bucket_number, sizeof(int *));
  for (int i = 0; i < bucket_number; i++)
  {
    // 给对应数字的桶设置默认值, 这里也可以设置可变数组
    buckets[i] = (int *)malloc(len * sizeof(int));
    // 给桶内设置1个默认标记，这种标记数据将被忽略
    memset(buckets[i], FLAG, len * sizeof(int));
  }

  for (int i = 0; i < len; i++)
  {
    int item = arr[i];
    // 获得桶的下标
    int idx = (item - min_value) / bucket_size;
    int last_idx = find(buckets[idx], len, FLAG);
    printf("\r\n i=%d item=%d idx=%d last_idx=%d", i, item, idx, last_idx);
    insert(buckets[idx], item, last_idx);
  }

  int *output = malloc(len * sizeof(int));
  int output_idx = 0;
  for (int i = 0; i < bucket_number; i++)
  {
    for (int j = 0; j < len; j++)
    {
      // 这里没有按照实际长度来取数据，而是通过过滤标记来取出
      // 因此标记数会被过滤掉，对于不含标记数的数组来说没问题
      if (buckets[i][j] == FLAG)
        break;
      output[output_idx] = buckets[i][j];
      output_idx++;
    }
    free(buckets[i]);
  }
  free(buckets);
  return output;
}

int main()
{
  // int arr[11] = {2, 4, 5, 7, 10, 3, 8, 2, 9, 6, 14};
  int arr[10] = {-20, 0, -1, 5, 30, 30, 15, 13, 80, 30};
  int arr2[12] = {2, 11, -9, 30, -15, 13, -2, 3, 4, 90, 0, 120};
  int arr3[5] = {9, -1, -2, 0, 4};
  // int arr3[7] = { 20, 11, 9, 30, 15, 13, 80 };
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("origin arr:");
  printArray(arr, len);
  printf("\r\nbucketSort1 start\n");
  float startTime = clock();
  int *result = bucketSort1(arr, len);
  printf("\r\nsorted:");
  printArray(result, len);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\nbucketSort1 end\n");

  printf("\r\nbucketSort2 start\n");
  startTime = clock();
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printArray(arr2, len2);
  // int *result2 = bucketSort1(arr2, len2);
  int *result2 = bucketSort2(arr2, len2);
  printf("\r\nsorted:");
  printArray(result2, len2);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\nbucketSort2 end\n");

  printf("\r\nbucketSort1 start\n");
  startTime = clock();
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  printArray(arr3, len3);
  int *result3 = bucketSort1(arr3, len3);
  printf("\r\nsorted:");
  printArray(result3, len3);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\nbucketSort1 end\n");
}

/*
jarry@jarrys-MacBook-Pro bucketsort % gcc bucket_sort.c -o bucket_sort
jarry@jarrys-MacBook-Pro bucketsort % ./bucket_sort
origin arr:{ -20, 0, -1, 5, 30, 30, 15, 13, 80, 30 }
bucketSort1 start
bucket_size=80 len=10 bucket_number=1
 i=0 item=-20 idx=0 buckets_real_length[idx]=0
 i=1 item=0 idx=0 buckets_real_length[idx]=1
 i=2 item=-1 idx=0 buckets_real_length[idx]=2
 i=3 item=5 idx=0 buckets_real_length[idx]=3
 i=4 item=30 idx=0 buckets_real_length[idx]=4
 i=5 item=30 idx=0 buckets_real_length[idx]=5
 i=6 item=15 idx=0 buckets_real_length[idx]=6
 i=7 item=13 idx=0 buckets_real_length[idx]=7
 i=8 item=80 idx=0 buckets_real_length[idx]=8
 i=9 item=30 idx=0 buckets_real_length[idx]=9{ -20, -1, 0, 5, 13, 15, 30, 30, 30, 80 }
sorted:{ -20, -1, 0, 5, 13, 15, 30, 30, 30, 80 }
time: 0.107000 ms.
bucketSort1 end

bucketSort2 start
{ 2, 11, -9, 30, -15, 13, -2, 3, 4, 90, 0, 120 }bucket_size=120 len=12 bucket_number=1
 i=0 item=2 idx=0 last_idx=0
 i=1 item=11 idx=0 last_idx=1
 i=2 item=-9 idx=0 last_idx=2
 i=3 item=30 idx=0 last_idx=3
 i=4 item=-15 idx=0 last_idx=4
 i=5 item=13 idx=0 last_idx=5
 i=6 item=-2 idx=0 last_idx=6
 i=7 item=3 idx=0 last_idx=7
 i=8 item=4 idx=0 last_idx=8
 i=9 item=90 idx=0 last_idx=9
 i=10 item=0 idx=0 last_idx=10
 i=11 item=120 idx=0 last_idx=11
sorted:{ -15, -9, -2, 0, 2, 3, 4, 11, 13, 30, 90, 120 }
time: 0.051000 ms.
bucketSort2 end

bucketSort1 start
{ 9, -1, -2, 0, 4 }bucket_size=9 len=5 bucket_number=1
 i=0 item=9 idx=0 buckets_real_length[idx]=0
 i=1 item=-1 idx=0 buckets_real_length[idx]=1
 i=2 item=-2 idx=0 buckets_real_length[idx]=2
 i=3 item=0 idx=0 buckets_real_length[idx]=3
 i=4 item=4 idx=0 buckets_real_length[idx]=4{ -2, -1, 0, 4, 9 }
sorted:{ -2, -1, 0, 4, 9 }
time: 0.023000 ms.
bucketSort1 end
*/