// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 日期格式化与解析 (Date Format)
// 支持多种日期格式转换

// 英文月份名称
static MONTH_NAMES_EN: &[&str] = &[
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December",
];

// 中文月份名称
static MONTH_NAMES_CN: &[&str] = &[
    "一月", "二月", "三月", "四月",
    "五月", "六月", "七月", "八月",
    "九月", "十月", "十一月", "十二月",
];

/// 将日期格式化为不同格式的字符串
/// 参数: year, month, day - 年月日, format - 格式类型: "ISO", "US", "CN", "FULL"
/// 返回: 格式化后的日期字符串
fn format_date(year: i32, month: i32, day: i32, format: &str) -> String {
    format_datetime(year, month, day, 0, 0, 0, format)
}

/// 将日期时间格式化为不同格式的字符串
fn format_datetime(year: i32, month: i32, day: i32,
                  hour: i32, minute: i32, second: i32, format: &str) -> String {
    let fmt_upper = format.to_uppercase();
    
    match fmt_upper.as_str() {
        "ISO" => {
            // ISO 8601: 2024-01-01
            format!("{:04}-{:02}-{:02}", year, month, day)
        }
        "US" => {
            // US格式: 01/01/2024
            format!("{:02}/{:02}/{:04}", month, day, year)
        }
        "CN" => {
            // 中文格式: 2024年01月01日
            format!("{:04}年{:02}月{:02}日", year, month, day)
        }
        "FULL" => {
            // 完整格式: 2024-01-01 12:30:45
            format!("{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
                    year, month, day, hour, minute, second)
        }
        _ => "Unknown format".to_string()
    }
}

/// 获取月份名称
/// 参数: month - 月份 (1-12), chinese - 是否返回中文名称
/// 返回: 月份名称
fn get_month_name(month: i32, chinese: bool) -> &'static str {
    if month < 1 || month > 12 {
        if chinese {
            return "未知";
        }
        return "Unknown";
    }
    if chinese {
        MONTH_NAMES_CN[(month - 1) as usize]
    } else {
        MONTH_NAMES_EN[(month - 1) as usize]
    }
}

/// 测试主函数
fn main() {
    println!("日期格式化示例");
    println!("==============");
    
    let year = 2024;
    let month = 3;
    let day = 15;
    let hour = 14;
    let minute = 30;
    let second = 0;
    
    println!("原始日期: {}年{}月{}日", year, month, day);
    println!();
    
    // 测试各种格式
    println!("ISO格式:   {}", format_date(year, month, day, "ISO"));
    println!("US格式:    {}", format_date(year, month, day, "US"));
    println!("中文格式:  {}", format_date(year, month, day, "CN"));
    println!("完整格式:  {}", format_datetime(year, month, day, hour, minute, second, "FULL"));
    println!();
    
    // 测试月份名称
    println!("月份名称:");
    println!("  英文: {}", get_month_name(month, false));
    println!("  中文: {}", get_month_name(month, true));
}
