"""
数学基础 - 平方根计算 (Square Root)
"""

import math

def sqrt_newton(n: float, epsilon: float = 1e-10) -> float:
    if n < 0:
        raise ValueError("不能计算负数的平方根")
    if n == 0:
        return 0.0
    x = n
    while abs(x * x - n) > epsilon:
        x = (x + n / x) / 2.0
    return x

def sqrt_integer(n: int) -> int:
    if n < 0:
        raise ValueError("不能计算负数的平方根")
    if n < 2:
        return n
    left, right = 1, n // 2
    while left <= right:
        mid = (left + right) // 2
        square = mid * mid
        if square == n:
            return mid
        if square < n:
            left = mid + 1
        else:
            right = mid - 1
    return right

def test_sqrt():
    print("平方根计算:")
    test_values = [1, 2, 4, 9, 16, 25, 100]
    for n in test_values:
        result = sqrt_newton(n)
        print(f"sqrt({n}) = {result:.10f} (math.sqrt: {math.sqrt(n)})")

if __name__ == "__main__":
    test_sqrt()
