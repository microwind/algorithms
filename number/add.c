#include <stdio.h>
/**
 * output:
 * please input the first number(int):12
 * please input the second number(int):14
 * 12 + 14  = 26
 */
int main()
{
    int b, h, a;
    printf("please input the first number(int):");
    scanf("%d", &b);
    printf("please input the second number(int):");
    scanf("%d", &h);
    a = (b + h);
    printf("%d + %d  = %d\n", b, h, a);
    return 0;
}