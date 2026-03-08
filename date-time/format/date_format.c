/*
 * 日期时间 - 日期格式化与解析
 * 支持多种日期格式转换
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} DateTime;

// 将日期格式化为字符串
void format_date(DateTime dt, char *output, const char *format) {
    if (strcmp(format, "ISO") == 0) {
        // ISO 8601: 2024-01-01
        sprintf(output, "%04d-%02d-%02d", dt.year, dt.month, dt.day);
    } else if (strcmp(format, "US") == 0) {
        // US格式: 01/01/2024
        sprintf(output, "%02d/%02d/%04d", dt.month, dt.day, dt.year);
    } else if (strcmp(format, "CN") == 0) {
        // 中文格式: 2024年01月01日
        sprintf(output, "%04d年%02d月%02d日", dt.year, dt.month, dt.day);
    } else if (strcmp(format, "FULL") == 0) {
        // 完整格式: 2024-01-01 12:30:45
        sprintf(output, "%04d-%02d-%02d %02d:%02d:%02d",
                dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
    } else {
        strcpy(output, "Unknown format");
    }
}

// 解析日期字符串 (支持 YYYY-MM-DD)
int parse_date(const char *date_str, DateTime *dt) {
    int result = sscanf(date_str, "%d-%d-%d", &dt->year, &dt->month, &dt->day);
    if (result != 3) {
        return -1; // 解析失败
    }
    dt->hour = 0;
    dt->minute = 0;
    dt->second = 0;
    return 0; // 解析成功
}

// 获取月份名称
const char* get_month_name(int month) {
    const char* months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    }
    return "Unknown";
}

// 获取月份名称(中文)
const char* get_month_name_cn(int month) {
    const char* months[] = {
        "一月", "二月", "三月", "四月",
        "五月", "六月", "七月", "八月",
        "九月", "十月", "十一月", "十二月"
    };
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    }
    return "未知";
}

int main() {
    DateTime dt = {2024, 3, 15, 14, 30, 0};
    char buffer[100];
    
    printf("日期格式化示例:\n\n");
    
    printf("日期: %04d-%02d-%02d %02d:%02d:%02d\n\n",
           dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
    
    // 不同格式输出
    format_date(dt, buffer, "ISO");
    printf("ISO格式:      %s\n", buffer);
    
    format_date(dt, buffer, "US");
    printf("US格式:       %s\n", buffer);
    
    format_date(dt, buffer, "CN");
    printf("中文格式:     %s\n", buffer);
    
    format_date(dt, buffer, "FULL");
    printf("完整格式:     %s\n\n", buffer);
    
    // 月份名称
    printf("月份名称:\n");
    printf("  英文: %s\n", get_month_name(dt.month));
    printf("  中文: %s\n\n", get_month_name_cn(dt.month));
    
    // 解析示例
    const char *input = "2024-12-25";
    DateTime parsed;
    if (parse_date(input, &parsed) == 0) {
        printf("解析字符串 '%s':\n", input);
        printf("  年: %d\n", parsed.year);
        printf("  月: %d\n", parsed.month);
        printf("  日: %d\n", parsed.day);
    }
    
    return 0;
}
