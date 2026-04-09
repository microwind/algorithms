"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

温度单位转换 (Temperature Unit Conversion)
摄氏度与华氏度之间的相互转换
"""

def celsius_to_fahrenheit(c: float) -> float:
    """摄氏度转华氏度"""
    return 9.0 / 5.0 * c + 32

def fahrenheit_to_celsius(f: int) -> int:
    """华氏度转摄氏度"""
    return 5 * (f - 32) // 9

def print_conversion_table(start: int, end: int, step: int) -> None:
    """打印转换表"""
    print("摄氏度到华氏度转换表")
    print("摄氏度 | 华氏度")
    print("-------|-------")
    
    for c in range(start, end + 1, step):
        f = celsius_to_fahrenheit(c)
        print(f"{c:6d}  | {f:6.1f}")

def main():
    print("温度单位转换演示")
    print("================\n")
    
    print_conversion_table(0, 100, 5)
    
    print("\n转换公式:")
    print("• 摄氏度→华氏度: °F = °C × 9/5 + 32")
    print("• 华氏度→摄氏度: °C = (°F - 32) × 5/9")

if __name__ == "__main__":
    main()
