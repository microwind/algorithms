#include <stdio.h>
/**
 * output:
 * please input the first number(int):12
 * please input the second number(int):15
 * 12 + 15的平均值  = 13 * 
 */
int main()
{
    int b, h, a;
    printf("please input the first number(int):");
    scanf("%d", &b);
    printf("please input the second number(int):");
    scanf("%d", &h);
    a = (b + h) / 2;
    printf("%d + %d  average  = %d\n", b, h, a);
    return 0;
}