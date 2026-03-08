"""
字符串算法 - Boyer-Moore 模式匹配
使用坏字符规则和好后缀规则实现高效匹配
最坏O(mn)，平均O(n/m)
"""


def bad_char_heuristic(pattern):
    """
    构建坏字符规则表
    记录每个字符在模式串中最右出现的位置
    """
    bad_char = {}
    for i, char in enumerate(pattern):
        bad_char[char] = i
    return bad_char


def boyer_moore_search(text, pattern):
    """
    Boyer-Moore字符串匹配算法
    从右向左比较，利用坏字符规则快速跳过
    
    参数:
        text: 主文本
        pattern: 模式串
    返回:
        匹配位置的列表
    """
    m = len(pattern)
    n = len(text)
    
    if m > n:
        return []
    
    # 构建坏字符规则表
    bad_char = bad_char_heuristic(pattern)
    matches = []
    
    s = 0  # 模式串在文本中的位移
    while s <= n - m:
        j = m - 1  # 从模式串末尾开始比较
        
        # 从右向左比较
        while j >= 0 and pattern[j] == text[s + j]:
            j -= 1
        
        if j < 0:
            # 找到匹配
            matches.append(s)
            # 移动模式串（使用坏字符规则）
            s += (m - bad_char.get(text[s + m], -1)) if s + m < n else 1
        else:
            # 不匹配，使用坏字符规则计算位移
            bad_char_shift = bad_char.get(text[s + j], -1)
            s += max(1, j - bad_char_shift)
    
    return matches


# 测试示例
if __name__ == "__main__":
    print("=" * 50)
    print("Boyer-Moore 模式匹配")
    print("=" * 50)
    
    text = "ABAAABCDABCABCABCAB"
    pattern = "ABC"
    
    print(f"\n文本: {text}")
    print(f"模式: {pattern}")
    
    matches = boyer_moore_search(text, pattern)
    print(f"\n匹配位置: {matches}")
    
    print("\n算法特点:")
    print("  • 从右向左比较")
    print("  • 坏字符规则：跳过不可能匹配的位置")
    print("  • 好后缀规则：利用已匹配后缀")
    print("  • 适合大字母表（如英文文本）")
    print("  • 实际应用中通常最快")
