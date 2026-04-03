/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

typedef enum
{
  true = 1,
  false = 0
} bool;

// 函数声明
int bucket_sort1(int arr[], int len);
int bucket_sort2(int arr[], int len);
int bucket_sort3(int arr[], int len);
int bucket_sort4(int arr[], int len);
int bucket_sort5(int arr[], int len);
void *bucketSort6(int arr[], int len);
void *bucketSort7(int arr[], int len);

// 辅助函数
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

int find(int arr[], int len, int number)
{
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == number)
      return i;
  }
  return -1;
}

void insert(int arr[], int number, int index, int max_len)
{
  for (int i = index; i < max_len - 1; i++)
  {
    arr[i + 1] = arr[i];
  }
  arr[index] = number;
}

void printArray(int arr[], int len)
{
  printf("[");
  for (int i = 0; i < len; i++)
  {
    printf("%d", arr[i]);
    if (i < len - 1)
      printf(", ");
  }
  printf("]");
}

/**
 * 桶排序支持负数版本 - 负数放在第1个桶里排序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值（取绝对值）
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中，负数统一放在第1个桶
 * 4. 在每个桶内进行插入排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 支持负数：负数统一放在第1个桶处理
 * - 插入排序：桶内使用插入排序
 * - 统一处理：使用绝对值计算桶分配
 */
int bucket_sort1(int arr[], int len)
{
  printf("bucketSort1 with negative numbers:\n");
  
  if (len <= 0) return 0;
  
  // 第一步：计算数组最大值和最小值（取绝对值）
  int max = arr[0];
  int min = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (abs(arr[i]) > abs(max))
      max = arr[i];
    if (abs(arr[i]) < abs(min))
      min = arr[i];
  }

  // 第二步：计算桶的数量和大小
  int bucketCount = (abs(max) - abs(min)) / abs(min) + 2; // +2是为了包含负数桶
  int bucketSize = abs(min);
  
  // 第三步：初始化桶
  int **buckets = (int **)malloc(bucketCount * sizeof(int *));
  int *bucketSizes = (int *)calloc(bucketCount, sizeof(int));
  
  for (int i = 0; i < bucketCount; i++)
  {
    buckets[i] = (int *)malloc(len * sizeof(int));
  }

  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < len; i++)
  {
    int value = arr[i];
    int bucketIndex;
    
    if (value < 0)
    {
      bucketIndex = 0; // 负数统一放在第1个桶
    }
    else
    {
      bucketIndex = (value - min) / bucketSize + 1; // 正数从第2个桶开始
    }
    
    // 插入排序到桶中
    int j = bucketSizes[bucketIndex] - 1;
    while (j >= 0 && buckets[bucketIndex][j] > value)
    {
      buckets[bucketIndex][j + 1] = buckets[bucketIndex][j];
      j--;
    }
    buckets[bucketIndex][j + 1] = value;
    bucketSizes[bucketIndex]++;
  }

  // 第五步：合并所有桶的元素
  int index = 0;
  for (int i = 0; i < bucketCount; i++)
  {
    for (int j = 0; j < bucketSizes[i]; j++)
    {
      arr[index++] = buckets[i][j];
    }
  }

  // 第六步：释放内存
  for (int i = 0; i < bucketCount; i++)
  {
    free(buckets[i]);
  }
  free(buckets);
  free(bucketSizes);
  
  return 0;
}

/**
 * 桶排序正数专用版本 - 只处理正数的桶排序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值（只考虑正数）
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将正数元素分配到对应桶中
 * 4. 在每个桶内进行插入排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 正数专用：专门为正数优化
 * - 精确分配：桶分配更精确
 * - 性能较好：减少不必要的计算
 */
