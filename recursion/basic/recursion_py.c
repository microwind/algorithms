/*
 * 递归算法示例集合（基于Python版本）
 * 包含阶乘、斐波那契、汉诺塔、二分查找、数组求和、字符串反转等示例
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 阶乘 (Factorial)
// 时间复杂度: O(n), 空间复杂度: O(n)（递归栈深度）
int factorial(int n) {
    /* 计算 n 的阶乘 */
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 2. 斐波那契数列
// 普通递归: 时间复杂度 O(2^n)，空间复杂度 O(n)
int fibonacci(int n) {
    /* 计算斐波那契数列第 n 项（普通递归） */
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 优化版本（记忆化）
int fibonacci_memo_helper(int n, int* memo) {
    if (memo[n] != -1) {
        return memo[n];
    }
    
    if (n <= 1) {
        memo[n] = n;
    } else {
        memo[n] = fibonacci_memo_helper(n - 1, memo) + fibonacci_memo_helper(n - 2, memo);
    }
    
    return memo[n];
}

int fibonacci_memo(int n) {
    /* 计算斐波那契数列第 n 项（带记忆化） */
    int* memo = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    
    int result = fibonacci_memo_helper(n, memo);
    free(memo);
    return result;
}

// 3. 汉诺塔问题
// 时间复杂度: O(2^n - 1)，空间复杂度: O(n)
void hanoi(int n, const char* source, const char* target, const char* auxiliary) {
    /*
     * 解决汉诺塔问题
     * 将 n 个盘子从 source 柱移动到 target 柱
     */
    if (n == 1) {
        printf("Move disk 1 from %s to %s\n", source, target);
        return;
    }
    
    // 将 n-1 个盘子从 source 移动到 auxiliary
    hanoi(n - 1, source, auxiliary, target);
    
    // 将最后一个盘子从 source 移动到 target
    printf("Move disk %d from %s to %s\n", n, source, target);
    
    // 将 n-1 个盘子从 auxiliary 移动到 target
    hanoi(n - 1, auxiliary, target, source);
}

// 4. 二分查找（递归版本）
// 时间复杂度: O(log n)，空间复杂度: O(log n)
int binary_search(int* arr, int target, int low, int high) {
    /* 在排序数组中递归查找目标值 */
    if (low > high) {
        return -1;
    }
    
    int mid = (low + high) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] > target) {
        return binary_search(arr, target, low, mid - 1);
    } else {
        return binary_search(arr, target, mid + 1, high);
    }
}

// 5. 数组求和
// 时间复杂度: O(n)，空间复杂度: O(n)
int array_sum(int* arr, int size) {
    /* 递归计算数组元素和 */
    if (size == 0) {
        return 0;
    }
    return arr[0] + array_sum(arr + 1, size - 1);
}

// 6. 反转字符串
// 时间复杂度: O(n)，空间复杂度: O(n)
void reverse_string_helper(const char* s, char* result, int index) {
    if (s[index] == '\0') {
        result[0] = '\0';
        return;
    }
    
    reverse_string_helper(s, result + 1, index + 1);
    result[0] = s[index];
}

void reverse_string(const char* s, char* result) {
    /* 递归反转字符串 */
    reverse_string_helper(s, result, 0);
}

int main() {
    printf("=== 递归算法测试 ===\n\n");
    
    // 测试阶乘
    printf("1. 阶乘\n");
    printf("5! = %d\n", factorial(5));
    
    // 测试斐波那契
    printf("\n2. 斐波那契数列\n");
    printf("fib(10) = %d\n", fibonacci(10));
    printf("fib(10) with memo = %d\n", fibonacci_memo(10));
    
    // 测试汉诺塔
    printf("\n3. 汉诺塔问题 (n=3)\n");
    hanoi(3, "A", "C", "B");
    
    // 测试二分查找
    printf("\n4. 二分查找\n");
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    printf("查找 7: 索引 = %d\n", binary_search(arr, 7, 0, arr_size - 1));
    
    // 测试数组求和
    printf("\n5. 数组求和\n");
    int sum_arr[] = {1, 2, 3, 4, 5};
    int sum_size = sizeof(sum_arr) / sizeof(sum_arr[0]);
    printf("sum([1,2,3,4,5]) = %d\n", array_sum(sum_arr, sum_size));
    
    // 测试字符串反转
    printf("\n6. 字符串反转\n");
    const char* original = "hello";
    char reversed[100];
    reverse_string(original, reversed);
    printf("reverse('hello') = %s\n", reversed);
    
    return 0;
}
