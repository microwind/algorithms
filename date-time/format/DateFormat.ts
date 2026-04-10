/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日期格式化与解析 (Date Format)
 * 支持多种日期格式转换
 */

// 英文月份名称
const MONTH_NAMES_EN: string[] = [
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
];

// 中文月份名称
const MONTH_NAMES_CN: string[] = [
    "一月", "二月", "三月", "四月",
    "五月", "六月", "七月", "八月",
    "九月", "十月", "十一月", "十二月"
];

/**
 * 将日期格式化为不同格式的字符串
 * @param year - 年份
 * @param month - 月份 (1-12)
 * @param day - 日期 (1-31)
 * @param format - 格式类型: "ISO", "US", "CN", "FULL"
 * @returns 格式化后的日期字符串
 */
function formatDate(year: number, month: number, day: number, format: string = "ISO"): string {
    return formatDateTime(year, month, day, 0, 0, 0, format);
}

/**
 * 将日期时间格式化为不同格式的字符串
 * @param year - 年份
 * @param month - 月份 (1-12)
 * @param day - 日期 (1-31)
 * @param hour - 小时
 * @param minute - 分钟
 * @param second - 秒
 * @param format - 格式类型: "ISO", "US", "CN", "FULL"
 * @returns 格式化后的日期时间字符串
 */
function formatDateTime(year: number, month: number, day: number,
                       hour: number, minute: number, second: number, format: string = "ISO"): string {
    const fmtUpper = format.toUpperCase();
    const y = String(year).padStart(4, '0');
    const m = String(month).padStart(2, '0');
    const d = String(day).padStart(2, '0');
    const h = String(hour).padStart(2, '0');
    const min = String(minute).padStart(2, '0');
    const s = String(second).padStart(2, '0');
    
    switch (fmtUpper) {
        case "ISO":
            // ISO 8601: 2024-01-01
            return `${y}-${m}-${d}`;
        case "US":
            // US格式: 01/01/2024
            return `${m}/${d}/${y}`;
        case "CN":
            // 中文格式: 2024年01月01日
            return `${y}年${m}月${d}日`;
        case "FULL":
            // 完整格式: 2024-01-01 12:30:45
            return `${y}-${m}-${d} ${h}:${min}:${s}`;
        default:
            return "Unknown format";
    }
}

/**
 * 获取月份名称
 * @param month - 月份 (1-12)
 * @param chinese - 是否返回中文名称
 * @returns 月份名称
 */
function getMonthName(month: number, chinese: boolean = false): string {
    if (month < 1 || month > 12) return chinese ? "未知" : "Unknown";
    return chinese ? MONTH_NAMES_CN[month - 1] : MONTH_NAMES_EN[month - 1];
}

// 测试主函数
function main(): void {
    console.log("日期格式化示例");
    console.log("==============");
    
    const year = 2024, month = 3, day = 15;
    const hour = 14, minute = 30, second = 0;
    
    console.log(`原始日期: ${year}年${month}月${day}日`);
    console.log();
    
    // 测试各种格式
    console.log("ISO格式:   " + formatDate(year, month, day, "ISO"));
    console.log("US格式:    " + formatDate(year, month, day, "US"));
    console.log("中文格式:  " + formatDate(year, month, day, "CN"));
    console.log("完整格式:  " + formatDateTime(year, month, day, hour, minute, second, "FULL"));
    console.log();
    
    // 测试月份名称
    console.log("月份名称:");
    console.log("  英文: " + getMonthName(month, false));
    console.log("  中文: " + getMonthName(month, true));
}

main();

// 导出函数供其他模块使用
export { formatDate, formatDateTime, getMonthName };
