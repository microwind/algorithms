#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/* Dijkstra 最短路径算法，循环遍历 */

#define V 6

// 找到距离最小的未处理节点
int minDistance(int dist[], bool sptSet[])
{
  int min = INT_MAX, min_index;
  for (int v = 0; v < V; v++)
  {
    if (!sptSet[v] && dist[v] <= min)
    {
      min = dist[v];
      min_index = v;
    }
  }
  return min_index;
}

// 打印最短路径
void printSolution(int dist[])
{
  printf("Vertex \t Distance from Source\n");
  for (int i = 0; i < V; i++)
  {
    printf("%d \t %d\n", i, dist[i]);
  }
}

// Dijkstra算法
void dijkstra(int graph[V][V], int src)
{
  int dist[V];    // 存储最短距离
  bool sptSet[V]; // 记录节点是否已处理

  // 初始化矩阵
  for (int i = 0; i < V; i++)
  {
    dist[i] = INT_MAX;
    sptSet[i] = false;
  }
  dist[src] = 0;

  for (int count = 0; count < V - 1; count++)
  {
    // 选择距离最小的未处理节点
    int u = minDistance(dist, sptSet);
    sptSet[u] = true;

    // 更新邻接节点的距离
    for (int v = 0; v < V; v++)
    {
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
      {
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }

  printSolution(dist);
}

int main()
{
  int graph[V][V] = {
      {0, 4, 0, 0, 0, 0},
      {4, 0, 8, 0, 0, 0},
      {0, 8, 0, 7, 0, 4},
      {0, 0, 7, 0, 9, 14},
      {0, 0, 0, 9, 0, 10},
      {0, 0, 4, 14, 10, 0}};

  dijkstra(graph, 0); // 从顶点0开始计算最短路径

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