"""
数学基础 - 加法运算 (Addition)
"""

def add(a: int, b: int) -> int:
    return a + b

def safe_add(a: int, b: int) -> int:
    result = a + b
    if (a > 0 and b > 0 and result < 0) or (a < 0 and b < 0 and result > 0):
        raise OverflowError("加法溢出")
    return result

def test_add():
    print("加法运算:")
    print(f"5 + 3 = {add(5, 3)}")
    print(f"100 + 200 = {add(100, 200)}")

if __name__ == "__main__":
    test_add()
