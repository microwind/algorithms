/*
 * 阶乘递归示例
 * n! = n × (n-1) × (n-2) × ... × 1
 */

#include <stdio.h>

// 方法1: 递归版本
long long factorial_recursive(int n) {
    /* 递归计算阶乘，O(n) 时间复杂度，O(n) 空间复杂度 */
    if (n <= 1) {
        return 1;
    }
    return n * factorial_recursive(n - 1);
}

// 方法2: 迭代版本
long long factorial_iterative(int n) {
    /* 迭代计算阶乘，O(n) 时间复杂度，O(1) 空间复杂度 */
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 方法3: 尾递归
long long factorial_tail(int n, long long acc) {
    /* 尾递归版本 */
    if (n <= 1) {
        return acc;
    }
    return factorial_tail(n - 1, n * acc);
}

long long factorial_tail_wrapper(int n) {
    return factorial_tail(n, 1);
}

int main() {
    printf("=== 阶乘计算 ===\n\n");
    
    int test_values[] = {5, 10, 20};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int n = test_values[i];
        printf("%d! = %lld\n", n, factorial_recursive(n));
        printf("迭代版本: %d! = %lld\n", n, factorial_iterative(n));
        printf("尾递归版本: %d! = %lld\n", n, factorial_tail_wrapper(n));
        printf("\n");
    }
    
    return 0;
}
