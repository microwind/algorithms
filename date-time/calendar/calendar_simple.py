"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

日历打印 (Calendar Printer)
根据年月输出当月日历

本文件提供两种算法实现：
1. Zeller公式法：通过数学公式直接计算星期几，计算速度快
2. 基准日期法：从1900年1月1日累加天数计算，直观易懂（与C版本一致）
"""

# 基准日期设定：1900年1月1日，星期一（与C版本一致）
START_YEAR = 1900
START_MONTH = 1
START_DAY = 1
START_WEEKDAY = 1  # 1=星期一

# 星期标题
WEEKDAYS = ["日", "一", "二", "三", "四", "五", "六"]

# 月份名称
MONTH_NAMES = [
    "一月", "二月", "三月", "四月", "五月", "六月",
    "七月", "八月", "九月", "十月", "十一月", "十二月"
]


def is_leap_year(year: int) -> bool:
    """
    判断是否为闰年
    参数: year - 年份
    返回: True表示闰年
    """
    return ((year % 4 == 0) and (year % 100 != 0)) or (year % 400 == 0)


def get_month_days(year: int, month: int) -> int:
    """
    获取某月的天数
    参数: year - 年份, month - 月份 (1-12)
    返回: 该月天数
    """
    days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    if month == 2 and is_leap_year(year):
        return 29
    return days[month - 1]


def get_first_weekday_zeller(year: int, month: int) -> int:
    """
    使用Zeller公式计算某月第一天是星期几
    算法特点：数学公式直接计算，O(1)时间复杂度
    参数: year - 年份, month - 月份 (1-12)
    返回: 0=星期日, 1=星期一, ..., 6=星期六
    """
    y, m = year, month
    if m < 3:
        m += 12
        y -= 1
    k = y % 100
    j = y // 100
    h = (1 + (13 * (m + 1)) // 5 + k + k // 4 + j // 4 - 2 * j) % 7
    if h < 0:
        h += 7
    day_map = [6, 0, 1, 2, 3, 4, 5]
    return day_map[h]


def get_weekday_of_date_base(year: int, month: int, day: int) -> int:
    """
    使用基准日期法计算指定日期是星期几
    算法特点：从1900年1月1日累加天数，直观易懂
    公式：(START_WEEKDAY + 天数差) % 7 = 目标星期
    参数: year - 年份, month - 月份 (1-12), day - 日期 (1-31)
    返回: 0=星期日, 1=星期一, ..., 6=星期六
    """
    total_days = START_WEEKDAY
    
    # 累加从1900年到目标年份-1的所有天数
    for i in range(START_YEAR, year):
        total_days += 365
        if is_leap_year(i):
            total_days += 1  # 闰年加1天
    
    # 累加从1月到目标月份-1的所有天数
    for i in range(START_MONTH, month):
        total_days += get_month_days(year, i)
    
    # 加上目标日期与1日的差值
    if day > START_DAY:
        total_days += (day - START_DAY)
    
    # 对7取模得到星期
    return total_days % 7


def get_first_weekday(year: int, month: int) -> int:
    """
    获取某月第一天是星期几（默认使用基准日期法，与C版本一致）
    参数: year - 年份, month - 月份 (1-12)
    返回: 0=星期日, 1=星期一, ..., 6=星期六
    """
    # 使用基准日期法，与C版本calendar_simple.c算法一致
    return get_weekday_of_date_base(year, month, 1)


def print_calendar(year: int, month: int) -> None:
    """
    打印日历
    参数: year - 年份, month - 月份 (1-12)
    """
    print(f"\n      {MONTH_NAMES[month - 1]} {year}")
    print("===========================")
    
    # 打印星期标题
    print(" ".join(f"{day:>3}" for day in WEEKDAYS))
    
    # 计算第一天是星期几和该月天数
    first_weekday = get_first_weekday(year, month)
    days_in_month = get_month_days(year, month)
    
    # 打印第一行前面的空格
    line = "    " * first_weekday
    
    # 打印日期
    weekday = first_weekday
    for day in range(1, days_in_month + 1):
        line += f"{day:>3} "
        weekday += 1
        if weekday == 7:
            print(line)
            line = ""
            weekday = 0
    
    if line:
        print(line)


def main():
    """测试主函数"""
    print("日历打印程序")
    print("============")
    
    # 打印2024年1月日历
    print_calendar(2024, 1)
    
    # 打印2024年6月日历
    print_calendar(2024, 6)


if __name__ == "__main__":
    main()
