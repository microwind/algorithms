"""
数学基础 - 素数判定与生成 (Prime Numbers)
判断素数并生成素数表
支持试除法和埃拉托斯特尼筛法
时间复杂度: O(√n) - 试除法, O(n log log n) - 筛法
"""

import math
from typing import List, Set


def is_prime_basic(n: int) -> bool:
    """
    试除法判断素数（基本版）
    
    算法原理：
    - 若 n 为合数，则必有一个小于等于 √n 的因子
    - 只需检查 2 到 √n 的整数
    
    参数:
        n: 正整数
    返回:
        True - 是素数, False - 不是素数
    
    时间复杂度: O(√n)
    空间复杂度: O(1)
    """
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    
    # 检查奇数因子
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    
    return True


def is_prime_optimized(n: int) -> bool:
    """
    优化的试除法判断素数
    
    进一步优化：
    - 检查 2 和 3
    - 然后检查形如 6k±1 的数（所有素数>3都符合此形式）
    
    时间复杂度: O(√n)（约比基本版快3倍）
    """
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    
    # 检查形如6k±1的数
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    
    return True


def is_prime_miller_rabin(n: int, k: int = 5) -> bool:
    """
    Miller-Rabin素性测试（概率算法）
    
    适合测试大数（>10^16），准确率很高（1 - 4^(-k)）
    
    参数:
        n: 待测试的数
        k: 测试轮数，准确率 1 - 4^(-k)
    返回:
        False - 一定是合数
        True - 可能是素数（概率取决于k）
    """
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False
    
    # 写成 n-1 = d * 2^r 的形式
    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2
    
    # 测试轮数
    import random
    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, d, n)
        
        if x == 1 or x == n - 1:
            continue
        
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    
    return True


def sieve_of_eratosthenes(limit: int) -> List[bool]:
    """
    埃拉托斯特尼筛法生成素数表
    
    算法原理：
    - 从2开始，将每个素数的倍数标记为合数
    - 剩余未标记的数即为素数
    
    参数:
        limit: 上限范围
    返回:
        布尔数组，is_prime[i]表示i是否为素数
    
    时间复杂度: O(n log log n)
    空间复杂度: O(n)
    """
    if limit < 2:
        return [False] * (limit + 1)
    
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False
    
    for p in range(2, int(math.sqrt(limit)) + 1):
        if is_prime[p]:
            # 标记所有p的倍数为合数
            for multiple in range(p * p, limit + 1, p):
                is_prime[multiple] = False
    
    return is_prime


def sieve_linear(n: int) -> List[int]:
    """
    线性筛法（欧拉筛）
    
    时间复杂度严格O(n)，每个合数只被标记一次
    
    返回:
        素数列表
    """
    if n < 2:
        return []
    
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    primes = []
    
    for i in range(2, n + 1):
        if is_prime[i]:
            primes.append(i)
        for p in primes:
            if i * p > n:
                break
            is_prime[i * p] = False
            if i % p == 0:  # 保证每个合数只被最小质因子筛除
                break
    
    return primes


def get_primes(limit: int) -> List[int]:
    """
    获取小于等于limit的所有素数
    """
    sieve = sieve_of_eratosthenes(limit)
    return [i for i, is_p in enumerate(sieve) if is_p]


def prime_factorization(n: int) -> List[int]:
    """
    素因数分解
    
    将n分解为素因数的乘积
    返回: 素因数列表（可能包含重复值）
    
    示例: 12 = [2, 2, 3]
    """
    if n < 2:
        return []
    
    factors = []
    d = 2
    while d * d <= n:
        while n % d == 0:
            factors.append(d)
            n //= d
        d += 1
    
    if n > 1:
        factors.append(n)
    
    return factors


def count_primes(n: int) -> int:
    """
    素数计数函数 π(n)
    
    计算小于等于n的素数个数
    """
    if n < 2:
        return 0
    sieve = sieve_of_eratosthenes(n)
    return sum(sieve)


def nth_prime(n: int) -> int:
    """
    获取第n个素数
    
    使用素数定理估算上界: p_n ≈ n * ln(n)
    """
    if n < 1:
        raise ValueError("n必须为正整数")
    
    # 估算上界（使用素数定理）
    if n < 6:
        limit = 15
    else:
        limit = int(n * (math.log(n) + math.log(math.log(n)))) + 10
    
    primes = get_primes(limit)
    return primes[n - 1]


