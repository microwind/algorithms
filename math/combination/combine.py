"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

组合计算 (Combination)
计算从n个元素中选取k个元素的组合数
"""

def factorial(n: int) -> int:
    """计算阶乘"""
    product = 1
    for i in range(1, n + 1):
        product *= i
    return product

def combine(n: int, k: int) -> int:
    """计算组合数 C(n,k)"""
    return factorial(n) // (factorial(k) * factorial(n - k))

def main():
    n = 5
    print("组合计算 C(n,k)")
    print("===============")
    
    for k in range(1, n + 1):
        result = combine(n, k)
        print(f"C({n},{k}) = {result}")

if __name__ == "__main__":
    main()
