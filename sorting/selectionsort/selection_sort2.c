/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 选择排序算法实现
 * 提供双向选择优化版本，适合不同场景和性能需求
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

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
 * 选择排序双向选择优化版本
 *
 * 算法原理：
 * 1. 每轮同时选择最小和最大元素
 * 2. 将最小元素放到左侧，最大元素放到右侧
 * 3. 减少排序轮数，提高效率
 *
 * ## 实现步骤
 * 1. 初始化左右边界指针
 * 2. 外循环控制排序轮数，同时处理两端
 * 3. 内循环在未排序区域查找最小和最大元素
 * 4. 交换最小元素到左侧，最大元素到右侧
 * 5. 调整边界指针
 *
 * @param arr - 待排序的整数数组
 * @param len - 数组长度
 */
void selection_sort(int arr[], int len)
{
    printf("selection_sort bidirectional:");
    int min_value, max_value, min_idx, max_idx;
    int min_list_idx, max_list_idx;
    
    for (int i = 0; i < len - 1; i++)
    {
        // 初始化最小值和下标
        min_idx = i;
        min_value = arr[min_idx];
        // 初始化最大值和下标
        max_idx = i;
        max_value = arr[max_idx];
        
        // 设置左右边界交换位置
        // 左边界从前往后递增，右边界从后往前递减
        min_list_idx = min_idx;
        max_list_idx = len - 1 - i;
        
        // 如果左右边界相遇，说明只剩一个元素，终止循环
        if (min_list_idx == max_list_idx)
        {
            break;
        }

        // 在待排序区间查找最小和最大值
        // 待排序区间：从i+1到len-i-1
        int j;
        for (j = i + 1; j < len - i; j++)
        {
            // 更新最小值
            if (arr[j] < min_value)
            {
                min_idx = j;
                min_value = arr[min_idx];
            }
            // 更新最大值
            else if (arr[j] > max_value)
            {
                max_idx = j;
                max_value = arr[max_idx];
            }
        }

        printf("\r\n i=%d j=%d min=%d max=%d min_idx=%d max_idx=%d min_list_idx=%d max_list_idx=%d arr[]=",
               i, j, min_value, max_value, min_idx, max_idx, min_list_idx, max_list_idx);
        for (int k = 0; k < len; k++) {
            printf("%d", arr[k]);
            if (k < len - 1) printf(", ");
        }
        printf(")");

        // 执行双向交换，先交换最小值到左边界
        arr[min_idx] = arr[min_list_idx];
        arr[min_list_idx] = min_value;
        
        // 处理最大值位置变化的特殊情况
        if (arr[min_idx] == max_value)
        {
            max_idx = min_idx;
        }
        
        // 交换最大值到右边界
        arr[max_idx] = arr[max_list_idx];
        arr[max_list_idx] = max_value;
    }
}

int main()
{
    // 测试：双向选择优化版本
    performanceTest(selection_sort, testData, testDataSize, "双向选择优化版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 双向选择优化版本：同时选择最大最小，效率提升\n");
    
    return 0;
}

/*打印结果
jarry@Mac selectionsort % gcc selection_sort2.c -o selection_sort2 && ./selection_sort2
双向选择优化版本原始数组: : [7, 11, 9, 10, 12, 13, 8]
selection_sort bidirectional:
 i=0 j=7 min=7 max=13 min_idx=0 max_idx=5 min_list_idx=0 max_list_idx=6 arr[]=7, 11, 9, 10, 12, 13, 8)
 i=1 j=6 min=8 max=12 min_idx=5 max_idx=4 min_list_idx=1 max_list_idx=5 arr[]=7, 11, 9, 10, 12, 8, 13)
 i=2 j=5 min=9 max=11 min_idx=2 max_idx=4 min_list_idx=2 max_list_idx=4 arr[]=7, 8, 9, 10, 11, 12, 13)双向选择优化版本: 0.008ms
双向选择优化版本排序结果: : [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 双向选择优化版本：同时选择最大最小，效率提升
*/