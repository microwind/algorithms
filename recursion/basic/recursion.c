/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 递归算法完整示例
 * 
 * 包含5种递归模式：
 * - 基础递归：factorial, factorial2
 * - 多分支递归：recursion, recursion2  
 * - 尾递归：tail_recursion
 * 
 * 核心三要素：
 * - 终止条件：防止无限递归
 * - 递归关系：问题分解
 * - 递归调用：自身调用
 * 
 * 学习重点：掌握递归思维，理解复杂度差异
 */
#include <stdio.h>

/**
 * 阶乘递归函数 - n! = n × (n-1)!
 * 时间复杂度: O(n)，空间复杂度: O(n)
 * @param x 要计算阶乘的整数
 * @return x的阶乘值
 */
int factorial(int x)
{
  printf("\nx=%d", x);
  
  // 递归终止条件：0! = 1, 1! = 1
  if (x == 0 || x == 1)
    return 1;

  // 递归调用：n! = n × (n-1)!
  return x * factorial(x - 1);
}

/**
 * 阶乘递归函数改进版 - 统一基本情况处理
 * @param x 要计算阶乘的整数
 * @return x的阶乘值
 */
int factorial2(int x)
{
  printf("\nx=%d", x);
  
  // 统一终止条件：0! = 1, 1! = 1
  if (x <= 1)
    return 1;

  // 递归调用：n! = n × (n-1)!
  return x * factorial2(x - 1);
}

/* 递归调用树
   f(5)
  /   \
5 * f(5 - 1)
      /    \
    4 * f(4 - 1)
         /    \
       3 * f(3 - 1)
            /   \
          2 * f(2 - 1)
               /    \
             1 * f(1 - 1)
// output
x= 5
x= 4
x= 3
x= 2
x= 1
x= 0
factorial(5) 120
*/

/**
 * 多分支递归函数 - 展示双分支递归调用
 * 时间复杂度: O(2^n)，空间复杂度: O(n)
 * @param n 输入参数
 * @return 计算结果
 */
int recursion(int n)
{
  printf("\nbegin: n=%d", n);
  
  // 递归终止条件：n ≥ 15 时返回 n
  if (n >= 15)
    return n;
  
  // 预处理：n 乘以 3
  n *= 3;

  // 双分支递归调用，返回结果和
  return recursion(n + 1) + recursion(n * 2);
}

/**
 * 尾递归函数示例 - 优化的递归形式
 * 时间复杂度: O(n)，空间复杂度: O(1)（编译器优化后）
 * @param n 当前处理的数值
 * @param accumulator 累加器，保存中间结果
 * @return 最终计算结果
 */
int tail_recursion(int n, int accumulator)
{
  // 递归终止条件：n ≥ 15 时返回累加结果
  if (n >= 15)
    return accumulator + n;
  
  // 尾递归调用，使用累加器传递结果
  return tail_recursion(n * 3 + 1, accumulator);
}

/* 递归调用树
                               f(1)
                      /                  \
                f(3 + 1)      +        f(3 * 2)
               /      \                 /         \
        f(12 + 1)  + f(12 * 2)     f(18 + 1)  + f(18 * 2)
        /      \        24             19           36
  f(39 + 1) + f(39 * 2)
      40    +    78

      total = 40 + 78 + 24 + 19 + 36 = 197

// output
begin: n= 1
begin: n= 4
begin: n= 13
begin: n= 40
begin: n= 78
begin: n= 24
begin: n= 6
begin: n= 19
begin: n= 36
recursion(1)= 197
*/

/**
 * 减法递归函数 - 展示递归中的减法操作
 * 与recursion函数对比：递归结果相减而非相加
 * @param n 输入参数
 * @return 计算结果（两个递归分支的差）
 */
int recursion2(int n)
{
  printf("\nbegin: n=%d", n);
  
  // 递归终止条件：n ≥ 15 时返回 n
  if (n >= 15)
    return n;
  
  // 预处理：n 乘以 3
  n *= 3;

  // 双分支递归调用，返回结果差
  return recursion2(n + 1) - recursion2(n * 2);
}

/*
*

                               f(1)
                      /                  \
                f(3 + 1)      -        f(3 * 2)
               /      \                 /         \
        f(12 + 1)  - f(12 * 2)     f(18 + 1)  - f(18 * 2)
        /      \        24             19           36
  f(39 + 1) - f(39 * 2)
      40    -    78

      total = (40 - 78) - (24) - (19 - 36) = -45

// output
begin: n= 1
begin: n= 4
begin: n= 13
begin: n= 40
begin: n= 78
begin: n= 24
begin: n= 6
begin: n= 19
begin: n= 36
recursion2(1)= -45
*/

int main()
{
  // 测试1：基础阶乘递归 - 预期结果：120
  printf("\r\nfactorial(5) %d", factorial(5));
  printf("\r\n===");
  
  // 测试2：改进版阶乘递归 - 预期结果：120
  printf("\r\nfactorial2(5) %d", factorial2(5));
  printf("\r\n===");
  
  // 测试3：多分支递归（加法版本） - 预期结果：197
  printf("\r\nrecursion(1) %d", recursion(1));
  printf("\r\n===");
  
  // 测试4：多分支递归（减法版本） - 预期结果：-45
  printf("\r\nrecursion2(1) %d", recursion2(1));
  
  return 0;
}

/*打印结果
jarry@Mac basic % gcc recursion.c -o recursion && ./recursion

x=5
x=4
x=3
x=2
x=1
factorial(5) 120
===
x=5
x=4
x=3
x=2
x=1
factorial2(5) 120
===
begin: n=1
begin: n=4
begin: n=13
begin: n=40
begin: n=78
begin: n=24
begin: n=6
begin: n=19
begin: n=36
recursion(1) 197
===
begin: n=1
begin: n=4
begin: n=13
begin: n=40
begin: n=78
begin: n=24
begin: n=6
begin: n=19
begin: n=36
recursion2(1) -45
*/