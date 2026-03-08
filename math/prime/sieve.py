"""
数学算法 - 素数筛 (Sieve of Eratosthenes)
高效找出一定范围内的所有素数
"""


def sieve_of_eratosthenes(n):
    """
    埃拉托斯特尼筛法
    找出2到n之间的所有素数
    
    时间复杂度: O(n log log n)
    空间复杂度: O(n)
    """
    # 初始化：假设所有数都是素数
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    
    # 筛法：从2开始，将每个素数的倍数标记为合数
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            # 从i*i开始标记，因为更小的倍数已经被之前的素数标记过了
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    
    # 收集所有素数
    primes = [i for i in range(2, n + 1) if is_prime[i]]
    return primes


def count_primes(n):
    """计算小于n的素数个数"""
    primes = sieve_of_eratosthenes(n - 1)
    return len(primes)


def is_prime(n):
    """判断单个数是否为素数（简单方法）"""
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(n**0.5) + 1, 2):
        if n % i == 0:
            return False
    return True


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("素数筛 (Sieve of Eratosthenes)")
    print("=" * 50)
    
    # 找出100以内的素数
    primes = sieve_of_eratosthenes(100)
    print(f"\n100以内的素数 ({len(primes)}个):")
    print(" ".join(map(str, primes)))
    
    # 计算更大范围的素数数量
    ranges = [100, 1000, 10000]
    print("\n不同范围的素数数量:")
    for r in ranges:
        count = count_primes(r)
        print(f"  小于 {r}: {count} 个素数")
    
    # 验证
    print("\n验证单个数字:")
    test_numbers = [17, 25, 97, 100]
    for num in test_numbers:
        result = "素数" if is_prime(num) else "合数"
        print(f"  {num}: {result}")
