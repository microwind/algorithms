/**
 * Copyhigh © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

void printArray(int *arr, int len)
{
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
}

void printArray2(int *arr, int start, int end)
{
  printf("[");
  for (int i = start; i < end; i++)
  {
    printf("%d", arr[i]);
    if (i != end - 1) 
    printf(", ");
  }
  printf("]");
}

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

/** 方式1,标准递归版本。需要左右不断交换，无需新建数组。*/
void *quickSort1(int arr[], int low, int high)
{
  int i = low > 0 ? low : 0;
  int j = high;
  int midIndex = (i + j) / 2;
  int pivot = arr[midIndex];

  // 当左侧小于等于右侧则表示还有值没有对比，需要继续
  while (i <= j)
  {
    // 当左侧小于基准时查找位置右移，直到找出比基准值大的位置来
    while (arr[i] < pivot)
    {
      printf("\r\narr[i] < pivot: i=%d, j=%d, pivot=%d", i, j, pivot);
      i++;
    }
    // 当前右侧大于基准时左移，直到找出比基准值小的位置来
    while (arr[j] > pivot)
    {
      printf("\r\narr[i] > pivot: i=%d, j=%d, pivot=%d", i, j, pivot);
      j--;
    }

    printf("\r\n  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);

    // 当左侧位置小于右侧时，将数据交换，小的交换到基准左侧，大的交换到右侧
    if (i <= j)
    {
      swap(&arr[i], &arr[j]);
      // 缩小搜查范围，直到左侧都小于基数，右侧都大于基数
      i++;
      j--;
    }
  }
  // 左侧小于基数位置，不断递归左边部分
  if (low < j)
  {
    printf("\r\n  low < j:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
    quickSort1(arr, low, j);
  }
  // 基数位置小于右侧，不断递归右侧部分
  if (i < high)
  {
    printf("\r\n  i < high:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
    quickSort1(arr, i, high);
  }

  return arr;
}


/* 快排方式2，递归分区交换 */
// 数组分区写法，以左侧第1个数为基准，将大于基准的数放在右侧
int partition(int *arr, int left, int right)
{
  // 基数位置以左侧为准
  int pivotIndex = left;
  int partitionIndex = pivotIndex + 1;
  for (int i = partitionIndex; i <= right; i++)
  {
    // 当比较项小于基数时，将比较项逐个挪到左侧，同时左侧下标移动1位
    if (arr[i] < arr[pivotIndex])
    {
      swap(&arr[i], &arr[partitionIndex]);
      partitionIndex++;
    }
  }
  // 将基数项调整到最新交换位置，交换位置-1就是分割线
  swap(&arr[pivotIndex], &arr[partitionIndex - 1]);
  printf("\r\n");
  printArray2(arr, left, partitionIndex);
  printf(" partitionIndex=%d, arr[partitionIndex]=%d ", partitionIndex, arr[partitionIndex]);
  printArray2(arr, partitionIndex, right);
  return partitionIndex - 1;
}
// 快排方式2，递归分区交换
int *quickSort2(int *arr, int left, int right)
{
  if (left < right)
  {
    int pivot = partition(arr, left, right);
    quickSort2(arr, left, pivot - 1);
    quickSort2(arr, pivot + 1, right);
  }
  return arr;
}

/** 方式3,非递归版本。先建立栈，或引入外部stack库。*/
/* defined stack  */
typedef int item;
typedef struct stack *Stack;
Stack stack_create(int);
void stack_println(Stack);
bool stack_push(Stack, item);
item stack_pop(Stack);
bool stack_is_full(Stack);
bool stack_is_empty(Stack);
void stack_make_empty(Stack);
int stack_len(Stack);

/* stack.c */
struct stack
{
  int top;
  int size;
  item *data_array;
};

Stack stack_create(int size)
{
  Stack s = malloc(sizeof(struct stack));
  if (s == NULL)
  {
    return NULL;
  }

  s->data_array = malloc(sizeof(int) * size);
  if (s->data_array == NULL)
  {
    return NULL;
  }

  s->top = 0;
  s->size = size;
  return s;
}

void stack_println(Stack s)
{
  for (int i = 0; i < s->top; i++)
  {
    printf("%d ", s->data_array[i]);
  }

  printf("\n");
}

bool stack_is_full(Stack s)
{
  return s->top == s->size;
}

bool stack_is_empty(Stack s)
{
  return s->top == 0;
}

bool stack_push(Stack s, item data)
{
  if (stack_is_full(s))
  {
    return false;
  }

  s->data_array[s->top++] = data;
  return true;
}

item stack_pop(Stack s)
{
  if (stack_is_empty(s))
  {
    return 0;
  }

  return s->data_array[--s->top];
}

void stack_make_empty(Stack s)
{
  s->top = 0;
  return;
}

int stack_len(Stack s)
{
  return s->top;
}

/** 非递归版本。需要交换，无需新建数组，利用stack或queue遍历。*/
void *quickSortNotRecurion(int arr[], int low, int high)
{

  Stack stack = stack_create(high - low);
  printf("\nhigh - low = %d\n", high - low);
  int i, j, midIndex, pivot, tmp;
  // 与标准递归版相同，只是将递归改为遍历栈的方式
  // 先将左右各取一个入栈
  stack_push(stack, low);
  stack_push(stack, high);

  while (!stack_is_empty(stack))
  {
    // 如果栈内还有数据，则一并马上取出，其他逻辑与标准递归版同
    j = high = stack_pop(stack);
    i = low = stack_pop(stack);

    midIndex = (i + j) / 2;
    pivot = arr[midIndex];

    while (i <= j)
    {
      while (arr[i] < pivot)
      {
        printf("\r\narr[i] < pivot: i=%d, j=%d, arr[i]=%d, arr[j]=%d, pivot=%d", i, j, arr[i], arr[j], pivot);
        i++;
      }
      while (arr[j] > pivot)
      {
        printf("\r\narr[i] > pivot: i=%d, j=%d, arr[i]=%d, arr[j]=%d, pivot=%d", i, j, arr[i], arr[j], pivot);
        j--;
      }

      if (i <= j)
      {
        tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
        i++;
        j--;
      }
    }
    if (low < j)
    {
      // 与递归版不同，这里添加到栈中，以便继续循环
      printf("\r\n  low < j:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
      stack_push(stack, low);
      stack_push(stack, j);
    }
    if (i < high)
    {
      printf("\r\n  i < high:recursion:  low=%d, high=%d, i=%d, j=%d, midIndex=%d, pivot=%d", low, high, i, j, midIndex, pivot);
      stack_push(stack, i);
      stack_push(stack, high);
    }
  }
  free(stack);
  return arr;
}

// test
int main()
{
  printf("\r\n sort start\r\n");

  // test quicksort1
  printf("\r\n==quick1 origin==\r\n");
  int arr1[7] = {7, 11, 9, 10, 12, 13, 8};
  int len1 = sizeof(arr1) / sizeof(arr1[0]);
  printArray(arr1, len1);
  float startTime = clock();
  int *newArr1 = quickSort1(arr1, 0, len1 - 1);
  // int *newArr = quickSortNotRecurion(arr, 0, len - 1);
  printf("\r\nquick1 sorted:");
  printArray(newArr1, len1);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\n==quick1 end==\n");

  // test quicksort1
  printf("\r\n==quick2 origin==\r\n");
  int arr2[7] = {7, 11, 9, 10, 12, 13, 8};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printArray(arr2, len2);
  startTime = clock();
  int *newArr2 = quickSort2(arr2, 0, len2 - 1);
  printf("\r\n quick2 sorted:");
  printArray(newArr2, len2);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\n==quick2 end==\n");

  // test quicksort3
  printf("\r\n==quick3 origin==\r\n");
  int arr3[7] = {7, 11, 9, 10, 12, 13, 8};
  int len3 = sizeof(arr3) / sizeof(arr3[0]);
  printArray(arr3, len3);
  startTime = clock();
  int *newArr3 = quickSortNotRecurion(arr3, 0, len3 - 1);
  printf("\r\n quick3 sorted:");
  printArray(newArr3, len3);
  printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\n==quick3 end==\n");

}

/**
jarry@jarrys-MacBook-Pro quicksort % gcc quick_sort.c
jarry@jarrys-MacBook-Pro quicksort % ./a.out 

 sort start

==quick1 origin==
7 11 9 10 12 13 8 
arr[i] < pivot: i=0, j=6, pivot=10
  low=0, high=6, i=1, j=6, midIndex=3, pivot=10
arr[i] < pivot: i=2, j=5, pivot=10
arr[i] > pivot: i=3, j=5, pivot=10
arr[i] > pivot: i=3, j=4, pivot=10
  low=0, high=6, i=3, j=3, midIndex=3, pivot=10
  low < j:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=0, j=2, pivot=8
arr[i] > pivot: i=1, j=2, pivot=8
  low=0, high=2, i=1, j=1, midIndex=1, pivot=8
  i < high:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=4, j=6, pivot=13
  low=4, high=6, i=5, j=6, midIndex=5, pivot=13
  low < j:recursion:  low=4, high=6, i=6, j=5, midIndex=5, pivot=13
  low=4, high=5, i=4, j=5, midIndex=4, pivot=12
quick1 sorted:7 8 9 10 11 12 13 
time: 0.046000 ms.
==quick1 end==

==quick2 origin==
7 11 9 10 12 13 8 
[7] partitionIndex=1, arr[partitionIndex]=11 [11, 9, 10, 12, 13]
[8, 9, 10, 11] partitionIndex=5, arr[partitionIndex]=13 [13]
[8] partitionIndex=2, arr[partitionIndex]=9 [9]
[9] partitionIndex=3, arr[partitionIndex]=10 []
[12, 13] partitionIndex=7, arr[partitionIndex]=0 []
 quick2 sorted:7 8 9 10 11 12 13 
time: 0.023000 ms.
==quick2 end==

==quick3 origin==
7 11 9 10 12 13 8 
high - low = 6

arr[i] < pivot: i=0, j=6, arr[i]=7, arr[j]=8, pivot=10
arr[i] < pivot: i=2, j=5, arr[i]=9, arr[j]=13, pivot=10
arr[i] > pivot: i=3, j=5, arr[i]=10, arr[j]=13, pivot=10
arr[i] > pivot: i=3, j=4, arr[i]=10, arr[j]=12, pivot=10
  low < j:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
  i < high:recursion:  low=0, high=6, i=4, j=2, midIndex=3, pivot=10
arr[i] < pivot: i=4, j=6, arr[i]=12, arr[j]=11, pivot=13
  low < j:recursion:  low=4, high=6, i=6, j=5, midIndex=5, pivot=13
arr[i] < pivot: i=0, j=2, arr[i]=7, arr[j]=9, pivot=8
arr[i] > pivot: i=1, j=2, arr[i]=8, arr[j]=9, pivot=8
 quick3 sorted:7 8 9 10 11 12 13 
time: 0.075000 ms.
==quick3 end==
 */
