/**
 * Copyright https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 斐波那契数列示例
 * 
 * 包含多种实现方式：
 * - 递归版本：基础递归实现
 * - 迭代版本：空间优化实现
 * 
 * 核心公式：F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1
 * 
 * 学习重点：理解递归与迭代的性能差异
 */
#include <stdio.h>

/*
递归思维：
斐波那契数列的递推公式是 F(n) = F(n-1) + F(n-2)，其中 F(0) = 0, F(1) = 1。
*/
// 计算第 n 个斐波那契数递归版
int fibonacci(int n) {
    if (n == 0) return 0;  // 递归终止条件
    if (n == 1) return 1;  // 递归终止条件
    return fibonacci(n - 1) + fibonacci(n - 2);  // 递归调用
}

// 循环实现（优化版），请仔细对比递归版
int fibonacci_iterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    // 定义前2个数a,b以及结果
    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        // 下一个数是前2个之和
        temp = a + b;
        // 重新设定前2个数
        a = b;
        b = temp;
    }
    return b;
}


int main() {
/*
fibonacci(5) 计算过程：
fibonacci(5) = fibonacci(4) + fibonacci(3)
             = (fibonacci(3) + fibonacci(2)) + (fibonacci(2) + fibonacci(1))
             = ((fibonacci(2) + fibonacci(1)) + fibonacci(1)) + (fibonacci(1) + fibonacci(0)) + fibonacci(1)
             = (((fibonacci(1) + fibonacci(0)) + fibonacci(1)) + fibonacci(1)) + (fibonacci(1) + fibonacci(0)) + fibonacci(1)
             = (((1 + 0) + 1) + 1) + (1 + 0) + 1
             = (1 + 1 + 1) + 1 + 1 + 1 = 5

=======

调用过程图：
          fibonacci(5)
         /            \
    fibonacci(4)    fibonacci(3)
    /       \        /       \
fibonacci(3) fibonacci(2) fibonacci(2) fibonacci(1)
   /    \      /    \        /   \    
f(2)  f(1)  f(1)  f(0)   f(1)  f(0)
 /  \
f(1) f(0)
*/
    int num = 6;
    // 递归版
    printf("Fibonacci(%d) = %d\n", num, fibonacci(num));
    // 循环版调用
    printf("Iterative: Fibonacci(%d) = %d\n", num, fibonacci_iterative(num));
    return 0;
}