"""
日期时间 - 星期计算 (Day of Week)
使用 Zeller 公式计算给定日期是星期几
"""


def day_of_week(year, month, day):
    """
    使用 Zeller 公式计算星期几
    
    返回: 0=星期六, 1=星期日, 2=星期一, ..., 6=星期五
    """
    # 调整月份：1月和2月视为上一年的13月和14月
    if month < 3:
        month += 12
        year -= 1
    
    q = day  # 日期
    m = month  # 调整后的月份
    k = year % 100  # 世纪内的年份
    j = year // 100  # 零基世纪
    
    # Zeller 公式
    h = (q + (13 * (m + 1)) // 5 + k + k // 4 + j // 4 - 2 * j) % 7
    
    # 调整结果，使其符合常用习惯 (0=星期日, 1=星期一, ..., 6=星期六)
    # Zeller公式的0是星期六，需要转换
    day_map = {0: 6, 1: 0, 2: 1, 3: 2, 4: 3, 5: 4, 6: 5}
    return day_map[h]


def get_weekday_name(weekday):
    """获取星期几的中文名称"""
    names = ["星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"]
    return names[weekday]


def get_weekday_name_en(weekday):
    """获取星期几的英文名称"""
    names = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
    return names[weekday]


# 测试示例
if __name__ == "__main__":
    test_dates = [
        (2024, 1, 1),   # 元旦
        (2024, 2, 10),  # 春节
        (2024, 3, 15),  # 随机日期
        (2024, 6, 1),   # 儿童节
        (2024, 10, 1),  # 国庆节
        (2000, 1, 1),   # 千禧年
        (1997, 7, 1),   # 香港回归
    ]
    
    print("=" * 50)
    print("星期计算 - Zeller公式")
    print("=" * 50)
    
    for year, month, day in test_dates:
        weekday = day_of_week(year, month, day)
        name_cn = get_weekday_name(weekday)
        name_en = get_weekday_name_en(weekday)
        print(f"{year}年{month:02d}月{day:02d}日: {name_cn} ({name_en})")
