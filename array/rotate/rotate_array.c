#include <stdio.h>

// 旋转数组：旋转数组可以分为左旋转和右旋转两类。
// 左旋转是指将数组的元素向左移动若干位置，而右旋转是指将数组的元素向右移动若干位置。此为右旋转。
void rotateArray(int arr[], int d, int n)
{
  int temp[d];
  for (int i = 0; i < d; i++)
  {
    temp[i] = arr[i];
  }
  for (int i = 0; i < n - d; i++)
  {
    arr[i] = arr[i + d];
  }
  for (int i = 0; i < d; i++)
  {
    arr[n - d + i] = temp[i];
  }
}

int main()
{
  int arr[] = {1, 2, 3, 4, 5, 6, 7};
  int n = sizeof(arr) / sizeof(arr[0]);
  int d = 3;
  rotateArray(arr, d, n);
  printf("Rotated array: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  return 0;
}

/**
jarry@jarrys-MacBook-Pro rotate % gcc rotate_array.c
jarry@jarrys-MacBook-Pro rotate % ./a.out           
Rotated array: 4 5 6 7 1 2 3 %    
 */