/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

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
  // 使用临时变量交换数组中两个位置的元素
  int tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

/**
 * 冒泡排序升序，将最大的元素冒泡到最后
 * 时间复杂度：O(n²)，空间复杂度：O(1)，稳定性：稳定
 */
int *bubbleSort1(int arr[], int len)
{
  printf("bubbleSort1 from left to right:");
  // 外层循环控制排序轮数，每轮确定一个最大值的位置
  for (int i = 0; i < len; i++)
  {
    // 内层循环控制比较次数，len-i-1 避免重复比较已排序部分
    for (int j = 0; j < len - i - 1; j++)
    {
      // 自左往右每两个进行比较，把大的交换到右侧
      // 逐轮冒出最大数，已经排好序的不要再比较
      if (arr[j] > arr[j + 1])
      {
        // 使用临时变量交换相邻元素
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
      printf("\r\n i=%d j=%d", i, j);
    }
  }
  return arr;
}

/**
 * 冒泡排序降序，将最小的元素冒泡到最后
 * 从右向左比较，逐轮冒出最小数
 * 时间复杂度：O(n²)，空间复杂度：O(1)，稳定性：稳定
 */
int bubbleSort2(int arr[], int len)
{
  printf("bubbleSort2 from right to left:");
  // 外层循环控制排序轮数，每轮确定一个最小值的位置
  for (int i = 0; i < len; i++)
  {
    // 内层循环从右向左比较，j > i 避免重复比较已排序部分
    for (int j = len - 1; j > i; j--)
    {
      // 自右往左每两个进行比较，把小的交换到右侧
      // 逐轮冒出最小数，已经排好序的不要再比较
      if (arr[j - 1] < arr[j])
      {
        // 使用 swap 函数交换元素
        swap(arr, j, j - 1);
      }
      printf("\r\n i=%d j=%d", i, j);
    }
  }
  return 0;
}

/**
 * 冒泡排序升序，增加交换标志优化
 * 当某一轮无交换时提前终止，针对有序情况优化
 * 时间复杂度：最好O(n)，最坏O(n²)，空间复杂度：O(1)
 */
void bubbleSort3(int arr[], int len)
{
  printf("bubbleSort3 add flag:");
  // 增加一个标志，如果某一轮没有进行过任何的交换
  // 则说明当前数组已排好序，则不必继续后面的遍历，
  bool flag = true;

  // 外层循环增加 flag 条件，当数组已有序时提前终止
  for (int i = 0; i < len && flag == true; i++)
  {
    flag = false;  // 每轮开始时重置标志
    printf("\r\nno. %d", i);
    // 内层循环控制比较次数，len-i-1 避免重复比较已排序部分
    for (int j = 0; j < len - i - 1; j++)
    {
      // 自左往右每两个进行比较，把大的交换到右侧
      // 逐轮冒出最大数，已经排好序的不要再比较
      if (arr[j] > arr[j + 1])
      {
        flag = true;  // 发生交换，设置标志
        // 使用 swap 函数交换元素
        swap(arr, j, j + 1);
      }
      printf("\r\n i=%d j=%d", i, j);
    }
  }
}


/**
 * 插入冒泡排序法，分为左右两个序列，左侧为已排序，将待排项与左侧逐个对比并交换位置
 */
int *bubbleSort4(int arr[], int len)
{
  printf("bubbleSort4:");
  // 外层循环控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
  for (int i = 1; i < len; i++)
  {
    int j = i - 1;    // j 指向已排序区域的最后一个元素
    int current = i;  // current 指向待插入元素
    // 从已排序区域的末尾向前比较，将待插入元素冒泡到正确位置
    while (j >= 0)
    {
      // 与插入排序同，不同的是，插入排序整体右移，空出位置，然后再插入
      // 冒泡则实时交换位置，把最小的冒泡到最前面
      if (arr[current] < arr[j])
      {
        printf("\r\ni=%d, j=%d, arr[i]=%d, arr[j+1]=%d", i, j, arr[i], arr[j + 1]);
        // 交换待插入元素和当前比较的元素
        int temp = arr[current];
        arr[current] = arr[j];
        arr[j] = temp;
      }
      current = j;  // 更新待插入元素的位置
      j--;  // 继续向前比较
    }
  }

  return arr;
}

int main()
{
  // sort1
  printf("\r\nbubbleSort1 start\r\n");
  int arr1[7] = {7, 11, -9, 10, 12, 13, 8};
  int len1 = sizeof(arr1) / sizeof(arr1[0]);
  float startTime = clock();
  bubbleSort1(arr1, len1);
  printf("\r\nbubbleSort1 sorted:");
  for (int i = 0; i < len1; i++)
  {
    printf("%d ", arr1[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  // sort2
  int arr2[7] = {7, 11, -9, 10, 12, 13, 8};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  startTime = clock();
  bubbleSort2(arr2, len2);
  printf("\r\nbubbleSort2 sorted:");
  for (int i = 0; i < len2; i++)
  {
    printf("%d ", arr2[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  // sort3
  int arr3[7] = {7, 11, -9, 10, 12, 13, 8};
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  bubbleSort3(arr3, len3);
  printf("\r\nbubbleSort3 sorted:");
  for (int i = 0; i < len3; i++)
  {
    printf("%d ", arr3[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

  // sort4
  int arr4[7] = {7, 11, -9, 10, 12, 13, 8};
  int len4 = sizeof(arr4) / sizeof(arr4[0]);
  bubbleSort4(arr4, len4);
  printf("\r\nbubbleSort4 sorted:");
  for (int i = 0; i < len4; i++)
  {
    printf("%d ", arr4[i]);
  }
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

}
/*
jarrys-MacBook-Pro:bubblesort jarry$ gcc bubble_sort.c
jarrys-MacBook-Pro:bubblesort jarry$ ./a.out
bubbleSort1 start
bubbleSort1 from left to right:
 i=0 j=0
 i=0 j=1
 i=0 j=2
 i=0 j=3
 i=0 j=4
 i=0 j=5
 i=1 j=0
 i=1 j=1
 i=1 j=2
 i=1 j=3
 i=1 j=4
 i=2 j=0
 i=2 j=1
 i=2 j=2
 i=2 j=3
 i=3 j=0
 i=3 j=1
 i=3 j=2
 i=4 j=0
 i=4 j=1
 i=5 j=0
bubbleSort1 sorted:-9 7 8 10 11 12 13 
time: 0.051000 ms.bubbleSort2 from right to left:
 i=0 j=7
 i=0 j=6
 i=0 j=5
 i=0 j=4
 i=0 j=3
 i=0 j=2
 i=0 j=1
 i=1 j=7
 i=1 j=6
 i=1 j=5
 i=1 j=4
 i=1 j=3
 i=1 j=2
 i=2 j=7
 i=2 j=6
 i=2 j=5
 i=2 j=4
 i=2 j=3
 i=3 j=7
 i=3 j=6
 i=3 j=5
 i=3 j=4
 i=4 j=7
 i=4 j=6
 i=4 j=5
 i=5 j=7
 i=5 j=6
 i=6 j=7
bubbleSort2 sorted:13 12 11 10 8 7 0 
time: 0.062000 ms.bubbleSort3 add flag:
no. 0
 i=0 j=0
 i=0 j=1
 i=0 j=2
 i=0 j=3
 i=0 j=4
 i=0 j=5
no. 1
 i=1 j=0
 i=1 j=1
 i=1 j=2
 i=1 j=3
 i=1 j=4
no. 2
 i=2 j=0
 i=2 j=1
 i=2 j=2
 i=2 j=3
no. 3
 i=3 j=0
 i=3 j=1
 i=3 j=2
no. 4
 i=4 j=0
 i=4 j=1
bubbleSort3 sorted:-9 7 8 10 11 12 13 
time: 0.182000 ms.bubbleSort4:
i=2, j=1, arr[i]=-9, arr[j+1]=-9
i=2, j=0, arr[i]=11, arr[j+1]=-9
i=3, j=2, arr[i]=10, arr[j+1]=10
i=6, j=5, arr[i]=8, arr[j+1]=8
i=6, j=4, arr[i]=13, arr[j+1]=8
i=6, j=3, arr[i]=13, arr[j+1]=8
i=6, j=2, arr[i]=13, arr[j+1]=8
bubbleSort4 sorted:-9 7 8 10 11 12 13 
time: 0.227000 ms.%  
*/