/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <memory.h>

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

// 根据最大长度来获取数字第n位的值，从前往后开始，前面不足最大长度时补零
int get_digit_by_position(int num, int position, int max_length)
{
  if (num == 0)
  {
    return 0;
  }
  int number_length = (int)log10(num) + 1;
  // 查询的位置加上自身长度不足最大长度则返回0
  if ((position + number_length) < max_length)
  {
    return 0;
  }
  int exponent = (int)pow(10, number_length - position);
  int digit = 0;
  if (exponent > 0)
  {
    digit = (num / exponent) % 10;
  }
  printf("\r\nnum=%d position=%d max_length=%d number_length=%d exponent=%d position=%d digit=%d.", num, position, max_length, number_length, exponent, position, digit);
  return digit;
}

// 基数排序，从高位到逐个对比排序，通过桶排序递归调用
// arr是数组，len是当前数组长度，position为自前往后的位置，max_length是最大值的数位
int *bucket_sort(int arr[], int len, int position, int max_length)
{
  printf("\r\nlen=%d position=%d max_length=%d ", len, position, max_length);

  if (len <= 1 || position > max_length)
  {
    return arr;
  }

  // 找出最小值
  int min_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] < min_value)
      min_value = arr[i];
  }

  int range = 10;
  // 桶一共从0-9十个数字
  int buckets[range][len];
  for (int i = 0; i < range; i++)
  {
    // 此处未提前使用，也可以不设置默认值
    memset(buckets[i], 0, len * sizeof(int));
    // print_array(buckets[i], len);
  }

  // 默认填充内容为0
  int bucket_count_list[range];
  memset(bucket_count_list, 0, range * sizeof(int));

  for (int i = 0; i < len; i++)
  {
    int item = arr[i] - min_value;
    // 根据数位上的值，减去最小值，分配到对应的桶里
    int bucket_idx = get_digit_by_position(item, position, max_length);
    // 把数据按下标插入到桶里
    int number_idx = bucket_count_list[bucket_idx];
    printf("\r\narr[%d]=%d item=%d bucket_idx=%d number_idx=%d", i, arr[i], item, bucket_idx, number_idx);
    buckets[bucket_idx][number_idx] = arr[i];
    bucket_count_list[bucket_idx] += 1;
  }

  // 将每个桶的数据按顺序逐个取出，重新赋值给原数组
  int sorted_idx = 0;

  for (int i = 0; i < range; i++)
  {
    int *bucket = buckets[i];
    int bucket_len = bucket_count_list[i];
    int bucket_size = sizeof(*bucket) / sizeof(bucket[0]);
    // 如果只有一个值，则直接更新到原数组
    if (bucket_count_list[i] == 1)
    {
      arr[sorted_idx] = bucket[0];
      sorted_idx += 1;
    }
    else if (bucket_size > 0 && bucket_len > 0)
    {
      // 如果是数组且记录追加大于1则继续递归调用，位置增加1位
      // 递归调用传参时需要传入当前子序列、子序列长度、当前分解的位数基数
      int *sorted_bucket = bucket_sort(bucket, bucket_len, position + 1, max_length);
      // 依照已排序的子序列实际长度，把各个桶里的值按顺序赋给原数组
      for (int j = 0; j < bucket_len; j++)
      {
        int num = sorted_bucket[j];
        arr[sorted_idx] = num;
        sorted_idx += 1;
      }
    }
  }
  printf("\r\n position:%d", position);
  print_array(arr, len);
  return arr;
}

// 计数排序，根据数字的位置逐个对比排序，从高到低MSD，递归方式
int *radix_sort_msd(int arr[], int len)
{
  // 找出最大值
  int max_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
  }
  // 获取最小项
  int min_value = arr[0];
  for (int i = 0; i < len; i++)
  {
    if (min_value > arr[i])
    {
      min_value = arr[i];
    }
  }
  // 获取数字一共有几位，减去min得到最大值，以支持负数和减少最大值
  int max_length = (int)(log10(max_value - min_value) + 1);
  // 根据数组最大值的长度，从前往后逐个对比排序。
  return bucket_sort(arr, len, 1, max_length);
}

