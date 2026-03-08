"""
日期时间 - Unix时间戳转换
演示时间戳与日期时间之间的相互转换
"""
import time
from datetime import datetime, timezone


def timestamp_to_datetime(ts, is_milliseconds=False):
    """
    将Unix时间戳转换为日期时间字符串
    
    参数:
        ts: 时间戳（秒或毫秒）
        is_milliseconds: 是否为毫秒级时间戳
    """
    if is_milliseconds:
        ts = ts / 1000
    
    # 转换为UTC时间
    dt = datetime.fromtimestamp(ts, tz=timezone.utc)
    return dt.strftime("%Y-%m-%d %H:%M:%S UTC")


def datetime_to_timestamp(date_str, fmt="%Y-%m-%d %H:%M:%S"):
    """
    将日期时间字符串转换为Unix时间戳（秒）
    """
    dt = datetime.strptime(date_str, fmt)
    # 假设输入为UTC时间
    dt = dt.replace(tzinfo=timezone.utc)
    return int(dt.timestamp())


def get_current_timestamp():
    """获取当前Unix时间戳（秒和毫秒）"""
    seconds = int(time.time())
    milliseconds = int(time.time() * 1000)
    return seconds, milliseconds


def is_leap_year_timestamp(timestamp):
    """根据时间戳判断对应年份是否为闰年"""
    year = datetime.fromtimestamp(timestamp, tz=timezone.utc).year
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("Unix时间戳转换")
    print("=" * 50)
    
    # 一些特殊的时间戳
    test_timestamps = [
        0,                    # Unix纪元起点
        1704067200,          # 2024-01-01 00:00:00
        1000000000,          # 2001-09-09
        1234567890,          # 2009-02-13
        2000000000,          # 2033-05-18
    ]
    
    print("\n时间戳转日期时间:")
    for ts in test_timestamps:
        dt_str = timestamp_to_datetime(ts)
        leap = "闰年" if is_leap_year_timestamp(ts) else "平年"
        print(f"  {ts:>12}  →  {dt_str} ({leap})")
    
    # 当前时间
    print("\n当前时间:")
    ts_sec, ts_ms = get_current_timestamp()
    print(f"  秒级时间戳: {ts_sec}")
    print(f"  毫秒级时间戳: {ts_ms}")
    print(f"  可读格式: {timestamp_to_datetime(ts_sec)}")
    
    # 反向转换
    print("\n日期时间转时间戳:")
    date_str = "2024-01-01 00:00:00"
    ts = datetime_to_timestamp(date_str)
    print(f"  {date_str}  →  {ts}")
    
    print("\n2038年问题说明:")
    print("  32位有符号整数最大值为 2147483647")
    print("  对应时间: 2038-01-19 03:14:07 UTC")
    print("  之后会发生溢出，需要使用64位整数")
