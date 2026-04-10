/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 日期格式化与解析 (Date Format)
 * 支持多种日期格式转换
 */

class DateFormat {
    
    // 英文月份名称
    private static final String[] MONTH_NAMES_EN = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    
    // 中文月份名称
    private static final String[] MONTH_NAMES_CN = {
        "一月", "二月", "三月", "四月",
        "五月", "六月", "七月", "八月",
        "九月", "十月", "十一月", "十二月"
    };
    
    /**
     * 将日期格式化为不同格式的字符串
     * 参数:
     *     year, month, day - 年月日
     *     format - 格式类型: "ISO", "US", "CN", "FULL"
     * 返回: 格式化后的日期字符串
     */
    static String formatDate(int year, int month, int day, String format) {
        return formatDateTime(year, month, day, 0, 0, 0, format);
    }
    
    /**
     * 将日期时间格式化为不同格式的字符串
     */
    static String formatDateTime(int year, int month, int day, 
                                  int hour, int minute, int second, String format) {
        switch (format.toUpperCase()) {
            case "ISO":
                // ISO 8601: 2024-01-01
                return String.format("%04d-%02d-%02d", year, month, day);
            case "US":
                // US格式: 01/01/2024
                return String.format("%02d/%02d/%04d", month, day, year);
            case "CN":
                // 中文格式: 2024年01月01日
                return String.format("%04d年%02d月%02d日", year, month, day);
            case "FULL":
                // 完整格式: 2024-01-01 12:30:45
                return String.format("%04d-%02d-%02d %02d:%02d:%02d",
                        year, month, day, hour, minute, second);
            default:
                return "Unknown format";
        }
    }
    
    /**
     * 获取月份名称
     */
    static String getMonthName(int month, boolean chinese) {
        if (month < 1 || month > 12) return chinese ? "未知" : "Unknown";
        return chinese ? MONTH_NAMES_CN[month - 1] : MONTH_NAMES_EN[month - 1];
    }
    
    // 测试主函数
    public static void main(String[] args) {
        System.out.println("日期格式化示例");
        System.out.println("==============");
        
        int year = 2024, month = 3, day = 15;
        int hour = 14, minute = 30, second = 0;
        
        System.out.printf("原始日期: %d年%d月%d日%n", year, month, day);
        System.out.println();
        
        // 测试各种格式
        System.out.println("ISO格式:   " + formatDate(year, month, day, "ISO"));
        System.out.println("US格式:    " + formatDate(year, month, day, "US"));
        System.out.println("中文格式:  " + formatDate(year, month, day, "CN"));
        System.out.println("完整格式:  " + formatDateTime(year, month, day, hour, minute, second, "FULL"));
        System.out.println();
        
        // 测试月份名称
        System.out.println("月份名称:");
        System.out.println("  英文: " + getMonthName(month, false));
        System.out.println("  中文: " + getMonthName(month, true));
    }
}
