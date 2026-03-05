/*
 * 深度优先搜索（DFS）实现 (C语言)
 * 
 * 特点：
 * - 优先往纵深方向探索
 * - 使用栈或递归
 * - 回溯机制
 * - 时间复杂度：O(V + E)
 * - 空间复杂度：O(V)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_STACK_SIZE 100

// 栈结构
typedef struct {
    int items[MAX_STACK_SIZE];
    int top;
} Stack;

// 图结构（邻接表）
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* adjLists[MAX_VERTICES];
    int numVertices;
} Graph;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;
}

// 检查栈是否为空
bool isStackEmpty(Stack* s) {
    return s->top == -1;
}

// 入栈
void push(Stack* s, int value) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("栈已满\n");
        return;
    }
    s->top++;
    s->items[s->top] = value;
}

// 出栈
int pop(Stack* s) {
    if (isStackEmpty(s)) {
        printf("栈为空\n");
        return -1;
    }
    int item = s->items[s->top];
    s->top--;
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

// DFS递归实现
void dfsRecursive(Graph* graph, int vertex, bool visited[]) {
    // 标记当前顶点为已访问
    visited[vertex] = true;
    printf("%d ", vertex);
    
    // 递归访问所有未访问的邻接顶点
    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        
        if (!visited[adjVertex]) {
            dfsRecursive(graph, adjVertex, visited);
        }
        
        temp = temp->next;
    }
}

// DFS递归遍历（包装函数）
void dfsRecursiveTraversal(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    
    printf("DFS递归遍历结果: ");
    dfsRecursive(graph, startVertex, visited);
    printf("\n");
}

// DFS迭代实现（使用栈）
void dfsIterative(Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = {false};
    Stack stack;
    
    initStack(&stack);
    
    // 将起始顶点入栈
    push(&stack, startVertex);
    
    printf("DFS迭代遍历结果: ");
    
    while (!isStackEmpty(&stack)) {
        // 出栈一个顶点
        int currentVertex = pop(&stack);
        
        // 如果该顶点未被访问
        if (!visited[currentVertex]) {
            visited[currentVertex] = true;
            printf("%d ", currentVertex);
            
            // 将所有未访问的邻接顶点入栈
            // 注意：为了保持与递归相似的顺序，需要反向入栈
            Node* temp = graph->adjLists[currentVertex];
            
            // 先收集所有邻接顶点
            int neighbors[MAX_VERTICES];
            int neighborCount = 0;
            
            while (temp != NULL) {
                int adjVertex = temp->vertex;
                if (!visited[adjVertex]) {
                    neighbors[neighborCount++] = adjVertex;
                }
                temp = temp->next;
            }
            
            // 反向入栈以保持顺序
            for (int i = neighborCount - 1; i >= 0; i--) {
                push(&stack, neighbors[i]);
            }
        }
    }
    
    printf("\n");
}

// DFS查找路径
bool dfsFindPath(Graph* graph, int current, int target, bool visited[], int path[], int* pathIndex) {
    // 标记当前顶点为已访问
    visited[current] = true;
    path[*pathIndex] = current;
    (*pathIndex)++;
    
    // 如果找到目标
    if (current == target) {
        return true;
    }
    
    // 递归访问所有邻接顶点
    Node* temp = graph->adjLists[current];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        
        if (!visited[adjVertex]) {
            if (dfsFindPath(graph, adjVertex, target, visited, path, pathIndex)) {
                return true;
            }
        }
        
        temp = temp->next;
    }
    
    // 回溯：从路径中移除当前顶点
    (*pathIndex)--;
    return false;
}

// 查找两点之间的路径
void findPath(Graph* graph, int start, int end) {
    bool visited[MAX_VERTICES] = {false};
    int path[MAX_VERTICES];
    int pathIndex = 0;
    
    printf("从 %d 到 %d 的路径查找:\n", start, end);
    
    if (dfsFindPath(graph, start, end, visited, path, &pathIndex)) {
        printf("找到路径: ");
        for (int i = 0; i < pathIndex; i++) {
            printf("%d", path[i]);
            if (i < pathIndex - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("未找到路径\n");
    }
}

// DFS检测环
bool dfsDetectCycle(Graph* graph, int vertex, int parent, bool visited[]) {
    visited[vertex] = true;
    
    Node* temp = graph->adjLists[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        
        // 如果邻接顶点未被访问，递归检查
        if (!visited[adjVertex]) {
            if (dfsDetectCycle(graph, adjVertex, vertex, visited)) {
                return true;
            }
        }
        // 如果邻接顶点已被访问且不是父节点，则存在环
        else if (adjVertex != parent) {
            return true;
        }
        
        temp = temp->next;
    }
    
    return false;
}

// 检测图中是否存在环
bool hasCycle(Graph* graph) {
    bool visited[MAX_VERTICES] = {false};
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            if (dfsDetectCycle(graph, i, -1, visited)) {
                return true;
            }
        }
    }
    
    return false;
}

// DFS计算连通分量
void dfsConnectedComponents(Graph* graph) {
    bool visited[MAX_VERTICES] = {false};
    int componentCount = 0;
    
    printf("连通分量:\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            componentCount++;
            printf("分量 %d: ", componentCount);
            
            // 使用DFS遍历当前连通分量
            dfsRecursive(graph, i, visited);
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
    printf("=== 深度优先搜索（DFS）演示 ===\n\n");
    
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
    
    // 1. DFS递归遍历
    printf("1. DFS递归遍历（从顶点0开始）\n");
    dfsRecursiveTraversal(&graph, 0);
    printf("\n");
    
    // 2. DFS迭代遍历
    printf("2. DFS迭代遍历（从顶点0开始）\n");
    dfsIterative(&graph, 0);
    printf("\n");
    
    // 3. 查找路径
    printf("3. 查找路径\n");
    findPath(&graph, 0, 7);
    printf("\n");
    
    // 4. 检测环
    printf("4. 检测环\n");
    if (hasCycle(&graph)) {
        printf("图中存在环\n");
    } else {
        printf("图中不存在环\n");
    }
    printf("\n");
    
    // 5. 计算连通分量
    printf("5. 计算连通分量\n");
    dfsConnectedComponents(&graph);
    printf("\n");
    
    // 6. 从不同起点开始DFS
    printf("6. 从不同起点开始DFS\n");
    printf("从顶点3开始（递归）: ");
    bool visited[MAX_VERTICES] = {false};
    dfsRecursive(&graph, 3, visited);
    printf("\n");
    
    // 释放内存
    freeGraph(&graph);
    
    return 0;
}
