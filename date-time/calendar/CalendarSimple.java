/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日历打印 (Calendar Printer)
 * 根据年月输出当月日历
 * 
 * 本文件提供两种算法实现：
 * 1. Zeller公式法：通过数学公式直接计算星期几，计算速度快
 * 2. 基准日期法：从1900年1月1日累加天数计算，直观易懂（与C版本一致）
 */

class CalendarSimple {
    
    // 基准日期设定：1900年1月1日，星期一（与C版本一致）
    private static final int START_YEAR = 1900;
    private static final int START_MONTH = 1;
    private static final int START_DAY = 1;
    private static final int START_WEEKDAY = 1; // 1=星期一
    
    // 星期标题
    private static final String[] WEEKDAYS = {"日", "一", "二", "三", "四", "五", "六"};
    
    // 月份名称
    private static final String[] MONTH_NAMES = {
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"
    };
    
    /**
     * 判断是否为闰年
     */
    static boolean isLeapYear(int year) {
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }
    
    /**
     * 获取某月的天数
     */
    static int getMonthDays(int year, int month) {
        int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return days[month - 1];
    }
    
    /**
     * 使用Zeller公式计算某月第一天是星期几
     * 算法特点：数学公式直接计算，O(1)时间复杂度
     * 返回: 0=星期日, 1=星期一, ..., 6=星期六
     */
    static int getFirstWeekdayZeller(int year, int month) {
        int m = month;
        int y = year;
        if (m < 3) {
            m += 12;
            y -= 1;
        }
        int k = y % 100;
        int j = y / 100;
        int h = (1 + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
        if (h < 0) h += 7;
        int[] dayMap = {6, 0, 1, 2, 3, 4, 5};
        return dayMap[h];
    }
    
    /**
     * 使用基准日期法计算指定日期是星期几
     * 算法特点：从1900年1月1日累加天数，直观易懂
     * 公式：(START_WEEKDAY + 天数差) % 7 = 目标星期
     * 返回: 0=星期日, 1=星期一, ..., 6=星期六
     */
    static int getWeekdayOfDateBase(int year, int month, int day) {
        int totalDays = START_WEEKDAY;
        
        // 累加从1900年到目标年份-1的所有天数
        for (int i = START_YEAR; i < year; i++) {
            totalDays += 365;
            if (isLeapYear(i)) {
                totalDays += 1; // 闰年加1天
            }
        }
        
        // 累加从1月到目标月份-1的所有天数
        for (int i = START_MONTH; i < month; i++) {
            totalDays += getMonthDays(year, i);
        }
        
        // 加上目标日期与1日的差值
        if (day > START_DAY) {
            totalDays += (day - START_DAY);
        }
        
        // 对7取模得到星期
        return totalDays % 7;
    }
    
    /**
     * 获取某月第一天是星期几（默认使用基准日期法，与C版本一致）
     */
    static int getFirstWeekday(int year, int month) {
        // 使用基准日期法，与C版本calendar_simple.c算法一致
        return getWeekdayOfDateBase(year, month, 1);
    }
    
    /**
     * 打印日历
     */
    static void printCalendar(int year, int month) {
        System.out.printf("\n      %s %d\n", MONTH_NAMES[month - 1], year);
        System.out.println("===========================");
        
        // 打印星期标题
        for (String day : WEEKDAYS) {
            System.out.printf("%3s ", day);
        }
        System.out.println();
        
        // 计算第一天是星期几和该月天数
        int firstWeekday = getFirstWeekday(year, month);
        int daysInMonth = getMonthDays(year, month);
        
        // 打印第一行前面的空格
        for (int i = 0; i < firstWeekday; i++) {
            System.out.print("    ");
        }
        
        // 打印日期
        int weekday = firstWeekday;
        for (int day = 1; day <= daysInMonth; day++) {
            System.out.printf("%3d ", day);
            weekday++;
            if (weekday == 7) {
                System.out.println();
                weekday = 0;
            }
        }
        System.out.println();
    }
    
    // 测试主函数
    public static void main(String[] args) {
        System.out.println("日历打印程序");
        System.out.println("============");
        
        // 打印2024年1月日历
        printCalendar(2024, 1);
        
        // 打印2024年6月日历
        printCalendar(2024, 6);
    }
}
