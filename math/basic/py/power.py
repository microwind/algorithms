"""
数学基础 - 幂运算 (Power/Exponentiation)
计算基数的指数次幂
支持快速幂算法（二分幂）
时间复杂度: O(log n) - 快速幂，O(n) - 普通幂
"""

import math
from typing import Union


Numeric = Union[int, float]


def power_linear(base: Numeric, exp: int) -> float:
    """
    普通幂运算 - 线性算法
    
    算法原理：
    - 将基数乘以自身 n 次
    - result = base × base × ... × base (共n次)
    
    参数:
        base: 基数
        exp: 指数（非负整数）
    返回:
        base^exp 的结果
    
    时间复杂度: O(n) - 线性复杂度
    空间复杂度: O(1) - 常数空间
    """
    if exp < 0:
        raise ValueError("请使用power_with_negative支持负指数")
    if exp == 0:
        return 1.0
    
    result = 1.0
    base_float = float(base)
    
    for _ in range(exp):
        result *= base_float
    
    return result


def power_fast(base: Numeric, exp: int) -> float:
    """
    快速幂运算 - 二分算法（二进制分解）
    
    算法原理：
    - 利用指数的二进制表示
    - a^n = a^(2^k1) × a^(2^k2) × ... × a^(2^km)
    - 通过平方运算快速计算大指数
    
    示例: 2^13 = 2^8 × 2^4 × 2^1 = 8192
          13 = 1101₂
    
    参数:
        base: 基数
        exp: 指数（非负整数）
    返回:
        base^exp 的结果
    
    时间复杂度: O(log n) - 对数复杂度
    空间复杂度: O(1) - 常数空间
    """
    if exp < 0:
        raise ValueError("请使用power_with_negative支持负指数")
    if exp == 0:
        return 1.0
    
    result = 1.0
    base_float = float(base)
    remaining_exp = exp
    current_power = base_float
    
    # 二进制分解计算幂
    while remaining_exp > 0:
        # 如果当前二进制位为1，乘以对应的幂
        if remaining_exp & 1:
            result *= current_power
        
        # 计算下一个平方幂
        current_power *= current_power
        remaining_exp >>= 1
    
    return result


def power_with_negative(base: Numeric, exp: int) -> float:
    """
    支持负指数的幂运算
    
    a^(-n) = 1 / a^n
    """
    if exp >= 0:
        return power_fast(base, exp)
    else:
        return 1.0 / power_fast(base, -exp)


def power_int(base: int, exp: int) -> int:
    """
    整数幂运算（返回整数结果）
    
    参数:
        base: 整数基数
        exp: 指数（非负整数）
    返回:
        base^exp 的整数结果
    注意:
        可能溢出，结果需验证
    """
    if exp < 0:
        raise ValueError("整数幂不支持负指数")
    if exp == 0:
        return 1
    
    result = 1
    current_base = base
    remaining_exp = exp
    
    # 快速幂算法
    while remaining_exp > 0:
        if remaining_exp & 1:
            result *= current_base
        remaining_exp >>= 1
        if remaining_exp > 0:
            current_base *= current_base
    
    return result


def power_mod(base: int, exp: int, mod: int) -> int:
    """
    模幂运算（Modular Exponentiation）
    
    计算 (base^exp) % mod
    
    应用：
    - RSA加密算法
    - 大数幂运算的低位计算
    - 防止整数溢出
    
    时间复杂度: O(log exp)
    空间复杂度: O(1)
    """
    if mod == 1:
        return 0
    if exp < 0:
        raise ValueError("模幂运算不支持负指数")
    
    result = 1 % mod
    base = base % mod
    remaining_exp = exp
    
    while remaining_exp > 0:
        if remaining_exp & 1:
            result = (result * base) % mod
        base = (base * base) % mod
        remaining_exp >>= 1
    
    return result


def nth_root(n: Numeric, x: Numeric, epsilon: float = 1e-10) -> float:
    """
    计算n次方根（牛顿迭代法）
    
    求解: y^n = x，即 y = x^(1/n)
    
    牛顿迭代公式:
    y_{k+1} = ((n-1)*y_k + x/y_k^(n-1)) / n
    
    参数:
        n: 根的次数
        x: 被开方数
        epsilon: 精度要求
    返回:
        x的n次方根
    """
    if x < 0 and n % 2 == 0:
        raise ValueError("偶次根不能取负数")
    if x == 0:
        return 0.0
    
    n_float = float(n)
    x_float = float(x)
    
    # 初始猜测
    y = x_float / n_float if x_float > 1 else 1.0
    
    while True:
        # 牛顿迭代
        y_next = ((n_float - 1) * y + x_float / power_fast(y, int(n) - 1)) / n_float
        
        if abs(y_next - y) < epsilon:
            return y_next
        
        y = y_next


def log_power(base: Numeric, result: Numeric) -> float:
    """
    计算对数: 找到指数x使得 base^x = result
    
    即: x = log_base(result)
    
    使用换底公式: log_a(b) = ln(b) / ln(a)
    """
    if base <= 0 or base == 1:
        raise ValueError("底数必须大于0且不等于1")
    if result <= 0:
        raise ValueError("真数必须大于0")
    
    return math.log(result) / math.log(base)


