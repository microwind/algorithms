#include <stdio.h>

#define V 5
#define QUEUE_SIZE 10

// 广度优先搜索（BFS）
void bfs(int graph[V][V], int start)
{
    int queue[QUEUE_SIZE], front = 0, rear = 0;
    int visited[V] = {0};

    queue[rear++] = start;
    visited[start] = 1;

    // 使用stack遍历
    while (front < rear)
    {
        int vertex = queue[front++];
        printf("Visited %d\n", vertex);

        for (int i = 0; i < V; i++)
        {
            if (graph[vertex][i] == 1 && !visited[i])
            {
                queue[rear++] = i;
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

    printf("BFS traversal:\n");
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