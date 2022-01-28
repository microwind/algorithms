/**
 * Copyhigh © https://github.com/jarry All highs reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// 1. 双层循环，从0开始逐个与右侧全部项进行比较，记录重复次数，大于1的可去掉相同项。删除前面的重复项
int *uniqueArray1(int arr[], int len)
{
  int frequent[len];
  int result_len = len;
  for (int i = 0; i < len; i++)
  {
    // 默认记录出现1次
    int count = 1;
    for (int j = i + 1; j < len; j++)
    {
      // printf("\n i=%d j=%d arr[i]=%d arr[j]=%d", i, j, arr[i], arr[j]);
      if (arr[i] == arr[j])
      {
        // 重复则记录增加1次，表示重复，且跳出循环
        // printf("\r\n arr[%d] equals arr[%d]:%d", i, j, arr[i]);
        count++;
        result_len--;
        break;
      }
    }
    frequent[i] = count;
  }

  printf("\n frequent[]=");
  printArray(frequent, len);
  printf("\n print uniqueArray1 result:");
  int k = 0;
  int result_idx = 0;
  int result[result_len];
  while (k < len)
  {
    if (frequent[k] == 1)
    {
      result[result_idx] = arr[k];
      result_idx++;
    }
    k++;
  }
  // 打印或返回结果
  printArray(result, result_len);
  return 0;
}

// 2. 双层循环，从1开始逐个与左侧全部项进行比较，记录重复次数，大于1的可去掉相同项。删除后面的重复项。
int *uniqueArray2(int arr[], int len)
{
  int frequent[len];
  frequent[0] = 1;
  for (int i = 1; i < len; i++)
  {
    frequent[i] = 1;
    for (int j = 0; j < i; j++)
    {
      // printf("\n i=%d j=%d arr[i]=%d arr[j]=%d", i, j, arr[i], arr[j]);
      if (arr[i] == arr[j])
      {
        // printf("\r\n arr[%d] equals arr[%d]:%d", i, j, arr[i]);
        frequent[i] += 1;
        break;
      }
    }
  }
  printf("\n frequent[]=");
  printArray(frequent, len);
  printf("\n");

  printf("\n print uniqueArray2 result: ");
  int k = 0;
  while (k < len)
  {
    if (frequent[k] == 1)
    {
      printf("%d ", arr[k]);
    }
    k++;
  }
  return 0;
}


// 3. 双层循环，自前往后逐个与前面项进行比较，如果值和下标都相同可以认为是第一次出现。
int *uniqueArray3(int arr[], int len)
{
  int *result = (int *)malloc(len * sizeof(int));
  int idx = 0;
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      // printf("\n i=%d j=%d arr[i]=%d arr[j]=%d", i, j, arr[i], arr[j]);
      if (arr[i] == arr[j])
      {
        // 值相同且下标也相同则表示第一次出现，可以追加到新数组中去
        if (i == j) {
          // printf("\r\n arr[%d] vs [%d]:%d", i, j, arr[i]);
          result[idx] = arr[i];
          idx++;
        }
        break;
      }
    }
  }

  printf("\n print uniqueArray3 result: ");
  int k = 0;
  while (k < idx)
  {
    printf("%d ", result[k]);
    k++;
  }
  return 0;
}

// test
int main()
{
  // 1.
  int arr1[10] = {1, 3, -1, 1, 2, 2, 4, 2, 2, -1};
  int len = sizeof(arr1) / sizeof(arr1[0]);
  printf("\r\n arr1:");
  printArray(arr1, len);
  float startTime1 = clock();
  uniqueArray1(arr1, len);
  printf("\ncost: %f ms.", ((clock() - startTime1) / CLOCKS_PER_SEC * 1000));
  printf("\n uniqArray1 end\n");

  // 2.
  int arr2[10] = {1, 3, -1, 1, 2, 2, 4, 2, 2, -1};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n arr2:");
  printArray(arr2, len2);
  printf("\r\n");
  float startTime2 = clock();
  uniqueArray2(arr2, len);
  printf("\ncost: %f ms.", ((clock() - startTime2) / CLOCKS_PER_SEC * 1000));
  printf("\n uniqArray2 end\n");

  // 3.
  int arr3[10] = {1, 3, -1, 1, 2, 2, 4, 2, 2, -1};
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  printf("\r\n arr3:");
  printArray(arr3, len3);
  printf("\r\n");
  float startTime3 = clock();
  uniqueArray3(arr3, len);
  printf("\ncost: %f ms.", ((clock() - startTime3) / CLOCKS_PER_SEC * 1000));
  printf("\n uniqArray2 end\n");


}

/*
jarrys-MacBook-Pro:unique jarry$ gcc unique.c
jarrys-MacBook-Pro:unique jarry$ ./a.out 
  arr1:{ 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 }
 frequent[]={ 2, 1, 2, 1, 2, 2, 1, 2, 1, 1 }
 print uniqueArray1 result:{ 3, 1, 4, 2, -1 }
cost: 0.023000 ms.
 uniqArray1 end

 arr2:{ 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 }

 frequent[]={ 1, 1, 1, 2, 1, 2, 1, 2, 2, 2 }

 print uniqueArray2 result: 1 3 -1 2 4 
cost: 0.012000 ms.
 uniqArray2 end

 arr3:{ 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 }

 print uniqueArray3 result: 1 3 -1 2 4 
cost: 0.012000 ms.

*/