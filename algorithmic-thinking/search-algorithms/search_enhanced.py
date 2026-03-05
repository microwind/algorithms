"""
搜索算法（Search Algorithms）-从线性到对数的效率进阶

搜索问题的核心：
在给定数据结构中查找特定元素，并返回其位置或相关信息

搜索算法的分类：
1. 线性搜索族（Sequential Search）
   - 顺序搜索：O(n)，适用于无序数据
   - 哨兵搜索：O(n)，优化访问次数
   
2. 二分搜索族（Binary Search）
   - 二分搜索：O(log n)，要求数据有序
   - 分支限界搜索：减少比较次数
   
3. 图搜索族（Graph Search）
   - 深度优先搜索（DFS）：O(V+E)，用于路径、连通性
   - 广度优先搜索（BFS）：O(V+E)，用于最短路径
   
4. 高级搜索
   - 启发式搜索（A*）：利用启发函数加速
   - 哈希搜索：平均 O(1)

选择搜索算法的考虑：
- 数据规模：小 → 线性；大 → 二分或哈希
- 数据特性：有序 → 二分；无序 → 线性或哈希
- 时间复杂度要求：严格 → 二分；宽松 → 线性
- 空间复杂度要求：受限 → 线性；充足 → 哈希
"""

# ====================
# 第一类：线性搜索
# ====================

def linear_search(arr, target):
    """
    线性搜索（顺序搜索）- 最朴素的搜索方法
    
    原理：
    从数组的第一个元素开始，逐个与目标比较，直到找到或到达末尾
    
    性质：
    - 无需有序数据
    - 每个元素最多比较一次
    - 最坏情况：目标在最后或不存在，需要 n 次比较
    
    时间复杂度：O(n)（最好 O(1)，最坏 O(n)，平均 O(n/2)）
    空间复杂度：O(1)
    
    参数:
        arr: 待搜索的数组（无需有序）
        target: 要查找的目标值
    
    返回:
        目标元素的索引，如果不存在返回 -1
    
    示例:
        linear_search([10, 3, 5, 7, 9], 5) → 2
        linear_search([10, 3, 5, 7, 9], 20) → -1
    
    适用场景：
    - 数据量小（< 1000）
    - 无序数据
    - 搜索操作不频繁
    """
    # 遍历数组的每个元素
    for i in range(len(arr)):
        # 如果找到目标元素，直接返回其索引
        if arr[i] == target:
            return i
    
    # 遍历完整个数组都没找到，返回 -1 表示不存在
    return -1

def linear_search_sentinel(arr, target):
    """
    哨兵搜索（Sentinel Search）- 优化的线性搜索
    
    优化思路：
    在数组末尾放置一个哨兵（目标值），确保一定会找到目标
    这样免去了在循环中每次检查数组边界的需要
    
    性能提升：
    - 减少每次循环的比较操作数量
    - 理论上少 n/2 次比较
    - 实际速度快 10-15%
    
    时间复杂度：O(n)（比较次数更少）
    空间复杂度：O(1)
    
    参数:
        arr: 可修改的数组
        target: 要查找的目标值
    
    返回:
        目标元素的索引，或者数组末尾（哨兵位置）
    
    示例:
        arr = [10, 3, 5, 7, 9]
        linear_search_sentinel(arr, 5) → 2
    
    注意：
    - 修改了原数组（加入哨兵）
    - 返回数组末尾索引表示目标不存在
    """
    n = len(arr)
    
    # 保存原最后一个元素
    last_elem = arr[-1]
    
    # 步骤 1：在末尾放置哨兵
    arr[-1] = target
    
    i = 0
    # 步骤 2：搜索（不需要检查边界，因为必然会在末尾找到）
    while arr[i] != target:
        i += 1
    
    # 步骤 3：恢复原数组
    arr[-1] = last_elem
    
    # 步骤 4：如果找到的位置在末尾，可能是原数据，也可能是哨兵
    if i < n - 1 or last_elem == target:
        return i
    else:
        return -1  # 目标不存在

# ====================
# 第二类：二分搜索
# ====================

