/**
 * Copyright © https://github.com/jarry All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

// 归并排序c语言非递归版，类似二叉树后序遍历
int min(int x, int y)
{
    return x < y ? x : y;
}
void merge_sort(int arr[], int len)
{
    // 新建数组1引用
    int *one = arr;
    // 新建输出空数组
    int *output = (int *)malloc(len * sizeof(int));
    // 外循环从1开始遍历到整个数组
    for (int i = 1; i < len; i++)
    {
        // 内循环从0开始遍历整个数组，步长为2个i
        int step = i * 2;
        for (int start = 0; start < len; start += step)
        {
            int k = start;
            // 根据中间值将数组分为2部分
            // 找出start与最后一位的最小值作为中间数
            int mid = min(start + i, len);
            // 找出步长和最后一位的最小值作为最大值
            int max = min(start + step, len);
            // 定义各个起始下标及结束下标
            int start1 = start, end1 = mid;
            int start2 = mid, end2 = max;
            // 两两比较进行合并，将小的值逐个取出给新数组
            while (start1 < end1 && start2 < end2) {
                output[k++] = one[start1] < one[start2] ? one[start1++] : one[start2++];
            }
            while (start1 < end1) {
                output[k++] = one[start1++];
            }
            while (start2 < end2) {
                output[k++] = one[start2++];
            }
        }
        // 每轮循环之后数组互换
        int *temp = one;
        one = output;
        output = temp;
    }

    // 如果数组轮换后不是原数组，则复制one到新数组中
    if (one != arr)
    {
        for (int j = 0; j < len; j++)
        {
            output[j] = one[j];
        }
        output = one;
    }
    free(output);
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
    // int arr[] = {-2, 1, 15, 6, 23, 71, 24, 92, 8, 90};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("Origin array: \n");
    print_array(arr, len);

    float start_time = clock();

    merge_sort(arr, len);

    printf("\nSorted array: \n");
    print_array(arr, len);
    printf("\ntime: %f ms.", ((clock() - start_time) / CLOCKS_PER_SEC * 1000));
    return 0;
}
/**
jarry@jarrys-MacBook-Pro mergesort % gcc merge_sort_iteration.c
jarry@jarrys-MacBook-Pro mergesort % ./a.out                   
Origin array: 
{ 7, 11, 9, 10, 12, 13, 8 }
Sorted array: 
{ 7, 8, 9, 10, 11, 12, 13 }
time: 0.023000 ms.% 
 */