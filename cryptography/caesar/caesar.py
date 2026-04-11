"""
*
 * 凯撒密码 - 简单的替换加密
 *
 * 问题：将字母表中的每个字母移动固定位数
 *
 * 核心思想：
 * - 字母替换
 * - 循环移位
 * - 保持大小写
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
"""


def caesar_encrypt(text: str, shift: int) -> str:
    """
    凯撒加密

    Args:
        text: 明文
        shift: 移位数

    Returns:
        密文
    """
    result = []

    for char in text:
        if char.isupper():
            result.append(chr((ord(char) - ord('A') + shift) % 26 + ord('A')))
        elif char.islower():
            result.append(chr((ord(char) - ord('a') + shift) % 26 + ord('a')))
        else:
            result.append(char)

    return ''.join(result)


def caesar_decrypt(text: str, shift: int) -> str:
    """
    凯撒解密

    Args:
        text: 密文
        shift: 移位数

    Returns:
        明文
    """
    return caesar_encrypt(text, 26 - (shift % 26))


def main():
    """主函数"""
    print("=== 凯撒密码 ===")

    text = "Hello, World!"
    shift = 3

    print(f"明文: {text}")
    print(f"移位数: {shift}")

    # 加密
    encrypted = caesar_encrypt(text, shift)
    print(f"加密后: {encrypted}")

    # 解密
    decrypted = caesar_decrypt(encrypted, shift)
    print(f"解密后: {decrypted}")

    print(f"验证: {text == decrypted}")


if __name__ == "__main__":
    main()
