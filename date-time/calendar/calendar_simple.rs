// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 日历打印 (Calendar Printer)
// 根据年月输出当月日历
//
// 本文件提供两种算法实现：
// 1. Zeller公式法：通过数学公式直接计算星期几，计算速度快
// 2. 基准日期法：从1900年1月1日累加天数计算，直观易懂（与C版本一致）

// 基准日期设定：1900年1月1日，星期一（与C版本一致）
const START_YEAR: i32 = 1900;
const START_MONTH: i32 = 1;
const START_DAY: i32 = 1;
const START_WEEKDAY: i32 = 1; // 1=星期一

// 星期标题
static WEEKDAYS: &[&str] = &["日", "一", "二", "三", "四", "五", "六"];

// 月份名称
static MONTH_NAMES: &[&str] = &[
    "一月", "二月", "三月", "四月", "五月", "六月",
    "七月", "八月", "九月", "十月", "十一月", "十二月",
];

/// 判断是否为闰年
fn is_leap_year(year: i32) -> bool {
    ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)
}

/// 获取某月的天数
fn get_month_days(year: i32, month: i32) -> i32 {
    let days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    if month == 2 && is_leap_year(year) {
        return 29;
    }
    days[(month - 1) as usize]
}

/// 使用Zeller公式计算某月第一天是星期几
/// 算法特点：数学公式直接计算，O(1)时间复杂度
/// 返回: 0=星期日, 1=星期一, ..., 6=星期六
fn get_first_weekday_zeller(mut year: i32, mut month: i32) -> i32 {
    if month < 3 {
        month += 12;
        year -= 1;
    }
    let k = year % 100;
    let j = year / 100;
    let mut h = (1 + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    if h < 0 {
        h += 7;
    }
    let day_map = [6, 0, 1, 2, 3, 4, 5];
    day_map[h as usize]
}

/// 使用基准日期法计算指定日期是星期几
/// 算法特点：从1900年1月1日累加天数，直观易懂
/// 公式：(START_WEEKDAY + 天数差) % 7 = 目标星期
/// 返回: 0=星期日, 1=星期一, ..., 6=星期六
fn get_weekday_of_date_base(year: i32, month: i32, day: i32) -> i32 {
    let mut total_days = START_WEEKDAY;

    // 累加从1900年到目标年份-1的所有天数
    for i in START_YEAR..year {
        total_days += 365;
        if is_leap_year(i) {
            total_days += 1; // 闰年加1天
        }
    }

    // 累加从1月到目标月份-1的所有天数
    for i in START_MONTH..month {
        total_days += get_month_days(year, i);
    }

    // 加上目标日期与1日的差值
    if day > START_DAY {
        total_days += (day - START_DAY);
    }

    // 对7取模得到星期
    total_days % 7
}

/// 获取某月第一天是星期几（默认使用基准日期法，与C版本一致）
fn get_first_weekday(year: i32, month: i32) -> i32 {
    // 使用基准日期法，与C版本calendar_simple.c算法一致
    get_weekday_of_date_base(year, month, 1)
}

/// 打印日历
fn print_calendar(year: i32, month: i32) {
    println!("\n      {} {}", MONTH_NAMES[(month - 1) as usize], year);
    println!("===========================");

    // 打印星期标题
    for day in WEEKDAYS {
        print!("{:>3} ", day);
    }
    println!();

    // 计算第一天是星期几和该月天数
    let first_weekday = get_first_weekday(year, month);
    let days_in_month = get_month_days(year, month);

    // 打印第一行前面的空格
    for _ in 0..first_weekday {
        print!("    ");
    }

    // 打印日期
    let mut weekday = first_weekday;
    for day in 1..=days_in_month {
        print!("{:>3} ", day);
        weekday += 1;
        if weekday == 7 {
            println!();
            weekday = 0;
        }
    }
    println!();
}

/// 测试主函数
fn main() {
    println!("日历打印程序");
    println!("============");

    // 打印2024年1月日历
    print_calendar(2024, 1);

    // 打印2024年6月日历
    print_calendar(2024, 6);
}
