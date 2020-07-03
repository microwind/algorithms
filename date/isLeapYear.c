#include <stdio.h>
#include <stdlib.h>
//#include <genlib.h>

typedef enum
{
    false,
    true,
    FLASE,
    TRUE
} BOOL;
typedef int bool;
bool isLeapYear(int year);
/**
 * output:
 * please input the year(format:1999):2004
 * 2004 is a leap year
 */
int main()
{
    int year;
    printf("please input the year(format:1999):");

    scanf("%d", &year);
    printf("%d is ", year);
    if (isLeapYear(year))
    {
        printf("a leap year");
    }
    else
    {
        printf("not leap year");
    }

    getchar();
    return 0;
}

bool isLeapYear(int year)
{
    //return ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0) );

    if ((year % 4 == 0) && (year % 100 != 0))
    {
        // 闰年每4年一次，但00结尾的年除外
        return true;
    }
    else if (year % 400 == 0)
    {
        // 以00结尾的年如能被400整除也是闰年
        return true;
    }
    else
    {
        return false;
    }
}