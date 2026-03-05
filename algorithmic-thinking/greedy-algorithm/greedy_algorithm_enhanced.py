"""
贪心算法（Greedy Algorithm）- 局部最优选择的艺术

核心思想：
- 每一步都选择当前看起来最优（最有利）的选择
- 不回溯去改变之前的决定，一步一步向前
- 贪心选择性质：全局最优解由一系列局部最优选择组成

贪心算法的三个要素（判断题目是否适用贪心）：
1. 贪心选择性质（Greedy Choice Property）
   - 当前局部最优选择能导向全局最优解
   
2. 最优子结构（Optimal Substructure）
   - 问题的最优解包含其子问题的最优解

3. 可行性（Feasibility）
   - 贪心选择不会违反约束条件

适用场景：
- 活动选择问题（选择最多互不重叠的活动）
- 霍夫曼编码（前缀码的最优编码）
- 分数背包（与 0/1 背包的对比）
- 任务调度问题
- 最小生成树（Kruskal/Prim 算法）
- 单源最短路（Dijkstra 算法）

注意：不是所有问题都适合贪心！
- 0/1 背包不能用贪心（需要动态规划）
- 全局最优可能由多个不同的局部选择组成
"""

# 问题 1: 活动选择问题 - 贪心的经典案例
def activity_selection(activities):
    """
    活动选择问题 - 选择最多的互不重叠活动
    
    问题描述：
    给定多个时间段内的活动，每个活动有开始时间和结束时间
    需要选择最多数量的互不重叠活动
    
    贪心策略：
    按结束时间排序，每次选择结束最早的活动
    这样能为后续活动留出最多时间空间
    
    时间复杂度: O(n log n)（主要用于排序）
    空间复杂度: O(n)
    
    参数:
        activities: 活动列表，每个元素是 (开始时间, 结束时间) 的元组
    
    返回:
        选中的活动列表
    
    示例:
        活动 = [(1,3), (2,5), (4,6), (6,7), (5,8), (8,9)]
        结果 = [(1,3), (4,6), (6,7), (8,9)]  （4个活动）
    """
    # 没有活动的边界情况
    if not activities:
        return []
    
    # 贪心步骤 1：按结束时间排序
    # 这是贪心的关键：确保优先考虑结束最早的活动
    sorted_activities = sorted(activities, key=lambda x: x[1])
    
    # 初始化结果：第一个活动（结束时间最早）一定会被选中
    selected = [sorted_activities[0]]
    last_end_time = sorted_activities[0][1]
    
    # 贪心步骤 2：遍历剩余活动，选择与已选活动不重叠的
    for i in range(1, len(sorted_activities)):
        start, end = sorted_activities[i]
        # 如果当前活动的开始时间 >= 上一个活动的结束时间，则不重叠
        if start >= last_end_time:
            # 贪心选择：选中这个活动
            selected.append((start, end))
            # 更新最后活动的结束时间
            last_end_time = end
    
    return selected

