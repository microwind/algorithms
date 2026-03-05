#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 随机快速排序（Randomized QuickSort）- C 版本
 *
 * 与普通快速排序一致，但在每次分区时随机选择枢轴，
 * 使得绝大多数输入情况下的时间复杂度期望为 O(n log n)。
 */

// 交换两个整数
static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 随机分区：选择 [left, right] 中的随机下标作为枢轴，然后分区
int randomized_partition(int *arr, int left, int right) {
    int random_idx = left + rand() % (right - left + 1);
    swap(&arr[random_idx], &arr[right]);

    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

// 随机快速排序（原地排序）
void randomized_quicksort(int *arr, int left, int right) {
    if (left < right) {
        int pivot_idx = randomized_partition(arr, left, right);
        randomized_quicksort(arr, left, pivot_idx - 1);
        randomized_quicksort(arr, pivot_idx + 1, right);
    }
}

// 随机选择：平均 O(n) 时间找到第 k 小元素（0-based）
int randomized_select(int *arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    int pivot_idx = randomized_partition(arr, left, right);
    if (k == pivot_idx) {
        return arr[k];
    } else if (k < pivot_idx) {
        return randomized_select(arr, left, pivot_idx - 1, k);
    } else {
        return randomized_select(arr, pivot_idx + 1, right, k);
    }
}

// 打印数组
void print_array(const int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("========== Randomized QuickSort (C) ==========\n");

    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    printf("原数组: ");
    print_array(arr, n);

    int sorted[9];
    for (int i = 0; i < n; i++) sorted[i] = arr[i];
    randomized_quicksort(sorted, 0, n - 1);
    printf("排序后: ");
    print_array(sorted, n);

    int copy[9];
    for (int i = 0; i < n; i++) copy[i] = arr[i];
    int k = 3;
    int kth = randomized_select(copy, 0, n - 1, k);
    printf("第 %d 小元素: %d\n", k, kth);

    return 0;
}