def prime_gap_statistics(limit: int) -> dict:
    """
    素数间隙统计
    
    分析相邻素数之间的差值分布
    """
    primes = get_primes(limit)
    gaps = [primes[i+1] - primes[i] for i in range(len(primes) - 1)]
    
    if not gaps:
        return {"max_gap": 0, "avg_gap": 0, "gaps": []}
    
    return {
        "max_gap": max(gaps),
        "avg_gap": sum(gaps) / len(gaps),
        "gaps": gaps[:20]  # 前20个间隙
    }


def test_prime():
    """测试函数"""
    print("=" * 60)
    print("    素数判定与生成 (Prime Numbers)")
    print("=" * 60)
    print()
    
    # 100以内的素数
    print("100以内的素数:")
    print("-" * 60)
    primes_100 = get_primes(100)
    for i, p in enumerate(primes_100):
        print(f"{p:3d}", end=" ")
        if (i + 1) % 10 == 0:
            print()
    print(f"\n共 {len(primes_100)} 个素数")
    
    # 素数判定测试
    print("\n" + "=" * 60)
    print("素数判定测试:")
    print("=" * 60)
    test_numbers = [1, 2, 3, 4, 17, 18, 97, 100, 541, 1009, 10007]
    for n in test_numbers:
        result = "是素数" if is_prime_optimized(n) else "不是素数"
        print(f"{n:6d} {result}")
    
    # 大数测试（Miller-Rabin）
    print("\n" + "=" * 60)
    print("大数素性测试 (Miller-Rabin):")
    print("=" * 60)
    big_numbers = [10**9 + 7, 10**9 + 9, 982451653]
    for n in big_numbers:
        is_prime = is_prime_miller_rabin(n, k=10)
        print(f"{n:15d} {'可能是素数' if is_prime else '一定是合数'}")
    
    # 素因数分解
    print("\n" + "=" * 60)
    print("素因数分解:")
    print("=" * 60)
    numbers_to_factor = [12, 100, 360, 1001, 2024]
    for n in numbers_to_factor:
        factors = prime_factorization(n)
        factor_str = " × ".join(map(str, factors))
        print(f"{n:6d} = {factor_str}")
    
    # 第n个素数
    print("\n" + "=" * 60)
    print("第n个素数:")
    print("=" * 60)
    for n in [1, 10, 100, 1000, 10000]:
        p = nth_prime(n)
        print(f"第{n:6d}个素数是 {p}")
    
    # 素数计数
    print("\n" + "=" * 60)
    print("素数计数 π(n):")
    print("=" * 60)
    for n in [10, 100, 1000, 10000, 100000]:
        count = count_primes(n)
        approx = n / math.log(n)  # 素数定理近似
        error = abs(count - approx) / count * 100
        print(f"π({n:6d}) = {count:6d} (近似: {approx:.1f}, 误差: {error:.2f}%)")
    
    # 素数间隙
    print("\n" + "=" * 60)
    print("素数间隙统计 (n < 1000):")
    print("=" * 60)
    stats = prime_gap_statistics(1000)
    print(f"最大间隙: {stats['max_gap']}")
    print(f"平均间隙: {stats['avg_gap']:.2f}")
    
    # 数学性质
    print("\n" + "=" * 60)
    print("素数的数学性质:")
    print("=" * 60)
    print("• 定义: 大于1的自然数，只有1和自身两个因子")
    print("• 素数定理: π(n) ~ n/ln(n)")
    print("• 欧几里得定理: 素数有无穷多个")
    print("• 孪生素数猜想: 存在无穷多对相差2的素数")
    print("• 哥德巴赫猜想: 大于2的偶数可表示为两素数之和")
    print("• 唯一分解定理: 每个整数可唯一表示为素数乘积")
    
    # 应用场景
    print("\n" + "=" * 60)
    print("应用场景:")
    print("=" * 60)
    print("• 密码学: RSA加密基于大素数分解")
    print("• 哈希表: 素数大小的表减少冲突")
    print("• 随机数生成: 梅森旋转算法")
    print("• 校验和: ISBN、信用卡号码验证")
    print("• 数论研究: 黎曼猜想、哥德巴赫猜想")
    print("• 编码理论: 纠错码设计")


if __name__ == "__main__":
    test_prime()
