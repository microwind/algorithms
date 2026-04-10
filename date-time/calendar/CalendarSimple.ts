/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日历打印 (Calendar Printer)
 * 根据年月输出当月日历
 * 
 * 本文件提供两种算法实现：
 * 1. Zeller公式法：通过数学公式直接计算星期几，计算速度快
 * 2. 基准日期法：从1900年1月1日累加天数计算，直观易懂（与C版本一致）
 */

// 基准日期设定：1900年1月1日，星期一（与C版本一致）
const START_YEAR: number = 1900;
const START_MONTH: number = 1;
const START_DAY: number = 1;
const START_WEEKDAY: number = 1; // 1=星期一

// 星期标题
const WEEKDAYS: string[] = ["日", "一", "二", "三", "四", "五", "六"];

// 月份名称
const MONTH_NAMES: string[] = [
    "一月", "二月", "三月", "四月", "五月", "六月",
    "七月", "八月", "九月", "十月", "十一月", "十二月"
];

/**
 * 判断是否为闰年
 * @param year - 年份
 * @returns true表示闰年
 */
function isLeapYear(year: number): boolean {
    return ((year % 4 === 0) && (year % 100 !== 0)) || (year % 400 === 0);
}

/**
 * 获取某月的天数
 * @param year - 年份
 * @param month - 月份 (1-12)
 * @returns 该月天数
 */
function getMonthDays(year: number, month: number): number {
    const days: number[] = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    if (month === 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

/**
 * 使用Zeller公式计算某月第一天是星期几
 * 算法特点：数学公式直接计算，O(1)时间复杂度
 * @param year - 年份
 * @param month - 月份 (1-12)
 * @returns 0=星期日, 1=星期一, ..., 6=星期六
 */
function getFirstWeekdayZeller(year: number, month: number): number {
    let y: number = year;
    let m: number = month;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    const k: number = y % 100;
    const j: number = Math.floor(y / 100);
    let h: number = (1 + Math.floor((13 * (m + 1)) / 5) + k + Math.floor(k / 4) + Math.floor(j / 4) - 2 * j) % 7;
    if (h < 0) h += 7;
    const dayMap: number[] = [6, 0, 1, 2, 3, 4, 5];
    return dayMap[h];
}

/**
 * 使用基准日期法计算指定日期是星期几
 * 算法特点：从1900年1月1日累加天数，直观易懂
 * 公式：(START_WEEKDAY + 天数差) % 7 = 目标星期
 * @param year - 年份
 * @param month - 月份 (1-12)
 * @param day - 日期 (1-31)
 * @returns 0=星期日, 1=星期一, ..., 6=星期六
 */
function getWeekdayOfDateBase(year: number, month: number, day: number): number {
    let totalDays: number = START_WEEKDAY;
    
    // 累加从1900年到目标年份-1的所有天数
    for (let i: number = START_YEAR; i < year; i++) {
        totalDays += 365;
        if (isLeapYear(i)) {
            totalDays += 1; // 闰年加1天
        }
    }
    
    // 累加从1月到目标月份-1的所有天数
    for (let i: number = START_MONTH; i < month; i++) {
        totalDays += getMonthDays(year, i);
    }
    
    // 加上目标日期与1日的差值
    if (day > START_DAY) {
        totalDays += (day - START_DAY);
    }
    
    // 对7取模得到星期
    return totalDays % 7;
}

/**
 * 获取某月第一天是星期几（默认使用基准日期法，与C版本一致）
 * @param year - 年份
 * @param month - 月份 (1-12)
 * @returns 0=星期日, 1=星期一, ..., 6=星期六
 */
function getFirstWeekday(year: number, month: number): number {
    // 使用基准日期法，与C版本calendar_simple.c算法一致
    return getWeekdayOfDateBase(year, month, 1);
}

/**
 * 打印日历
 * @param year - 年份
 * @param month - 月份 (1-12)
 */
function printCalendar(year: number, month: number): void {
    console.log(`\n      ${MONTH_NAMES[month - 1]} ${year}`);
    console.log("===========================");
    
    // 打印星期标题
    let header = "";
    for (const day of WEEKDAYS) {
        header += `${day.padStart(3)} `;
    }
    console.log(header);
    
    // 计算第一天是星期几和该月天数
    const firstWeekday: number = getFirstWeekday(year, month);
    const daysInMonth: number = getMonthDays(year, month);
    
    // 打印第一行前面的空格
    let line = "";
    for (let i = 0; i < firstWeekday; i++) {
        line += "    ";
    }
    
    // 打印日期
    let weekday: number = firstWeekday;
    for (let day = 1; day <= daysInMonth; day++) {
        line += String(day).padStart(3) + " ";
        weekday++;
        if (weekday === 7) {
            console.log(line);
            line = "";
            weekday = 0;
        }
    }
    if (line.length > 0) {
        console.log(line);
    }
}

// 测试主函数
function main(): void {
    console.log("日历打印程序");
    console.log("============");
    
    // 打印2024年1月日历
    printCalendar(2024, 1);
    
    // 打印2024年6月日历
    printCalendar(2024, 6);
}

main();

// 导出函数供其他模块使用
export { isLeapYear, getMonthDays, getFirstWeekday, printCalendar };
