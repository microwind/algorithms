// Copyright © https://github.com/microwind All rights reserved.
//
// @author: jarryli@gmail.com
// @version: 1.0
package main

import (
  "fmt"
  "time"
)

/*
*
 * 本例子展示普通递归与尾递归的区别
 * 1. 普通递归：递归调用后仍有计算操作，需要保留当前栈帧
 * 2. 尾递归：最后一步是递归调用，无后续操作，可被编译器优化
 * 3. Go语言对尾递归有较好的优化支持
*/

// 普通递归实现阶乘
// 参数：n为待计算的数，accumulator用于跟踪中间结果
func factorial(n, accumulator int) int {
  fmt.Printf("\ncurrent number: %d, accumulator: %d", n, accumulator)

  // 递归终止条件
  if n <= 1 {
    return 1
  }

  // 递归调用后还有乘法操作，不是尾递归
  return n * factorial(n-1, n*accumulator)
}

// 尾递归核心函数
// 参数：n为待计算的数，accumulator用于累积计算结果
func tailFactorial(n, accumulator int) int {
  fmt.Printf("\ncurrent number: %d, accumulator: %d", n, accumulator)

  // 递归终止条件，直接返回累积结果
  if n <= 1 {
    return accumulator
  }

  // 最后一步是递归调用，无其他操作，符合尾递归特征
  return tailFactorial(n-1, n*accumulator)
}

// 尾递归包装函数，提供更友好的接口
func factorialTail(n int) int {
  return tailFactorial(n, 1)
}

func main() {
  // 测试普通递归
  startTime := time.Now()
  fmt.Printf("\nfactorial(5) result: %d", factorial(5, 1))
  elapsedTime := time.Since(startTime).Microseconds() / 1000.0
  fmt.Printf("\ntime: %.6f ms.", elapsedTime)

  // 测试尾递归
  startTime2 := time.Now()
  fmt.Printf("\n===============\n")
  fmt.Printf("\nfactorialTail(5) result: %d", factorialTail(5))
  elapsedTime2 := time.Since(startTime2).Microseconds() / 1000.0
  fmt.Printf("\ntime: %.6f ms.", elapsedTime2)
}

/*
jarry@Mac tail-recursion % go run tail_factorial.go

current number: 5, accumulator: 1
current number: 4, accumulator: 5
current number: 3, accumulator: 20
current number: 2, accumulator: 60
current number: 1, accumulator: 120
factorial(5) result: 120
time: %!f(int64=000000) ms.
===============

current number: 5, accumulator: 1
current number: 4, accumulator: 5
current number: 3, accumulator: 20
current number: 2, accumulator: 60
current number: 1, accumulator: 120
factorialTail(5) result: 120
time: %!f(int64=000000) ms.%
*/
