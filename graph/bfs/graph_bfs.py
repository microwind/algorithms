"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

图的广度优先搜索（BFS）算法实现
使用队列数据结构，按层次遍历图

时间复杂度: O(V + E)，其中V是顶点数，E是边数
空间复杂度: O(V)，用于存储访问标记和队列
"""

from collections import deque
from typing import List

V = 5

def bfs(graph: List[List[int]], start: int) -> None:
    """广度优先搜索遍历"""
    queue = deque([start])
    visited = [False] * V
    visited[start] = True
    
    print("BFS traversal:")
    while queue:
        vertex = queue.popleft()
        print(f"Visited {vertex}")
        
        for i in range(V):
            if graph[vertex][i] == 1 and not visited[i]:
                queue.append(i)
                visited[i] = True

def main():
    graph = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 1, 1],
        [0, 1, 0, 0, 1],
        [1, 1, 0, 0, 1],
        [0, 1, 1, 1, 0]
    ]
    bfs(graph, 0)

if __name__ == "__main__":
    main()
