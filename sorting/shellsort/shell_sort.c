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
 * 希尔排序标准版 - 基于插入排序进行分组排序，步长按1/2缩减
 * 
 * 算法原理：
 * 1. 设置分组增量值（步长）为1/2的数组长度
 * 2. 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
 * 3. 对子序列按照插入排序
 * 4. 调整步长为1/2
 * 
 * 时间复杂度：平均O(n^1.3)，最坏O(n^2)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
void shellSort1(int arr[], int size) {
    printf("shellSort1 original sequence:\n");
    
    // 设置分组增量值（步长）为1/2的数组长度
    int gap = size / 2;
    // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            int current = arr[i];
            int j = i;
            // 对子序列按照插入排序
            while (j >= gap && current < arr[j - gap]) {
                printf("\r\n gap=%d, i=%d, (j-gap)=%d, j=%d", gap, i, (j - gap), j);
                arr[j] = arr[j - gap];
                j -= gap;
            }
            // 交换当前项
            arr[j] = current;
        }
        // 调整步长为1/2
        gap = gap / 2;
    }
    printArray(arr, size, "排序后数组");
}

/**
 * 希尔排序优化版 - 基于插入排序进行分组排序，步长按3倍递减
 * 
 * 算法原理：
 * 1. 设置分组增量值（步长）为1/2的数组长度
 * 2. 初始步长按3倍递增，小于1/3数组长度（Knuth序列）
 * 3. 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
 * 4. 对子序列按照插入排序
 * 5. 步长按3倍缩减
 * 
 * 时间复杂度：平均O(n^1.25)，比原始序列更优
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 插入排序的不稳定性继承
 */
void shellSort2(int arr[], int size) {
    printf("shellSort2 Knuth sequence:\n");
    
    // 设置分组增量值（步长）为1/2的数组长度
    int gap = 1;
    // 初始步长按3倍递增，小于1/3数组长度
    while (gap < size / 3) {
        // Knuth 序列：1, 4, 13, 40...
        gap = gap * 3 + 1;
    }
    // 根据步长得到子序列，如果间隔大于0，则表示还可以继续分组
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            int current = arr[i];
            int j = i - gap;
            // 对子序列按照插入排序
            for (; j >= 0 && arr[j] > current; j -= gap) {
                printf("\r\n gap=%d, i=%d, j=%d, (j+gap)=%d", gap, i, j, (j + gap));
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = current;
        }
        // 步长按3倍缩减
        gap = (gap / 3);
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

/**
 * 希尔排序 - 递归版本（尾递归实现）
 * 
 * 算法思路：
 * 递归处理增量（分组）序列，每个增量插入排序
 * 增量序列采用 gap/2（希尔原始序列）
 * 
 * 递归结构：
 * - 外层尾递归：处理递减的增量序列
 * - 内层循环：对每个位置进行插入排序
 */
void shellSort5(int arr[], int size, int gap) {
    // 递归终止条件
    if (gap <= 0) {
        return;
    }
    
    // 对当前增量（分组）进行插入排序
    for (int i = gap; i < size; i++) {
        int temp = arr[i];
        int j = i;
        
        // 向前查找插入位置
        while (j >= gap && arr[j - gap] > temp) {
            arr[j] = arr[j - gap];
            j -= gap;
        }
        
        // 插入到对应位置
        arr[j] = temp;
    }
    
    // 尾递归调用：递归是函数的最后操作
    shellSort5(arr, size, gap / 2);
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

    // 测试5：递归版本（尾递归）
    printf("shellSort5 递归版本: ");
    printArray(testData, testDataSize, "");
    shellSort5(testData, testDataSize, testDataSize / 2);
    printArray(testData, testDataSize, "递归版本排序后");

    printf("=== 算法对比总结 ===\n");
    printf("1. 原始Shell序列：简单实现，易于理解\n");
    printf("2. Knuth序列：经典优化，性能提升\n");
    printf("3. Hibbard序列：数学优化，理论更优\n");
    printf("4. Sedgewick序列：最优序列，性能最佳\n");
    printf("5. 递归版本：尾递归优化实现\n");

    return 0;
}

/*
打印结果
jarry@Mac shellsort % gcc shell_sort.c -o shell_sort && ./shell_sort
原始Shell序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort1 original sequence:

 gap=5, i=5, (j-gap)=0, j=5
 gap=5, i=9, (j-gap)=4, j=9
 gap=2, i=5, (j-gap)=3, j=5
 gap=2, i=6, (j-gap)=4, j=6
 gap=2, i=8, (j-gap)=6, j=8
 gap=1, i=5, (j-gap)=4, j=5排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
原始Shell序列: 0.007ms
原始Shell序列: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Knuth序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort2 Knuth sequence:

 gap=4, i=5, j=1, (j+gap)=5
 gap=4, i=8, j=4, (j+gap)=8
 gap=1, i=1, j=0, (j+gap)=1
 gap=1, i=2, j=1, (j+gap)=2
 gap=1, i=5, j=4, (j+gap)=5
 gap=1, i=5, j=3, (j+gap)=4
 gap=1, i=5, j=2, (j+gap)=3
 gap=1, i=5, j=1, (j+gap)=2
 gap=1, i=6, j=5, (j+gap)=6
 gap=1, i=9, j=8, (j+gap)=9排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Knuth序列: 0.009ms
Knuth序列: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Hibbard序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort3 Hibbard sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Hibbard序列: 0.004ms
Hibbard序列: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

Sedgewick序列: [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
shellSort4 Sedgewick sequence:
排序后数组: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
Sedgewick序列: 0.003ms
Sedgewick序列: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]

shellSort5 递归版本: : [33, 4, 15, 43, 323454, -7, 105, 1235, 200, 87431]
递归版本排序后: [-7, 4, 15, 33, 43, 105, 200, 1235, 87431, 323454]
=== 算法对比总结 ===
1. 原始Shell序列：简单实现，易于理解
2. Knuth序列：经典优化，性能提升
3. Hibbard序列：数学优化，理论更优
4. Sedgewick序列：最优序列，性能最佳
5. 递归版本：尾递归优化实现
*/
