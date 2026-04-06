/*
 * 图的深度优先搜索 (DFS) 和广度优先搜索 (BFS)
 * 使用递归实现DFS，使用队列实现BFS
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_QUEUE_SIZE 100

// 邻接表表示图
typedef struct Node {
    char vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

typedef struct {
    AdjList* array;
    int numVertices;
} Graph;

// 队列结构（用于BFS）
typedef struct {
    char items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 全局访问标记
bool visited[MAX_VERTICES];

// 创建图
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    
    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// 添加边
void addEdge(Graph* graph, char src, char dest) {
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    
    // 添加 src -> dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->array[srcIndex].head;
    graph->array[srcIndex].head = newNode;
    
    // 添加 dest -> src (无向图)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->array[destIndex].head;
    graph->array[destIndex].head = newNode;
}

// 获取顶点索引
int getVertexIndex(char vertex) {
    return vertex - 'A';
}

// 获取顶点字符
char getVertexChar(int index) {
    return 'A' + index;
}

// DFS递归遍历
void dfsRecursive(Graph* graph, char vertex) {
    int vertexIndex = getVertexIndex(vertex);
    
    // 访问当前节点
    visited[vertexIndex] = true;
    printf("DFS访问: %c\n", vertex);
    
    // 递归访问所有未访问的邻居
    Node* current = graph->array[vertexIndex].head;
    while (current != NULL) {
        int neighborIndex = getVertexIndex(current->vertex);
        if (!visited[neighborIndex]) {
            dfsRecursive(graph, current->vertex);
        }
        current = current->next;
    }
}

// 队列操作
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, char value) {
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

char dequeue(Queue* q) {
    char item;
    if (isEmpty(q)) {
        printf("队列为空\n");
        return '\0';
    }
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// BFS迭代遍历
void bfsIterative(Graph* graph, char start) {
    int numVertices = graph->numVertices;
    
    // 初始化访问标记
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    Queue q;
    initQueue(&q);
    
    int startIndex = getVertexIndex(start);
    visited[startIndex] = true;
    enqueue(&q, start);
    
    printf("\nBFS遍历:\n");
    while (!isEmpty(&q)) {
        char vertex = dequeue(&q);
        printf("BFS访问: %c\n", vertex);
        
        // 将所有未访问的邻居加入队列
        int vertexIndex = getVertexIndex(vertex);
        Node* current = graph->array[vertexIndex].head;
        while (current != NULL) {
            int neighborIndex = getVertexIndex(current->vertex);
            if (!visited[neighborIndex]) {
                visited[neighborIndex] = true;
                enqueue(&q, current->vertex);
            }
            current = current->next;
        }
    }
}

int main() {
    // 创建示例图
    Graph* graph = createGraph(6); // A, B, C, D, E, F
    
    // 添加边
    addEdge(graph, 'A', 'B');
    addEdge(graph, 'A', 'C');
    addEdge(graph, 'B', 'D');
    addEdge(graph, 'B', 'E');
    addEdge(graph, 'C', 'F');
    addEdge(graph, 'E', 'F');
    
    printf("图结构:\n");
    printf("    A\n");
    printf("   / \\\n");
    printf("  B---C\n");
    printf("  |   |\n");
    printf("  D E--F\n");
    printf("\n");
    
    printf("==============================\n");
    printf("DFS深度优先遍历:\n");
    
    // 初始化访问标记
    for (int i = 0; i < 6; i++) {
        visited[i] = false;
    }
    
    dfsRecursive(graph, 'A');
    
    bfsIterative(graph, 'A');
    
    return 0;
}
