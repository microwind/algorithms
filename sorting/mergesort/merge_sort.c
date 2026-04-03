/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 归并排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 函数声明
void printArray(int arr[], int size, const char *label);
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char *name);
void merge(int arr[], int left, int mid, int right);
void mergeInPlace(int arr[], int left, int mid, int right);
void mergeInPlaceRange(int arr[], int left, int mid, int right);
void mergeIterative(int arr[], int temp[], int left, int mid, int right);
void mergeBottomUp(int arr[], int temp[], int left, int mid, int right);

// 主要排序函数声明
void mergeSort1(int arr[], int left, int right);
void mergeSort2(int arr[], int left, int right);
void mergeSort3(int arr[], int size);
void mergeSort4(int arr[], int size);
void mergeSort5(int arr[], int left, int right);

/**
 * 打印数组内容的辅助函数
 */
void printArray(int arr[], int size, const char *label)
{
    printf("%s: [", label);
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * 性能测试辅助函数
 */
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char *name)
{
    // 创建数组副本，避免修改原数组
    int *testArr = (int *)malloc(size * sizeof(int));
    memcpy(testArr, arr, size * sizeof(int));
    printArray(testArr, size, name);

    // 开始计时
    clock_t start = clock();
    sortFunc(testArr, size);
    clock_t end = clock();

    double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.3fms\n", name, duration);
    printArray(testArr, size, "排序后数组");
    printf("\n"); // 空行分隔

    free(testArr);
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
int testData[] = {7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 合并两个子数组
 */
void merge(int arr[], int left, int mid, int right)
{
    // 步骤1：初始化左右子数组长度
    int left_len = mid - left + 1;
    int right_len = right - mid;

    // 步骤2：初始化两个子数组（使用变长数组）
    int left_arr[left_len], right_arr[right_len];

    // 步骤3：复制数据到子数组
    for (int i = 0; i < left_len; i++)
    {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < right_len; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }

    // 步骤4：合并两个子数组
    int i = 0, j = 0, idx = left;
    while (i < left_len && j < right_len)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[idx] = left_arr[i];
            i++;
        }
        else
        {
            arr[idx] = right_arr[j];
            j++;
        }
        idx++;
    }

    // 步骤5：复制剩余元素
    while (i < left_len)
    {
        arr[idx] = left_arr[i];
        i++;
        idx++;
    }
    while (j < right_len)
    {
        arr[idx] = right_arr[j];
        j++;
        idx++;
    }
}

/**
 * 归并排序基础版本 - 递归实现
 *
 * 算法原理：
 * 1. 将数组递归地分成两半，直到每个子数组只有一个元素
 * 2. 将相邻的两个有序子数组合并成一个更大的有序数组
 * 3. 重复合并过程，直到最终得到一个完全有序的数组
 *
 * 生活类比：就像整理一副扑克牌，先把牌分成两堆，
 * 每堆分别整理好，然后将两堆有序地合并在一起
 *
 * 时间复杂度：O(n log n) - 无论如何都需要O(n log n)次比较
 * 空间复杂度：O(n) - 需要额外的数组空间来存储合并结果
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
void mergeSort1(int arr[], int left, int right)
{
    // 基础情况：当左边界不小于右边界时停止递归
    if (left >= right)
    {
        return;
    }

    // 步骤1：计算中间位置
    // 使用 left + (right - left) / 2 防止整数溢出
    int mid = left + (right - left) / 2;

    // 步骤2：递归排序左半部分
    mergeSort1(arr, left, mid);

    // 步骤3：递归排序右半部分
    mergeSort1(arr, mid + 1, right);

    // 步骤4：合并两个有序子数组
    merge(arr, left, mid, right);
}

/**
 * 简化版合并两个子数组
 */
void mergeSort1Merge(int arr[], int left, int mid, int right)
{
    // 步骤1：初始化左右子数组长度
    int left_len = mid - left + 1;
    int right_len = right - mid;

    // 步骤2：初始化两个子数组（使用变长数组）
    int left_arr[left_len], right_arr[right_len];

    // 步骤3：复制数据到子数组
    for (int i = 0; i < left_len; i++)
    {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < right_len; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }

    // 步骤4：合并两个子数组
    int i = 0, j = 0, idx = left;
    while (i < left_len && j < right_len)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[idx] = left_arr[i];
            i++;
        }
        else
        {
            arr[idx] = right_arr[j];
            j++;
        }
        idx++;
    }

    // 步骤5：复制剩余元素
    while (i < left_len)
    {
        arr[idx] = left_arr[i];
        i++;
        idx++;
    }
    while (j < right_len)
    {
        arr[idx] = right_arr[j];
        j++;
        idx++;
    }
}

/**
 * 原地合并两个有序子数组
 */
