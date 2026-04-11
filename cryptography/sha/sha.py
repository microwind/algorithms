"""
*
 * SHA-256哈希算法 - 密码学哈希函数
 *
 * 问题：生成消息的固定长度哈希值
 *
 * 核心思想：
 * - 填充消息到512位的倍数
 * - 分块处理
 * - 位操作和逻辑运算
 *
 * 注意：此实现使用Python内置库
 * 实际应用应使用成熟的加密库
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
"""

import hashlib


def sha256_hash(message: str) -> str:
    return hashlib.sha256(message.encode()).hexdigest()


def main():
    print("=== SHA-256哈希算法 ===")
    message = "Hello, World!"
    print(f"消息: {message}")
    hash_value = sha256_hash(message)
    print(f"SHA-256: {hash_value}")
    print("\n注意：此实现使用Python内置库，")
    print("实际应用应使用成熟的加密库。")


if __name__ == "__main__":
    main()
