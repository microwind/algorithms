/**
 * Copyhigh © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <iostream>
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void printArray(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::right;
}

// 把数组分按照基准值分为左右两部分，再返回新的中间位置作为排序的pivot
int partition(int *arr, int left, int right)
{
  // 这里的pivot以右侧为准
  int pivotIndex = right;
  int pivot = arr[pivotIndex];
  // 记录交换的位置
  int swapIndex = left - 1;
  for (int i = left; i < right; i++)
  {
    // 如果小于基准则进行交换
    // 把小于基数的逐个往左侧放，大于基数的往右侧放
    if (arr[i] < pivot)
    {
      swapIndex++;
      swap(&arr[swapIndex], &arr[i]);
    }
  }
  swapIndex++;
  // 最后把原基数调换到分区线的位置，并返回分区线位置
  swap(&arr[swapIndex], &arr[pivotIndex]);
  return swapIndex;
}

// 数组分区写法2，与第一种类似
int partition2(int *arr, int left, int right)
{
  // 基数位置以左侧为准
  int pivotIndex = left;
  int swapIndex = pivotIndex + 1;
  for (int i = swapIndex; i <= right; i++)
  {
    // 当比较项小于基数时，将比较项逐个挪到左侧，同时左侧下标移动1位
    if (arr[i] < arr[pivotIndex])
    {
      swap(&arr[i], &arr[swapIndex]);
      swapIndex++;
    }
  }
  swap(&arr[pivotIndex], &arr[swapIndex - 1]);
  return swapIndex - 1;
}

void quickSort(int *arr, int left, int right)
{
  if (left < right)
  {
    int pivot = partition(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
  }
}

int main()
{

  int arr[] = {7, 11, 9, 10, 12, 13, 8};
  int len = sizeof(arr) / sizeof(arr[0]);
  std::cout << "original:\n";
  printArray(arr, len);

  quickSort(arr, 0, len - 1);

  std::cout << "\nsorted:\n";
  printArray(arr, len);
  return 0;
}

/**
jarry@jarrys-MacBook-Pro quicksort % gcc -std=c++11 -o quick_sort quick_sort.cpp
或者
jarry@jarrys-MacBook-Pro quicksort % g++ quick_sort.cpp
jarry@jarrys-MacBook-Pro quicksort % ./quick_sort
original:
7 11 9 10 12 13 8
sorted:
7 8 9 10 11 12 13
 */