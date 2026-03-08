/*
 * 日期时间 - 闰年判断与计算
 * 判断给定年份是否为闰年，并计算闰年相关数据
 */
#include <stdio.h>

// 判断是否为闰年
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 计算两个年份之间的闰年数量
int count_leap_years(int start_year, int end_year) {
    int count = 0;
    for (int year = start_year; year <= end_year; year++) {
        if (is_leap_year(year)) {
            count++;
        }
    }
    return count;
}

// 获取某年的天数
int days_in_year(int year) {
    return is_leap_year(year) ? 366 : 365;
}

// 获取某年2月的天数
int days_in_february(int year) {
    return is_leap_year(year) ? 29 : 28;
}

// 获取某月的天数
int get_days_in_month(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days[month - 1];
}

int main() {
    int year = 2024;
    
    printf("闰年判断与计算:\n\n");
    
    // 判断单个年份
    printf("年份 %d: %s\n", year, is_leap_year(year) ? "闰年" : "平年");
    printf("  全年天数: %d\n", days_in_year(year));
    printf("  二月天数: %d\n\n", days_in_february(year));
    
    // 列出21世纪的闰年
    printf("21世纪的闰年 (2001-2100):\n");
    int leap_count = 0;
    for (int y = 2001; y <= 2100; y++) {
        if (is_leap_year(y)) {
            printf("  %d", y);
            leap_count++;
            if (leap_count % 5 == 0) {
                printf("\n");
            }
        }
    }
    printf("\n共 %d 个闰年\n\n", leap_count);
    
    // 计算闰年数量
    int start = 2000, end = 2024;
    printf("从 %d 到 %d 共有 %d 个闰年\n", 
           start, end, count_leap_years(start, end));
    
    // 2024年各月天数
    printf("\n2024年各月天数:\n");
    const char* months[] = {
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"
    };
    for (int m = 1; m <= 12; m++) {
        printf("  %s: %d天\n", months[m-1], get_days_in_month(2024, m));
    }
    
    return 0;
}
