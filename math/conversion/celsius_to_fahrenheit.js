/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 温度单位转换 (Temperature Unit Conversion)
 * 摄氏度与华氏度之间的相互转换
 */

function celsiusToFahrenheit(c) {
    return 9.0 / 5.0 * c + 32;
}

function fahrenheitToCelsius(f) {
    return Math.round(5 * (f - 32) / 9);
}

function printConversionTable(start, end, step) {
    console.log("摄氏度到华氏度转换表");
    console.log("摄氏度 | 华氏度");
    console.log("-------|-------");
    
    for (let c = start; c <= end; c += step) {
        const f = celsiusToFahrenheit(c);
        console.log(`${c.toString().padStart(6)}  | ${f.toFixed(1).padStart(6)}`);
    }
}

function main() {
    console.log("温度单位转换演示");
    console.log("================\n");
    
    printConversionTable(0, 100, 5);
    
    console.log("\n转换公式:");
    console.log("• 摄氏度→华氏度: °F = °C × 9/5 + 32");
    console.log("• 华氏度→摄氏度: °C = (°F - 32) × 5/9");
}

main();

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { celsiusToFahrenheit, fahrenheitToCelsius };
}
