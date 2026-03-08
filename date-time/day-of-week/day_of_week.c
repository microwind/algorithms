/*
 * 日期时间 - 星期计算 (Day of Week)
 * 使用 Zeller 公式计算给定日期是星期几
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 使用 Zeller 公式计算星期几
 * 
 * 参数:
 *     year: 年份
 *     month: 月份 (1-12)
 *     day: 日期 (1-31)
 * 返回:
 *     0=星期日, 1=星期一, ..., 6=星期六
 */
int day_of_week(int year, int month, int day) {
    // 调整月份：1月和2月视为上一年的13月和14月
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    
    int q = day;           // 日期
    int m = month;         // 调整后的月份
    int k = year % 100;    // 世纪内的年份
    int j = year / 100;    // 零基世纪
    
    // Zeller 公式
    int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    
    // 调整结果：Zeller公式的0是星期六，需要转换为0=星期日
    if (h < 0) h += 7;  // 处理负数情况
    
    // 转换映射：Zeller结果 -> 标准结果 (0=星期日, 1=星期一, ..., 6=星期六)
    int day_map[] = {6, 0, 1, 2, 3, 4, 5};  // h=0->6, h=1->0, h=2->1, ...
    return day_map[h];
}

/**
 * 获取星期几的中文名称
 */
const char* get_weekday_name_cn(int weekday) {
    static const char* names[] = {
        "星期日", "星期一", "星期二", "星期三", 
        "星期四", "星期五", "星期六"
    };
    return names[weekday];
}

/**
 * 获取星期几的英文名称
 */
const char* get_weekday_name_en(int weekday) {
    static const char* names[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", 
        "Thursday", "Friday", "Saturday"
    };
    return names[weekday];
}

/**
 * 获取星期几的缩写
 */
