/*
 * 日期时间 - Unix时间戳转换
 * 演示时间戳与日期时间之间的相互转换
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// 定义32位有符号整数的最大值（2038年问题）
#define INT32_MAX 2147483647

/**
 * 将Unix时间戳转换为日期时间字符串
 * 
 * 参数:
 *     timestamp: 时间戳（秒）
 *     buffer: 存储结果的缓冲区
 *     buffer_size: 缓冲区大小
 * 返回:
 *     成功返回0，失败返回-1
 */
int timestamp_to_datetime(time_t timestamp, char* buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }
    
    // 转换为UTC时间
    struct tm* utc_time = gmtime(&timestamp);
    if (utc_time == NULL) {
        return -1;
    }
    
    // 格式化为字符串
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S UTC", utc_time);
    return 0;
}

/**
 * 将日期时间字符串转换为Unix时间戳
 * 
 * 参数:
 *     date_str: 日期时间字符串
 *     format: 格式字符串
 *     timestamp: 存储结果的指针
 * 返回:
 *     成功返回0，失败返回-1
 */
int datetime_to_timestamp(const char* date_str, const char* format, time_t* timestamp) {
    if (date_str == NULL || format == NULL || timestamp == NULL) {
        return -1;
    }
    
    struct tm tm_time = {0};
    
    // 解析字符串
    if (strptime(date_str, format, &tm_time) == NULL) {
        return -1;
    }
    
    // 转换为时间戳（假设为UTC时间）
    *timestamp = timegm(&tm_time);
    return 0;
}

/**
 * 获取当前Unix时间戳（秒和毫秒）
 */
void get_current_timestamp(time_t* seconds, long long* milliseconds) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    
    if (seconds != NULL) {
        *seconds = ts.tv_sec;
    }
    
    if (milliseconds != NULL) {
        *milliseconds = (long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    }
}

/**
 * 根据时间戳判断对应年份是否为闰年
 */
