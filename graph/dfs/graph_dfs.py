"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

图的深度优先搜索（DFS）算法实现
使用递归方式遍历图

时间复杂度: O(V + E)，其中V是顶点数，E是边数
空间复杂度: O(V)，用于存储访问标记和递归栈
"""

from typing import List

V = 5

def dfs(graph: List[List[int]], visited: List[bool], vertex: int) -> None:
    """深度优先搜索递归函数"""
    print(f"Visited {vertex}")
    visited[vertex] = True
    
    for i in range(V):
        if graph[vertex][i] == 1 and not visited[i]:
            dfs(graph, visited, i)

def main():
    graph = [
        [0, 1, 0, 1, 0],
        [1, 0, 1, 1, 1],
        [0, 1, 0, 0, 1],
        [1, 1, 0, 0, 1],
        [0, 1, 1, 1, 0]
    ]
    visited = [False] * V
    
    print("DFS traversal:")
    dfs(graph, visited, 0)

if __name__ == "__main__":
    main()
