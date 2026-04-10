/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 星期计算 (Day of Week)
 * 使用 Zeller 公式计算给定日期是星期几
 */

// 星期名称（中文）
const WEEKDAY_NAMES_CN = [
    "星期日", "星期一", "星期二", "星期三",
    "星期四", "星期五", "星期六"
];

// 星期名称（英文）
const WEEKDAY_NAMES_EN = [
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
];

/**
 * 使用 Zeller 公式计算星期几
 * 参数:
 *     year: 年份
 *     month: 月份 (1-12)
 *     day: 日期 (1-31)
 * 返回: 0=星期日, 1=星期一, ..., 6=星期六
 */
function dayOfWeek(year, month, day) {
    // 调整月份：1月和2月视为上一年的13月和14月
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    
    const q = day;           // 日期
    const m = month;         // 调整后的月份
    const k = year % 100;    // 世纪内的年份
    const j = Math.floor(year / 100);  // 零基世纪
    
    // Zeller 公式计算
    let h = (q + Math.floor((13 * (m + 1)) / 5) + k + Math.floor(k / 4) + Math.floor(j / 4) - 2 * j) % 7;
    
    // 处理负数情况
    if (h < 0) h += 7;
    
    // 转换映射：Zeller结果 -> 标准结果 (0=星期日)
    const dayMap = [6, 0, 1, 2, 3, 4, 5];
    return dayMap[h];
}

/**
 * 获取星期名称
 */
function getWeekdayName(weekday, chinese = true) {
    if (chinese) {
        return WEEKDAY_NAMES_CN[weekday];
    } else {
        return WEEKDAY_NAMES_EN[weekday];
    }
}

// 测试主函数
function main() {
    const testDates = [
        [2024, 1, 1],    // 元旦
        [2024, 2, 10],   // 春节
        [2024, 10, 1],   // 国庆节
        [2000, 1, 1],    // 千禧年
        [1949, 10, 1],   // 建国日
    ];
    
    console.log("星期计算测试");
    console.log("============");
    
    for (const [year, month, day] of testDates) {
        const weekday = dayOfWeek(year, month, day);
        const name = getWeekdayName(weekday, true);
        console.log(`${year}-${String(month).padStart(2, '0')}-${String(day).padStart(2, '0')}: ${name}`);
    }
}

main();

// 导出函数供其他模块使用
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { dayOfWeek, getWeekdayName };
}
