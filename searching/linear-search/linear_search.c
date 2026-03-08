/*
 * 线性查找 - Linear Search
 * 逐个遍历查找目标元素
 * 时间复杂度: O(n)
 */
#include <stdio.h>

// 基本线性查找
int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // 找到目标，返回索引
        }
    }
    return -1;  // 未找到
}

// 查找所有匹配项
int linear_search_all(int arr[], int n, int target, int result[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            result[count++] = i;
        }
    }
    return count;  // 返回匹配数量
}

// 带哨兵的线性查找（减少比较次数）
int linear_search_sentinel(int arr[], int n, int target) {
    int last = arr[n - 1];  // 保存最后一个元素
    arr[n - 1] = target;     // 设置哨兵
    
    int i = 0;
    while (arr[i] != target) {
        i++;
    }
    
    arr[n - 1] = last;  // 恢复最后一个元素
    
    if (i < n - 1 || arr[n - 1] == target) {
        return i;
    }
    return -1;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 22};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;
    
    printf("线性查找演示:\n\n");
    printf("数组: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n目标元素: %d\n\n", target);
    
    // 基本查找
    int index = linear_search(arr, n, target);
    if (index != -1) {
        printf("基本查找: 找到于索引 %d\n", index);
    } else {
        printf("基本查找: 未找到\n");
    }
    
    // 查找所有匹配
    int result[10];
    int count = linear_search_all(arr, n, target, result);
    printf("所有匹配位置: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("(共%d个)\n", count);
    
    // 查找不存在的元素
    int not_found = linear_search(arr, n, 100);
    printf("查找100: %s\n", not_found != -1 ? "找到" : "未找到");
    
    return 0;
}
