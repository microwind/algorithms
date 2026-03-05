
"""
跳跃游戏（贪心算法）

算法思路：
- 给定一个数组，每个元素表示当前位置最大可跳跃步数
- 判断能否到达最后一个位置
- 贪心策略：每一步记录当前能到达的最远位置
- 如果当前位置超过了最远可达位置，则无法到达

时间复杂度：O(n)
空间复杂度：O(1)

关键：每一步都维护最远可达位置max_reach，如果某个位置无法到达则返回False

贪心选择：不需要决定每步跳多远，只需判断最远可达位置是否能继续前进

示例：
nums = [2, 3, 1, 1, 4]
    位置0: 可达2
    位置1: 可达4（更新max_reach）
    能到达最后一位 → True
nums = [3, 2, 1, 0, 4]
    位置0: 可达3
    位置1: 可达3
    位置2: 可达3
    位置3: 可达3
    无法到达最后一位 → False
"""

from typing import List


def can_jump(nums: List[int]) -> bool:
    """
    判断能否到达最后一个位置

    参数:
        nums: 每个元素为当前位置最大可跳跃步数的数组

    返回:
        能到达返回True，否则返回False

    示例:
        >>> can_jump([2, 3, 1, 1, 4])
        True
        >>> can_jump([3, 2, 1, 0, 4])
        False
    """
    if not nums or len(nums) <= 1:
        return True
    max_reach = 0  # 当前能到达的最远位置
    for i in range(len(nums)):
        # 如果当前位置超过了最远可达位置，则无法到达
        if i > max_reach:
            return False
        # 更新最远可达位置
        max_reach = max(max_reach, i + nums[i])
        # 如果已经能到达最后一位，提前返回True
        if max_reach >= len(nums) - 1:
            return True
    return max_reach >= len(nums) - 1


def jump_game_steps(nums: List[int]) -> tuple:
    """
    返回能否到达终点及最少跳跃次数

    参数:
        nums: 每个元素为当前位置最大可跳跃步数的数组

    返回:
        (能否到达终点, 最少跳跃次数)
    """
    if not nums or len(nums) <= 1:
        return (True, 0)

    # Check if we can reach the end
    max_reach = 0
    for i in range(len(nums)):
        if i > max_reach:
            return (False, -1)
        max_reach = max(max_reach, i + nums[i])
        if max_reach >= len(nums) - 1:
            break

    can_reach = max_reach >= len(nums) - 1

    if not can_reach:
        return (False, -1)

    # Find minimum jumps needed (greedy)
    jumps = 0
    current_end = 0
    farthest = 0

    for i in range(len(nums) - 1):
        farthest = max(farthest, i + nums[i])

        if i == current_end:
            jumps += 1
            current_end = farthest

    return (True, jumps)


def jump_game_path(nums: List[int]) -> List[int]:
    """
    返回到达终点的跳跃路径（索引序列）

    参数:
        nums: 每个元素为当前位置最大可跳跃步数的数组

    返回:
        跳跃路径索引列表，无法到达则返回空列表
    """
    if not nums:
        return []

    if len(nums) == 1:
        return [0]

    # First check if we can reach the end
    max_reach = 0
    for i in range(len(nums)):
        if i > max_reach:
            return []
        max_reach = max(max_reach, i + nums[i])
        if max_reach >= len(nums) - 1:
            break

    # Greedy path construction: always jump as far as possible
    path = [0]
    current_pos = 0

    while current_pos < len(nums) - 1:
        max_next_pos = current_pos
        for next_pos in range(current_pos + 1, min(current_pos + nums[current_pos] + 1, len(nums))):
            # Greedy: choose the position that can reach farthest
            if next_pos + nums[next_pos] > max_next_pos + nums[max_next_pos]:
                max_next_pos = next_pos

        if max_next_pos == current_pos:
            # Can't make progress (shouldn't happen if can_jump returned True)
            return []

        path.append(max_next_pos)
        current_pos = max_next_pos

    return path


