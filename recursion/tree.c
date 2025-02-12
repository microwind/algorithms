#include <stdio.h>
#include <stdlib.h>

// 二叉树的遍历（如前序、中序、后序遍历）也是递归的典型应用。
// 定义二叉树节点
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// 创建新节点
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 前序遍历
void preOrder(struct Node* node) {
    if (node == NULL) return; // 基本情况：空节点
    printf("%d ", node->data); // 访问根节点
    preOrder(node->left); // 递归遍历左子树
    preOrder(node->right); // 递归遍历右子树
}

int main() {
    // 创建二叉树
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

/*
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
*/

    printf("Preorder traversal of binary tree is \n");
    preOrder(root);

    return 0;
}