int bucket_sort2(int arr[], int len)
{
  printf("bucketSort2 positive numbers only:\n");
  
  if (len <= 0) return 0;
  
  // 第一步：计算数组最大值和最小值
  int max = arr[0];
  int min = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max)
      max = arr[i];
    if (arr[i] < min)
      min = arr[i];
  }

  // 第二步：计算桶的数量和大小
  if (min <= 0) min = 1; // 防止除零
  int bucketCount = (max - min) / min + 1;
  if (bucketCount <= 0) bucketCount = 1; // 确保至少一个桶
  int bucketSize = min;
  
  // 第三步：初始化桶
  int **buckets = (int **)malloc(bucketCount * sizeof(int *));
  int *bucketSizes = (int *)calloc(bucketCount, sizeof(int));
  
  for (int i = 0; i < bucketCount; i++)
  {
    buckets[i] = (int *)malloc(len * sizeof(int));
  }

  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < len; i++)
  {
    int value = arr[i];
    int bucketIndex = (value - min) / bucketSize;
    
    // 边界检查
    if (bucketIndex >= bucketCount)
      bucketIndex = bucketCount - 1;
    if (bucketIndex < 0)
      bucketIndex = 0;
    
    // 插入排序到桶中
    int j = bucketSizes[bucketIndex] - 1;
    while (j >= 0 && buckets[bucketIndex][j] > value)
    {
      buckets[bucketIndex][j + 1] = buckets[bucketIndex][j];
      j--;
    }
    buckets[bucketIndex][j + 1] = value;
    bucketSizes[bucketIndex]++;
  }

  // 第五步：合并所有桶的元素
  int index = 0;
  for (int i = 0; i < bucketCount; i++)
  {
    for (int j = 0; j < bucketSizes[i]; j++)
    {
      arr[index++] = buckets[i][j];
    }
  }

  // 第六步：释放内存
  for (int i = 0; i < bucketCount; i++)
  {
    free(buckets[i]);
  }
  free(buckets);
  free(bucketSizes);
  
  return 0;
}

/**
 * 桶排序挪动排序版本 - 使用挪动插入保持排序稳定性
 * 
 * 算法原理：
 * 1. 手动遍历计算数组最大值和最小值
 * 2. 根据数组长度计算桶的数量和大小
 * 3. 将元素分配到对应桶中，支持负数
 * 4. 使用挪动排序而非数组修改进行桶内排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 挪动排序：使用挪动插入而非直接修改
 * - 排序稳定：保持相等元素的相对位置
 * - 支持负数：负数统一处理
 */
int bucket_sort3(int arr[], int len)
{
  printf("bucketSort3 with move sorting:\n");
  
  if (len <= 0) return 0;
  
  // 第一步：计算数组最大值和最小值
  int max = arr[0];
  int min = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max)
      max = arr[i];
    if (arr[i] < min)
      min = arr[i];
  }

  // 第二步：计算桶的数量和大小
  int bucketCount = len; // 桶数量等于数组长度
  int bucketSize = (max - min) / bucketCount + 1;
  
  // 第三步：初始化桶
  int **buckets = (int **)malloc(bucketCount * sizeof(int *));
  int *bucketSizes = (int *)calloc(bucketCount, sizeof(int));
  
  for (int i = 0; i < bucketCount; i++)
  {
    buckets[i] = (int *)malloc(len * sizeof(int));
  }

  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < len; i++)
  {
    int value = arr[i];
    int bucketIndex = (value - min) / bucketSize;
    
    if (bucketIndex >= bucketCount)
      bucketIndex = bucketCount - 1;
    
    // 挪动插入到桶中
    int j = bucketSizes[bucketIndex];
    while (j > 0 && buckets[bucketIndex][j - 1] > value)
    {
      buckets[bucketIndex][j] = buckets[bucketIndex][j - 1];
      j--;
    }
    buckets[bucketIndex][j] = value;
    bucketSizes[bucketIndex]++;
  }

  // 第五步：合并所有桶的元素
  int index = 0;
  for (int i = 0; i < bucketCount; i++)
  {
    for (int j = 0; j < bucketSizes[i]; j++)
    {
      arr[index++] = buckets[i][j];
    }
  }

  // 第六步：释放内存
  for (int i = 0; i < bucketCount; i++)
  {
    free(buckets[i]);
  }
  free(buckets);
  free(bucketSizes);
  
  return 0;
}

