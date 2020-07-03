#include <stdio.h>
int getLastNumber(int n);
int getFrontNumber(int n);
/**
 * output:
 * please input the number(int) : 12345
 * lastNumber : 5
 * frontNumber : 1234
 * anti-sorting : 5-4-3-2-1-
 * sum of one by one : 15
 */
int main()
{
    int num, sum;
    printf("please input the number(int):");
    scanf("%d", &num);
    printf("lastNumber : %d", getLastNumber(num));
    printf("\nfrontNumber : %d", getFrontNumber(num));

    sum = 0;
    printf("\nanti-sorting : ");
    while (num > 0)
    {
        sum += num % 10; // 除10取模得到最后一位
        printf("%d-", num % 10);
        num = num / 10; // 得到除10的数，即减去最后一位剩下的数,一直到0;
    }
    printf("\nsum of one by one : %d\n", sum);
    return 0;
}

int getLastNumber(int n)
{
    return n % 10;
}

int getFrontNumber(int n)
{
    return n / 10;
}