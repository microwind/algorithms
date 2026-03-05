/*
*
 * 快速排序 - 分治法的高效应用
 *
 * 分治法三个步骤：
 * 1. 分解：选择一个基准元素，将数组分为三部分
 * 2. 求解：递归对左右两部分进行快速排序
 * 3. 合并：基准元素已经在最终位置，无需额外合并
 *
 * 时间复杂度: O(n log n) 平均，O(n²) 最坏
 * 空间复杂度: O(log n)
 *
 * 特点：
 * - 原地排序
 * - 不稳定的排序算法
 * - 平均性能优于归并排序
 * - 缓存友好
*/

#include <stdio.h>
#include <stdlib.h>

/*
*
 * 分割函数：使用 Hoare 分割方案
 *
 * @param arr 数组
 * @param low 起始位置
 * @param high 结束位置
 * @return 分割点位置
*/
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            // 交换 arr[i] 和 arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // 交换 arr[i+1] 和 arr[high]
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

/*
*
 * 递归进行快速排序
 *
 * @param arr 数组
 * @param low 起始位置
 * @param high 结束位置
*/
void quick_sort_helper(int *arr, int low, int high) {
    if (low < high) {
        // 分割
        int pi = partition(arr, low, high);

        // 递归排序左右两部分
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

/*
*
 * 快速排序入口函数
 *
 * @param arr 待排序数组
 * @param n 数组大小
*/
void quick_sort(int *arr, int n) {
    if (n <= 1) {
        return;
    }
    quick_sort_helper(arr, 0, n - 1);
}

/*
*
 * 打印数组
*/
void print_array(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

/*
*
 * 测试函数
*/
int main() {
    printf("=== 快速排序 ===\n\n");

    // 测试用例1：随机数组
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("原数组: ");
    print_array(arr1, n1);
    quick_sort(arr1, n1);
    printf("\n排序后: ");
    print_array(arr1, n1);
    printf("\n\n");

    // 测试用例2：已排序数组
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("已排序数组: ");
    print_array(arr2, n2);
    quick_sort(arr2, n2);
    printf("\n排序后: ");
    print_array(arr2, n2);
    printf("\n\n");

    // 测试用例3：反序数组
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("反序数组: ");
    print_array(arr3, n3);
    quick_sort(arr3, n3);
    printf("\n排序后: ");
    print_array(arr3, n3);
    printf("\n\n");

    // 测试用例4：包含重复元素
    int arr4[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("包含重复: ");
    print_array(arr4, n4);
    quick_sort(arr4, n4);
    printf("\n排序后: ");
    print_array(arr4, n4);
    printf("\n");

    return 0;
}