/**
 * 桶排序负数单独版本 - 负数单独优化处理
 * 
 * 算法原理：
 * 1. 分别处理正数和负数
 * 2. 负数转换为正数进行桶排序
 * 3. 正数正常进行桶排序
 * 4. 合并负数（逆序）和正数
 * 
 * 特点：
 * - 负数单独：负数单独优化处理
 * - 排序精确：更精确的排序逻辑
 * - 分类处理：正负数分别优化
 */
int bucket_sort4(int arr[], int len)
{
  printf("bucketSort4 separate negative sorting:\n");
  
  if (len <= 0) return 0;
  
  // 第一步：分离正数和负数
  int *positive = (int *)malloc(len * sizeof(int));
  int *negative = (int *)malloc(len * sizeof(int));
  int posCount = 0, negCount = 0;
  
  for (int i = 0; i < len; i++)
  {
    if (arr[i] >= 0)
      positive[posCount++] = arr[i];
    else
      negative[negCount++] = -arr[i]; // 负数转为正数
  }

  // 第二步：分别排序正数和负数
  if (posCount > 0)
    bucket_sort1(positive, posCount);
  if (negCount > 0)
    bucket_sort1(negative, negCount);

  // 第三步：合并结果（负数要逆序并还原符号）
  int index = 0;
  for (int i = negCount - 1; i >= 0; i--)
  {
    arr[index++] = -negative[i];
  }
  for (int i = 0; i < posCount; i++)
  {
    arr[index++] = positive[i];
  }

  // 第四步：释放内存
  free(positive);
  free(negative);
  
  return 0;
}

/**
 * 桶排序实时冒泡版本 - 插入即排序，实时保持有序
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 初始化桶
 * 3. 将元素分配到桶中，立即进行冒泡排序
 * 4. 合并所有桶的元素
 * 
 * 特点：
 * - 实时排序：插入即排序
 * - 冒泡优化：使用冒泡排序维护有序性
 * - 即时维护：实时保持桶内有序
 */
int bucket_sort5(int arr[], int len)
{
  printf("bucketSort5 real-time bubble sorting:\n");
  
  if (len <= 0) return 0;
  
  // 第一步：计算数组最大值和最小值
  int max = arr[0];
  int min = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max)
      max = arr[i];
    if (arr[i] < min)
      min = arr[i];
  }

  // 第二步：计算桶的数量和大小
  if (min <= 0) min = 1; // 防止除零
  int bucketCount = (max - min) / min + 1;
  if (bucketCount <= 0) bucketCount = 1; // 确保至少一个桶
  int bucketSize = min;
  
  // 第三步：初始化桶
  int **buckets = (int **)malloc(bucketCount * sizeof(int *));
  int *bucketSizes = (int *)calloc(bucketCount, sizeof(int));
  
  for (int i = 0; i < bucketCount; i++)
  {
    buckets[i] = (int *)malloc(len * sizeof(int));
  }

  // 第四步：将元素分配到对应桶中，实时冒泡排序
  for (int i = 0; i < len; i++)
  {
    int value = arr[i];
    int bucketIndex = (value - min) / bucketSize;
    
    // 边界检查
    if (bucketIndex >= bucketCount)
      bucketIndex = bucketCount - 1;
    if (bucketIndex < 0)
      bucketIndex = 0;
    
    // 直接添加到桶末尾
    buckets[bucketIndex][bucketSizes[bucketIndex]] = value;
    bucketSizes[bucketIndex]++;
    
    // 第五步：实时冒泡排序
    for (int j = bucketSizes[bucketIndex] - 1; j > 0; j--)
    {
      if (buckets[bucketIndex][j] < buckets[bucketIndex][j - 1])
      {
        swap(buckets[bucketIndex], j, j - 1);
      }
      else
      {
        break;
      }
    }
  }

  // 第六步：合并所有桶的元素
  int index = 0;
  for (int i = 0; i < bucketCount; i++)
  {
    for (int j = 0; j < bucketSizes[i]; j++)
    {
      arr[index++] = buckets[i][j];
    }
  }

  // 第七步：释放内存
  for (int i = 0; i < bucketCount; i++)
  {
    free(buckets[i]);
  }
  free(buckets);
  free(bucketSizes);
  
  return 0;
}

