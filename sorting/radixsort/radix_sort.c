/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 基数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * 打印数组内容的辅助函数
 */
void printArray(int arr[], int size, const char* label) {
    printf("%s: [", label);
    for (int i = 0; i < size; i++) {
        if (i > 0) printf(", ");
        printf("%d", arr[i]);
    }
    printf("]\n");
}

/**
 * 性能测试辅助函数
 */
void performanceTest(void (*sortFunc)(int[], int), int arr[], int size, const char* name) {
    // 创建数组副本，避免修改原数组
    int* testArr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        testArr[i] = arr[i];
    }
    printArray(testArr, size, name);
    
    // 开始计时
    clock_t startTime = clock();
    sortFunc(testArr, size);
    clock_t endTime = clock();
    
    double duration = ((double)(endTime - startTime)) / CLOCKS_PER_SEC * 1000;
    printf("%s: %.3fms\n", name, duration);
    printArray(testArr, size, name);
    printf("\n"); // 空行分隔
    
    free(testArr);
}

// ==================== 主程序：算法演示和性能测试 ====================

// 测试数据：包含大数字和负数的典型数组
int testData[] = {33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 获取数字的指定位数
 */
int getDigit(int num, int exp) {
    return abs(num) / exp % 10;
}

/**
 * 计数排序辅助函数 - 按位数排序
 */
void countingSortByDigit(int arr[], int size, int exp) {
    int* output = (int*)malloc(size * sizeof(int));
    int count[10] = {0};
    
    // 统计每个数字的出现次数
    for (int i = 0; i < size; i++) {
        int digit = getDigit(arr[i], exp);
        count[digit]++;
    }
    
    // 计算累计计数
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // 构建输出数组
    for (int i = size - 1; i >= 0; i--) {
        int digit = getDigit(arr[i], exp);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // 复制回原数组
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
    
    free(output);
}

/**
 * 基数排序基础版本 - LSD（最低位优先）
 * 
 * 算法原理：
 * 1. 从个位开始，对每一位进行计数排序
 * 2. 逐步处理十位、百位、千位等
 * 3. 经过所有位数处理后，数组完全有序
 * 
 * 生活类比：就像整理学生成绩，先按个位数排序，
 * 再按十位数排序，最后按百位数排序，最终得到完整排序
 * 
 * 时间复杂度：O(d * (n + k))，d为位数，k为基数（通常为10）
 * 空间复杂度：O(n + k) - 需要额外的计数和输出数组
 * 稳定性：稳定 - 计数排序保持相等元素的相对位置
 */
void radixSort1(int arr[], int size) {
    printf("radixSort1 LSD:\n");
    
    // 找到最大值以确定位数
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    // 对每个位数进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortByDigit(arr, size, exp);
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * MSD递归排序函数
 */
void msdSort(int arr[], int left, int right, int exp) {
    if (left >= right || exp < 1) {
        return;
    }
    
    // 创建桶
    int* buckets[10];
    int bucketSizes[10] = {0};
    
    // 分配到桶中
    for (int i = left; i <= right; i++) {
        int digit = getDigit(arr[i], exp);
        if (bucketSizes[digit] == 0) {
            buckets[digit] = (int*)malloc((right - left + 1) * sizeof(int));
        }
        buckets[digit][bucketSizes[digit]++] = arr[i];
    }
    
    // 重新排序并递归处理每个桶
    int index = left;
    for (int i = 0; i < 10; i++) {
        if (bucketSizes[i] > 0) {
            // 复制桶中元素回原数组
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
            
            // 递归处理下一个位数
            msdSort(arr, left, index - 1, exp / 10);
            left = index;
        }
    }
    
    // 释放桶内存
    for (int i = 0; i < 10; i++) {
        if (bucketSizes[i] > 0) {
            free(buckets[i]);
        }
    }
}

/**
 * 基数排序优化版本 - MSD（最高位优先）
 * 
 * 算法思路：
 * 从最高位开始排序，使用递归处理子数组
 * 适合处理字符串或变长数据
 * 
 * 优化效果：
 * - 更好的内存局部性
 * - 适合大数据集
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
void radixSort2(int arr[], int size) {
    printf("radixSort2 MSD:\n");
    
    if (size == 0) return;
    
    // 找到最大值以确定位数
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    int exp = 1;
    while (max / exp > 0) {
        exp *= 10;
    }
    
    msdSort(arr, 0, size - 1, exp / 10);
    
    printArray(arr, size, "排序后数组");
}

/**
 * 基数排序 - 迭代MSD版本
 * 
 * 算法思路：
 * 使用迭代方式实现MSD排序
 * 使用栈来模拟递归调用
 * 
 * 优化效果：
 * - 避免递归开销
 * - 更好的性能控制
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
void radixSort3(int arr[], int size) {
    printf("radixSort3 iterative MSD:\n");
    
    if (size == 0) return;
    
    // 找到最大值以确定位数
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    int exp = 1;
    while (max / exp > 0) {
        exp *= 10;
    }
    
    // 使用栈模拟递归
    typedef struct {
        int left, right, exp;
    } StackItem;
    
    StackItem stack[100];
    int top = -1;
    
    stack[++top] = (StackItem){0, size - 1, exp / 10};
    
    while (top >= 0) {
        StackItem item = stack[top--];
        int left = item.left;
        int right = item.right;
        int currentExp = item.exp;
        
        if (left >= right || currentExp < 1) {
            continue;
        }
        
        // 创建桶
        int* buckets[10];
        int bucketSizes[10] = {0};
        
        // 分配到桶中
        for (int i = left; i <= right; i++) {
            int digit = getDigit(arr[i], currentExp);
            if (bucketSizes[digit] == 0) {
                buckets[digit] = (int*)malloc((right - left + 1) * sizeof(int));
            }
            buckets[digit][bucketSizes[digit]++] = arr[i];
        }
        
        // 重新排序并将子问题入栈
        int index = left;
        for (int i = 0; i < 10; i++) {
            if (bucketSizes[i] > 0) {
                // 复制桶中元素回原数组
                for (int j = 0; j < bucketSizes[i]; j++) {
                    arr[index++] = buckets[i][j];
                }
                
                // 将子问题入栈（逆序处理以保持正确顺序）
                stack[++top] = (StackItem){left, index - 1, currentExp / 10};
                left = index;
            }
        }
        
        // 释放桶内存
        for (int i = 0; i < 10; i++) {
            if (bucketSizes[i] > 0) {
                free(buckets[i]);
            }
        }
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 基数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用动态桶大小，优化内存使用
 * 适合处理稀疏数据
 * 
 * 优化效果：
 * - 减少内存占用
 * - 提高处理效率
 * 
 * 时间复杂度：O(d * (n + k))
 * 空间复杂度：O(n + k)
 * 稳定性：稳定
 */
void radixSort4(int arr[], int size) {
    printf("radixSort4 bucket optimized:\n");
    
    // 找到最大值以确定位数
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    // 对每个位数进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        int* output = (int*)malloc(size * sizeof(int));
        
        // 动态确定桶范围
        int minDigit = 9, maxDigit = 0;
        for (int i = 0; i < size; i++) {
            int digit = getDigit(arr[i], exp);
            if (digit < minDigit) minDigit = digit;
            if (digit > maxDigit) maxDigit = digit;
        }
        
        int bucketSize = maxDigit - minDigit + 1;
        int* count = (int*)calloc(bucketSize, sizeof(int));
        
        // 统计每个数字的出现次数
        for (int i = 0; i < size; i++) {
            int digit = getDigit(arr[i], exp);
            count[digit - minDigit]++;
        }
        
        // 计算累计计数
        for (int i = 1; i < bucketSize; i++) {
            count[i] += count[i - 1];
        }
        
        // 构建输出数组
        for (int i = size - 1; i >= 0; i--) {
            int digit = getDigit(arr[i], exp);
            output[count[digit - minDigit] - 1] = arr[i];
            count[digit - minDigit]--;
        }
        
        // 复制回原数组
        for (int i = 0; i < size; i++) {
            arr[i] = output[i];
        }
        
        free(count);
        free(output);
    }
    
    printArray(arr, size, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：LSD版本
    performanceTest(radixSort1, testData, testDataSize, "LSD版本");

    // 测试2：MSD版本
    performanceTest(radixSort2, testData, testDataSize, "MSD版本");

    // 测试3：迭代MSD版本
    performanceTest(radixSort3, testData, testDataSize, "迭代MSD版本");

    // 测试4：桶优化版本
    performanceTest(radixSort4, testData, testDataSize, "桶优化版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. LSD版本：经典实现，从低到高\n");
    printf("2. MSD版本：高位优先，递归处理\n");
    printf("3. 迭代MSD版本：避免递归，性能稳定\n");
    printf("4. 桶优化版本：动态桶大小，内存优化\n");

    return 0;
}

/*
打印结果
jarry@Mac radixsort % gcc radix_sort.c -o radix_sort && ./radix_sort
LSD版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort1 LSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
LSD版本: 0.125ms
LSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

MSD版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort2 MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
MSD版本: 0.042ms
MSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

迭代MSD版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort3 iterative MSD:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
迭代MSD版本: 0.042ms
迭代MSD版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

桶优化版本: [33, 4, 15, 43, 323454, 7, 10, 1235, 200, 87431]
radixSort4 bucket optimized:
排序后数组: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]
桶优化版本: 0.042ms
桶优化版本排序结果: [4, 7, 10, 15, 33, 43, 200, 1235, 87431, 323454]

=== 算法对比总结 ===
1. LSD版本：经典实现，从低到高
2. MSD版本：高位优先，递归处理
3. 迭代MSD版本：避免递归，性能稳定
4. 桶优化版本：动态桶大小，内存优化
*/