def analyze_jump_game(nums: List[int]) -> dict:
    """
    综合分析跳跃游戏问题

    参数:
        nums: 每个元素为当前位置最大可跳跃步数的数组

    返回:
        分析结果字典
    """
    can_reach, min_jumps = jump_game_steps(nums)
    path = jump_game_path(nums) if can_reach else []

    return {
        'can_reach': can_reach,
        'min_jumps': min_jumps,
        'path': path,
        'length': len(path) - 1 if path else -1
    }



if __name__ == "__main__":
    print("=" * 60)
    print("跳跃游戏 - 贪心算法")
    print("=" * 60)
    # 测试用例 1: 可到达
    print("\n[测试1] 可到达")
    nums1 = [2, 3, 1, 1, 4]
    result1 = can_jump(nums1)
    print(f"输入: {nums1}")
    print(f"能到达终点: {result1}")
    analysis1 = analyze_jump_game(nums1)
    print(f"最少跳跃次数: {analysis1['min_jumps']}, 路径: {analysis1['path']}")
    # 测试用例 2: 不可到达
    print("\n[测试2] 不可到达")
    nums2 = [3, 2, 1, 0, 4]
    result2 = can_jump(nums2)
    print(f"输入: {nums2}")
    print(f"能到达终点: {result2}")
    # 测试用例 3: 单元素
    print("\n[测试3] 单元素")
    nums3 = [0]
    result3 = can_jump(nums3)
    print(f"输入: {nums3}")
    print(f"能到达终点: {result3}")
    # 测试用例 4: 除最后一位外全为零
    print("\n[测试4] 除最后一位外全为零")
    nums4 = [0, 1]
    result4 = can_jump(nums4)
    print(f"输入: {nums4}")
    print(f"能到达终点: {result4}")
    # 测试用例 5: 跳跃步数很大
    print("\n[测试5] 跳跃步数很大")
    nums5 = [10, 0, 0, 0, 0]
    result5 = can_jump(nums5)
    print(f"输入: {nums5}")
    print(f"能到达终点: {result5}")
    analysis5 = analyze_jump_game(nums5)
    print(f"最少跳跃次数: {analysis5['min_jumps']}, 路径: {analysis5['path']}")
    # 测试用例 6: 需要多次跳跃
    print("\n[测试6] 需要多次跳跃")
    nums6 = [2, 3, 1, 1, 1]
    result6 = can_jump(nums6)
    print(f"输入: {nums6}")
    print(f"能到达终点: {result6}")
    analysis6 = analyze_jump_game(nums6)
    print(f"最少跳跃次数: {analysis6['min_jumps']}, 路径: {analysis6['path']}")
    # 测试用例 7: 倒数第二步被阻断
    print("\n[测试7] 倒数第二步被阻断")
    nums7 = [1, 0, 1, 0]
    result7 = can_jump(nums7)
    print(f"输入: {nums7}")
    print(f"能到达终点: {result7}")
    # 测试用例 8: 两元素数组
    print("\n[测试8] 两元素数组")
    nums8 = [2, 3]
    result8 = can_jump(nums8)
    print(f"输入: {nums8}")
    print(f"能到达终点: {result8}")
    analysis8 = analyze_jump_game(nums8)
    print(f"最少跳跃次数: {analysis8['min_jumps']}, 路径: {analysis8['path']}")
    # 测试用例 9: 大数组递减
    print("\n[测试9] 大数组递减")
    nums9 = [5, 4, 3, 2, 1, 0]
    result9 = can_jump(nums9)
    print(f"输入: {nums9}")
    print(f"能到达终点: {result9}")
    analysis9 = analyze_jump_game(nums9)
    print(f"最少跳跃次数: {analysis9['min_jumps']}, 路径: {analysis9['path']}")
    # 测试用例 10: 复杂可达场景
    print("\n[测试10] 复杂可达场景")
    nums10 = [2, 5, 0, 0]
    result10 = can_jump(nums10)
    print(f"输入: {nums10}")
    print(f"能到达终点: {result10}")
    analysis10 = analyze_jump_game(nums10)
    print(f"最少跳跃次数: {analysis10['min_jumps']}, 路径: {analysis10['path']}")
