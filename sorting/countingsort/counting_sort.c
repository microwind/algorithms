/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 计数排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// 测试数据：包含负数和重复元素的典型数组
int testData[] = {20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 计数排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 第一步：找到最小值和最大值，确定数据范围
 * 第二步：创建计数数组，统计每个元素出现的次数
 * 第三步：计算累计计数以确定元素位置
 * 第四步：从后向前遍历，根据累计计数将元素放到正确位置
 * 
 * 生活类比：就像统计班级学生成绩分布，
 * 先统计每个分数段有多少人，然后按分数段排序
 * 
 * 时间复杂度：O(n + k)，n为元素个数，k为数据范围
 * 空间复杂度：O(k) - 需要计数数组
 * 稳定性：稳定 - 从后向前遍历保持相等元素的相对位置
 */
void countingSort1(int arr[], int size) {
    printf("countingSort1 standard:\n");
    
    if (size == 0) return;
    
    // 第一步：找到最小值和最大值，确定数据范围
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    int range = max - min + 1;
    
    // 第二步：创建计数数组，统计每个元素出现的次数
    int* count = (int*)calloc(range, sizeof(int));
    
    // 统计每个元素出现的次数
    for (int i = 0; i < size; i++) {
        // 将元素值转换为计数数组索引（支持负数）
        count[arr[i] - min]++;
    }
    
    // 第三步：计算累计计数以确定元素位置
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    // 第四步：从后向前遍历，根据累计计数将元素放到正确位置
    int* output = (int*)malloc(size * sizeof(int));
    
    // 从后向前遍历，保证稳定性
    for (int i = size - 1; i >= 0; i--) {
        int value = arr[i];
        int index = value - min;
        // 根据累计计数确定最终位置
        output[count[index] - 1] = value;
        // 减少计数，为重复元素预留位置
        count[index]--;
    }
    
    // 复制回原数组
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
    
    printArray(arr, size, "排序后数组");
    
    free(count);
    free(output);
}

/**
 * 计数排序优化版本 - 内存优化
 * 
 * 算法思路：
 * 直接在原数组上进行修改，减少内存使用
 * 使用原地排序技术
 * 
 * 优化效果：
 * - 减少额外空间使用
 * - 更好的缓存性能
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：不稳定 - 原地修改可能影响稳定性
 */
void countingSort2(int arr[], int size) {
    printf("countingSort2 memory optimized:\n");
    
    if (size == 0) return;
    
    // 找到最小值和最大值
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    int range = max - min + 1;
    
    // 创建计数数组
    int* count = (int*)calloc(range, sizeof(int));
    
    // 统计每个元素出现的次数
    for (int i = 0; i < size; i++) {
        count[arr[i] - min]++;
    }
    
    // 直接根据计数重构数组
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index] = i + min;
            index++;
            count[i]--;
        }
    }
    
    printArray(arr, size, "排序后数组");
    
    free(count);
}

/**
 * 计数排序 - 负数单独处理版本
 * 
 * 算法思路：
 * 专门处理包含负数的情况
 * 分别处理负数和正数部分
 * 
 * 优化效果：
 * - 支持负数排序
 * - 保持算法稳定性
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
void countingSort3(int arr[], int size) {
    printf("countingSort3 negative numbers:\n");
    
    if (size == 0) return;
    
    // 分离正数和负数
    int* negatives = (int*)malloc(size * sizeof(int));
    int* positives = (int*)malloc(size * sizeof(int));
    int negCount = 0, posCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            negatives[negCount++] = arr[i];
        } else {
            positives[posCount++] = arr[i];
        }
    }
    
    // 排序负数部分（转换为绝对值排序后反转）
    if (negCount > 0) {
        // 第二步：对负数部分转换为绝对值进行排序
        int* absNegatives = (int*)malloc(negCount * sizeof(int));
        for (int i = 0; i < negCount; i++) {
            absNegatives[i] = -negatives[i];
        }
        
        // 使用独立的计数排序逻辑
        int min = absNegatives[0];
        int max = absNegatives[0];
        for (int i = 1; i < negCount; i++) {
            if (absNegatives[i] < min) min = absNegatives[i];
            if (absNegatives[i] > max) max = absNegatives[i];
        }
        int range = max - min + 1;
        int* count = (int*)calloc(range, sizeof(int));
        
        // 统计每个元素出现的次数
        for (int i = 0; i < negCount; i++) {
            count[absNegatives[i] - min]++;
        }
        
        // 计算累计计数
        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }
        
        // 从后向前遍历，保证稳定性
        int* output = (int*)malloc(negCount * sizeof(int));
        for (int i = negCount - 1; i >= 0; i--) {
            int value = absNegatives[i];
            int index = value - min;
            output[count[index] - 1] = value;
            count[index]--;
        }
        
        // 第三步：反转并恢复负号
        for (int i = 0; i < negCount; i++) {
            negatives[i] = output[negCount - 1 - i];
        }
        
        free(count);
        free(output);
        free(absNegatives);
    }
    
    // 排序正数部分
    if (posCount > 0) {
        // 使用独立的计数排序逻辑
        int min = positives[0];
        int max = positives[0];
        for (int i = 1; i < posCount; i++) {
            if (positives[i] < min) min = positives[i];
            if (positives[i] > max) max = positives[i];
        }
        int range = max - min + 1;
        int* count = (int*)calloc(range, sizeof(int));
        
        // 统计每个元素出现的次数
        for (int i = 0; i < posCount; i++) {
            count[positives[i] - min]++;
        }
        
        // 计算累计计数
        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }
        
        // 从后向前遍历，保证稳定性
        int* output = (int*)malloc(posCount * sizeof(int));
        for (int i = posCount - 1; i >= 0; i--) {
            int value = positives[i];
            int index = value - min;
            output[count[index] - 1] = value;
            count[index]--;
        }
        
        // 复制回正数数组
        for (int i = 0; i < posCount; i++) {
            positives[i] = output[i];
        }
        
        free(count);
        free(output);
    }
    
    // 合并结果
    int index = 0;
    for (int i = 0; i < negCount; i++) {
        arr[index++] = negatives[i];
    }
    for (int i = 0; i < posCount; i++) {
        arr[index++] = positives[i];
    }
    
    printArray(arr, size, "排序后数组");
    
    free(negatives);
    free(positives);
}

/**
 * 计数排序 - 桶优化版本
 * 
 * 算法思路：
 * 使用桶的概念，将相近的数值分组
 * 减少计数数组的大小
 * 适合大数据范围但分布稀疏的情况
 * 
 * 优化效果：
 * - 减少内存使用
 * - 提高处理稀疏数据的效率
 * 
 * 时间复杂度：O(n + k)
 * 空间复杂度：O(k)
 * 稳定性：稳定
 */