# 问题 2: 分数背包问题
def fractional_knapsack(weights, values, capacity):
    """
    分数背包问题 - 可以买物品的一部分
    
    与 0/1 背包的对比：
    - 0/1 背包：每个物品要么全选，要么不选
    - 分数背包：可以选择物品的一部分
    
    贪心策略：
    根据价值密度（价值/重量）排序，优先选择密度高的物品
    如果最后一个物品放不下，就选一部分
    
    时间复杂度: O(n log n)（排序）
    空间复杂度: O(n)
    
    参数:
        weights: 物品重量列表
        values: 物品价值列表
        capacity: 背包容量
    
    返回:
        值：背包能放入的最大价值（可能是小数）
    
    示例:
        weights = [2, 3, 4]
        values = [12, 8, 8]
        capacity = 5
        按密度排序：[2(密度6), 3(密度2.67), 4(密度2)]
        选 2 个单位（价值12），再选 3 个物品的 3/3（价值8），总价值 20
    """
    # 创建物品对象，包含重量、价值、密度
    items = []
    for i in range(len(weights)):
        # 计算价值密度（每单位重量的价值）
        density = values[i] / weights[i]
        items.append({
            'weight': weights[i],
            'value': values[i],
            'density': density,
            'index': i
        })
    
    # 贪心步骤 1：按价值密度降序排序
    # 密度高的物品优先放入背包
    items.sort(key=lambda x: x['density'], reverse=True)
    
    total_value = 0.0
    remaining_capacity = capacity
    
    # 贪心步骤 2：依次尝试放入每个物品
    for item in items:
        # 如果当前物品能完全放入
        if item['weight'] <= remaining_capacity:
            # 贪心选择：选择这个物品
            total_value += item['value']
            remaining_capacity -= item['weight']
        else:
            # 当前物品不能完全放入，放一部分
            # 这正是分数背包与 0/1 背包的区别
            fraction = remaining_capacity / item['weight']
            total_value += item['value'] * fraction
            remaining_capacity = 0  # 背包满了
            break  # 不需要继续考虑其他物品
    
    return total_value

# 问题 3: 跳跃游戏
def can_jump(nums):
    """
    跳跃游戏 - 判断是否能从起点跳到末尾
    
    问题描述：
    数组代表当前位置，值代表最多能向前跳的步数
    判断是否能通过跳跃到达最后一个位置
    
    贪心策略：
    跟踪能到达的最远位置
    如果当前位置超过最远位置，说明无法继续
    
    时间复杂度: O(n)（单次遍历）
    空间复杂度: O(1)
    
    参数:
        nums: 每个位置最多能跳跃的步数
    
    返回:
        True 如果能到达末尾，False 否则
    
    示例:
        nums = [2, 3, 1, 1, 4]
        从位置 0 跳 1 步到位置 1，再跳 3 步到位置 4 → True
        
        nums = [3, 2, 1, 0, 4]
        无论怎么跳，最终都会落在位置 3 的 0 处，无法继续 → False
    """
    # 记录能到达的最远位置
    max_reach = 0
    
    # 遍历数组中的每个位置
    for i in range(len(nums)):
        # 如果当前位置超过能到达的最远位置，说明无法继续
        if i > max_reach:
            return False
        
        # 更新能到达的最远位置
        # 从当前位置 i 能跳至最远 i + nums[i]
        max_reach = max(max_reach, i + nums[i])
        
        # 如果已经能到达末尾，直接返回 True
        if max_reach >= len(nums) - 1:
            return True
    
    return False

# 问题 4: 用最少数量的箭射爆气球
def find_min_arrow_shots(balloons):
    """
    用最少箭数射爆所有气球
    
    问题描述：
    每个气球有起始和结束位置，一箭可以射爆所有其在路径中的气球
    找最少需要多少箭
    
    贪心策略：
    按结束位置排序，选择覆盖范围最窄的气球
    一箭射向该气球的末尾，可以射爆后续所有重叠的气球
    
    时间复杂度: O(n log n)
    空间复杂度: O(1)
    
    参数:
        balloons: 气球列表，每个元素是 (起始, 结束) 的元组
    
    返回:
        最少需要的箭数
    
    示例:
        balloons = [[10,16],[2,8],[1,6],[7,12]]
        排序后: [[1,6],[2,8],[7,12],[10,16]]
        一箭射向 6，爆掉 [1,6] 和 [2,8]
        一箭射向 12，爆掉 [7,12]
        一箭射向 16，爆掉 [10,16]
        总共 3 箭
    """
    if not balloons:
        return 0
    
    # 按结束位置排序
    balloons.sort(key=lambda x: x[1])
    
    arrows = 1  # 至少需要一箭
    last_shot_pos = balloons[0][1]  # 第一箭射向第一个气球的末尾
    
    # 遍历剩余气球
    for i in range(1, len(balloons)):
        start, end = balloons[i]
        
        # 如果当前气球的起始位置超过上一箭的位置，说明不重叠
        # 需要一支新箭
        if start > last_shot_pos:
            arrows += 1
            last_shot_pos = end  # 新箭射向当前气球的末尾
    
    return arrows

