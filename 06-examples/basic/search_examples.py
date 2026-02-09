"""
基础搜索算法示例
"""

def linear_search(arr, target):
    """线性查找，O(n)"""
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1

def binary_search(arr, target):
    """二分查找，O(log n)"""
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

def dfs(graph, node, visited=None):
    """深度优先搜索"""
    if visited is None:
        visited = set()
    visited.add(node)
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            dfs(graph, neighbor, visited)
    return visited

def bfs(graph, start):
    """广度优先搜索"""
    from collections import deque
    visited = set([start])
    queue = deque([start])
    while queue:
        node = queue.popleft()
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    return visited

if __name__ == "__main__":
    print("=== 搜索算法示例 ===\n")
    
    arr = [2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78]
    print(f"线性搜索 23: {linear_search(arr, 23)}")
    print(f"二分搜索 23: {binary_search(arr, 23)}")
    
    graph = {'A': ['B', 'C'], 'B': ['D'], 'C': ['E'], 'D': [], 'E': []}
    print(f"DFS 结果: {dfs(graph, 'A')}")
    print(f"BFS 结果: {bfs(graph, 'A')}")