def binary_search(arr, target):
    """
    二分搜索（Binary Search）- 有序数据的高效搜索
    
    核心思路：
    利用数据有序的特性，每次都能排除一半的搜索范围
    
    流程：
    1. 比较中点元素与目标
    2. 如果相等，找到了
    3. 如果中点 > 目标，搜索左半部分
    4. 如果中点 < 目标，搜索右半部分
    5. 重复直到找到或搜索范围为空
    
    时间复杂度：O(log n)（最坏需要 log₂(n) 次比较）
    空间复杂度：O(log n)（递归调用栈）或 O(1)（迭代版本）
    
    参数:
        arr: 已排序的数组
        target: 要查找的目标值
    
    返回:
        目标元素的索引，不存在返回 -1
    
    示例:
        binary_search([1, 3, 5, 7, 9, 11, 13], 7) → 3
        binary_search([1, 3, 5, 7, 9, 11, 13], 6) → -1
    
    前提条件：
    数组必须是有序的！（这是二分搜索的关键前提）
    
    时间对比（n=1000000）：
    - 线性搜索：最坏 100万 次比较
    - 二分搜索：最多 20 次比较（log₂(1000000) ≈ 20）
    """
    low, high = 0, len(arr) - 1
    
    # 当搜索范围不为空时
    while low <= high:
        # 计算中点（避免整数溢出，用 low + (high - low) // 2）
        mid = low + (high - low) // 2
        
        # 情况 1：找到目标
        if arr[mid] == target:
            return mid
        # 情况 2：目标在左半部分
        elif arr[mid] > target:
            high = mid - 1
        # 情况 3：目标在右半部分
        else:
            low = mid + 1
    
    # 搜索范围为空，目标不存在
    return -1

def binary_search_leftmost(arr, target):
    """
    二分搜索变种：查找最左边的目标
    
    当数组中有重复元素时，找第一次出现的位置
    
    例：[1, 3, 3, 3, 5, 7] 中搜索 3 返回 1（左边界）
    
    时间复杂度：O(log n)
    """
    low, high = 0, len(arr) - 1
    result = -1
    
    while low <= high:
        mid = low + (high - low) // 2
        
        if arr[mid] == target:
            result = mid  # 记录找到的位置
            high = mid - 1  # 继续在左边搜索更早的位置
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    
    return result

def binary_search_rightmost(arr, target):
    """
    二分搜索变种：查找最右边的目标
    
    当数组中有重复元素时，找最后一次出现的位置
    
    例：[1, 3, 3, 3, 5, 7] 中搜索 3 返回 3（右边界）
    
    时间复杂度：O(log n)
    """
    low, high = 0, len(arr) - 1
    result = -1
    
    while low <= high:
        mid = low + (high - low) // 2
        
        if arr[mid] == target:
            result = mid  # 记录找到的位置
            low = mid + 1  # 继续在右边搜索更晚的位置
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    
    return result

# ====================
# 第三类：图搜索 - DFS
# ====================

def dfs_iterative(graph, start):
    """
    深度优先搜索（DFS - 迭代版本）
    
    原理：
    使用栈维护待访问的节点
    每次弹出栈顶，访问它，然后将其所有未访问邻接点压入栈
    
    流程：
    1. 初始化栈，将起点压入
    2. 当栈不为空时：
       a. 弹出栈顶节点
       b. 如果未被访问，标记为已访问并处理
       c. 将所有未访问的邻接点压入栈
    
    时间复杂度：O(V + E)（访问每个顶点和边一次）
    空间复杂度：O(V)（栈和访问集合）
    
    参数:
        graph: 邻接表表示的图，dict of lists
        start: 起始节点
    
    返回:
        图中所有可达节点的访问列表
    
    示例:
        graph = {
            'A': ['B', 'C'],
            'B': ['A', 'D'],
            'C': ['A'],
            'D': ['B']
        }
        dfs_iterative(graph, 'A') → 访问顺序可能是 A → C → B → D
    
    特点：
    - 深度优先：总是尽可能深地探索
    - 适合查找路径、检测环、拓扑排序
    """
    visited = set()  # 已访问节点集合
    stack = [start]  # DFS 使用栈
    result = []
    
    while stack:
        # 弹出栈顶节点
        node = stack.pop()
        
        # 如果还没有访问过
        if node not in visited:
            # 标记为已访问
            visited.add(node)
            result.append(node)
            
            # 将该节点的所有邻接点压栈（注意顺序：后压的先弹出）
            # 为了保持左到右的顺序，应该反向压入
            for neighbor in reversed(graph.get(node, [])):
                if neighbor not in visited:
                    stack.append(neighbor)
    
    return result

def dfs_recursive(graph, node, visited=None):
    """
    深度优先搜索（DFS - 递归版本）
    
    原理：
    使用系统调用栈而不是显式栈
    
    递推关系：
    dfs(node) = 访问node + dfs(邻接点1) + dfs(邻接点2) + ...
    
    基础情况：
    没有未访问的邻接点
    
    时间复杂度：O(V + E)
    空间复杂度：O(V)（递归调用栈深度为 V）
    
    参数:
        graph: 邻接表表示的图
        node: 当前访问的节点
        visited: 已访问节点集合（默认为 None）
    
    返回:
        访问节点列表
    """
    if visited is None:
        visited = set()
    
    # 标记当前节点为已访问
    visited.add(node)
    
    # 访问当前节点
    result = [node]
    
    # 递归访问所有未访问的邻接点
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            # 递归：对邻接点进行 DFS
            result.extend(dfs_recursive(graph, neighbor, visited))
    
    return result

