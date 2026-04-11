"""
*
 * Ford-Fulkerson算法 - 使用DFS的最大流算法
 *
 * 问题：在流网络中找到从源点到汇点的最大流量
 *
 * 核心思想：
 * - 使用DFS寻找增广路径
 * - 沿增广路径增加流量
 * - 更新残差网络
 *
 * 时间复杂度: O(E * max_flow)
 * 空间复杂度: O(V + E)
"""

MAX_V = 100

graph = [[0] * MAX_V for _ in range(MAX_V)]
V = 0


def dfs(r_graph, u, t, visited, min_flow):
    """DFS寻找增广路径"""
    if u == t:
        return min_flow

    visited[u] = True

    for v in range(V):
        if not visited[v] and r_graph[u][v] > 0:
            flow = dfs(r_graph, v, t, visited, min(min_flow, r_graph[u][v]))

            if flow > 0:
                r_graph[u][v] -= flow
                r_graph[v][u] += flow
                return flow

    return 0


def ford_fulkerson(s, t):
    """Ford-Fulkerson算法"""
    r_graph = [[graph[i][j] for j in range(V)] for i in range(V)]
    max_flow = 0

    while True:
        visited = [False] * V
        path_flow = dfs(r_graph, s, t, visited, float('inf'))

        if path_flow == 0:
            break

        max_flow += path_flow

    return max_flow


def main():
    """主函数"""
    global V
    print("=== Ford-Fulkerson算法 ===")

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
    max_flow = ford_fulkerson(s, t)

    print(f"最大流量: {max_flow}")


if __name__ == "__main__":
    main()
