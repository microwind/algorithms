// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0

/// 温度单位转换 (Temperature Unit Conversion)
/// 摄氏度与华氏度之间的相互转换

fn celsius_to_fahrenheit(c: f64) -> f64 {
    9.0 / 5.0 * c + 32.0
}

fn fahrenheit_to_celsius(f: i32) -> i32 {
    5 * (f - 32) / 9
}

fn print_conversion_table(start: i32, end: i32, step: i32) {
    println!("摄氏度到华氏度转换表");
    println!("摄氏度 | 华氏度");
    println!("-------|-------");
    
    let mut c = start;
    while c <= end {
        let f = celsius_to_fahrenheit(c as f64);
        println!("{:6}  | {:6.1}", c, f);
        c += step;
    }
}

fn main() {
    println!("温度单位转换演示");
    println!("================\n");
    
    print_conversion_table(0, 100, 5);
    
    println!("\n转换公式:");
    println!("• 摄氏度→华氏度: °F = °C × 9/5 + 32");
    println!("• 华氏度→摄氏度: °C = (°F - 32) × 5/9");
}
