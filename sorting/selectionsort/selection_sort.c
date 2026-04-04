/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供5种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    for (int i = 0; i < size; i++)
    {
        testArr[i] = arr[i];
    }

    printf("%s原始数组: ", name);
    printArray(testArr, size, "");

    // 开始计时
    clock_t start = clock();
    sortFunc(testArr, size);
    clock_t end = clock();

    double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.3fms\n", name, duration);
    printf("%s排序结果: ", name);
    printArray(testArr, size, "");
    printf("\n"); // 空行分隔

    free(testArr);
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：
int testData[] = {7, 11, 9, 10, 12, 13, 8};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 选择排序基础版本 - 标准版：原地交换
 *
 * 算法原理：
 * 1. 将数组分为两部分：左侧已排序区域，右侧待排序区域
 * 2. 每次从待排序区域中选择最小元素
 * 3. 将最小元素与待排序区域的第一个元素交换
 * 4. 重复以上过程，直到所有元素排序完成
 *
 * ## 实现步骤
 * 1. 外循环遍历数组，每轮确定一个最小值的位置
 * 2. 内循环在未排序区域中查找最小元素
 * 3. 记录最小值和其索引位置
 * 4. 将最小元素交换到当前轮次的起始位置
 *
 * @param arr - 待排序的整数数组
 * @param len - 数组长度
 * @return void* - 排序后的数组指针
 */
void *selectionSort1(int arr[], int len)
{
    printf("selectionSort1 basic:\n");
    // 初始化变量
    int min_value, min_idx, tmp;

    // 外循环：每轮确定一个最小值
    for (int i = 0; i < len - 1; i++)
    {
        // 假设当前位置为最小值
        min_value = arr[i];
        min_idx = i;
        int j = i + 1;

        // 内循环：在未排序区域查找最小值
        for (; j < len; j++)
        {
            if (arr[j] < min_value)
            {
                min_value = arr[j];
                min_idx = j;
            }
        }

        // 输出调试信息
        printf("\r\n i=%d j=%d min_value=%d min_idx=%d", i, j, min_value, min_idx);

        // 交换最小值到正确位置
        if (min_idx != i)
        {
            tmp = arr[i];
            arr[i] = min_value;
            arr[min_idx] = tmp;
        }
    }
    return arr;
}

/**
 * 根据下标移除数组项目的辅助函数
 *
 * ## 实现原理
 * - 从指定索引位置开始，将后续元素向前移动一位
 * - 覆盖要删除的元素，实现数组元素的"删除"
 *
 * ## 实现步骤
 * 1. 从指定索引开始遍历数组
 * 2. 将每个位置的后一个元素前移
 * 3. 数组长度减1（由调用者处理）
 *
 * ## 关键点
 * - 时间复杂度：O(n) - 最坏情况下需要移动n-1个元素
 * - 空间复杂度：O(1) - 原地操作，无需额外空间
 * - 注意：函数不修改数组长度，需要调用者处理
 *
 * @param arr - 整数数组
 * @param len - 数组当前长度
 * @param idx - 要移除的元素索引
 * @return int - 成功返回1
 */
