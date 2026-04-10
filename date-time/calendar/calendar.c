/*
 * Copyright  https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 完整版日历打印程序 (Calendar - Full Version)
 * 根据年月输出当月日历，支持显示前后月份日期
 * 
 * 核心算法：
 * 1. 以1900年1月1日（星期一）为基准日期
 * 2. 使用累加天数法计算任意日期是星期几
 * 3. 支持1900年之前日期的计算（反向推算）
 * 4. 日历显示包含上个月末尾几天和下个月开头几天
 * 
 * 闰年判断：能被4整除且不能被100整除，或能被400整除
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
// 布尔类型定义，兼容C89/C90标准
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
#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

// 基准日期设定：1900年1月1日，星期一
// 这是计算任意日期星期几的参考起点
// 算法原理：计算目标日期与基准日期的天数差，然后用模7运算得到星期
#define START_YEAR 1900    // 基准年份
#define START_MONTH 1      // 基准月份（1月）
#define START_DAY 1        // 基准日期（1日）
#define START_WEEKDAY 1    // 基准星期（1=星期一，与MONDAY宏对应）

// 星期名称数组（英文缩写）
static string weeklyArray[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

/**
 * 根据年月打印日历函数(mm, yyyy)
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
 * 根据第一天是周几，判断在第一行有多少空格缩进
 */
void printIndentFirstLine(int weekday);
/**
 * 根据第一天是周几，打印上个月最后的几个日期
 */
void printLastMonthLastDays(int weekday, int month, int year);

/**
 * 根据最后一个星期几少于星期六，打印下个月日期
 */
void printNextMonthStartDays(int weekday);

/**
 * 根据数字得到对应月份名称
 */
string getMonthName(int month);

/**
 * 判断是否为闰年
 */
bool isLeapYear(int year);

/**
 * 根据月和年，返回该月有多少天
 */
int getMonthDays(int month, int year);
/**
 * 返回上个月有多少天
 */
int getLastMonthDays(int month, int year);

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

/**
 * 输入年月(mmyyyy)，得到该月最后一天是周几
 */
int getLastWeekdayOfMonth(int month, int year);

/*
 * 得到早于初始日期的某个日期是周几
 */
int getWeekdayBeforeStartYear(int month, int day, int year);
/*
 * 得到过去日期一共有多少天
 */
long getDaysFromPassedDate(int month, int day, int year);
/*
 * 根据过去N天和当前是周几计算得到过去N天是周几
 */
int getWeekdayOfPassedDays(long passedDays);

/**
 * main函数：测试入口
 * 测试内容：
 * 1. 验证getMonthDays函数：计算2003年12月有31天
 * 2. 验证getWeekdayOfDate函数：计算2003年12月30日是周几
 * 3. 循环打印48个月的日历（从2003年12月开始，连续打印4年）
 */
int main()
{
     int month, day, year;

     // 测试数据：2003年12月30日
     month = 12;
     day = 30;
     year = 2003;

     // 测试1：获取月份天数
     int days = getMonthDays(month, year);
     // 测试2：计算指定日期是星期几
     int weekday = getWeekdayOfDate(month, day, year);

     printf("[%d] = %s\n", weekday, weeklyArray[weekday]);

     printf("TEST : \n-------------------------\n %s %d days = %d", getMonthName(month), year, days);
     printf("\n%d-%d-%d is %s = weeklyArray[%d]", year, month, day, weeklyArray[weekday], weekday);
     printf("\n---------------------------\n");

     // 测试3：循环打印48个月的日历（4年）
     int tmp_month = 0, tmp_year = year;
     int max_month = 48; // 4年的月份数
     for (month = 0; month < max_month; month++)
     {
          tmp_month++;
          if (tmp_month == 13)
          {
               tmp_month = 1;
               tmp_year += 1;
          }
          printf("%d-%d\n", tmp_month, tmp_year);
          printCalender(tmp_month, tmp_year);
          printf("\n");
     }
     return 0;
}

