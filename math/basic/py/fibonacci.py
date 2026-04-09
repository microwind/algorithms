"""
数学基础 - 斐波那契数列 (Fibonacci Sequence)
计算斐波那契数列的第n项
支持递归、迭代、矩阵快速幂和通项公式
时间复杂度: O(2^n) - 朴素递归, O(n) - 迭代, O(log n) - 矩阵快速幂
"""

import math
from typing import List, Tuple
from functools import lru_cache


def fibonacci_recursive(n: int) -> int:
    """
    朴素递归计算斐波那契数
    
    时间复杂度: O(2^n) - 指数级，存在大量重复计算
    空间复杂度: O(n) - 递归栈深度
    
    仅适用于小n（n ≤ 30）
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n <= 1:
        return n
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)


def fibonacci_memoization(n: int, memo: dict = None) -> int:
    """
    记忆化递归（Memoization）
    
    用字典存储已计算的结果，避免重复计算
    
    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    if n < 0:
        raise ValueError("n必须非负")
    if memo is None:
        memo = {}
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    
    memo[n] = fibonacci_memoization(n - 1, memo) + fibonacci_memoization(n - 2, memo)
    return memo[n]


@lru_cache(maxsize=None)
def fibonacci_lru(n: int) -> int:
    """
    使用functools.lru_cache的记忆化递归
    
    Python内置的缓存装饰器
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n <= 1:
        return n
    return fibonacci_lru(n - 1) + fibonacci_lru(n - 2)


def fibonacci_iterative(n: int) -> int:
    """
    迭代计算斐波那契数
    
    自底向上计算，保存前两个值
    
    时间复杂度: O(n)
    空间复杂度: O(1) - 只使用常数空间
    
    适用于: n ≤ 92 (受限于64位整数)
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n <= 1:
        return n
    
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b


def fibonacci_generator(limit: int = None):
    """
    斐波那契数列生成器
    
    使用yield实现无限序列的惰性求值
    
    示例:
        for i, fib in zip(range(10), fibonacci_generator()):
            print(f"F({i}) = {fib}")
    """
    a, b = 0, 1
    count = 0
    while limit is None or count < limit:
        yield a
        a, b = b, a + b
        count += 1


def fibonacci_list(n: int) -> List[int]:
    """
    获取前n个斐波那契数
    """
    return list(fibonacci_generator(n))


