// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 完整版日历打印程序 (Calendar - Full Version)
// 根据年月输出当月日历，支持显示前后月份日期
//
// 核心算法：
// 1. 以1900年1月1日（星期一）为基准日期
// 2. 使用累加天数法计算任意日期是星期几
// 3. 日历显示包含上个月末尾几天和下个月开头几天

// 基准日期设定：1900年1月1日，星期一
const START_YEAR: i32 = 1900;
const START_MONTH: i32 = 1;
const START_DAY: i32 = 1;
const START_WEEKDAY: i32 = 1; // 1=星期一

// 星期标题
static WEEKDAYS: &[&str] = &["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];

// 月份名称
static MONTH_NAMES: &[&str] = &[
    "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
    "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec.",
];

/// 判断是否为闰年
fn is_leap_year(year: i32) -> bool {
    ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)
}

/// 获取某月的天数
fn get_month_days(month: i32, year: i32) -> i32 {
    match month {
        2 => if is_leap_year(year) { 29 } else { 28 },
        4 | 6 | 9 | 11 => 30,
        _ => 31,
    }
}

/// 获取上个月的天数
fn get_last_month_days(month: i32, year: i32) -> i32 {
    let last_month = if month == 1 { 12 } else { month - 1 };
    let last_year = if month == 1 { year - 1 } else { year };
    get_month_days(last_month, last_year)
}

/// 计算指定日期是星期几（核心算法）
fn get_weekday_of_date(month: i32, day: i32, year: i32) -> i32 {
    let mut weekday = START_WEEKDAY;

    // 累加从1900年到目标年份-1的所有天数
    for i in START_YEAR..year {
        weekday = (weekday + 365) % 7;
        if is_leap_year(i) {
            weekday = (weekday + 1) % 7;
        }
    }

    // 累加从1月到目标月份-1的所有天数
    for i in START_MONTH..month {
        weekday = (weekday + get_month_days(i, year)) % 7;
    }

    // 加上目标日期与1日的差值
    if day > START_DAY {
        weekday = (weekday + (day - START_DAY)) % 7;
    }

    weekday
}

/// 获取某月第一天是星期几
fn get_first_weekday_of_month(month: i32, year: i32) -> i32 {
    get_weekday_of_date(month, 1, year)
}

/// 获取某月最后一天是星期几
fn get_last_weekday_of_month(month: i32, year: i32) -> i32 {
    let last_day = get_month_days(month, year);
    get_weekday_of_date(month, last_day, year)
}

/// 打印日历标题
fn print_calendar_title(month: i32, year: i32) {
    println!("{:>16} {}", MONTH_NAMES[(month - 1) as usize], year);
}

/// 打印星期标题
fn print_weekly_title() {
    for day in WEEKDAYS {
        print!("{:>5}", day);
    }
    println!();
}

/// 打印上个月最后几天（用"]"标记）
fn print_last_month_last_days(weekday: i32, month: i32, year: i32) {
    let last_days = get_last_month_days(month, year);
    let start_day = last_days - weekday + 1;
    for i in start_day..=last_days {
        print!("  {:>2}]", i);
    }
}

/// 打印下个月开始几天（用"]"标记）
fn print_next_month_start_days(weekday: i32) {
    let next_days = 7 - weekday;
    for i in 1..next_days {
        print!("  {:>2}]", i);
    }
}

/// 打印日历（包含前后月份日期）
fn print_calendar(month: i32, year: i32) {
    // 打印标题和星期标题
    print_calendar_title(month, year);
    print_weekly_title();

    // 计算当月第一天是周几
    let first_weekday = get_first_weekday_of_month(month, year);
    let mut weekday = first_weekday;

    // 打印上个月最后几天
    print_last_month_last_days(weekday, month, year);

    // 获取当月总天数
    let days_in_month = get_month_days(month, year);

    // 循环输出当月所有日期
    for day in 1..=days_in_month {
        print!("{:>5}", day);
        if weekday == 6 {
            // Saturday
            println!();
        }
        weekday = (weekday + 1) % 7;
    }

    // 打印下个月开头几天
    let last_weekday = get_last_weekday_of_month(month, year);
    print_next_month_start_days(last_weekday);
    println!();
}

/// 测试主函数
fn main() {
    println!("完整版日历打印程序");
    println!("==================");

    let month = 12;
    let day = 30;
    let year = 2003;

    // 测试：计算2003年12月30日是星期几
    let weekday = get_weekday_of_date(month, day, year);
    println!("[{}] = {}", weekday, WEEKDAYS[weekday as usize]);
    println!(
        "TEST: {} {} days = {}",
        MONTH_NAMES[(month - 1) as usize],
        year,
        get_month_days(month, year)
    );
    println!(
        "{}-{}-{} is {} = WEEKDAYS[{}]",
        year, month, day, WEEKDAYS[weekday as usize], weekday
    );
    println!();

    // 循环打印48个月的日历（4年）
    let mut tmp_month = 0;
    let mut tmp_year = year;
    let max_month = 48;

    for _m in 0..max_month {
        tmp_month += 1;
        if tmp_month == 13 {
            tmp_month = 1;
            tmp_year += 1;
        }
        println!("{}-{}", tmp_month, tmp_year);
        print_calendar(tmp_month, tmp_year);
        println!();
    }
}

/*打印结果
jarry@Mac calendar % rustc calendar.rs && ./calendar
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
*/