// 测试
int main()
{
  int arr[] = {195, 272, 276, 2343, 196, 89, 275};
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("\r\n origin arr1:");
  print_array(arr, len);
  float startTime = clock();
  int *result1 = radix_sort_msd(arr, len);
  printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\r\n result1 sorted:");
  print_array(result1, len);

  int arr2[] = {33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n\r\n origin arr2:");
  print_array(arr2, len2);
  startTime = clock();
  int *result2 = radix_sort_msd(arr2, len2);
  printf("\r\n result2 sorted:");
  print_array(result2, len2);
  printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  return 0;
}

/*
jarry@jarrys-MacBook-Pro radixsort % gcc radix_sort_msd.c
jarry@jarrys-MacBook-Pro radixsort % ./a.out

 origin arr1:
{ 195, 272, 276, 2343, 196, 89, 275 }
len=7 position=1 max_length=4
num=106 position=1 max_length=4 number_length=3 exponent=100 position=1 digit=1.
arr[0]=195 item=106 bucket_idx=1 number_idx=0
num=183 position=1 max_length=4 number_length=3 exponent=100 position=1 digit=1.
arr[1]=272 item=183 bucket_idx=1 number_idx=1
num=187 position=1 max_length=4 number_length=3 exponent=100 position=1 digit=1.
arr[2]=276 item=187 bucket_idx=1 number_idx=2
num=2254 position=1 max_length=4 number_length=4 exponent=1000 position=1 digit=2.
arr[3]=2343 item=2254 bucket_idx=2 number_idx=0
num=107 position=1 max_length=4 number_length=3 exponent=100 position=1 digit=1.
arr[4]=196 item=107 bucket_idx=1 number_idx=3
arr[5]=89 item=0 bucket_idx=0 number_idx=0
num=186 position=1 max_length=4 number_length=3 exponent=100 position=1 digit=1.
arr[6]=275 item=186 bucket_idx=1 number_idx=4
len=5 position=2 max_length=4
arr[0]=195 item=0 bucket_idx=0 number_idx=0
num=77 position=2 max_length=4 number_length=2 exponent=1 position=2 digit=7.
arr[1]=272 item=77 bucket_idx=7 number_idx=0
num=81 position=2 max_length=4 number_length=2 exponent=1 position=2 digit=1.
arr[2]=276 item=81 bucket_idx=1 number_idx=0
arr[3]=196 item=1 bucket_idx=0 number_idx=1
num=80 position=2 max_length=4 number_length=2 exponent=1 position=2 digit=0.
arr[4]=275 item=80 bucket_idx=0 number_idx=2
len=3 position=3 max_length=4
arr[0]=195 item=0 bucket_idx=0 number_idx=0
num=1 position=3 max_length=4 number_length=1 exponent=0 position=3 digit=0.
arr[1]=196 item=1 bucket_idx=0 number_idx=1
num=80 position=3 max_length=4 number_length=2 exponent=0 position=3 digit=0.
arr[2]=275 item=80 bucket_idx=0 number_idx=2
len=3 position=4 max_length=4
arr[0]=195 item=0 bucket_idx=0 number_idx=0
num=1 position=4 max_length=4 number_length=1 exponent=0 position=4 digit=0.
arr[1]=196 item=1 bucket_idx=0 number_idx=1
num=80 position=4 max_length=4 number_length=2 exponent=0 position=4 digit=0.
arr[2]=275 item=80 bucket_idx=0 number_idx=2
len=3 position=5 max_length=4
 position:4
{ 195, 196, 275 }
 position:3
{ 195, 196, 275 }
 position:2
{ 195, 196, 275, 276, 272 }
 position:1
{ 89, 195, 196, 275, 276, 272, 2343 }
 time: 0.213000 ms.
 result1 sorted:
{ 89, 195, 196, 275, 276, 272, 2343 }

 origin arr2:
{ 33, -4, 15, 43, -323454, 7, 10, 1235, 200, 87431 }
len=10 position=1 max_length=6
num=323487 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[0]=33 item=323487 bucket_idx=3 number_idx=0
num=323450 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[1]=-4 item=323450 bucket_idx=3 number_idx=1
num=323469 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[2]=15 item=323469 bucket_idx=3 number_idx=2
num=323497 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[3]=43 item=323497 bucket_idx=3 number_idx=3
arr[4]=-323454 item=0 bucket_idx=0 number_idx=0
num=323461 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[5]=7 item=323461 bucket_idx=3 number_idx=4
num=323464 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[6]=10 item=323464 bucket_idx=3 number_idx=5
num=324689 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[7]=1235 item=324689 bucket_idx=3 number_idx=6
num=323654 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=3.
arr[8]=200 item=323654 bucket_idx=3 number_idx=7
num=410885 position=1 max_length=6 number_length=6 exponent=100000 position=1 digit=4.
arr[9]=87431 item=410885 bucket_idx=4 number_idx=0
len=8 position=2 max_length=6
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
arr[2]=15 item=19 bucket_idx=0 number_idx=2
arr[3]=43 item=47 bucket_idx=0 number_idx=3
arr[4]=7 item=11 bucket_idx=0 number_idx=4
arr[5]=10 item=14 bucket_idx=0 number_idx=5
num=1239 position=2 max_length=6 number_length=4 exponent=100 position=2 digit=2.
arr[6]=1235 item=1239 bucket_idx=2 number_idx=0
arr[7]=200 item=204 bucket_idx=0 number_idx=6
len=7 position=3 max_length=6
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
arr[2]=15 item=19 bucket_idx=0 number_idx=2
arr[3]=43 item=47 bucket_idx=0 number_idx=3
arr[4]=7 item=11 bucket_idx=0 number_idx=4
arr[5]=10 item=14 bucket_idx=0 number_idx=5
num=204 position=3 max_length=6 number_length=3 exponent=1 position=3 digit=4.
arr[6]=200 item=204 bucket_idx=4 number_idx=0
len=6 position=4 max_length=6
num=37 position=4 max_length=6 number_length=2 exponent=0 position=4 digit=0.
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
num=19 position=4 max_length=6 number_length=2 exponent=0 position=4 digit=0.
arr[2]=15 item=19 bucket_idx=0 number_idx=2
num=47 position=4 max_length=6 number_length=2 exponent=0 position=4 digit=0.
arr[3]=43 item=47 bucket_idx=0 number_idx=3
num=11 position=4 max_length=6 number_length=2 exponent=0 position=4 digit=0.
arr[4]=7 item=11 bucket_idx=0 number_idx=4
num=14 position=4 max_length=6 number_length=2 exponent=0 position=4 digit=0.
arr[5]=10 item=14 bucket_idx=0 number_idx=5
len=6 position=5 max_length=6
num=37 position=5 max_length=6 number_length=2 exponent=0 position=5 digit=0.
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
num=19 position=5 max_length=6 number_length=2 exponent=0 position=5 digit=0.
arr[2]=15 item=19 bucket_idx=0 number_idx=2
num=47 position=5 max_length=6 number_length=2 exponent=0 position=5 digit=0.
arr[3]=43 item=47 bucket_idx=0 number_idx=3
num=11 position=5 max_length=6 number_length=2 exponent=0 position=5 digit=0.
arr[4]=7 item=11 bucket_idx=0 number_idx=4
num=14 position=5 max_length=6 number_length=2 exponent=0 position=5 digit=0.
arr[5]=10 item=14 bucket_idx=0 number_idx=5
len=6 position=6 max_length=6
num=37 position=6 max_length=6 number_length=2 exponent=0 position=6 digit=0.
arr[0]=33 item=37 bucket_idx=0 number_idx=0
arr[1]=-4 item=0 bucket_idx=0 number_idx=1
num=19 position=6 max_length=6 number_length=2 exponent=0 position=6 digit=0.
arr[2]=15 item=19 bucket_idx=0 number_idx=2
num=47 position=6 max_length=6 number_length=2 exponent=0 position=6 digit=0.
arr[3]=43 item=47 bucket_idx=0 number_idx=3
num=11 position=6 max_length=6 number_length=2 exponent=0 position=6 digit=0.
arr[4]=7 item=11 bucket_idx=0 number_idx=4
num=14 position=6 max_length=6 number_length=2 exponent=0 position=6 digit=0.
arr[5]=10 item=14 bucket_idx=0 number_idx=5
len=6 position=7 max_length=6
 position:6
{ 33, -4, 15, 43, 7, 10 }
 position:5
{ 33, -4, 15, 43, 7, 10 }
 position:4
{ 33, -4, 15, 43, 7, 10 }
 position:3
{ 33, -4, 15, 43, 7, 10, 200 }
 position:2
{ 33, -4, 15, 43, 7, 10, 200, 1235 }
 position:1
{ -323454, 33, -4, 15, 43, 7, 10, 200, 1235, 87431 }
 result2 sorted:
{ -323454, 33, -4, 15, 43, 7, 10, 200, 1235, 87431 }
 time: 0.388000 ms.%
*/