/**
 * printCalender函数实现：打印完整日历（包含前后月份日期）
 * 执行流程：
 * 1. 打印标题（月份年份）
 * 2. 打印星期标题行
 * 3. 计算当月第一天是周几
 * 4. 打印上个月末尾几天（填充第一行）
 * 5. 循环打印当月所有日期
 * 6. 打印下个月开头几天（填充最后一行）
 */
void printCalender(int month, int year)
{
     int firstWeekday, lastWeekday, weekday, ndays, day;
     
     // 步骤1-2：打印标题和星期标题
     printCalanderTitle(month, year);
     printWeeklyTitle();
     printf("\n");
     
     // 步骤3：计算当月第一天是周几
     firstWeekday = getFirstWeekdayOfMonth(month, year);
     
     // 步骤4：打印上个月最后几天（用"]"标记）
     weekday = firstWeekday;
     printLastMonthLastDays(weekday, month, year);
     
     // 获取当月总天数
     ndays = getMonthDays(month, year);

     // 步骤5：循环输出当月所有日期
     for (day = 1; day <= ndays; day++)
     {
          printf("%2s", "");         // 前导空格保持对齐
          printf("%3d", day);        // 输出日期数字
          if (weekday == SATURDAY)
               printf("\n");         // 周六换行
          weekday = (weekday + 1) % 7; // 星期循环
     }

     // 步骤6：打印下个月开头几天（用"]"标记）
     lastWeekday = getLastWeekdayOfMonth(month, year);
     printNextMonthStartDays(lastWeekday);
}

/**
 * 根据过去N天和当前是周几计算得到过去N天是周几
 * 分析：过去的天数等于除7取余数
 * - ndays = ndasy % 7
 * - 比较ndays 与 开始的周几
 * - 如果ndays < 开始的周几，则weekday = (START_WEEKDAY - ndasy) % 7 
 * - 否则, 7 减去 ndays 与 START_WEEKDAY之间的差
 * 
 * @param  weekday          当前是周几
 * @param  passedDays       N天以前
 * @return weekday          新的周几
 */
int getWeekdayOfPassedDays(long passedDays)
{
     int weekday;
     long ndays = passedDays; //得到N天前的绝对值，除7得到余数。
     ndays = abs((int)ndays) % 7;
     if (START_WEEKDAY > ndays)
     { // 如果开始日期大于N天，则表示仍在本周内。如周4的3天前是周1。
          weekday = (START_WEEKDAY - ndays) % 7;
     }
     else
     { // 如果START_WEEKDAY比N天小，则表示追溯到上周，7减去当前周几与N天的差。
          weekday = 7 - (ndays - START_WEEKDAY);
     }
     return weekday;
}

/**
 * 本例是用来得到N天后是星期几的函数
 * 根据1900-1-1是星期一
 * 往后的日期得到一个天数，然后通过公式(weekday + k天) / 7 取余数得到。
 */
int getWeekdayOfDate(int month, int day, int year)
{
     if (year < START_YEAR)
          return getWeekdayBeforeStartYear(month, day, year);

     int i, weekday, ndays;
     weekday = START_WEEKDAY;
     // ndays    = weekday;                                   // 总天数
     for (i = START_YEAR; i < year; i++)
     {
          // ndays += 365;
          weekday = (weekday + 365) % 7;
          if (isLeapYear(i))
          {
               //ndays += 1;
               weekday = (weekday + 1) % 7; // 闰年增加1天到366
          }
     }
     for (i = START_MONTH; i < month; i++)
     {
          // ndays += getMonthDays(i, year);
          weekday = (weekday + getMonthDays(i, year)) % 7; // 根据每月的天数增加
     }
     if (day > START_DAY)
     {
          // ndays += (day - START_DAY);
          weekday = (weekday + (day - START_DAY)) % 7;        // 如果比初始天要大，初始天加上与k天之间的差
     }
     //return (weekday = ndays % 7);                          // 当前周几加上k天除7取余数，得到k天后是周几
     return weekday;
}

/**
 * isLeapYear函数实现：闰年判断
 * 闰年规则（格里高利历）：
 * 1. 能被4整除但不能被100整除，或
 * 2. 能被400整除
 * 
 * 逻辑表达式解析：
 * - (year % 4 == 0 && year % 100 != 0)：能被4整除但不能被100整除
 * - || (year % 400 == 0)：或者能被400整除（如2000年是闰年）
 * 
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
 * 获取某月的天数
 * 根据月份和年份（考虑闰年）返回该月天数
 */
