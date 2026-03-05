"""
使用回溯生成排列

算法说明:
- 使用回溯生成列表的所有排列
- 在每一步，为当前排列会归选择一个未使用的元素
- 当使用所有元素时，我们就有一个完整的排列
- 通过移除上一个元素并尝试下一个选项来回溯

时间复杂度：O(n! * n) - n! 个排列，每个需要 O(n) 时间复制
空间复杂度：O(n) - 递归深度（不计算输出）

示例:
    permute([1, 2, 3]) 返回 [
        [1, 2, 3], [1, 3, 2], [2, 1, 3],
        [2, 3, 1], [3, 1, 2], [3, 2, 1]
    ]
"""

def permute(nums):
    """
    使用回溯生成 nums 的所有排列。

    参数:
        nums: 待排列的元素列表

    返回:
        二维列表，每个内层列表是一个排列
    """
    result = []

    def backtrack(current_permutation, remaining):
        """
        括最的构建排列。

        参数:
            current_permutation: 正在构建的子排列
            remaining: 未使用的元素列表
        """
        # 基础情况：所有元素都已使用，添加到结果中
        if not remaining:
            result.append(current_permutation[:])
            return

        # 尝试每个剩余元素作为下一个元素
        for i in range(len(remaining)):
            # 选择：将 remaining[i] 添加到当前排列
            current_permutation.append(remaining[i])

            # 探索：递归构建排列的余下部分
            new_remaining = remaining[:i] + remaining[i+1:]
            backtrack(current_permutation, new_remaining)

            # 撤销：移除元素以回溯
            current_permutation.pop()

    backtrack([], nums)
    return result


def permute_optimized(nums):
    """
    优化的排列数据使用原位置交换。
    会修改源数组，以节省存储空间。

    时间复杂度：O(n! * n)
    空间复杂度：O(n)
    """
    result = []

    def backtrack(index):
        """
        原位置交换元素而不是创建新数组。

        参数:
            index: 孜开始排列的桟位置
        """
        # 基础情况：到达数组末尾
        if index == len(nums):
            result.append(nums[:])  # 添加当前排列的副本
            return

        # 尝试每个元素书什䆯下一个元素
        for i in range(index, len(nums)):
            # 选择：交换元素
            nums[index], nums[i] = nums[i], nums[index]

            # 探索：排列剩余部分
            backtrack(index + 1)

            # 撤销：交换回去
            nums[index], nums[i] = nums[i], nums[index]

    backtrack(0)
    return result


# 测试用例
if __name__ == "__main__":
    print("=== 排列回溯测试用例 ===\n")

    # 测试用例 1: 小列表
    print("测试 1: permute([1, 2, 3])")
    result1 = permute([1, 2, 3])
    print(f"结果（共 {len(result1)} 个）:")
    for perm in result1:
        print(f"  {perm}")
    print()

    # 测试用例 2: 两个元素
    print("测试 2: permute([1, 2])")
    result2 = permute([1, 2])
    print(f"结果（共 {len(result2)} 个）:")
    for perm in result2:
        print(f"  {perm}")
    print()

    # 测试用例 3: 单个元素
    print("测试 3: permute([1])")
    result3 = permute([1])
    print(f"结果（共 {len(result3)} 个）:")
    for perm in result3:
        print(f"  {perm}")
    print()

    # 测试用例 4: 优化的版本，4 个元素
    print("测试 4: permute_optimized([1, 2, 3, 4])")
    test_input = [1, 2, 3, 4]
    result4 = permute_optimized(test_input)
    print(f"结果（共 {len(result4)} 个）:")
    print(f"前 3 个排列: {result4[:3]}")
    print(f"后 3 个排列: {result4[-3:]}")
    print()

    # 测试用例 5: 字符串字符
    print("测试 5: permute(['A', 'B', 'C'])")
    result5 = permute(['A', 'B', 'C'])
    print(f"结果（共 {len(result5)} 个）:")
    for perm in result5:
        print(f"  {''.join(perm)}")