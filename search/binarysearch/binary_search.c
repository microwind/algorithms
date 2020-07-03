/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

// 标准非递归版本，传递左右区间指针
int binary_search1(int *arr, int len, int item)
{
  int left = 0;
  int right = len - 1;
  int mid_index;
  int middle;
  while (left <= right)
  {
    mid_index = (left + right) / 2;
    middle = arr[mid_index];
    if (item > middle)
    {
      left = mid_index + 1;
    }
    else
    {
      right = mid_index - 1;
    }
  }
  if (left < len && arr[left] == item)
    return left;
  return -1;
}

// 递归实现，移动左右区间指针
int binary_search2(int *arr, int item, int left, int right)
{
  int mid_index = (left + right) / 2;
  int middle = arr[mid_index];
  if (middle == item)
  {
    if (arr[left] == item)
      return left;
    return mid_index;
  }
  if (left >= right)
    return -1;

  if (item > middle)
    return binary_search2(arr, item, mid_index + 1, right);
  else
    return binary_search2(arr, item, left, mid_index - 1);
}

int main()
{
  /* find search1 */
  int arr[6] = {2, 3, 8, 10, 10, 13};
  int len = sizeof(arr) / sizeof(arr[0]);
  float startTime = clock();
  printf("search start:");
  int result = binary_search1(arr, len, 3); // 1
  printf("\n binary_search1(arr, len, 3), %d", result);
  result = binary_search1(arr, len, 10);    // 3
  printf("\n binary_search1(arr, len, 10), %d", result);
  result = binary_search1(arr, len, 111);    // -1
  printf("\n binary_search1(arr, len, 11), %d", result);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  /* test search2 */
  int arr2[6] = {2, 3, 8, 10, 10, 13};
  int len2 = sizeof(arr) / sizeof(arr[0]);
  startTime = clock();
  printf("search start:");
  result = binary_search2(arr2, 3, 0, len2);     // 1
  printf("\n binary_search1(arr, len, 3), %d", result);
  result = binary_search2(arr2, 10, 0, len2);    // 3
  printf("\n binary_search1(arr2, len2, 10), %d", result);
  result = binary_search2(arr, 111, 0, len2);    // -1
  printf("\n binary_search1(arr, len, 111), %d", result);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
}

/**
jarry@jarrys-MacBook-Pro binarysearch % gcc binary_search.c
jarry@jarrys-MacBook-Pro binarysearch % ./a.out            
search start:
 binary_search1(arr, len, 3), 1
 binary_search1(arr, len, 10), 3
 binary_search1(arr, len, 11), -1
time: 0.027000 ms.search start:
 binary_search1(arr, len, 3), 1
 binary_search1(arr2, len2, 10), 3
 binary_search1(arr, len, 111), -1
time: 0.005000 ms.%    
*/