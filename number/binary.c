#include <stdio.h>
#include <math.h>

void decimalToBinary(int num);
void binaryToDecimal(long num);
void decimal2Binary(int num);

int main()
{
  decimalToBinary(20);
  decimal2Binary(20);
  binaryToDecimal(10100L);
  return 0;
}

int length(double n)
{
  return (int)log10(n) + 1;
}

void decimalToBinary(int num)
{
  int remainder;
  int pvoit = 2;
  // 不断除2取余，倒序打印余数。
  printf("\n %d convert to binary: ", num);
  while (num != 0)
  {
    remainder = num % pvoit;
    num /= pvoit;
    // printf("%d / %d = %d remainder %d", num, pvoit, remainder);
    printf("%d", remainder);
  }
}

void decimal2Binary(int num)
{
  long binary = 0L;
  int remainder;
  int i = 1;
  int step = 1;
  int pvoit = 2;
  int origin = num;
  while (num != 0)
  {
    remainder = num % pvoit;
    // printf("Step %d: %d/2, remainder = %d, quotient = %d\n", step++, num, remainder, num / 2);
    num /= pvoit;
    // 以余数乘以位数相加
    binary += remainder * 10;
    i *= 10;
  }
  printf("\n %d convert to binary: %ld", origin, binary);
}

void binaryToDecimal(long num)
{
  long origin = num;
  int decimal = 0;
  int i = 0;
  int remainder;
  int pvoit = 10;
  while (num != 0)
  {
    remainder = num % pvoit;
    num /= pvoit;
    // 从右往左用二进制的每个数去乘以2的次方，次方是数字的位置，以0开始，从右往左递增
    decimal += remainder * pow(2, i);
    i++;
  }
  printf("\n %ld convert to decimal: %d", origin, decimal);
}