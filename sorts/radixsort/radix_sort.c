/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

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
  int tmp = arr[b];
  arr[b] = arr[a];
  arr[a] = tmp;
}

int count(int arr[], int len, int number)
{
  int count = 0;
  for (int i = 0; i < len; i++)
  {
    if (arr[i] == number)
      count++;
  }
  return count;
}

void print_array(int *arr, int len)
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

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void count_sort(int arr[], int len, int exp)
{
  int output[len];
  int size = 10;
  int i;
  int count[size];
  memset(count, 0, size * sizeof(int));

  // Store count of occurrences in count[]
  for (i = 0; i < len; i++)
  {
    int item = arr[i];
    count[(item / exp) % size]++;
  }

  // Change count[i] so that count[i] now contains actual
  // position of this digit in output[]
  for (i = 1; i < size; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (i = len - 1; i >= 0; i--)
  {
    output[count[(arr[i] / exp) % size] - 1] = arr[i];
    count[(arr[i] / exp) % size]--;
  }

  // Copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < len; i++)
  {
    arr[i] = output[i];
  }
}

// The main function to that sorts arr[] of size n using
// Radix Sort
int *radix_sort(int arr[], int len)
{
  // Find the maximum number to know number of digits
  int max_value = arr[0];
  for (int i = 1; i < len; i++)
  {
    if (arr[i] > max_value)
      max_value = arr[i];
  }

  // Do counting sort for every digit. Note that instead
  // of passing digit number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; max_value / exp > 0; exp *= 10)
    count_sort(arr, len, exp);

  return arr;
}

// Driver program to test above functions
int main()
{
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int len = sizeof(arr) / sizeof(arr[0]);
  printf("\r\n origin arr1:");
  print_array(arr, len);
  int *result1 = radix_sort(arr, len);
  printf("\r\n sorted:");
  print_array(result1, len);

  int arr2[] = { 3, 4, 15, 2, 2, 123, 2, 3, 3, 237, 10};
  int len2 = sizeof(arr2) / sizeof(arr2[0]);
  printf("\r\n origin arr2:");
  print_array(arr2, len2);
  float startTime = clock();
  int *result2 = radix_sort(arr2, len2);
  printf("\r\n sorted:");
  print_array(result2, len2);
  printf("\r\n time: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));
  printf("\r\n radix_sort end\n");
  return 0;
}

/*
jarry@jarrys-MacBook-Pro radixsort % gcc radix_sort.c
jarry@jarrys-MacBook-Pro radixsort % ./a.out         

 origin arr1:{ 170, 45, 75, 90, 802, 24, 2, 66 }
 sorted:{ 2, 24, 45, 66, 75, 90, 170, 802 }
 origin arr2:{ 3, 4, 15, 2, 2, 123, 2, 3, 3, 237, 10 }
 sorted:{ 2, 2, 2, 3, 3, 3, 4, 10, 15, 123, 237 }
 time: 0.007000 ms.
 radix_sort end
*/