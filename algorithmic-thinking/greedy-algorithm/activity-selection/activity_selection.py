
"""
活动选择问题 - 贪心算法选最多不重叠活动

算法思路：
- 给定一组活动，每个活动有开始和结束时间
- 选择最多数量的互不重叠活动
- 策略：按结束时间排序，贪心选择结束最早的活动

时间复杂度：O(n log n)（排序）
空间复杂度：O(1)（不计输出）

关键：每次选结束最早的活动，为后续留出最多空间
证明：任何最优解都可以替换为结束最早的活动而不影响可行性
"""


def activity_selection(activities):
    """
    选择最多数量的不重叠活动

    参数:
        activities: 活动列表，每个元素为 (开始时间, 结束时间)

    返回:
        选中的活动列表

    示例:
        >>> activities = [(1, 3), (2, 5), (4, 6), (6, 7), (5, 8), (8, 9)]
        >>> result = activity_selection(activities)
        >>> len(result)
        4
    """
    if not activities:
        return []

    # 按结束时间升序排序，贪心选择结束最早的活动
    sorted_activities = sorted(activities, key=lambda x: x[1])  # 贪心关键
    selected = [sorted_activities[0]]  # 先选第一个活动
    last_end_time = sorted_activities[0][1]
    # 遍历剩余活动，选择与已选活动不重叠的
    for i in range(1, len(sorted_activities)):
        start_time, end_time = sorted_activities[i]
        # 如果当前活动开始时间不早于上一个已选活动的结束时间，则可选
        if start_time >= last_end_time:
            selected.append(sorted_activities[i])
            last_end_time = end_time
    return selected


def activity_count(activities):
    """
    返回最多不重叠活动的数量

    参数:
        activities: 活动列表 (开始时间, 结束时间)

    返回:
        选中活动的数量
    """
    return len(activity_selection(activities))


def compare_with_brute_force(activities):
    """
    与暴力法对比，验证贪心解是否最优（仅适合小规模输入）
    """
    from itertools import combinations
    if not activities:
        return True
    greedy_count = len(activity_selection(activities))
    # 枚举所有子集，找最大不重叠活动数
    max_valid = 0
    for r in range(len(activities), 0, -1):
        for subset in combinations(activities, r):
            sorted_subset = sorted(subset, key=lambda x: x[1])
            valid = True
            for j in range(1, len(sorted_subset)):
                if sorted_subset[j][0] < sorted_subset[j-1][1]:
                    valid = False
                    break
            if valid:
                max_valid = max(max_valid, len(subset))
                if max_valid > greedy_count:
                    return False
        if max_valid >= greedy_count:
            break
    return max_valid == greedy_count



if __name__ == "__main__":
    print("=" * 60)
    print("活动选择问题 - 贪心算法")
    print("=" * 60)
    # 测试用例 1: 基本重叠活动
    print("\n[测试1] 基本重叠活动")
    activities1 = [(1, 3), (2, 5), (4, 6), (6, 7), (5, 8), (8, 9)]
    result1 = activity_selection(activities1)
    print(f"输入活动: {activities1}")
    print(f"选中活动: {result1}")
    print(f"数量: {len(result1)}")
    print(f"最优: {compare_with_brute_force(activities1)}")
    # 测试用例 2: 全部兼容
    print("\n[测试2] 全部活动不重叠")
    activities2 = [(1, 2), (2, 3), (3, 4), (4, 5)]
    result2 = activity_selection(activities2)
    print(f"输入活动: {activities2}")
    print(f"选中活动: {result2}")
    print(f"数量: {len(result2)}")
    # 测试用例 3: 全部重叠
    print("\n[测试3] 全部活动重叠")
    activities3 = [(1, 10), (2, 9), (3, 8), (4, 7)]
    result3 = activity_selection(activities3)
    print(f"输入活动: {activities3}")
    print(f"选中活动: {result3}")
    print(f"数量: {len(result3)}")
    # 测试用例 4: 单个活动
    print("\n[测试4] 单个活动")
    activities4 = [(5, 10)]
    result4 = activity_selection(activities4)
    print(f"输入活动: {activities4}")
    print(f"选中活动: {result4}")
    print(f"数量: {len(result4)}")
    # 测试用例 5: 空输入
    print("\n[测试5] 空输入")
    activities5 = []
    result5 = activity_selection(activities5)
    print(f"输入活动: {activities5}")
    print(f"选中活动: {result5}")
    print(f"数量: {len(result5)}")
    # 测试用例 6: 复杂调度
    print("\n[测试6] 复杂调度场景")
    activities6 = [(0, 6), (1, 4), (3, 5), (5, 7), (8, 9), (5, 9)]
    result6 = activity_selection(activities6)
    print(f"输入活动: {activities6}")
    print(f"选中活动: {result6}")
    print(f"数量: {len(result6)}")
    print(f"最优: {compare_with_brute_force(activities6)}")