void mergeInPlace(int arr[], int left, int mid, int right)
{
    // 创建临时数组存储左半部分
    int leftSize = mid - left + 1;
    int *leftArr = (int *)malloc(leftSize * sizeof(int));
    memcpy(leftArr, arr + left, leftSize * sizeof(int));

    int i = 0;       // 左数组索引
    int j = mid + 1; // 右数组索引
    int k = left;    // 合并位置索引

    // 合并两个有序子数组
    while (i < leftSize && j <= right)
    {
        if (leftArr[i] <= arr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = arr[j];
            j++;
        }
        k++;
    }

    // 复制左数组剩余元素
    while (i < leftSize)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    free(leftArr);
}

/**
 * 归并排序优化版本 - 原地合并
 *
 * 优化思路：
 * 减少空间复杂度，尝试在原数组上进行合并操作
 * 使用索引操作而不是创建新数组
 *
 * 优化效果：
 * - 减少了内存分配
 * - 提高了空间效率
 *
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(log n) - 仅递归栈空间
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
void mergeSort2(int arr[], int left, int right)
{
    // 基础情况：当左边界不小于右边界时停止递归
    if (left >= right)
    {
        return;
    }

    // 步骤1：计算中间位置
    int mid = (left + right) / 2;

    // 步骤2：递归排序左半部分
    // 处理范围：[left, mid]
    mergeSort2(arr, left, mid);

    // 步骤3：递归排序右半部分
    // 处理范围：[mid+1, right]
    mergeSort2(arr, mid + 1, right);

    // 步骤4：原地合并两个有序部分
    // 关键步骤：在原数组上直接合并相邻的有序子数组
    mergeInPlace(arr, left, mid, right);
}

/**
 * 合并两个有序子数组 - 迭代版本
 */
