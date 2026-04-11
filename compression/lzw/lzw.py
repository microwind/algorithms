"""
*
 * LZW压缩算法 - 字典压缩
 *
 * 问题：使用动态字典进行无损数据压缩
 *
 * 核心思想：
 * - 动态构建编码字典
 * - 查找最长匹配字符串
 * - 输出字典索引
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
"""

MAX_DICT_SIZE = 4096


def lzw_compress(input_str: str) -> list:
    """
    LZW压缩

    Args:
        input_str: 输入字符串

    Returns:
        压缩后的编码列表
    """
    dictionary = {}

    # 初始化字典（单字符）
    for i in range(256):
        dictionary[chr(i)] = i

    compressed = []
    current = ""
    dict_size = 256

    for char in input_str:
        combined = current + char

        if combined in dictionary:
            current = combined
        else:
            # 输出current的编码
            compressed.append(dictionary[current])

            # 将combined加入字典
            if dict_size < MAX_DICT_SIZE:
                dictionary[combined] = dict_size
                dict_size += 1

            # 重置current为char
            current = char

    # 输出最后一个编码
    if current:
        compressed.append(dictionary[current])

    return compressed


def lzw_decompress(compressed: list) -> str:
    """
    LZW解压

    Args:
        compressed: 压缩后的编码列表

    Returns:
        解压后的字符串
    """
    dictionary = {}

    # 初始化字典（单字符）
    for i in range(256):
        dictionary[i] = chr(i)

    output = ""
    old_code = compressed[0]
    old_string = dictionary[old_code]
    output += old_string

    dict_size = 256

    for new_code in compressed[1:]:
        if new_code not in dictionary:
            # 特殊情况：new_code不在字典中
            string_val = old_string + old_string[0]
        else:
            string_val = dictionary[new_code]

        output += string_val

        # 将old_string + string[0]加入字典
        if dict_size < MAX_DICT_SIZE:
            dictionary[dict_size] = old_string + string_val[0]
            dict_size += 1

        old_string = string_val

    return output


def main():
    """主函数"""
    input_str = "TOBEORNOTTOBEORTOBEORNOT"
    print("=== LZW压缩算法 ===")
    print(f"原始文本: {input_str}")

    compressed = lzw_compress(input_str)
    print(f"压缩后编码: {compressed}")

    decompressed = lzw_decompress(compressed)
    print(f"解压后文本: {decompressed}")

    print(f"验证: {input_str == decompressed}")


if __name__ == "__main__":
    main()
