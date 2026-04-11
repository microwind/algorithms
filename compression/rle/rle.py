"""
*
 * 游程编码 (RLE) - 简单的压缩算法
 *
 * 问题：将连续重复的字符压缩为字符+计数的形式
 *
 * 核心思想：
 * - 统计连续相同字符的数量
 * - 用字符+计数表示重复序列
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
"""

def compress(text: str) -> str:
    """
    压缩函数

    Args:
        text: 输入文本

    Returns:
        压缩后的文本
    """
    if not text:
        return text

    compressed = []
    current_char = text[0]
    count = 1

    for i in range(1, len(text)):
        if text[i] == current_char:
            count += 1
        else:
            compressed.append(current_char)
            if count > 1:
                compressed.append(str(count))
            current_char = text[i]
            count = 1

    # 处理最后一个字符
    compressed.append(current_char)
    if count > 1:
        compressed.append(str(count))

    return ''.join(compressed)


def decompress(compressed: str) -> str:
    """
    解压函数

    Args:
        compressed: 压缩后的文本

    Returns:
        解压后的文本
    """
    if not compressed:
        return compressed

    decompressed = []
    i = 0

    while i < len(compressed):
        current_char = compressed[i]
        i += 1
        count_str = ""

        # 解析数字
        while i < len(compressed) and compressed[i].isdigit():
            count_str += compressed[i]
            i += 1

        count = 1
        if count_str:
            count = int(count_str)

        # 添加字符
        decompressed.append(current_char * count)

    return ''.join(decompressed)


def compression_ratio(original: str, compressed: str) -> float:
    """
    计算压缩比

    Args:
        original: 原始文本
        compressed: 压缩后的文本

    Returns:
        压缩比
    """
    return len(compressed) / len(original)


def main():
    """主函数"""
    text = "AAAABBBCCDAA"
    print("=== 游程编码 (RLE) ===")
    print(f"原始文本: {text}")

    compressed = compress(text)
    print(f"压缩后: {compressed}")

    decompressed = decompress(compressed)
    print(f"解压后: {decompressed}")

    print(f"压缩比: {compression_ratio(text, compressed):.2f}")
    print(f"验证: {text == decompressed}")

    # 测试用例2
    print("\n测试用例2:")
    text2 = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB"
    compressed2 = compress(text2)
    decompressed2 = decompress(compressed2)
    print(f"原始文本: {text2}")
    print(f"压缩后: {compressed2}")
    print(f"解压后: {decompressed2}")
    print(f"验证: {text2 == decompressed2}")


if __name__ == "__main__":
    main()