# 问题 5: 任务调度 - 优先完成截止日期近的任务
def schedule_tasks(tasks):
    """
    任务调度问题 - 最大化完成的优先级任务
    
    问题描述：
    每个任务有截止日期和优先级
    找调度方案使得尽可能多的高优先级任务在截止期前完成
    
    贪心策略：
    按优先级降序排列任务
    对每个任务，尽量在其截止日期前安排
    
    时间复杂度: O(n² ) （排序 + 调度）
    空间复杂度: O(n)
    
    参数:
        tasks: 任务列表，每个元素是 (截止日期, 优先级) 的元组
    
    返回:
        完成的总优先级
    
    示例:
        tasks = [(4, 20), (1, 10), (1, 40), (1, 30)]
        最优调度能完成优先级 20+40+30 = 90
    """
    if not tasks:
        return 0
    
    # 按优先级降序排列（高优先级任务优先）
    tasks.sort(key=lambda x: x[1], reverse=True)
    
    # 记录每个时间槽是否被占用
    max_deadline = max(task[0] for task in tasks)
    schedule = [False] * (max_deadline + 1)
    
    total_priority = 0
    
    # 对每个任务，尝试在其截止日期前找到空闲时间槽
    for deadline, priority in tasks:
        # 从截止日期开始，向前查找空闲时间槽
        # 这在贪心中很关键：为高优先级任务保留空间
        for time_slot in range(deadline, 0, -1):
            if not schedule[time_slot]:
                # 找到空闲时间槽，安排这个任务
                schedule[time_slot] = True
                total_priority += priority
                break
    
    return total_priority

# 测试代码
if __name__ == "__main__":
    print("=" * 70)
    print("贪心算法 - 完整中文注释版本")
    print("=" * 70)
    
    # 测试活动选择
    print("\n1. 活动选择问题")
    activities = [(1,3), (2,5), (4,6), (6,7), (5,8), (8,9)]
    selected = activity_selection(activities)
    print(f"   活动: {activities}")
    print(f"   所有活动: {activities}")
    print(f"   选中活动: {selected}")
    print(f"   最多活动数: {len(selected)}")
    
    # 测试分数背包
    print("\n2. 分数背包问题")
    weights = [2, 3, 4]
    values = [12, 8, 8]
    capacity = 5
    max_value = fractional_knapsack(weights, values, capacity)
    print(f"   重量: {weights}")
    print(f"   价值: {values}")
    print(f"   容量: {capacity}")
    print(f"   最大价值: {max_value:.2f}")
    
    # 测试跳跃游戏
    print("\n3. 跳跃游戏")
    nums1 = [2, 3, 1, 1, 4]
    nums2 = [3, 2, 1, 0, 4]
    print(f"   输入: {nums1} → 能否到达末尾: {can_jump(nums1)}")
    print(f"   输入: {nums2} → 能否到达末尾: {can_jump(nums2)}")
    
    # 测试射气球
    print("\n4. 用箭射爆气球")
    balloons = [[10,16],[2,8],[1,6],[7,12]]
    min_arrows = find_min_arrow_shots(balloons)
    print(f"   气球: {balloons}")
    print(f"   最少箭数: {min_arrows}")
    
    # 测试任务调度
    print("\n5. 任务调度")
    tasks = [(4, 20), (1, 10), (1, 40), (1, 30)]
    total_priority = schedule_tasks(tasks)
    print(f"   任务(截止日期, 优先级): {tasks}")
    print(f"   完成的总优先级: {total_priority}")
    
    print("\n" + "=" * 70)
