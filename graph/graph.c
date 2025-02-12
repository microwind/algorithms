#include <stdio.h>
#include <stdlib.h>

/* 邻接表表示 */

#define V 5 // 顶点数

// 链表节点
typedef struct Node
{
    int dest;
    struct Node *next;
} Node;

// 图结构
typedef struct Graph
{
    Node *adjList[V];
} Graph;

// 创建图
Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    for (int i = 0; i < V; i++)
        graph->adjList[i] = NULL;
    return graph;
}

// 添加边
void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// 打印邻接表
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

int main()
{
    Graph *graph = createGraph();
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

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