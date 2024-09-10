#!/usr/bin/env python
# -*- encoding: UTF-8-*-
"""
在Python中，可以使用字典和列表来实现图的邻接表
"""


class Graph:
    def __init__(self, vertices):
        self.numVertices = vertices
        self.adjLists = {i: [] for i in range(vertices)}

    def addEdge(self, src, dest):
        self.adjLists[src].append(dest)
        self.adjLists[dest].append(src)

    def printGraph(self):
        for v in range(self.numVertices):
            print(f"Vertex {v}:", " -> ".join(map(str, self.adjLists[v])))


if __name__ == "__main__":
    graph = Graph(4)
    graph.addEdge(0, 1)
    graph.addEdge(0, 2)
    graph.addEdge(1, 2)
    graph.addEdge(2, 3)

    print(graph.adjLists)

    graph.printGraph()

"""
jarry@jarrys-MacBook-Pro graph % python graph.py
{0: [1, 2], 1: [0, 2], 2: [0, 1, 3], 3: [2]}
Vertex 0: 1 -> 2
Vertex 1: 0 -> 2
Vertex 2: 0 -> 1 -> 3
Vertex 3: 2
"""