def is_power_of_two(n: int) -> bool:
    """
    判断是否为2的幂
    
    技巧: n & (n-1) == 0 当且仅当n是2的幂
    """
    return n > 0 and (n & (n - 1)) == 0


def is_perfect_power(n: int) -> tuple:
    """
    判断是否为完全幂
    
    即是否存在 a, b > 1 使得 a^b = n
    
    返回: (a, b) 或 None
    """
    if n < 4:
        return None
    
    max_exp = int(math.log2(n)) + 1
    
    for b in range(2, max_exp + 1):
        a = round(n ** (1.0 / b))
        if a > 1 and a ** b == n:
            return (a, b)
    
    return None


def test_power():
    """测试函数"""
    print("=" * 60)
    print("    幂运算演示 (Power/Exponentiation)")
    print("=" * 60)
    print()
    
    # 基本幂运算测试
    print("基本幂运算测试:")
    print("-" * 60)
    test_cases = [
        (2, 10),
        (3, 5),
        (5, 3),
        (10, 0),
        (2.5, 4),
    ]
    
    for base, exp in test_cases:
        linear = power_linear(base, exp)
        fast = power_fast(base, exp)
        builtin = base ** exp
        print(f"{base}^{exp} = {fast:.6f} (线性:{linear:.6f}, 内置:{builtin:.6f})")
    
    # 负指数
    print("\n" + "=" * 60)
    print("负指数测试:")
    print("=" * 60)
    for base, exp in [(2, -3), (10, -2), (5, -1)]:
        result = power_with_negative(base, exp)
        print(f"{base}^{exp} = {result:.6f}")
    
    # 整数幂
    print("\n" + "=" * 60)
    print("整数幂测试:")
    print("=" * 60)
    for base, exp in [(2, 20), (3, 10), (5, 8), (10, 6)]:
        result = power_int(base, exp)
        print(f"{base}^{exp} = {result}")
    
    # 模幂运算
    print("\n" + "=" * 60)
    print("模幂运算 (用于RSA加密):")
    print("=" * 60)
    print("计算 7^256 mod 13:")
    result = power_mod(7, 256, 13)
    print(f"7^256 mod 13 = {result}")
    print(f"验证: {pow(7, 256, 13)}")
    
    print("\n计算大数模幂:")
    for exp in [10, 100, 1000, 10000]:
        result = power_mod(3, exp, 1000)
        print(f"3^{exp} mod 1000 = {result:03d}")
    
    # n次方根
    print("\n" + "=" * 60)
    print("n次方根测试:")
    print("=" * 60)
    root_tests = [
        (2, 16),   # √16 = 4
        (3, 27),   # ³√27 = 3
        (4, 81),   # ⁴√81 = 3
        (5, 32),   # ⁵√32 = 2
        (2, 2),    # √2 ≈ 1.414
    ]
    
    for n, x in root_tests:
        root = nth_root(n, x)
        print(f"{n}√{x} = {root:.6f}")
    
    # 2的幂判断
    print("\n" + "=" * 60)
    print("2的幂判断:")
    print("=" * 60)
    test_numbers = [1, 2, 3, 4, 8, 15, 16, 32, 64, 100, 1024, 2048]
    for n in test_numbers:
        result = "是" if is_power_of_two(n) else "不是"
        print(f"{n:6d} {result}2的幂")
    
    # 完全幂判断
    print("\n" + "=" * 60)
    print("完全幂判断:")
    print("=" * 60)
    perfect_tests = [4, 8, 9, 16, 27, 32, 36, 64, 100, 125, 216, 1000]
    for n in perfect_tests:
        result = is_perfect_power(n)
        if result:
            a, b = result
            print(f"{n} = {a}^{b}")
        else:
            print(f"{n} 不是完全幂")
    
    # 性能比较
    print("\n" + "=" * 60)
    print("算法复杂度分析:")
    print("=" * 60)
    print("普通幂算法:")
    print("  原理: 连乘法")
    print("  复杂度: O(n) 时间")
    print()
    print("快速幂算法:")
    print("  原理: 二进制分解，a^n = ∏ a^(2^ki)")
    print("  复杂度: O(log n) 时间")
    print("  优势: 大指数计算效率高")
    
    # 数学性质
    print("\n" + "=" * 60)
    print("幂运算数学性质:")
    print("=" * 60)
    print("• 同底数幂相乘: a^m × a^n = a^(m+n)")
    print("• 幂的乘方:    (a^m)^n = a^(m×n)")
    print("• 积的乘方:    (a×b)^n = a^n × b^n")
    print("• 商的乘方:    (a/b)^n = a^n / b^n")
    print("• 任何数的0次方: a^0 = 1 (a ≠ 0)")
    print("• 负指数:      a^(-n) = 1/a^n")
    
    # 应用场景
    print("\n" + "=" * 60)
    print("应用场景:")
    print("=" * 60)
    print("• 复利计算: 本金 × (1+利率)^年数")
    print("• 人口增长: 初始人口 × 增长率^年数")
    print("• 二进制转换: 2^n 表示二进制位数")
    print("• 密码学: 大数幂运算（RSA加密）")
    print("• 物理公式: 动能 = ½mv²")
    print("• 面积体积: 正方形面积 a²，立方体体积 a³")


if __name__ == "__main__":
    test_power()
