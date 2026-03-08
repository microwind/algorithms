"""
图的深度优先搜索 (DFS) 和广度优先搜索 (BFS)
使用递归实现DFS，使用队列实现BFS
"""

from collections import deque


def dfs_recursive(graph, node, visited=None):
    """
    深度优先搜索 - 递归实现
    沿着一条路径尽可能深地搜索，直到无法继续才回溯
    """
    if visited is None:
        visited = set()
    
    # 访问当前节点
    visited.add(node)
    print(f"DFS访问: {node}")
    
    # 递归访问所有未访问的邻居
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            dfs_recursive(graph, neighbor, visited)
    
    return visited


def bfs_iterative(graph, start):
    """
    广度优先搜索 - 迭代实现（使用队列）
    逐层遍历，先访问所有邻居，再访问邻居的邻居
    """
    visited = {start}
    queue = deque([start])
    
    print(f"\nBFS遍历:")
    while queue:
        node = queue.popleft()
        print(f"BFS访问: {node}")
        
        # 将所有未访问的邻居加入队列
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    
    return visited


# 示例图（邻接表表示）
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

print("图结构:")
print("    A")
print("   / \\")
print("  B---C")
print("  |\   |")
print("  D E--F")
print()

print("=" * 30)
print("DFS深度优先遍历:")
dfs_recursive(graph, 'A')

print()
bfs_iterative(graph, 'A')
