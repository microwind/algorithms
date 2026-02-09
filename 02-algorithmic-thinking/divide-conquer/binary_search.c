/**
 * 二分查找 - 分治法的查询应用
 *
 * 二分查找的三个步骤：
 * 1. 分解：在中间位置检查元素
 * 2. 求解：递归地在左半部分或右半部分查找
 * 3. 合并：返回查找结果
 *
 * 前置条件：数组必须已排序
 *
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1)
 */

#include <stdio.h>

/**
 * 二分查找（迭代版本）
 *
 * @param arr 已排序的数组
 * @param n 数组大小
 * @param target 查找的目标值
 * @return 目标值的索引，如果不存在返回 -1
 */
int binary_search(int *arr, int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

/**
 * 二分查找（递归版本）
 */
int binary_search_recursive(int *arr, int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binary_search_recursive(arr, mid + 1, right, target);
    } else {
        return binary_search_recursive(arr, left, mid - 1, target);
    }
}

/**
 * 查找第一个 >= target 的元素位置（左边界）
 */
int binary_search_left(int *arr, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] >= target) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

/**
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

/**
 * 测试函数
 */
int main() {
    printf("=== 二分查找 ===\n\n");

    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("数组: ");
    print_array(arr, n);
    printf("\n\n");

    // 测试用例1：基本查找（迭代）
    printf("1. 迭代版本:\n");
    printf("  查找 7: %d\n", binary_search(arr, n, 7));
    printf("  查找 20: %d\n", binary_search(arr, n, 20));
    printf("\n");

    // 测试用例2：递归版本
    printf("2. 递归版本:\n");
    printf("  查找 9: %d\n", binary_search_recursive(arr, 0, n - 1, 9));
    printf("  查找 2: %d\n", binary_search_recursive(arr, 0, n - 1, 2));
    printf("\n");

    // 测试用例3：查找左边界
    int arr_dup[] = {1, 2, 2, 2, 3, 4, 5, 5, 5, 6};
    int n_dup = sizeof(arr_dup) / sizeof(arr_dup[0]);
    printf("3. 查找边界 (数组: ");
    print_array(arr_dup, n_dup);
    printf("):\n");
    printf("  左边界 2: %d\n", binary_search_left(arr_dup, n_dup, 2));
    printf("  左边界 5: %d\n", binary_search_left(arr_dup, n_dup, 5));
    printf("\n");

    // 测试用例4：查找不存在的元素
    printf("4. 查找不存在的元素:\n");
    printf("  查找 100: %d\n", binary_search(arr, n, 100));
    printf("  查找 0: %d\n", binary_search(arr, n, 0));

    return 0;
}
