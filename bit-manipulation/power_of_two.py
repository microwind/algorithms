"""
2的幂 - 位运算和数字性质

问题：
1. 检查一个数是否是2的幂
2. 计算2的幂相关的位操作

核心思想：
- 2的幂在二进制表示中只有一个1（1, 2, 4, 8, 16, ...）
- n & (n-1) == 0 可以判断是否为2的幂
- 利用位运算的性质进行快速计算

时间复杂度: O(1)
空间复杂度: O(1)
"""


def is_power_of_two(n):
    """
    判断一个数是否是2的幂

    原理：
    - 2的幂的二进制表示只有一个1，其余为0
    - 例如：8 = 1000 (二进制)
    - n-1 = 0111 (二进制)
    - n & (n-1) = 0

    时间复杂度: O(1)
    空间复杂度: O(1)
    """
    return n > 0 and (n & (n - 1)) == 0


def is_power_of_two_builtin(n):
    """
    使用内置函数判断（备选方案）

    时间复杂度: O(1)
    空间复杂度: O(1)
    """
    if n <= 0:
        return False
    return bin(n).count('1') == 1


def power_of_two_count(n):
    """
    计算2的幂中的位置（幂的指数）

    例如：
    - 8 (1000) 的位置是 3 (2^3 = 8)
    - 16 (10000) 的位置是 4 (2^4 = 16)

    时间复杂度: O(1)
    空间复杂度: O(1)
    """
    if not is_power_of_two(n):
        return -1

    # 方法1：计算二进制位数减1
    return n.bit_length() - 1


def next_power_of_two(n):
    """
    找到大于等于n的最小2的幂

    例如：
    - n=5 -> 8 (2^3)
    - n=8 -> 8 (2^3)
    - n=10 -> 16 (2^4)

    时间复杂度: O(1)
    空间复杂度: O(1)
    """
    if n <= 1:
        return 1

    # 如果已经是2的幂，直接返回
    if is_power_of_two(n):
        return n

    # 找到下一个2的幂
    n -= 1
    n |= n >> 1
    n |= n >> 2
    n |= n >> 4
    n |= n >> 8
    n |= n >> 16
    n |= n >> 32
    return n + 1


def get_power_exponent(n):
    """
    获取n是2的几次方

    时间复杂度: O(1)
    空间复杂度: O(1)
    """
    if not is_power_of_two(n):
        return -1
    return (n - 1).bit_length()


if __name__ == "__main__":
    print("=== 2的幂 ===\n")

    # 测试用例1：判断是否为2的幂
    print("1. 判断是否为2的幂:")
    test_nums = [1, 2, 3, 4, 5, 8, 16, 17, 32, 100]
    for num in test_nums:
        result = is_power_of_two(num)
        print(f"  {num:3d} 是2的幂: {result}")
    print()

    # 测试用例2：获取幂的指数
    print("2. 获取2的幂中的指数:")
    power_nums = [1, 2, 4, 8, 16, 32, 64, 128, 256]
    for num in power_nums:
        exp = get_power_exponent(num)
        print(f"  2^{exp} = {num}")
    print()

    # 测试用例3：找下一个2的幂
    print("3. 找大于等于n的最小2的幂:")
    test_nums = [1, 3, 5, 7, 8, 9, 15, 16, 17, 100]
    for num in test_nums:
        next_pow = next_power_of_two(num)
        print(f"  n={num:3d} -> {next_pow}")
    print()

    # 测试用例4：边界情况
    print("4. 边界情况:")
    print(f"  0 是2的幂: {is_power_of_two(0)}")
    print(f"  1 是2的幂: {is_power_of_two(1)}")
    print(f"  负数 -8 是2的幂: {is_power_of_two(-8)}")
