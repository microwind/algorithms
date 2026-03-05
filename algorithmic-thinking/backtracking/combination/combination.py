"""
使用回溯生成组合

算法说明:
- 生成从n个元素中选取k个元素的所有组合 (C(n,k))
- 使用回溯系统地探索所有选择
- 在每一步，选择包含或排除一个元素
- 仅探索 >= 当前位置的元素以避免重复
- 当选择了k个元素或枚举了所有选项时回溯

时间复杂度：O(C(n,k) * k)，其中C(n,k)是组合数
空间复杂度：O(k)，用于递归深度和当前组合

示例:
    combine(4, 2) 返回 [
        [1, 2], [1, 3], [1, 4],
        [2, 3], [2, 4], [3, 4]
    ]
"""

def combine(n, k):
    """
    生成从1到n中选取k个元素的所有组合.

    参数:
        n: 元素的总数（1到n）
        k: 每个组合的大小

    返回:
        列表的列表，每个包含一个组合
    """
    result = []

    def backtrack(start, current_combination):
        """
        递归地构建组合.

        参数:
            start: 开始的数字（避免重复）
            current_combination: 当前要构建的组合
        """
        # 基本情况：组合已完成
        if len(current_combination) == k:
            result.append(current_combination[:])
            return

        # 尝试从start到n的每个数字
        for num in range(start, n + 1):
            # 选择：将num添加到当前组合
            current_combination.append(num)

            # 探索：构建组合的其余部分
            # 仅数字 >= num+1 以避免重复
            backtrack(num + 1, current_combination)

            # 取消选择：移除num以进行回溯
            current_combination.pop()

    backtrack(1, [])
    return result


def combine_optimized(n, k):
    """
    使用提前终止的优化组合.
    剪枝不可能产生k个元素的分支.

    Time Complexity: O(C(n,k) * k)
    Space Complexity: O(k)
    """
    result = []

    def backtrack(start, current_combination):
        # 基本情况：组合已完成
        if len(current_combination) == k:
            result.append(current_combination[:])
            return

        # 优化：提前终止
        # 剩余需要的位置：k - len(current_combination)
        # 可用的元素：n - start + 1
        # 如果没有足够的可用元素，则停止
        remaining = k - len(current_combination)
        available = n - start + 1
        if available < remaining:
            return

        # 尝试从start到n的每个数字
        for num in range(start, n + 1):
            current_combination.append(num)
            backtrack(num + 1, current_combination)
            current_combination.pop()

    backtrack(1, [])
    return result


# 测试用例
if __name__ == "__main__":
    print("=== Combination Backtracking Test Cases ===\n")

    # 测试用例 1: combine(4, 2)
    print("Test 1: combine(4, 2)")
    result1 = combine(4, 2)
    print(f"Result (count={len(result1)}):")
    for combo in result1:
        print(f"  {combo}")
    print()

    # 测试用例 2: combine(3, 1)
    print("Test 2: combine(3, 1)")
    result2 = combine(3, 1)
    print(f"Result (count={len(result2)}):")
    for combo in result2:
        print(f"  {combo}")
    print()

    # 测试用例 3: combine(3, 3)
    print("Test 3: combine(3, 3)")
    result3 = combine(3, 3)
    print(f"Result (count={len(result3)}):")
    for combo in result3:
        print(f"  {combo}")
    print()

    # 测试用例 4: combine(5, 3)
    print("Test 4: combine(5, 3)")
    result4 = combine(5, 3)
    print(f"Result (count={len(result4)}):")
    for combo in result4:
        print(f"  {combo}")
    print()

    # 测试用例 5: combine(6, 2) using optimized
    print("Test 5: combine_optimized(6, 2)")
    result5 = combine_optimized(6, 2)
    print(f"Result (count={len(result5)}):")
    for combo in result5:
        print(f"  {combo}")
    print()

    # 测试用例 6: combine_optimized(5, 4)
    print("Test 6: combine_optimized(5, 4)")
    result6 = combine_optimized(5, 4)
    print(f"Result (count={len(result6)}):")
    for combo in result6:
        print(f"  {combo}")