def fibonacci_matrix(n: int) -> int:
    """
    矩阵快速幂算法
    
    利用矩阵乘法：
    | F(n+1)  F(n)   |   | 1  1 | ^n
    | F(n)    F(n-1) | = | 1  0 |
    
    时间复杂度: O(log n)
    空间复杂度: O(1)
    
    适用于大n计算
    """
    if n < 0:
        raise ValueError("n必须非负")
    if n <= 1:
        return n
    
    def matrix_multiply(A: List[List[int]], B: List[List[int]]) -> List[List[int]]:
        """2x2矩阵乘法"""
        return [
            [A[0][0]*B[0][0] + A[0][1]*B[1][0], A[0][0]*B[0][1] + A[0][1]*B[1][1]],
            [A[1][0]*B[0][0] + A[1][1]*B[1][0], A[1][0]*B[0][1] + A[1][1]*B[1][1]]
        ]
    
    def matrix_power(M: List[List[int]], n: int) -> List[List[int]]:
        """矩阵快速幂"""
        if n == 1:
            return M
        if n % 2 == 0:
            half = matrix_power(M, n // 2)
            return matrix_multiply(half, half)
        else:
            return matrix_multiply(M, matrix_power(M, n - 1))
    
    M = [[1, 1], [1, 0]]
    result = matrix_power(M, n - 1)
    return result[0][0]


def fibonacci_formula(n: int) -> float:
    """
    通项公式（比内公式）
    
    F(n) = (φ^n - ψ^n) / √5
    其中 φ = (1+√5)/2 ≈ 1.618（黄金比例）
         ψ = (1-√5)/2 ≈ -0.618
    
    由于浮点精度限制，仅适用于小n
    
    时间复杂度: O(1)
    """
    if n < 0:
        raise ValueError("n必须非负")
    
    sqrt5 = math.sqrt(5)
    phi = (1 + sqrt5) / 2  # 黄金比例
    psi = (1 - sqrt5) / 2
    
    return (phi**n - psi**n) / sqrt5


def fibonacci_mod(n: int, mod: int) -> int:
    """
    计算F(n) mod m
    
    应用：
    - 计算大斐波那契数的低位数字
    - 周期性检测（皮萨诺周期）
    """
    if n < 0:
        raise ValueError("n必须非负")
    if mod == 1:
        return 0
    if n <= 1:
        return n % mod
    
    a, b = 0 % mod, 1 % mod
    for _ in range(2, n + 1):
        a, b = b, (a + b) % mod
    return b


def pisano_period(mod: int) -> int:
    """
    计算皮萨诺周期
    
    斐波那契数列模m的周期
    """
    if mod == 1:
        return 1
    
    a, b = 0, 1
    period = 0
    
    while True:
        a, b = b, (a + b) % mod
        period += 1
        if a == 0 and b == 1:
            return period


def fibonacci_ratio(n: int) -> float:
    """
    计算相邻两项的比值 F(n)/F(n-1)
    
    当n→∞时，比值趋近黄金比例φ
    """
    if n <= 1:
        raise ValueError("n必须大于1")
    return fibonacci_iterative(n) / fibonacci_iterative(n - 1)


def sum_of_fibonacci(n: int) -> int:
    """
    计算前n项和
    
    公式: ΣF(i) [i=0 to n] = F(n+2) - 1
    """
    return fibonacci_iterative(n + 2) - 1


def sum_of_squares(n: int) -> int:
    """
    计算前n项平方和
    
    公式: ΣF(i)² [i=0 to n] = F(n) × F(n+1)
    """
    return fibonacci_iterative(n) * fibonacci_iterative(n + 1)


def test_fibonacci():
    """测试函数"""
    print("=" * 60)
    print("    斐波那契数列 (Fibonacci Sequence)")
    print("=" * 60)
    print()
    
    # 前20项
    print("斐波那契数列前20项:")
    print("-" * 60)
    fibs = fibonacci_list(20)
    for i, fib in enumerate(fibs):
        print(f"F({i:2d}) = {fib:8d}", end="  ")
        if (i + 1) % 3 == 0:
            print()
    
    # 黄金比例近似
    print("\n" + "=" * 60)
    print("黄金比例近似:")
    print("=" * 60)
    phi = (1 + math.sqrt(5)) / 2
    for i in range(2, 16):
        ratio = fibonacci_ratio(i)
        error = abs(ratio - phi) / phi * 100
        print(f"F({i})/F({i-1}) = {ratio:.10f}  (误差: {error:.6f}%)")
    print(f"真实黄金比例 φ = {phi:.10f}")
    
    # 大数计算（矩阵快速幂）
    print("\n" + "=" * 60)
    print("大数计算（矩阵快速幂）:")
    print("=" * 60)
    for n in [50, 100, 200]:
        fib_n = fibonacci_matrix(n)
        digits = len(str(fib_n))
        print(f"F({n}) 的位数: {digits}")
    
    # F(100)的前50位
    fib_100 = fibonacci_matrix(100)
    fib_str = str(fib_100)
    print(f"\nF(100) = {fib_str[:50]}...{fib_str[-20:]}")
    
    # 模运算
    print("\n" + "=" * 60)
    print("斐波那契数模1000（后3位）:")
    print("=" * 60)
    for n in [10, 50, 100, 500, 1000]:
        last_3 = fibonacci_mod(n, 1000)
        print(f"F({n}) mod 1000 = {last_3:03d}")
    
    # 皮萨诺周期
    print("\n" + "=" * 60)
    print("皮萨诺周期（模m的周期）:")
    print("=" * 60)
    for m in [2, 3, 5, 10, 100]:
        period = pisano_period(m)
        print(f"π({m}) = {period}")
    
    # 数学性质
    print("\n" + "=" * 60)
    print("数学性质:")
    print("=" * 60)
    print("• 定义: F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)")
    print("• 黄金比例: lim F(n+1)/F(n) = φ = (1+√5)/2 ≈ 1.618")
    print("• 求和性质: ΣF(i) [i=0 to n] = F(n+2) - 1")
    print(f"  验证: ΣF(0..9) = {sum_of_fibonacci(9)}, F(11)-1 = {fibonacci_iterative(11) - 1}")
    print("• 平方和: ΣF(i)² [i=0 to n] = F(n) × F(n+1)")
    print(f"  验证: ΣF²(0..9) = {sum_of_squares(9)}, F(9)×F(10) = {fibonacci_iterative(9) * fibonacci_iterative(10)}")
    print("• 卡西尼恒等式: F(n-1)×F(n+1) - F(n)² = (-1)^n")
    print("• 组合公式: F(n) = C(n-1,0) + C(n-2,1) + C(n-3,2) + ...")
    
    # 应用场景
    print("\n" + "=" * 60)
    print("应用场景:")
    print("=" * 60)
    print("• 自然界: 向日葵种子排列、鹦鹉螺壳螺旋")
    print("• 艺术设计: 黄金分割、构图比例")
    print("• 金融分析: 斐波那契回撤、技术分析")
    print("• 算法分析: AVL树的最少节点数")
    print("• 数据结构: 斐波那契堆")
    print("• 生物数学: 兔子繁殖模型")


if __name__ == "__main__":
    test_fibonacci()