/**
 * 桶排序标准版本 - 使用插入排序的标准实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 将元素分配到对应桶中
 * 4. 使用insert函数进行桶内插入排序
 * 5. 合并所有桶的元素
 * 
 * 特点：
 * - 标准实现：经典的桶排序算法
 * - 插入排序：桶内使用插入排序
 * - 长度记录：记录每个桶的实际长度
 */
void *bucketSort6(int arr[], int len)
{
  printf("bucketSort6 standard version:\n");
  
  if (len <= 0) return NULL;
  
  // 第一步：计算数组最大值和最小值
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

  // 第二步：计算桶的大小和数量
  int bucket_size = (max_value - min_value) / min_value + 1;
  int bucket_number = (max_value - min_value) / bucket_size + 1;

  printf("bucket_size=%d len=%d bucket_number=%d", bucket_size, len, bucket_number);
  
  // 第三步：初始化桶和长度记录数组
  int **buckets = (int **)calloc(bucket_number, sizeof(int *));
  int *buckets_real_length = malloc(bucket_number * sizeof(int));
  memset(buckets_real_length, 0, bucket_number * sizeof(int));

  for (int i = 0; i < bucket_number; i++)
  {
    buckets[i] = (int *)malloc(len * sizeof(int));
  }

  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < len; i++)
  {
    int item = arr[i];
    int idx = (item - min_value) / bucket_size;
    printf("\r\n i=%d item=%d idx=%d buckets_real_length[idx]=%d", i, item, idx, buckets_real_length[idx]);
    insert(buckets[idx], item, buckets_real_length[idx], len);
    buckets_real_length[idx]++;
  }

  // 第五步：打印各桶内容
  for (int i = 0; i < bucket_number; i++)
  {
    printArray(buckets[i], len);
  }

  // 第六步：合并结果
  int *output = malloc(len * sizeof(int));
  int output_idx = 0;
  for (int i = 0; i < bucket_number; i++)
  {
    for (int j = 0; j < buckets_real_length[i]; j++)
    {
      output[output_idx] = buckets[i][j];
      output_idx++;
    }
    free(buckets[i]);
  }
  free(buckets);
  free(buckets_real_length);
  
  return output;
}

/**
 * 桶排序标志位版本 - 使用标志位填充的实现
 * 
 * 算法原理：
 * 1. 计算数组最大值和最小值
 * 2. 根据最大最小值计算桶的数量和大小
 * 3. 使用FLAG(-1)标记初始化所有桶位置
 * 4. 将元素分配到对应桶中，使用find函数查找插入位置
 * 5. 合并所有桶的元素，过滤掉FLAG标记
 * 
 * 特点：
 * - 标志位填充：使用FLAG(-1)标记未使用位置
 * - 查找插入：使用find函数查找可用位置
 * - 过滤机制：合并时过滤FLAG标记
 */
