"""
数学基础 - 平均值计算 (Average)
"""

from typing import List

def average(numbers: List[float]) -> float:
    if not numbers:
        raise ValueError("列表不能为空")
    return sum(numbers) / len(numbers)

def average_safe(a: int, b: int) -> float:
    return a / 2.0 + b / 2.0

def test_average():
    print("平均值计算:")
    numbers = [10.0, 20.0, 30.0, 40.0, 50.0]
    print(f"平均值 = {average(numbers)}")

if __name__ == "__main__":
    test_average()
