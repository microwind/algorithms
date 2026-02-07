#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef int bool;
typedef enum
{
  false,
  true,
  FLASE,
  TRUE
} BOOL;

bool isPrime(int n);
void factorization(int n);

/**
 * output:
 * 90 = 2 * 3 * 3 * 5
 * ====
 * 2 * 3 * 3 * 5 = 90
 */
int main()
{

  int num, k = 1, flag = 1;

  printf("please input the number: ");

  scanf("%d", &num);

  int n = num;
  // 调用函数
  printf("%d = ", n);
  factorization(n);

  // 直接输出
  printf("\n====\n");

  while (num != flag)
  {
    // flag为1，如果num等于1表示分解完毕

    while (isPrime(k))
    {
      // 如果是素数就执行

      if (num % k == 0)
      {
        // 如果是素数并且是num的约数，打印输出

        printf("%d", k);
        // 重新给num赋值为除以该素数的商

        num /= k;

        // 输出乘号，最后一个不输出
        if (num != 1)
          printf(" * ");
      }
      else
      {

        k++;
        // k是素数，但是不能被整除，k递加直到能被整除
      }
    }
    // 如果k非素数，则i递加
    k++;
  }
  printf(" = %d", n);
  getchar();

  return 0;
}

/**
 * 将一个正整数按素数分解，这个分解是唯一的。例如：输入90.打印出2 * 2 * 3。 
 * - 思路：应先找到能被该数整除的最小素数，然后给这个数重新赋值为除以素数的商：
 × - 设该数为n，设k为1。得到一个能被n整除的最小素数k;   
 * - 如k是素数，且能被n整除，打印输出这个最小的素数。 
 * - 用n除以k的商,作为新的正整数n, 继续循环得到能被新的n整除的最小素数。
 * - 如果n不能被k整除，则用k+1作为k的值,重复执行第一步，直到完全分解(n=n/n=1)。
 */
void factorization(int n)
{

  int k = 1;
  while (n != 1)
  {
    // 如果n不等于1，也就是没有分解完成，则继续循环分解
    while (isPrime(k) && n % k == 0)
    {
      // 得到能被整除的最小的素数k。k是素数且能被n整除，打印k。
      printf("%d", k);
      if (n / k != 1)
        printf(" * ");
      n /= k;
      // n赋值为n除k的商，得到新的正整数
      // 继续循环，判断k是否为素数和能否被n整除
    }
    k++;
    // k递加，重新执行循环直到完全分解
  }
}

bool isPrime(int n)
{

  int i;

  if (n <= 1)
    return false; // 1不是
  if (n == 2)
    return true; // 2是
  if (n % 2 == 0)
    return false; // 偶数不是

  int limit;
  limit = sqrt(n) + 1;

  // 平方根这样可以减少循环，但是计算平方根也要花时间
  // 再加一位，避免平方根浮点数错误
  for (i = 3; i < limit; i += 2)
  {

    if (n % i == 0)
    {

      return false;
    }
  }

  return true;
}