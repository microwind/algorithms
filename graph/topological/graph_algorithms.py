"""
高级图算法示例
"""

# Dijkstra 算法 - 最短路径
def dijkstra(graph, start):
    """
    Dijkstra 算法求最短路径
    时间复杂度: O((V + E) log V)
    """
    import heapq
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    pq = [(0, start)]
    
    while pq:
        current_dist, current_node = heapq.heappop(pq)
        
        if current_dist > distances[current_node]:
            continue
        
        for neighbor, weight in graph[current_node].items():
            distance = current_dist + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))
    
    return distances

# Floyd-Warshall 算法 - 所有对最短路径
def floyd_warshall(graph):
    """所有对最短路径"""
    nodes = list(graph.keys())
    dist = {node: graph[node].copy() for node in nodes}
    
    for intermediate in nodes:
        for start in nodes:
            for end in nodes:
                if start in dist and end in dist[start]:
                    dist[start][end] = min(
                        dist[start][end],
                        dist[start][intermediate] + dist[intermediate][end]
                    )
    
    return dist

# Topological Sort - 拓扑排序
def topological_sort(graph):
    """拓扑排序，用于检测循环依赖"""
    from collections import deque
    
    in_degree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            in_degree[neighbor] += 1
    
    queue = deque([node for node in graph if in_degree[node] == 0])
    result = []
    
    while queue:
        node = queue.popleft()
        result.append(node)
        
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    return result if len(result) == len(graph) else None

if __name__ == "__main__":
    print("=== 图算法示例 ===\n")
    
    # Dijkstra
    graph1 = {
        'A': {'B': 4, 'C': 2},
        'B': {'C': 1, 'D': 5},
        'C': {'D': 8, 'E': 10},
        'D': {'E': 2},
        'E': {}
    }
    print("Dijkstra 最短路径:", dijkstra(graph1, 'A'))
