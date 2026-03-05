"""
Maximize Number - Remove k digits to get maximum value

Algorithm:
- Given a digit string and k, remove k digits to maximize the resulting number
- Use a greedy stack-based approach:
  1. Iterate through digits
  2. If current digit is greater than the top of stack, pop smaller digits
  3. Add current digit to stack
  4. If we still need to delete digits, remove from the end
  5. Return the remaining digits

Time Complexity: O(n) - each digit is pushed/popped at most once
Space Complexity: O(n) - for the stack

Key Insight:
To maximize the number, we want larger digits at the front.
When we encounter a digit larger than those before it, we should
remove smaller digits that came before it (if we still have deletions left).

示例:
- num = "1432219", k = 3
- Process: '1'[1] -> '4'[1,4] (remove 1) -> '3' -> '2' -> '2' -> '1' -> '9'[4,3,2,2,1,9] (remove last 3)
- Result: "4321"
"""

from typing import Tuple


def remove_k_digits(num_str: str, k: int) -> str:
    """
    Remove k digits from the string to get maximum resulting number.

    参数:
        num_str: String of digits
        k: Number of digits to remove

    返回:
        String representing the maximum number after removing k digits

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

    # Stack-based greedy approach
    stack = []
    to_delete = k

    for digit in num_str:
        # Remove smaller digits from stack when we encounter a larger digit
        while to_delete > 0 and stack and stack[-1] < digit:
            stack.pop()
            to_delete -= 1
        stack.append(digit)

    # If we still have digits to delete, remove from the end
    if to_delete > 0:
        stack = stack[:-to_delete]

    # Handle leading zeros
    result = ''.join(stack).lstrip('0')
    return result if result else "0"


def maximize_number_greedy(num: int, k: int) -> str:
    """
    Convenience function accepting integer input.

    参数:
        num: Integer number
        k: Number of digits to remove

    返回:
        String representing the maximum number
    """
    return remove_k_digits(str(num), k)


def maximize_number_with_tracking(num_str: str, k: int) -> Tuple[str, list]:
    """
    Return the result along with the deletion positions.

    参数:
        num_str: String of digits
        k: Number of digits to remove

    返回:
        Tuple of (result_string, list of deleted positions)
    """
    if k >= len(num_str):
        return ("0", list(range(len(num_str))))

    if k == 0:
        return (num_str, [])

    stack = []
    to_delete = k
    deleted_positions = []

    for i, digit in enumerate(num_str):
        while to_delete > 0 and stack and stack[-1][0] < digit:
            _, pos = stack.pop()
            deleted_positions.append(pos)
            to_delete -= 1
        stack.append((digit, i))

    # Delete remaining from end if needed
    if to_delete > 0:
        while to_delete > 0 and stack:
            _, pos = stack.pop()
            deleted_positions.append(pos)
            to_delete -= 1

    # Build result from stack
    result = ''.join([d[0] for d in stack])
    result = result.lstrip('0') or "0"

    return (result, sorted(deleted_positions))


def is_valid_maximization(num_str: str, k: int, result: str) -> bool:
    """
    Validate that the result is correct (for testing).
    """
    # Check that exactly k digits were removed
    if len(num_str) - k != len(result.lstrip('0')) and result != "0":
        return False

    # Check that result uses digits from original in same order
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
    print("MAXIMIZE NUMBER - Remove k Digits for Maximum Value")
    print("=" * 60)

    # 测试用例 1: Standard example
    print("\n[Test 1] Standard example from problem")
    num1 = "1432219"
    k1 = 3
    result1 = remove_k_digits(num1, k1)
    print(f"Input: '{num1}', k={k1}")
    print(f"Output: '{result1}'")
    print(f"Expected: '4321'")

    # 测试用例 2: Another standard case
    print("\n[Test 2] Remove leading zeros")
    num2 = "10200"
    k2 = 1
    result2 = remove_k_digits(num2, k2)
    print(f"Input: '{num2}', k={k2}")
    print(f"Output: '{result2}'")
    print(f"Expected: '200'")

    # 测试用例 3: All same digits
    print("\n[Test 3] All same digits")
    num3 = "1111"
    k3 = 2
    result3 = remove_k_digits(num3, k3)
    print(f"Input: '{num3}', k={k3}")
    print(f"Output: '{result3}'")
    print(f"Expected: '11'")

    # 测试用例 4: Descending order (worst case for greedy)
    print("\n[Test 4] Descending digits - remove from end")
    num4 = "54321"
    k4 = 2
    result4 = remove_k_digits(num4, k4)
    print(f"Input: '{num4}', k={k4}")
    print(f"Output: '{result4}'")
    print(f"Expected: '321'")

    # 测试用例 5: Ascending order (best case for greedy)
    print("\n[Test 5] Ascending digits - remove from front")
    num5 = "12345"
    k5 = 2
    result5 = remove_k_digits(num5, k5)
    print(f"Input: '{num5}', k={k5}")
    print(f"Output: '{result5}'")
    print(f"Expected: '345'")

    # 测试用例 6: Remove all digits
    print("\n[Test 6] Remove all digits")
    num6 = "123"
    k6 = 3
    result6 = remove_k_digits(num6, k6)
    print(f"Input: '{num6}', k={k6}")
    print(f"Output: '{result6}'")
    print(f"Expected: '0'")

    # 测试用例 7: Remove zero digits
    print("\n[Test 7] Remove zero digits")
    num7 = "1234"
    k7 = 0
    result7 = remove_k_digits(num7, k7)
    print(f"Input: '{num7}', k={k7}")
    print(f"Output: '{result7}'")
    print(f"Expected: '1234'")

    # 测试用例 8: Mixed with leading zeros
    print("\n[Test 8] Multiple zeros in middle")
    num8 = "100200"
    k8 = 2
    result8 = remove_k_digits(num8, k8)
    print(f"Input: '{num8}', k={k8}")
    print(f"Output: '{result8}'")

    # 测试用例 9: Large number
    print("\n[Test 9] Large number")
    num9 = "112"
    k9 = 1
    result9 = remove_k_digits(num9, k9)
    print(f"Input: '{num9}', k={k9}")
    print(f"Output: '{result9}'")
    print(f"Expected: '12'")

    # 测试用例 10: Complex case with tracking
    print("\n[Test 10] With deletion position tracking")
    num10 = "987654321"
    k10 = 4
    result10, deleted_pos = maximize_number_with_tracking(num10, k10)
    print(f"Input: '{num10}', k={k10}")
    print(f"Output: '{result10}'")
    print(f"Deleted positions: {deleted_pos}")
