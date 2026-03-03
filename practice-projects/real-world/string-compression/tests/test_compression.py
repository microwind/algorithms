"""
字符串压缩系统 - 单元测试
"""

import sys
sys.path.insert(0, '../src/python')

from string_compression import (
    RunLengthEncoding,
    DataCompressionService,
    JsonCompressor
)


def test_rle_compression():
    """测试RLE编码"""
    text = "AAABBBCCCC"
    compressed = RunLengthEncoding.compress(text)
    decompressed = RunLengthEncoding.decompress(compressed)

    assert decompressed == text, "压缩后应该能正确解压"
    assert len(compressed) < len(text), "应该有压缩效果"


def test_gzip_compression():
    """测试Gzip压缩"""
    text = "Python is great. " * 100
    compressed, original, compressed_size = DataCompressionService.gzip_compress(text)

    assert compressed_size < original, "压缩后应该更小"
    assert len(text.encode()) == original

    # 验证解压
    decompressed = DataCompressionService.gzip_decompress(compressed)
    assert decompressed == text


def test_json_compression():
    """测试JSON压缩"""
    data = {
        'users': [
            {'id': 1, 'name': 'Alice'},
            {'id': 2, 'name': 'Bob'}
        ]
    }

    compressed, original, compressed_size = JsonCompressor.compress_json(data)
    assert compressed_size < original, "压缩后应该更小"

    # 验证解压
    decompressed = JsonCompressor.decompress_json(compressed)
    assert decompressed == data


if __name__ == "__main__":
    print("运行字符串压缩系统测试...\n")

    test_rle_compression()
    print("✅ test_rle_compression 通过")

    test_gzip_compression()
    print("✅ test_gzip_compression 通过")

    test_json_compression()
    print("✅ test_json_compression 通过")

    print("\n✅ 所有测试通过！")