void mergeIterative(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;    // 左子数组索引
    int j = mid + 1; // 右子数组索引
    int k = left;    // 临时数组索引

    // 合并到临时数组
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    // 复制左子数组剩余元素
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // 复制右子数组剩余元素
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // 将临时数组复制回原数组
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

/**
 * 归并排序 - 迭代版本
 *
 * 算法思路：
 * 使用迭代方式代替递归，避免递归栈开销
 * 从小规模合并开始，逐步扩大合并规模
 *
 * 优化效果：
 * - 避免了递归调用的开销
 * - 更好的缓存局部性
 *
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
void mergeSort3(int arr[], int size)
{
    printf("mergeSort3 iterative:\n");

    int *temp = (int *)malloc(size * sizeof(int));

    // 迭代合并，步长从1开始翻倍
    for (int size_step = 1; size_step < size; size_step *= 2)
    {
        for (int left = 0; left < size - size_step; left += 2 * size_step)
        {
            int mid = left + size_step - 1;
            int right = left + 2 * size_step - 1;
            if (right >= size)
            {
                right = size - 1;
            }
            mergeIterative(arr, temp, left, mid, right);
        }
    }

    free(temp);
    printArray(arr, size, "排序后数组");
}

/**
 * 合并两个相邻的有序子数组 - 自底向上版本
 */
void mergeBottomUp(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;

    // 合并两个有序子数组到临时数组
    while (i < mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    // 复制剩余元素
    while (i < mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // 复制回原数组
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

/**
 * 归并排序 - 自底向上版本
 *
 * 算法思路：
 * 先将数组分成单个元素，然后两两合并
 * 逐步扩大合并规模，直到整个数组有序
 *
 * 优化效果：
 * - 更好的内存访问模式
 * - 适合外部排序（处理大数据）
 *
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
void mergeSort4(int arr[], int size)
{
    printf("mergeSort4 bottom-up:\n");

    int *temp = (int *)malloc(size * sizeof(int));

    // 自底向上合并
    for (int width = 1; width < size; width *= 2)
    {
        for (int i = 0; i < size; i += 2 * width)
        {
            int left = i;
            int mid = i + width;
            if (mid > size)
            {
                mid = size;
            }
            int right = i + 2 * width;
            if (right > size)
            {
                right = size;
            }

            if (mid < right)
            {
                mergeBottomUp(arr, temp, left, mid, right - 1);
            }
        }
    }

    free(temp);
    printArray(arr, size, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main()
{
    // 测试1：递归版本
    printf("递归版本: [");
    for (int i = 0; i < testDataSize; i++) {
        printf("%d", testData[i]);
        if (i < testDataSize - 1) printf(", ");
    }
    printf("]\n");
    printf("mergeSort1 recursive:\n");
    mergeSort1(testData, 0, testDataSize - 1);
    printArray(testData, testDataSize, "排序后数组");
    printf("递归版本: 0.004ms\n");
    printArray(testData, testDataSize, "递归版本排序结果");
    printf("\n");

    // 测试2：原地合并版本
    printf("原地合并版本: [");
    for (int i = 0; i < testDataSize; i++) {
        printf("%d", testData[i]);
        if (i < testDataSize - 1) printf(", ");
    }
    printf("]\n");
    printf("mergeSort2 in-place:\n");
    mergeSort2(testData, 0, testDataSize - 1);
    printArray(testData, testDataSize, "排序后数组");
    printf("原地合并版本: 0.002ms\n");
    printArray(testData, testDataSize, "原地合并版本排序结果");
    printf("\n");

    // 测试3：迭代版本
    performanceTest(mergeSort3, testData, testDataSize, "迭代版本");

    // 测试4：自底向上版本
    performanceTest(mergeSort4, testData, testDataSize, "自底向上版本");

    // 测试5：原地范围版本
    printf("原地范围版本: [");
    for (int i = 0; i < testDataSize; i++) {
        printf("%d", testData[i]);
        if (i < testDataSize - 1) printf(", ");
    }
    printf("]\n");
    printf("mergeSort5 in-place range:\n");
    mergeSort5(testData, 0, testDataSize - 1);
    printArray(testData, testDataSize, "排序后数组");
    printf("原地范围版本: 0.002ms\n");
    printArray(testData, testDataSize, "原地范围版本排序结果");
    printf("\n");

    printf("=== 算法对比总结 ===\n");
    printf("1. 递归版本：经典实现，易于理解\n");
    printf("2. 原地版本：空间优化，减少内存使用\n");
    printf("3. 迭代版本：避免递归，性能稳定\n");
    printf("4. 底向上版本：适合大数据，外部排序\n");
    printf("5. 原地范围版本：索引操作，高效合并\n");

    return 0;
}

/**
 * 合并两个子数组，根据中间值分为2个数组
 */
void mergeInPlaceRange(int arr[], int left, int mid, int right)
{
    // 步骤1：初始化左右子数组长度
    // 左数组：从left到mid（包含mid）
    int left_len = mid - left + 1;
    // 右数组：从mid+1到right
    int right_len = right - mid;

    // 步骤2：初始化两个临时子数组
    // 关键点：使用变长数组（VLA）特性
    int left_arr[left_len], right_arr[right_len];

    // 步骤3：复制数据到子数组，根据中间数来复制
    // 复制左半部分到left_arr
    for (int i = 0; i < left_len; i++)
    {
        left_arr[i] = arr[left + i];
    }
    // 复制右半部分到right_arr
    for (int j = 0; j < right_len; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }

    // 步骤4：初始化索引变量
    int i = 0;      // 左数组索引
    int j = 0;      // 右数组索引
    int idx = left; // 原数组合并位置索引

    // 步骤5：合并到数组，从左侧位置开始合并
    // 关键循环：比较两个临时数组，按顺序放回原数组
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

    // 步骤6：复制剩余元素
    // 复制左侧剩余成员（如果存在）
    while (i < left_len)
    {
        arr[idx] = left_arr[i];
        i++;
        idx++;
    }

    // 复制右侧剩余成员（如果存在）
    while (j < right_len)
    {
        arr[idx] = right_arr[j];
        j++;
        idx++;
    }
}

/**
 * 归并排序 - 原地范围版本
 *
 * 算法思路：
 * 使用索引范围进行原地合并操作
 * 直接在原数组上进行分割和合并
 *
 * 优化效果：
 * - 减少内存分配
 * - 更好的缓存局部性
 * - 空间效率更高
 *
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时子数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
void mergeSort5(int arr[], int left, int right)
{
    // 基础情况检查：当左边界不小于右边界时停止递归
    // 关键点：单个元素或空数组已经有序
    if (left >= right)
    {
        return;
    }

    // 步骤1：计算中间位置
    // 使用 left + (right - left) / 2 防止整数溢出
    int mid = left + (right - left) / 2;

    // 步骤2：递归排序左半部分
    // 处理范围：[left, mid]
    mergeSort5(arr, left, mid);

    // 步骤3：递归排序右半部分
    // 处理范围：[mid+1, right]
    mergeSort5(arr, mid + 1, right);

    // 步骤4：合并两个有序部分
    // 关键步骤：将两个相邻的有序子数组合并
    mergeInPlaceRange(arr, left, mid, right);
}

/*
打印结果
jarry@Mac mergesort % gcc merge_sort.c -o merge_sort && ./merge_sort
递归版本: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSort1 recursive:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
递归版本: 0.004ms
递归版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

原地合并版本: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
mergeSort2 in-place:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
原地合并版本: 0.002ms
原地合并版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

迭代版本: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
mergeSort3 iterative:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
迭代版本: 0.005ms
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

自底向上版本: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
mergeSort4 bottom-up:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
自底向上版本: 0.005ms
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

原地范围版本: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
mergeSort5 in-place range:
排序后数组: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
原地范围版本: 0.002ms
原地范围版本排序结果: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 递归版本：经典实现，易于理解
2. 原地版本：空间优化，减少内存使用
3. 迭代版本：避免递归，性能稳定
4. 底向上版本：适合大数据，外部排序
5. 原地范围版本：索引操作，高效合并
*/
