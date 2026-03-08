#include <stdio.h>

#define V 5
// 深度优先搜索（DFS）
void dfs(int graph[V][V], int visited[V], int vertex)
{
    printf("Visited %d\n", vertex);
    visited[vertex] = 1;

    // 循环遍历
    for (int i = 0; i < V; i++)
    {
        if (graph[vertex][i] == 1 && !visited[i])
        {
            // 递归 DFS 调用
            dfs(graph, visited, i);
        }
    }
}

int main()
{
    int graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}};
    int visited[V] = {0};

    printf("DFS traversal:\n");
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