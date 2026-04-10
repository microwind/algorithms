/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日历打印程序 (Calendar Print)
 * 根据年月输出当月日历，支持计算某日期是星期几
 * 
 * 核心算法：
 * 1. 以1900年1月1日（星期一）为基准日期
 * 2. 计算目标日期与基准日期之间的天数差
 * 3. 使用公式：(基准星期 + 天数差) % 7 = 目标星期
 * 4. 闰年判断：能被4整除且不能被100整除，或能被400整除
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
// 布尔类型定义，兼容C89/C90标准
// true=1, false=0 表示布尔真假值
typedef enum
{
    false,
    true,
    FLASE,
    TRUE
} BOOL;
typedef int bool;      // 简化布尔类型别名
typedef char *string;  // 字符串类型别名
// 星期枚举定义，0=周日，1=周一，...，6=周六
// 符合国际标准ISO 8601中星期的编号方式
#define sunday 0
#define monday 1
#define tuesday 2
#define wednesday 3
#define thursday 4
#define friday 5
#define saturday 6

// 基准日期设定：1900年1月1日，星期一
// 这是计算任意日期星期几的参考起点
// 算法原理：计算目标日期与基准日期的天数差，然后用模7运算得到星期
#define startYear 1900    // 基准年份
#define startMonth 1      // 基准月份（1月）
#define startDay 1        // 基准日期（1日）
#define startWeekday 1    // 基准星期（1=星期一，与monday宏对应）

/**
 * 打印指定年月的完整日历
 * 参数：
 *     month - 月份 (1-12)
 *     year - 年份 (如2024)
 * 功能：输出格式化后的月历，包括标题、星期标题和所有日期
 */
void printCalender(int month, int year);

/**
 * 打印日历标题（月份和年份）
 * 参数：month - 月份，year - 年份
 * 输出格式：居中显示的"Month Year"，如"    Jan. 2024"
 */
void printCalanderTitle(int month, int year);

/**
 * 打印星期标题行
 * 根据weeklyArray数组输出星期名称（Sun Mon Tue Wed Thu Fri Sat）
 * 每个名称占5个字符宽度，便于与日期对齐
 */
void printWeeklyTitle();

/**
 * 打印日历第一行的缩进空格
 * 参数：weekday - 当月第一天是星期几 (0-6)
 * 功能：根据第一天是周几，在第一行输出相应数量的空格，使日期对齐
 * 例如：如果第一天是周三(3)，则输出3个空位（每个占5字符）
 */
void printIndentFirstLine(int weekday);

/**
 * 根据月份数字获取英文月份名称
 * 参数：month - 月份 (1-12)
 * 返回：对应的英文月份缩写（如"Jan.", "Feb."等）
 * 如果月份无效，返回"Illegal month"
 */
string getMonthName(int month);

/**
 * 判断指定年份是否为闰年
 * 闰年规则（格里高利历）：
 * 1. 能被4整除但不能被100整除，或
 * 2. 能被400整除
 * 参数：year - 年份
 * 返回：true是闰年，false不是闰年
 * 示例：2000年是闰年，1900年不是闰年，2024年是闰年
 */
bool isLeapYear(int year);

/**
 * 获取指定年月的天数
 * 参数：
 *     month - 月份 (1-12)
 *     year - 年份
 * 返回：该月的天数
 * 规则：
 *     - 4,6,9,11月：30天
 *     - 1,3,5,7,8,10,12月：31天
 *     - 2月：闰年29天，平年28天
 */
int getMonthDays(int month, int year);

/**
 * 计算指定日期是星期几
 * 核心算法：基于基准日期1900年1月1日（星期一）计算
 * 公式：(startWeekday + 天数差) % 7 = 目标星期
 * 参数：
 *     month - 月份 (1-12)
 *     day - 日期 (1-31)
 *     year - 年份
 * 返回：星期几 (0=周日, 1=周一, ..., 6=周六)
 * 计算步骤：
 *     1. 累加从1900年到目标年份-1的所有天数（考虑闰年）
 *     2. 累加从1月到目标月份-1的所有天数
 *     3. 加上目标日期与1日的差值
 *     4. 对7取模得到星期
 */