const char* get_weekday_abbr(int weekday) {
    static const char* abbr[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return abbr[weekday];
}

/**
 * 验证日期的有效性
 */
int is_valid_date(int year, int month, int day) {
    // 基本范围检查
    if (year < 1 || year > 9999) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    // 检查每月的天数
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // 闰年二月有29天
    if (month == 2) {
        int is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (is_leap && day > 29) return 0;
        if (!is_leap && day > 28) return 0;
    } else {
        if (day > days_in_month[month - 1]) return 0;
    }
    
    return 1;
}

/**
 * 计算某年某月的第一个星期几
 */
int first_day_of_month(int year, int month) {
    return day_of_week(year, month, 1);
}

/**
 * 计算某年某月的天数
 */
int days_in_month(int year, int month) {
    if (month == 2) {
        // 闰年判断
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    }
    
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}

/**
 * 打印月历
 */
void print_month_calendar(int year, int month) {
    const char* month_names[] = {
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"
    };
    
    printf("\n%s %d\n", month_names[month - 1], year);
    printf("日 一 二 三 四 五 六\n");
    
    int first_day = first_day_of_month(year, month);
    int days = days_in_month(year, month);
    
    // 打印前面的空格
    for (int i = 0; i < first_day; i++) {
        printf("   ");
    }
    
    // 打印日期
    for (int day = 1; day <= days; day++) {
        printf("%2d ", day);
        if ((first_day + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

/**
 * 计算两个日期之间的天数差
 */
int days_between_dates(int year1, int month1, int day1, 
                    int year2, int month2, int day2) {
    // 简化实现：使用绝对天数计算
    // 这里使用一个近似公式，实际应用中需要更精确的算法
    
    if (!is_valid_date(year1, month1, day1) || !is_valid_date(year2, month2, day2)) {
        return -1;  // 无效日期
    }
    
    // 转换为从公元1年1月1日开始的天数（简化版）
    int days1 = year1 * 365 + month1 * 30 + day1;
    int days2 = year2 * 365 + month2 * 30 + day2;
    
    return days2 - days1;
}

/**
 * 打印日期信息
 */
void print_date_info(int year, int month, int day) {
    if (!is_valid_date(year, month, day)) {
        printf("无效日期: %d年%d月%d日\n", year, month, day);
        return;
    }
    
    int weekday = day_of_week(year, month, day);
    const char* name_cn = get_weekday_name_cn(weekday);
    const char* name_en = get_weekday_name_en(weekday);
    const char* abbr = get_weekday_abbr(weekday);
    
    printf("%d年%02d月%02d日: %s (%s, %s)\n", 
           year, month, day, name_cn, name_en, abbr);
}

/**
 * 测试特定日期
 */
void test_specific_dates() {
    printf("特定日期测试:\n");
    
    struct {
        int year;
        int month;
        int day;
        const char* description;
    } test_dates[] = {
        {2024, 1, 1, "元旦"},
        {2024, 2, 10, "春节"},
        {2024, 3, 15, "随机日期"},
        {2024, 6, 1, "儿童节"},
        {2024, 10, 1, "国庆节"},
        {2000, 1, 1, "千禧年"},
        {1997, 7, 1, "香港回归"},
        {1999, 12, 31, "世纪末"},
        {2023, 12, 25, "圣诞节"}
    };
    
    int num_dates = sizeof(test_dates) / sizeof(test_dates[0]);
    
    for (int i = 0; i < num_dates; i++) {
        printf("  %s: ", test_dates[i].description);
        print_date_info(test_dates[i].year, test_dates[i].month, test_dates[i].day);
    }
}

/**
 * 验证Zeller公式的正确性
 */
void verify_zeller_formula() {
    printf("\nZeller公式验证:\n");
    
    // 已知结果的日期
    struct {
        int year, month, day;
        int expected_weekday;
    } known_dates[] = {
        {2024, 1, 1, 1},   // 星期一
        {2024, 2, 14, 3},  // 星期三
        {2024, 7, 4, 4},   // 星期四
        {2000, 1, 1, 6},   // 星期六
        {1999, 12, 31, 5}, // 星期五
        {2023, 12, 25, 1}  // 星期一
    };
    
    int num_dates = sizeof(known_dates) / sizeof(known_dates[0]);
    int all_correct = 1;
    
    for (int i = 0; i < num_dates; i++) {
        int calculated = day_of_week(known_dates[i].year, 
                                   known_dates[i].month, 
                                   known_dates[i].day);
        int expected = known_dates[i].expected_weekday;
        
        printf("  %d/%02d/%02d: 计算=%s, 期望=%s %s\n",
               known_dates[i].year, known_dates[i].month, known_dates[i].day,
               get_weekday_name_cn(calculated),
               get_weekday_name_cn(expected),
               (calculated == expected) ? "✓" : "✗");
        
        if (calculated != expected) {
            all_correct = 0;
        }
    }
    
    printf("\n验证结果: %s\n", all_correct ? "全部正确 ✓" : "存在错误 ✗");
}

/**
 * 交互式日期查询
 */
void interactive_date_query() {
    printf("\n交互式日期查询:\n");
    printf("输入格式: 年 月 日 (例如: 2024 3 15)\n");
    printf("输入 0 0 0 退出\n\n");
    
    int year, month, day;
    
    while (1) {
        printf("> ");
        if (scanf("%d %d %d", &year, &month, &day) != 3) {
            printf("输入格式错误\n");
            while (getchar() != '\n'); // 清除输入缓冲区
            continue;
        }
        
        if (year == 0 && month == 0 && day == 0) {
            break;
        }
        
        print_date_info(year, month, day);
    }
}

// 测试示例
int main() {
    printf("==================================================\n");
    printf("星期计算 - Zeller公式 (Day of Week)\n");
    printf("==================================================\n");
    
    // 测试特定日期
    test_specific_dates();
    
    // 验证Zeller公式
    verify_zeller_formula();
    
    // 打印当前月份的日历（示例）
    printf("\n2024年3月日历:\n");
    print_month_calendar(2024, 3);
    
    printf("\nZeller公式说明:\n");
    printf("  h = (q + (13(m+1))/5 + k + k/4 + j/4 - 2j) mod 7\n");
    printf("  其中:\n");
    printf("    h: 星期几 (0=星期六, 1=星期日, ..., 6=星期五)\n");
    printf("    q: 日期\n");
    printf("    m: 月份 (3=三月, 4=四月, ..., 12=十二月, 13=一月, 14=二月)\n");
    printf("    k: 年份 % 100\n");
    printf("    j: 年份 / 100\n");
    
    printf("\n应用场景:\n");
    printf("  • 日历应用开发\n");
    printf("  • 日期计算工具\n");
    printf("  • 调度系统\n");
    printf("  • 历史日期验证\n");
    printf("  • 节假日计算\n");
    
    printf("\n注意事项:\n");
    printf("  • 适用于格里高利历（1582年10月15日后）\n");
    printf("  • 1月和2月要视为前一年的13月和14月\n");
    printf("  • 结果需要调整以符合常规的星期表示\n");
    
    // 交互式查询（可选）
    // interactive_date_query();
    
    return 0;
}