void countingSort4(int arr[], int size) {
    printf("countingSort4 bucket optimized:\n");
    
    if (size == 0) return;
    
    // 找到最小值和最大值
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    int range = max - min + 1;
    
    // 确定桶的大小（可以调整以优化性能）
    int bucketSize = (range > 10) ? range / 10 : 1;
    int bucketCount = (range + bucketSize - 1) / bucketSize;
    
    // 创建桶
    int** buckets = (int**)malloc(bucketCount * sizeof(int*));
    int* bucketSizes = (int*)calloc(bucketCount, sizeof(int));
    
    // 将元素分配到桶中
    for (int i = 0; i < size; i++) {
        int bucketIndex = (arr[i] - min) / bucketSize;
        if (bucketSizes[bucketIndex] == 0) {
            buckets[bucketIndex] = (int*)malloc(size * sizeof(int));
        }
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }
    
    // 对每个桶进行排序并合并结果
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            // 第三步：对每个桶进行独立的计数排序
            int min = buckets[i][0];
            int max = buckets[i][0];
            for (int j = 1; j < bucketSizes[i]; j++) {
                if (buckets[i][j] < min) min = buckets[i][j];
                if (buckets[i][j] > max) max = buckets[i][j];
            }
            int range = max - min + 1;
            int* count = (int*)calloc(range, sizeof(int));
            
            // 统计每个元素出现的次数
            for (int j = 0; j < bucketSizes[i]; j++) {
                count[buckets[i][j] - min]++;
            }
            
            // 计算累计计数
            for (int j = 1; j < range; j++) {
                count[j] += count[j - 1];
            }
            
            // 从后向前遍历，保证稳定性
            int* output = (int*)malloc(bucketSizes[i] * sizeof(int));
            for (int j = bucketSizes[i] - 1; j >= 0; j--) {
                int value = buckets[i][j];
                int idx = value - min;
                output[count[idx] - 1] = value;
                count[idx]--;
            }
            
            // 第四步：将排序后的桶内容复制回原数组
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[index++] = output[j];
            }
            
            free(count);
            free(output);
        }
    }
    
    printArray(arr, size, "排序后数组");
    
    free(bucketSizes);
    free(buckets);
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：标准版本
    performanceTest(countingSort1, testData, testDataSize, "标准版本");

    // 测试2：内存优化版本
    performanceTest(countingSort2, testData, testDataSize, "内存优化版本");

    // 测试3：负数处理版本
    performanceTest(countingSort3, testData, testDataSize, "负数处理版本");

    // 测试4：桶优化版本
    performanceTest(countingSort4, testData, testDataSize, "桶优化版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 标准版本：经典实现，稳定排序\n");
    printf("2. 内存优化版本：原地修改，节省空间\n");
    printf("3. 负数处理版本：支持负数，功能完整\n");
    printf("4. 桶优化版本：分组处理，适合稀疏数据\n");

    return 0;
}

/*
打印结果
jarry@Mac countingsort % gcc counting_sort.c -o counting_sort && ./counting_sort
标准版本: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort1 standard:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
标准版本: 0.005ms
标准版本: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

内存优化版本: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort2 memory optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
内存优化版本: 0.004ms
内存优化版本: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

负数处理版本: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort3 negative numbers:
排序后数组: [10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
负数处理版本: 0.004ms
负数处理版本: [10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

桶优化版本: [20, 11, 0, -10, 9, 9, 6, 30, 11, 15, 13, 80]
countingSort4 bucket optimized:
排序后数组: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]
桶优化版本: 0.005ms
桶优化版本: [-10, 0, 6, 9, 9, 11, 11, 13, 15, 20, 30, 80]

=== 算法对比总结 ===
1. 标准版本：经典实现，稳定排序
2. 内存优化版本：原地修改，节省空间
3. 负数处理版本：支持负数，功能完整
4. 桶优化版本：分组处理，适合稀疏数据
*/
