"""
数学基础 - 最大公约数与最小公倍数 (GCD and LCM)
使用欧几里得算法计算两个整数的最大公约数
时间复杂度: O(log min(a,b))
"""

import math
from typing import Tuple, List


def gcd_euclidean(a: int, b: int) -> int:
    """
    欧几里得算法（辗转相除法）- 递归版
    
    算法原理：
    - gcd(a, b) = gcd(b, a mod b)
    - 基准条件: gcd(a, 0) = a
    
    数学定理：
    对于任意整数 a, b (b ≠ 0)，有 gcd(a, b) = gcd(b, a % b)
    
    参数:
        a, b: 两个整数（可为0）
    返回:
        a 和 b 的最大公约数
    
    时间复杂度: O(log min(a,b))
    空间复杂度: O(log min(a,b)) - 递归栈
    """
    a, b = abs(a), abs(b)
    
    # 基准条件
    if b == 0:
        return a
    
    # 递归步骤
    return gcd_euclidean(b, a % b)


def gcd_iterative(a: int, b: int) -> int:
    """
    欧几里得算法 - 迭代版
    
    参数:
        a, b: 两个整数
    返回:
        a 和 b 的最大公约数
    
    时间复杂度: O(log min(a,b))
    空间复杂度: O(1)
    """
    a, b = abs(a), abs(b)
    
    # 循环直到余数为0
    while b != 0:
        a, b = b, a % b
    
    return a


def gcd_binary(a: int, b: int) -> int:
    """
    二进制GCD算法（Stein算法）
    
    优点：
    - 只使用移位和减法，避免除法运算
    - 在某些情况下比欧几里得算法更快
    
    算法步骤：
    1. 如果都是偶数，gcd(a,b) = 2 × gcd(a/2, b/2)
    2. 如果一个是偶数，gcd(a,b) = gcd(a/2, b) 或 gcd(a, b/2)
    3. 如果都是奇数，gcd(a,b) = gcd(|a-b|/2, min(a,b))
    """
    if a == 0:
        return b
    if b == 0:
        return a
    
    a, b = abs(a), abs(b)
    
    # 找出公因数2的幂次
    shift = 0
    while ((a | b) & 1) == 0:
        a >>= 1
        b >>= 1
        shift += 1
    
    # 去除a的所有因数2
    while (a & 1) == 0:
        a >>= 1
    
    # 主循环
    while b != 0:
        # 去除b的所有因数2
        while (b & 1) == 0:
            b >>= 1
        
        # 确保a <= b
        if a > b:
            a, b = b, a
        
        b = b - a
    
    # 恢复公因数2
    return a << shift


