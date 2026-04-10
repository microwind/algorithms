/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 图的深度优先搜索 - 迭代实现 (DFS Iterative)
 * 
 * 算法原理：
 * - 使用显式栈代替递归调用栈
 * - 从起始顶点开始，将其压入栈
 * - 弹出栈顶顶点访问，并将其未访问的邻居压入栈
 * - 重复直到栈为空
 * 
 * 时间复杂度: O(V + E)
 * 空间复杂度: O(V) - 显式栈和visited数组
 * 
 * 优势：
 * - 避免递归栈溢出问题
 * - 可以处理更深的图
 */

#include <stdio.h>

#define V 5           // 图的顶点数量
#define STACK_SIZE 10 // 栈的大小

/**
 * 深度优先搜索（迭代实现，使用显式栈）
 * 
 * @param graph - 邻接矩阵表示的图
 * @param start - 起始顶点
 * 
 * 算法步骤：
 * 1. 初始化栈，将起始顶点压栈并标记已访问
 * 2. 当栈不为空时：
 *    a. 弹出栈顶顶点并访问
 *    b. 遍历该顶点的所有邻居
 *    c. 将未访问的邻居压栈并标记
 * 3. 重复直到栈为空
 */
void dfs_iterative(int graph[V][V], int start)
{
    int stack[STACK_SIZE], top = -1;  // 栈：top为栈顶索引，-1表示空栈
    int visited[V] = {0};             // visited[i]=1 表示顶点i已访问

    // 步骤1：起始顶点压栈
    stack[++top] = start;
    visited[start] = 1;

    // 步骤2：栈不为空时继续遍历
    while (top >= 0)
    {
        // 步骤2a：弹出栈顶顶点并访问
        int vertex = stack[top--];
        printf("Visited %d\n", vertex);

        // 步骤2b：遍历所有邻居顶点
        for (int i = 0; i < V; i++)
        {
            // 如果存在边且邻居未被访问
            if (graph[vertex][i] == 1 && !visited[i])
            {
                // 步骤2c：邻居压栈并标记
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
}

/**
 * 主函数：测试迭代DFS遍历
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

    printf("Iterative DFS traversal (starting from vertex 0):\n");
    dfs_iterative(graph, 0);
    return 0;
}

/*
jarry@MacBook-Pro graph % gcc graph_dfs_iterative.c
jarry@MacBook-Pro graph % ./a.out
Iterative DFS traversal:
Visited 0
Visited 3
Visited 4
Visited 2
Visited 1
*/