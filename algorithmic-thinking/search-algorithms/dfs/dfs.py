# 深度优先搜索 (DFS) - Python 实现

"""
深度优先搜索（Depth First Search）
时间复杂度: O(V + E)
空间复杂度: O(V)
"""

def dfs_recursive(graph, node, visited=None, result=None):
    """
    递归版 DFS
    graph: 邻接表 {node: [neighbors]}
    返回: 遍历顺序列表
    """
    if visited is None:
        visited = set()
    if result is None:
        result = []
    
    visited.add(node)
    result.append(node)
    
    # 访问所有未访问的邻接点
    for neighbor in graph.get(node, []):
        if neighbor not in visited:
            dfs_recursive(graph, neighbor, visited, result)
    
    return result

def dfs_iterative(graph, start):
    """
    迭代版 DFS（使用栈）
    时间: O(V + E), 空间: O(V)
    """
    visited = set()
    stack = [start]
    result = []
    
    while stack:
        node = stack.pop()
        
        if node not in visited:
            visited.add(node)
            result.append(node)
            
            # 添加未访问的邻接点，注意顺序需要反转
            # 这样弹出时与递归版本顺序一致
            neighbors = graph.get(node, [])
            stack.extend(reversed(neighbors))
    
    return result

def dfs_all_paths(graph, start, end, path=None, all_paths=None):
    """
    查找图中两点间的所有路径
    """
    if path is None:
        path = []
    if all_paths is None:
        all_paths = []
    
    path = path + [start]
    
    if start == end:
        all_paths.append(path)
        return all_paths
    
    for node in graph.get(start, []):
        if node not in path:  # 避免环
            dfs_all_paths(graph, node, end, path, all_paths)
    
    return all_paths

def has_cycle_dfs(graph):
    """
    检测有向图中是否存在环
    使用三种颜色：白色(0)=未访问, 灰色(1)=访问中, 黑色(2)=访问完
    """
    color = {node: 0 for node in graph}
    
    def dfs_cycle(node):
        color[node] = 1  # 标记为灰色
        
        for neighbor in graph.get(node, []):
            if color[neighbor] == 1:
                # 发现后向边，存在环
                return True
            elif color[neighbor] == 0:  # 白色，继续 DFS
                if dfs_cycle(neighbor):
                    return True
        
        color[node] = 2  # 标记为黑色
        return False
    
    # 检查所有节点（处理非连通图）
    for node in graph:
        if color[node] == 0:
            if dfs_cycle(node):
                return True
    
    return False

def topological_sort(graph):
    """
    拓扑排序（针对有向无环图）
    使用 DFS 实现
    """
    visited = set()
    stack = []
    
    def dfs_topo(node):
        visited.add(node)
        
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                dfs_topo(neighbor)
        
        # 后序处理：加入栈
        stack.append(node)
    
    # 对所有未访问的节点进行 DFS
    for node in graph:
        if node not in visited:
            dfs_topo(node)
    
    # 反序即为拓扑顺序
    return stack[::-1]

if __name__ == "__main__":
    print("=" * 50)
    print("深度优先搜索 (DFS) - Python 实现")
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
    
    # 测试 1：递归 DFS
    print("\n测试 1: 递归 DFS")
    print(f"图: {graph}")
    result = dfs_recursive(graph, 'A')
    print(f"从 A 开始的递归 DFS: {result}")
    
    # 测试 2：迭代 DFS
    print("\n测试 2: 迭代 DFS")
    result = dfs_iterative(graph, 'A')
    print(f"从 A 开始的迭代 DFS: {result}")
    
    # 测试 3：查找所有路径
    print("\n测试 3: 查找 A 到 F 的所有路径")
    paths = dfs_all_paths(graph, 'A', 'F')
    for i, path in enumerate(paths, 1):
        print(f"  路径 {i}: {' -> '.join(path)}")
    
    # 测试 4：环检测
    print("\n测试 4: 环检测")
    # 无环图
    has_cycle = has_cycle_dfs(graph)
    print(f"图是否有环: {has_cycle}")
    
    # 有环图
    cyclic_graph = {
        'A': ['B'],
        'B': ['C'],
        'C': ['A']  # 形成环
    }
    has_cycle = has_cycle_dfs(cyclic_graph)
    print(f"环图是否有环: {has_cycle}")
    
    # 测试 5：拓扑排序
    print("\n测试 5: 拓扑排序")
    dag = {
        'A': ['B', 'C'],
        'B': ['D'],
        'C': ['D'],
        'D': ['E'],
        'E': []
    }
    topo_order = topological_sort(dag)
    print(f"有向无环图: {dag}")
    print(f"拓扑顺序: {topo_order}")
    
    print("\n" + "=" * 50)
