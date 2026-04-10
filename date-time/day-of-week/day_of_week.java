/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 星期计算 (Day of Week)
 * 使用 Zeller 公式计算给定日期是星期几
 * 
 * Zeller公式原理：
 * 基于格里高利历，通过数学运算将日期映射为星期
 * 特别处理1月和2月，将其视为上一年的13月和14月
 */

class DayOfWeek {
    
    // 星期名称（中文）
    private static final String[] WEEKDAY_NAMES_CN = {
        "星期日", "星期一", "星期二", "星期三", 
        "星期四", "星期五", "星期六"
    };
    
    // 星期名称（英文）
    private static final String[] WEEKDAY_NAMES_EN = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    
    /**
     * 使用 Zeller 公式计算星期几
     * 参数:
     *     year: 年份
     *     month: 月份 (1-12)
     *     day: 日期 (1-31)
     * 返回: 0=星期日, 1=星期一, ..., 6=星期六
     */
    public static int dayOfWeek(int year, int month, int day) {
        // 调整月份：1月和2月视为上一年的13月和14月
        if (month < 3) {
            month += 12;
            year -= 1;
        }
        
        int q = day;           // 日期
        int m = month;         // 调整后的月份
        int k = year % 100;    // 世纪内的年份
        int j = year / 100;    // 零基世纪
        
        // Zeller 公式计算
        int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
        
        // 处理负数情况
        if (h < 0) h += 7;
        
        // 转换映射：Zeller结果 -> 标准结果 (0=星期日)
        int[] dayMap = {6, 0, 1, 2, 3, 4, 5};  // h=0->6, h=1->0, ...
        return dayMap[h];
    }
    
    /**
     * 获取星期名称
     */
    public static String getWeekdayName(int weekday, boolean chinese) {
        if (chinese) {
            return WEEKDAY_NAMES_CN[weekday];
        } else {
            return WEEKDAY_NAMES_EN[weekday];
        }
    }
    
    // 测试主函数
    public static void main(String[] args) {
        // 测试几个重要日期
        int[][] testDates = {
            {2024, 1, 1},    // 元旦
            {2024, 2, 10},   // 春节
            {2024, 10, 1},   // 国庆节
            {2000, 1, 1},    // 千禧年
            {1949, 10, 1},   // 建国日
        };
        
        System.out.println("星期计算测试");
        System.out.println("============");
        
        for (int[] date : testDates) {
            int year = date[0];
            int month = date[1];
            int day = date[2];
            int weekday = dayOfWeek(year, month, day);
            String name = getWeekdayName(weekday, true);
            System.out.printf("%d-%02d-%02d: %s%n", year, month, day, name);
        }
    }
}
