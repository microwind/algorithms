/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 完整版日历打印程序 (Calendar - Full Version)
 * 根据年月输出当月日历，支持显示前后月份日期
 */

// 基准日期设定：1900年1月1日，星期一
const START_YEAR = 1900;
const START_MONTH = 1;
const START_DAY = 1;
const START_WEEKDAY = 1; // 1=星期一

// 星期标题
const WEEKDAYS = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];

// 月份名称
const MONTH_NAMES = [
    "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
    "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
];

/**
 * 判断是否为闰年
 * @param {number} year - 年份
 * @returns {boolean}
 */
function isLeapYear(year) {
    return ((year % 4 === 0) && (year % 100 !== 0)) || (year % 400 === 0);
}

/**
 * 获取某月的天数
 * @param {number} month - 月份
 * @param {number} year - 年份
 * @returns {number}
 */
function getMonthDays(month, year) {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

/**
 * 获取上个月的天数
 * @param {number} month - 月份
 * @param {number} year - 年份
 * @returns {number}
 */
function getLastMonthDays(month, year) {
    const lastMonth = month === 1 ? 12 : month - 1;
    const lastYear = month === 1 ? year - 1 : year;
    return getMonthDays(lastMonth, lastYear);
}

/**
 * 计算指定日期是星期几（核心算法）
 * @param {number} month - 月份
 * @param {number} day - 日期
 * @param {number} year - 年份
 * @returns {number} - 0=周日, 1=周一, ..., 6=周六
 */
function getWeekdayOfDate(month, day, year) {
    let weekday = START_WEEKDAY;
    
    // 累加从1900年到目标年份-1的所有天数
    for (let i = START_YEAR; i < year; i++) {
        weekday = (weekday + 365) % 7;
        if (isLeapYear(i)) {
            weekday = (weekday + 1) % 7;
        }
    }
    
    // 累加从1月到目标月份-1的所有天数
    for (let i = START_MONTH; i < month; i++) {
        weekday = (weekday + getMonthDays(i, year)) % 7;
    }
    
    // 加上目标日期与1日的差值
    if (day > START_DAY) {
        weekday = (weekday + (day - START_DAY)) % 7;
    }
    
    return weekday;
}

/**
 * 获取某月第一天是星期几
 * @param {number} month - 月份
 * @param {number} year - 年份
 * @returns {number}
 */
function getFirstWeekdayOfMonth(month, year) {
    return getWeekdayOfDate(month, 1, year);
}

/**
 * 获取某月最后一天是星期几
 * @param {number} month - 月份
 * @param {number} year - 年份
 * @returns {number}
 */
function getLastWeekdayOfMonth(month, year) {
    const lastDay = getMonthDays(month, year);
    return getWeekdayOfDate(month, lastDay, year);
}

/**
 * 打印日历标题
 * @param {number} month - 月份
 * @param {number} year - 年份
 */
function printCalendarTitle(month, year) {
    console.log(`${MONTH_NAMES[month - 1].padStart(16)} ${year}`);
}

/**
 * 打印星期标题
 */
function printWeeklyTitle() {
    let header = "";
    for (const day of WEEKDAYS) {
        header += day.padStart(5);
    }
    console.log(header);
}

/**
 * 打印上个月最后几天（用"]"标记）
 * @param {number} weekday - 当月第一天星期几
 * @param {number} month - 月份
 * @param {number} year - 年份
 */
function printLastMonthLastDays(weekday, month, year) {
    const lastDays = getLastMonthDays(month, year);
    const startDay = lastDays - weekday + 1;
    let line = "";
    for (let i = startDay; i <= lastDays; i++) {
        line += `${String(i).padStart(2)}]`;
    }
    process.stdout.write(line);
}

/**
 * 打印下个月开始几天（用"]"标记）
 * @param {number} weekday - 当月最后一天星期几
 */
function printNextMonthStartDays(weekday) {
    const nextDays = 7 - weekday;
    let line = "";
    for (let i = 1; i < nextDays; i++) {
        line += `${String(i).padStart(2)}]`;
    }
    process.stdout.write(line);
}

/**
 * 打印日历（包含前后月份日期）
 * @param {number} month - 月份
 * @param {number} year - 年份
 */
function printCalendar(month, year) {
    // 打印标题和星期标题
    printCalendarTitle(month, year);
    printWeeklyTitle();
    
    // 计算当月第一天是周几
    const firstWeekday = getFirstWeekdayOfMonth(month, year);
    let weekday = firstWeekday;
    
    // 打印上个月最后几天
    printLastMonthLastDays(weekday, month, year);
    
    // 获取当月总天数
    const daysInMonth = getMonthDays(month, year);
    
    // 循环输出当月所有日期
    for (let day = 1; day <= daysInMonth; day++) {
        process.stdout.write(String(day).padStart(5));
        if (weekday === 6) { // Saturday
            console.log();
        }
        weekday = (weekday + 1) % 7;
    }
    
    // 打印下个月开头几天
    const lastWeekday = getLastWeekdayOfMonth(month, year);
    printNextMonthStartDays(lastWeekday);
    console.log();
}

/**
 * 测试主函数
 */
function main() {
    console.log("完整版日历打印程序");
    console.log("==================");
    
    let month = 12;
    const day = 30;
    let year = 2003;
    
    // 测试：计算2003年12月30日是星期几
    const weekday = getWeekdayOfDate(month, day, year);
    console.log(`[${weekday}] = ${WEEKDAYS[weekday]}`);
    console.log(`TEST: ${MONTH_NAMES[month - 1]} ${year} days = ${getMonthDays(month, year)}`);
    console.log(`${year}-${month}-${day} is ${WEEKDAYS[weekday]} = WEEKDAYS[${weekday}]`);
    console.log();
    
    // 循环打印48个月的日历（4年）
    let tmpMonth = 0;
    let tmpYear = year;
    const maxMonth = 48;
    
    for (let m = 0; m < maxMonth; m++) {
        tmpMonth++;
        if (tmpMonth === 13) {
            tmpMonth = 1;
            tmpYear++;
        }
        console.log(`${tmpMonth}-${tmpYear}`);
        printCalendar(tmpMonth, tmpYear);
        console.log();
    }
}

main();
