/*
 * 广度优先搜索（BFS）实现 (C语言)
 * 
 * 特点：
 * - 逐层探索，由近到远
 * - 使用队列（FIFO）
 * - 找到的第一条路径就是最短路径
 * - 时间复杂度：O(V + E)
 * - 空间复杂度：O(V)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_QUEUE_SIZE 100

// 队列结构
typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 图结构（邻接表）
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* adjLists[MAX_VERTICES];
    int numVertices;
} Graph;

// 初始化队列
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// 检查队列是否为空
bool isEmpty(Queue* q) {
    return q->rear == -1;
}

// 入队
void enqueue(Queue* q, int value) {
    if (q->rear == MAX_QUEUE_SIZE - 1) {
        printf("队列已满\n");
        return;
    }
    
    if (q->front == -1) {
        q->front = 0;
    }
    
    q->rear++;
    q->items[q->rear] = value;
}

// 出队
int dequeue(Queue* q) {
    int item;
    
    if (isEmpty(q)) {
        printf("队列为空\n");
        return -1;
    }
    
    item = q->items[q->front];
    q->front++;
    
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    
    return item;
}

// 创建新节点
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 初始化图
void initGraph(Graph* graph, int vertices) {
    graph->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
}

// 添加边（无向图）
void addEdge(Graph* graph, int src, int dest) {
    // 添加 src -> dest 的边
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // 添加 dest -> src 的边（无向图）
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// BFS遍历
void bfs(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Queue q;
    
    initQueue(&q);
    
    // 标记起始顶点为已访问并入队
    visited[startVertex] = true;
    enqueue(&q, startVertex);
    
    printf("BFS遍历结果: ");
    
    while (!isEmpty(&q)) {
        // 出队一个顶点
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);
        
        // 访问所有邻接顶点
        Node* temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(&q, adjVertex);
            }
            
            temp = temp->next;
        }
    }
    
    printf("\n");
}

// BFS查找最短路径
void bfsShortestPath(Graph* graph, int startVertex, int endVertex) {
    bool visited[MAX_VERTICES] = {false};
    int distance[MAX_VERTICES] = {0};
    int parent[MAX_VERTICES];
    Queue q;
    
    initQueue(&q);
    
    // 初始化
    for (int i = 0; i < graph->numVertices; i++) {
        parent[i] = -1;
    }
    
    // 标记起始顶点为已访问并入队
    visited[startVertex] = true;
    enqueue(&q, startVertex);
    
    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        
        // 如果找到目标顶点，停止搜索
        if (currentVertex == endVertex) {
            break;
        }
        
        // 访问所有邻接顶点
        Node* temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                distance[adjVertex] = distance[currentVertex] + 1;
                parent[adjVertex] = currentVertex;
                enqueue(&q, adjVertex);
            }
            
            temp = temp->next;
        }
    }
    
    // 输出最短路径
    if (visited[endVertex]) {
        printf("从 %d 到 %d 的最短路径长度: %d\n", startVertex, endVertex, distance[endVertex]);
        
        // 重建路径
        int path[MAX_VERTICES];
        int pathLength = 0;
        int current = endVertex;
        
        while (current != -1) {
            path[pathLength++] = current;
            current = parent[current];
        }
        
        printf("路径: ");
        for (int i = pathLength - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("从 %d 到 %d 没有路径\n", startVertex, endVertex);
    }
}

// BFS计算连通分量
void bfsConnectedComponents(Graph* graph) {
    bool visited[MAX_VERTICES] = {false};
    int componentCount = 0;
    
    printf("连通分量:\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            componentCount++;
            printf("分量 %d: ", componentCount);
            
            Queue q;
            initQueue(&q);
            
            visited[i] = true;
            enqueue(&q, i);
            
            while (!isEmpty(&q)) {
                int currentVertex = dequeue(&q);
                printf("%d ", currentVertex);
                
                Node* temp = graph->adjLists[currentVertex];
                while (temp != NULL) {
                    int adjVertex = temp->vertex;
                    
                    if (!visited[adjVertex]) {
                        visited[adjVertex] = true;
                        enqueue(&q, adjVertex);
                    }
                    
                    temp = temp->next;
                }
            }
            
            printf("\n");
        }
    }
    
    printf("总连通分量数: %d\n", componentCount);
}

// 释放图内存
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
}

int main() {
    printf("=== 广度优先搜索（BFS）演示 ===\n\n");
    
    // 创建图
    Graph graph;
    int vertices = 8;
    initGraph(&graph, vertices);
    
    // 添加边
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 2, 5);
    addEdge(&graph, 2, 6);
    addEdge(&graph, 3, 7);
    addEdge(&graph, 4, 7);
    addEdge(&graph, 5, 6);
    
    printf("图结构:\n");
    printf("0 -- 1 -- 3 -- 7\n");
    printf("|    |         |\n");
    printf("|    |         |\n");
    printf("2 -- 4 --------|\n");
    printf("|    |\n");
    printf("|    |\n");
    printf("5 -- 6\n\n");
    
    // 1. 基本BFS遍历
    printf("1. 基本BFS遍历（从顶点0开始）\n");
    bfs(&graph, 0);
    printf("\n");
    
    // 2. BFS查找最短路径
    printf("2. BFS查找最短路径\n");
    bfsShortestPath(&graph, 0, 7);
    printf("\n");
    
    // 3. BFS计算连通分量
    printf("3. BFS计算连通分量\n");
    bfsConnectedComponents(&graph);
    printf("\n");
    
    // 4. 从不同起点开始BFS
    printf("4. 从不同起点开始BFS\n");
    printf("从顶点3开始: ");
    bfs(&graph, 3);
    
    // 释放内存
    freeGraph(&graph);
    
    return 0;
}
