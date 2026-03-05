"""
计数1位 - Hamming权重

问题：计算整数二进制表示中1的个数

核心思想：
- 逐位检查：与1进行AND操作
- Brian Kernighan算法：n & (n-1) 移除最右边的1
- 预计算查表法（对于频繁调用优化）

时间复杂度: O(log n) 或 O(1) 取决于实现方式
空间复杂度: O(1)
"""


def count_ones_builtin(n):
    """
    使用Python内置函数计数1位

    时间复杂度: O(1)
    空间复杂度: O(1)
    """
    return bin(n).count('1')


def count_ones_loop(n):
    """
    逐位检查：循环检查每一位

    原理：
    - 将n与1进行AND操作，检查最右边的位
    - 右移n，继续检查下一位
    - 重复直到n为0

    时间复杂度: O(log n)
    空间复杂度: O(1)
    """
    count = 0
    while n:
        count += n & 1
        n >>= 1
    return count


def count_ones_kernighan(n):
    """
    Brian Kernighan算法：移除最右边的1

    原理：
    - n & (n-1) 移除n的最右边的1
    - 重复这个操作直到n为0
    - 操作次数就是1的个数
    - 只需O(k)的时间，k是1的个数

    时间复杂度: O(k) 其中k是1的个数
    空间复杂度: O(1)
    """
    count = 0
    while n:
        n &= n - 1  # 移除最右边的1
        count += 1
    return count


def count_ones_table(n):
    """
    使用查表法（用于频繁调用的优化）

    时间复杂度: O(log n / 8)（字节查询）
    空间复杂度: O(256)
    """
    # 预计算0-255中1的个数
    lookup_table = [bin(i).count('1') for i in range(256)]

    count = 0
    while n:
        count += lookup_table[n & 0xFF]
        n >>= 8
    return count


def count_ones_parallel(n):
    """
    并行计数法（位操作优化）

    时间复杂度: O(log log n)
    空间复杂度: O(1)
    """
    # 对于32位整数
    n = ((n & 0xaaaaaaaa) >> 1) + (n & 0x55555555)
    n = ((n & 0xcccccccc) >> 2) + (n & 0x33333333)
    n = ((n & 0xf0f0f0f0) >> 4) + (n & 0x0f0f0f0f)
    n = ((n & 0xff00ff00) >> 8) + (n & 0x00ff00ff)
    n = ((n & 0xffff0000) >> 16) + (n & 0x0000ffff)
    return n


if __name__ == "__main__":
    print("=== 计数1位 (Hamming权重) ===\n")

    # 测试用例1：基本用例
    print("1. 基本用例:")
    test_nums = [0, 1, 3, 5, 7, 15, 31, 63, 127, 255]
    for num in test_nums:
        builtin = count_ones_builtin(num)
        loop = count_ones_loop(num)
        kernighan = count_ones_kernighan(num)
        binary_str = bin(num)[2:].rjust(8, '0')
        print(f"  {num:3d} ({binary_str}): {builtin}")
    print()

    # 测试用例2：比较不同算法
    print("2. 不同算法的结果比较:")
    test_nums = [1, 7, 15, 127, 255, 1023]
    for num in test_nums:
        builtin = count_ones_builtin(num)
        loop = count_ones_loop(num)
        kernighan = count_ones_kernighan(num)
        table = count_ones_table(num)
        print(f"  n={num:4d}: builtin={builtin}, loop={loop}, "
              f"kernighan={kernighan}, table={table}")
    print()

    # 测试用例3：大数值
    print("3. 大数值:")
    large_nums = [2**16 - 1, 2**20 - 1, 2**30 - 1]
    for num in large_nums:
        count = count_ones_kernighan(num)
        print(f"  2^{num.bit_length()} - 1 = {num}, 1的个数: {count}")
    print()

    # 测试用例4：性能对比（针对稀疏1）
    print("4. 稀疏1的情况（Kernighan优势明显）:")
    sparse_nums = [1, 2, 4, 8, 16, 32, 64, 128, 256]
    for num in sparse_nums:
        count = count_ones_kernighan(num)
        print(f"  {num:3d} (2^?): 1的个数 = {count}")
