/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日期差计算 (Date Difference)
 * 计算两个日期之间的天数差
 */

/**
 * 判断是否为闰年
 * @param {number} year - 年份
 * @returns {boolean} - true表示闰年
 */
function isLeapYear(year) {
    return ((year % 4 === 0) && (year % 100 !== 0)) || (year % 400 === 0);
}

/**
 * 获取某月的天数
 * @param {number} year - 年份
 * @param {number} month - 月份 (1-12)
 * @returns {number} - 该月天数
 */
function daysInMonth(year, month) {
    const days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    if (month === 2 && isLeapYear(year)) {
        return 29;  // 闰年2月有29天
    }
    return days[month - 1];
}

/**
 * 计算从公元1年1月1日到给定日期的天数
 * @param {Object} date - 日期对象 {year, month, day}
 * @returns {number} - 累计天数
 */
function daysSinceEpoch(date) {
    let days = 0;
    
    // 计算之前年份的天数
    for (let y = 1; y < date.year; y++) {
        days += isLeapYear(y) ? 366 : 365;
    }
    
    // 计算之前月份的天数
    for (let m = 1; m < date.month; m++) {
        days += daysInMonth(date.year, m);
    }
    
    // 计算当月的天数
    days += date.day;
    
    return days;
}

/**
 * 计算两个日期之间的天数差
 * @param {Object} date1 - 第一个日期
 * @param {Object} date2 - 第二个日期
 * @returns {number} - 天数差（绝对值）
 */
function daysBetween(date1, date2) {
    const days1 = daysSinceEpoch(date1);
    const days2 = daysSinceEpoch(date2);
    return Math.abs(days2 - days1);
}

// 测试主函数
function main() {
    const date1 = { year: 2024, month: 1, day: 1 };   // 元旦
    const date2 = { year: 2024, month: 10, day: 1 };  // 国庆节
    
    const diff = daysBetween(date1, date2);
    console.log("日期差计算测试");
    console.log("============");
    console.log(`从 ${date1.year}-${String(date1.month).padStart(2, '0')}-${String(date1.day).padStart(2, '0')} 到 ${date2.year}-${String(date2.month).padStart(2, '0')}-${String(date2.day).padStart(2, '0')}`);
    console.log(`相差天数: ${diff} 天`);
}

main();

// 导出函数供其他模块使用
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { isLeapYear, daysInMonth, daysSinceEpoch, daysBetween };
}
