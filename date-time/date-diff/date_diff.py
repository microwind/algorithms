"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

日期差计算 (Date Difference)
计算两个日期之间的天数差

算法原理：
1. 将两个日期分别转换为从公元1年1月1日以来的天数
2. 计算两个天数的差值即为日期间隔
3. 支持闰年计算，确保精度准确
"""

from dataclasses import dataclass
from typing import Tuple


@dataclass
class Date:
    """日期类"""
    year: int
    month: int
    day: int


def is_leap_year(year: int) -> bool:
    """
    判断是否为闰年
    参数: year - 年份
    返回: True表示闰年
    """
    return ((year % 4 == 0) and (year % 100 != 0)) or (year % 400 == 0)


def days_in_month(year: int, month: int) -> int:
    """
    获取某月的天数
    参数: year - 年份, month - 月份 (1-12)
    返回: 该月天数
    """
    days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    if month == 2 and is_leap_year(year):
        return 29  # 闰年2月有29天
    return days[month - 1]


def days_since_epoch(date: Date) -> int:
    """
    计算从公元1年1月1日到给定日期的天数
    参数: date - 日期对象
    返回: 累计天数
    """
    days = 0
    
    # 计算之前年份的天数
    for y in range(1, date.year):
        days += 366 if is_leap_year(y) else 365
    
    # 计算之前月份的天数
    for m in range(1, date.month):
        days += days_in_month(date.year, m)
    
    # 计算当月的天数
    days += date.day
    
    return days


def days_between(date1: Date, date2: Date) -> int:
    """
    计算两个日期之间的天数差
    参数: date1 - 第一个日期, date2 - 第二个日期
    返回: 天数差（绝对值）
    """
    days1 = days_since_epoch(date1)
    days2 = days_since_epoch(date2)
    return abs(days2 - days1)


def main():
    """测试主函数"""
    date1 = Date(2024, 1, 1)   # 元旦
    date2 = Date(2024, 10, 1)  # 国庆节
    
    diff = days_between(date1, date2)
    print("日期差计算测试")
    print("============")
    print(f"从 {date1.year}-{date1.month:02d}-{date1.day:02d} 到 {date2.year}-{date2.month:02d}-{date2.day:02d}")
    print(f"相差天数: {diff} 天")


if __name__ == "__main__":
    main()
