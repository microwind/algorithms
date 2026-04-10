// Copyright © https://github.com/microwind All rights reserved.
// @author: jarryli@gmail.com
// @version: 1.0
//
// 温度转换 (Temperature Conversion)
// 摄氏度、华氏度、开尔文之间的相互转换

/// 摄氏度转华氏度
/// 公式: °F = °C × 9/5 + 32
fn celsius_to_fahrenheit(celsius: f64) -> f64 {
    celsius * 9.0 / 5.0 + 32.0
}

/// 华氏度转摄氏度
/// 公式: °C = (°F - 32) × 5/9
fn fahrenheit_to_celsius(fahrenheit: f64) -> f64 {
    (fahrenheit - 32.0) * 5.0 / 9.0
}

/// 摄氏度转开尔文
/// 公式: K = °C + 273.15
fn celsius_to_kelvin(celsius: f64) -> f64 {
    celsius + 273.15
}

/// 开尔文转摄氏度
/// 公式: °C = K - 273.15
fn kelvin_to_celsius(kelvin: f64) -> f64 {
    kelvin - 273.15
}

/// 华氏度转开尔文
fn fahrenheit_to_kelvin(fahrenheit: f64) -> f64 {
    celsius_to_kelvin(fahrenheit_to_celsius(fahrenheit))
}

/// 开尔文转华氏度
fn kelvin_to_fahrenheit(kelvin: f64) -> f64 {
    celsius_to_fahrenheit(kelvin_to_celsius(kelvin))
}

/// 测试主函数
fn main() {
    println!("温度转换测试");
    println!("============");
    
    let celsius = 25.0;
    println!("摄氏度 {:.2}°C = 华氏度 {:.2}°F", 
             celsius, celsius_to_fahrenheit(celsius));
    println!("摄氏度 {:.2}°C = 开尔文 {:.2}K", 
             celsius, celsius_to_kelvin(celsius));
    
    let fahrenheit = 98.6;
    println!("华氏度 {:.2}°F = 摄氏度 {:.2}°C", 
             fahrenheit, fahrenheit_to_celsius(fahrenheit));
    
    let kelvin = 300.0;
    println!("开尔文 {:.2}K = 摄氏度 {:.2}°C", 
             kelvin, kelvin_to_celsius(kelvin));
    println!("开尔文 {:.2}K = 华氏度 {:.2}°F", 
             kelvin, kelvin_to_fahrenheit(kelvin));
}
