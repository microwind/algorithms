// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 日期差计算 (Date Difference)
// 计算两个日期之间的天数差

/// 日期结构体
#[derive(Debug, Clone, Copy)]
struct Date {
    year: i32,
    month: i32,
    day: i32,
}

/// 判断是否为闰年
fn is_leap_year(year: i32) -> bool {
    ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)
}

/// 获取某月的天数
fn days_in_month(year: i32, month: i32) -> i32 {
    let days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    if month == 2 && is_leap_year(year) {
        return 29; // 闰年2月有29天
    }
    days[(month - 1) as usize]
}

/// 计算从公元1年1月1日到给定日期的天数
fn days_since_epoch(date: Date) -> i32 {
    let mut days = 0;
    
    // 计算之前年份的天数
    for y in 1..date.year {
        days += if is_leap_year(y) { 366 } else { 365 };
    }
    
    // 计算之前月份的天数
    for m in 1..date.month {
        days += days_in_month(date.year, m);
    }
    
    // 计算当月的天数
    days += date.day;
    
    days
}

/// 计算两个日期之间的天数差
fn days_between(date1: Date, date2: Date) -> i32 {
    let days1 = days_since_epoch(date1);
    let days2 = days_since_epoch(date2);
    (days2 - days1).abs()
}

/// 测试主函数
fn main() {
    let date1 = Date { year: 2024, month: 1, day: 1 };   // 元旦
    let date2 = Date { year: 2024, month: 10, day: 1 };  // 国庆节
    
    let diff = days_between(date1, date2);
    println!("日期差计算测试");
    println!("============");
    println!("从 {:04}-{:02}-{:02} 到 {:04}-{:02}-{:02}",
             date1.year, date1.month, date1.day,
             date2.year, date2.month, date2.day);
    println!("相差天数: {} 天", diff);
}
