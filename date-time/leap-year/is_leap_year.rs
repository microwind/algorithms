// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 闰年判断 (Leap Year Check)
// 判断给定年份是否为闰年

/// 判断是否为闰年
/// 参数: year - 待判断的年份
/// 返回: true表示闰年，false表示平年
fn is_leap_year(year: i32) -> bool {
    // 闰年条件：能被4整除且不能被100整除，或者能被400整除
    ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)
}

// 测试主函数
fn main() {
    let test_years = [2000, 2004, 1900, 2023, 2024];
    
    println!("闰年判断测试");
    println!("============");
    
    for &year in &test_years {
        let is_leap = is_leap_year(year);
        if is_leap {
            println!("{}年: 闰年", year);
        } else {
            println!("{}年: 平年", year);
        }
    }
}
