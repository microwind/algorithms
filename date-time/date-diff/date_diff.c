/*
 * 日期时间 - 计算两个日期之间的天数差
 * 支持闰年计算，精度准确
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int month;
    int day;
} Date;

// 判断是否为闰年
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取某月的天数
int days_in_month(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days[month - 1];
}

// 计算从公元1年1月1日到给定日期的天数
int days_since_epoch(Date date) {
    int days = 0;
    
    // 计算之前年份的天数
    for (int y = 1; y < date.year; y++) {
        days += is_leap_year(y) ? 366 : 365;
    }
    
    // 计算之前月份的天数
    for (int m = 1; m < date.month; m++) {
        days += days_in_month(date.year, m);
    }
    
    // 计算当月的天数
    days += date.day;
    
    return days;
}

// 计算两个日期之间的天数差
int days_between(Date date1, Date date2) {
    int days1 = days_since_epoch(date1);
    int days2 = days_since_epoch(date2);
    return abs(days2 - days1);
}

// 计算加上指定天数后的日期
Date add_days(Date date, int days) {
    Date result = date;
    
    while (days > 0) {
        int month_days = days_in_month(result.year, result.month);
        int remaining = month_days - result.day;
        
        if (days <= remaining) {
            result.day += days;
            break;
        }
        
        days -= (remaining + 1);
        result.day = 1;
        result.month++;
        
        if (result.month > 12) {
            result.month = 1;
            result.year++;
        }
    }
    
    return result;
}

int main() {
    Date date1 = {2024, 1, 1};
    Date date2 = {2024, 12, 31};
    Date date3 = {2023, 6, 15};
    
    printf("日期差值计算:\n\n");
    
    int diff = days_between(date1, date2);
    printf("从 %d-%02d-%02d 到 %d-%02d-%02d\n", 
           date1.year, date1.month, date1.day,
           date2.year, date2.month, date2.day);
    printf("相差: %d 天\n\n", diff);
    
    diff = days_between(date3, date1);
    printf("从 %d-%02d-%02d 到 %d-%02d-%02d\n",
           date3.year, date3.month, date3.day,
           date1.year, date1.month, date1.day);
    printf("相差: %d 天\n\n", diff);
    
    // 演示日期加法
    Date new_date = add_days(date1, 100);
    printf("%d-%02d-%02d 加上 100 天 = %d-%02d-%02d\n",
           date1.year, date1.month, date1.day,
           new_date.year, new_date.month, new_date.day);
    
    return 0;
}
