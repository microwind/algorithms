"""
数学算法 - 扩展欧几里得算法
计算GCD的同时，找到满足 ax + by = gcd(a,b) 的x和y
"""


def extended_gcd(a, b):
    """
    扩展欧几里得算法
    返回 (gcd, x, y) 使得 ax + by = gcd(a, b)
    
    应用:
    - 求解模逆元
    - 求解线性丢番图方程
    - RSA加密算法
    """
    if b == 0:
        return (a, 1, 0)
    
    gcd, x1, y1 = extended_gcd(b, a % b)
    
    # 回代
    x = y1
    y = x1 - (a // b) * y1
    
    return (gcd, x, y)


def mod_inverse(a, m):
    """
    计算a关于模m的乘法逆元
    即找到x使得 (a * x) % m = 1
    当且仅当gcd(a, m) = 1时存在逆元
    """
    gcd, x, _ = extended_gcd(a, m)
    
    if gcd != 1:
        return None  # 逆元不存在
    
    # 确保结果为正数
    return (x % m + m) % m


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("扩展欧几里得算法 (Extended GCD)")
    print("=" * 50)
    
    test_cases = [
        (30, 12),
        (35, 15),
        (7, 5),
        (17, 3120),  # RSA中的典型用例
    ]
    
    print("\n扩展GCD计算:")
    for a, b in test_cases:
        gcd, x, y = extended_gcd(a, b)
        print(f"\n  gcd({a}, {b}) = {gcd}")
        print(f"  {a}×({x}) + {b}×({y}) = {a*x + b*y}")
    
    print("\n模逆元计算:")
    inverse_cases = [
        (3, 11),
        (7, 26),
        (17, 3120),
    ]
    
    for a, m in inverse_cases:
        inv = mod_inverse(a, m)
        if inv:
            print(f"  {a}^(-1) mod {m} = {inv}")
            print(f"  验证: {a} × {inv} = {a * inv} ≡ {(a * inv) % m} (mod {m})")
        else:
            print(f"  {a} 关于模 {m} 的逆元不存在")
