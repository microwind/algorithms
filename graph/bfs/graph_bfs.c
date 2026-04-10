/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 图的广度优先搜索 (BFS - Breadth First Search)
 * 
 * 算法原理：
 * - 从起始顶点开始，先访问所有相邻顶点（第一层）
 * - 再依次访问这些相邻顶点的相邻顶点（第二层）
 * - 使用队列实现，保证先访问的顶点的邻居先被访问
 * 
 * 时间复杂度: O(V + E) - 访问所有顶点和边
 * 空间复杂度: O(V) - 队列和visited数组
 * 
 * 应用场景：
 * - 最短路径（无权图）
 * - 连通性检测
 * - 层级遍历
 */

#include <stdio.h>

#define V 5           // 图的顶点数量
#define QUEUE_SIZE 10 // 队列大小

/**
 * 广度优先搜索 (BFS)
 * 
 * @param graph - 邻接矩阵表示的图
 * @param start - 起始顶点
 * 
 * 算法步骤：
 * 1. 初始化队列，将起始顶点入队并标记已访问
 * 2. 当队列不为空时：
 *    a. 取出队首顶点并访问
 *    b. 遍历该顶点的所有邻居
 *    c. 将未访问的邻居入队并标记
 * 3. 重复直到队列为空
 */
void bfs(int graph[V][V], int start)
{
    int queue[QUEUE_SIZE], front = 0, rear = 0;  // 队列：front队首，rear队尾
    int visited[V] = {0};                        // visited[i]=1 表示顶点i已访问

    // 步骤1：起始顶点入队
    queue[rear++] = start;
    visited[start] = 1;

    // 步骤2：队列不为空时继续遍历
    while (front < rear)
    {
        // 步骤2a：取出队首顶点并访问
        int vertex = queue[front++];
        printf("Visited %d\n", vertex);

        // 步骤2b：遍历所有邻居顶点
        for (int i = 0; i < V; i++)
        {
            // 如果存在边且邻居未被访问
            if (graph[vertex][i] == 1 && !visited[i])
            {
                // 步骤2c：邻居入队并标记已访问
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

/**
 * 主函数：测试BFS遍历
 * 
 * 测试图结构（邻接矩阵）：
 *     0 -- 1 -- 2
 *     |    |    |
 *     3 -- 4 --
 * 
 * 顶点0的邻居: 1, 3
 * 顶点1的邻居: 0, 2, 3, 4
 * 顶点2的邻居: 1, 4
 * 顶点3的邻居: 0, 1, 4
 * 顶点4的邻居: 1, 2, 3
 */
int main()
{
    // 邻接矩阵表示无向图：graph[i][j]=1 表示顶点i和j之间有边
    int graph[V][V] = {
        {0, 1, 0, 1, 0},  // 顶点0: 连接1, 3
        {1, 0, 1, 1, 1},  // 顶点1: 连接0, 2, 3, 4
        {0, 1, 0, 0, 1},  // 顶点2: 连接1, 4
        {1, 1, 0, 0, 1},  // 顶点3: 连接0, 1, 4
        {0, 1, 1, 1, 0}}; // 顶点4: 连接1, 2, 3

    printf("BFS traversal (starting from vertex 0):\n");
    bfs(graph, 0);
    return 0;
}

/*
jarry@MacBook-Pro graph % gcc graph_bfs.c
jarry@MacBook-Pro graph % ./a.out
BFS traversal:
Visited 0
Visited 1
Visited 3
Visited 2
Visited 4
*/