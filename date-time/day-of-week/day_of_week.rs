// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 星期计算 (Day of Week)
// 使用 Zeller 公式计算给定日期是星期几

/// 星期名称（中文）
static WEEKDAY_NAMES_CN: &[&str] = &[
    "星期日", "星期一", "星期二", "星期三",
    "星期四", "星期五", "星期六",
];

/// 使用 Zeller 公式计算星期几
/// 参数:
///     year: 年份
///     month: 月份 (1-12)
///     day: 日期 (1-31)
/// 返回: 0=星期日, 1=星期一, ..., 6=星期六
fn day_of_week(mut year: i32, mut month: i32, day: i32) -> i32 {
    // 调整月份：1月和2月视为上一年的13月和14月
    if month < 3 {
        month += 12;
        year -= 1;
    }
    
    let q = day;           // 日期
    let m = month;         // 调整后的月份
    let k = year % 100;    // 世纪内的年份
    let j = year / 100;    // 零基世纪
    
    // Zeller 公式计算
    let mut h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    
    // 处理负数情况
    if h < 0 {
        h += 7;
    }
    
    // 转换映射：Zeller结果 -> 标准结果 (0=星期日)
    let day_map = [6, 0, 1, 2, 3, 4, 5];
    day_map[h as usize]
}

/// 获取星期名称
fn get_weekday_name(weekday: usize) -> &'static str {
    WEEKDAY_NAMES_CN[weekday]
}

// 测试主函数
fn main() {
    let test_dates = [
        (2024, 1, 1),    // 元旦
        (2024, 2, 10),   // 春节
        (2024, 10, 1),   // 国庆节
        (2000, 1, 1),    // 千禧年
        (1949, 10, 1),   // 建国日
    ];
    
    println!("星期计算测试");
    println!("============");
    
    for (year, month, day) in test_dates {
        let weekday = day_of_week(year, month, day) as usize;
        let name = get_weekday_name(weekday);
        println!("{:04}-{:02}-{:02}: {}", year, month, day, name);
    }
}
