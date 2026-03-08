"""
字符串算法 - Rabin-Karp 模式匹配
使用滚动哈希实现高效的字符串匹配
平均时间复杂度 O(m+n)
"""


def rabin_karp_search(text, pattern, prime=101):
    """
    Rabin-Karp字符串匹配算法
    使用哈希值快速筛选可能的匹配位置
    
    参数:
        text: 主文本
        pattern: 模式串
        prime: 用于取模的素数
    返回:
        匹配位置的列表
    """
    d = 256  # 字符集大小
    n = len(text)
    m = len(pattern)
    
    if m > n:
        return []
    
    pattern_hash = 0
    text_hash = 0
    h = 1
    matches = []
    
    # 计算 h = d^(m-1) % prime
    for _ in range(m - 1):
        h = (h * d) % prime
    
    # 计算模式串和文本第一个窗口的哈希值
    for i in range(m):
        pattern_hash = (d * pattern_hash + ord(pattern[i])) % prime
        text_hash = (d * text_hash + ord(text[i])) % prime
    
    # 滑动窗口
    for i in range(n - m + 1):
        # 哈希值匹配，需要逐个字符验证
        if pattern_hash == text_hash:
            match = True
            for j in range(m):
                if text[i + j] != pattern[j]:
                    match = False
                    break
            if match:
                matches.append(i)
        
        # 计算下一个窗口的哈希值
        if i < n - m:
            text_hash = (d * (text_hash - ord(text[i]) * h) + ord(text[i + m])) % prime
            if text_hash < 0:
                text_hash += prime
    
    return matches


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("Rabin-Karp 模式匹配")
    print("=" * 50)
    
    text = "ABABDABACDABABCABAB"
    pattern = "ABABCABAB"
    
    print(f"\n文本: {text}")
    print(f"模式: {pattern}")
    
    matches = rabin_karp_search(text, pattern)
    print(f"\n匹配位置: {matches}")
    
    print("\n算法特点:")
    print("  • 使用滚动哈希快速筛选")
    print("  • 哈希冲突时逐个字符验证")
    print("  • 适合多模式匹配场景")
    print("  • 平均时间复杂度: O(m + n)")
