#include <stdio.h>

/*
 * 线性搜索（Linear Search）- C 版本
 *
 * 从头到尾依次比较数组中的每一个元素，找到目标值的下标。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

// 查找第一个等于 target 的下标，未找到返回 -1
int linear_search(const int *arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 查找所有等于 target 的下标，结果存入 indices，返回找到的个数
int linear_search_all(const int *arr, int n, int target, int *indices) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            indices[count++] = i;
        }
    }
    return count;
}

int main(void) {
    printf("========== Linear Search (C) ==========\n");

    int arr[] = {5, 2, 8, 1, 9, 3, 7};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    printf("数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int idx = linear_search(arr, n, 8);
    printf("查找 8 -> %d\n", idx);

    idx = linear_search(arr, n, 10);
    printf("查找 10 -> %d\n", idx);

    int arr2[] = {1, 2, 3, 2, 4, 2};
    int m = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int indices[6];
    int count = linear_search_all(arr2, m, 2, indices);
    printf("数组2: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n查找所有 2 -> ");
    for (int i = 0; i < count; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    return 0;
}

