#include <stdio.h>
#include <stdlib.h>
//#include <genlib.h>

int abs(int n);
/**
 * output:
 * 
 */
int main()
{
    int number;
    printf("please input one negative number, get absolute value :");

    scanf("%d", &number);
    printf("your input is %d, it's abs = %d .", number, abs(number));

    getchar();
    return 0;
}

int abs(int n)
{
    if (n > 0)
    {
        return n;
    }
    else
    {
        return -n;
    }
}