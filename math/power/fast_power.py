"""
数学算法 - 快速幂 (Fast Power / Binary Exponentiation)
使用二分法高效计算大数幂，时间复杂度 O(log n)
"""


def fast_power(base, exponent, mod=None):
    """
    快速幂算法
    计算 base^exponent，可选取模
    
    时间复杂度: O(log exponent)
    空间复杂度: O(1)
    """
    result = 1
    base = base % mod if mod else base
    
    while exponent > 0:
        # 如果指数是奇数，乘以当前底数
        if exponent % 2 == 1:
            result = (result * base) % mod if mod else result * base
        
        # 底数平方
        base = (base * base) % mod if mod else base * base
        
        # 指数减半
        exponent //= 2
    
    return result


def fast_power_recursive(base, exponent, mod=None):
    """
    快速幂 - 递归实现
    base^exponent = (base^(exponent/2))^2  如果exponent是偶数
    base^exponent = base * base^(exponent-1) 如果exponent是奇数
    """
    # 基础情况
    if exponent == 0:
        return 1
    if exponent == 1:
        return base % mod if mod else base
    
    # 递归计算
    half = fast_power_recursive(base, exponent // 2, mod)
    half = half % mod if mod else half
    
    if exponent % 2 == 0:
        # 偶数: (base^(n/2))^2
        return (half * half) % mod if mod else half * half
    else:
        # 奇数: base * (base^((n-1)/2))^2
        result = (half * half) % mod if mod else half * half
        return (result * base) % mod if mod else result * base


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("快速幂算法 (Fast Power)")
    print("=" * 50)
    
    test_cases = [
        (2, 10),
        (3, 5),
        (5, 3),
        (10, 6),
    ]
    
    print("\n快速幂计算:")
    for base, exp in test_cases:
        result = fast_power(base, exp)
        verify = base ** exp
        print(f"  {base}^{exp} = {result} (验证: {verify})")
    
    # 大数取模
    print("\n大数幂取模 (模 1000000007):")
    print(f"  2^100 mod 1e9+7 = {fast_power(2, 100, 1000000007)}")
    print(f"  10^18 mod 1e9+7 = {fast_power(10, 18, 1000000007)}")
    
    print("\n与普通循环对比:")
    print("  普通: O(n) - 需要n次乘法")
    print("  快速幂: O(log n) - 只需要log n次乘法")
