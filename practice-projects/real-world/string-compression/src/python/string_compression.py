"""
实际应用：字符串压缩
场景：数据传输、存储优化、日志压缩、网络协议

使用场景：
- HTTP传输中的GZIP压缩
- 日志文件压缩存储
- 网络通信中的数据压缩
- JSON数据压缩
- 重复模式的数据压缩 (RLE、Huffman编码)
"""

import zlib
import gzip
import json
from collections import Counter
from io import BytesIO


class RunLengthEncoding:
    """游程编码 - 简单的数据压缩"""

    @staticmethod
    def compress(s):
        """RLE压缩"""
        if not s:
            return ""

        result = []
        i = 0
        while i < len(s):
            char = s[i]
            count = 1
            while i + count < len(s) and s[i + count] == char:
                count += 1

            if count > 2:
                result.append(f"{char}{count}")
            else:
                result.extend([char] * count)
            i += count

        return "".join(result)

    @staticmethod
    def decompress(s):
        """RLE解压"""
        result = []
        i = 0
        while i < len(s):
            if i + 1 < len(s) and s[i + 1].isdigit():
                char = s[i]
                j = i + 1
                while j < len(s) and s[j].isdigit():
                    j += 1
                count = int(s[i + 1:j])
                result.append(char * count)
                i = j
            else:
                result.append(s[i])
                i += 1

        return "".join(result)


class SimpleHuffmanEncoder:
    """简化的Huffman编码"""

    @staticmethod
    def compress(text):
        """使用字符频率压缩"""
        if not text:
            return "", {}

        # 计算字符频率
        freq = Counter(text)

        # 生成编码表 (简化版)
        sorted_freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)
        code_map = {}
        for i, (char, _) in enumerate(sorted_freq):
            code_map[char] = format(i, '08b')  # 8位编码

        # 编码文本
        encoded = "".join(code_map[char] for char in text)

        return encoded, code_map

    @staticmethod
    def decompress(encoded_text, code_map):
        """Huffman解码"""
        reverse_map = {v: k for k, v in code_map.items()}
        result = []
        i = 0
        while i < len(encoded_text):
            code = encoded_text[i:i + 8]
            if code in reverse_map:
                result.append(reverse_map[code])
            i += 8
        return "".join(result)


class DataCompressionService:
    """数据压缩服务"""

    @staticmethod
    def gzip_compress(data):
        """Gzip压缩"""
        if isinstance(data, str):
            data = data.encode()

        buf = BytesIO()
        with gzip.GzipFile(fileobj=buf, mode='wb') as f:
            f.write(data)
        compressed = buf.getvalue()

        return compressed, len(data), len(compressed)

    @staticmethod
    def gzip_decompress(compressed_data):
        """Gzip解压"""
        buf = BytesIO(compressed_data)
        with gzip.GzipFile(fileobj=buf, mode='rb') as f:
            decompressed = f.read()
        return decompressed.decode()

    @staticmethod
    def zlib_compress(data):
        """Zlib压缩"""
        if isinstance(data, str):
            data = data.encode()

        compressed = zlib.compress(data)
        return compressed, len(data), len(compressed)

    @staticmethod
    def zlib_decompress(compressed_data):
        """Zlib解压"""
        decompressed = zlib.decompress(compressed_data)
        return decompressed.decode()


class JsonCompressor:
    """JSON数据压缩"""

    @staticmethod
    def compress_json(data):
        """压缩JSON数据"""
        # 紧凑JSON (去除空格)
        compact = json.dumps(data, separators=(',', ':'), ensure_ascii=False)

        # 再使用Gzip压缩
        compressed, original_size, compressed_size = DataCompressionService.gzip_compress(compact)

        return compressed, original_size, compressed_size

    @staticmethod
    def decompress_json(compressed_data):
        """解压JSON数据"""
        decompressed = DataCompressionService.gzip_decompress(compressed_data)
        return json.loads(decompressed)


