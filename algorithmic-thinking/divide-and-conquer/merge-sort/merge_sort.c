/*
*
 * 归并排序 - 分治法的典型应用
 *
 * 分治法三个步骤：
 * 1. 分解：将数组分成两个子数组
 * 2. 求解：递归对子数组进行归并排序
 * 3. 合并：将两个已排序的子数组合并
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(n)
 *
 * 特点：
 * - 稳定的排序算法
 * - 适合链表排序
 * - 适合大数据外部排序
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*
 * 合并两个已排序的数组
 *
 * @param arr 原数组
 * @param left 左侧起始位置
 * @param mid 中间位置
 * @param right 右侧结束位置
*/
void merge(int *arr, int left, int mid, int right) {
    // 创建临时数组
    int temp_size = right - left + 1;
    int *temp = (int *)malloc(temp_size * sizeof(int));

    int i = left;
    int j = mid + 1;
    int k = 0;

    // 比较两个子数组的元素
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // 复制左侧剩余元素
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 复制右侧剩余元素
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将临时数组复制回原数组
    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }

    free(temp);
}

/*
*
 * 递归进行归并排序
 *
 * @param arr 待排序数组
 * @param left 起始位置
 * @param right 结束位置
*/
void merge_sort_helper(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 递归排序左半部分
        merge_sort_helper(arr, left, mid);

        // 递归排序右半部分
        merge_sort_helper(arr, mid + 1, right);

        // 合并两个已排序的部分
        merge(arr, left, mid, right);
    }
}

/*
*
 * 归并排序入口函数
 *
 * @param arr 待排序数组
 * @param n 数组大小
*/
void merge_sort(int *arr, int n) {
    if (n <= 1) {
        return;
    }
    merge_sort_helper(arr, 0, n - 1);
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
    printf("=== 归并排序 ===\n\n");

    // 测试用例1：随机数组
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("原数组: ");
    print_array(arr1, n1);
    merge_sort(arr1, n1);
    printf("\n排序后: ");
    print_array(arr1, n1);
    printf("\n\n");

    // 测试用例2：已排序数组
    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("已排序数组: ");
    print_array(arr2, n2);
    merge_sort(arr2, n2);
    printf("\n排序后: ");
    print_array(arr2, n2);
    printf("\n\n");

    // 测试用例3：反序数组
    int arr3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("反序数组: ");
    print_array(arr3, n3);
    merge_sort(arr3, n3);
    printf("\n排序后: ");
    print_array(arr3, n3);
    printf("\n\n");

    // 测试用例4：包含重复元素
    int arr4[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("包含重复: ");
    print_array(arr4, n4);
    merge_sort(arr4, n4);
    printf("\n排序后: ");
    print_array(arr4, n4);
    printf("\n");

    return 0;
}
