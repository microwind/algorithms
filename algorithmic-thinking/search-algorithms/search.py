"""
搜索算法 - 在数据中查找特定元素

特点：
- 线性搜索：简单，适合小数据集
- 二分搜索：高效，需要有序数据
- DFS：探索深度方向，用于图/树
- BFS：逐层探索，找最短路径
"""

# 例1: 线性搜索
def linear_search(arr, target):
    """
    在数组中线性搜索目标值
    时间: O(n), 空间: O(1)
    """
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1

# 例2: 二分搜索
def binary_search(arr, target):
    """
    在有序数组中进行二分搜索
    时间: O(log n), 空间: O(1)
    """
    left, right = 0, len(arr) - 1
    
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return -1

# 例3: 二分搜索 (递归版)
def binary_search_recursive(arr, target, left=0, right=None):
    """
    递归实现二分搜索
    时间: O(log n), 空间: O(log n)
    """
    if right is None:
        right = len(arr) - 1
    
    if left > right:
        return -1
    
    mid = (left + right) // 2
    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_recursive(arr, target, mid + 1, right)
    else:
        return binary_search_recursive(arr, target, left, mid - 1)

# 例4: 深度优先搜索 (递归)
def dfs_recursive(graph, node, visited=None):
    """
    使用递归进行深度优先搜索
    时间: O(V+E), 空间: O(V)
    """
    if visited is None:
        visited = set()
    
    visited.add(node)
    result = [node]
    
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            result.extend(dfs_recursive(graph, neighbor, visited))
    
    return result

# 例5: 深度优先搜索 (迭代)
def dfs_iterative(graph, start):
    """
    使用栈进行深度优先搜索
    时间: O(V+E), 空间: O(V)
    """
    visited = set()
    stack = [start]
    result = []
    
    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            result.append(node)
            # 注意：添加邻接点时要反序，保持与递归相同的顺序
            stack.extend(reversed(graph.get(node, [])))
    
    return result

# 例6: 广度优先搜索
def bfs(graph, start):
    """
    使用队列进行广度优先搜索
    时间: O(V+E), 空间: O(V)
    """
    from collections import deque
    
    visited = set()
    queue = deque([start])
    visited.add(start)
    result = []
    
    while queue:
        node = queue.popleft()
        result.append(node)
        
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    
    return result

# 测试代码
if __name__ == "__main__":
    print("=" * 50)
    print("搜索算法示例")
    print("=" * 50)
    
    # 线性搜索测试
    print("\n1. 线性搜索")
    arr = [5, 2, 8, 1, 9, 3]
    target = 8
    result = linear_search(arr, target)
    print(f"  数组: {arr}")
    print(f"  查找 {target}: 索引 = {result}")
    
    # 二分搜索测试
    print("\n2. 二分搜索（有序数组）")
    sorted_arr = [1, 2, 3, 5, 8, 9]
    target = 5
    result = binary_search(sorted_arr, target)
    print(f"  数组: {sorted_arr}")
    print(f"  查找 {target}: 索引 = {result}")
    
    # 二分搜索递归版测试
    print("\n3. 二分搜索（递归版）")
    result = binary_search_recursive(sorted_arr, target)
    print(f"  查找 {target}: 索引 = {result}")
    
    # DFS 测试
    print("\n4. 深度优先搜索")
    graph = {
        'A': ['B', 'C'],
        'B': ['A', 'D', 'E'],
        'C': ['A', 'F'],
        'D': ['B'],
        'E': ['B', 'F'],
        'F': ['C', 'E']
    }
    print(f"  图: {graph}")
    print(f"  DFS（递归）从 A 开始: {dfs_recursive(graph, 'A')}")
    print(f"  DFS（迭代）从 A 开始: {dfs_iterative(graph, 'A')}")
    
    # BFS 测试
    print("\n5. 广度优先搜索")
    print(f"  BFS 从 A 开始: {bfs(graph, 'A')}")
    
    print("\n" + "=" * 50)
