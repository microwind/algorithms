/*
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * 
 * 拓扑排序算法 (Topological Sort)
 * 
 * 算法原理：
 * - 对有向无环图(DAG)的顶点进行线性排序
 * - 使得对于每条边(u, v)，u在排序中总位于v之前
 * - 使用Kahn算法：基于入度的BFS方法
 * 
 * 时间复杂度: O(V + E)
 * 空间复杂度: O(V)
 * 
 * 应用场景：
 * - 任务调度（有依赖关系的任务）
 * - 课程选修计划（先修课程）
 * - 编译顺序（Makefile依赖）
 * - 数据处理管道
 */

#include <stdio.h>
#include <stdlib.h>

#define V 6  // 图的顶点数量
/**
 * 队列结构定义
 * 用于存储入度为0的顶点
 */
typedef struct { 
    int items[V];  // 队列数组
    int front;     // 队首索引
    int rear;      // 队尾索引
} Queue;

/** 初始化空队列 */
void initQueue(Queue* q) { q->front = q->rear = -1; }

/** 检查队列是否为空 */
int isEmpty(Queue* q) { return q->front == -1; }

/** 入队操作 */
void enqueue(Queue* q, int value) {
    if (q->rear == V - 1) return;      // 队列满
    if (q->front == -1) q->front = 0;  // 第一个元素
    q->items[++q->rear] = value;
}

/** 出队操作 */
int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    if (q->front >= q->rear) q->front = q->rear = -1;  // 队列变空
    else q->front++;
    return item;
}
/**
 * Kahn算法实现拓扑排序
 * 
 * @param graph       - 邻接矩阵表示的有向图
 * @param numVertices - 顶点数量
 * 
 * 算法步骤：
 * 1. 计算所有顶点的入度
 * 2. 将所有入度为0的顶点入队
 * 3. 当队列不为空时：
 *    a. 出队一个顶点u，加入结果
 *    b. 对于u的每个邻居v，入度减1
 *    c. 如果v的入度变为0，入队
 * 4. 如果结果顶点数不等于总顶点数，说明存在环
 */
void topologicalSort(int graph[V][V], int numVertices) {
    int inDegree[V] = {0};   // inDegree[i] = 顶点i的入度
    Queue q; initQueue(&q);
    
    // 步骤1：计算所有顶点的入度
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (graph[i][j]) inDegree[j]++;
    
    // 步骤2：入度为0的顶点入队
    for (int i = 0; i < numVertices; i++)
        if (inDegree[i] == 0) enqueue(&q, i);
    
    int result[V], count = 0;  // 存储拓扑排序结果
    
    // 步骤3：处理队列中的顶点
    while (!isEmpty(&q)) {
        int u = dequeue(&q);       // 取出入度为0的顶点
        result[count++] = u;       // 加入结果
        
        // 更新u的所有邻居的入度
        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v]) {     // 存在边u->v
                inDegree[v]--;     // v的入度减1
                if (inDegree[v] == 0) enqueue(&q, v);  // 入度为0，入队
            }
        }
    }
    
    // 步骤4：检查是否存在环
    if (count != numVertices) { 
        printf("Graph contains cycle - topological sort not possible\n"); 
        return; 
    }
    
    // 输出拓扑排序结果
    printf("Topological Sort: ");
    for (int i = 0; i < count; i++) printf("%d ", result[i]);
    printf("\n");
}
/**
 * 主函数：测试拓扑排序
 * 
 * 测试图结构（DAG示例）：
 *     5 ----> 0 <---- 4
 *     |               |
 *     v               v
 *     2 ----> 3 ----> 1
 * 
 * 边列表：
 * - 5 -> 2, 5 -> 0
 * - 4 -> 0, 4 -> 1
 * - 2 -> 3
 * - 3 -> 1
 * 
 * 可能的拓扑排序结果：5 4 2 3 1 0 或 4 5 2 3 0 1 等
 */
int main() {
    // 初始化邻接矩阵（全0）
    int graph[V][V] = {0};
    
    // 添加有向边（值为1表示有边）
    graph[5][2] = graph[5][0] = 1;  // 5->2, 5->0
    graph[4][0] = graph[4][1] = 1;  // 4->0, 4->1
    graph[2][3] = 1;                // 2->3
    graph[3][1] = 1;                // 3->1
    
    // 执行拓扑排序
    topologicalSort(graph, 6);
    return 0;
}
