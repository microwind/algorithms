/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <memory.h>

void print_array(int *arr, int len)
{
  std::cout << "{ " << "";
  for (int i = 0; i < len; i++)
  {
    std::cout << arr[i] << " ";
    if (i < len - 1)
    {
      std::cout <<  ", " << "";
    }
  }
  std::cout <<  " }" << "";
  std::cout << std::right;
}

// 基数排序，基于计数排序实现，计数排序写在一个方法内
int *radixSort(int *arr, int len)
{

  // 以10倍递进
  int range = 10;
  int output[len];

  int max = arr[0];
  for (int i = 0; i < len; i++)
  {
    if (arr[i] > max)
    {
      max = arr[i];
    }
  }

  // 根据最大值，逐个按进位(基数)来应用排序，exponent即基数。
  for (int exponent = 1; (max / exponent) > 0; exponent *= range)
  {

    // 计数数组，长度为10，0-9一共10个数字
    int countList[range];
    memset(countList, 0, range * sizeof(int));
    // 根据基数得到当前位数，并给计数数组对应位置加1
    for (int i = 0; i < len; i++)
    {
      int item = arr[i];
      int idx = (item / exponent) % range;
      countList[idx] += 1;
    }

    // 计数排序构建，自前往后，逐个将上一项的值存入当前项
    for (int i = 1; i < range; i++)
    {
      countList[i] += countList[i - 1];
    }

    // 根据计数数组按顺序取出排序内容
    for (int i = len - 1; i >= 0; i--)
    {
      int idx = (arr[i] / exponent) % range;
      output[countList[idx] - 1] = arr[i];
      countList[idx] -= 1;
    }

    // 复制输出数组到原始数组
    for (int i = 0; i < len; i++)
    {
      arr[i] = output[i];
    }
  }

  return arr;
}

// 测试
int main()
{
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int len = sizeof(arr) / sizeof(arr[0]);
  std::cout << "\r\n origin arr1:";
  print_array(arr, len);
  int *result1 = radixSort(arr, len);
  std::cout << ("\r\n arr1 sorted:")  << std::endl;
  print_array(result1, len);

  int arr2[] = { 3, 4, 15, 2, 2, 123, 2, 3, 3, 237, 10 };
  int len2 = sizeof(arr) / sizeof(arr[0]);
  std::cout << "\r\n origin arr2:";
  print_array(arr2, len2);
  int *result2 = radixSort(arr2, len2);
  std::cout << ("\r\n arr2 sorted:") << std::endl;
  print_array(result2, len);

  return 0;
}

/*
jarry@jarrys-MacBook-Pro radixsort % g++ radix_sort.cpp
jarry@jarrys-MacBook-Pro radixsort % ./a.out           

 origin arr1:{ 170 , 45 , 75 , 90 , 802 , 24 , 2 , 66  }
 arr1 sorted:
{ 2 , 24 , 45 , 66 , 75 , 90 , 170 , 802  }
 origin arr2:{ 3 , 4 , 15 , 2 , 2 , 123 , 2 , 3  }
 arr2 sorted:
{ 2 , 2 , 2 , 3 , 3 , 4 , 15 , 123  }%  
*/