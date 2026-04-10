"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

日期格式化与解析 (Date Format)
支持多种日期格式转换
"""

# 英文月份名称
MONTH_NAMES_EN = [
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
]

# 中文月份名称
MONTH_NAMES_CN = [
    "一月", "二月", "三月", "四月",
    "五月", "六月", "七月", "八月",
    "九月", "十月", "十一月", "十二月"
]


def format_date(year: int, month: int, day: int, fmt: str = "ISO") -> str:
    """
    将日期格式化为不同格式的字符串
    参数:
        year, month, day - 年月日
        fmt - 格式类型: "ISO", "US", "CN", "FULL"
    返回: 格式化后的日期字符串
    """
    return format_datetime(year, month, day, 0, 0, 0, fmt)


def format_datetime(year: int, month: int, day: int,
                   hour: int, minute: int, second: int, fmt: str = "ISO") -> str:
    """
    将日期时间格式化为不同格式的字符串
    参数:
        year, month, day, hour, minute, second - 年月日时分秒
        fmt - 格式类型: "ISO", "US", "CN", "FULL"
    返回: 格式化后的日期时间字符串
    """
    fmt_upper = fmt.upper()
    
    if fmt_upper == "ISO":
        # ISO 8601: 2024-01-01
        return f"{year:04d}-{month:02d}-{day:02d}"
    elif fmt_upper == "US":
        # US格式: 01/01/2024
        return f"{month:02d}/{day:02d}/{year:04d}"
    elif fmt_upper == "CN":
        # 中文格式: 2024年01月01日
        return f"{year:04d}年{month:02d}月{day:02d}日"
    elif fmt_upper == "FULL":
        # 完整格式: 2024-01-01 12:30:45
        return f"{year:04d}-{month:02d}-{day:02d} {hour:02d}:{minute:02d}:{second:02d}"
    else:
        return "Unknown format"


def get_month_name(month: int, chinese: bool = False) -> str:
    """
    获取月份名称
    参数:
        month - 月份 (1-12)
        chinese - 是否返回中文名称
    返回: 月份名称
    """
    if month < 1 or month > 12:
        return "未知" if chinese else "Unknown"
    return MONTH_NAMES_CN[month - 1] if chinese else MONTH_NAMES_EN[month - 1]


def main():
    """测试主函数"""
    print("日期格式化示例")
    print("==============")
    
    year, month, day = 2024, 3, 15
    hour, minute, second = 14, 30, 0
    
    print(f"原始日期: {year}年{month}月{day}日")
    print()
    
    # 测试各种格式
    print(f"ISO格式:   {format_date(year, month, day, 'ISO')}")
    print(f"US格式:    {format_date(year, month, day, 'US')}")
    print(f"中文格式:  {format_date(year, month, day, 'CN')}")
    print(f"完整格式:  {format_datetime(year, month, day, hour, minute, second, 'FULL')}")
    print()
    
    # 测试月份名称
    print("月份名称:")
    print(f"  英文: {get_month_name(month, False)}")
    print(f"  中文: {get_month_name(month, True)}")


if __name__ == "__main__":
    main()
