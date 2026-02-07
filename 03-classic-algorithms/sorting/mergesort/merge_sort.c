/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <math.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right);
void merge_sort(int arr[], int left, int right);

// 合并两个子数组，根据中间值分为2个数组
void merge(int arr[], int left, int mid, int right)
{
    // 初始化左右子数组长度
    int left_len = mid - left + 1;
    int right_len = right - mid;

    // 初始化两个子数组
    int left_arr[left_len], right_arr[right_len];

    /* 复制数据到子数组，根据中间数来复制 */
    for (int i = 0; i < left_len; i++)
    {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < right_len; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    // 合并到数组，从左侧位置开始合并
    int idx = left;
    while (i < left_len && j < right_len)
    {
        if (left_arr[i] <= right_arr[j])
        {
            // 左侧小于右侧，则复制左侧成员
            arr[idx] = left_arr[i];
            i++;
        }
        else
        {
            // 否则复制右侧成员到原数组
            arr[idx] = right_arr[j];
            j++;
        }
        idx++;
    }

    /* 复制左侧剩余成员 */
    while (i < left_len)
    {
        arr[idx] = left_arr[i];
        i++;
        idx++;
    }

    /* 复制右侧剩余成员 */
    while (j < right_len)
    {
        arr[idx] = right_arr[j];
        j++;
        idx++;
    }
}

// 递归调用左右侧进行数组合并
void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        // 中间值为左+右/2取整
        int mid = left + (right - left) / 2;

        // 递归合并左侧
        merge_sort(arr, left, mid);
        // 递归合并右侧
        merge_sort(arr, mid + 1, right);
        // 合并排序
        merge(arr, left, mid, right);
    }
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

int main()
{
    int arr[7] = {7, 11, 9, 10, 12, 13, 8};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("Origin array: \n");
    print_array(arr, len);

    float start_time = clock();

    merge_sort(arr, 0, len - 1);

    printf("\nSorted array: \n");
    print_array(arr, len);
    printf("\ntime: %f ms.", ((clock() - start_time) / CLOCKS_PER_SEC * 1000));
    return 0;
}
/**
jarry@jarrys-mbp mergesort % gcc merge_sort.c
jarry@jarrys-mbp mergesort % ./a.out 
Origin array: 
{ 7, 11, 9, 10, 12, 13, 8 }
Sorted array: 
{ 7, 8, 9, 10, 11, 12, 13 }
time: 0.016000 ms.%   
 */