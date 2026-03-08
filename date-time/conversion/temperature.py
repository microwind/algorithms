"""
日期时间 - 温度转换
摄氏度、华氏度、开尔文之间的相互转换
"""


def celsius_to_fahrenheit(c):
    """摄氏度转华氏度: °F = °C × 9/5 + 32"""
    return c * 9 / 5 + 32


def fahrenheit_to_celsius(f):
    """华氏度转摄氏度: °C = (°F - 32) × 5/9"""
    return (f - 32) * 5 / 9


def celsius_to_kelvin(c):
    """摄氏度转开尔文: K = °C + 273.15"""
    return c + 273.15


def kelvin_to_celsius(k):
    """开尔文转摄氏度: °C = K - 273.15"""
    return k - 273.15


def fahrenheit_to_kelvin(f):
    """华氏度转开尔文"""
    return celsius_to_kelvin(fahrenheit_to_celsius(f))


def kelvin_to_fahrenheit(k):
    """开尔文转华氏度"""
    return celsius_to_fahrenheit(kelvin_to_celsius(k))


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("温度转换")
    print("=" * 50)
    
    # 常见温度点
    test_cases = [
        ("绝对零度", -273.15),
        ("冰点", 0),
        ("室温", 20),
        ("人体体温", 37),
        ("沸点", 100),
    ]
    
    print("\n常见温度对照表:")
    print(f"{'描述':<12} {'摄氏°C':<10} {'华氏°F':<12} {'开尔文K':<10}")
    print("-" * 50)
    
    for name, celsius in test_cases:
        fahrenheit = celsius_to_fahrenheit(celsius)
        kelvin = celsius_to_kelvin(celsius)
        print(f"{name:<12} {celsius:<10.2f} {fahrenheit:<12.2f} {kelvin:<10.2f}")
    
    # 双向转换验证
    print("\n转换验证:")
    c = 25
    f = celsius_to_fahrenheit(c)
    k = celsius_to_kelvin(c)
    print(f"{c}°C → {f:.2f}°F → {fahrenheit_to_celsius(f):.2f}°C (验证)")
    print(f"{c}°C → {k:.2f}K → {kelvin_to_celsius(k):.2f}°C (验证)")
