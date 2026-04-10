/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 图的邻接表表示法 (Graph Adjacency List Representation)
 * 
 * 邻接表 vs 邻接矩阵：
 * - 邻接表：适合稀疏图（边数远小于V²），空间复杂度O(V+E)
 * - 邻接矩阵：适合稠密图，空间复杂度O(V²)
 * 
 * 邻接表结构：
 * - 每个顶点维护一个链表，存储其所有邻居
 * - 链表节点包含：目标顶点、指向下一个节点的指针
 * 
 * 应用场景：
 * - 稀疏图的存储（大多数实际问题中的图都是稀疏的）
 * - 社交网络（用户-好友关系）
 * - 网页链接图
 */

#include <stdio.h>
#include <stdlib.h>

#define V 5  // 图的顶点数

/**
 * 链表节点结构
 * 用于存储邻接表中每个顶点的邻居信息
 */
typedef struct Node
{
    int dest;           // 目标顶点（邻居）
    struct Node *next;  // 指向下一个邻居节点
} Node;

/**
 * 图结构（邻接表表示）
 * adjList[i] 是顶点i的邻居链表的头指针
 */
typedef struct Graph
{
    Node *adjList[V];   // 邻接表数组，每个元素是一个链表头
} Graph;

/**
 * 创建空图
 * 初始化所有顶点的邻接链表为空
 * @return 指向新创建的图的指针
 */
Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    // 初始化所有顶点的邻接链表为空
    for (int i = 0; i < V; i++)
        graph->adjList[i] = NULL;
    return graph;
}

/**
 * 添加有向边
 * 
 * @param graph - 图结构指针
 * @param src   - 源顶点
 * @param dest  - 目标顶点
 * 
 * 操作：在src的邻接链表头部插入新节点（dest）
 * 时间复杂度: O(1) - 头插法
 */
void addEdge(Graph *graph, int src, int dest)
{
    // 创建新节点
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->dest = dest;
    
    // 头插法：新节点指向原来的头节点
    newNode->next = graph->adjList[src];
    
    // 更新头指针指向新节点
    graph->adjList[src] = newNode;
}

/**
 * 打印邻接表
 * 遍历每个顶点的邻居链表并输出
 * @param graph - 图结构指针
 */
void printGraph(Graph *graph)
{
    for (int i = 0; i < V; i++)
    {
        printf("Adjacency list of vertex %d: ", i);
        Node *temp = graph->adjList[i];
        while (temp)
        {
            printf(" -> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

/**
 * 主函数：测试邻接表图结构
 * 
 * 测试图结构（有向图）：
 *     0 ----> 1 ----> 2
 *     |       |       |
 *     v       v       v
 *     3 ----> 4 <-----
 * 
 * 边列表：
 * - 0 -> 1, 0 -> 3
 * - 1 -> 2, 1 -> 3, 1 -> 4
 * - 2 -> 4
 * - 3 -> 4
 */
int main()
{
    // 创建空图
    Graph *graph = createGraph();
    
    // 添加有向边
    addEdge(graph, 0, 1);  // 0 -> 1
    addEdge(graph, 0, 3);  // 0 -> 3
    addEdge(graph, 1, 2);  // 1 -> 2
    addEdge(graph, 1, 3);  // 1 -> 3
    addEdge(graph, 1, 4);  // 1 -> 4
    addEdge(graph, 2, 4);  // 2 -> 4
    addEdge(graph, 3, 4);  // 3 -> 4

    // 打印邻接表
    printGraph(graph);
    return 0;
}

/*
jarry@MacBook-Pro graph % gcc graph.c
jarry@MacBook-Pro graph % ./a.out
Adjacency list of vertex 0:  -> 3 -> 1
Adjacency list of vertex 1:  -> 4 -> 3 -> 2
Adjacency list of vertex 2:  -> 4
Adjacency list of vertex 3:  -> 4
Adjacency list of vertex 4:
*/