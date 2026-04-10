/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * Dijkstra最短路径算法 (Dijkstra's Shortest Path Algorithm)
 * 
 * 算法原理：
 * - 贪心算法，每次选择距离源点最近的未处理顶点
 * - 通过"松弛"操作更新其他顶点的最短距离
 * - 适用于带权有向图，边权必须非负
 * 
 * 时间复杂度: O(V²) - 使用邻接矩阵和简单数组
 * 空间复杂度: O(V) - 存储距离和访问标记数组
 * 
 * 优化版本：使用优先队列(最小堆)可将时间复杂度降至 O((V+E)logV)
 * 
 * 应用场景：
 * - 地图导航最短路径
 * - 网络路由优化
 * - 任务调度
 */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // 图的顶点数量

/**
 * 找到距离最小的未处理顶点
 * 
 * @param dist    - 各顶点到源点的当前最短距离数组
 * @param sptSet  - 最短路径树集合标记（已处理顶点）
 * @return        - 距离最小的未处理顶点索引
 * 
 * 算法：遍历所有顶点，找出未在sptSet中且距离最小的顶点
 */
int minDistance(int dist[], bool sptSet[])
{
  int min = INT_MAX, min_index;
  
  // 遍历所有顶点
  for (int v = 0; v < V; v++)
  {
    // 如果顶点v未处理且距离更小
    if (!sptSet[v] && dist[v] <= min)
    {
      min = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

/**
 * 打印最短路径结果
 * @param dist - 各顶点到源点的最短距离数组
 */
void printSolution(int dist[])
{
  printf("Vertex \t Distance from Source\n");
  for (int i = 0; i < V; i++)
  {
    printf("%d \t %d\n", i, dist[i]);
  }
}

/**
 * Dijkstra算法实现
 * 
 * @param graph - 邻接矩阵表示的带权图，graph[i][j]表示边i->j的权重，0表示无边
 * @param src   - 源点（起始顶点）
 * 
 * 算法步骤：
 * 1. 初始化：所有顶点距离设为无穷大，源点距离设为0
 * 2. 重复V-1次：
 *    a. 选择距离最小的未处理顶点u
 *    b. 将u加入最短路径树（标记为已处理）
 *    c. 对所有u的邻居v进行"松弛"操作：
 *       如果 dist[u] + graph[u][v] < dist[v]，则更新dist[v]
 * 3. 输出所有顶点的最短距离
 */
void dijkstra(int graph[V][V], int src)
{
  int dist[V];    // dist[i] = 顶点i到源点的当前最短距离
  bool sptSet[V]; // sptSet[i] = true 表示顶点i已加入最短路径树

  // 步骤1：初始化
  for (int i = 0; i < V; i++)
  {
    dist[i] = INT_MAX;    // 初始距离设为无穷大
    sptSet[i] = false;    // 所有顶点未处理
  }
  dist[src] = 0;          // 源点到自身距离为0

  // 步骤2：循环处理V-1个顶点
  for (int count = 0; count < V - 1; count++)
  {
    // 步骤2a：选择距离最小的未处理顶点u
    int u = minDistance(dist, sptSet);
    sptSet[u] = true;     // 标记为已处理

    // 步骤2c：松弛操作 - 更新u的所有邻居的距离
    for (int v = 0; v < V; v++)
    {
      // 条件检查：v未处理、u到v有边、u可达、通过u到v更短
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
          && dist[u] + graph[u][v] < dist[v])
      {
        dist[v] = dist[u] + graph[u][v];  // 更新最短距离
      }
    }
  }

  // 步骤3：输出结果
  printSolution(dist);
}

/**
 * 主函数：测试Dijkstra算法
 * 
 * 测试图结构（带权无向图）：
 * 
 *       (4)    (8)    (7)
 *    0 ----- 1 ----- 2 -----
 *            |       |  (4)
 *           (11)     |
 *            |       |
 *    3 ----- 4 -----
 *       (9)    (10)    (14)
 * 
 * 预期结果（从顶点0出发）：
 * - 到顶点0: 0
 * - 到顶点1: 4 (0->1)
 * - 到顶点2: 12 (0->1->2)
 * - 到顶点3: 19 (0->1->2->5->3 或 0->1->4->5->3)
 * - 到顶点4: 21 (0->1->4)
 * - 到顶点5: 11 (0->1->2->5)
 */
int main()
{
  // 邻接矩阵：graph[i][j] = 边权重，0表示无直接连接
  int graph[V][V] = {
      {0, 4, 0, 0, 0, 0},   // 顶点0: 到1距离4
      {4, 0, 8, 0, 11, 0},  // 顶点1: 到0距离4, 到2距离8, 到4距离11
      {0, 8, 0, 0, 0, 4},   // 顶点2: 到1距离8, 到5距离4
      {0, 0, 0, 0, 9, 14},  // 顶点3: 到4距离9, 到5距离14
      {0, 11, 0, 9, 0, 10}, // 顶点4: 到1距离11, 到3距离9, 到5距离10
      {0, 0, 4, 14, 10, 0}};// 顶点5: 到2距离4, 到3距离14, 到4距离10

  printf("Dijkstra shortest path from vertex 0:\n\n");
  dijkstra(graph, 0);  // 从顶点0开始计算最短路径

  return 0;
}

/*
jarry@MacBook-Pro graph % gcc graph_dijkstra.c
jarry@MacBook-Pro graph % ./a.out
Vertex   Distance from Source
0        0
1        4
2        12
3        19
4        26
5        16
*/