
"""
移除k位数字使数值最大（贪心算法）

算法思路：
- 给定一个数字字符串和整数k
- 移除k位数字，使剩下的数字最大
- 策略：贪心地用单调栈，每次遇到比栈顶大的数字就移除栈顶

时间复杂度：O(n)
空间复杂度：O(n)

关键：每次遇到前一位比后一位小就移除前一位，保证高位尽量大

示例：
num = "1432219", k = 3
处理过程：'1' -> '4'（移除1）-> '3' -> '2' -> '2' -> '1' -> '9'（移除最后3位）
结果："4321"
"""

from typing import Tuple


def remove_k_digits(num_str: str, k: int) -> str:
    """
    移除k位数字，使剩下的数字最大

    参数:
        num_str: 数字字符串
        k: 需要移除的位数

    返回:
        移除后最大的数字字符串

    示例:
        >>> remove_k_digits("1432219", 3)
        '4321'
        >>> remove_k_digits("10200", 1)
        '200'
    """
    if k >= len(num_str):
        return "0"
    if k == 0:
        return num_str
    stack = []  # 单调栈，保存结果
    to_delete = k  # 剩余可移除位数
    for digit in num_str:
        # 贪心：如果栈顶比当前数字小且还有移除名额，则移除栈顶
        while to_delete > 0 and stack and stack[-1] < digit:
            stack.pop()
            to_delete -= 1
        stack.append(digit)
    # 如果还有剩余移除名额，则从末尾移除
    if to_delete > 0:
        stack = stack[:-to_delete]
    # 去除前导零
    result = ''.join(stack).lstrip('0')
    return result if result else "0"


def maximize_number_greedy(num: int, k: int) -> str:
    """
    整数输入的便捷函数

    参数:
        num: 整数
        k: 需要移除的位数

    返回:
        移除后最大的数字字符串
    """
    return remove_k_digits(str(num), k)


def maximize_number_with_tracking(num_str: str, k: int) -> Tuple[str, list]:
    """
    返回最大值及被删除的位置（便于调试）

    参数:
        num_str: 数字字符串
        k: 需要移除的位数

    返回:
        (最大值字符串, 被删除的位置列表)
    """
    if k >= len(num_str):
        return ("0", list(range(len(num_str))))
    if k == 0:
        return (num_str, [])
    stack = []
    to_delete = k
    deleted_positions = []
    for i, digit in enumerate(num_str):
        # 贪心：如果栈顶比当前数字小且还有移除名额，则移除栈顶
        while to_delete > 0 and stack and stack[-1][0] < digit:
            _, pos = stack.pop()
            deleted_positions.append(pos)
            to_delete -= 1
        stack.append((digit, i))
    # 如果还有剩余移除名额，则从末尾移除
    if to_delete > 0:
        while to_delete > 0 and stack:
            _, pos = stack.pop()
            deleted_positions.append(pos)
            to_delete -= 1
    # 构造结果字符串
    result = ''.join([d[0] for d in stack])
    result = result.lstrip('0') or "0"
    return (result, sorted(deleted_positions))


def is_valid_maximization(num_str: str, k: int, result: str) -> bool:
    """
    验证结果是否正确（测试用）
    """
    # 检查是否恰好移除了k位
    if len(num_str) - k != len(result.lstrip('0')) and result != "0":
        return False
    # 检查结果是否按原顺序选取数字
    j = 0
    for digit in result:
        found = False
        while j < len(num_str):
            if num_str[j] == digit:
                j += 1
                found = True
                break
            j += 1
        if not found:
            return False
    return True



if __name__ == "__main__":
    print("=" * 60)
    print("移除k位数字使数值最大 - 贪心算法")
    print("=" * 60)
    # 测试用例 1: 标准示例
    print("\n[测试1] 标准示例")
    num1 = "1432219"
    k1 = 3
    result1 = remove_k_digits(num1, k1)
    print(f"输入: '{num1}', k={k1}")
    print(f"输出: '{result1}'")
    print(f"期望: '4321'")
    # 测试用例 2: 去除前导零
    print("\n[测试2] 去除前导零")
    num2 = "10200"
    k2 = 1
    result2 = remove_k_digits(num2, k2)
    print(f"输入: '{num2}', k={k2}")
    print(f"输出: '{result2}'")
    print(f"期望: '200'")
    # 测试用例 3: 全部相同数字
    print("\n[测试3] 全部相同数字")
    num3 = "1111"
    k3 = 2
    result3 = remove_k_digits(num3, k3)
    print(f"输入: '{num3}', k={k3}")
    print(f"输出: '{result3}'")
    print(f"期望: '11'")
    # 测试用例 4: 递减数字（贪心最差情况）
    print("\n[测试4] 递减数字 - 从末尾移除")
    num4 = "54321"
    k4 = 2
    result4 = remove_k_digits(num4, k4)
    print(f"输入: '{num4}', k={k4}")
    print(f"输出: '{result4}'")
    print(f"期望: '321'")
    # 测试用例 5: 递增数字（贪心最优情况）
    print("\n[测试5] 递增数字 - 从前面移除")
    num5 = "12345"
    k5 = 2
    result5 = remove_k_digits(num5, k5)
    print(f"输入: '{num5}', k={k5}")
    print(f"输出: '{result5}'")
    print(f"期望: '345'")
    # 测试用例 6: 移除所有数字
    print("\n[测试6] 移除所有数字")
    num6 = "123"
    k6 = 3
    result6 = remove_k_digits(num6, k6)
    print(f"输入: '{num6}', k={k6}")
    print(f"输出: '{result6}'")
    print(f"期望: '0'")
    # 测试用例 7: 不移除数字
    print("\n[测试7] 不移除数字")
    num7 = "1234"
    k7 = 0
    result7 = remove_k_digits(num7, k7)
    print(f"输入: '{num7}', k={k7}")
    print(f"输出: '{result7}'")
    print(f"期望: '1234'")
    # 测试用例 8: 中间有多个零
    print("\n[测试8] 中间有多个零")
    num8 = "100200"
    k8 = 2
    result8 = remove_k_digits(num8, k8)
    print(f"输入: '{num8}', k={k8}")
    print(f"输出: '{result8}'")
    # 测试用例 9: 较大数字
    print("\n[测试9] 较大数字")
    num9 = "112"
    k9 = 1
    result9 = remove_k_digits(num9, k9)
    print(f"输入: '{num9}', k={k9}")
    print(f"输出: '{result9}'")
    print(f"期望: '12'")
    # 测试用例 10: 带删除位置跟踪
    print("\n[测试10] 带删除位置跟踪")
    num10 = "987654321"
    k10 = 4
    result10, deleted_pos = maximize_number_with_tracking(num10, k10)
    print(f"输入: '{num10}', k={k10}")
    print(f"输出: '{result10}'")
    print(f"被删除的位置: {deleted_pos}")
