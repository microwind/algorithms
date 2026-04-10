"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

闰年判断 (Leap Year Check)
判断给定年份是否为闰年
"""

def is_leap_year(year: int) -> bool:
    """
    判断是否为闰年
    参数: year - 待判断的年份
    返回: True表示闰年，False表示平年
    """
    # 闰年条件：能被4整除且不能被100整除，或者能被400整除
    return ((year % 4 == 0) and (year % 100 != 0)) or (year % 400 == 0)


def main():
    """测试主函数"""
    test_years = [2000, 2004, 1900, 2023, 2024]
    
    print("闰年判断测试")
    print("============")
    
    for year in test_years:
        is_leap = is_leap_year(year)
        print(f"{year}年: {'闰年' if is_leap else '平年'}")


if __name__ == "__main__":
    main()
