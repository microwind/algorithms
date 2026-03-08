/*
 * 递归排序 - 快速排序
 * 使用分治递归实现高效的排序算法
 */
#include <stdio.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分区函数：将数组分为两部分，左边小于pivot，右边大于pivot
int partition(int arr[], int low, int high) {
    // 选择最后一个元素作为pivot
    int pivot = arr[high];
    int i = low - 1;  // 小于pivot的元素的边界
    
    for (int j = low; j < high; j++) {
        // 如果当前元素小于等于pivot，放到左边
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // 将pivot放到正确位置
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 快速排序 - 递归实现
void quickSort(int arr[], int low, int high) {
    // 基础情况：数组长度为0或1
    if (low < high) {
        // 分区，获取pivot的最终位置
        int pi = partition(arr, low, high);
        
        // 递归排序左半部分
        quickSort(arr, low, pi - 1);
        
        // 递归排序右半部分
        quickSort(arr, pi + 1, high);
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
    
    printf("快速排序演示:\n\n");
    printf("原始数组: ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("排序结果: ");
    printArray(arr, n);
    
    printf("\n递归过程:\n");
    printf("  quickSort(0, 6)          [64,34,25,12,22,11,90]\n");
    printf("    ├── quickSort(0, 3)    [11,34,25,12] (左半部分)\n");
    printf("    │     └── ...          继续递归\n");
    printf("    └── quickSort(5, 6)    [90] (右半部分)\n");
    printf("\n时间复杂度: 平均 O(n log n)\n");
    
    return 0;
}
