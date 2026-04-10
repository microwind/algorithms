/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 图的深度优先搜索 (DFS - Depth First Search)
 * 
 * 算法原理：
 * - 从起始顶点开始，沿着一条路径尽可能深入探索
 * - 当无法继续深入时（没有未访问的邻居），回溯到上一个顶点
 * - 递归实现，使用系统调用栈
 * 
 * 时间复杂度: O(V + E) - 访问所有顶点和边
 * 空间复杂度: O(V) - 递归栈和visited数组
 * 
 * 应用场景：
 * - 连通性检测
 * - 拓扑排序
 * - 寻找连通分量
 * - 检测环
 */

#include <stdio.h>

#define V 5  // 图的顶点数量

/**
 * 深度优先搜索（递归实现）
 * 
 * @param graph   - 邻接矩阵表示的图
 * @param visited - 访问标记数组
 * @param vertex  - 当前访问的顶点
 * 
 * 算法步骤：
 * 1. 访问当前顶点并标记为已访问
 * 2. 遍历当前顶点的所有邻居
 * 3. 对于未访问的邻居，递归调用DFS
 */
void dfs(int graph[V][V], int visited[V], int vertex)
{
    // 步骤1：访问当前顶点并标记
    printf("Visited %d\n", vertex);
    visited[vertex] = 1;

    // 步骤2：遍历所有邻居顶点
    for (int i = 0; i < V; i++)
    {
        // 如果存在边且邻居未被访问
        if (graph[vertex][i] == 1 && !visited[i])
        {
            // 步骤3：递归访问邻居（深入探索）
            dfs(graph, visited, i);
        }
    }
}

/**
 * 主函数：测试DFS遍历
 * 
 * 测试图结构（邻接矩阵）：
 *     0 -- 1 -- 2
 *     |    |    |
 *     3 -- 4 --
 */
int main()
{
    // 邻接矩阵表示无向图
    int graph[V][V] = {
        {0, 1, 0, 1, 0},  // 顶点0: 连接1, 3
        {1, 0, 1, 1, 1},  // 顶点1: 连接0, 2, 3, 4
        {0, 1, 0, 0, 1},  // 顶点2: 连接1, 4
        {1, 1, 0, 0, 1},  // 顶点3: 连接0, 1, 4
        {0, 1, 1, 1, 0}}; // 顶点4: 连接1, 2, 3
    
    // 访问标记数组，初始全为0（未访问）
    int visited[V] = {0};

    printf("DFS traversal (recursive, starting from vertex 0):\n");
    dfs(graph, visited, 0);
    return 0;
}

/*
jarry@MacBook-Pro graph % gcc graph_dfs.c
jarry@MacBook-Pro graph % ./a.out
DFS traversal:
Visited 0
Visited 1
Visited 2
Visited 4
Visited 3
*/