/*
 * 图的DFS - 连通分量检测
 * 使用递归DFS找出图中的所有连通分量
 */
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// 邻接矩阵表示图
int graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int numVertices;

// DFS递归遍历
void dfs(int vertex) {
    // 标记当前顶点为已访问
    visited[vertex] = true;
    printf("%d ", vertex);
    
    // 递归访问所有未访问的邻居
    for (int i = 0; i < numVertices; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

// 查找所有连通分量
void findConnectedComponents() {
    int componentCount = 0;
    
    printf("连通分量检测:\n\n");
    
    // 初始化访问数组
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    // 遍历所有顶点，对每个未访问的顶点进行DFS
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            componentCount++;
            printf("连通分量 %d: ", componentCount);
            dfs(i);
            printf("\n");
        }
    }
    
    printf("\n总共找到 %d 个连通分量\n", componentCount);
}

int main() {
    // 创建一个示例图（两个连通分量）
    // 分量1: 0-1-2
    // 分量2: 3-4
    numVertices = 5;
    
    // 初始化邻接矩阵
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph[i][j] = 0;
        }
    }
    
    // 添加边
    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[3][4] = graph[4][3] = 1;
    
    printf("图结构:\n");
    printf("  分量1: 0 -- 1 -- 2\n");
    printf("  分量2: 3 -- 4\n\n");
    
    findConnectedComponents();
    
    return 0;
}
