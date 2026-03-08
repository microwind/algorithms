"""
图算法 - 拓扑排序 (Topological Sort)
使用Kahn算法（基于BFS）对有向无环图进行拓扑排序
"""
from collections import deque


def topological_sort(graph, num_vertices):
    """
    Kahn算法实现拓扑排序
    
    参数:
        graph: 邻接表表示的有向图 {节点: [邻居列表]}
        num_vertices: 顶点数量
    返回:
        拓扑排序结果列表，如果存在环则返回空列表
    """
    # 计算每个顶点的入度
    in_degree = [0] * num_vertices
    for u in graph:
        for v in graph[u]:
            in_degree[v] += 1
    
    # 将所有入度为0的顶点加入队列
    queue = deque()
    for i in range(num_vertices):
        if in_degree[i] == 0:
            queue.append(i)
    
    result = []
    
    while queue:
        u = queue.popleft()
        result.append(u)
        
        # 将u的所有邻居的入度减1
        for v in graph.get(u, []):
            in_degree[v] -= 1
            if in_degree[v] == 0:
                queue.append(v)
    
    # 检查是否存在环
    if len(result) != num_vertices:
        return []  # 存在环，无法拓扑排序
    
    return result


# 测试示例
if __name__ == "__main__":
    # 示例：课程先修关系
    # 0: 数学, 1: 编程, 2: 数据结构, 3: 算法
    # 先修关系：数学->编程, 编程->数据结构, 编程->算法, 数据结构->算法
    
    graph = {
        0: [1],      # 数学 -> 编程
        1: [2, 3],   # 编程 -> 数据结构, 算法
        2: [3],      # 数据结构 -> 算法
        3: []
    }
    num_vertices = 4
    
    print("=" * 50)
    print("拓扑排序 (Topological Sort)")
    print("=" * 50)
    
    print("\n课程先修关系图:")
    print("数学(0) → 编程(1) → 数据结构(2)")
    print("                ↘          ↓")
    print("                   → 算法(3)")
    
    result = topological_sort(graph, num_vertices)
    
    if result:
        print(f"\n拓扑排序结果: {result}")
        print("解释: 按此顺序学习，满足所有先修条件")
    else:
        print("\n图中存在环，无法进行拓扑排序")
