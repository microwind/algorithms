#include <stdio.h>

/*
 * 二分搜索（Binary Search）- C 版本
 *
 * 要求数组按升序排序。
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */

// 迭代版二分搜索
int binary_search_iterative(const int *arr, int n, int target) {
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

// 查找第一个等于 target 的位置
int find_first_occurrence(const int *arr, int n, int target) {
    int left = 0, right = n - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// 查找最后一个等于 target 的位置
int find_last_occurrence(const int *arr, int n, int target) {
    int left = 0, right = n - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main(void) {
    printf("========== Binary Search (C) ==========\n");

    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    printf("数组: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("迭代查找 7 -> %d\n", binary_search_iterative(arr, n, 7));

    int arr2[] = {1, 3, 5, 5, 5, 7, 9};
    int m = (int)(sizeof(arr2) / sizeof(arr2[0]));
    printf("\n数组2: ");
    for (int i = 0; i < m; i++) printf("%d ", arr2[i]);
    printf("\n");
    printf("第一个 5 的位置 -> %d\n", find_first_occurrence(arr2, m, 5));
    printf("最后一个 5 的位置 -> %d\n", find_last_occurrence(arr2, m, 5));

    return 0;
}

