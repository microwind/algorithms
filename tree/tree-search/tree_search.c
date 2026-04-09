/**
 * 版权所有 © https://github.com/microwind 保留所有权利
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 *  树搜索算法 - 矩阵节点路径查找
 * 实现BFS和DFS用于二维矩阵中的最短路径查找
 * 用于路径查找、迷宫求解、图遍历等
 * 支持4方向移动和多条最短路径
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 具有4方向连接的矩阵节点
typedef struct MatrixNode {
    int data;                    // 节点存储的数据
    struct MatrixNode *up;        // 上方节点连接
    struct MatrixNode *down;      // 下方节点连接
    struct MatrixNode *left;      // 左侧节点连接
    struct MatrixNode *right;     // 右侧节点连接
} MatrixNode;

// BFS队列节点
typedef struct QueueNode {
    MatrixNode *node;             // 存储的矩阵节点
    struct QueueNode *next;       // 下一个队列节点指针
} QueueNode;

// BFS队列结构
typedef struct Queue {
    QueueNode *front;             // 队列前端
    QueueNode *rear;              // 队列后端
} Queue;

// 路径结构用于存储路径
typedef struct Path {
    MatrixNode **nodes;           // 路径中的节点数组
    int length;                   // 路径长度
    int capacity;                 // 路径容量
} Path;

/**
 * 创建n x n的互连矩阵节点
 * 
 * 算法:
 * 1. 创建n x n的节点矩阵
 * 2. 用顺序数据初始化每个节点
 * 3. 建立水平连接（左右）
 * 4. 建立垂直连接（上下）
 * 
 * 时间复杂度: O(n²) - 处理n²个节点
 * 空间复杂度: O(n²) - 存储n²个节点
 * 
 * @param n 矩阵维度 (n x n)
 * @return 头节点（左上角）
 */
MatrixNode* create_matrix(int n) {
    MatrixNode ***matrix = (MatrixNode***)malloc(n * sizeof(MatrixNode**));
    
    // 初始化n x n节点矩阵
    for (int i = 0; i < n; i++) {
        matrix[i] = (MatrixNode**)malloc(n * sizeof(MatrixNode*));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (MatrixNode*)malloc(sizeof(MatrixNode));
            matrix[i][j]->data = i * n + j + 1;
            matrix[i][j]->up = NULL;
            matrix[i][j]->down = NULL;
            matrix[i][j]->left = NULL;
            matrix[i][j]->right = NULL;
        }
    }
    
    // 连接左右（水平连接）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            matrix[i][j + 1]->left = matrix[i][j];   // 设置左连接
            matrix[i][j]->right = matrix[i][j + 1]; // 设置右连接
        }
    }

    // 连接上下
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i + 1][j]->up = matrix[i][j];   // 设置上连接
            matrix[i][j]->down = matrix[i + 1][j]; // 设置下连接
        }
    }

    MatrixNode *head = matrix[0][0]; // 获取头节点（左上角）
    
    // 释放矩阵结构但保留节点
    for (int i = 0; i < n; i++) {
        free(matrix[i]); // 释放行内存
    }
    free(matrix); // 释放矩阵内存
    
    return head;
}

/**
 * 从头节点开始打印矩阵
 * 
 * 算法:
 * 1. 从头节点开始逐行遍历
 * 2. 使用down指针移动到下一行
 * 3. 使用right指针在每行内遍历
 * 4. 打印每个节点的数据值
 * 
 * @param head 头节点（左上角）
 * @param n 矩阵维度
 */
void print_matrix(MatrixNode *head, int n) {
    MatrixNode *current_row = head;
    
    for (int i = 0; i < n; i++) {
        MatrixNode *current = current_row;
        for (int j = 0; j < n; j++) {
            printf("%d ", current->data);
            current = current->right;
        }
        printf("\n");
        current_row = current_row->down;
    }
}

/**
 * BFS队列操作
 */

// 创建空队列
Queue* create_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// 将节点入队
void enqueue(Queue *queue, MatrixNode *node) {
    QueueNode *new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->node = node;
    new_node->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

// 从队列中出队
MatrixNode* dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    
    QueueNode *temp = queue->front;
    MatrixNode *node = temp->node;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    return node;
}

// 检查队列是否为空
int is_queue_empty(Queue *queue) {
    return queue->front == NULL;
}

/**
 * 路径操作用于存储和管理路径
 */

// 创建空路径
Path* create_path() {
    Path *path = (Path*)malloc(sizeof(Path));
    path->capacity = 10;
    path->nodes = (MatrixNode**)malloc(path->capacity * sizeof(MatrixNode*));
    path->length = 0;
    return path;
}

// 将节点添加到路径
void add_to_path(Path *path, MatrixNode *node) {
    if (path->length >= path->capacity) {
        path->capacity *= 2;
        path->nodes = (MatrixNode**)realloc(path->nodes, path->capacity * sizeof(MatrixNode*));
    }
    path->nodes[path->length++] = node;
}

// 复制路径
Path* copy_path(Path *path) {
    Path *new_path = create_path();
    new_path->length = path->length;
    new_path->capacity = path->capacity;
    new_path->nodes = (MatrixNode**)malloc(path->capacity * sizeof(MatrixNode*));
    memcpy(new_path->nodes, path->nodes, path->length * sizeof(MatrixNode*));
    return new_path;
}

// 释放路径内存
void free_path(Path *path) {
    free(path->nodes);
    free(path);
}

// 检查路径是否包含节点
int path_contains(Path *path, MatrixNode *node) {
    for (int i = 0; i < path->length; i++) {
        if (path->nodes[i] == node) {
            return 1;
        }
    }
    return 0;
}

