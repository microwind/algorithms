"""
贪心算法 - 每步选择当前最优

贪心策略：
- 每一步都做出当前最优选择
- 不会回溯前面的选择
- 时间和空间效率通常很高

注意：贪心不总是能得到全局最优解
"""

# 例1: 活动选择问题
def activity_selection(activities):
    """
    选择最多的兼容活动
    活动格式: (start_time, end_time)
    时间复杂度: O(n log n)
    """
    # 按结束时间排序
    activities.sort(key=lambda x: x[1])
    
    selected = [activities[0]]
    for i in range(1, len(activities)):
        if activities[i][0] >= selected[-1][1]:
            selected.append(activities[i])
    
    return selected

# 例2: 零钱兑换（贪心）
def coin_change_greedy(coins, amount):
    """
    最少硬币数（贪心解法，不一定最优）
    时间复杂度: O(n log n)
    """
    coins.sort(reverse=True)
    count = 0
    
    for coin in coins:
        while amount >= coin:
            amount -= coin
            count += 1
    
    return count if amount == 0 else -1

# 例3: 分割数字字符串得到最大值
def maximize_number(num_str, k):
    """删除 k 个数字，使得剩余数字组成的数最大"""
    stack = []
    to_delete = k
    
    for digit in num_str:
        while to_delete > 0 and stack and stack[-1] < digit:
            stack.pop()
            to_delete -= 1
        stack.append(digit)
    
    if to_delete > 0:
        stack = stack[:-to_delete]
    
    return ''.join(stack)

# 例4: 跳跃游戏
def can_jump(nums):
    """
    判断是否能跳到最后一个位置
    每个位置 i 最多能跳 nums[i] 步
    """
    max_reach = 0
    for i in range(len(nums)):
        if i > max_reach:
            return False
        max_reach = max(max_reach, i + nums[i])
    return True

if __name__ == "__main__":
    print("=== 贪心算法示例 ===\n")
    
    # 活动选择
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