def gcd_extended(a: int, b: int) -> Tuple[int, int, int]:
    """
    扩展欧几里得算法
    
    功能：
    找到整数 x, y 使得: ax + by = gcd(a, b)
    
    参数:
        a, b: 两个整数
    返回:
        (gcd, x, y) 其中 gcd = ax + by
    
    应用：
    - 求解同余方程
    - 计算模逆元
    - RSA算法
    """
    if b == 0:
        return (a, 1, 0) if a > 0 else (-a, -1, 0)
    
    gcd_val, x1, y1 = gcd_extended(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    
    return (gcd_val, x, y)


def lcm(a: int, b: int) -> int:
    """
    最小公倍数 (LCM)
    
    公式: lcm(a, b) = |a × b| / gcd(a, b)
    
    参数:
        a, b: 两个非零整数
    返回:
        a 和 b 的最小公倍数
    """
    if a == 0 or b == 0:
        return 0
    
    return abs(a * b) // gcd_iterative(a, b)


def lcm_multiple(*numbers: int) -> int:
    """
    多个数的最小公倍数
    """
    if not numbers:
        return 0
    
    result = numbers[0]
    for num in numbers[1:]:
        result = lcm(result, num)
    
    return result


def gcd_multiple(*numbers: int) -> int:
    """
    多个数的最大公约数
    """
    if not numbers:
        return 0
    
    result = numbers[0]
    for num in numbers[1:]:
        result = gcd_iterative(result, num)
    
    return result


def are_coprime(a: int, b: int) -> bool:
    """
    判断两个数是否互质（互素）
    
    两个数互质当且仅当它们的最大公约数为1
    """
    return gcd_iterative(a, b) == 1


def euler_totient(n: int) -> int:
    """
    欧拉函数 φ(n)
    
    计算小于等于n且与n互质的正整数的个数
    
    公式: φ(n) = n × ∏(1 - 1/p) 其中p是n的所有不同质因数
    """
    if n <= 0:
        return 0
    
    result = n
    temp = n
    
    # 遍历所有可能的质因数
    p = 2
    while p * p <= temp:
        if temp % p == 0:
            # p是质因数
            while temp % p == 0:
                temp //= p
            result -= result // p
        p += 1
    
    # 如果temp > 1，则temp是质因数
    if temp > 1:
        result -= result // temp
    
    return result


def test_gcd():
    """测试函数"""
    print("=" * 60)
    print("  最大公约数计算 (GCD) - 欧几里得算法")
    print("=" * 60)
    print()
    
    # 测试用例
    test_cases = [
        (48, 18),
        (56, 98),
        (100, 35),
        (101, 103),  # 互质
        (0, 5),
        (0, 0),
        (-24, 36),   # 负数
        (1000000, 999999),
    ]
    
    print("GCD测试:")
    print("-" * 60)
    for a, b in test_cases:
        gcd_rec = gcd_euclidean(a, b)
        gcd_iter = gcd_iterative(a, b)
        gcd_bin = gcd_binary(a, b)
        gcd_math = math.gcd(a, b)
        lcm_val = lcm(a, b)
        
        print(f"gcd({a}, {b}) = {gcd_iter} (递归:{gcd_rec}, 二进制:{gcd_bin}, 标准库:{gcd_math})")
        print(f"lcm({a}, {b}) = {lcm_val}")
        print()
    
    # 扩展欧几里得算法演示
    print("=" * 60)
    print("扩展欧几里得算法:")
    print("=" * 60)
    a, b = 240, 46
    gcd_val, x, y = gcd_extended(a, b)
    print(f"{a} × ({x}) + {b} × ({y}) = {gcd_val}")
    print(f"验证: {a * x} + {b * y} = {a * x + b * y}")
    
    # 多个数的GCD和LCM
    print("\n" + "=" * 60)
    print("多个数的GCD和LCM:")
    print("=" * 60)
    numbers = [12, 18, 24, 36]
    print(f"数字: {numbers}")
    print(f"gcd = {gcd_multiple(*numbers)}")
    print(f"lcm = {lcm_multiple(*numbers)}")
    
    # 互质判断
    print("\n" + "=" * 60)
    print("互质判断:")
    print("=" * 60)
    coprime_pairs = [(14, 15), (21, 28), (100, 99), (17, 19)]
    for a, b in coprime_pairs:
        result = "互质" if are_coprime(a, b) else "不互质"
        print(f"{a} 和 {b}: {result} (gcd={gcd_iterative(a, b)})")
    
    # 欧拉函数
    print("\n" + "=" * 60)
    print("欧拉函数 φ(n):")
    print("=" * 60)
    for n in range(1, 21):
        phi = euler_totient(n)
        print(f"φ({n:2d}) = {phi:2d}", end="  ")
        if n % 5 == 0:
            print()
    
    # 算法步骤演示
    print("\n" + "=" * 60)
    print("欧几里得算法步骤演示:")
    print("=" * 60)
    a, b = 1071, 462
    print(f"计算 gcd({a}, {b})")
    step = 1
    temp_a, temp_b = a, b
    while temp_b != 0:
        quotient = temp_a // temp_b
        remainder = temp_a % temp_b
        print(f"步骤 {step}: {temp_a} = {quotient} × {temp_b} + {remainder}")
        temp_a, temp_b = temp_b, remainder
        step += 1
    print(f"最终结果: gcd({a}, {b}) = {temp_a}")
    
    # 数学性质
    print("\n" + "=" * 60)
    print("数学性质:")
    print("=" * 60)
    print("• 交换律: gcd(a, b) = gcd(b, a)")
    print("• 结合律: gcd(a, gcd(b, c)) = gcd(gcd(a, b), c)")
    print("• 分配律: gcd(a, b) × lcm(a, b) = |a × b|")
    print("• gcd(a, 0) = |a|")
    print("• gcd(a, 1) = 1")
    print("• 贝祖定理: 存在整数x,y使得 ax + by = gcd(a,b)")
    print("• 线性组合: gcd是所有线性组合ax+by中的最小正整数")
    
    # 应用场景
    print("\n" + "=" * 60)
    print("应用场景:")
    print("=" * 60)
    print("• 分数约分: 分子分母同除以gcd")
    print("• 密码学: RSA算法中的密钥生成")
    print("• 数论: 同余方程求解、模逆元计算")
    print("• 音乐理论: 计算和谐音程")
    print("• 计算机图形: 简化比例、像素对齐")
    print("• 调度算法: 计算任务周期")
    print("• 错误检测: 校验和算法")
    
    # Python特性
    print("\n" + "=" * 60)
    print("Python特性:")
    print("=" * 60)
    print("• math.gcd: 标准库内置GCD函数（Python 3.5+）")
    print("• math.lcm: 标准库内置LCM函数（Python 3.9+）")
    print("• 类型提示: 支持静态类型检查")
    print("• 大整数: 自动支持任意精度整数")
    print("• 函数式编程: 支持高阶函数和lambda")


if __name__ == "__main__":
    test_gcd()
