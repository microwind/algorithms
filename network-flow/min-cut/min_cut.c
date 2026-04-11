/*
*
 * 最小割算法 - 基于最大流
 *
 * 问题：找到容量最小的割，使源点和汇点不再连通
 *
 * 核心思想：
 * - 使用最大流算法计算最大流
 * - 在残差网络中从源点BFS标记可达顶点
 * - 从可达集到不可达集的边即为最小割
 *
 * 时间复杂度: O(VE²)
 * 空间复杂度: O(V + E)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_V 100

int graph[MAX_V][MAX_V];
int V;

int bfs(int rGraph[MAX_V][MAX_V], int s, int t, int parent[]) {
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;

    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;

                if (v == t) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int maxFlow(int s, int t, int rGraph[MAX_V][MAX_V]) {
    int u, v;
    int parent[MAX_V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = (path_flow < rGraph[u][v]) ? path_flow : rGraph[u][v];
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void minCut(int s, int t) {
    int u, v;
    int rGraph[MAX_V][MAX_V];
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;

    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int max_flow = maxFlow(s, t, rGraph);
    printf("最大流量: %d\n", max_flow);

    queue[rear++] = s;
    visited[s] = 1;

    while (front < rear) {
        u = queue[front++];

        for (v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                visited[v] = 1;
            }
        }
    }

    printf("最小割边:\n");
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            if (visited[u] && !visited[v] && graph[u][v] > 0) {
                printf("  %d -> %d (容量: %d)\n", u, v, graph[u][v]);
            }
        }
    }
}

int main() {
    printf("=== 最小割算法 ===\n");

    V = 6;

    memset(graph, 0, sizeof(graph));

    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][2] = 9;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    int s = 0, t = 5;
    minCut(s, t);

    return 0;
}
