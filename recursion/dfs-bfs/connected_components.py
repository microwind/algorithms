"""
图的DFS - 连通分量检测
使用递归DFS找出图中的所有连通分量
"""

MAX_VERTICES = 100

# 邻接矩阵表示图
graph = [[0 for _ in range(MAX_VERTICES)] for _ in range(MAX_VERTICES)]
visited = [False] * MAX_VERTICES
num_vertices = 0

def dfs(vertex):
    """DFS递归遍历"""
    # 标记当前顶点为已访问
    visited[vertex] = True
    print(vertex, end=' ')
    
    # 递归访问所有未访问的邻居
    for i in range(num_vertices):
        if graph[vertex][i] == 1 and not visited[i]:
            dfs(i)

def find_connected_components():
    """查找所有连通分量"""
    component_count = 0
    
    print("连通分量检测:\n")
    
    # 初始化访问数组
    for i in range(num_vertices):
        visited[i] = False
    
    # 遍历所有顶点，对每个未访问的顶点进行DFS
    for i in range(num_vertices):
        if not visited[i]:
            component_count += 1
            print(f"连通分量 {component_count}: ", end='')
            dfs(i)
            print()
    
    print(f"\n总共找到 {component_count} 个连通分量")

def add_edge(from_vertex, to_vertex):
    """添加边"""
    graph[from_vertex][to_vertex] = 1
    graph[to_vertex][from_vertex] = 1

def main():
    global num_vertices
    
    # 创建一个示例图（两个连通分量）
    # 分量1: 0-1-2
    # 分量2: 3-4
    num_vertices = 5
    
    # 添加边
    add_edge(0, 1)
    add_edge(1, 2)
    add_edge(3, 4)
    
    print("图结构:")
    print("  分量1: 0 -- 1 -- 2")
    print("  分量2: 3 -- 4\n")
    
    find_connected_components()

if __name__ == "__main__":
    main()
