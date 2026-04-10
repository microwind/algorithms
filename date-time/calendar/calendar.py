"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

完整版日历打印程序 (Calendar - Full Version)
根据年月输出当月日历，支持显示前后月份日期

核心算法：
1. 以1900年1月1日（星期一）为基准日期
2. 使用累加天数法计算任意日期是星期几
3. 日历显示包含上个月末尾几天和下个月开头几天
"""

# 基准日期设定：1900年1月1日，星期一
START_YEAR = 1900
START_MONTH = 1
START_DAY = 1
START_WEEKDAY = 1  # 1=星期一

# 星期标题
WEEKDAYS = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]

# 月份名称
MONTH_NAMES = [
    "Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.",
    "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."
]


def is_leap_year(year: int) -> bool:
    """
    判断是否为闰年
    闰年规则：能被4整除且不能被100整除，或能被400整除
    """
    return ((year % 4 == 0) and (year % 100 != 0)) or (year % 400 == 0)


def get_month_days(month: int, year: int) -> int:
    """
    获取某月的天数
    """
    if month == 2:
        return 29 if is_leap_year(year) else 28
    elif month in [4, 6, 9, 11]:
        return 30
    else:
        return 31


def get_last_month_days(month: int, year: int) -> int:
    """
    获取上个月的天数
    """
    last_month = 12 if month == 1 else month - 1
    last_year = year - 1 if month == 1 else year
    return get_month_days(last_month, last_year)


def get_weekday_of_date(month: int, day: int, year: int) -> int:
    """
    计算指定日期是星期几（核心算法）
    基于1900年1月1日（星期一）累加天数计算
    """
    weekday = START_WEEKDAY
    
    # 累加从1900年到目标年份-1的所有天数
    for i in range(START_YEAR, year):
        weekday = (weekday + 365) % 7
        if is_leap_year(i):
            weekday = (weekday + 1) % 7
    
    # 累加从1月到目标月份-1的所有天数
    for i in range(START_MONTH, month):
        weekday = (weekday + get_month_days(i, year)) % 7
    
    # 加上目标日期与1日的差值
    if day > START_DAY:
        weekday = (weekday + (day - START_DAY)) % 7
    
    return weekday


def get_first_weekday_of_month(month: int, year: int) -> int:
    """
    获取某月第一天是星期几
    """
    return get_weekday_of_date(month, 1, year)


def get_last_weekday_of_month(month: int, year: int) -> int:
    """
    获取某月最后一天是星期几
    """
    last_day = get_month_days(month, year)
    return get_weekday_of_date(month, last_day, year)


def print_calendar_title(month: int, year: int) -> None:
    """
    打印日历标题
    """
    print(f"{MONTH_NAMES[month - 1]:>16} {year}")


def print_weekly_title() -> None:
    """
    打印星期标题
    """
    print("".join(f"{day:>5}" for day in WEEKDAYS))


def print_last_month_last_days(weekday: int, month: int, year: int) -> None:
    """
    打印上个月最后几天（用"]"标记）
    """
    last_days = get_last_month_days(month, year)
    start_day = last_days - weekday + 1
    for i in range(start_day, last_days + 1):
        print(f"{i:>2}]", end="")


def print_next_month_start_days(weekday: int) -> None:
    """
    打印下个月开始几天（用"]"标记）
    """
    next_days = 7 - weekday
    for i in range(1, next_days):
        print(f"{i:>2}]", end="")


def print_calendar(month: int, year: int) -> None:
    """
    打印日历（包含前后月份日期）
    """
    # 打印标题和星期标题
    print_calendar_title(month, year)
    print_weekly_title()
    
    # 计算当月第一天是周几
    first_weekday = get_first_weekday_of_month(month, year)
    weekday = first_weekday
    
    # 打印上个月最后几天
    print_last_month_last_days(weekday, month, year)
    
    # 获取当月总天数
    days_in_month = get_month_days(month, year)
    
    # 循环输出当月所有日期
    for day in range(1, days_in_month + 1):
        print(f"{day:>5}", end="")
        if weekday == 6:  # Saturday
            print()
        weekday = (weekday + 1) % 7
    
    # 打印下个月开头几天
    last_weekday = get_last_weekday_of_month(month, year)
    print_next_month_start_days(last_weekday)
    print()


def main():
    """测试主函数"""
    print("完整版日历打印程序")
    print("==================")
    
    month = 12
    day = 30
    year = 2003
    
    # 测试：计算2003年12月30日是星期几
    weekday = get_weekday_of_date(month, day, year)
    print(f"[{weekday}] = {WEEKDAYS[weekday]}")
    print(f"TEST: {MONTH_NAMES[month - 1]} {year} days = {get_month_days(month, year)}")
    print(f"{year}-{month}-{day} is {WEEKDAYS[weekday]} = WEEKDAYS[{weekday}]")
    print()
    
    # 循环打印48个月的日历（4年）
    tmp_month = 0
    tmp_year = year
    max_month = 48
    
    for m in range(max_month):
        tmp_month += 1
        if tmp_month == 13:
            tmp_month = 1
            tmp_year += 1
        print(f"{tmp_month}-{tmp_year}")
        print_calendar(tmp_month, tmp_year)
        print()


if __name__ == "__main__":
    main()
