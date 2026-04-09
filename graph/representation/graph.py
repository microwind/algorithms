"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0

图的邻接表表示实现
使用链表存储图的邻接关系
"""

from typing import List, Optional

class Node:
    def __init__(self, dest: int):
        self.dest = dest
        self.next: Optional['Node'] = None

class Graph:
    V = 5
    
    def __init__(self):
        self.adj_list: List[Optional[Node]] = [None] * self.V
    
    def add_edge(self, src: int, dest: int) -> None:
        new_node = Node(dest)
        new_node.next = self.adj_list[src]
        self.adj_list[src] = new_node
    
    def print_graph(self) -> None:
        for i in range(self.V):
            result = f"Adjacency list of vertex {i}: "
            temp = self.adj_list[i]
            while temp:
                result += f" -> {temp.dest}"
                temp = temp.next
            print(result)

def main():
    graph = Graph()
    graph.add_edge(0, 1)
    graph.add_edge(0, 3)
    graph.add_edge(1, 2)
    graph.add_edge(1, 3)
    graph.add_edge(1, 4)
    graph.add_edge(2, 4)
    graph.add_edge(3, 4)
    
    graph.print_graph()

if __name__ == "__main__":
    main()
