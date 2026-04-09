"""
数学基础 - 最大值与最小值 (Max and Min)
"""

from typing import List

def max_val(a: int, b: int) -> int:
    return a if a > b else b

def min_val(a: int, b: int) -> int:
    return a if a < b else b

def max_of_list(numbers: List[int]) -> int:
    return max(numbers)

def min_of_list(numbers: List[int]) -> int:
    return min(numbers)

def test_max():
    print("最大值/最小值:")
    print(f"max(5, 3) = {max_val(5, 3)}")
    print(f"min(5, 3) = {min_val(5, 3)}")
    numbers = [10, 25, 3, 100, 7]
    print(f"列表 {numbers}:")
    print(f"最大值 = {max_of_list(numbers)}")
    print(f"最小值 = {min_of_list(numbers)}")

if __name__ == "__main__":
    test_max()
