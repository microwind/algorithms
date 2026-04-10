// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// Unix时间戳转换 (Timestamp Conversion)
// 演示时间戳与日期时间字符串之间的相互转换

use chrono::{DateTime, Local, NaiveDateTime, TimeZone, Utc};

/// 将Unix时间戳转换为日期时间字符串
/// 参数: timestamp - 时间戳（秒）
/// 返回: 格式化的日期时间字符串
fn timestamp_to_datetime(timestamp: i64) -> String {
    // 转换为DateTime对象
    let datetime = Utc.timestamp_opt(timestamp, 0).single().unwrap();
    // 格式化为字符串
    datetime.format("%Y-%m-%d %H:%M:%S UTC").to_string()
}

/// 将日期时间字符串转换为Unix时间戳
/// 参数: datetime_str - 日期时间字符串 (格式: "%Y-%m-%d %H:%M:%S")
/// 返回: 时间戳（秒）
fn datetime_to_timestamp(datetime_str: &str) -> Result<i64, chrono::ParseError> {
    let datetime = NaiveDateTime::parse_from_str(datetime_str, "%Y-%m-%d %H:%M:%S")?;
    Ok(datetime.timestamp())
}

/// 获取当前时间戳（秒）
fn get_current_timestamp() -> i64 {
    Utc::now().timestamp()
}

/// 测试主函数
fn main() {
    println!("Unix时间戳转换测试");
    println!("==================");
    
    // 测试时间戳转日期
    let timestamp: i64 = 1704067200; // 2024-01-01 00:00:00 UTC
    let datetime = timestamp_to_datetime(timestamp);
    println!("时间戳 {} -> 日期时间: {}", timestamp, datetime);
    
    // 测试日期转时间戳
    let test_date = "2024-06-15 12:30:00";
    match datetime_to_timestamp(test_date) {
        Ok(ts) => println!("日期时间 {} -> 时间戳: {}", test_date, ts),
        Err(e) => println!("解析错误: {}", e),
    }
    
    // 测试当前时间戳
    let current = get_current_timestamp();
    println!("当前时间戳: {}", current);
    println!("当前日期时间: {}", timestamp_to_datetime(current));
}
