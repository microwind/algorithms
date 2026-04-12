/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 满二叉树数据结构 - C实现
 */

#include <stdio.h>
#include <stdlib.h>

// 树节点结构体
typedef struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
    struct TreeNode *next;
    int value;
} TreeNode;

// 创建新节点
TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->next = NULL;
    return node;
}

// 按 idx 作为根节点的"占位"值，buildHeight 为层数构造满二叉树，并设置 parent 指针
TreeNode* buildFullTree(int idx, int height) {
    if (height <= 0) {
        return NULL;
    }
    TreeNode* node = createNode(idx);
    node->left = buildFullTree(idx * 2, height - 1);
    if (node->left != NULL)
        node->left->parent = node;
    node->right = buildFullTree(idx * 2 + 1, height - 1);
    if (node->right != NULL)
        node->right->parent = node;
    return node;
}

// 先序遍历（根→左→右）
void printPreOrder(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    printf("value: %d\n", node->value);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

// 广度优先遍历（BFS）打印
void printBFS(TreeNode* root) {
    if (root == NULL)
        return;
    
    // 使用数组模拟队列
    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front < rear) {
        TreeNode* n = queue[front++];
        printf("%d ", n->value);
        if (n->left != NULL)
            queue[rear++] = n->left;
        if (n->right != NULL)
            queue[rear++] = n->right;
    }
    printf("\n");
}

// 找到当前节点所在树的根
TreeNode* findRoot(TreeNode* node) {
    while (node->parent != NULL) {
        node = node->parent;
    }
    return node;
}

// 无额外空间遍历单棵树（含 parent 指针），中序风格打印
void traverseTree(TreeNode* root) {
    TreeNode* prev = NULL, *current = root;
    while (current != NULL) {
        TreeNode* next;
        if (prev == current->parent) {
            // 从 parent 下来：优先下探左子
            if (current->left != NULL) {
                next = current->left;
            } else {
                // 否则中序访问自己
                printf("%d ", current->value);
                next = (current->right != NULL ? current->right : current->parent);
            }
        } else if (prev == current->left) {
            // 从左子回到 current：中序访问自己
            printf("%d ", current->value);
            next = (current->right != NULL ? current->right : current->parent);
        } else {
            // 从右子回到 current：回父节点
            next = current->parent;
        }
        prev = current;
        current = next;
    }
}

// 从任意节点开始遍历串联在一起的多棵树
void traverseFromAnyNode(TreeNode* any) {
    TreeNode* root = findRoot(any);
    while (root != NULL) {
        traverseTree(root);
        root = root->next;
    }
    printf("\n");
}

// 对单棵树按层序（BFS）重新赋连续值
int assignLevelOrderValues(TreeNode* root, int startVal) {
    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int val = startVal;
    
    while (front < rear) {
        TreeNode* n = queue[front++];
        n->value = val++;
        if (n->left != NULL)
            queue[rear++] = n->left;
        if (n->right != NULL)
            queue[rear++] = n->right;
    }
    return val;
}

// 释放树内存
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int height = 4;

    // 1) 构造形状（value暂时无意义）
    TreeNode* T1 = buildFullTree(1, height);
    TreeNode* T2 = buildFullTree(1, height);
    TreeNode* T3 = buildFullTree(1, height);

    // 2) 按层序给每棵树分别连续编号：T1 → 1..15, T2 → 16..30, T3 → 31..45
    int nextId = assignLevelOrderValues(T1, 1);
    nextId = assignLevelOrderValues(T2, nextId);
    assignLevelOrderValues(T3, nextId);

    // 3) 串联根：T1 → T2 → T3
    T1->next = T2;
    T2->next = T3;
    T3->next = NULL;

    printf("=== 先序遍历 T1 ===\n");
    printPreOrder(T1);

    printf("\n=== 广度优先遍历 T1 ===\n");
    printBFS(T1);

    // 4) 从任意节点遍历
    printf("\n=== 从任意节点遍历 ===\n");
    traverseFromAnyNode(T3->left);

    // 5) 从 T2 的某个子节点开始，无额外空间遍历整片"森林"
    TreeNode* any = T2->left->left;
    printf("\n=== 从节点 %d 开始无栈遍历 ===\n", any->value);
    traverseFromAnyNode(any);

    // 释放内存
    freeTree(T1);
    freeTree(T2);
    freeTree(T3);

    return 0;
}
