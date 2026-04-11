/*
*
 * Edmonds-Karp算法 - 使用BFS的最大流算法
 *
 * 问题：在流网络中找到从源点到汇点的最大流量
 *
 * 核心思想：
 * - 使用BFS寻找最短增广路径
 * - 沿增广路径增加流量
 * - 更新残差网络
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

int edmondsKarp(int s, int t) {
    int u, v;
    int rGraph[MAX_V][MAX_V];
    int parent[MAX_V];
    int max_flow = 0;

    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

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

int main() {
    printf("=== Edmonds-Karp算法 ===\n");

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
    int max_flow = edmondsKarp(s, t);

    printf("最大流量: %d\n", max_flow);

    return 0;
}
