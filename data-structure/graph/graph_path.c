#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6 // 节点数量（A, B, C, D, E, F）

/*
城市中的地点：A、B、C、D、E、F
每条边代表两地点之间的道路，边的权重表示道路的距离（单位：公里）
如何找到最近的连个点？

邻接矩阵：我们用一个6x6的二维数组graph表示图，graph[i][j]表示从节点i到节点j的距离。如果graph[i][j]为0，则表示两节点之间没有直接路径。
Dijkstra算法：dijkstra()函数用来计算从源节点（src）到图中其他所有节点的最短路径。它维护了一个dist数组，记录当前从源节点到各个节点的最短距离。sptSet数组用于标记节点是否已经被处理。
minDistance函数：该函数遍历所有未处理的节点，找到距离源节点最小的节点。
主要逻辑：在每一步中，算法选择当前距离最小的节点，将其标记为已处理，然后更新其相邻节点的距离，直到处理完所有节点。
 */

// 查找距离集合中最小的节点
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Dijkstra算法实现
void dijkstra(int graph[V][V], int src)
{
    int dist[V];    // 记录从源节点到各节点的最短距离
    bool sptSet[V]; // 记录已找到最短路径的节点

    // 初始化所有节点的距离为无穷大，并设置sptSet为false
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // 设置源节点的距离为0
    dist[src] = 0;

    // 寻找V-1条最短路径
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet); // 找到当前未处理节点中距离最小的节点
        sptSet[u] = true;                  // 标记该节点已处理

        // 更新相邻节点的距离
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // 打印结果
    printf("从源点到各节点的最短距离:\n");
    char nodes[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 0; i < V; i++)
        printf("%c 到 %c 的最短距离是: %d\n", nodes[src], nodes[i], dist[i]);
}

int main()
{
    // 示例城市地图的邻接矩阵表示
    // 0表示无连接，其他数字表示两点之间的距离
    int graph[V][V] = {
        {0, 5, 2, 0, 0, 0},
        {5, 0, 1, 3, 0, 0},
        {2, 1, 0, 8, 10, 0},
        {0, 3, 8, 0, 4, 6},
        {0, 0, 10, 4, 0, 2},
        {0, 0, 0, 6, 2, 0}};

    // 计算从节点A（索引0）到所有其他节点的最短路径
    dijkstra(graph, 0);

    return 0;
}

/**
jarry@jarrys-MacBook-Pro graph % gcc graph_path.c
jarry@jarrys-MacBook-Pro graph % ./a.out 
从源点到各节点的最短距离:
A 到 A 的最短距离是: 0
A 到 B 的最短距离是: 3
A 到 C 的最短距离是: 2
A 到 D 的最短距离是: 6
A 到 E 的最短距离是: 10
A 到 F 的最短距离是: 12
 */