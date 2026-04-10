/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日期差计算 (Date Difference)
 * 计算两个日期之间的天数差
 * 
 * 算法原理：
 * 1. 将两个日期分别转换为从公元1年1月1日以来的天数
 * 2. 计算两个天数的差值即为日期间隔
 * 3. 支持闰年计算，确保精度准确
 */

class DateDiff {
    
    // 日期类
    static class Date {
        int year, month, day;
        
        Date(int year, int month, int day) {
            this.year = year;
            this.month = month;
            this.day = day;
        }
    }
    
    /**
     * 判断是否为闰年
     */
    static boolean isLeapYear(int year) {
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }
    
    /**
     * 获取某月的天数
     */
    static int daysInMonth(int year, int month) {
        int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year)) {
            return 29;  // 闰年2月有29天
        }
        return days[month - 1];
    }
    
    /**
     * 计算从公元1年1月1日到给定日期的天数
     */
    static int daysSinceEpoch(Date date) {
        int days = 0;
        
        // 计算之前年份的天数
        for (int y = 1; y < date.year; y++) {
            days += isLeapYear(y) ? 366 : 365;
        }
        
        // 计算之前月份的天数
        for (int m = 1; m < date.month; m++) {
            days += daysInMonth(date.year, m);
        }
        
        // 计算当月的天数
        days += date.day;
        
        return days;
    }
    
    /**
     * 计算两个日期之间的天数差
     */
    static int daysBetween(Date date1, Date date2) {
        int days1 = daysSinceEpoch(date1);
        int days2 = daysSinceEpoch(date2);
        return Math.abs(days2 - days1);
    }
    
    // 测试主函数
    public static void main(String[] args) {
        // 测试日期差计算
        Date date1 = new Date(2024, 1, 1);   // 元旦
        Date date2 = new Date(2024, 10, 1);  // 国庆节
        
        int diff = daysBetween(date1, date2);
        System.out.println("日期差计算测试");
        System.out.println("============");
        System.out.printf("从 %d-%02d-%02d 到 %d-%02d-%02d%n", 
                         date1.year, date1.month, date1.day,
                         date2.year, date2.month, date2.day);
        System.out.printf("相差天数: %d 天%n", diff);
    }
}
