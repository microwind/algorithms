/**
 * 冒泡排序算法实现
 * 提供四种不同的实现方式，适合不同场景和性能需求
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// 函数声明
void printArray(int arr[], int len, const char* label);
void performanceTest(void (*sortFunc)(int[], int), int arr[], int len, const char* name);

void bubbleSort1(int arr[], int len) {
    printf("bubbleSort1 from left to right:\n");
    // 外循环：控制排序轮数，每轮确定一个最大值的位置
    for (int i = 0; i < len; i++) {
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for (int j = 0; j < len - i - 1; j++) {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if (arr[j] > arr[j + 1]) {
                // C特点：使用临时变量交换
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printArray(arr, len, "基础升序版本排序结果");
}

void bubbleSort2(int arr[], int len) {
    printf("bubbleSort2 from right to left:\n");
    // 外循环：控制排序轮数，每轮确定一个最小值的位置
    for (int i = 0; i < len; i++) {
        // 内循环：从右向左比较，j > i 避免重复比较已排序部分
        for (int j = len - 1; j > i; j--) {
            // 关键点：自右往左每两个进行比较，把小的交换到右侧
            if (arr[j - 1] < arr[j]) {
                // C特点：使用临时变量交换
                int tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }
    printArray(arr, len, "基础降序版本排序结果");
}

void bubbleSort3(int arr[], int len) {
    printf("bubbleSort3 add flag:\n");
    // 优化点：增加一个标志，如果某一轮没有进行过任何的交换
    // 则说明当前数组已排好序，则不必继续后面的遍历
    bool flag = true;

    // 外循环：增加 flag 条件，当数组已有序时提前终止
    for (int i = 0; i < len && flag == true; i++) {
        flag = false; // 每轮开始时重置标志
        // 内循环：控制比较次数，len-i-1 避免重复比较已排序部分
        for (int j = 0; j < len - i - 1; j++) {
            // 关键点：自左往右每两个进行比较，把大的交换到右侧
            if (arr[j] > arr[j + 1]) {
                flag = true; // 发生交换，设置标志
                // C特点：使用临时变量交换
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printArray(arr, len, "优化版本排序结果");
}

void bubbleSort4(int arr[], int len) {
    printf("bubbleSort4:\n");
    // 外循环：控制排序轮数，i 从 1 开始，因为第 0 个元素默认为已排序
    for (int i = 1; i < len; i++) {
        // 内循环：在已排序区域中查找插入位置
        for (int j = 0; j < i; j++) {
            // 关键点：如果待插入元素小于已排序区域的某个元素，则交换
            if (arr[j] > arr[i]) {
                // C特点：使用临时变量交换
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printArray(arr, len, "插入式版本排序结果");
}

void printArray(int arr[], int len, const char* label) {
    printf("%s: [", label);
    for (int i = 0; i < len; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    printf("]\n");
}

void performanceTest(void (*sortFunc)(int[], int), int arr[], int len, const char* name) {
    // 创建数组副本，避免修改原数组
    int testArr[len];
    memcpy(testArr, arr, len * sizeof(int));
    printArray(testArr, len, name);
    
    // 开始计时
    clock_t start = clock();
    sortFunc(testArr, len);
    clock_t end = clock();
    
    printf("%s: %.3fms\n", name, (double)(end - start) * 1000 / CLOCKS_PER_SEC);
    printf("\n"); // 空行分隔
}

int main() {
    // 测试数据：
    int testData[] = {7, 11, 9, 10, 12, 13, 8};
    int len = sizeof(testData) / sizeof(testData[0]);
    
    printf("=== 冒泡排序算法演示 ===\n\n");
    
    // 测试1：基础升序版本
    performanceTest(bubbleSort1, testData, len, "基础升序版本");
    
    // 测试2：基础降序版本
    performanceTest(bubbleSort2, testData, len, "基础降序版本");
    
    // 测试3：优化版本
    performanceTest(bubbleSort3, testData, len, "优化版本");
    
    // 测试4：插入式版本
    performanceTest(bubbleSort4, testData, len, "插入式版本");
    
    printf("=== 算法对比总结 ===\n");
    printf("1. 基础版本：简单易懂，适合学习算法原理\n");
    printf("2. 降序版本：展示算法的灵活性，可按需排序\n");
    printf("3. 优化版本：通过标志位优化，适合实际应用\n");
    printf("4. 插入式版本：结合其他排序思想，性能更稳定\n");
    
    return 0;
}

/* 打印结果
jarry@Mac bubblesort % gcc bubble_sort.c -o bubble_sort && ./bubble_sort
=== 冒泡排序算法演示 ===

基础升序版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort1 from left to right:
基础升序版本排序结果: [7, 8, 9, 10, 11, 12, 13]
基础升序版本: 0.xxxms

基础降序版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort2 from right to left:
基础降序版本排序结果: [13, 12, 11, 10, 9, 8, 7]
基础降序版本: 0.xxxms

优化版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort3 add flag:
优化版本排序结果: [7, 8, 9, 10, 11, 12, 13]
优化版本: 0.xxxms

插入式版本: [7, 11, 9, 10, 12, 13, 8]
bubbleSort4:
插入式版本排序结果: [7, 8, 9, 10, 11, 12, 13]
插入式版本: 0.xxxms

=== 算法对比总结 ===
1. 基础版本：简单易懂，适合学习算法原理
2. 降序版本：展示算法的灵活性，可按需排序
3. 优化版本：通过标志位优化，适合实际应用
4. 插入式版本：结合其他排序思想，性能更稳定
*/
