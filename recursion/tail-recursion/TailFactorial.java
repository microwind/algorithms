/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 尾递归算法示例
 * 
 * 展示普通递归与尾递归的区别：
 * - 普通递归：递归调用后仍有计算操作，需要保留当前栈帧
 * - 尾递归：最后一步是递归调用，无后续操作，部分JVM可优化
 * 
 * 学习重点：理解尾递归优化原理和性能差异
 */
public class TailFactorial {

    /**
     * 普通递归实现阶乘
     * 时间复杂度: O(n)，空间复杂度: O(n)
     * @param n 待计算的数
     * @param accumulator 用于跟踪中间结果
     * @return 计算结果
     */
    public static int factorial(int n, int accumulator) {
        System.out.printf("\ncurrent number: %d, accumulator: %d", n, accumulator);
        
        // 递归终止条件
        if (n <= 1) {
            return 1;
        }
        
        // 递归调用后还有乘法操作，不是尾递归
        return n * factorial(n - 1, n * accumulator);
    }

    /**
     * 尾递归核心函数
     * 时间复杂度: O(n)，空间复杂度: O(1)（编译器优化后）
     * @param n 待计算的数
     * @param accumulator 用于累积计算结果
     * @return 计算结果
     */
    private static int tailFactorial(int n, int accumulator) {
        System.out.printf("\ncurrent number: %d, accumulator: %d", n, accumulator);
        
        // 递归终止条件，直接返回累积结果
        if (n <= 1) {
            return accumulator;
        }
        
        // 最后一步是递归调用，无其他操作，符合尾递归特征
        return tailFactorial(n - 1, n * accumulator);
    }

    /**
     * 尾递归包装函数，提供更友好的接口
     * @param n 待计算的数
     * @return 计算结果
     */
    public static int factorialTail(int n) {
        return tailFactorial(n, 1);
    }

    /**
     * 主函数 - 测试递归性能对比
     */
    public static void main(String[] args) {
        // 测试1：普通递归
        long startTime = System.nanoTime();
        System.out.printf("\nfactorial(5) result: %d", factorial(5, 1));
        double elapsedTime = (System.nanoTime() - startTime) / 1_000_000.0;
        System.out.printf("\ntime: %.6f ms.", elapsedTime);
        
        // 测试2：尾递归
        long startTime2 = System.nanoTime();
        System.out.printf("\n===============\n");
        System.out.printf("\nfactorialTail(5) result: %d", factorialTail(5));
        double elapsedTime2 = (System.nanoTime() - startTime2) / 1_000_000.0;
        System.out.printf("\ntime: %.6f ms.", elapsedTime2);
    }
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
time: 4.737542 ms.
===============

current number: 5, accumulator: 1
current number: 4, accumulator: 5
current number: 3, accumulator: 20
current number: 2, accumulator: 60
current number: 1, accumulator: 120
factorialTail(5) result: 120
time: 0.131625 ms.%
*/