int is_leap_year_timestamp(time_t timestamp) {
    struct tm* utc_time = gmtime(&timestamp);
    if (utc_time == NULL) {
        return 0;
    }
    
    int year = utc_time->tm_year + 1900;
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * 格式化时间戳为多种格式
 */
void format_timestamp_multiple(time_t timestamp) {
    char buffer[100];
    struct tm* utc_time = gmtime(&timestamp);
    
    if (utc_time == NULL) {
        printf("无效时间戳\n");
        return;
    }
    
    // ISO 8601格式
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", utc_time);
    printf("  ISO 8601: %s\n", buffer);
    
    // 可读格式
    strftime(buffer, sizeof(buffer), "%Y年%m月%d日 %H时%M分%S秒", utc_time);
    printf("  可读格式: %s\n", buffer);
    
    // 星期格式
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %A", utc_time);
    printf("  星期格式: %s\n", buffer);
    
    // 闰年判断
    printf("  是否闰年: %s\n", is_leap_year_timestamp(timestamp) ? "是" : "否");
}

/**
 * 计算两个时间戳之间的时间差
 */
void calculate_time_difference(time_t ts1, time_t ts2) {
    time_t diff = ts2 - ts1;
    
    if (diff < 0) {
        diff = -diff;
        printf("时间差: %ld秒 (%.1f天)\n", diff, (double)diff / 86400.0);
    } else {
        printf("时间差: %ld秒 (%.1f天)\n", diff, (double)diff / 86400.0);
    }
    
    // 转换为天、小时、分钟、秒
    int days = diff / 86400;
    int hours = (diff % 86400) / 3600;
    int minutes = (diff % 3600) / 60;
    int seconds = diff % 60;
    
    printf("  相当于: %d天 %d小时 %d分钟 %d秒\n", days, hours, minutes, seconds);
}

/**
 * 演示2038年问题
 */
void demonstrate_y2k38_problem() {
    printf("\n2038年问题说明:\n");
    printf("  32位有符号整数最大值: %d\n", INT32_MAX);
    
    char buffer[100];
    timestamp_to_datetime(INT32_MAX, buffer, sizeof(buffer));
    printf("  对应时间: %s\n", buffer);
    
    printf("  之后会发生溢出，需要使用64位整数\n");
    
    // 演示溢出
    time_t overflow_time = (time_t)INT32_MAX + 1;
    timestamp_to_datetime(overflow_time, buffer, sizeof(buffer));
    printf("  溢出后时间: %s\n", buffer);
}

/**
 * 时间戳运算示例
 */
void timestamp_arithmetic() {
    printf("\n时间戳运算示例:\n");
    
    time_t base_time = 1704067200;  // 2024-01-01 00:00:00 UTC
    char buffer[100];
    
    timestamp_to_datetime(base_time, buffer, sizeof(buffer));
    printf("  基准时间: %s\n", buffer);
    
    // 加1天
    time_t plus_1_day = base_time + 86400;
    timestamp_to_datetime(plus_1_day, buffer, sizeof(buffer));
    printf("  +1天:      %s\n", buffer);
    
    // 加1小时
    time_t plus_1_hour = base_time + 3600;
    timestamp_to_datetime(plus_1_hour, buffer, sizeof(buffer));
    printf("  +1小时:    %s\n", buffer);
    
    // 加1周
    time_t plus_1_week = base_time + 7 * 86400;
    timestamp_to_datetime(plus_1_week, buffer, sizeof(buffer));
    printf("  +1周:      %s\n", buffer);
}

/**
 * 测试特殊时间戳
 */
void test_special_timestamps() {
    printf("\n特殊时间戳测试:\n");
    
    struct {
        time_t timestamp;
        const char* description;
    } test_cases[] = {
        {0, "Unix纪元起点"},
        {1704067200, "2024年元旦"},
        {1000000000, "十亿秒时刻"},
        {1234567890, "有趣的时间戳"},
        {2000000000, "二十亿秒时刻"},
        {INT32_MAX, "32位最大值"}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("  %-12s %-20s %s\n", "时间戳", "描述", "日期时间");
    printf("  %-12s %-20s %s\n", "------------", "--------------------", "-------------------");
    
    for (int i = 0; i < num_cases; i++) {
        char buffer[100];
        timestamp_to_datetime(test_cases[i].timestamp, buffer, sizeof(buffer));
        printf("  %-12ld %-20s %s\n", 
               test_cases[i].timestamp, 
               test_cases[i].description, 
               buffer);
    }
}

/**
 * 交互式时间戳转换
 */
void interactive_timestamp_conversion() {
    printf("\n交互式时间戳转换:\n");
    printf("输入格式:\n");
    printf("  ts 时间戳     - 时间戳转日期\n");
    printf("  dt 日期时间   - 日期转时间戳 (格式: YYYY-MM-DD HH:MM:SS)\n");
    printf("输入 'q' 退出\n\n");
    
    char input[100];
    char command[10];
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // 移除换行符
        input[strcspn(input, "\n")] = 0;
        
        if (input[0] == 'q' || input[0] == 'Q') {
            break;
        }
        
        if (sscanf(input, "%s", command) != 1) {
            printf("格式错误\n");
            continue;
        }
        
        if (strcmp(command, "ts") == 0) {
            time_t timestamp;
            if (sscanf(input, "ts %ld", &timestamp) == 1) {
                char buffer[100];
                if (timestamp_to_datetime(timestamp, buffer, sizeof(buffer)) == 0) {
                    printf("  日期时间: %s\n", buffer);
                    format_timestamp_multiple(timestamp);
                } else {
                    printf("  时间戳无效\n");
                }
            } else {
                printf("  格式: ts 时间戳\n");
            }
        } else if (strcmp(command, "dt") == 0) {
            char date_str[50];
            if (sscanf(input, "dt %49[^\n]", date_str) == 1) {
                time_t timestamp;
                if (datetime_to_timestamp(date_str, "%Y-%m-%d %H:%M:%S", &timestamp) == 0) {
                    char buffer[100];
                    timestamp_to_datetime(timestamp, buffer, sizeof(buffer));
                    printf("  时间戳: %ld\n", timestamp);
                    printf("  验证: %s\n", buffer);
                } else {
                    printf("  日期格式无效\n");
                }
            } else {
                printf("  格式: dt YYYY-MM-DD HH:MM:SS\n");
            }
        } else {
            printf("  未知命令，使用 ts 或 dt\n");
        }
    }
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("Unix时间戳转换 (Timestamp Conversion)\n");
    printf("==================================================\n");
    
    // 测试特殊时间戳
    test_special_timestamps();
    
    // 当前时间
    printf("\n当前时间:\n");
    time_t current_sec;
    long long current_ms;
    get_current_timestamp(&current_sec, &current_ms);
    
    char buffer[100];
    timestamp_to_datetime(current_sec, buffer, sizeof(buffer));
    printf("  秒级时间戳: %ld\n", current_sec);
    printf("  毫秒级时间戳: %lld\n", current_ms);
    printf("  可读格式: %s\n", buffer);
    
    // 反向转换测试
    printf("\n日期时间转时间戳:\n");
    const char* date_str = "2024-01-01 00:00:00";
    time_t timestamp;
    if (datetime_to_timestamp(date_str, "%Y-%m-%d %H:%M:%S", &timestamp) == 0) {
        printf("  %s → %ld\n", date_str, timestamp);
        
        // 验证转换
        timestamp_to_datetime(timestamp, buffer, sizeof(buffer));
        printf("  验证: %s\n", buffer);
    }
    
    // 时间差计算
    printf("\n时间差计算:\n");
    calculate_time_difference(1704067200, current_sec);  // 2024年元旦到现在
    
    // 时间戳运算
    timestamp_arithmetic();
    
    // 2038年问题
    demonstrate_y2k38_problem();
    
    printf("\n应用场景:\n");
    printf("  • 数据库时间戳存储\n");
    printf("  • 日志时间记录\n");
    printf("  • 缓存过期时间\n");
    printf("  • 分布式系统时间同步\n");
    printf("  • API请求时间戳\n");
    
    printf("\n注意事项:\n");
    printf("  • Unix时间戳从1970-01-01 00:00:00 UTC开始\n");
    printf("  • 32位系统存在2038年问题\n");
    printf("  • 时区处理需要特别注意\n");
    printf("  • 闰秒由系统自动处理\n");
    
    // 交互式转换（可选）
    // interactive_timestamp_conversion();
    
    return 0;
}
