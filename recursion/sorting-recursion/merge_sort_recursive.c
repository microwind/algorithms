/*
 * 递归排序 - 归并排序
 * 使用分治递归实现稳定的排序算法
 */
#include <stdio.h>
#include <stdlib.h>

// 合并两个有序数组
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

// 归并排序 - 递归实现
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

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("归并排序演示:\n\n");
    printf("原始数组: ");
    printArray(arr, n);
    
    mergeSort(arr, 0, n - 1);
    
    printf("排序结果: ");
    printArray(arr, n);
    
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
