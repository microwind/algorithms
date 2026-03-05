# 广度优先搜索 (BFS) - Python 实现

"""
广度优先搜索（Breadth First Search）
时间复杂度: O(V + E)
空间复杂度: O(V)
"""

from collections import deque

def bfs_traversal(graph, start):
    """
    BFS 遍历：从起点开始逐层访问所有节点
    graph: 邻接表 {node: [neighbors]}
    返回: 遍历顺序列表
    """
    visited = set()
    queue = deque([start])
    visited.add(start)
    result = []
    
    while queue:
        node = queue.popleft()
        result.append(node)
        
        # 添加所有未访问的邻接点
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    
    return result

def bfs_shortest_path(graph, start, end):
    """
    BFS 查找最短路径（无权图）
    返回: 最短路径列表，如果不存在返回 None
    """
    if start == end:
        return [start]
    
    visited = {start: None}  # {node: parent}
    queue = deque([start])
    
    while queue:
        node = queue.popleft()
        
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited[neighbor] = node
                
                if neighbor == end:
                    # 重构路径
                    path = []
                    current = end
                    while current is not None:
                        path.append(current)
                        current = visited[current]
                    return path[::-1]
                
                queue.append(neighbor)
    
    return None  # 无路径

def bfs_level_order(graph, start):
    """
    BFS 按层级遍历（树专用）
    返回: [[第0层节点], [第1层节点], ...]
    """
    levels = []
    visited = {start}
    current_level = [start]
    
    while current_level:
        levels.append(current_level)
        next_level = []
        
        for node in current_level:
            for neighbor in graph.get(node, []):
                if neighbor not in visited:
                    visited.add(neighbor)
                    next_level.append(neighbor)
        
        current_level = next_level
    
    return levels

def bfs_all_shortest_paths(graph, start):
    """
    BFS 计算从起点到所有节点的最短距离和路径
    返回: {node: (distance, path)}
    """
    distances = {start: 0}
    parents = {start: []}  # 可能有多个父节点
    queue = deque([start])
    
    while queue:
        node = queue.popleft()
        
        for neighbor in graph.get(node, []):
            if neighbor not in distances:
                distances[neighbor] = distances[node] + 1
                parents[neighbor] = [node]
                queue.append(neighbor)
            elif distances[neighbor] == distances[node] + 1:
                # 找到另一条等长最短路径
                parents[neighbor].append(node)
    
    # 重构所有最短路径
    def reconstruct_paths(node):
        if not parents[node]:
            return [[node]]
        
        paths = []
        for parent in parents[node]:
            for path in reconstruct_paths(parent):
                paths.append(path + [node])
        return paths
    
    result = {}
    for node in distances:
        paths = reconstruct_paths(node)
        result[node] = (distances[node], paths)
    
    return result

def bfs_connected_components(graph):
    """
    BFS 查找无向图的所有连通分量
    返回: [分量1节点集, 分量2节点集, ...]
    """
    visited = set()
    components = []
    
    for node in graph:
        if node not in visited:
            component = set()
            queue = deque([node])
            visited.add(node)
            
            while queue:
                current = queue.popleft()
                component.add(current)
                
                for neighbor in graph.get(current, []):
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
            
            components.append(component)
    
    return components

if __name__ == "__main__":
    print("=" * 50)
    print("广度优先搜索 (BFS) - Python 实现")
    print("=" * 50)
    
    # 无向图
    graph = {
        'A': ['B', 'C'],
        'B': ['A', 'D', 'E'],
        'C': ['A', 'F'],
        'D': ['B'],
        'E': ['B', 'F'],
        'F': ['C', 'E']
    }
    
    # 测试 1：BFS 遍历
    print("\n测试 1: BFS 遍历")
    print(f"图: {graph}")
    result = bfs_traversal(graph, 'A')
    print(f"从 A 开始的 BFS: {result}")
    
    # 测试 2：最短路径
    print("\n测试 2: 最短路径")
    path = bfs_shortest_path(graph, 'A', 'F')
    if path:
        print(f"A 到 F 的最短路径: {' -> '.join(path)}")
    else:
        print("无路径")
    
    # 测试 3：层级遍历
    print("\n测试 3: 层级遍历")
    tree = {
        'A': ['B', 'C'],
        'B': ['D', 'E'],
        'C': ['F'],
        'D': [],
        'E': [],
        'F': []
    }
    levels = bfs_level_order(tree, 'A')
    for i, level in enumerate(levels):
        print(f"  第 {i} 层: {level}")
    
    # 测试 4：所有最短路径
    print("\n测试 4: 所有最短路径")
    simple_graph = {
        'A': ['B', 'C'],
        'B': ['D'],
        'C': ['D'],
        'D': []
    }
    all_paths = bfs_all_shortest_paths(simple_graph, 'A')
    print(f"从 A 出发的最短路径:")
    for node, (dist, paths) in all_paths.items():
        print(f"  到 {node} (距离 {dist}): {paths}")
    
    # 测试 5：连通分量
    print("\n测试 5: 连通分量")
    disconnected_graph = {
        'A': ['B'],
        'B': ['A'],
        'C': ['D'],
        'D': ['C'],
        'E': []
    }
    components = bfs_connected_components(disconnected_graph)
    print(f"图: {disconnected_graph}")
    for i, comp in enumerate(components, 1):
        print(f"  分量 {i}: {comp}")
    
    print("\n" + "=" * 50)
