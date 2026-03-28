/*
*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
*/
#include <stdio.h>
#include <time.h>

/*
*
 * 本例子在于说明递归与尾递归的区别
 * 区别：
 * 1. 普通递归：函数调用自身后仍有计算操作（如乘法），需要保留当前栈帧
 * 2. 尾递归：函数的最后一个操作就是调用自身，没有后续计算，理论上可被编译器优化
 * 3. 栈使用：普通递归随着n增大栈深度线性增加，尾递归优化后可保持固定栈深度
 * 4. 效率：尾递归通常效率更高，且更不易发生栈溢出
*/

// 普通递归实现阶乘
// 参数：n为待计算阶乘的数，accumulator仅用于跟踪中间结果（非累加器模式）
int factorial(int n, int accumulator) {
    // 打印当前递归层级的参数状态，便于观察执行过程
    printf("\r\n current number:%d accumulator: %d", n, accumulator);
    
    // 递归终止条件：当n小于等于1时，返回1（阶乘的数学定义）
    if (n <= 1) return 1;
    
    // 递归调用后仍有乘法操作，因此不是尾递归
    // 执行过程：先计算factorial(n-1)，再将结果与n相乘
    return n * factorial(n - 1, n * accumulator);
}

// 尾递归实现阶乘
// 参数：n为待计算阶乘的数，accumulator用于累积中间计算结果
int tailFactorial(int n, int accumulator) {
    // 打印当前递归层级的参数状态，便于观察执行过程
    printf("\r\n current number:%d accumulator:%d", n, accumulator);
    
    // 递归终止条件：当n小于等于1时，直接返回累积的结果
    if (n <= 1) return accumulator;
    
    // 最后一步操作就是递归调用自身，没有后续计算，符合尾递归定义
    // 执行过程：将当前计算结果(n*accumulator)作为参数传递给下一层递归
    return tailFactorial(n - 1, n * accumulator);
}

// 尾递归包装函数
// 作用：提供更友好的接口（无需用户手动传入初始累加器）
int factorialTail(int n) {
    // 初始累加器为1（阶乘计算的起始值）
    return tailFactorial(n, 1);
}

// 测试验证
int main() {
    // 记录普通递归开始时间
    float startTime = clock();
    // 计算5的阶乘（普通递归方式），第二个参数1仅用于跟踪
    printf("\r\n factorial(5) result: %d", factorial(5, 1));
    // 计算并打印普通递归执行时间（毫秒）
    printf("\ntime: %f ms.", ((clock() - startTime) / CLOCKS_PER_SEC * 1000));

    // 记录尾递归开始时间
    float startTime2 = clock();
    printf("\r\n===============\r\n");
    // 计算5的阶乘（尾递归方式）
    printf("\r\n factorialTail(5) result: %d", factorialTail(5));
    // 计算并打印尾递归执行时间（毫秒）
    printf("\ntime: %f ms.", ((clock() - startTime2) / CLOCKS_PER_SEC * 1000));

    return 0;
}

/*
*
jarry@Mac tail-recursion % java TailFactorial.java 

current number: 5, accumulator: 1
current number: 4, accumulator: 5
current number: 3, accumulator: 20
current number: 2, accumulator: 60
current number: 1, accumulator: 120
factorial(5) result: 120
time: 4.947792 ms.
===============

current number: 5, accumulator: 1
current number: 4, accumulator: 5
current number: 3, accumulator: 20
current number: 2, accumulator: 60
current number: 1, accumulator: 120
factorialTail(5) result: 120
time: 0.289250 ms.%
*/