/* Copyright https://github.com/microwind */
#include <stdio.h>
#include <stdlib.h>
#define V 6
typedef struct { int items[V], front, rear; } Queue;
void initQueue(Queue* q) { q->front = q->rear = -1; }
int isEmpty(Queue* q) { return q->front == -1; }
void enqueue(Queue* q, int value) {
    if (q->rear == V - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}
int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    if (q->front >= q->rear) q->front = q->rear = -1;
    else q->front++;
    return item;
}
void topologicalSort(int graph[V][V], int numVertices) {
    int inDegree[V] = {0};
    Queue q; initQueue(&q);
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (graph[i][j]) inDegree[j]++;
    for (int i = 0; i < numVertices; i++)
        if (inDegree[i] == 0) enqueue(&q, i);
    int result[V], count = 0;
    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        result[count++] = u;
        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0) enqueue(&q, v);
            }
        }
    }
    if (count != numVertices) { printf("Graph contains cycle\n"); return; }
    printf("Topological Sort: ");
    for (int i = 0; i < count; i++) printf("%d ", result[i]);
    printf("\n");
}
int main() {
    int graph[V][V] = {0};
    graph[5][2] = graph[5][0] = 1;
    graph[4][0] = graph[4][1] = 1;
    graph[2][3] = graph[3][1] = 1;
    topologicalSort(graph, 6);
    return 0;
}
