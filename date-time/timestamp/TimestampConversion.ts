/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * Unix时间戳转换 (Timestamp Conversion)
 * 演示时间戳与日期时间字符串之间的相互转换
 */

/**
 * 将Unix时间戳转换为日期时间字符串
 * @param timestamp - 时间戳（秒或毫秒）
 * @returns 格式化的日期时间字符串
 */
function timestampToDatetime(timestamp: number): string {
    // 判断是秒还是毫秒（时间戳大于1e10认为是毫秒）
    if (timestamp < 1e10) {
        timestamp *= 1000;  // 转换为毫秒
    }
    
    const date = new Date(timestamp);
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');
    const hours = String(date.getHours()).padStart(2, '0');
    const minutes = String(date.getMinutes()).padStart(2, '0');
    const seconds = String(date.getSeconds()).padStart(2, '0');
    
    return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
}

/**
 * 将日期时间字符串转换为Unix时间戳（秒）
 * @param datetimeStr - 日期时间字符串
 * @returns 时间戳（秒），错误时返回-1
 */
function datetimeToTimestamp(datetimeStr: string): number {
    const date = new Date(datetimeStr);
    if (isNaN(date.getTime())) {
        console.error('日期时间格式错误');
        return -1;
    }
    return Math.floor(date.getTime() / 1000);
}

/**
 * 获取当前时间戳（秒）
 * @returns 当前时间戳
 */
function getCurrentTimestamp(): number {
    return Math.floor(Date.now() / 1000);
}

// 测试主函数
function main(): void {
    console.log("Unix时间戳转换测试");
    console.log("==================");
    
    // 测试时间戳转日期
    const timestamp = 1704067200;  // 2024-01-01 00:00:00 UTC
    const datetime = timestampToDatetime(timestamp);
    console.log(`时间戳 ${timestamp} -> 日期时间: ${datetime}`);
    
    // 测试日期转时间戳
    const testDate = "2024-06-15 12:30:00";
    const convertedTimestamp = datetimeToTimestamp(testDate);
    console.log(`日期时间 ${testDate} -> 时间戳: ${convertedTimestamp}`);
    
    // 测试当前时间戳
    const current = getCurrentTimestamp();
    console.log(`当前时间戳: ${current}`);
    console.log(`当前日期时间: ${timestampToDatetime(current)}`);
}

main();

// 导出函数供其他模块使用
export { timestampToDatetime, datetimeToTimestamp, getCurrentTimestamp };
