"""
数学基础 - 乘法运算 (Multiplication)
"""

def multiply(a: int, b: int) -> int:
    return a * b

def safe_multiply(a: int, b: int) -> int:
    result = a * b
    if a != 0 and result // a != b:
        raise OverflowError("乘法溢出")
    return result

def power_of_two_multiply(a: int, power: int) -> int:
    return a << power

def test_multiplication():
    print("乘法运算:")
    print(f"12 × 8 = {multiply(12, 8)}")
    print(f"100 × 25 = {multiply(100, 25)}")
    print(f"7 × 8 (移位) = {power_of_two_multiply(7, 3)}")

if __name__ == "__main__":
    test_multiplication()