class LogCompression:
    """日志压缩系统"""

    def __init__(self):
        self.logs = []
        self.compressed_logs = None

    def add_log(self, level, message):
        """添加日志"""
        self.logs.append({
            'level': level,
            'message': message
        })

    def compress_logs(self):
        """压缩日志"""
        log_text = "\n".join(
            f"[{log['level']}] {log['message']}"
            for log in self.logs
        )

        self.compressed_logs, original_size, compressed_size = \
            DataCompressionService.gzip_compress(log_text)

        return original_size, compressed_size

    def get_compression_ratio(self):
        """获取压缩率"""
        log_text = "\n".join(
            f"[{log['level']}] {log['message']}"
            for log in self.logs
        )
        original_size = len(log_text.encode())
        compressed_size = len(self.compressed_logs) if self.compressed_logs else 0

        if original_size == 0:
            return 0

        ratio = (1 - compressed_size / original_size) * 100
        return ratio


class DataTransmission:
    """数据传输优化"""

    @staticmethod
    def prepare_for_transmission(data, max_size=1024):
        """准备数据传输"""
        if isinstance(data, str):
            original = data.encode()
        else:
            original = data

        original_size = len(original)

        if original_size > max_size:
            # 需要压缩
            compressed = zlib.compress(original)
            compressed_size = len(compressed)

            if compressed_size > max_size:
                return None, f"压缩后仍超过限制: {compressed_size} > {max_size}"

            return {
                'compressed': True,
                'data': compressed,
                'original_size': original_size,
                'compressed_size': compressed_size,
                'ratio': f"{(1 - compressed_size/original_size)*100:.2f}%"
            }, "压缩成功"
        else:
            return {
                'compressed': False,
                'data': original,
                'size': original_size
            }, "无需压缩"


if __name__ == "__main__":
    print("=== 字符串压缩实际应用 ===\n")

    # 1. 游程编码
    print("--- 游程编码 (RLE) ---")
    text1 = "AAABBBCCCC"
    compressed = RunLengthEncoding.compress(text1)
    decompressed = RunLengthEncoding.decompress(compressed)
    print(f"原始: {text1} (长度: {len(text1)})")
    print(f"压缩: {compressed} (长度: {len(compressed)})")
    print(f"解压: {decompressed}\n")

    # 2. Gzip压缩
    print("--- Gzip压缩 ---")
    text2 = "Python is a great programming language. " * 10
    compressed, original, compressed_size = DataCompressionService.gzip_compress(text2)
    print(f"原始大小: {original} 字节")
    print(f"压缩后: {compressed_size} 字节")
    print(f"压缩率: {(1 - compressed_size/original)*100:.2f}%\n")

    # 3. JSON压缩
    print("--- JSON压缩 ---")
    data = {
        'users': [
            {'id': 1, 'name': 'Alice'},
            {'id': 2, 'name': 'Bob'},
            {'id': 3, 'name': 'Charlie'}
        ],
        'total': 3
    }
    compressed, original, compressed_size = JsonCompressor.compress_json(data)
    print(f"原始大小: {original} 字节")
    print(f"压缩后: {compressed_size} 字节")
    print(f"压缩率: {(1 - compressed_size/original)*100:.2f}%\n")

    # 4. 日志压缩
    print("--- 日志压缩 ---")
    log_system = LogCompression()
    for i in range(100):
        log_system.add_log("INFO", f"Processing request {i}")
        if i % 10 == 0:
            log_system.add_log("WARNING", f"Slow request at {i}")

    original, compressed = log_system.compress_logs()
    print(f"日志条数: {len(log_system.logs)}")
    print(f"原始大小: {original} 字节")
    print(f"压缩后: {compressed} 字节")
    print(f"压缩率: {log_system.get_compression_ratio():.2f}%\n")

    # 5. 数据传输
    print("--- 数据传输优化 ---")
    large_data = "Data " * 500  # 2500字节
    result, message = DataTransmission.prepare_for_transmission(large_data, max_size=1024)

    if result:
        print(f"状态: {message}")
        print(f"是否压缩: {result.get('compressed')}")
        if result.get('compressed'):
            print(f"原始: {result['original_size']} → 压缩: {result['compressed_size']} 字节")
            print(f"压缩率: {result['ratio']}")
        else:
            print(f"大小: {result['size']} 字节")
