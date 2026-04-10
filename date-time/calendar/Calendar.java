/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 完整版日历打印程序 (Calendar - Full Version)
 * 根据年月输出当月日历，支持显示前后月份日期
 * 
 * 核心算法：
 * 1. 以1900年1月1日（星期一）为基准日期
 * 2. 使用累加天数法计算任意日期是星期几
 * 3. 日历显示包含上个月末尾几天和下个月开头几天
 */

class Calendar {
    
    // 基准日期设定：1900年1月1日，星期一
    private static final int START_YEAR = 1900;
    private static final int START_MONTH = 1;
    private static final int START_DAY = 1;
    private static final int START_WEEKDAY = 1; // 1=星期一
    
    // 星期标题
    private static final String[] WEEKDAYS = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    
    // 月份名称
    private static final String[] MONTH_NAMES = {
        "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
        "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
    };
    
    /**
     * 判断是否为闰年
     * 闰年规则：能被4整除且不能被100整除，或能被400整除
     */
    static boolean isLeapYear(int year) {
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }
    
    /**
     * 获取某月的天数
     */
    static int getMonthDays(int month, int year) {
        switch (month) {
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
    static int getLastMonthDays(int month, int year) {
        int lastMonth = (month > 1) ? month - 1 : 12;
        int lastYear = (month > 1) ? year : year - 1;
        return getMonthDays(lastMonth, lastYear);
    }
    
    /**
     * 计算指定日期是星期几（核心算法）
     * 基于1900年1月1日（星期一）累加天数计算
     */
    static int getWeekdayOfDate(int month, int day, int year) {
        int weekday = START_WEEKDAY;
        
        // 累加从1900年到目标年份-1的所有天数
        for (int i = START_YEAR; i < year; i++) {
            weekday = (weekday + 365) % 7;
            if (isLeapYear(i)) {
                weekday = (weekday + 1) % 7;
            }
        }
        
        // 累加从1月到目标月份-1的所有天数
        for (int i = START_MONTH; i < month; i++) {
            weekday = (weekday + getMonthDays(i, year)) % 7;
        }
        
        // 加上目标日期与1日的差值
        if (day > START_DAY) {
            weekday = (weekday + (day - START_DAY)) % 7;
        }
        
        return weekday;
    }
    
    /**
     * 获取某月第一天是星期几
     */
    static int getFirstWeekdayOfMonth(int month, int year) {
        return getWeekdayOfDate(month, 1, year);
    }
    
    /**
     * 获取某月最后一天是星期几
     */
    static int getLastWeekdayOfMonth(int month, int year) {
        int lastDay = getMonthDays(month, year);
        return getWeekdayOfDate(month, lastDay, year);
    }
    
    /**
     * 打印日历标题
     */
    static void printCalendarTitle(int month, int year) {
        System.out.printf("%12s%4s %d\n", "", MONTH_NAMES[month - 1], year);
    }
    
    /**
     * 打印星期标题
     */
    static void printWeeklyTitle() {
        for (String day : WEEKDAYS) {
            System.out.printf("%5s", day);
        }
    }
    
    /**
     * 打印上个月最后几天（用"]"标记）
     */
    static void printLastMonthLastDays(int weekday, int month, int year) {
        int lastDays = getLastMonthDays(month, year);
        int startDay = lastDays - weekday + 1;
        for (int i = startDay; i <= lastDays; i++) {
            System.out.printf("%2s%2d]", "", i);
        }
    }
    
    /**
     * 打印下个月开始几天（用"]"标记）
     */
    static void printNextMonthStartDays(int weekday) {
        int nextDays = 7 - weekday;
        for (int i = 1; i < nextDays; i++) {
            System.out.printf("%2s%2d]", "", i);
        }
    }
    
    /**
     * 打印日历（包含前后月份日期）
     */
    static void printCalendar(int month, int year) {
        // 打印标题和星期标题
        printCalendarTitle(month, year);
        printWeeklyTitle();
        System.out.println();
        
        // 计算当月第一天是周几
        int firstWeekday = getFirstWeekdayOfMonth(month, year);
        int weekday = firstWeekday;
        
        // 打印上个月最后几天
        printLastMonthLastDays(weekday, month, year);
        
        // 获取当月总天数
        int daysInMonth = getMonthDays(month, year);
        
        // 循环输出当月所有日期
        for (int day = 1; day <= daysInMonth; day++) {
            System.out.printf("%2s", "");
            System.out.printf("%3d", day);
            if (weekday == 6) { // Saturday
                System.out.println();
            }
            weekday = (weekday + 1) % 7;
        }
        
        // 打印下个月开头几天
        int lastWeekday = getLastWeekdayOfMonth(month, year);
        printNextMonthStartDays(lastWeekday);
    }
    
    /**
     * 测试主函数
     */
    public static void main(String[] args) {
        System.out.println("完整版日历打印程序");
        System.out.println("==================");
        
        int month = 12;
        int day = 30;
        int year = 2003;
        
        // 测试：计算2003年12月30日是星期几
        int weekday = getWeekdayOfDate(month, day, year);
        System.out.printf("[%d] = %s\n", weekday, WEEKDAYS[weekday]);
        System.out.printf("TEST: %s %d days = %d\n", MONTH_NAMES[month - 1], year, getMonthDays(month, year));
        System.out.printf("%d-%d-%d is %s = WEEKDAYS[%d]\n", year, month, day, WEEKDAYS[weekday], weekday);
        System.out.println();
        
        // 循环打印48个月的日历（4年）
        int tmpMonth = 0;
        int tmpYear = year;
        int maxMonth = 48;
        
        for (int m = 0; m < maxMonth; m++) {
            tmpMonth++;
            if (tmpMonth == 13) {
                tmpMonth = 1;
                tmpYear++;
            }
            System.out.printf("%d-%d\n", tmpMonth, tmpYear);
            printCalendar(tmpMonth, tmpYear);
            System.out.println("\n");
        }
    }
}

/*打印结果
jarry@Mac calendar % java Calendar.java       
完整版日历打印程序
==================
[2] = Tue
TEST: Dec. 2003 days = 31
2003-12-30 is Tue = WEEKDAYS[2]

1-2003
            Jan. 2003
  Sun  Mon  Tue  Wed  Thu  Fri  Sat
  29]  30]  31]    1    2    3    4
    5    6    7    8    9   10   11
   12   13   14   15   16   17   18
   19   20   21   22   23   24   25
   26   27   28   29   30   31   1]

2-2003
…………
*/