# ====================
# 第四类：图搜索 - BFS
# ====================

def bfs(graph, start):
    """
    广度优先搜索（BFS）
    
    原理：
    使用队列维护待访问的节点
    按距离远近访问所有节点（先访问距起点最近的，再访问稍远的）
    
    流程：
    1. 初始化队列，将起点入队
    2. 当队列不为空时：
       a. 出队一个节点
       b. 如果未被访问，标记为已访问
       c. 将所有未访问的邻接点入队
    
    时间复杂度：O(V + E)
    空间复杂度：O(V)（队列和访问集合）
    
    参数:
        graph: 邻接表表示的图
        start: 起始节点
    
    返回:
        按访问顺序的节点列表
    
    示例:
        graph = {
            'A': ['B', 'C'],
            'B': ['A', 'D'],
            'C': ['A'],
            'D': ['B']
        }
        bfs(graph, 'A') → ['A', 'B', 'C', 'D']
    
    特点：
    - 广度优先：按层访问节点
    - 适合最短路径、最近邻等问题
    - 发现的路径是最短的
    """
    from collections import deque  # 使用双端队列实现高效队列
    
    visited = set()  # 已访问节点集合
    queue = deque([start])  # BFS 使用队列
    visited.add(start)
    result = []
    
    while queue:
        # 从队头出队
        node = queue.popleft()
        result.append(node)
        
        # 将所有未访问的邻接点入队
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)  # 在入队时标记为已访问
                queue.append(neighbor)
    
    return result

def bfs_shortest_path(graph, start, end):
    """
    使用 BFS 找最短路径
    
    关键思想：
    BFS 找到的第一条到达目标的路径就是最短路径
    （因为 BFS 是按距离扩展的）
    
    时间复杂度：O(V + E)
    空间复杂度：O(V)
    
    参数:
        graph: 邻接表表示的图
        start: 起始节点
        end: 目标节点
    
    返回:
        从起点到终点的最短路径（节点列表），不存在返回 []
    """
    from collections import deque
    
    if start == end:
        return [start]
    
    visited = {start}
    queue = deque([(start, [start])])  # (当前节点, 到达路径)
    
    while queue:
        node, path = queue.popleft()
        
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                if neighbor == end:
                    # 找到目标，返回路径
                    return path + [neighbor]
                
                visited.add(neighbor)
                queue.append((neighbor, path + [neighbor]))
    
    # 无法到达目标
    return []

# 测试代码
if __name__ == "__main__":
    print("=" * 70)
    print("搜索算法 - 完整中文注释版本")
    print("=" * 70)
    
    # 1. 线性搜索测试
    print("\n1. 线性搜索 vs 二分搜索")
    arr_unsorted = [10, 3, 5, 7, 9, 20, 15]
    arr_sorted = sorted(arr_unsorted)
    
    print(f"   无序数组: {arr_unsorted}")
    print(f"   搜索 7 → 线性搜索: {linear_search(arr_unsorted, 7)}")
    
    print(f"\n   有序数组: {arr_sorted}")
    print(f"   搜索 7 → 二分搜索: {binary_search(arr_sorted, 7)}")
    
    # 2. 重复元素的二分搜索
    print("\n2. 重复元素的二分搜索")
    arr_dup = [1, 3, 3, 3, 5, 7]
    print(f"   数组: {arr_dup}")
    print(f"   搜索 3 的最左位置: {binary_search_leftmost(arr_dup, 3)}")
    print(f"   搜索 3 的最右位置: {binary_search_rightmost(arr_dup, 3)}")
    
    # 3. 图搜索测试
    print("\n3. 图的搜索（DFS vs BFS）")
    graph = {
        'A': ['B', 'C'],
        'B': ['A', 'D', 'E'],
        'C': ['A', 'F'],
        'D': ['B'],
        'E': ['B'],
        'F': ['C']
    }
    
    print(f"   图: {graph}")
    print(f"   DFS 从 A 开始: {dfs_iterative(graph, 'A')}")
    print(f"   BFS 从 A 开始: {bfs(graph, 'A')}")
    
    # 4. 最短路径
    print("\n4. BFS 最短路径")
    path = bfs_shortest_path(graph, 'A', 'E')
    print(f"   从 A 到 E 的最短路径: {' → '.join(path)}")
    
    print("\n" + "=" * 70)
