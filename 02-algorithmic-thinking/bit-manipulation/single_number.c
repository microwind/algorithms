/**
 * 单数问题 - 使用XOR技巧找到单个数字
 *
 * 问题：给定一个整数数组，其中除了一个元素出现一次外，
 * 其他元素都出现两次。找到只出现一次的那个元素。
 *
 * 核心思想：
 * - XOR 的性质：a ^ a = 0, a ^ 0 = a
 * - 对所有元素进行XOR操作，两个相同的数会相消，留下单个数字
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 使用XOR技巧找到单个数字
 *
 * 原理：
 * - 0 ^ x = x
 * - x ^ x = 0
 * - XOR满足交换律和结合律
 * - 对所有数字XOR，重复数字相消，留下单个数字
 *
 * @param nums 输入数组
 * @param n 数组大小
 * @return 单个数字
 */
int singleNumberXor(int *nums, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= nums[i];
    }
    return result;
}

/**
 * 使用哈希表统计频数（备选方案）
 *
 * @param nums 输入数组
 * @param n 数组大小
 * @return 单个数字，如果未找到返回 -1
 */
int singleNumberHash(int *nums, int n) {
    // 使用简单的哈希策略（假设数字范围有限）
    // 实际应用中应使用完整的哈希表实现
    // 这里只是演示，实际会超出范围处理的复杂性

    // 快速排序后比较
    int *sorted = (int *)malloc(n * sizeof(int));
    memcpy(sorted, nums, n * sizeof(int));

    // 简单冒泡排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    // 查找单个数字
    for (int i = 0; i < n - 1; i += 2) {
        if (sorted[i] != sorted[i + 1]) {
            free(sorted);
            return sorted[i];
        }
    }

    free(sorted);
    return sorted[n - 1];
}

/**
 * 打印数组
 */
void printArray(int *arr, int n) {
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
    printf("=== 单数问题 ===\n\n");

    // 测试用例1：基本用例
    printf("1. 基本用例:\n");
    int nums1[] = {2, 2, 1};
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("  数组: ");
    printArray(nums1, n1);
    printf("\n  单数: %d\n\n", singleNumberXor(nums1, n1));

    // 测试用例2：较大数组
    printf("2. 较大数组:\n");
    int nums2[] = {4, 1, 2, 1, 2};
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("  数组: ");
    printArray(nums2, n2);
    printf("\n  单数: %d\n\n", singleNumberXor(nums2, n2));

    // 测试用例3：负数
    printf("3. 包含负数:\n");
    int nums3[] = {-1, -1, 5, 5, 3};
    int n3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("  数组: ");
    printArray(nums3, n3);
    printf("\n  单数: %d\n\n", singleNumberXor(nums3, n3));

    // 测试用例4：单个元素
    printf("4. 单个元素:\n");
    int nums4[] = {42};
    int n4 = sizeof(nums4) / sizeof(nums4[0]);
    printf("  数组: ");
    printArray(nums4, n4);
    printf("\n  单数: %d\n\n", singleNumberXor(nums4, n4));

    // 测试用例5：较大数值
    printf("5. 较大数值:\n");
    int nums5[] = {7, 7, 8, 8, 9};
    int n5 = sizeof(nums5) / sizeof(nums5[0]);
    printf("  数组: ");
    printArray(nums5, n5);
    printf("\n  单数: %d\n\n", singleNumberXor(nums5, n5));

    // 性能对比
    printf("6. 不同方法的结果比较:\n");
    int nums6[] = {100, 100, 200, 200, 300};
    int n6 = sizeof(nums6) / sizeof(nums6[0]);
    printf("  数组: ");
    printArray(nums6, n6);
    printf("\n");
    printf("  XOR方法: %d\n", singleNumberXor(nums6, n6));
    printf("  排序方法: %d\n", singleNumberHash(nums6, n6));

    return 0;
}