int getMonthDays(int month, int year)
{
     switch (month)
     {
     case 2:
          return isLeapYear(year) ? 29 : 28;
     case 4:
     case 6:
     case 9:
     case 11:
          return 30;
     default:
          return 31;
     }
}

/**
 * 获取上个月的天数
 */
int getLastMonthDays(int month, int year)
{
     int lastMonth = (month > 1) ? month - 1 : 12;
     int lastYear = (month > 1) ? year : year - 1;
     return getMonthDays(lastMonth, lastYear);
}

/**
 * 打印日历标题
 * 格式：月份名称 + 年份，居中显示
 */
void printCalanderTitle(int month, int year)
{
     printf("%12s%s %d\n", "", getMonthName(month), year);
}

/**
 * 打印星期标题
 * 输出：Sun Mon Tue Wed Thu Fri Sat
 */
void printWeeklyTitle()
{
     int i;
     for (i = 0; i < 7; i++)
     {
          printf("%5s", weeklyArray[i]);
     }
}

/**
 * 打印上个月最后几天（用"]"标记）
 * 根据当月第一天是周几，计算并打印上个月末尾的日期
 */
void printLastMonthLastDays(int weekday, int month, int year)
{
     int lastDays = getLastMonthDays(month, year);
     int startDay = lastDays - weekday + 1;
     int i;
     for (i = startDay; i <= lastDays; i++)
     {
          printf("%2s%2d]", "", i);
     }
}

/**
 * 打印下个月开始几天（用"]"标记）
 * 根据当月最后一天是周几，计算并打印下个月开头的日期
 */
void printNextMonthStartDays(int weekday)
{
     int nextDays = 7 - weekday;
     int i;
     for (i = 1; i < nextDays; i++)
     {
          printf("%2s%2d]", "", i);
     }
}

/**
 * 获取某月第一天是星期几
 * 调用getWeekdayOfDate计算该月1日的星期
 */
int getFirstWeekdayOfMonth(int month, int year)
{
     return getWeekdayOfDate(month, 1, year);
}

/**
 * 获取某月最后一天是星期几
 * 调用getWeekdayOfDate计算该月最后一天的星期
 */
int getLastWeekdayOfMonth(int month, int year)
{
     int lastDay = getMonthDays(month, year);
     return getWeekdayOfDate(month, lastDay, year);
}

/**
 * 获取早于基准日期（1900年前）的某个日期是星期几
 * 通过计算从目标日期到1900年1月1日的天数差，反向推算
 */
int getWeekdayBeforeStartYear(int month, int day, int year)
{
     long days = getDaysFromPassedDate(month, day, year);
     return getWeekdayOfPassedDays(days);
}

/**
 * 获取过去日期一共有多少天
 * 计算从目标日期到1900年1月1日之间的天数
 */
long getDaysFromPassedDate(int month, int day, int year)
{
     long ndays = 0;
     int i;

     // 累加从目标年份到1900年的年天数
     for (i = year; i < START_YEAR; i++)
     {
          ndays += 365;
          if (isLeapYear(i))
               ndays += 1;
     }

     // 累加从目标月份到1月的天数
     for (i = month; i > START_MONTH; i--)
     {
          ndays += getMonthDays(i - 1, year);
     }

     // 累加从目标日期到1日的天数
     if (day > START_DAY)
          ndays += (day - START_DAY);

     return ndays;
}

/*打印结果
jarry@Mac calendar % gcc calendar.c -o calendar && ./calendar
[2] = Tue
TEST : 
-------------------------
 Dec. 2003 days = 31
2003-12-30 is Tue = weeklyArray[2]
---------------------------
1-2003
            Jan. 2003
  Sun  Mon  Tue  Wed  Thu  Fri  Sat
  29]  30]  31]    1    2    3    4
    5    6    7    8    9   10   11
   12   13   14   15   16   17   18
   19   20   21   22   23   24   25
   26   27   28   29   30   31   1]
2-2003
*/