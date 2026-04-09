"""
数学基础 - 阶乘计算 (Factorial)
计算非负整数的阶乘 n!
支持递归、迭代和大数计算
时间复杂度: O(n)
"""

import math
from functools import reduce
from typing import Union


def factorial_iterative(n: int) -> int:
    """
    迭代计算阶乘
    
    算法原理：
    - n! = 1 × 2 × 3 × ... × n
    - 0! = 1（空积的定义）
    
    参数:
        n: 非负整数
    返回:
        n! 的结果
    
    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n > 20:
        raise ValueError("n太大，会导致int溢出，请使用factorial_big")
    
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def factorial_recursive(n: int) -> int:
    """
    递归计算阶乘
    
    时间复杂度: O(n)
    空间复杂度: O(n) - 递归栈
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n <= 1:
        return 1
    return n * factorial_recursive(n - 1)


def factorial_tail_recursive(n: int, accumulator: int = 1) -> int:
    """
    尾递归优化版本
    
    注意：Python不优化尾递归，这只是演示
    """
    if n <= 1:
        return accumulator
    return factorial_tail_recursive(n - 1, n * accumulator)


def factorial_big(n: int) -> int:
    """
    大数阶乘计算
    
    Python的int可以自动处理大数，没有溢出问题
    1000! 有 2568 位数字
    10000! 有 35660 位数字
    """
    if n < 0:
        raise ValueError("n必须非负")
    
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def factorial_reduce(n: int) -> int:
    """
    使用reduce函数计算阶乘（函数式风格）
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n <= 1:
        return 1
    return reduce(lambda x, y: x * y, range(1, n + 1))


def factorial_math(n: int) -> int:
    """
    使用math.factorial（标准库）
    """
    return math.factorial(n)


def double_factorial(n: int) -> int:
    """
    双阶乘 n!! = n × (n-2) × (n-4) × ...
    """
    if n < 0:
        raise ValueError("n必须非负")
    
    result = 1
    for i in range(n, 0, -2):
        result *= i
    return result


def permutation(n: int, k: int) -> int:
    """
    排列数 P(n, k) = n! / (n-k)!
    从n个不同元素中取出k个元素的排列数
    """
    if k > n or k < 0:
        raise ValueError("k必须在0到n之间")
    
    result = 1
    for i in range(n, n - k, -1):
        result *= i
    return result


def combination(n: int, k: int) -> int:
    """
    组合数 C(n, k) = n! / (k! × (n-k)!)
    从n个不同元素中取出k个元素的组合数
    
    使用对称性优化：C(n,k) = C(n, n-k)
    """
    if k > n or k < 0:
        raise ValueError("k必须在0到n之间")
    
    # 利用对称性减少计算
    k = min(k, n - k)
    
    result = 1
    for i in range(1, k + 1):
        result = result * (n - k + i) // i
    return result


def stirling_approximation(n: int) -> float:
    """
    斯特林公式近似计算阶乘
    
    n! ≈ √(2πn) × (n/e)^n
    """
    import math
    if n < 0:
        raise ValueError("n必须非负")
    if n == 0:
        return 1.0
    
    return math.sqrt(2 * math.pi * n) * (n / math.e) ** n


def test_factorial():
    """测试函数"""
    print("=" * 50)
    print("    阶乘计算演示 (Factorial n!)")
    print("=" * 50)
    print()
    
    # 阶乘表
    print("阶乘表 (0! 到 20!):")
    print("-" * 50)
    for i in range(21):
        result = factorial_iterative(i)
        print(f"{i:2d}! = {result:20d}")
    
    # 大数阶乘
    print("\n" + "=" * 50)
    print("大数阶乘:")
    print("=" * 50)
    for n in [50, 100, 500, 1000]:
        fact_n = factorial_big(n)
        digits = len(str(fact_n))
        print(f"{n}! 的位数: {digits}")
    
    # 显示100!的前50位和后20位
    fact_100 = factorial_big(100)
    fact_100_str = str(fact_100)
    print(f"\n100! = {fact_100_str[:50]}...{fact_100_str[-20:]}")
    
    # 斯特林近似
    print("\n" + "=" * 50)
    print("斯特林公式近似:")
    print("=" * 50)
    for n in [5, 10, 20, 50, 100]:
        exact = factorial_big(n)
        approx = stirling_approximation(n)
        error = abs(exact - approx) / exact * 100
        print(f"{n}! 精确值: {len(str(exact))}位数")
        print(f"{n}! 近似值: {approx:.2e}")
        print(f"相对误差: {error:.6f}%")
        print()
    
    # 排列组合
    print("=" * 50)
    print("排列组合计算:")
    print("=" * 50)
    print(f"P(10, 3) = {permutation(10, 3)} (从10个中取3个排列)")
    print(f"C(10, 3) = {combination(10, 3)} (从10个中取3个组合)")
    print(f"C(52, 5) = {combination(52, 5)} (扑克牌5张组合数)")
    
    # 杨辉三角
    print("\n" + "=" * 50)
    print("杨辉三角（前8行）:")
    print("=" * 50)
    for n in range(8):
        # 打印前导空格
        print("  " * (7 - n), end="")
        for k in range(n + 1):
            print(f"{combination(n, k):4d}", end=" ")
        print()
    
    # 双阶乘
    print("\n" + "=" * 50)
    print("双阶乘:")
    print("=" * 50)
    for n in range(1, 16):
        df = double_factorial(n)
        print(f"{n:2d}!! = {df}")
    
    # 数学性质
    print("\n" + "=" * 50)
    print("阶乘的数学性质:")
    print("=" * 50)
    print("• 定义: n! = n × (n-1) × ... × 2 × 1")
    print("• 递推: n! = n × (n-1)!")
    print("• 0! = 1（空积的定义）")
    print("• 增长: 阶乘比指数增长更快")
    print("• 斯特林近似: n! ≈ √(2πn) × (n/e)^n")
    print("• 勒让德公式: n!中素数p的幂次 = Σ⌊n/p^k⌋")
    
    # 应用场景
    print("\n" + "=" * 50)
    print("应用场景:")
    print("=" * 50)
    print("• 排列组合: 计算可能性的总数")
    print("• 概率论: 生日问题、洗牌算法")
    print("• 泰勒级数: e^x = Σ x^n/n!")
    print("• 图论: 计算不同图的数量")
    print("• 信息论: 编码理论")
    print("• 数论: 威尔逊定理 (p-1)! ≡ -1 (mod p)")
    
    # Python特性
    print("\n" + "=" * 50)
    print("Python特性:")
    print("=" * 50)
    print("• 大整数支持: 自动处理任意精度整数")
    print("• 多种实现: 迭代、递归、reduce、math库")
    print("• 类型提示: 支持静态类型检查")
    print("• 函数式编程: map, filter, reduce支持")
    print("• 科学计算: 与NumPy、SciPy集成")


if __name__ == "__main__":
    test_factorial()
