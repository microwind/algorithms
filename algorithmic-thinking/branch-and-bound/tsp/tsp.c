#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_N 10

int dist[MAX_N][MAX_N];
int visited[MAX_N];
int path[MAX_N];
int n;
int minCost;
int currentCost;

// 计算下界（1-树近似法）
int lowerBound(int node, int level) {
    // 简化：使用到未访问城市的最小成本
    int bound = currentCost;
    int minEdge = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            minEdge = (dist[node][i] < minEdge) ? dist[node][i] : minEdge;
        }
    }
    
    bound += minEdge;
    
    // 估计剩余城市的成本
    for (int i = 0; i < n; i++) {
        if (!visited[i] && i != node) {
            int min1 = INT_MAX, min2 = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && j != i) {
                    if (dist[i][j] < min1) {
                        min2 = min1;
                        min1 = dist[i][j];
                    } else if (dist[i][j] < min2) {
                        min2 = dist[i][j];
                    }
                }
            }
            if (min2 != INT_MAX) {
                bound += min1;
            }
        }
    }
    
    return bound;
}

void branchAndBound(int node, int level, int cost) {
    // 剪枝：如果下界超过当前最优解，则跳过该分支
    if (lowerBound(node, level) >= minCost) {
        return;
    }
    
    // 找到完整路径
    if (level == n - 1) {
        int totalCost = cost + dist[node][0];
        if (totalCost < minCost) {
            minCost = totalCost;
            path[level] = node;
        }
        return;
    }
    
    // 分支到未访问的城市
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            path[level] = i;
            currentCost = cost + dist[node][i];
            
            branchAndBound(i, level + 1, currentCost);
            
            visited[i] = 0;
        }
    }
}

int solveTSP() {
    minCost = INT_MAX;
    currentCost = 0;
    memset(visited, 0, sizeof(visited));
    
    visited[0] = 1;
    path[0] = 0;
    
    branchAndBound(0, 1, 0);
    
    return minCost;
}

int main() {
    n = 4;
    int graph[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    memcpy(dist, graph, sizeof(graph));
    
    printf("旅行商问题 - 分支定界算法\n");
    printf("距离矩阵:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
    
    int minTourCost = solveTSP();
    printf("\n最小路径成本: %d\n", minTourCost);
    printf("路径: 0");
    for (int i = 1; i < n; i++) {
        printf(" -> %d", path[i]);
    }
    printf(" -> 0\n");
    
    return 0;
}
