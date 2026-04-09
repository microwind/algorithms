"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

Dijkstra最短路径算法实现
使用贪心策略，适用于非负权重的图

时间复杂度: O(V²)，使用优先队列可优化至O((V+E)logV)
空间复杂度: O(V)，用于存储距离和访问标记
"""

from typing import List

V = 6
INF = float('inf')

def min_distance(dist: List[float], visited: List[bool]) -> int:
    """找到距离最小的未处理顶点"""
    min_val = INF
    min_index = -1
    
    for v in range(V):
        if not visited[v] and dist[v] <= min_val:
            min_val = dist[v]
            min_index = v
    return min_index

def dijkstra(graph: List[List[int]], src: int) -> None:
    """Dijkstra算法实现"""
    dist = [INF] * V
    visited = [False] * V
    dist[src] = 0
    
    for _ in range(V - 1):
        u = min_distance(dist, visited)
        visited[u] = True
        
        for v in range(V):
            if (not visited[v] and graph[u][v] != 0 and
                dist[u] != INF and dist[u] + graph[u][v] < dist[v]):
                dist[v] = dist[u] + graph[u][v]
    
    print("Vertex \t Distance from Source")
    for i in range(V):
        print(f"{i} \t {int(dist[i])}")

def main():
    graph = [
        [0, 4, 0, 0, 0, 0],
        [4, 0, 8, 0, 0, 0],
        [0, 8, 0, 7, 0, 4],
        [0, 0, 7, 0, 9, 14],
        [0, 0, 0, 9, 0, 10],
        [0, 0, 4, 14, 10, 0]
    ]
    dijkstra(graph, 0)

if __name__ == "__main__":
    main()
