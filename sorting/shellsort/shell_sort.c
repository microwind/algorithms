/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 希尔排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
int testData[] = {33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 希尔排序基础版本 - 原始Shell序列
 * 
 * 算法原理：
 * 1. 选择一个增量序列，如 n/2, n/4, ..., 1
 * 2. 对每个增量进行插入排序，但只比较相距增量的元素
 * 3. 逐步减小增量，直到增量为1，此时数组基本有序
 * 4. 最后一次插入排序完成整个排序过程
 * 
 * 生活类比：就像整理一副扑克牌，先按间隔几张牌进行分组整理，
 * 然后逐步缩小间隔，最后对相邻的牌进行精细整理
 * 
 * 时间复杂度：平均O(n^1.3)，最坏O(n^2)，取决于增量序列
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 相距增量的元素交换可能改变相等元素的相对位置
 */
void shellSort1(int arr[], int size) {
    printf("shellSort1 original sequence:\n");
    
    // 原始Shell序列：n/2, n/4, ..., 1
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // 对每个增量进行插入排序
        for (int i = gap; i < size; i++) {
            // 关键点：保存当前元素，与前面相距gap的元素比较
            int temp = arr[i];
            int j = i;
            
            // 向前查找插入位置
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            // 插入元素
            arr[j] = temp;
        }
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 希尔排序优化版本 - Knuth序列
 * 
 * 算法思路：
 * 使用Knuth提出的增量序列：1, 4, 13, 40, ...
 * 公式：gap = 3 * gap + 1，然后反向递减
 * 
 * 优化效果：
 * - 更好的增量序列，减少比较次数
 * - 理论上更优的时间复杂度
 * 
 * 时间复杂度：平均O(n^1.25)，比原始序列更优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
void shellSort2(int arr[], int size) {
    printf("shellSort2 Knuth sequence:\n");
    
    // 计算初始增量（Knuth序列）
    int gap = 1;
    while (gap < size / 3) {
        gap = 3 * gap + 1; // 1, 4, 13, 40, 121, ...
    }
    
    // 反向递减处理
    for (; gap > 0; gap /= 3) {
        // 对每个增量进行插入排序
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            
            // 向前查找插入位置
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = temp;
        }
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 希尔排序 - Hibbard序列
 * 
 * 算法思路：
 * 使用Hibbard序列：1, 3, 7, 15, 31, ...
 * 公式：gap = 2^k - 1
 * 
 * 优化效果：
 * - 更好的增量分布
 * 理论时间复杂度为O(n^(3/2))
 * 
 * 时间复杂度：平均O(n^1.5)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
void shellSort3(int arr[], int size) {
    printf("shellSort3 Hibbard sequence:\n");
    
    // 生成Hibbard序列
    int* gaps = (int*)malloc(size * sizeof(int));
    int gapCount = 0;
    int k = 1;
    
    while (1) {
        int gap = (int)(pow(2, k) - 1); // 2^k - 1
        if (gap >= size) break;
        gaps[gapCount++] = gap;
        k++;
    }
    
    // 反向使用序列
    for (int g = gapCount - 1; g >= 0; g--) {
        int gap = gaps[g];
        
        // 对每个增量进行插入排序
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            
            // 向前查找插入位置
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = temp;
        }
    }
    
    free(gaps);
    printArray(arr, size, "排序后数组");
}

/**
 * 希尔排序 - Sedgewick序列
 * 
 * 算法思路：
 * 使用Sedgewick序列：1, 5, 19, 41, 109, ...
 * 结合4^k + 3*2^(k-1) + 1和9*2^k - 9*2^(k/2) + 1
 * 
 * 优化效果：
 * - 最优的增量序列之一
 * - 更好的性能表现
 * 
 * 时间复杂度：平均O(n^1.25)，接近最优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
void shellSort4(int arr[], int size) {
    printf("shellSort4 Sedgewick sequence:\n");
    
    // 生成Sedgewick序列
    // 使用简化版本：1, 5, 19, 41, 109, 209, 505, 929, 2161
    int sedgewickGaps[] = {1, 5, 19, 41, 109, 209, 505, 929, 2161};
    int* gaps = (int*)malloc(size * sizeof(int));
    int gapCount = 0;
    
    for (int i = 0; i < 9; i++) {
        if (sedgewickGaps[i] < size) {
            gaps[gapCount++] = sedgewickGaps[i];
        }
    }
    
    // 反向使用序列
    for (int g = gapCount - 1; g >= 0; g--) {
        int gap = gaps[g];
        
        // 对每个增量进行插入排序
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            
            // 向前查找插入位置
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = temp;
        }
    }
    
    free(gaps);
    printArray(arr, size, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：原始Shell序列
    performanceTest(shellSort1, testData, testDataSize, "原始Shell序列");

    // 测试2：Knuth序列
    performanceTest(shellSort2, testData, testDataSize, "Knuth序列");

    // 测试3：Hibbard序列
    performanceTest(shellSort3, testData, testDataSize, "Hibbard序列");

    // 测试4：Sedgewick序列
    performanceTest(shellSort4, testData, testDataSize, "Sedgewick序列");

    printf("=== 算法对比总结 ===\n");
    printf("1. 原始Shell序列：简单实现，易于理解\n");
    printf("2. Knuth序列：经典优化，性能提升\n");
    printf("3. Hibbard序列：数学优化，理论更优\n");
    printf("4. Sedgewick序列：最优序列，性能最佳\n");

    return 0;
}

/*
打印结果
jarry@Mac shellsort % gcc shell_sort.c -o shell_sort && ./shell_sort
原始Shell序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort1 original sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
原始Shell序列: 0.125ms
原始Shell序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Knuth序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort2 Knuth sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Knuth序列: 0.042ms
Knuth序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Hibbard序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort3 Hibbard sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Hibbard序列: 0.042ms
Hibbard序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Sedgewick序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort4 Sedgewick sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Sedgewick序列: 0.042ms
Sedgewick序列排序结果: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

=== 算法对比总结 ===
1. 原始Shell序列：简单实现，易于理解
2. Knuth序列：经典优化，性能提升
3. Hibbard序列：数学优化，理论更优
4. Sedgewick序列：最优序列，性能最佳
*/
