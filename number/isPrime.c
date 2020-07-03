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
/**
 * 是否是素数，只能被1和自身整除，不包含1。
 * return {true : flase}
 */
bool isPrime(int n);
/**
 * output:
 * 1) 1.41 * 1.41 ~= 2 is prime.
 * 2) 1.73 * 1.73 ~= 3 is prime.
 * 3) 2.24 * 2.24 ~= 5 is prime.
 * 4) 2.65 * 2.65 ~= 7 is prime.
 * 5) 3.32 * 3.32 ~= 11 is prime.
 * 6) 3.61 * 3.61 ~= 13 is prime.
 */
int main()
{
    int i, no;
    no = 0;
    for (i = 1; i <= 15; i++)
    {

        if (isPrime(i))
        {
            no++;
            printf("%d) %.2f * %.2f ~= %d is prime.\n", no, sqrt(i), sqrt(i), i);
        }
        else
        {
            //printf("%.2f * %.2f ~= %d is no prime.\n", sqrt(i), sqrt(i), i);
        }
    }
    return 0;
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
    // 3、5、7的倍数的也不是
    if (n > 7 && (n % 3 == 0 || n % 5 == 0 || n % 7 == 0))
        return false;

    int limit;
    limit = sqrt(n) + 1;
    // 平方根这样可以减少循环，但是计算平方根也要花时间
    // 再加一位，避免平方根浮点数错误
    for (i = 3; i < limit; i += 2)
    {
        //for (i = 3; i < n; i += 2) {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
