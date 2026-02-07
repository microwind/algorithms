/**
 * @file: calendar.c
 * @author: jarryli
 * @desc: 根据年月输出当月日历
 * @date: 2003-2-1
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
typedef enum
{
    false,
    true,
    FLASE,
    TRUE
} BOOL;
typedef int bool;
typedef char *string;
#define sunday 0
#define monday 1
#define tuesday 2
#define wednesday 3
#define thursday 4
#define friday 5
#define saturday 6

// 初始为1900年1月1日，星期一
#define startYear 1900
#define startMonth 1
#define startDay 1
#define startWeekday 1

/**
 * 打印日历函数(mm, yyyy)
 */
void printCalender(int month, int year);

/**
 * 打印日历标题，月与年
 */
void printCalanderTitle(int month, int year);

/**
 * 打印周标题，根据weeklyArray输出
 */
void printWeeklyTitle();

/**
 * 根据第一天是周几，判断在第一行输出多少空格
 */
void printIndentFirstLine(int weekday);

/**
 * 根据数字得到对应月份名称
 */
string getMonthName(int month);

/**
 * 判断是否为闰年
 * ---------------------------
 * 闰年每4年一次，凡00结尾的除外，00结尾中能整除400的也是闰年
 */
bool isLeapYear(int year);

/**
 * 根据月和年，返回该月有多少天
 * ----------------------------
 * 4 6 9 11为30天，1 3 5 7 8 10 12为31天
 * 2月如果是闰年29，否则28天
 */
int getMonthDays(int month, int year);

/**
 * 输入有效的年月日(mmddyyyy)，得到某年某月的第一天是星期几
 * ----------------------------
 * 公式：(weekday + k) % 7 = k天后是周几
 * 初始日期为1900年1月1日，星期1
 * 根据1年365天闰年366年，再加上每月的天数计算出
 × 离某年某月的第1天还有多少天，再根据公式返回星期几
 */
int getWeekdayOfDate(int month, int day, int year);

/**
 * 输入年月(mmyyyy)，得到该月第一天是周几
 */
int getFirstWeekdayOfMonth(int month, int year);

static string weeklyArray[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

/**
 * 输出一个日历
 * output:
 * 
 * 
 */
int main()
{
    int month, day, year;

    month = 1;
    day = 11;
    year = 2010;

    // Test
    int days = getMonthDays(month, year);
    int weekday = getWeekdayOfDate(month, day, year);
    printf("TEST : \n-------------------------\n %s %d days = %d", getMonthName(month), year, days);
    printf("\n%d-%d-%d is %s = weeklyArray[%d]", year, month, day, weeklyArray[weekday], weekday);
    printf("\n---------------------------\n");
    // Test end

    // output the calander
    printCalender(month, year);
    return 0;
}

void printCalender(int month, int year)
{
    int firstWeekday, weekday, ndays, day;
    printCalanderTitle(month, year); // 日历标题
    printWeeklyTitle();              // 星期名称
    printf("\n");
    firstWeekday = getFirstWeekdayOfMonth(month, year); // 当月第一天是周几
    printIndentFirstLine(firstWeekday);                 // 根据第一天是周几打印缩进

    weekday = firstWeekday;            // 设当前星期为当月的第一个星期几
    ndays = getMonthDays(month, year); // 当月一共多少天

    // 循环输出日历
    for (day = 1; day <= ndays; day++)
    {
        printf("%2s", "");
        printf("%3d", day);
        if (weekday == saturday)
            printf("\n");            // 设定星期六换行换行
        weekday = (weekday + 1) % 7; // weekday按7天轮循
    }
}

void printWeeklyTitle()
{
    int i;
    int len = sizeof(weeklyArray) / sizeof(weeklyArray[0]);
    for (i = 0; i < len; i++)
    {
        printf("%5s", weeklyArray[i]);
        // 根据静态数组循环输出星期名
    }
}

void printIndentFirstLine(int weekday)
{
    int i;
    for (i = 0; i < weekday; i++)
    {
        printf("%5s", "");
        // 根据第一行是周几打印空行
    }
}

void printCalanderTitle(int month, int year)
{
    printf("%12s%4s %d\n", "", getMonthName(month), year);
}

int getMonthDays(int month, int year)
{
    switch (month)
    {
    case 2:
        return (isLeapYear(year) ? 29 : 28);
    case 4:
    case 6:
    case 9:
    case 11:
        return (30);
    default:
        return (31);
    }
}

int getFirstWeekdayOfMonth(int month, int year)
{
    return getWeekdayOfDate(month, 1, year);
}

int getWeekdayOfDate(int month, int day, int year)
{
    int i, weekday, ndays;
    weekday = startWeekday;
    ndays = weekday;
    for (i = startYear; i < year; i++)
    {
        ndays += 365;
        if (isLeapYear(i))
            ndays += 1;
        // 闰年增加1天到366
    }
    for (i = startMonth; i < month; i++)
    {
        ndays += getMonthDays(i, year);
        // 根据每月的天数增加
    }
    if (day > startDay)
        ndays += (day - startDay);
    // 如果比初始天要大，初始天加上与k天之间的差

    //当前周几加上k天除7取余数，得到k天后是周几
    return (weekday = ndays % 7);
}

bool isLeapYear(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

string getMonthName(int month)
{
    switch (month)
    {
    case 1:
        return ("Jan.");
    case 2:
        return ("Feb.");
    case 3:
        return ("Mar.");
    case 4:
        return ("Apr.");
    case 5:
        return ("May");
    case 6:
        return ("Jun.");
    case 7:
        return ("Jul.");
    case 8:
        return ("Aug.");
    case 9:
        return ("Sep.");
    case 10:
        return ("Oct.");
    case 11:
        return ("Nov.");
    case 12:
        return ("Dec.");
    default:
        return ("Illegal month");
    }
}