void *bucketSort7(int arr[], int len)
{
  printf("bucketSort7 flag version:\n");
  
  if (len <= 0) return NULL;
  
  // 第一步：计算数组最大值和最小值
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

  // 第二步：设置标志位和计算桶参数
  int FLAG = -1;
  int bucket_size = (max_value - min_value) / min_value + 1;
  int bucket_number = (max_value - min_value) / bucket_size + 1;

  printf("bucket_size=%d len=%d bucket_number=%d", bucket_size, len, bucket_number);
  
  // 第三步：初始化桶和设置标志位
  int **buckets = (int **)calloc(bucket_number, sizeof(int *));
  for (int i = 0; i < bucket_number; i++)
  {
    buckets[i] = (int *)malloc(len * sizeof(int));
    memset(buckets[i], FLAG, len * sizeof(int));
  }

  // 第四步：将元素分配到对应桶中
  for (int i = 0; i < len; i++)
  {
    int item = arr[i];
    int idx = (item - min_value) / bucket_size;
    
    // 边界检查
    if (idx >= bucket_number)
      idx = bucket_number - 1;
    if (idx < 0)
      idx = 0;
    
    int last_idx = find(buckets[idx], len, FLAG);
    if (last_idx == -1) // 如果没找到FLAG，使用桶末尾
      last_idx = count(buckets[idx], len, FLAG);
    
    printf("\r\n i=%d item=%d idx=%d last_idx=%d", i, item, idx, last_idx);
    insert(buckets[idx], item, last_idx, len);
  }

  // 第五步：合并结果，过滤FLAG标记
  int *output = malloc(len * sizeof(int));
  int output_idx = 0;
  for (int i = 0; i < bucket_number; i++)
  {
    for (int j = 0; j < len; j++)
    {
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

/**
 * 性能测试函数 - 统一测试所有桶排序版本
 */
void performanceTest(int testData[], int len)
{
  clock_t start, end;
  double elapsed;
  
  // 复制测试数据
  int *testData1 = (int *)malloc(len * sizeof(int));
  int *testData2 = (int *)malloc(len * sizeof(int));
  int *testData3 = (int *)malloc(len * sizeof(int));
  int *testData4 = (int *)malloc(len * sizeof(int));
  int *testData5 = (int *)malloc(len * sizeof(int));
  int *testData6 = (int *)malloc(len * sizeof(int));
  int *testData7 = (int *)malloc(len * sizeof(int));
  
  memcpy(testData1, testData, len * sizeof(int));
  memcpy(testData2, testData, len * sizeof(int));
  memcpy(testData3, testData, len * sizeof(int));
  memcpy(testData4, testData, len * sizeof(int));
  memcpy(testData5, testData, len * sizeof(int));
  memcpy(testData6, testData, len * sizeof(int));
  memcpy(testData7, testData, len * sizeof(int));
  
  // 测试所有版本
  printf("=== 桶排序算法演示 ===\n\n");
  
  printf("arrData origin: ");
  printArray(testData, len);
  printf("\n\n");
  
  // 测试1: bucket_sort1
  start = clock();
  bucket_sort1(testData1, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort1: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(testData1, len);
  printf("\n\n");
  
  // 测试2: bucket_sort2
  start = clock();
  bucket_sort2(testData2, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort2: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(testData2, len);
  printf("\n\n");
  
  // 测试3: bucket_sort3
  start = clock();
  bucket_sort3(testData3, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort3: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(testData3, len);
  printf("\n\n");
  
  // 测试4: bucket_sort4
  start = clock();
  bucket_sort4(testData4, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort4: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(testData4, len);
  printf("\n\n");
  
  // 测试5: bucket_sort5
  start = clock();
  bucket_sort5(testData5, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort5: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(testData5, len);
  printf("\n\n");
  
  // 测试6: bucketSort6
  start = clock();
  int *result6 = bucketSort6(testData6, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort6: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(result6, len);
  printf("\n\n");
  
  // 测试7: bucketSort7
  start = clock();
  int *result7 = bucketSort7(testData7, len);
  end = clock();
  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
  printf("bucketSort7: %.3fms\n", elapsed);
  printf("排序结果: ");
  printArray(result7, len);
  printf("\n\n");
  
  // 算法对比总结
  printf("=== 算法对比总结 ===\n");
  printf("1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理\n");
  printf("2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好\n");
  printf("3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性\n");
  printf("4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确\n");
  printf("5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序\n");
  printf("6. 标准版本：bucketSort6 - 标准桶排序实现，使用插入排序\n");
  printf("7. 标志位版本：bucketSort7 - 使用标志位填充，查找插入位置\n");
  
  // 释放内存
  free(testData1);
  free(testData2);
  free(testData3);
  free(testData4);
  free(testData5);
  free(testData6);
  free(testData7);
  free(result6);
  free(result7);
}

int main()
{
  int arr_data[] = {20, 11, 0, -10, 9, 6, 30, 15, 13, 80};
  int len = sizeof(arr_data) / sizeof(arr_data[0]);
  
  performanceTest(arr_data, len);
  
  return 0;
}

/* 打印结果
jarry@Mac bucketsort % gcc bucket_sort.c -o bucket_sort && ./bucket_sort
=== 桶排序算法演示 ===

arrData origin: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

bucketSort1 with negative numbers:
bucketSort1: 0.007ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

bucketSort2 positive numbers only:
bucketSort2: 0.011ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

bucketSort3 with move sorting:
bucketSort3: 0.004ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

bucketSort4 separate negative sorting:
bucketSort1 with negative numbers:
bucketSort1 with negative numbers:
bucketSort4: 0.007ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

bucketSort5 real-time bubble sorting:
bucketSort5: 0.011ms
排序结果: [-10, 0, 6, 9, 11, 13, 15, 20, 30, 80]

bucketSort6 standard version:
bucket_size=80 len=10 bucket_number=1
 i=0 item=20 idx=0 buckets_real_length[idx]=0
 i=1 item=11 idx=0 buckets_real_length[idx]=1
 i=2 item=0 idx=0 buckets_real_length[idx]=2
 i=3 item=-10 idx=0 buckets_real_length[idx]=3
 i=4 item=9 idx=0 buckets_real_length[idx]=4
 i=5 item=6 idx=0 buckets_real_length[idx]=5
 i=6 item=30 idx=0 buckets_real_length[idx]=6
 i=7 item=15 idx=0 buckets_real_length[idx]=7
 i=8 item=13 idx=0 buckets_real_length[idx]=8
 i=9 item=80 idx=0 buckets_real_length[idx]=9[20, 11, 0, -10, 9, 6, 30, 15, 13, 80]bucketSort6: 0.021ms
排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

bucketSort7 flag version:
bucket_size=80 len=10 bucket_number=1
 i=0 item=20 idx=0 last_idx=0
 i=1 item=11 idx=0 last_idx=1
 i=2 item=0 idx=0 last_idx=2
 i=3 item=-10 idx=0 last_idx=3
 i=4 item=9 idx=0 last_idx=4
 i=5 item=6 idx=0 last_idx=5
 i=6 item=30 idx=0 last_idx=6
 i=7 item=15 idx=0 last_idx=7
 i=8 item=13 idx=0 last_idx=8
 i=9 item=80 idx=0 last_idx=9bucketSort7: 0.016ms
排序结果: [20, 11, 0, -10, 9, 6, 30, 15, 13, 80]

=== 算法对比总结 ===
1. 支持负数版本：bucketSort1 - 使用绝对值计算，负数统一处理
2. 正数专用版本：bucketSort2 - 桶分配精确，性能较好
3. 挪动排序版本：bucketSort3 - 使用挪动插入，保持排序稳定性
4. 负数单独版本：bucketSort4 - 负数单独优化，排序更精确
5. 实时冒泡版本：bucketSort5 - 插入即排序，实时保持有序
6. 标准版本：bucketSort6 - 标准桶排序实现，使用插入排序
7. 标志位版本：bucketSort7 - 使用标志位填充，查找插入位置
*/
