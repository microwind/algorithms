#include <stdio.h>
#include <stdlib.h>

int step = 0; // 记录分解步骤计数

// 辅助函数：打印数组
void printArray(int *arr, int len) {
    printf("[ ");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// 递归分解数组，返回合并后的数组
int* divide(int *arr, int len) {
    // 输出当前分解阶段的数组
    printf("start: ");
    printArray(arr, len);

    // 递归终止条件：数组长度小于 2，不再拆分
    if (len < 2) {
        return arr;
    }

    // 计算中点位置
    int mid = (len + 1) / 2; // 向上取整分割
    int *left = (int *)malloc(mid * sizeof(int));        // 左半部分
    int *right = (int *)malloc((len - mid) * sizeof(int)); // 右半部分

    // 拷贝左半部分
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    // 拷贝右半部分
    for (int i = mid; i < len; i++) {
        right[i - mid] = arr[i];
    }

    // 递归分解左半部分
    left = divide(left, mid);
    // 递归分解右半部分
    right = divide(right, len - mid);

    // 记录分解步骤
    step++;
    printf("after: %d -> ", step);
    printArray(arr, len);
    printf("Left: ");
    printArray(left, mid);
    printf("Right: ");
    printArray(right, len - mid);

    // 合并左右部分
    int *merged = (int *)malloc(len * sizeof(int));
    for (int i = 0; i < mid; i++) {
        merged[i] = left[i];
    }
    for (int i = mid; i < len; i++) {
        merged[i] = right[i - mid];
    }

    // 释放左右部分的内存
    free(left);
    free(right);
    return merged;
}

int main() {
    int arr[] = {3, 1, 2, 5, 6, 4};
    int len = sizeof(arr) / sizeof(arr[0]);

    // 递归分解数组
    int *result = divide(arr, len);

    // 输出最终结果
    printf("Final result: ");
    printArray(result, len);

    // 释放最终结果数组
    free(result);
    return 0;
}

/*
// 递归分解图形示例：
           f([3, 1, 2, 5, 6, 4])
              /             \
          f([3, 1, 2])    f([5, 6, 4])
          /        \         /        \
      f([3, 1])   f([2])  f([5, 6]), f([4])
      /     \              /      \
  f([3])    f([1])      f([5]) f([6])
*/

/*
jarry@MacBook-Pro recursion % gcc divide.c
jarry@MacBook-Pro recursion % ./a.out 
start: [ 3 1 2 5 6 4 ]
start: [ 3 1 2 ]
start: [ 3 1 ]
start: [ 3 ]
start: [ 1 ]
after: 1 -> [ 3 1 ]
Left: [ 3 ]
Right: [ 1 ]
start: [ 2 ]
after: 2 -> [ 3 1 2 ]
Left: [ 3 1 ]
Right: [ 2 ]
start: [ 5 6 4 ]
start: [ 5 6 ]
start: [ 5 ]
start: [ 6 ]
after: 3 -> [ 5 6 ]
Left: [ 5 ]
Right: [ 6 ]
start: [ 4 ]
after: 4 -> [ 5 6 4 ]
Left: [ 5 6 ]
Right: [ 4 ]
after: 5 -> [ 3 1 2 5 6 4 ]
Left: [ 3 1 2 ]
Right: [ 5 6 4 ]
Final result: [ 3 1 2 5 6 4 ]
*/