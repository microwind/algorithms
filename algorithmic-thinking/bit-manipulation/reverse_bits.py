"""
反转二进制位

问题：反转一个32位整数的二进制表示

核心思想：
- 逐位提取和重建
- 位操作实现高效反转

时间复杂度: O(log n) 或 O(32) = O(1)
空间复杂度: O(1)
"""


def reverse_bits_builtin(n):
    """
    使用Python内置函数反转位

    时间复杂度: O(32)
    空间复杂度: O(32)
    """
    # 转换为32位二进制字符串
    binary_str = bin(n)[2:].zfill(32)
    # 反转字符串
    reversed_str = binary_str[::-1]
    # 转换回整数
    return int(reversed_str, 2)


def reverse_bits_iterative(n):
    """
    逐位反转：从右到左提取，从左到右重建

    原理：
    - 从n的最右边提取一位
    - 将其放在result的最左边
    - 继续处理n的其他位

    时间复杂度: O(32)
    空间复杂度: O(1)
    """
    result = 0
    for _ in range(32):
        # 提取n的最右边一位
        bit = n & 1
        # 右移n，处理下一位
        n >>= 1
        # result左移，为新位腾出空间
        result <<= 1
        # 将bit加到result
        result |= bit

    return result


def reverse_bits_manual(n):
    """
    手动位操作：逐字节反转后交换

    时间复杂度: O(32)
    空间复杂度: O(1)
    """
    result = 0
    # 处理32位
    for i in range(32):
        # 从n中提取第i位
        if (n >> i) & 1:
            # 在result中设置第(31-i)位
            result |= (1 << (31 - i))

    return result


def reverse_bits_byte_by_byte(n):
    """
    按字节反转（4个字节的整数）

    时间复杂度: O(32)
    空间复杂度: O(1)
    """
    result = 0

    # 处理4个字节
    for i in range(4):
        # 提取第i个字节
        byte = (n >> (i * 8)) & 0xFF
        # 反转字节内的位
        reversed_byte = 0
        for j in range(8):
            if (byte >> j) & 1:
                reversed_byte |= (1 << (7 - j))
        # 将反转后的字节放在结果的正确位置
        result |= (reversed_byte << ((3 - i) * 8))

    return result


def reverse_bits_lookup(n):
    """
    使用查表法反转（针对频繁调用优化）

    时间复杂度: O(1)
    空间复杂度: O(256)
    """
    # 预计算0-255的位反转
    lookup = [0] * 256
    for i in range(256):
        lookup[i] = int(format(i, '08b')[::-1], 2)

    result = 0
    for i in range(4):
        byte = (n >> (i * 8)) & 0xFF
        reversed_byte = lookup[byte]
        result |= (reversed_byte << ((3 - i) * 8))

    return result


if __name__ == "__main__":
    print("=== 反转二进制位 ===\n")

    # 测试用例1：基本用例
    print("1. 基本用例:")
    test_cases = [
        1,           # 00000000000000000000000000000001 -> 10000000000000000000000000000000
        2,           # 00000000000000000000000000000010 -> 01000000000000000000000000000000
        3,           # 00000000000000000000000000000011 -> 11000000000000000000000000000000
        43261596,    # 00000010100101000001111010011100 -> 00111001011110000101000101000010
    ]
    for num in test_cases:
        builtin = reverse_bits_builtin(num)
        iterative = reverse_bits_iterative(num)
        binary_orig = bin(num)[2:].zfill(32)
        binary_rev = bin(builtin)[2:].zfill(32)
        print(f"  输入:   {binary_orig} ({num})")
        print(f"  输出:   {binary_rev} ({builtin})")
        print()

    # 测试用例2：比较不同算法
    print("2. 不同算法的结果比较:")
    test_nums = [0, 1, 2, 7, 15, 255, 43261596, 2147483647]
    for num in test_nums:
        builtin = reverse_bits_builtin(num)
        iterative = reverse_bits_iterative(num)
        manual = reverse_bits_manual(num)
        byte_by_byte = reverse_bits_byte_by_byte(num)
        all_match = (builtin == iterative == manual == byte_by_byte)
        print(f"  n={num}: 所有算法一致 = {all_match}")
    print()

    # 测试用例3：特殊值
    print("3. 特殊值:")
    special_values = {
        0: "全0",
        0xFFFFFFFF: "全1",
        0x80000000: "仅最左位为1",
        0x00000001: "仅最右位为1",
        0x12345678: "任意值",
    }
    for num, desc in special_values.items():
        result = reverse_bits_iterative(num)
        print(f"  {desc:15s}: {hex(num)} -> {hex(result)}")
    print()

    # 测试用例4：验证对称性
    print("4. 验证反转的对称性（反转两次应该回到原值）:")
    test_nums = [1, 7, 255, 43261596]
    for num in test_nums:
        once = reverse_bits_iterative(num)
        twice = reverse_bits_iterative(once)
        symmetric = (num == twice)
        print(f"  {num}: 反转两次后恢复 = {symmetric}")