// 打印路径
void print_path(Path *path) {
    for (int i = 0; i < path->length; i++) {
        printf("%d", path->nodes[i]->data);
        if (i < path->length - 1) {
            printf(" -> ");
        }
    }
}

/**
 * 使用BFS查找最短路径
 * 
 * 算法:
 * 1. 使用队列进行层序遍历
 * 2. 跟踪最短路径长度
 * 3. 探索所有最小长度路径
 * 4. 使用路径跟踪避免循环
 * 
 * 时间复杂度: O(V + E) - V=顶点数, E=边数
 * 空间复杂度: O(V) - 用于队列和路径存储
 * 
 * @param start 起始节点
 * @param end 目标节点
 * @param path_count 找到的路径数量
 * @return 最短路径数组
 */
Path** find_shortest_paths_bfs(MatrixNode *start, MatrixNode *end, int *path_count) {
    Queue *queue = create_queue();
    Path **paths = (Path**)malloc(sizeof(Path*) * 100); // 最多100条路径
    *path_count = 0;
    int shortest_length = -1;
    
    // 从初始路径开始
    Path *initial_path = create_path();
    add_to_path(initial_path, start);
    enqueue(queue, (MatrixNode*)initial_path);
    
    while (!is_queue_empty(queue)) {
        Path *current_path = (Path*)dequeue(queue);
        MatrixNode *current = current_path->nodes[current_path->length - 1];
        
        // 检查是否到达目标
        if (current == end) {
            if (shortest_length == -1 || current_path->length < shortest_length) {
                shortest_length = current_path->length;
                *path_count = 0;
                paths[(*path_count)++] = copy_path(current_path);
            } else if (current_path->length == shortest_length) {
                paths[(*path_count)++] = copy_path(current_path);
            }
            free_path(current_path);
            continue;
        }
        
        // 如果已找到最短路径且当前路径更长，跳过
        if (shortest_length != -1 && current_path->length >= shortest_length) {
            free_path(current_path);
            continue;
        }
        
        // 探索邻居节点
        MatrixNode *neighbors[] = {current->left, current->up, current->down, current->right};
        
        for (int i = 0; i < 4; i++) {
            MatrixNode *neighbor = neighbors[i];
            if (neighbor && !path_contains(current_path, neighbor)) {
                Path *new_path = copy_path(current_path);
                add_to_path(new_path, neighbor);
                enqueue(queue, (MatrixNode*)new_path);
            }
        }
        
        free_path(current_path);
    }
    
    // 释放队列
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
    
    return paths;
}

/**
 * 打印所有找到的路径
 * 
 * @param paths 路径数组
 * @param path_count 路径数量
 */
void print_paths(Path **paths, int path_count) {
    if (path_count == 0) {
        printf("未找到路径\n");
        return;
    }
    
    printf("最短路径（长度 %d）:\n", paths[0]->length);
    for (int i = 0; i < path_count; i++) {
        printf("  路径 %d: ", i + 1);
        print_path(paths[i]);
        printf("\n");
    }
}

/**
 * 打印分隔线
 */
void print_separator() {
    for (int i = 0; i < 60; i++) {
        printf("=");
    }
    printf("\n");
}

/**
 * 主测试函数
 * 
 * 测试用例:
 * 1. 创建3x3矩阵网络
 * 2. 演示矩阵结构
 * 3. 使用BFS查找最短路径
 * 4. 比较算法特性
 */
int main() {
    int n = 3;
    MatrixNode *head = create_matrix(n);
    
    print_separator();
    printf("树搜索算法 - 矩阵节点路径查找\n");
    print_separator();
    printf("\n");
    
    printf("矩阵结构 (%dx%d):\n", n, n);
    print_matrix(head, n);
    printf("\n");
    
    // 查找特定节点用于演示
    MatrixNode *node2 = head->right;      // 值为2的节点
    MatrixNode *node9 = head;              // 从头节点开始
    // 导航到节点9（右下角）
    for (int i = 0; i < n - 1; i++) {
        node9 = node9->down;
    }
    for (int i = 0; i < n - 1; i++) {
        node9 = node9->right;
    }
    
    if (node2 && node9) {
        // BFS搜索
        printf("从 %d 到 %d 的BFS最短路径:\n", node2->data, node9->data);
        int bfs_path_count;
        Path **bfs_paths = find_shortest_paths_bfs(node2, node9, &bfs_path_count);
        print_paths(bfs_paths, bfs_path_count);
        printf("\n");
        
        // 释放路径
        for (int i = 0; i < bfs_path_count; i++) {
            free_path(bfs_paths[i]);
        }
        free(bfs_paths);
    } else {
        printf("无法找到所需节点\n");
    }
    
    printf("\n=== 算法特性 ===\n");
    printf("BFS（广度优先搜索）:\n");
    printf("  - 保证在无权图中找到最短路径\n");
    printf("  - 使用队列进行层序遍历\n");
    printf("  - 适用于最短路径查找\n");
    
    printf("\n复杂度分析:\n");
    printf("  - 时间复杂度: O(V + E)，其中V是顶点数，E是边数\n");
    printf("  - 空间复杂度: O(V)，用于队列/递归栈\n");
    printf("  - 矩阵导航: 4方向移动（上、下、左、右）\n");
    
    printf("\n=== 应用场景 ===\n");
    printf("矩阵路径查找用于:\n");
    printf("  - 迷宫求解和益智游戏\n");
    printf("  - 网络路由和导航\n");
    printf("  - 游戏AI和路径查找\n");
    printf("  - 电路板设计\n");
    printf("  - 图像处理和分析\n");
    
    return 0;
}
