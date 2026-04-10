/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 闰年判断 (Leap Year Check)
 * 判断给定年份是否为闰年
 */

/**
 * 判断是否为闰年
 * 参数: year - 待判断的年份
 * 返回: true表示闰年，false表示平年
 */
function isLeapYear(year: number): boolean {
    // 闰年条件：能被4整除且不能被100整除，或者能被400整除
    return ((year % 4 === 0) && (year % 100 !== 0)) || (year % 400 === 0);
}

// 测试主函数
function main(): void {
    const testYears = [2000, 2004, 1900, 2023, 2024];
    
    console.log("闰年判断测试");
    console.log("============");
    
    for (const year of testYears) {
        const isLeap = isLeapYear(year);
        console.log(`${year}年: ${isLeap ? "闰年" : "平年"}`);
    }
}

main();

// 导出函数供其他模块使用
export { isLeapYear };
