/**
 * Copyright © https://github.com/microwind All rights reserved.
 * 
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

import random
import base64

class Token:
    """LZ77压缩令牌类"""
    
    def __init__(self, offset=0, length=0, character=None):
        self.offset = offset
        self.length = length
        self.character = character
    
    def __str__(self):
        if self.length > 0:
            return f"({self.offset},{self.length})"
        else:
            return f"({self.character})"

def lz77_compress(input_str):
    """
    LZ77压缩算法
    @param input_str: 输入字符串
    @return: 压缩后的令牌列表
    """
    print("LZ77压缩开始...")
    tokens = []
    window_size = 256
    position = 0
    
    while position < len(input_str):
        max_length = min(window_size, position)
        window = input_str[max(0, position - max_length):position]
        
        best_length = 0
        best_offset = 0
        
        # 在窗口中搜索最长匹配
        for i in range(len(window)):
            match_length = 0
            while (position + match_length < len(input_str) and
                   i + match_length < len(window) and
                   input_str[position + match_length] == window[i + match_length]):
                match_length += 1
            
            if match_length > best_length:
                best_length = match_length
                best_offset = len(window) - i
        
        if best_length >= 3:  # 最小匹配长度
            next_char = input_str[position + best_length] if position + best_length < len(input_str) else None
            tokens.append(Token(best_offset, best_length, next_char))
            print(f"找到匹配: 偏移={best_offset}, 长度={best_length}")
            position += best_length + 1
        else:
            tokens.append(Token(0, 0, input_str[position]))
            print(f"字面量: {input_str[position]}")
            position += 1
    
    print(f"LZ77压缩完成，令牌数: {len(tokens)}")
    return tokens

def lz77_decompress(tokens):
    """
    LZ77解压算法
    @param tokens: 压缩令牌列表
    @return: 解压后的字符串
    """
    print("LZ77解压开始...")
    output = []
    
    for i, token in enumerate(tokens):
        print(f"处理令牌 {i}: {token}")
        
        if token.length > 0:
            start = len(output) - token.offset
            for j in range(token.length):
                output.append(output[start + j])
            if token.character is not None:
                output.append(token.character)
        else:
            output.append(token.character)
    
    print(f"LZ77解压完成，长度: {len(output)}")
    return ''.join(output)

def compression_ratio(original, compressed):
    """
    计算压缩比
    @param original: 原始字符串
    @param compressed: 压缩令牌列表
    @return: 压缩比
    """
    original_size = len(original) * 8  # 假设每个字符8位
    compressed_size = 0
    for token in compressed:
        compressed_size += 16  # 偏移和长度各8位
        if token.length > 0:
            compressed_size += 8  # 字符8位
    return compressed_size / original_size

def main():
    """主函数，演示LZ77压缩和解压"""
    input_str = "ABABABABABAABABABABA"
    print("=== LZ77算法演示 ===")
    print(f"原始文本: {input_str}")
    print(f"原始长度: {len(input_str)}")
    
    # 压缩
    compressed = lz77_compress(input_str)
    print(f"压缩结果: {compressed}")
    
    # 计算压缩比
    ratio = compression_ratio(input_str, compressed)
    print(f"压缩比: {ratio:.2f}")
    
    # 解压
    decompressed = lz77_decompress(compressed)
    print(f"解压结果: {decompressed}")
    print(f"解压长度: {len(decompressed)}")
    
    # 验证
    is_valid = input_str == decompressed
    print(f"验证结果: {'✓ 成功' if is_valid else '✗ 失败'}")
    print("=== 演示结束 ===")

if __name__ == "__main__":
    main()
