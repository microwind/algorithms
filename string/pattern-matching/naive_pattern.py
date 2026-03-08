"""
字符串算法 - 朴素模式匹配 (Naive Pattern Matching)
逐个字符比较，时间复杂度 O(m*n)
"""


def naive_search(text, pattern):
    """
    朴素字符串匹配算法
    逐个位置比较文本和模式串
    
    参数:
        text: 主文本字符串
        pattern: 要查找的模式串
    返回:
        所有匹配位置的列表
    """
    n = len(text)
    m = len(pattern)
    matches = []
    
    # 遍历文本的每个可能位置
    for i in range(n - m + 1):
        # 比较从位置i开始的m个字符
        match = True
        for j in range(m):
            if text[i + j] != pattern[j]:
                match = False
                break
        
        if match:
            matches.append(i)
    
    return matches


def naive_search_count(text, pattern):
    """统计匹配次数"""
    return len(naive_search(text, pattern))


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("朴素模式匹配 (Naive Pattern Matching)")
    print("=" * 50)
    
    text = "ABABDABACDABABCABAB"
    pattern = "ABABCABAB"
    
    print(f"\n文本: {text}")
    print(f"模式: {pattern}")
    
    matches = naive_search(text, pattern)
    print(f"\n匹配位置: {matches}")
    
    if matches:
        print("\n匹配可视化:")
        for pos in matches:
            print(f"  位置 {pos}: {text}")
            print(f"           {' ' * pos}{pattern}")
    
    print("\n复杂度分析:")
    print("  时间复杂度: O(m × n)")
    print("  空间复杂度: O(1)")
    print("  m = 模式串长度, n = 文本长度")
