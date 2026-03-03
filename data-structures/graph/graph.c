#include <stdio.h>
#include <stdlib.h>

/** 邻接表（Adjacency List）可表示图，在C语言使用结构体和链表来实现 */

// 定义节点结构体
struct Node
{
  int vertex;
  struct Node *next;
};

// 定义图结构体
struct Graph
{
  int numVertices;
  struct Node **adjLists;
};

// 创建节点
struct Node *createNode(int v)
{
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// 创建图
struct Graph *createGraph(int vertices)
{
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct Node *));

  for (int i = 0; i < vertices; i++)
  {
    graph->adjLists[i] = NULL;
  }

  return graph;
}

// 添加边
void addEdge(struct Graph *graph, int src, int dest)
{
  struct Node *newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// 打印图
void printGraph(struct Graph *graph)
{
  for (int v = 0; v < graph->numVertices; v++)
  {
    struct Node *temp = graph->adjLists[v];
    printf("\n Vertex %d\n: ", v);
    while (temp)
    {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

int main()
{
  struct Graph *graph = createGraph(4);
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);

  printGraph(graph);

  return 0;
}

/**
jarry@jarrys-MacBook-Pro graph % gcc graph.c  
jarry@jarrys-MacBook-Pro graph % ./a.out 

 Vertex 0
: 2 -> 1 -> 

 Vertex 1
: 2 -> 0 -> 

 Vertex 2
: 3 -> 1 -> 0 -> 

 Vertex 3
: 2 -> 
*/