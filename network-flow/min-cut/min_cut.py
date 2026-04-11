"""
*
 * 最小割算法 - 基于最大流
 *
 * 问题：找到容量最小的割，使源点和汇点不再连通
 *
 * 核心思想：
 * - 使用最大流算法计算最大流
 * - 在残差网络中从源点BFS标记可达顶点
 * - 从可达集到不可达集的边即为最小割
 *
 * 时间复杂度: O(VE²)
 * 空间复杂度: O(V + E)
"""

from collections import deque

MAX_V = 100

graph = [[0] * MAX_V for _ in range(MAX_V)]
V = 0


def bfs(r_graph, s, t, parent):
    """BFS寻找增广路径"""
    visited = [False] * V
    queue = deque()
    queue.append(s)
    visited[s] = True
    parent[s] = -1

    while queue:
        u = queue.popleft()

        for v in range(V):
            if not visited[v] and r_graph[u][v] > 0:
                queue.append(v)
                parent[v] = u
                visited[v] = True

                if v == t:
                    return True

    return False


def max_flow(s, t, r_graph):
    """最大流算法"""
    parent = [-1] * V
    max_flow = 0

    while bfs(r_graph, s, t, parent):
        path_flow = float('inf')

        v = t
        while v != s:
            u = parent[v]
            path_flow = min(path_flow, r_graph[u][v])
            v = u

        v = t
        while v != s:
            u = parent[v]
            r_graph[u][v] -= path_flow
            r_graph[v][u] += path_flow
            v = u

        max_flow += path_flow

    return max_flow


def min_cut(s, t):
    """最小割算法"""
    r_graph = [[graph[i][j] for j in range(V)] for i in range(V)]

    max_flow = max_flow(s, t, r_graph)
    print(f"最大流量: {max_flow}")

    visited = [False] * V
    queue = deque()
    queue.append(s)
    visited[s] = True

    while queue:
        u = queue.popleft()

        for v in range(V):
            if not visited[v] and r_graph[u][v] > 0:
                queue.append(v)
                visited[v] = True

    print("最小割边:")
    for u in range(V):
        for v in range(V):
            if visited[u] and not visited[v] and graph[u][v] > 0:
                print(f"  {u} -> {v} (容量: {graph[u][v]})")


def main():
    """主函数"""
    global V
    print("=== 最小割算法 ===")

    V = 6

    graph[0][1] = 16
    graph[0][2] = 13
    graph[1][2] = 10
    graph[1][3] = 12
    graph[2][1] = 4
    graph[2][4] = 14
    graph[3][2] = 9
    graph[3][5] = 20
    graph[4][3] = 7
    graph[4][5] = 4

    s = 0
    t = 5
    min_cut(s, t)


if __name__ == "__main__":
    main()
