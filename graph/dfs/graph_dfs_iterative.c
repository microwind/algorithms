#include <stdio.h>

#define V 5
#define STACK_SIZE 10

// 非递归 DFS（使用栈）
void dfs_iterative(int graph[V][V], int start)
{
    int stack[STACK_SIZE], top = -1;
    int visited[V] = {0};

    stack[++top] = start;
    visited[start] = 1;

    // 使用栈 实现遍历
    while (top >= 0)
    {
        int vertex = stack[top--];
        printf("Visited %d\n", vertex);

        for (int i = 0; i < V; i++)
        {
            if (graph[vertex][i] == 1 && !visited[i])
            {
                stack[++top] = i;
                visited[i] = 1;
            }
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

    printf("Iterative DFS traversal:\n");
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