#!/usr/bin/env python
# -*- encoding: UTF-8-*-
"""
下面是一个使用Python和networkx库的示例代码，在一个城市地图上找到最短路径。

应用场景：城市导航 - 寻找最短路径
示例城市地图
城市中的地点：A、B、C、D、E、F
每条边代表两地点之间的道路，边的权重表示道路的距离（单位：公里）


"""
import networkx as nx

# 创建一个有向加权图
city_map = nx.DiGraph()

# 添加边（地点之间的道路及其距离）
city_map.add_weighted_edges_from([
    ('A', 'B', 5),
    ('A', 'C', 2),
    ('B', 'C', 1),
    ('B', 'D', 3),
    ('C', 'D', 8),
    ('C', 'E', 10),
    ('D', 'E', 4),
    ('D', 'F', 6),
    ('E', 'F', 2)
])

# 使用Dijkstra算法计算从A到F的最短路径
shortest_path = nx.dijkstra_path(city_map, 'A', 'F')
shortest_distance = nx.dijkstra_path_length(city_map, 'A', 'F')

# 安装依赖库networkx
# $ pip install --upgrade pip --user
# $ pip install networkx        

# 输出最短路径及其总距离
print(f"从A到F的最短路径是: {shortest_path}")
print(f"总距离是: {shortest_distance} 公里")

"""
打印结果：
jarry@jarrys-MacBook-Pro graph % python graph_path.py
从A到F的最短路径是: ['A', 'B', 'D', 'F']
总距离是: 14 公里
"""

"""
  代码解析：
  创建图：我们使用networkx.DiGraph()创建一个有向图，因为道路的方向可能影响路径选择。
  添加边和权重：add_weighted_edges_from()函数将每个地点对（如('A', 'B', 5)）及其对应的距离（权重）添加到图中。
  Dijkstra算法：nx.dijkstra_path()计算从A到F的最短路径，nx.dijkstra_path_length()则计算该路径的总距离。
  实际应用场景：
  这里展示了在城市导航中如何使用图来表示道路网络，并通过Dijkstra算法计算出两地点之间的最短路径。这在GPS导航系统、地图应用或物流配送优化中非常有用。
"""
