"""
贪心算法 - 每步选择当前最优

贪心策略：
- 每一步都做出当前最优选择
- 不会回溯前面的选择
- 时间和空间效率通常很高

注意：贪心不总是能得到全局最优解
"""


# 示例1：活动选择问题（贪心思想，每次选最早结束的活动）
def activity_selection(activities):
    """
    选择最多的互不冲突活动
    活动格式: (开始时间, 结束时间)
    时间复杂度: O(n log n)
    """
    # 按结束时间升序排序，保证每次都选最早结束的活动
    activities.sort(key=lambda x: x[1])  # 关键贪心策略
    selected = [activities[0]]  # 先选第一个活动
    for i in range(1, len(activities)):
        # 如果当前活动的开始时间不早于上一个已选活动的结束时间，则可以选择
        if activities[i][0] >= selected[-1][1]:
            selected.append(activities[i])
    return selected


# 示例2：零钱兑换（贪心，优先用大面额）
def coin_change_greedy(coins, amount):
    """
    用最少硬币凑出目标金额（贪心解法，不一定最优）
    时间复杂度: O(n log n)
    """
    coins.sort(reverse=True)  # 先按面额从大到小排序
    count = 0
    for coin in coins:
        # 尽量多用当前面额的硬币
        while amount >= coin:
            amount -= coin
            count += 1
    # 如果刚好凑出，返回硬币数，否则返回-1
    return count if amount == 0 else -1


# 示例3：删除k位得到最大数（贪心+单调栈）
def maximize_number(num_str, k):
    """
    删除k个数字，使剩下的数字组成最大数
    """
    stack = []  # 单调递减栈，保证高位尽量大
    to_delete = k
    for digit in num_str:
        # 如果当前数字比栈顶大且还有删除名额，则弹出栈顶
        while to_delete > 0 and stack and stack[-1] < digit:
            stack.pop()
            to_delete -= 1
        stack.append(digit)
    # 如果还没删够k个，从末尾去掉
    if to_delete > 0:
        stack = stack[:-to_delete]
    return ''.join(stack)


# 示例4：跳跃游戏（贪心，每次维护最远可达位置）
def can_jump(nums):
    """
    判断是否能跳到最后一个位置
    每个位置i最多能跳nums[i]步
    """
    max_reach = 0  # 当前能到达的最远下标
    for i in range(len(nums)):
        if i > max_reach:
            # 如果当前位置已经超过最远可达，说明无法到达
            return False
        # 更新最远可达位置
        max_reach = max(max_reach, i + nums[i])
    return True


if __name__ == "__main__":
    print("=== 贪心算法示例 ===\n")
    # 活动选择问题
    print("1. 活动选择问题")
    activities = [(1, 3), (2, 5), (4, 6), (6, 7), (5, 8), (8, 9)]
    result = activity_selection(activities)
    print(f"选择的活动: {result}\n")
    # 零钱兑换
    print("2. 零钱兑换（贪心）")
    print(f"金额 11，硬币 [1,7,10]: {coin_change_greedy([1, 7, 10], 11)} 枚\n")
    # 跳跃游戏
    print("3. 跳跃游戏")
    nums = [2, 3, 1, 1, 4]
    print(f"数组 {nums}，能到达末位: {can_jump(nums)}")
