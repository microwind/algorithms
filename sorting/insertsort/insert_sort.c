/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 插入排序算法实现
 * 提供五种不同的实现方式，适合不同场景和性能需求
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

// 测试数据：
int testData[] = {7, 11, 9, 10, 12, 13, 8};
int testDataSize = sizeof(testData) / sizeof(testData[0]);

/**
 * 二分查找插入位置
 */
int binarySearch(int arr[], int value, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == value) {
            return mid + 1; // 插入到相同元素后面，保持稳定性
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return left;
}

/**
 * 插入排序基础版本 - 标准实现
 * 
 * 算法原理：
 * 1. 从第二个元素开始，将其作为"当前元素"
 * 2. 将当前元素与前面已排序的元素比较
 * 3. 找到合适的位置插入当前元素
 * 4. 重复步骤1-3，直到所有元素都排序完成
 * 
 * 生活类比：就像整理手中的扑克牌，
 * 每次拿起一张新牌，插入到手中已排序牌的合适位置
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定 - 保持相等元素的相对位置
 */
void insertSort1(int arr[], int size) {
    printf("insertSort1 standard:\n");
    
    // 从第二个元素开始遍历
    for (int i = 1; i < size; i++) {
        // 关键点：保存当前元素作为待插入元素
        int current = arr[i];
        int j = i - 1;
        
        // 向前查找插入位置，同时移动元素
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // 插入当前元素
        arr[j + 1] = current;
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 插入排序优化版本 - 二分查找插入位置
 * 
 * 算法思路：
 * 使用二分查找确定插入位置，减少比较次数
 * 保持插入操作，但优化查找过程
 * 
 * 优化效果：
 * - 减少比较次数：从O(n)到O(log n)
 * - 保持插入操作的时间复杂度
 * 
 * 时间复杂度：平均O(n²)，最好O(n log n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定
 */
void insertSort2(int arr[], int size) {
    printf("insertSort2 binary search:\n");
    
    // 从第二个元素开始遍历
    for (int i = 1; i < size; i++) {
        int current = arr[i];
        
        // 使用二分查找确定插入位置
        int insertPos = binarySearch(arr, current, 0, i - 1);
        
        // 移动元素为新元素腾出空间
        for (int j = i; j > insertPos; j--) {
            arr[j] = arr[j - 1];
        }
        
        // 插入元素
        arr[insertPos] = current;
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 插入排序 - 哨兵版本
 * 
 * 算法思路：
 * 在数组开头添加哨兵元素，简化边界检查
 * 减少循环中的条件判断
 * 
 * 优化效果：
 * - 减少边界检查
 * - 简化代码逻辑
 * - 轻微的性能提升
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序（忽略哨兵）
 * 稳定性：稳定
 */
void insertSort3(int arr[], int size) {
    printf("insertSort3 sentinel:\n");
    
    if (size == 0) return;
    
    // 找到最小值作为哨兵
    int minIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }
    
    // 将最小值移到开头作为哨兵
    if (minIndex != 0) {
        int temp = arr[0];
        arr[0] = arr[minIndex];
        arr[minIndex] = temp;
    }
    
    // 从第三个元素开始排序（第二个元素已经相对于哨兵有序）
    for (int i = 2; i < size; i++) {
        int current = arr[i];
        int j = i;
        
        // 向前查找插入位置（哨兵保证不会越界）
        while (arr[j - 1] > current) {
            arr[j] = arr[j - 1];
            j--;
        }
        
        arr[j] = current;
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 插入排序 - 希尔插入版本
 * 
 * 算法思路：
 * 结合希尔排序的增量概念
 * 对不同间隔的子序列进行插入排序
 * 
 * 优化效果：
 * - 更好的初始数据分布
 * - 减少总的移动次数
 * - 适合部分有序的数据
 * 
 * 时间复杂度：平均O(n^1.3)，取决于增量序列
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：不稳定 - 增量排序可能破坏稳定性
 */
void insertSort4(int arr[], int size) {
    printf("insertSort4 shell insertion:\n");
    
    // 使用希尔增量序列
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // 对每个增量进行插入排序
        for (int i = gap; i < size; i++) {
            int current = arr[i];
            int j = i;
            
            // 在增量子序列中进行插入排序
            while (j >= gap && arr[j - gap] > current) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = current;
        }
    }
    
    printArray(arr, size, "排序后数组");
}

/**
 * 插入排序 - 倒序遍历版本
 * 
 * 算法思路：
 * 使用for循环倒序遍历已排序区间
 * 通过不同的条件判断逻辑实现插入
 * 
 * 优化效果：
 * - 不同的遍历方式展示算法多样性
 * - 独特的逻辑实现
 * - 适合算法教学和对比
 * 
 * 时间复杂度：平均O(n²)，最好O(n)，最坏O(n²)
 * 空间复杂度：O(1) - 原地排序
 * 稳定性：稳定
 */
void insertSort5(int arr[], int size) {
    printf("insertSort5 reverse traversal:\n");
    
    for (int i = 0; i < size; i++) {
        int current = arr[i];
        int j = i - 1;
        
        // 倒序遍历已排序区间
        for (; j >= 0; j--) {
            // 如果当前项小于已排序项，则右移
            if (current < arr[j]) {
                arr[j + 1] = arr[j];
            } else {
                // 遇到不小于的项则跳出
                break;
            }
        }
        arr[j + 1] = current;
    }
    
    printArray(arr, size, "排序后数组");
}

// ==================== 算法测试和性能对比 ====================

int main() {
    // 测试1：标准版本
    performanceTest(insertSort1, testData, testDataSize, "标准版本");

    // 测试2：二分查找版本
    performanceTest(insertSort2, testData, testDataSize, "二分查找版本");

    // 测试3：哨兵版本
    performanceTest(insertSort3, testData, testDataSize, "哨兵版本");

    // 测试4：希尔插入版本
    performanceTest(insertSort4, testData, testDataSize, "希尔插入版本");

    // 测试5：倒序遍历版本
    performanceTest(insertSort5, testData, testDataSize, "倒序遍历版本");

    printf("=== 算法对比总结 ===\n");
    printf("1. 标准版本：经典实现，易于理解\n");
    printf("2. 二分查找版本：优化查找，减少比较\n");
    printf("3. 哨兵版本：简化边界，提升性能\n");
    printf("4. 希尔插入版本：增量排序，混合优化\n");
    printf("5. 倒序遍历版本：独特逻辑，算法多样性\n");

    return 0;
}

/*
打印结果
jarry@Mac insertsort % rustc insert_sort.rs && ./insert_sort
标准版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort1 standard:
排序后数组: [7, 11, 8, 10, 10, 12, 8]
标准版本: 0.000ms
标准版本排序结果: [7, 11, 8, 10, 10, 12, 8]

二分查找版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort2 binary search:
排序后数组: [7, 11, 11, 11, 12, 12, 12]
二分查找版本: 0.000ms
二分查找版本排序结果: [7, 11, 11, 11, 12, 12, 12]

哨兵版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort3 sentinel:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
哨兵版本: 0.000ms
哨兵版本排序结果: [7, 8, 9, 10, 11, 12, 13]

希尔插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
insertSort4 shell insertion:
排序后数组: [7, 8, 9, 10, 11, 12, 13]
希尔插入版本: 0.000ms
希尔插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

新建数组插入版本原始数组: [7, 11, 9, 10, 12, 13, 8]
新建数组插入版本: 0.000ms
新建数组插入版本排序结果: [7, 8, 9, 10, 11, 12, 13]

新建数组倒序遍历版本原始数组: [7, 11, 9, 10, 12, 13, 8]
新建数组倒序遍历版本: 0.000ms
新建数组倒序遍历版本排序结果: [7, 8, 9, 10, 11, 12, 13]

=== 算法对比总结 ===
1. 标准版本：经典实现，易于理解
2. 二分查找版本：优化查找，减少比较
3. 哨兵版本：简化边界，提升性能
4. 希尔插入版本：增量排序，混合优化
5. 新建数组插入版本：原数组不变，插入操作
*/
