/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 */

/**
 * 树递归算法示例 - 二叉树遍历
 * 
 * 算法特点：
 * - 二叉树的遍历是递归的典型应用
 * - 包含前序、中序、后序遍历
 * - 时间复杂度: O(n)，空间复杂度: O(h)
 * 
 * 学习重点：理解递归在树结构中的应用
 */
#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

/**
 * 创建新节点
 * @param data 节点数据
 * @return 新节点指针
 */
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * 前序遍历
 * 时间复杂度: O(n)，空间复杂度: O(h)
 * @param node 根节点
 */
void preOrder(struct Node* node) {
    // 基本情况：空节点
    if (node == NULL) return;
    
    // 访问根节点
    printf("%d ", node->data);
    
    // 递归遍历左子树
    preOrder(node->left);
    
    // 递归遍历右子树
    preOrder(node->right);
}

/**
 * 主函数 - 测试二叉树遍历
 */
int main() {
    // 测试1：创建二叉树
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    // 输出调用过程示例
    printf("调用过程示例：\n");
    printf("preOrder(root)\n");
    printf("   |\n");
    printf("   v\n");
    printf("printf(1)\n");
    printf("preOrder(root->left)\n");
    printf("   |\n");
    printf("   v\n");
    printf("printf(2)\n");
    printf("preOrder(root->left->left)\n");
    printf("   |\n");
    printf("   v\n");
    printf("printf(4)\n");
    printf("preOrder(root->left->right)\n");
    printf("   |\n");
    printf("   v\n");
    printf("printf(5)\n");
    printf("preOrder(root->right)\n");
    printf("   |\n");
    printf("   v\n");
    printf("printf(3)\n");
    printf("\n");

    // 测试2：执行前序遍历
    printf("Preorder traversal of binary tree is \n");
    preOrder(root);

    return 0;
}

/*打印结果
jarry@Mac tree-recursion % gcc tree.c -o tree && ./tree
调用过程示例：
preOrder(root)
   |
   v
printf(1)
preOrder(root->left)
   |
   v
printf(2)
preOrder(root->left->left)
   |
   v
printf(4)
preOrder(root->left->right)
   |
   v
printf(5)
preOrder(root->right)
   |
   v
printf(3)

Preorder traversal of binary tree is 
1 2 4 5 3 
*/