int getWeekdayOfDate(int month, int day, int year);

/**
 * 获取指定年月的第一天是星期几
 * 参数：month - 月份，year - 年份
 * 返回：该月第一天的星期 (0-6)
 * 这是printCalender函数中计算缩进的基础
 */
int getFirstWeekdayOfMonth(int month, int year);

static string weeklyArray[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

/**
 * printCalender函数实现：打印完整日历
 * 执行流程：
 * 1. 打印标题（月份年份）
 * 2. 打印星期标题行
 * 3. 计算当月第一天是周几，打印相应缩进
 * 4. 循环打印每一天，周六后换行
 */
void printCalender(int month, int year)
{
    int firstWeekday, weekday, ndays, day;
    printCalanderTitle(month, year); // 步骤1：输出日历标题
    printWeeklyTitle();              // 步骤2：输出星期名称行
    printf("\n");
    firstWeekday = getFirstWeekdayOfMonth(month, year); // 步骤3a：计算当月第一天星期
    printIndentFirstLine(firstWeekday);                 // 步骤3b：打印第一行缩进

    weekday = firstWeekday;            // 初始化当前星期为当月第一天
    ndays = getMonthDays(month, year); // 获取当月总天数

    // 步骤4：循环输出每一天
    for (day = 1; day <= ndays; day++)
    {
        printf("%2s", "");         // 前导空格，保持对齐
        printf("%3d", day);          // 输出日期数字（占3字符）
        if (weekday == saturday)
            printf("\n");            // 周六换行，开始新的一周
        weekday = (weekday + 1) % 7; // 星期循环：0->1->...->6->0
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

/**
 * isLeapYear函数实现：闰年判断
 * 逻辑表达式解析：
 * - (year % 4 == 0 && year % 100 != 0)：能被4整除但不能被100整除
 * - || (year % 400 == 0)：或者能被400整除（如2000年是闰年）
 * 注意：1900年能被4整除也能被100整除，但不能被400整除，所以不是闰年
 */
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

/**
 * main函数：测试入口
 * 测试内容：
 * 1. 验证getMonthDays函数：计算2010年1月有31天
 * 2. 验证getWeekdayOfDate函数：计算2010年1月11日是周一(weeklyArray[1])
 * 3. 打印2010年1月日历
 * 4. 打印2026年4月日历
 */
int main()
{
    int month, day, year;

    // 测试数据：2010年1月11日
    month = 1;
    day = 11;
    year = 2010;

    // 测试1：获取月份天数
    int days = getMonthDays(month, year);
    // 测试2：计算指定日期是星期几
    int weekday = getWeekdayOfDate(month, day, year);
    
    // 输出测试结果
    printf("TEST : \n-------------------------\n %s %d days = %d", getMonthName(month), year, days);
    printf("\n%d-%d-%d is %s = weeklyArray[%d]", year, month, day, weeklyArray[weekday], weekday);
    printf("\n---------------------------\n");

    // 测试3：打印2010年1月日历
    printCalender(month, year);

    // 测试4：打印2026年4月日历（额外测试）
    printCalender(4, 2026);
    return 0;
}

/*打印结果
jarry@Mac calendar % gcc calendar_simple.c -o calender_simple && ./calender_simple
TEST : 
-------------------------
 Jan. 2010 days = 31
2010-1-11 is Mon = weeklyArray[1]
---------------------------
            Jan. 2010
  Sun  Mon  Tue  Wed  Thu  Fri  Sat
                             1    2
    3    4    5    6    7    8    9
   10   11   12   13   14   15   16
   17   18   19   20   21   22   23
   24   25   26   27   28   29   30
   31            Apr. 2026
  Sun  Mon  Tue  Wed  Thu  Fri  Sat
                   1    2    3    4
    5    6    7    8    9   10   11
   12   13   14   15   16   17   18
   19   20   21   22   23   24   25
   26   27   28   29   30% 
*/