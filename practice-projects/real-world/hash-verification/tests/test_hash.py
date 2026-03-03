"""
Hash验证系统 - 单元测试
"""

import sys
sys.path.insert(0, '../src/python')

from hash_verification import (
    FileVerification,
    ContentDeduplication,
    DataIntegrityValidator
)


def test_content_hash():
    """测试内容哈希"""
    content1 = "Hello, World!"
    content2 = "Hello, World!"
    content3 = "Hello, Python!"

    hash1 = FileVerification.calculate_content_hash(content1)
    hash2 = FileVerification.calculate_content_hash(content2)
    hash3 = FileVerification.calculate_content_hash(content3)

    assert hash1 == hash2, "相同内容应该有相同hash"
    assert hash1 != hash3, "不同内容应该有不同hash"


def test_content_deduplication():
    """测试内容去重存储"""
    dedup = ContentDeduplication()

    # 存储相同内容的两个文件
    hash1 = dedup.add_content("Python is great", "file1.txt")
    hash2 = dedup.add_content("Python is great", "file2.txt")

    assert hash1 == hash2, "相同内容应该返回相同hash"
    assert len(dedup.storage) == 1, "应该只存储一份内容"

    stats = dedup.get_dedup_stats()
    assert stats['unique_content'] == 1
    assert stats['total_files'] == 2


def test_data_integrity():
    """测试数据完整性验证"""
    validator = DataIntegrityValidator()

    data = "Important data"
    validator.register_data("key1", data)

    # 验证未修改的数据
    is_valid, msg = validator.verify_data("key1", data)
    assert is_valid is True

    # 验证被修改的数据
    is_valid, msg = validator.verify_data("key1", "Modified data")
    assert is_valid is False


if __name__ == "__main__":
    print("运行Hash验证系统测试...\n")

    test_content_hash()
    print("✅ test_content_hash 通过")

    test_content_deduplication()
    print("✅ test_content_deduplication 通过")

    test_data_integrity()
    print("✅ test_data_integrity 通过")

    print("\n✅ 所有测试通过！")
