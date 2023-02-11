/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

/**
 * 插入排序标准版1
 */
int *insert_sort1(int arr[], int len)
{
  int j;
  int current;
  // 外循环用于遍历待排序区间，内循环用来遍历已排序区间
  for (int i = 0; i < len; i++)
  {
    int j = i;
    current = arr[i];
    // 将该项自右往左与已排序项逐个对比，当遇到比自己大的项(表示升序)时，将该位置右移
    // 直到遇到小于等于自己的项则停止移动，表示插入成功
    printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
    while (j-- > 0 && current < arr[j])
    {
      // 逐个位移，相当于整体右移
      arr[j + 1] = arr[j];
    }
    // 交换为当前项
    arr[j + 1] = current;
  }
  return arr;
}

/**
 * 插入排序标准版2
 */
int *insert_sort2(int arr[], int len)
{
  int j, current;
  for (int i = 1; i < len; i++)
  {
    j = i - 1;
    current = arr[i];
    printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
    while (j >= 0 && current < arr[j])
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = current;
  }
  return arr;
}

/**
 * 插入排序倒序版
 */
int *insert_sort3(int arr[], int len)
{
  for (int i = 0; i < len; i++)
  {
    int current = arr[i];
    int j = i - 1;
    printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
    for (; j >= 0; j--)
    {
      // 如果比较项大于已排序项，则逐个右移动
      if (current > arr[j])
        arr[j + 1] = arr[j];
      // 如果遇到不大于该项则跳出，继续下一项对比
      else
        break;
    }
    arr[j + 1] = current;
  }
  return arr;
}

int main()
{
  int arr[7] = {-7, 11, 9, 10, 12, 13, 8};
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("\n origin array:\n");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }

  // insert1
  float startTime1 = clock();
  int arr1[7] = {-7, 11, 9, 10, 12, 13, 8};
  int len1 = sizeof(arr1) / sizeof(arr1[0]);
  insert_sort1(arr1, len1);
  printf("\n insert_sort1 end:\n");
  for (int i = 0; i < len1; i++)
  {
    printf("%d ", arr1[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime1) / CLOCKS_PER_SEC * 1000));

  // insert2
  float startTime2 = clock();
  int arr2[7] = {-7, 11, 9, 10, 12, 13, 8};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  insert_sort2(arr2, len2);
  printf("\n insert_sort2 end:\n");
  for (int i = 0; i < len2; i++)
  {
    printf("%d ", arr2[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime2) / CLOCKS_PER_SEC * 1000));

  // insert3
  float startTime3 = clock();
  int arr3[7] = {-7, 11, 9, 10, 12, 13, 8};
  int len3 = sizeof(arr) / sizeof(arr[0]);
  insert_sort3(arr3, len3);
  printf("\n insert_sort3 end:\n");
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr3[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime3) / CLOCKS_PER_SEC * 1000));

  return 0;
}

/**
jarry@jarrys-MacBook-Pro insertsort % gcc --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/c++/4.2.1
Apple clang version 12.0.0 (clang-1200.0.32.29)
Target: x86_64-apple-darwin19.6.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
jarrys-mbp:insertsort jarry$ gcc insert_sort.c
jarrys-mbp:insertsort jarry$ ./a.out
 origin array:
-7 11 9 10 12 13 8 
i=0, j=0, arr[i]=-7, arr[j+1]=11
i=1, j=1, arr[i]=11, arr[j+1]=9
i=2, j=2, arr[i]=9, arr[j+1]=10
i=3, j=3, arr[i]=10, arr[j+1]=12
i=4, j=4, arr[i]=12, arr[j+1]=13
i=5, j=5, arr[i]=13, arr[j+1]=8
i=6, j=6, arr[i]=8, arr[j+1]=0
 insert_sort1 end:
-7 8 9 10 11 12 13 
time: 0.027000 ms.
i=1, j=0, arr[i]=11, arr[j+1]=11
i=2, j=1, arr[i]=9, arr[j+1]=9
i=3, j=2, arr[i]=10, arr[j+1]=10
i=4, j=3, arr[i]=12, arr[j+1]=12
i=5, j=4, arr[i]=13, arr[j+1]=13
i=6, j=5, arr[i]=8, arr[j+1]=8
 insert_sort2 end:
-7 8 9 10 11 12 13 
time: 0.022000 ms.
i=0, j=-1, arr[i]=-7, arr[j+1]=-7
i=1, j=0, arr[i]=11, arr[j+1]=11
i=2, j=1, arr[i]=9, arr[j+1]=9
i=3, j=2, arr[i]=10, arr[j+1]=10
i=4, j=3, arr[i]=12, arr[j+1]=12
i=5, j=4, arr[i]=13, arr[j+1]=13
i=6, j=5, arr[i]=8, arr[j+1]=8
 insert_sort3 end:
13 12 11 10 9 8 -7 
time: 0.024000 ms.% 
 */