/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 温度转换 (Temperature Conversion)
 * 摄氏度、华氏度、开尔文之间的相互转换
 */

/**
 * 摄氏度转华氏度
 * 公式: °F = °C × 9/5 + 32
 * @param celsius - 摄氏度
 * @returns 华氏度
 */
function celsiusToFahrenheit(celsius: number): number {
    return celsius * 9.0 / 5.0 + 32.0;
}

/**
 * 华氏度转摄氏度
 * 公式: °C = (°F - 32) × 5/9
 * @param fahrenheit - 华氏度
 * @returns 摄氏度
 */
function fahrenheitToCelsius(fahrenheit: number): number {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

/**
 * 摄氏度转开尔文
 * 公式: K = °C + 273.15
 * @param celsius - 摄氏度
 * @returns 开尔文
 */
function celsiusToKelvin(celsius: number): number {
    return celsius + 273.15;
}

/**
 * 开尔文转摄氏度
 * 公式: °C = K - 273.15
 * @param kelvin - 开尔文
 * @returns 摄氏度
 */
function kelvinToCelsius(kelvin: number): number {
    return kelvin - 273.15;
}

/**
 * 华氏度转开尔文
 * @param fahrenheit - 华氏度
 * @returns 开尔文
 */
function fahrenheitToKelvin(fahrenheit: number): number {
    return celsiusToKelvin(fahrenheitToCelsius(fahrenheit));
}

/**
 * 开尔文转华氏度
 * @param kelvin - 开尔文
 * @returns 华氏度
 */
function kelvinToFahrenheit(kelvin: number): number {
    return celsiusToFahrenheit(kelvinToCelsius(kelvin));
}

// 测试主函数
function main(): void {
    console.log("温度转换测试");
    console.log("============");
    
    const celsius = 25.0;
    console.log(`摄氏度 ${celsius.toFixed(2)}°C = 华氏度 ${celsiusToFahrenheit(celsius).toFixed(2)}°F`);
    console.log(`摄氏度 ${celsius.toFixed(2)}°C = 开尔文 ${celsiusToKelvin(celsius).toFixed(2)}K`);
    
    const fahrenheit = 98.6;
    console.log(`华氏度 ${fahrenheit.toFixed(2)}°F = 摄氏度 ${fahrenheitToCelsius(fahrenheit).toFixed(2)}°C`);
    
    const kelvin = 300.0;
    console.log(`开尔文 ${kelvin.toFixed(2)}K = 摄氏度 ${kelvinToCelsius(kelvin).toFixed(2)}°C`);
    console.log(`开尔文 ${kelvin.toFixed(2)}K = 华氏度 ${kelvinToFahrenheit(kelvin).toFixed(2)}°F`);
}

main();

// 导出函数供其他模块使用
export {
    celsiusToFahrenheit,
    fahrenheitToCelsius,
    celsiusToKelvin,
    kelvinToCelsius,
    fahrenheitToKelvin,
    kelvinToFahrenheit
};
