/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * Unix时间戳转换 (Timestamp Conversion)
 * 演示时间戳与日期时间字符串之间的相互转换
 * 
 * 时间戳：从1970-01-01 00:00:00 UTC至今的秒数
 */

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;

class TimestampConversion {
    
    /**
     * 将Unix时间戳转换为日期时间字符串
     * 参数: timestamp - 时间戳（秒）
     * 返回: 格式化的日期时间字符串
     */
    static String timestampToDatetime(long timestamp) {
        // 创建Instant对象
        Instant instant = Instant.ofEpochSecond(timestamp);
        // 转换为本地时间
        LocalDateTime dateTime = LocalDateTime.ofInstant(instant, ZoneId.systemDefault());
        // 格式化为字符串
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        return dateTime.format(formatter);
    }
    
    /**
     * 将日期时间字符串转换为Unix时间戳
     * 参数: datetimeStr - 日期时间字符串 (格式: yyyy-MM-dd HH:mm:ss)
     * 返回: 时间戳（秒）
     */
    static long datetimeToTimestamp(String datetimeStr) {
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            LocalDateTime dateTime = LocalDateTime.parse(datetimeStr, formatter);
            return dateTime.atZone(ZoneId.systemDefault()).toEpochSecond();
        } catch (DateTimeParseException e) {
            System.err.println("日期时间格式错误: " + e.getMessage());
            return -1;
        }
    }
    
    /**
     * 获取当前时间戳
     */
    static long getCurrentTimestamp() {
        return System.currentTimeMillis() / 1000;
    }
    
    // 测试主函数
    public static void main(String[] args) {
        System.out.println("Unix时间戳转换测试");
        System.out.println("==================");
        
        // 测试时间戳转日期
        long timestamp = 1704067200L;  // 2024-01-01 00:00:00 UTC
        String datetime = timestampToDatetime(timestamp);
        System.out.printf("时间戳 %d -> 日期时间: %s%n", timestamp, datetime);
        
        // 测试日期转时间戳
        String testDate = "2024-06-15 12:30:00";
        long convertedTimestamp = datetimeToTimestamp(testDate);
        System.out.printf("日期时间 %s -> 时间戳: %d%n", testDate, convertedTimestamp);
        
        // 测试当前时间戳
        long current = getCurrentTimestamp();
        System.out.printf("当前时间戳: %d%n", current);
        System.out.printf("当前日期时间: %s%n", timestampToDatetime(current));
    }
}
