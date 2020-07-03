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
#include <math.h>
#include <stdlib.h>
typedef enum
{
     false,
     true,
     FLASE,
     TRUE
} BOOL;
typedef int bool;
typedef char *string;
#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

/*
 * 设定一个初始值日期对应星期，通过这个日期来推算其他时间对应的星期
 * 初始值为1900年1月1日，星期一
 */
#define START_YEAR 1900
#define START_MONTH 1
#define START_DAY 1
#define START_WEEKDAY 1

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
 * 输出日历
 * output:
 * ---------------------------
 *           Jan. 2003
 * Sun  Mon  Tue  Wed  Thu  Fri  Sat
 *                 1    2    3    4
 *  5    6    7    8    9   10   11
 * 12   13   14   15   16   17   18
 * 19   20   21   22   23   24   25
 * 26   27   28   29   30   31
 */
int main()
{
     int month, day, year;

     month = 12;
     day = 30;
     year = 2003;

     // Test
     int days = getMonthDays(month, year);
     int weekday = getWeekdayOfDate(month, day, year);

     printf("[%d] = %s\n", weekday, weeklyArray[weekday]);

     printf("TEST : \n-------------------------\n %s %d days = %d", getMonthName(month), year, days);
     printf("\n%d-%d-%d is %s = weeklyArray[%d]", year, month, day, weeklyArray[weekday], weekday);
     printf("\n---------------------------\n");
     // Test end

     // output the calander
     int tmp_month = 0, tmp_year = year;
     int max_month = 48; // two years
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

void printCalender(int month, int year)
{
     int firstWeekday, lastWeekday, weekday, ndays, day;
     printCalanderTitle(month, year); // 日历标题
     printWeeklyTitle();              // 星期名称
     printf("\n");
     firstWeekday = getFirstWeekdayOfMonth(month, year); // 当月第一天是周几
                                                         //printIndentFirstLine(firstWeekday);                        // 根据第一天是周几打印缩进

     weekday = firstWeekday;                       // 设当前星期为当月的第一个星期几
     printLastMonthLastDays(weekday, month, year); // 打印上个月的最后几天
     ndays = getMonthDays(month, year);            // 当月一共多少天

     for (day = 1; day <= ndays; day++)
     { // 循环输出日历
          printf("%2s", "");
          printf("%3d", day);
          if (weekday == SATURDAY)
               printf("\n");           // 设定星期六换行换行
          weekday = (weekday + 1) % 7; // weekday按7天轮循
     }

     lastWeekday = getLastWeekdayOfMonth(month, year);
     printNextMonthStartDays(lastWeekday);
}

void printWeeklyTitle()
{
     int i;
     int len = sizeof(weeklyArray) / sizeof(weeklyArray[0]);
     for (i = 0; i < len; i++)
     {
          printf("%5s", weeklyArray[i]); // 根据静态数组循环输出星期名
     }
}

void printLastMonthLastDays(int weekday, int month, int year)
{
     int lastDays = getLastMonthDays(month, year);
     int i = lastDays - weekday + 1;
     for (; i <= lastDays; i++)
     {
          printf("%2s%2d]", "", i); // 根据第一天是周几打印上个月最后几天
     }
}

void printIndentFirstLine(int weekday)
{
     int i;
     for (i = 0; i < weekday; i++)
     {
          printf("%5s", ""); // 根据第一行是周几打印空行或者输入日期
     }
}

void printNextMonthStartDays(int weekday)
{
     int i;
     int nextDays = 7 - weekday;
     for (i = 1; i < nextDays; i++)
     {
          printf("%2s%2d]", "", i);
     }
}

void printCalanderTitle(int month, int year)
{
     printf("%12s%4s %d\n", "", getMonthName(month), year);
}

/*
 * 返回某月的天数
 * 4 6 9 11为30天，1 3 5 7 8 10 12为31天
 * 2月如果是闰年29，否则28天
 * @param  month
 * @parma  year
 * @return days 天数
 */
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

/**
 * 得到上个月最后一天有多少天
 * @see getMonthDays(int month, int year)
 */
int getLastMonthDays(int month, int year)
{
     int nextMonth;
     nextMonth = month > 1 ? month - 1 : 12; // 上个月是当前月减去1
     year = month > 1 ? year : year - 1;     // 如果是1月份则是12月，年也减去1
     return getMonthDays(nextMonth, year);
}

int getFirstWeekdayOfMonth(int month, int year)
{
     return getWeekdayOfDate(month, 1, year);
}

int getLastWeekdayOfMonth(int month, int year)
{
     int lastDay = getMonthDays(month, year);
     return getWeekdayOfDate(month, lastDay, year);
}

/**
 * 从过去的一个日期里得到总天数
 * ndays可以是int或long类型
 */
long getDaysFromPassedDate(int month, int day, int year)
{
     int i, weekday;
     long ndays;              // 一共有多少天
     weekday = START_WEEKDAY; // 当前周几取自define常量
     ndays = weekday - 1;     // 减去自身的这1天

     for (i = year; i < START_YEAR; i++)
     {
          ndays -= 365;
          if (isLeapYear(i))
               ndays -= 1; // 闰年366
     }
     for (i = START_MONTH; i < month; i++)
     {
          ndays += getMonthDays(i, year); // 若月份大于1，则根据每月的天数增加
     }
     if (day > START_DAY)
          ndays += (day - START_DAY); // 如果比初始天要大，初始天加上与k天之间的差

     return ndays;
}

/**
 * 根据当前是周几返回多少天以前是周几
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
 * 根据得到N天前是星期几，时间早于设定的初日期
 * 
 * @param  month 
 * @parma  dya  
 * @return year 
 * @see int getWeekdayOfPassedDays (int weekday, int passedDays)
 * @see int getDaysFromPassedDate (int month, int day, int year)
 */
int getWeekdayBeforeStartYear(int month, int day, int year)
{
     int weekday;
     long ndays = getDaysFromPassedDate(month, day, year);
     weekday = getWeekdayOfPassedDays(ndays);
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
 * 返回闰年
 * 闰年每4年一次，凡00结尾的除外，00结尾中能整除400的也是闰年
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