int removeIndex(int arr[], int len, int idx)
{
    // 第一步：边界检查
    // 关键点：确保索引在有效范围内
    if (idx < 0 || idx >= len)
    {
        return 0; // 索引无效
    }

    // 第二步：元素前移
    // 关键点：从idx开始，将后续元素逐个前移
    for (int i = idx; i < len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    return 1;
}

/**
 * 选择排序新建数组版本 - 无需交换
 *
 * 算法思路：
 * 1. 创建一个新数组来存储排序结果
 * 2. 每次从原数组中找到最小值
 * 3. 将最小值添加到新数组
 * 4. 从原数组中删除该最小值
 * 5. 重复直到原数组为空
 *
 * ## 实现步骤
 * 1. 初始化新数组和索引
 * 2. 外循环控制选择轮数
 * 3. 内循环查找当前最小值
 * 4. 将最小值添加到新数组
 * 5. 从原数组中移除已选择的元素
 * 6. 调整循环变量以适应数组长度变化
 *
 * @param arr - 待排序的整数数组
 * @param len - 数组长度
 * @return int* - 排序后的新数组指针
 */
int *selectionSort2(int arr[], int len)
{
    printf("selectionSort2 new array:\n");
    // 初始化变量
    int min_value, min_idx;
    int *new_arr = (int *)malloc(len * sizeof(int));
    int new_idx = 0;
    int arr_len = len;

    // 外循环：每轮选择一个最小值
    for (int i = 0; i < arr_len; i++)
    {
        // 假设当前位置为最小值
        min_value = arr[i];
        min_idx = i;
        int j = i + 1;

        // 内循环：在剩余元素中查找最小值
        for (; j < arr_len; j++)
        {
            if (arr[j] < min_value)
            {
                min_value = arr[j];
                min_idx = j;
            }
        }

        // 输出调试信息
        printf("\r\n i=%d j=%d min_value=%d min_idx=%d", i, j, min_value, min_idx);

        // 添加最小值到新数组
        new_arr[new_idx++] = min_value;

        // 从原数组中移除已选择的元素
        removeIndex(arr, arr_len, min_idx);
        arr_len--; // 调整长度
        i--;       // 补偿索引变化
    }

    return new_arr;
}

/**
 * 选择排序降序版本
 *
 * 算法思路：
 * 与基础版本相反，每次选择最大元素
 * 将最大元素与待排序区域的第一个元素交换
 *
 * ## 实现步骤
 * 1. 外循环控制排序轮数，每轮确定一个最大值的位置
 * 2. 内循环在未排序区域中查找最大元素
 * 3. 记录最大值和其索引位置
 * 4. 将最大元素交换到当前轮次的起始位置
 */
void selectionSort3(int arr[], int size)
{
    printf("selectionSort3 descending:\n");

    // 外循环：每轮确定一个最大值
    for (int i = 0; i < size - 1; i++)
    {
        // 假设当前位置为最大值
        int maxIndex = i;

        // 内循环：在未排序区域查找最大值
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] > arr[maxIndex])
            {
                maxIndex = j;
            }
        }

        // 交换最大元素到正确位置
        if (maxIndex != i)
        {
            int tmp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = tmp;
        }
    }
    printf("排序后数组: ");
    printArray(arr, size, "");
}

/**
 * 选择排序优化版本 - 双向选择
 *
 * 优化思路：
 * 每轮同时选择最小和最大元素
 * 将最小元素放到左侧，最大元素放到右侧
 * 减少排序轮数，提高效率
 *
 * ## 实现步骤
 * 1. 初始化左右边界指针
 * 2. 外循环控制排序轮数，同时处理两端
 * 3. 内循环在未排序区域中查找最小和最大元素
 * 4. 交换最小元素到左侧，最大元素到右侧
 * 5. 调整边界指针
 *
 */
void selectionSort4(int arr[], int size)
{
    printf("selectionSort4 bidirectional:\n");
    int left = 0;
    int right = size - 1;

    // 外循环：同时处理左右两端
    while (left < right)
    {
        int minIndex = left;
        int maxIndex = left;

        // 内循环：同时查找最小和最大元素
        for (int i = left; i <= right; i++)
        {
            if (arr[i] < arr[minIndex])
            {
                minIndex = i;
            }
            if (arr[i] > arr[maxIndex])
            {
                maxIndex = i;
            }
        }

        // 交换最小元素到左侧
        if (minIndex != left)
        {
            int tmp = arr[left];
            arr[left] = arr[minIndex];
            arr[minIndex] = tmp;
        }

        // 处理最大元素位置变化的特殊情况
        if (maxIndex == left)
        {
            maxIndex = minIndex;
        }

        // 交换最大元素到右侧
        if (maxIndex != right)
        {
            int tmp = arr[right];
            arr[right] = arr[maxIndex];
            arr[maxIndex] = tmp;
        }

        left++;
        right--;
    }
    printf("排序后数组: ");
    printArray(arr, size, "");
}

/**
 * 堆化辅助函数
 */
void heapify(int arr[], int n, int i)
{
    int largest = i;       // 初始化最大元素为根节点
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // 如果右子节点大于当前最大节点
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // 如果最大节点不是根节点，交换并继续堆化
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

/**
 * 选择排序 - 堆优化版本
 *
 * 算法思路：
 * 利用堆的性质来快速找到最大/最小元素
 * 每次从堆顶取出最大/最小元素
 * 重新调整堆结构
 *
 * ## 实现步骤
 * 1. 构建最大堆
 * 2. 逐个取出堆顶元素（最大值）
 * 3. 将堆顶元素与末尾元素交换
 * 4. 重新调整堆结构
 * 5. 重复直到堆为空
 */
void selectionSort5(int arr[], int size)
{
    printf("selectionSort5 heap optimized:\n");

    // 构建最大堆
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }

    // 逐个取出堆顶元素
    for (int i = size - 1; i > 0; i--)
    {
        // 交换堆顶与末尾元素
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 重新调整堆
        heapify(arr, i, 0);
    }

    printf("排序后数组: ");
    printArray(arr, size, "");
}

