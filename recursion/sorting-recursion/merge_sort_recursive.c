/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 递归排序算法示例 - 归并排序
 * 
 * 算法特点：
 * - 使用分治递归实现稳定的排序算法
 * - 时间复杂度: O(n log n)，空间复杂度: O(n)
 * 
 * 学习重点：理解分治策略在排序中的应用
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * 合并两个有序数组
 * @param arr 原数组
 * @param left 左边界
 * @param mid 中间位置
 * @param right 右边界
 */
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // 创建临时数组
    int L[n1], R[n2];
    
    // 复制数据到临时数组
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // 合并临时数组到原数组
    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // 复制剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * 归并排序 - 递归实现
 * 时间复杂度: O(n log n)，空间复杂度: O(n)
 * @param arr 待排序数组
 * @param left 左边界
 * @param right 右边界
 */
void mergeSort(int arr[], int left, int right) {
    // 基础情况：只有一个元素
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // 递归排序左半部分
        mergeSort(arr, left, mid);
        
        // 递归排序右半部分
        mergeSort(arr, mid + 1, right);
        
        // 合并两个有序部分
        merge(arr, left, mid, right);
    }
}

/**
 * 打印数组
 * @param arr 数组
 * @param size 数组大小
 */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * 主函数 - 测试归并排序
 */
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // 测试1：输出原始数组
    printf("归并排序演示:\n\n");
    printf("原始数组: ");
    printArray(arr, n);
    
    // 测试2：执行归并排序
    mergeSort(arr, 0, n - 1);
    
    // 测试3：输出排序结果
    printf("排序结果: ");
    printArray(arr, n);
    
    // 输出递归分解过程
    printf("\n递归分解过程:\n");
    printf("  [64,34,25,12,22,11,90]\n");
    printf("       /        \\\n");
    printf("  [64,34,25,12]  [22,11,90]\n");
    printf("    /    \\       /    \\\n");
    printf("[64,34][25,12] [22,11][90]\n");
    printf("  / \\    / \\    / \\    |\n");
    printf("[64][34][25][12][22][11][90]\n");
    printf("\n然后逐层合并...\n");
    
    return 0;
}

/*打印结果
jarry@Mac sorting-recursion % gcc merge_sort_recursive.c -o merge_sort && ./merge_sort
归并排序演示:

原始数组: 64 34 25 12 22 11 90 
排序结果: 11 12 22 25 34 64 90 

递归分解过程:
  [64,34,25,12,22,11,90]
       /        \
  [64,34,25,12]  [22,11,90]
    /    \       /    \
[64,34][25,12] [22,11][90]
  / \    / \    / \    |
[64][34][25][12][22][11][90]

然后逐层合并...
*/
