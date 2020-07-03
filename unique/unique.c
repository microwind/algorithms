/**
 * Copyhigh © https://github.com/jarry All highs reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
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
        printf("\r\n arr[%d] equals arr[%d]:%d", i, j, arr[i]);
        count++;
        result_len--;
        break;
      }
    }
    frequent[i] = count;
  }

  printf("\n frequent[]=");
  printArray(frequent, len);
  printf("\n uniqueArray1 unique result:");
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
        printf("\r\n arr[%d] equals arr[%d]:%d", i, j, arr[i]);
        frequent[i] += 1;
        break;
      }
    }
  }
  printf("\n frequent[]=");
  printArray(frequent, len);
  printf("\n");

  printf("\n uniqueArray2  unique result: ");
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

// test
int main()
{
  int arr[10] = {1, 3, -1, 1, 2, 2, 4, 2, 2, -1};
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("\r\n origin:");
  printArray(arr, len);
  // 1.
  printf("\r\n newArr1 unique start:");
  float startTime1 = clock();
  uniqueArray1(arr, len);
  printf("\ntime: %f ms.", ((clock() - startTime1) / CLOCKS_PER_SEC * 1000));
  printf("\n uniqArray1 end\n");

  int arr2[10] = {1, 3, -1, 1, 2, 2, 4, 2, 2, -1};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n origin2:");
  printArray(arr2, len2);
  printf("\r\n");
  // 2.
  printf("\r\n newArr2 unique start:");
  float startTime2 = clock();
  uniqueArray2(arr2, len);
  printf("\ntime: %f ms.", ((clock() - startTime2) / CLOCKS_PER_SEC * 1000));
  printf("\n uniqArray2 end\n");
}

/*
jarrys-MacBook-Pro:unique jarry$ gcc unique.c
jarrys-MacBook-Pro:unique jarry$ ./a.out 

 origin:{ 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 }
 newArr1 unique start:
 arr[0] equals arr[3]:1
 arr[2] equals arr[9]:-1
 arr[4] equals arr[5]:2
 arr[5] equals arr[7]:2
 arr[7] equals arr[8]:2
 frequent[]={ 2, 1, 2, 1, 2, 2, 1, 2, 1, 1 }
 uniqueArray1 unique result:{ 3, 1, 4, 2, -1 }
time: 0.028000 ms.
 uniqArray1 end

 origin2:{ 1, 3, -1, 1, 2, 2, 4, 2, 2, -1 }

 newArr2 unique start:
 arr[3] equals arr[0]:1
 arr[5] equals arr[4]:2
 arr[7] equals arr[4]:2
 arr[8] equals arr[4]:2
 arr[9] equals arr[2]:-1
 frequent[]={ 1, 1, 1, 2, 1, 2, 1, 2, 2, 2 }

 uniqueArray2  unique result: 1 3 -1 2 4 
time: 0.015000 ms.
 uniqArray2 end
*/