// ==================== 算法测试和性能对比 ====================

int main()
{

    printf("\n=== 算法性能对比 ===\n");

    // 测试1：基础选择版本（直接测试，不使用performanceTest）
    printf("基础选择版本原始数组: ");
    printArray(testData, testDataSize, "");
    int *temp_arr1 = (int *)malloc(testDataSize * sizeof(int));
    for (int i = 0; i < testDataSize; i++)
    {
        temp_arr1[i] = testData[i];
    }
    clock_t start1 = clock();
    selectionSort1(temp_arr1, testDataSize);
    clock_t end1 = clock();
    double duration1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC * 1000;
    printf("基础选择版本: %.3fms\n", duration1);
    printf("基础选择版本排序结果: ");
    printArray(temp_arr1, testDataSize, "");
    free(temp_arr1);
    printf("\n");

    // 测试2：新建数组版本（直接测试，不使用performanceTest）
    printf("新建数组版本原始数组: ");
    printArray(testData, testDataSize, "");
    int *temp_arr2 = (int *)malloc(testDataSize * sizeof(int));
    for (int i = 0; i < testDataSize; i++)
    {
        temp_arr2[i] = testData[i];
    }
    clock_t start2 = clock();
    int *result = selectionSort2(temp_arr2, testDataSize);
    clock_t end2 = clock();
    double duration2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC * 1000;
    printf("新建数组版本: %.3fms\n", duration2);
    printf("新建数组版本排序结果: ");
    printArray(result, testDataSize, "");
    free(result);
    free(temp_arr2);
    printf("\n");

    // 测试3：降序版本
    performanceTest(selectionSort3, testData, testDataSize, "降序版本");

    // 测试4：双向选择版本
    performanceTest(selectionSort4, testData, testDataSize, "双向选择版本");

    // 测试5：堆优化版本
    performanceTest(selectionSort5, testData, testDataSize, "堆优化版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 基础版本：标准版，原地交换，包含详细调试信息\n");
    printf("2. 新建数组版本：无需交换，避免交换操作\n");
    printf("3. 降序版本：展示算法灵活性，可按需排序\n");
    printf("4. 双向版本：同时选择最大最小，效率提升\n");
    printf("5. 堆优化版本：利用堆结构，复杂度优化\n");

    return 0;
}

/*
打印结果
jarry@Mac selectionsort % gcc selection_sort.c -o selection_sort && ./selection_sort

=== 算法性能对比 ===
基础选择版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selectionSort1 basic:

 i=0 j=7 min_value=7 min_idx=0
 i=1 j=7 min_value=8 min_idx=6
 i=2 j=7 min_value=9 min_idx=2
 i=3 j=7 min_value=10 min_idx=3
 i=4 j=7 min_value=11 min_idx=6
 i=5 j=7 min_value=12 min_idx=6基础选择版本: 0.012ms
基础选择版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

新建数组版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selectionSort2 new array:

 i=0 j=7 min_value=7 min_idx=0
 i=0 j=6 min_value=8 min_idx=5
 i=0 j=5 min_value=9 min_idx=1
 i=0 j=4 min_value=10 min_idx=1
 i=0 j=3 min_value=11 min_idx=0
 i=0 j=2 min_value=12 min_idx=0
 i=0 j=1 min_value=13 min_idx=0新建数组版本: 0.007ms
新建数组版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

降序版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selectionSort3 descending:
排序后数组: : [13, 12, 11, 10, 9, 8, 7]
降序版本: 0.002ms
降序版本排序结果: : [13, 12, 11, 10, 9, 8, 7]

双向选择版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selectionSort4 bidirectional:
排序后数组: : [7, 8, 9, 10, 11, 12, 13]
双向选择版本: 0.004ms
双向选择版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

堆优化版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selectionSort5 heap optimized:
排序后数组: : [7, 8, 9, 10, 11, 12, 13]
堆优化版本: 0.003ms
堆优化版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 基础版本：标准版，原地交换，包含详细调试信息
2. 新建数组版本：无需交换，避免交换操作
3. 降序版本：展示算法灵活性，可按需排序
4. 双向版本：同时选择最大最小，效率提升
5. 堆优化版本：利用堆结构，复杂度优化
*/
