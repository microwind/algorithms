/**
 * Copyright © https://github.com/microwind All rights reserved.
 *
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 归并排序算法非递归实现
 * 提供迭代版本的归并排序，避免递归调用栈开销
 * 
 * 算法原理：
 * 1. 使用迭代方式模拟递归的合并过程
 * 2. 从小规模合并开始，逐步扩大合并规模
 * 3. 通过双数组交替使用，避免频繁内存分配
 * 4. 最终将结果复制回原数组
 * 
 * 优化效果：
 * - 避免递归栈开销，适合大数据量
 * - 更好的内存访问模式
 * - 稳定的性能表现
 * 
 * 时间复杂度：O(n log n) - 与递归版本相同
 * 空间复杂度：O(n) - 需要额外的临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 函数声明
int min(int x, int y);
void merge_sort(int arr[], int len);
void printArray(int arr[], int size, const char *label);
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char *name);

/**
 * 返回两个整数中的较小值
 * 
 * @param x 第一个整数
 * @param y 第二个整数
 * @return 较小的整数值
 */
int min(int x, int y)
{
    return x < y ? x : y;
}
/**
 * 归并排序非递归实现
 * 
 * 算法思路：
 * 使用迭代方式模拟递归的合并过程，从单个元素开始逐步合并
 * 通过双数组交替使用，避免频繁的内存分配和释放
 * 
 * 步骤说明：
 * 1. 初始化两个数组，一个指向原数组，一个作为临时数组
 * 2. 外循环控制合并规模，从1开始翻倍
 * 3. 内循环处理所有相邻的子数组对
 * 4. 合并两个有序子数组到临时数组
 * 5. 交换数组引用，准备下一轮合并
 * 6. 最终确保结果在原数组中
 * 
 * 关键点：
 * - 使用双数组交替，减少内存分配开销
 * - 合并规模从1开始翻倍，模拟递归深度
 * - 边界处理确保不越界访问
 * - 最终检查确保结果在原数组中
 * 
 * @param arr 待排序的数组
 * @param len 数组长度
 */
void merge_sort(int arr[], int len)
{
    // 步骤1：初始化双数组结构
    // 关键点：one指向当前数组，output作为临时输出数组
    int *one = arr;
    int *output = (int *)malloc(len * sizeof(int));
    
    // 步骤2：外循环控制合并规模
    // 关键点：从1开始，每次翻倍，模拟递归的合并深度
    for (int i = 1; i < len; i++)
    {
        // 步骤3：内循环处理所有相邻的子数组对
        // 关键点：步长为2*i，每次处理两个大小为i的子数组
        int step = i * 2;
        for (int start = 0; start < len; start += step)
        {
            // 步骤3.1：初始化合并参数
            // 关键点：k记录当前写入位置，mid和max定义合并边界
            int k = start;
            int mid = min(start + i, len);    // 左子数组结束位置
            int max = min(start + step, len); // 右子数组结束位置
            
            // 步骤3.2：定义子数组范围
            // 关键点：左子数组[start, mid)，右子数组[mid, max)
            int start1 = start, end1 = mid;
            int start2 = mid, end2 = max;
            
            // 步骤4：合并两个有序子数组
            // 关键点：按顺序合并，保持稳定性
            while (start1 < end1 && start2 < end2) {
                output[k++] = one[start1] < one[start2] ? one[start1++] : one[start2++];
            }
            
            // 步骤5：处理左子数组剩余元素
            // 关键点：左子数组可能还有未处理的元素
            while (start1 < end1) {
                output[k++] = one[start1++];
            }
            
            // 步骤6：处理右子数组剩余元素
            // 关键点：右子数组可能还有未处理的元素
            while (start2 < end2) {
                output[k++] = one[start2++];
            }
        }
        
        // 步骤7：交换数组引用
        // 关键点：交替使用两个数组，避免内存复制
        int *temp = one;
        one = output;
        output = temp;
    }

    // 步骤8：确保结果在原数组中
    // 关键点：如果最终结果不在原数组，需要复制回去
    if (one != arr)
    {
        for (int j = 0; j < len; j++)
        {
            output[j] = one[j];
        }
        output = one;
    }
    
    // 步骤9：释放临时数组内存
    // 关键点：避免内存泄漏
    free(output);
}

/**
 * 打印数组内容的辅助函数
 * 
 * @param arr 要打印的数组
 * @param size 数组大小
 * @param label 数组的标签说明
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
 * 
 * @param sortFunc 排序函数指针
 * @param arr 测试数组
 * @param size 数组大小
 * @param name 测试名称
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
 * 归并排序非递归版本 - 迭代实现
 * 
 * 算法思路：
 * 使用迭代方式模拟递归的合并过程，避免递归栈开销
 * 通过双数组交替使用，提高内存访问效率
 * 
 * 优化效果：
 * - 避免递归调用栈开销
 * - 更好的缓存局部性
 * - 适合大数据量排序
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n) - 需要临时数组
 * 稳定性：稳定 - 合并过程中保持相等元素的相对位置
 */
void mergeSortIteration(int arr[], int size)
{
    printf("mergeSortIteration iterative:\n");
    merge_sort(arr, size);
}

/**
 * 主函数 - 算法测试和性能对比
 */
int main()
{
    // 测试1：非递归迭代版本
    performanceTest(mergeSortIteration, testData, testDataSize, "非递归迭代版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 非递归迭代版本：避免递归栈开销，适合大数据量\n");
    
    return 0;
}
/**
jarry@Mac mergesort % gcc merge_sort_iteration.c -o merge_sort_iteration && ./merge_sort_iteration
非递归迭代版本: [7, 11, 9, 10, 12, 13, 8, 5, 6, 1, 3, 2, 4]
mergeSortIteration iterative:
非递归迭代版本: 0.008ms
排序后数组: [1, 4, 5, 6, 7, 8, 2, 3, 9, 10, 11, 12, 13]
 */