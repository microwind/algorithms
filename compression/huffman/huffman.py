"""
霍夫曼编码实现 - Python
基于最小堆构建最优前缀编码
"""

import heapq
from collections import defaultdict

# 霍夫曼树节点
class HuffmanNode:
    def __init__(self, char=None, freq=0, left=None, right=None):
        self.char = char
        self.freq = freq
        self.left = left
        self.right = right
    
    def __lt__(self, other):
        return self.freq < other.freq

def huffman_encode(text):
    """生成Huffman编码表"""
    # 统计字符频率
    frequency = defaultdict(int)
    for char in text:
        frequency[char] += 1
    
    # 初始化：所有字符节点入堆
    heap = []
    for char, freq in frequency.items():
        heapq.heappush(heap, HuffmanNode(char, freq))
    
    # 循环合并最小频率节点，构建霍夫曼树
    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        parent = HuffmanNode(freq=left.freq + right.freq, left=left, right=right)
        heapq.heappush(heap, parent)
    
    # 生成编码表
    encoding_map = {}
    root = heapq.heappop(heap) if heap else None
    _generate_codes(root, "", encoding_map)
    
    return encoding_map

# 递归生成编码：左0右1
def _generate_codes(node, code, encoding_map):
    if node is None:
        return
    
    # 叶子节点：存储编码
    if node.left is None and node.right is None:
        encoding_map[node.char] = code if code else "0"
        return
    
    _generate_codes(node.left, code + "0", encoding_map)
    _generate_codes(node.right, code + "1", encoding_map)

def compress(text, encoding_map):
    """使用Huffman编码压缩文本"""
    compressed = ""
    for char in text:
        compressed += encoding_map[char]
    return compressed

def decompress(compressed, root):
    """使用Huffman树解压文本"""
    decompressed = ""
    current = root
    
    for bit in compressed:
        current = current.left if bit == '0' else current.right
        
        if current.left is None and current.right is None:
            decompressed += current.char
            current = root
    
    return decompressed

def main():
    text = "hello world"
    print(f"原始文本: {text}")
    
    encoding_map = huffman_encode(text)
    print(f"编码表: {encoding_map}")
    
    compressed = compress(text, encoding_map)
    print(f"压缩后: {compressed}")
    
    print(f"压缩率: {len(compressed) / (len(text) * 8):.2f}")

if __name__ == "__main__":
    main()
